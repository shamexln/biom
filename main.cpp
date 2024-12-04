#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <map>
#include <sstream>
#include <bitset>
using namespace std;

std::map<string, unsigned char> fixedresult {{"12-19", 0x01}, {"17-29", 0x02}, {"23-33", 0x04}, {"23-43", 0x08}, {"23-53", 0x10}, {"31-40", 0x20}, {"31-55", 0x40}, {"38-50", 0x80}};
std::vector<std::pair<string, unsigned char>>  results;
struct RANGE {
    int min;
    int max;
};


int gindex = 0;

double calc(const vector<RANGE>& ranges) {
    int num = 0;
    int _min = INT_MAX;
    int _max = INT_MIN;

    for (const auto& range : ranges) {
        num += (range.max - range.min);
        _min = min(_min, range.min);
        _max = max(_max, range.max);
    }

    int de = _max - _min;
    return static_cast<double>(num) / de;
}

void exec(const vector<RANGE>& ranges, vector<RANGE>& current, int index) {
    if (index == ranges.size()) {
        if (!current.empty() && calc(current) <= 1.35) {
            std::stringstream ss;
            std::stringstream summary;
            unsigned char sum = 0x00;
            cout << "可能的组合: ";
            auto value = 0;
            auto max = current[0].max;
            auto min = current[0].min;
            for (const auto& range : current) {
                ss.str("");
                ss << range.min << "-" << range.max;
                sum += fixedresult[ss.str()];
                summary << range.min << "-" << range.max << ", ";
                cout << range.min << "-" << range.max << ", ";
                value += range.max - range.min;
                max = range.max > max ? range.max : max;
                min = range.min < min ? range.min : min;
            }
            cout << endl;
            results.emplace_back(std::make_pair(summary.str(), sum));
            cout << "结果: " <<value << "/" << max - min << ": " << calc(current) << endl;

            cout << endl;
        }
        return;
    }

    current.push_back(ranges[index]);
    exec(ranges, current, index + 1);

    current.pop_back();
    exec(ranges, current, index + 1);
}

bool checkelemet(std::vector<std::pair<std::string, unsigned char>> &vct, std::pair<std::string, unsigned char> elem)
{
    /*if (vct.size() == 0)
    {
        return true;
    }
    for (int i =0; i< vct.size(); i++)
    {

        if (0 != (vct[i].second & pair.second))
        {
            return false;
        }


    }
    return true;*/
    return std::find(vct.begin(), vct.end(), elem) != vct.end();
}

// 递归函数，用来查找组合
void findCombinations(std::vector<std::pair<std::string, unsigned char>>& sumresult,
                      std::vector<std::pair<std::string, unsigned char>>& finalresult,
                      unsigned char ssum, int index) {
    // 如果 ssum 已经达到 255，则输出并返回
    if (ssum == 255) {
        gindex++;
        std::cout << "Group : " << gindex << std::endl;
        std::for_each(finalresult.begin(), finalresult.end(), [](std::pair<std::string, unsigned char> p) {
            std::bitset<8> binary(p.second);
            std::cout << p.first << std::endl;
            //std::cout << p.first << ": " << binary << std::endl;
        });
        std::cout << std::endl;
        return;
    }

    // 遍历 sumresult 中的元素，尝试添加到 finalresult 中
    for (int jj = index; jj < sumresult.size(); jj++) {
        // 如果当前元素与 ssum 的按位与为 0，表示可以合并
        if (0 == (sumresult[jj].second & ssum)) {
            auto bExist = checkelemet(finalresult, sumresult[jj]);
            if (!bExist) {
                finalresult.push_back(sumresult[jj]);  // 添加元素
                findCombinations(sumresult, finalresult, ssum + sumresult[jj].second, jj + 1);  // 递归调用
                finalresult.pop_back();  // 回溯，移除当前元素
            }
        }
    }
}

int main() {
    vector<RANGE> ranges = {
            {12, 19},{17, 29}, {23, 33}, {23, 43}, {23, 53}, {31, 40}, {31, 55}, {38, 50}
    };

    vector<RANGE> current;
    exec(ranges, current, 0);




    for (int i =0; i< results.size(); i++) {
        std::vector<std::pair<std::string, unsigned char>> sumresult;
        auto fr = results[i].second;
        for (int j = i + 1; j < results.size()  ; j++)
        {
            if (0 == (results[j].second & fr))
            {
                // 说明results[i].second元素没有和fr里面重合
                sumresult.emplace_back(std::make_pair(results[j].first, results[j].second));
            }
        }

        if (!sumresult.empty())
        {
            //找到和results[i]相匹配的数据，所以把results[i]也加入
            sumresult.emplace_back(std::make_pair(results[i].first, results[i].second));
        }

        //这一轮找好，现在还是排列组合
        std::vector<std::pair<std::string, unsigned char>> finalresult;
        unsigned char ssum = 0;
        findCombinations(sumresult, finalresult, ssum, 0);
        /*for (int ii =0; ii< sumresult.size(); ii++) {

            auto fr = sumresult[ii].second;
            ssum += sumresult[ii].second;
            finalresult.emplace_back(std::make_pair(sumresult[ii].first, sumresult[ii].second));
            for (int jj = ii + 1; jj < sumresult.size()  ; jj++)
            {
                if (0 == (sumresult[jj].second & fr))
                {
                    // 说明results[i].second元素没有和fr里面重合
                    auto bExist = checkelemet(finalresult, sumresult[jj]);
                    if(bExist)
                    {
                        ssum += sumresult[jj].second;
                        finalresult.emplace_back(std::make_pair(sumresult[jj].first, sumresult[jj].second));
                        if(ssum == 255)
                        {
                            std::for_each(finalresult.begin(), finalresult.end(), [](std::pair<std::string ,  int > p) {
                                std::bitset<8> binary(p.second);
                                std::cout << p.first << " " << std::endl;
                            });
                            std::cout << std::endl;
                            finalresult.clear();
                            ssum = 0;
                        }
                    }

                }
            }
            finalresult.clear();
            ssum = 0;
        }*/

    }
    std::cout <<  "Finish" << std::endl;
    _getch();
    return 0;
}


