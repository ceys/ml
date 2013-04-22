#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;


struct sample {
    string type;
    vector<int> features;
};

struct output {
    string id;
    string type;
};

struct typeDistance {
    string type;
    float distance;
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
        sort(ts.begin(), ts.end());
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


bool comp(typeDistance& t1, typeDistance& t2) {
    return t1.distance < t2.distance ? true : false;
}

string classify(const vector<sample>& train, vector<int>& test, string& id) {
    float distance;
    typeDistance td;
    td.id = "";
    td.distance = 0.0;
    vector<typeDistance> topN(td, 11);
    make_heap(topN.begin(), topN.end(), comp);
    for (vector<sample>::iterator iter = train.begin(); iter != train.end(); ++iter) {
        distance = jaccard_distance(*iter.features, &test);
        if (topN.frout().distance < distance) {
            pop_heap(topN.begin(),topN.end());
            topN.pop_back();
            typeDistance intd;
            intd.id = *id;
            intd.distance = distance;
            topN.push_back(intd);
            push_heap(topN.begin(),topN.end());
        }
    }
    map<string, int> countmap;
    for (vector<typeDistance>::iterater iter = topN.begin(); iter != topN.end(); ++iter) {
        countMap


void knn_process(const vector<sample>& train, const string pattern) {
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
        out.type = classify(train, &test)
        
    }
       

int main() {
    int va1[] = {1,2,3,4,5,6};
    int va2[] = {2,3,4,8,9};
    vector<int> v1(va1,va1+6);
    vector<int> v2(va2,va2+5); 
    float x = jaccard_distance(v1,v2);
    cout << x << endl;
    
    int test;
    while (cin >> test) {
        cout << test;
    }
    return 0;
}
