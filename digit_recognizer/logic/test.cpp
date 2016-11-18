#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <assert.h>
#include <iomanip>
using namespace std;
const double eps = 1e-14;
int n, m;
class Image {
 public:
    vector<int> pixel;
    int num;
    int y;
};

vector<Image> train, test, pre;
vector<double> theta[10];

void read() {
    char ch;
    int d;
    Image image;
    image.pixel = vector<int>(785, 1);
    train.clear();
    int num = 0;
    while (scanf("%d", &num) != EOF) {
        image.num = num;
        for (int i = 1; i <= 784; ++i) {
            getchar();
            scanf("%d", &image.pixel[i]);
            if (image.pixel[i]) {
                image.pixel[i] = 1;
            }
        }
        train.push_back(image);
    }
    m = train.size();
}

double dot(vector<double> &theta, vector<int> &pixel) {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += theta[i] * pixel[i];
    }
    return sum;
}

double costfunction(vector<double> &y, vector<double> &theta, double lambda) {
    double cost = 0.0;
    for (int i = 0; i < m; ++i) {
        cost += (-log(y[i] + eps) * train[i].y - log(1.0 - y[i] + eps) * (1.0 - train[i].y));
    }
    for (int i = 1; i < n; ++i) {
        cost += lambda * theta[i] * theta[i] / 2;
    }
    cost /= m;
    return cost;
}


double g(double x) {
    return 1.0 / (1.0 + exp(-x));
}

int main() {
    n = 785;
    ifstream in("theta");
    for (int i = 0; i < 10; ++i) {
        double t;
        for (int j = 0; j < n; ++j) {
            in >> t;
            theta[i].push_back(t);
        }
    }

    freopen("../data/train.csv", "r", stdin);
    read();
    int tolnum = m;
    m = m * 7 / 10;
    for (int i = m; i < tolnum; ++i) {
        test.push_back(train[i]);
    }
    train.erase(train.begin() + m, train.begin() + tolnum);
    int tol = 0, right = 0;
    cout << "Test set lagre " << test.size() << endl;
    for (auto &image : test) {
        ++tol;
        int num = -1;
        double max_p = 0.0;
        for (int dig = 0; dig < 10; ++dig) {
            double p = g(dot(theta[dig], image.pixel));
            // cout << "Probability of " << dig << " " << p << " ";
            if (p > max_p) {
                max_p = p;
                num = dig;
            }
        }
        cout << image.num << " is classfied as : " << num << endl;
        if (num == image.num) {
            ++right;
        }
    }
    double acc = 1.0 * right / tol;
    printf("acc = %9lf\n", acc);
    return 0;
}
