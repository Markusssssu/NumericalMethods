#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

const double EPS = 1e-4;

bool isConvergent(const vector<vector<double>>& C) {
    for (int i = 0; i < C.size(); ++i) {
        double sum = 0.0;
        for (int j = 0; j < C[i].size(); ++j) {
            if (i != j) sum += fabs(C[i][j]);
        }
        if (sum >= 1.0) return false;
    }
    return true;
}

vector<double> simpleIteration(
    const vector<vector<double>>& A,
    const vector<double>& b,
    const vector<double>& x0,
    double eps,
    int maxIter
) {
    int n = A.size();
    vector<double> x = x0;
    vector<double> x_new(n);

    for (int k = 0; k < maxIter; ++k) {
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (j != i) sum += A[i][j] * x[j];
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        double diff = 0.0;
        for (int i = 0; i < n; ++i) {
            diff += fabs(x_new[i] - x[i]);
        }

        x = x_new;

        if (diff < eps) {
            cout << "Итераций выполнено: " << k + 1 << endl;
            break;
        }
    }

    return x;
}

int main() {

    setlocale(LC_ALL, "ru");

    vector<vector<double>> A = {
        {0.62, 0.81, 0.77},
        {0.03, 1.11, -1.08},
        {0.97, 0.02, -1.08}
    };

    vector<double> b = { 1.0, 1.0, 1.0 };

    vector<double> x0 = { 0.0, 0.0, 0.0 };

    vector<vector<double>> C(A.size(), vector<double>(A.size()));
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A.size(); ++j) {
            if (i == j) C[i][j] = 0.0;
            else C[i][j] = -A[i][j] / A[i][i];
        }
    }


    vector<double> x = simpleIteration(A, b, x0, EPS, 1000);

    cout << "a11 * x1 + a12 * x2 + a13 * x3 = b1" << "\n";
    cout << "a21 * x1 + a22 * x2 + a23 * x3 = b1" << "\n";
    cout << "a31 * x1 + a32 * x2 + a33 * x3 = b1" << "\n";

    cout << setprecision(6);
    cout << "Решение системы:" << endl;
    for (int i = 0; i < x.size(); ++i) {
        cout << "x[" << i + 1 << "] = " << x[i] << endl;
    }

    for (int i = 0; i < A.size(); ++i)
    {
        for (int j = 0; j < A.size(); ++j)
            std::cout << std::setw(4) << A[i][j];
            std::cout << std::endl;
    }

    return 0;
}
