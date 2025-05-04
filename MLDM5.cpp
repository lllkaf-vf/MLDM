#include <iostream>
#include <vector>
#include <locale>
using namespace std;

int main() {
    setlocale(LC_ALL, "russian");
    int n;
    cout << "Введите размерность матрицы (количество вершин орграфа): ";
    cin >> n;
    vector<vector <int>> m(n, vector<int>(n));
    cout << "Введите матрицу смежности орграфа: " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> m[i][j];
        }
    }
    vector<vector<int>> w = m;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                w[i][j] = w[i][j] || (w[i][k] && w[k][j]);
            }
        }
    }
    cout << endl;
    cout << "матрица достижимости: " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << w[i][j] << "  ";
        }
        cout << endl;
    }
    return 0;
}
