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

// ツアーを出力する関数
void print_tour(const vector<int>& tour) {
    for (int city : tour) {
        cout << city << endl;
    }
    cout << endl;
}

// Union-Find
struct UnionFind {
    vector<int> par, rank, siz;

    // 構造体の初期化
    UnionFind(int n) : par(n, -1), rank(n, 0), siz(n, 1) {}

    // 根を求める
    int root(int x) {
        if (par[x] == -1) return x; // x が根の場合は x を返す
        else return par[x] = root(par[x]); // 経路圧縮
    }

    // x と y が同じグループに属するか (= 根が一致するか)
    bool issame(int x, int y) {
        return root(x) == root(y);
    }

    // x を含むグループと y を含むグループを併合する
    bool unite(int x, int y) {
        int rx = root(x), ry = root(y); // x 側と y 側の根を取得する
        if (rx == ry) return false; // すでに同じグループのときは何もしない
        // union by rank
        if (rank[rx] < rank[ry]) swap(rx, ry); // ry 側の rank が小さくなるようにする
        par[ry] = rx; // ry を rx の子とする
        if (rank[rx] == rank[ry]) rank[rx]++; // rx 側の rank を調整する
        siz[rx] += siz[ry]; // rx 側の siz を調整する
        return true;
    }

    // x を含む根付き木のサイズを求める
    int size(int x) {
        return siz[root(x)];
    }
};

// グラフのための構造体
struct Edge {
    double cost;
    int small;
    int large;

    Edge(double w, int s, int l) : cost(w), small(s), large(l) {}
};

//コストをソートするための関数
bool compare(const Edge& a,Edge& b){
    return a.cost<b.cost;
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

    //エッジを追加
    vector<Edge> edges;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            edges.push_back(Edge(dist[i][j], i, j));
        }
    }

    //コストでソート
    sort(edges.begin(),edges.end(),compare);

    //最小全域木を作る
    UnionFind uf(N);
    vector<vector<int>> min_tree(N,vector<int>(0));

    while (!edges.empty()){
        Edge edge=*edges.begin();
        if(uf.issame(edge.small,edge.large)){
            edges.erase(edges.begin());
        }else{
            uf.unite(edge.small,edge.large);
            min_tree[edge.small].push_back(edge.large);
            edges.erase(edges.begin());
        }
        
    }

    //0から深さ優先探索をする
    vector<int>tour;
    vector<int>visited(N,0);
    while(tour.size()<N){
        
    }

    



    int current_city = 0;
    set<int> unvisited_cities;
    for (int i = 1; i < N; ++i) {
        unvisited_cities.insert(i);
    }

    vector<int> tour = {current_city};

    // 最も近い都市を見つける
    while (!unvisited_cities.empty()) {
        auto compare = [&](int city1, int city2) {
            return dist[current_city][city1] < dist[current_city][city2];
        };
        auto it = min_element(unvisited_cities.begin(), unvisited_cities.end(), compare);
        int next_city = *it;

        unvisited_cities.erase(it);
        tour.push_back(next_city);
        current_city = next_city;
    }

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

