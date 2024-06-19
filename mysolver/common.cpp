
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>

using namespace std;
using City=pair<double,double>;

// 距離を計算する関数
double distance(pair<double, double> city1, pair<double, double> city2) {
    return sqrt(pow(city1.first - city2.first, 2) + pow(city1.second - city2.second, 2));
}

// ツアーを出力する関数
void print_tour(const vector<int>& tour) {
    for (int city : tour) {
        cout << city << endl;
    }
    cout << endl;
}


vector<pair<double, double>> read_input(const string& filename) {
    ifstream input_file(filename);
    if (!input_file) {
        cerr << "Error: Unable to open input file: " << filename << endl;
        exit(1);
    }

    string line;
    // 最初の行（ヘッダー）をスキップ
    getline(input_file, line);

    vector<pair<double, double>> cities;
    while (getline(input_file, line)) {
        stringstream ss(line);
        string x_str, y_str;
        if (getline(ss, x_str, ',') && getline(ss, y_str, ',')) {
            double x = stod(x_str);
            double y = stod(y_str);
            cities.emplace_back(x, y);
        }
    }
    return cities;
}