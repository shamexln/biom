#include <iostream>
#include <ostream>
#include <vector>
#include <map>
#include <iterator>

int getcuff(std::map<int,int> minorder) {
    int min =0;
    int max = 0 ;
    for (auto & it : minorder) {
        min += it.first;
        max += it.second;
    }
    return max - min;
}
int main() {
    std::vector<std::pair<int, int>> sum;
    std::vector<std::pair<int, int>> vct;
    vct.emplace_back(12,19);
    vct.emplace_back(17,29);
    vct.emplace_back(23,33);
    vct.emplace_back(23,43);
    vct.emplace_back(23,53);
    vct.emplace_back(31,40);
    vct.emplace_back(31,55);
    vct.emplace_back(35,50);


    // for two elements
    for (int i = 0; i < vct.size(); i++) {
        auto [min, max] = vct[i];
        for (int j = i +1; j < vct.size(); j++) {
            auto result = vct[j].second - vct[i].first;
            auto diff = (result + max - min) / (max > vct[j].second
                                                    ? max
                                                    : vct[j].second - min < vct[j].first
                                                          ? min
                                                          : vct[j].first);
            if (diff <= 1.35) {
                std::cout <<  "group begin" <<  std::endl;
                std::cout << vct[i].first << " " << vct[i].second << std::endl;
                std::cout << vct[j].first << " " << vct[j].second << std::endl;
                std::cout <<  "group end" <<  std::endl;

            }
        }
    }

    // for three elements

    for (int i = 0; i < vct.size(); i++) {
        std::map<int,int> minorder;
        std::map<int,int> maxorder;
        auto [min, max] = vct[i];
        minorder.insert(std::make_pair(min, max));
        maxorder.insert(std::make_pair(max, min));

        for (int j = i +1; j < vct.size(); j++) {
            auto fnd = minorder.find(min);
            minorder.erase(++fnd, minorder.end());

            auto fnd1 = maxorder.find(max);
            maxorder.erase(++fnd1, maxorder.end());

            auto [min2, max2] = vct[j];
            minorder.insert(std::make_pair(min2, max2));
            maxorder.insert(std::make_pair(max2, min2));
            for (int k = j +1; k < vct.size(); k++) {
                auto fnd = minorder.find(min2);
                minorder.erase(++fnd, minorder.end());

                auto fnd1 = maxorder.find(max2);
                maxorder.erase(++fnd1, maxorder.end());

                auto result = vct[k].second - vct[k].first;
                minorder.insert(std::make_pair(vct[k].first, vct[k].second));
                maxorder.insert(std::make_pair(vct[k].second, vct[k].first));

                auto itmaxend = maxorder.end();
                itmaxend--;
                auto itminbegin = minorder.begin();

                auto cuff = getcuff(minorder);

                auto diff = cuff /(itmaxend->first - itminbegin->first);

                if (diff <= 1.35) {
                    std::cout <<  "max value in group " <<  std::endl;
                    std::cout << itmaxend->first << " " <<  std::endl;
                    std::cout <<  "min value in group" <<  std::endl;
                    std::cout << itminbegin->first << std::endl;
                    std::cout <<  "cuff value in group" <<  std::endl;
                    std::cout << cuff << std::endl;

                    std::cout <<  "group begin" <<  std::endl;
                    std::cout << vct[i].first << " " << vct[i].second << std::endl;
                    std::cout << vct[j].first << " " << vct[j].second << std::endl;
                    std::cout << vct[k].first << " " << vct[k].second << std::endl;
                    std::cout <<  "group end" <<  std::endl;

                }
            }
        }
    }
    return 0;
}
