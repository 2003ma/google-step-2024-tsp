#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>

using namespace std;

// 距離を計算する関数
double distance(pair<double, double> city1, pair<double, double> city2) {
    return sqrt(pow(city1.first - city2.first, 2) + pow(city1.second - city2.second, 2));
}

// 2-opt法によるツアーの改善
vector<int> two_opt(vector<int> tour, const vector<vector<double>>& dist, int max_iterations = 10000) {
    int N = tour.size();
    bool improvement = true;
    int iteration = 0;

    while (improvement && iteration < max_iterations) {
        improvement = false;
        for (int i = 1; i < N - 1; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (j - i == 1) continue;
                if (dist[tour[i - 1]][tour[i]] + dist[tour[j]][tour[(j + 1) % N]] > dist[tour[i - 1]][tour[j]] + dist[tour[i]][tour[(j + 1) % N]]) {
                    reverse(tour.begin() + i, tour.begin() + j + 1); 
                    improvement = true;
                }
            }
        }
        ++iteration;
    }

    return tour;
}

//or_opt法によるツアーの改善
vector<int> or_opt(vector<int> tour, const vector<vector<double>>& dist, int max_iterations = 10000) {
    int N = tour.size();
    bool improvement = true;
    int iteration = 0;

    while (improvement && iteration < max_iterations) {
        improvement = false;
        for (int i = 1; i < N - 1; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (j - i == 1) continue;
                double d1=dist[tour[i-1]][tour[i]];
                double d2=dist[tour[i]][tour[(i+1)%N]];
                double d3=dist[tour[j]][tour[(j+1)%N]];
                double d4=dist[tour[i-1]][tour[(i+1)%N]];
                double d5=dist[tour[j]][tour[i]];
                double d6=dist[tour[(j+1)%N]][tour[i]];
                if(d1+d2+d3>d4+d5+d6){
                    int move_city=tour[i];
                    tour.erase(tour.begin() + i);
                    tour.insert(tour.begin()+j,move_city);
                    improvement = true;
                }
            }
        }
        ++iteration;
    }

    return tour;
}

// ツアーを出力する関数
void print_tour(const vector<int>& tour) {
    for (int city : tour) {
        cout << city << endl;
    }
}

// ツアーを計算する関数
vector<int> solve(const vector<pair<double, double>>& cities) {
    int N = cities.size();

    // 距離行列を計算
    vector<vector<double>> dist(N, vector<double>(N, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            dist[i][j] = dist[j][i] = distance(cities[i], cities[j]);
        }
    }

    int current_city = 0;
    set<int> unvisited_cities;
    for (int i = 1; i < N; ++i) {
        unvisited_cities.insert(i);
    }

    vector<int> tour = {current_city};

    // 最も近い都市を見つける
    while (!unvisited_cities.empty()) {
        int next_city = *min_element(unvisited_cities.begin(), unvisited_cities.end(), [&](int city1, int city2) {
            return dist[current_city][city1] < dist[current_city][city2];
        });

        unvisited_cities.erase(next_city);
        tour.push_back(next_city);
        current_city = next_city;
    }

    // 最後に出発都市に戻る
    tour.push_back(0);

    // 2-opt法でツアーを改善
    tour = two_opt(tour, dist);
    tour=or_opt(tour,dist);
    return tour;
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

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    vector<pair<double, double>> cities = read_input(argv[1]);
    vector<int> tour = solve(cities);
    cout << "index" << endl;
    print_tour(tour);

    return 0;
}
