#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
using namespace std;

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
            cout << "可能的组合: ";
            auto value = 0;
            auto max = current[0].max;
            auto min = current[0].min;
            for (const auto& range : current) {
                cout << range.min << "-" << range.max << ", ";
                value += range.max - range.min;
                max = range.max > max ? range.max : max;
                min = range.min < min ? range.min : min;
            }
            cout << endl;
            cout << "结果: " << value << "/" << max - min << ": " << calc(current) << endl;
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
            {17, 29}, {23, 33}, {23, 43}, {23, 53}, {31, 40}, {31, 55}, {35, 50}
    };

    vector<RANGE> current;
    exec(ranges, current, 0);
    _getch();
    return 0;
}