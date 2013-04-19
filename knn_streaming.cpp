#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;


struct sample {
    string type;
    vector<int> features;
};


//为了效率，使用该函数前需要把特征id号转换为整数,并按升序排序
float jaccard_distance(const vector<int>& v1, const vector<int>& v2) {
    int inter_num = 0;
    unsigned int i,j;
    i = j = 0;
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] == v2[j]) {
            ++i;
            ++j;
            ++inter_num;
        } else if (v1[i] < v2[j]) {
            ++i;
        } else {
            ++j;
        }
    }
    cout << inter_num;
    return (1.0 - ((float)inter_num / (v1.size() + v2.size() - inter_num)));
}


void readTrain(vector<sample>& train, const string& file) {
    ifstream fin(file.c_str());
    string line;
    int d = 0;
    while (getline(fin, line)) {
        istringstream sin(line);
        sample ts;
        sin >> ts.type;
        while (sin >> d) {
            ts.features.push_back(d);
        }
        train.push_back(ts);
    }
    fin.close();
}

//ToDo:可以考虑在这个函数加入对特征排序的选项
vector<int> split_to_int(string& str, const string& pattern) {
    string::size_type pos;
    str += pattern;
    int size = str.size();
    vector<int> result;

    for (int i=0; i<size; ++i) {
        pos = str.find(pattern);
        if (pos < size) {
             result.push_back((int)str.substr(i, pos-1));
             i = pos + pattern.size() -1;
        }
    }
    return result;
}


void knnProcess(const vector<sample>& train, const string pattern) {
    string line;
    while (cin >> line) { 
        

int main() {
    int va1[] = {1,2,3,4,5,6};
    int va2[] = {2,3,4,8,9};
    vector<int> v1(va1,va1+6);
    vector<int> v2(va2,va2+5); 
    float x = jaccard_distance(v1,v2);
    cout << x << endl;
    return 0;
}
