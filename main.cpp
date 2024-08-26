#include <iostream>
#include <ostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>

int getmin(std::vector<std::pair<int,int>> v) {
    std::vector<int> minvct;
    for (auto it = v.begin(); it != v.end(); it++) {
        minvct.emplace_back(it->first);
    }
    std::sort(minvct.begin(), minvct.end());
    return minvct[0];
}

int getmax(std::vector<std::pair<int,int>> v) {
    std::vector<int> maxvct;
    for (auto it = v.begin(); it != v.end(); it++) {
        maxvct.emplace_back(it->second);
    }
    std::sort(maxvct.begin(), maxvct.end());
    return maxvct[maxvct.size()-1];
}

float getcuff(std::vector<std::pair<int,int>> v) {
    int min =0;
    int max = 0 ;
    for (auto it = v.begin(); it != v.end(); it++) {
        min += it->first;
        max += it->second;
    }
    return max - min;
}

float getcuff(std::map<int,int> minorder) {
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
   // vct.emplace_back(12,19);
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
            auto result = vct[j].second - vct[j].first;
            float f = (float)(result + max - min);
            float g  = max >= vct[j].second ? max : vct[j].second;
            float gg = min <= vct[j].first ? min : vct[j].first;
            float ff = (max >= vct[j].second ? max : vct[j].second) -  (min <= vct[j].first ? min : vct[j].first);
            float diff = (float)(result + max - min) / (float)((max >= vct[j].second ? max : vct[j].second) -  (min <= vct[j].first ? min : vct[j].first));
            if (diff <= 1.35) {
                std::cout <<  "group begin 2 element" <<  std::endl;
                std::cout << vct[i].first << " " << vct[i].second << std::endl;
                std::cout << vct[j].first << " " << vct[j].second << std::endl;
                std::cout <<  "group end 2 element" <<  std::endl;
            }
        }
    }

    // for three elements
    for (int i = 0; i < vct.size(); i++) {
        std::vector<std::pair<int,int>> tmp;
        auto [min, max] = vct[i];
        tmp.emplace_back(min, max);

        for (int j = i +1; j < vct.size(); j++) {
            auto fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min && pair.second == max; });
            if (fnd != tmp.end()) {
                tmp.erase(++fnd, tmp.end());
            }
            auto [min2, max2] = vct[j];
            tmp.emplace_back(min2, max2);
            for (int k = j +1; k < vct.size(); k++) {
                auto fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min2 && pair.second == max2; });
                if (fnd != tmp.end()) {
                    tmp.erase(++fnd, tmp.end());
                }
                auto result = vct[k].second - vct[k].first;
                tmp.emplace_back(vct[k].first, vct[k].second);

                int nmax = getmax(tmp);
                int nmin = getmin(tmp);
                float cuff = getcuff(tmp);

                float diff = (float)cuff /(float)(nmax - nmin);

                if (diff <= 1.35) {
                    std::cout <<  "max value in group " <<  std::endl;
                    std::cout << nmax << " " <<  std::endl;
                    std::cout <<  "min value in group" <<  std::endl;
                    std::cout << nmin << std::endl;
                    std::cout <<  "cuff value in group" <<  std::endl;
                    std::cout << cuff << std::endl;

                    std::cout <<  "group begin 3 element" <<  std::endl;
                    std::cout << vct[i].first << " " << vct[i].second << std::endl;
                    std::cout << vct[j].first << " " << vct[j].second << std::endl;
                    std::cout << vct[k].first << " " << vct[k].second << std::endl;
                    std::cout <<  "group end 3 element" <<  std::endl;

                }
            }
        }
    }


    // for four  elements
    for (int i = 0; i < vct.size(); i++) {
        std::vector<std::pair<int,int>> tmp;
        auto [min, max] = vct[i];
        tmp.emplace_back(min, max);

        for (int j = i +1; j < vct.size(); j++) {
            auto fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min && pair.second == max; });
            if (fnd != tmp.end()) {
                tmp.erase(++fnd, tmp.end());
            }

            auto [min2, max2] = vct[j];
            tmp.emplace_back(min2, max2);
            for (int k = j +1; k < vct.size(); k++) {
                fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min2 && pair.second == max2; });
                if (fnd != tmp.end()) {
                    tmp.erase(++fnd, tmp.end());
                }

                auto [min3, max3] = vct[k];
                auto result = vct[k].second - vct[k].first;
                tmp.emplace_back(min3, max3);
                for (int l =  k + 1; l < vct.size(); l++) {
                    fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min3 && pair.second == max3; });
                    if (fnd != tmp.end()) {
                        tmp.erase(++fnd, tmp.end());
                    }

                    auto [min4, max4] = vct[l];
                    result = vct[l].second - vct[l].first;
                    tmp.emplace_back(min4, max4);

                    int nmax = getmax(tmp);
                    int nmin = getmin(tmp);

                    float cuff = getcuff(tmp);

                    float diff = (float)cuff /(float)(nmax - nmin);

                    if (diff <= 1.35) {
                        std::cout <<  "max value in group " <<  std::endl;
                        std::cout << nmax << " " <<  std::endl;
                        std::cout <<  "min value in group" <<  std::endl;
                        std::cout << nmin << std::endl;
                        std::cout <<  "cuff value in group" <<  std::endl;
                        std::cout << cuff << std::endl;

                        std::cout <<  "group begin 4 element" <<  std::endl;
                        std::cout << vct[i].first << " " << vct[i].second << std::endl;
                        std::cout << vct[j].first << " " << vct[j].second << std::endl;
                        std::cout << vct[k].first << " " << vct[k].second << std::endl;
                        std::cout << vct[l].first << " " << vct[l].second << std::endl;
                        std::cout <<  "group end 4 element" <<  std::endl;

                    }
                }
            }
        }
    }


    // for five  elements
    for (int i = 0; i < vct.size(); i++) {
        std::vector<std::pair<int,int>> tmp;
        auto [min, max] = vct[i];
        tmp.emplace_back(min, max);

        for (int j = i +1; j < vct.size(); j++) {
            auto fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min && pair.second == max; });
            if (fnd != tmp.end()) {
                tmp.erase(++fnd, tmp.end());
            }

            auto [min2, max2] = vct[j];
            tmp.emplace_back(min2, max2);
            for (int k = j +1; k < vct.size(); k++) {
                auto fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min2 && pair.second == max2; });
                if (fnd != tmp.end()) {
                    tmp.erase(++fnd, tmp.end());
                }

                auto [min3, max3] = vct[k];
                auto result = vct[k].second - vct[k].first;
                tmp.emplace_back(min3, max3);
                for (int l =  k + 1; l < vct.size(); l++) {
                    fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min3 && pair.second == max3; });
                    if (fnd != tmp.end()) {
                        tmp.erase(++fnd, tmp.end());
                    }

                    auto [min4, max4] = vct[l];
                    result = vct[l].second - vct[l].first;
                    tmp.emplace_back(min4, max4);

                    for (int m = l + 1; m < vct.size(); m++) {
                        fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min4 && pair.second == max4; });
                        if (fnd != tmp.end()) {
                            tmp.erase(++fnd, tmp.end());
                        }

                        auto [min5, max5] = vct[m];
                        result = vct[m].second - vct[m].first;
                        tmp.emplace_back(min5, max5);

                        int nmax = getmax(tmp);
                        int nmin = getmin(tmp);

                        float cuff = getcuff(tmp);

                        float diff = cuff /(nmax-nmin);

                        if (diff <= 1.35) {
                            std::cout <<  "max value in group " <<  std::endl;
                            std::cout << nmax << " " <<  std::endl;
                            std::cout <<  "min value in group" <<  std::endl;
                            std::cout << nmin << std::endl;
                            std::cout <<  "cuff value in group" <<  std::endl;
                            std::cout << cuff << std::endl;

                            std::cout <<  "group begin 5 element" <<  std::endl;
                            std::cout << vct[i].first << " " << vct[i].second << std::endl;
                            std::cout << vct[j].first << " " << vct[j].second << std::endl;
                            std::cout << vct[k].first << " " << vct[k].second << std::endl;
                            std::cout << vct[l].first << " " << vct[l].second << std::endl;
                            std::cout << vct[m].first << " " << vct[m].second << std::endl;
                            std::cout <<  "group end 5 element" <<  std::endl;

                        }
                    }

                }
            }
        }
    }

    // for six  elements
    for (int i = 0; i < vct.size(); i++) {
        std::vector<std::pair<int,int>> tmp;
        auto [min, max] = vct[i];
        tmp.emplace_back(min, max);

        for (int j = i +1; j < vct.size(); j++) {
            /*auto fnd =  std::find(minorder.rbegin() , minorder.rend(), min);
            minorder.erase(std::next(fnd).base(), minorder.end());

            auto fnd1 =  std::find(maxorder.rbegin() , maxorder.rend(), max);
            maxorder.erase(std::next(fnd1).base(), maxorder.end());*/
            auto fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min && pair.second == max; });
            if (fnd != tmp.end()) {
                tmp.erase(++fnd, tmp.end());
            }

            auto [min2, max2] = vct[j];
            tmp.emplace_back(min2, max2);
            for (int k = j +1; k < vct.size(); k++) {
                fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min2 && pair.second == max2; });
                if (fnd != tmp.end()) {
                    tmp.erase(++fnd, tmp.end());
                }

                auto [min3, max3] = vct[k];
                auto result = vct[k].second - vct[k].first;
                tmp.emplace_back(min3, max3);
                for (int l =  k + 1; l < vct.size(); l++) {
                    fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min3 && pair.second == max3; });
                    if (fnd != tmp.end()) {
                        tmp.erase(++fnd, tmp.end());
                    }

                    auto [min4, max4] = vct[l];
                    result = vct[l].second - vct[l].first;
                    tmp.emplace_back(min4, max4);

                    for (int m = l + 1; m < vct.size(); m++) {
                        fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min4 && pair.second == max4; });
                        if (fnd != tmp.end()) {
                            tmp.erase(++fnd, tmp.end());
                        }

                        auto [min5, max5] = vct[m];
                        result = vct[m].second - vct[m].first;
                        tmp.emplace_back(min5, max5);

                        for (int n = m + 1; n < vct.size(); n++) {
                            fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min5 && pair.second == max5; });
                            if (fnd != tmp.end()) {
                                tmp.erase(++fnd, tmp.end());
                            }
                            auto [min6, max6] = vct[n];
                            result = vct[n].second - vct[n].first;
                            tmp.emplace_back(min6, max6);

                            int nmax = getmax(tmp);
                            int nmin = getmin(tmp);

                            float cuff = getcuff(tmp);

                            float diff = cuff /(nmax-nmin);

                            if (diff <= 1.35) {
                                std::cout <<  "max value in group " <<  std::endl;
                                std::cout << nmax << " " <<  std::endl;
                                std::cout <<  "min value in group" <<  std::endl;
                                std::cout << nmin<< std::endl;
                                std::cout <<  "cuff value in group" <<  std::endl;
                                std::cout << cuff << std::endl;

                                std::cout <<  "group begin 6 element" <<  std::endl;
                                std::cout << vct[i].first << " " << vct[i].second << std::endl;
                                std::cout << vct[j].first << " " << vct[j].second << std::endl;
                                std::cout << vct[k].first << " " << vct[k].second << std::endl;
                                std::cout << vct[l].first << " " << vct[l].second << std::endl;
                                std::cout << vct[m].first << " " << vct[m].second << std::endl;
                                std::cout << vct[n].first << " " << vct[n].second << std::endl;
                                std::cout <<  "group end 6 element" <<  std::endl;

                            }
                        }

                    }

                }
            }
        }
    }


    // for seven  elements
    for (int i = 0; i < vct.size(); i++) {
        std::vector<std::pair<int,int>> tmp;
        auto [min, max] = vct[i];
        tmp.emplace_back(min, max);

        for (int j = i +1; j < vct.size(); j++) {
            auto fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min && pair.second == max; });
            if (fnd != tmp.end()) {
                tmp.erase(++fnd, tmp.end());
            }

            auto [min2, max2] = vct[j];
            tmp.emplace_back(min2, max2);
            for (int k = j +1; k < vct.size(); k++) {
                fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min2 && pair.second == max2; });
                if (fnd != tmp.end()) {
                    tmp.erase(++fnd, tmp.end());
                }

                auto [min3, max3] = vct[k];
                auto result = vct[k].second - vct[k].first;
                tmp.emplace_back(min3, max3);
                for (int l =  k + 1; l < vct.size(); l++) {
                    fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min3 && pair.second == max3; });
                    if (fnd != tmp.end()) {
                        tmp.erase(++fnd, tmp.end());
                    }

                    auto [min4, max4] = vct[l];
                    result = vct[l].second - vct[l].first;
                    tmp.emplace_back(min4, max4);

                    for (int m = l + 1; m < vct.size(); m++) {
                        fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min4 && pair.second == max4; });
                        if (fnd != tmp.end()) {
                            tmp.erase(++fnd, tmp.end());
                        }

                        auto [min5, max5] = vct[m];
                        result = vct[m].second - vct[m].first;
                        tmp.emplace_back(min5, max5);

                        for (int n = m + 1; n < vct.size(); n++) {
                            fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min5 && pair.second == max5; });
                            if (fnd != tmp.end()) {
                                tmp.erase(++fnd, tmp.end());
                            }

                            auto [min6, max6] = vct[n];
                            result = vct[n].second - vct[n].first;
                            tmp.emplace_back(min6, max6);

                            for (int  o = n + 1; o < vct.size(); o ++) {
                                fnd = std::find_if(tmp.begin(), tmp.end(), [=](const auto& pair){ return pair.first == min6 && pair.second == max6; });
                                if (fnd != tmp.end()) {
                                    tmp.erase(++fnd, tmp.end());
                                }

                                auto [min7, max7] = vct[o];
                                result = vct[o].second - vct[o].first;
                                tmp.emplace_back(min7, max7);

                                int nmax = getmax(tmp);
                                int nmin = getmin(tmp);
                                float cuff = getcuff(tmp);

                                float diff = cuff /(nmax-nmin);

                                if (diff <= 1.35) {
                                    std::cout <<  "max value in group " <<  std::endl;
                                    std::cout << nmax << " " <<  std::endl;
                                    std::cout <<  "min value in group" <<  std::endl;
                                    std::cout << nmin << std::endl;
                                    std::cout <<  "cuff value in group" <<  std::endl;
                                    std::cout << cuff << std::endl;

                                    std::cout <<  "group begin 7 element" <<  std::endl;
                                    std::cout << vct[i].first << " " << vct[i].second << std::endl;
                                    std::cout << vct[j].first << " " << vct[j].second << std::endl;
                                    std::cout << vct[k].first << " " << vct[k].second << std::endl;
                                    std::cout << vct[l].first << " " << vct[l].second << std::endl;
                                    std::cout << vct[m].first << " " << vct[m].second << std::endl;
                                    std::cout << vct[n].first << " " << vct[n].second << std::endl;
                                    std::cout << vct[o].first << " " << vct[o].second << std::endl;
                                    std::cout <<  "group end 7 element" <<  std::endl;

                                }
                            }

                        }

                    }

                }
            }
        }
    }

    // for eight  elements
    /*for (int i = 0; i < vct.size(); i++) {
        std::map<int,int> minorder;
        std::map<int,int> maxorder;
        auto [min, max] = vct[i];
        minorder.insert(std::make_pair(min, max));
        maxorder.insert(std::make_pair(max, min));

        for (int j = i +1; j < vct.size(); j++) {
            auto fnd = std::find_if(minorder.begin(), minorder.end(),  [=](const auto& pair) { return pair.first == min && pair.second == max; } );
            if (fnd != minorder.end()) {
                minorder.erase(++fnd, minorder.end());
            }

            auto fnd1 = std::find_if(maxorder.begin(), maxorder.end(),  [=](const auto& pair) { return pair.first == max && pair.second == min; } );
            if (fnd1 != maxorder.end()) {
                maxorder.erase(++fnd1, maxorder.end());
            }

            auto [min2, max2] = vct[j];
            minorder.insert(std::make_pair(min2, max2));
            maxorder.insert(std::make_pair(max2, min2));
            for (int k = j +1; k < vct.size(); k++) {
                fnd = std::find_if(minorder.begin(), minorder.end(),  [=](const auto& pair) { return pair.first == min2 && pair.second == max2; } );
                if (fnd != minorder.end()) {
                    minorder.erase(++fnd, minorder.end());
                }

                fnd1 = std::find_if(maxorder.begin(), maxorder.end(),  [=](const auto& pair) { return pair.first == max2 && pair.second == min2; } );
                if (fnd1 != maxorder.end()) {
                    maxorder.erase(++fnd1, maxorder.end());
                }

                auto [min3, max3] = vct[k];
                auto result = vct[k].second - vct[k].first;
                minorder.insert(std::make_pair(min3, max3));
                maxorder.insert(std::make_pair(max3, min3));
                for (int l =  k + 1; l < vct.size(); l++) {
                    fnd = std::find_if(minorder.begin(), minorder.end(),  [=](const auto& pair) { return pair.first == min3 && pair.second == max3; } );
                    if (fnd != minorder.end()) {
                        minorder.erase(++fnd, minorder.end());
                    }

                    fnd1 = std::find_if(maxorder.begin(), maxorder.end(),  [=](const auto& pair) { return pair.first == max3 && pair.second == min3; } );
                    if (fnd1 != maxorder.end()) {
                        maxorder.erase(++fnd1, maxorder.end());
                    }

                    auto [min4, max4] = vct[l];
                    result = vct[l].second - vct[l].first;
                    minorder.insert(std::make_pair(min4, max4));
                    maxorder.insert(std::make_pair(max4, min4));

                    for (int m = l + 1; m < vct.size(); m++) {
                        fnd = std::find_if(minorder.begin(), minorder.end(),  [=](const auto& pair) { return pair.first == min4 && pair.second == max4; } );
                        if (fnd != minorder.end()) {
                            minorder.erase(++fnd, minorder.end());
                        }

                        fnd1 = std::find_if(maxorder.begin(), maxorder.end(),  [=](const auto& pair) { return pair.first == max4 && pair.second == min4; } );
                        if (fnd1 != maxorder.end()) {
                            maxorder.erase(++fnd1, maxorder.end());
                        }

                        auto [min5, max5] = vct[m];
                        result = vct[m].second - vct[m].first;
                        minorder.insert(std::make_pair(min5, max5));
                        maxorder.insert(std::make_pair(max5, min5));

                        for (int n = m + 1; n < vct.size(); n++) {
                            fnd = std::find_if(minorder.begin(), minorder.end(),  [=](const auto& pair) { return pair.first == min5 && pair.second == max5; } );
                            if (fnd != minorder.end()) {
                                minorder.erase(++fnd, minorder.end());
                            }

                            fnd1 = std::find_if(maxorder.begin(), maxorder.end(),  [=](const auto& pair) { return pair.first == max5 && pair.second == min5; } );
                            if (fnd1 != maxorder.end()) {
                                maxorder.erase(++fnd1, maxorder.end());
                            }

                            auto [min6, max6] = vct[n];
                            result = vct[n].second - vct[n].first;
                            minorder.insert(std::make_pair(min6, max6));
                            maxorder.insert(std::make_pair(max6, min6));

                            for (int  o = n + 1; o < vct.size(); o ++) {
                                fnd = std::find_if(minorder.begin(), minorder.end(),  [=](const auto& pair) { return pair.first == min6 && pair.second == max6; } );
                                if (fnd != minorder.end()) {
                                    minorder.erase(++fnd, minorder.end());
                                }

                                fnd1 = std::find_if(maxorder.begin(), maxorder.end(),  [=](const auto& pair) { return pair.first == max6 && pair.second == min6; } );
                                if (fnd1 != maxorder.end()) {
                                    maxorder.erase(++fnd1, maxorder.end());
                                }

                                auto [min7, max7] = vct[o];
                                result = vct[o].second - vct[o].first;
                                minorder.insert(std::make_pair(min7, max7));
                                maxorder.insert(std::make_pair(max7, min7));

                                for ( int p = o + 1; p < vct.size(); p++) {
                                    fnd = std::find_if(minorder.begin(), minorder.end(),  [=](const auto& pair) { return pair.first == min7 && pair.second == max7; } );
                                    if (fnd != minorder.end()) {
                                        minorder.erase(++fnd, minorder.end());
                                    }

                                    fnd1 = std::find_if(maxorder.begin(), maxorder.end(),  [=](const auto& pair) { return pair.first == max7 && pair.second == min7; } );
                                    if (fnd1 != maxorder.end()) {
                                        maxorder.erase(++fnd1, maxorder.end());
                                    }

                                    auto [min8, max8] = vct[p];
                                    result = vct[p].second - vct[p].first;
                                    minorder.insert(std::make_pair(min8, max8));
                                    maxorder.insert(std::make_pair(max8, min8));

                                    auto itmaxend = maxorder.end();
                                    itmaxend--;
                                    auto itminbegin = minorder.begin();

                                    float cuff = getcuff(minorder);

                                    float diff = cuff /(itmaxend->first - itminbegin->first);

                                    if (diff <= 1.35) {
                                        std::cout <<  "max value in group " <<  std::endl;
                                        std::cout << itmaxend->first << " " <<  std::endl;
                                        std::cout <<  "min value in group" <<  std::endl;
                                        std::cout << itminbegin->first << std::endl;
                                        std::cout <<  "cuff value in group" <<  std::endl;
                                        std::cout << cuff << std::endl;

                                        std::cout <<  "group begin 8 element" <<  std::endl;
                                        std::cout << vct[i].first << " " << vct[i].second << std::endl;
                                        std::cout << vct[j].first << " " << vct[j].second << std::endl;
                                        std::cout << vct[k].first << " " << vct[k].second << std::endl;
                                        std::cout << vct[l].first << " " << vct[l].second << std::endl;
                                        std::cout << vct[m].first << " " << vct[m].second << std::endl;
                                        std::cout << vct[n].first << " " << vct[n].second << std::endl;
                                        std::cout << vct[o].first << " " << vct[o].second << std::endl;
                                        std::cout << vct[p].first << " " << vct[p].second << std::endl;
                                        std::cout <<  "group end 8 element" <<  std::endl;

                                    }
                                }

                            }

                        }

                    }

                }
            }
        }
    }*/
    return 0;
}
