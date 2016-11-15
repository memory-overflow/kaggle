#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
const int K = 5;

struct map {
    int num;
    vector<int> pixel;
    int dis(vector<int> &_pixel) {
        int ret = 0;
        for (int i = 0; i < _pixel.size(); ++i) {
            ret += (pixel[i] - _pixel[i]) * (pixel[i] - _pixel[i]);
        }
        return ret;
    }
};
vector<map> train, test;
vector< pair<int, int> > dis;

int main() {
    ifstream cin_train("../data/train.csv");
    train.clear();
    int num;
    while (cin_train >> num) {
        map image;
        image.num = num;
        for (int i = 0; i < 784; ++i) {
            char ch;
            cin_train >> ch;
            int d;
            cin_train >> d;
            image.pixel.push_back(d);
        }
        train.push_back(image);
    }
    cin_train.close();
    ifstream cin_test("../data/test.csv");
    int d;
    while (cin_test >> d) {
        map image;
        image.num = 0;
        image.pixel.push_back(d);
        for (int i = 1; i < 784; ++i) {
            char ch;
            cin_test >> ch;
            cin_test >> d;
            image.pixel.push_back(d);
        }
        test.push_back(image);
    }
    cin_test.close();
    for (int i = 0; i < test.size(); ++i) {
        dis.clear();
        for (int j = 0; j < train.size(); ++j) {
            dis.push_back(make_pair(test[i].dis(train[j].pixel), train[j].num));
        }
        sort(dis.begin(), dis.end());
        int num[10] = {0};
        for (int j = 0; j < K; ++j) {
            ++num[dis[j].second];
        }
        for (int j = 0; j < 10; ++j) {
            if (num[j] >= num[test[i].num]) {
                test[i].num = j;
            }
        }
    }
    ofstream out("result.csv");
    out << "ImageId,Labek" << endl;
    for (int i = 0; i < test.size(); ++i) {
        out << i + 1 << "," << test[i].num << endl;
    }
    return 0;
}
