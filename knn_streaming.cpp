#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;


struct sample {
    string type;
    vector<int> features;
};

struct output {
    string id;
    string type;
};

typedef pair<string, float> TypeDistance;


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
        sort(ts.features.begin(), ts.features.end());
        train.push_back(ts);
    }
    fin.close();
}


bool comp(const TypeDistance& t1, const TypeDistance& t2) {
    return t1.second < t2.second ? true : false;
}

string classify(const vector<sample>& train, vector<int>& test) {
    float distance;
    TypeDistance td("",0.0);
    vector<TypeDistance> topN(11, td);
    make_heap(topN.begin(), topN.end(), comp);
    for (vector<sample>::iterator iter = train.begin(); iter != train.end(); ++iter) {
        distance = jaccard_distance(iter->features, test);
        if (topN.front().second < distance) {
            pop_heap(topN.begin(),topN.end());
            topN.pop_back();
            TypeDistance intd(iter->type, distance);
            topN.push_back(intd);
            push_heap(topN.begin(),topN.end());
        }
    }
    map<string, int> countMap;
    for (vector<TypeDistance>::iterater iter = topN.begin(); iter != topN.end(); ++iter) {
        ++countMap[iter->type];
    }
    return *max_element(countMap.begin(), countMap.end());
}


void knn_process(vector<sample>& train) {
    string line;
    int d = 0;
    vector<int> test;
    while (getline(cin, line)) {
        istringstream sin(line);
        output out;
        sin >> out.id;
        while (sin >> d) {
            test.push_back(d);
        }
        sort(test.begin(), test.end());
        out.type = classify(train, test);
        cout << out.id << "\t" << out.type;
        test.clear();
    }
}
       

int main() {
    const string inputfile = "";
    vector<sample> train;
    readTrain(train, inputfile);
    knn_process(train);
}
