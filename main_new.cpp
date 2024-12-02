#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <map>
#include <sstream>
using namespace std;

std::map<string, int> fixedresult {{"12-19", 0x01}, {"17-29", 0x02}, {"23-33", 0x04}, {"23-43", 0x08}, {"23-53", 0x10}, {"31-40", 0x20}, {"31-55", 0x40}, {"35-50", 0x80}};
std::map<string, int>  results;
struct RANGE {
    int min;
    int max;
};

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
            results[summary.str()] = sum;
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

int main() {
    vector<RANGE> ranges = {
            {12, 19},{17, 29}, {23, 33}, {23, 43}, {23, 53}, {31, 40}, {31, 55}, {35, 50}
    };

    vector<RANGE> current;
    exec(ranges, current, 0);
    std::for_each(results.begin(), results.end(), [](std::pair<std::string ,  int > p) {
            std::cout << p.first << p.second << " ";
    });
    std::cout << std::endl;

    _getch();
    return 0;
}
