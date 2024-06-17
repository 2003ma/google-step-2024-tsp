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

vector<int> three_opt(vector<int> tour,const vector<vector<double>>& dist, int max_iterations=1000){
    int N = tour.size();
    bool improvement = true;
    int iteration = 0;

    while(improvement && iteration<max_iterations){
        improvement=false;
        for(int i=1;i<N-2;++i){
            for(int j=i+1;j<N-1;++j){
                for(int k=j+1;k<N;++k){
                    if (j - i == 1) continue;
                    if (k - j == 1) continue;
                    
                }
            }
        }
    }
}
