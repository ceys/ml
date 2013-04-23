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

typedef pair<int, float> CountDistance;
typedef pair<string, float> TypeDistance;


//此函数会被恐怖地调用(预测样本数*训练样本数)次，是决定程序性能的关键。
//不同的距离函数需要使用不同的数据结构存储特征向量,jaccard需要求交集
//求交集复杂度：vector,set:特征需有序，O(min(n,m)~m+n); hash_set:特征无需有序，O(n|m) ps:stl的set是由红黑树实现的
inline float jaccard_distance(const vector<int>& v1, const vector<int>& v2) {
    unsigned short inter_num = 0;
    unsigned short i,j;
    const unsigned short vsize1 = v1.size();
    const unsigned short vsize2 = v2.size();
    i = j = 0;
    while (i < vsize1 && j < vsize2) {
        if (v1[i] < v2[j]) {
            ++i;
        } else if (v1[i] > v2[j]) {
            ++j;
        } else {
            ++i;
            ++j;
            ++inter_num;
        }
    }
    return ((float)inter_num / (vsize1 + vsize2 - inter_num));
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
    return t2.second > t1.second ? true : false;
}


string classify(vector<sample>& train, vector<int>& test, map<string, float>& threshold) {
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
    map<string, CountDistance> countMap;
    for (vector<TypeDistance>::iterator iter2 = topN.begin(); iter2 != topN.end(); ++iter2) {
        ++(countMap[iter2->first].first);
        countMap[iter2->first].second += countMap[iter2->first].second;
    }
    map<string, CountDistance>::iterator it_map = max_element(countMap.begin(), countMap.end());
    if (threshold[it_map->first] > (it_map->second).second) return it_map->first;
    else return "0";
}


//ToDo：自己实现最大堆取top n，这个make_heap的泛型算法比较慢
/*
string classify_todo(vector<sample>& train, vector<int>& test) {
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
    for (vector<TypeDistance>::iterator iter2 = topN.begin(); iter2 != topN.end(); ++iter2) {
        ++countMap[iter2->first];
    }
    return max_element(countMap.begin(), countMap.end())->first;
}
*/

void knn_process(vector<sample>& train) {
    string line;
    int d = 0;
    vector<int> test;
    const char* tab = "\t";
    const char* eol = "\n";
    map<string, float> threshold;
    threshold["1"] = 0.0;
    threshold["2"] = 0.0;
    while (getline(cin, line)) {
        istringstream sin(line);
        output out;
        sin >> out.id;
        while (sin >> d) {
            test.push_back(d);
        }
        sort(test.begin(), test.end());
        out.type = classify(train, test, threshold);
        cout << out.id << tab << out.type << eol;
        test.clear();
    }
}
       

int main() {
    const string inputfile = "train";
    vector<sample> train;
    readTrain(train, inputfile);
    knn_process(train);
}

