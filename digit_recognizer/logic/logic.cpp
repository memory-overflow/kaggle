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

vector<Image> train, test, predict;

void read() {
    char ch;
    int d;
    Image image;
    image.pixel = vector<int>(785, 0);
    train.clear();
    int num = 0;
    while (scanf("%d", &num) != EOF) {
        image.num = num;
        for (int i = 1; i <= 784; ++i) {
            getchar();
            scanf("%d", &image.pixel[i]);
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

double diff(vector<double> &y, int dim) {
    double ret = 0;
    for (int i = 0; i < m; ++i) {
        ret += (y[i] - train[i].y) * train[i].pixel[dim];
    }
    return ret;
}

double g(double x) {
    return 1.0 / (1.0 + exp(-x));
}


void train_theta(int dig, int step, double lambda, double alpha) {
    cout << "Train dig " << dig << endl;
    vector<double> theta(n, 1);
    vector<double> cost;
    for (int s = 0; s < step; ++s) {
        vector<double> h;
        for (int i = 0; i < m; ++i) {
            h.push_back(g(dot(theta, train[i].pixel)));
            train[i].y = (train[i].num == dig);
        }
        double tmp = costfunction(h, theta, lambda);
        cost.push_back(tmp);
        printf("cost = %.9lf\n", tmp);
        theta[0] -= alpha * diff(h, 0);
        for (int i = 1; i < n; ++i) {
            theta[i] -= alpha * (diff(h, i) + lambda * theta[i]) / m;
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%.9lf ", theta[i]);
    }
    cout << endl;
    ofstream out("theta", ios::app);
    for (int i = 0; i < n; ++i) {
        out << setprecision(9) << theta[i] << " ";
    }
    out << endl;
}

int main() {
    freopen("../data/train.csv", "r", stdin);
    read();
    n = 785;
    int tolnum = m;
    m = m * 7 / 10;
    for (int i = m; i < tolnum; ++i) {
        test.push_back(train[i]);
    }
    train.erase(train.begin() + m, train.begin() + tolnum);
    for (int dig = 0; dig < 10; ++dig) {
        train_theta(dig, 1000, 0.0, 0.01);
    }
    return 0;
}
