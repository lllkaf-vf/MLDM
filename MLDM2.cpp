#include <iostream>
#include <locale>
using namespace std;

// Вывод матрицы отношения
void printArr(int** arr, int size) {
    cout << "Ваша матрица отношения: " << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

// Ввод матрицы отношения
void scanArr(int** arr, int size) {
    for (int i = 0; i < size; ++i) {
        cout << "Введите " << i + 1 << " строку матрицы отношения: ";
        for (int j = 0; j < size; ++j) {
            cin >> arr[i][j];
            if (arr[i][j] != 1 && arr[i][j] != 0) {
                cout << "Ввод некорректный! Попробуйте ещё раз" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                i = i - 1;
                break;
            }
        }
    }
}

// Проверка отношения на РЕФЛЕКСИВНОСТЬ
bool checkReflexivity(int** arr, int size) {
    for (int i = 0; i < size; ++i) {
        // Если хоть одно включение на главной диагонали не равно 1, то матрица не рефлексивна
        if (arr[i][i] == 0) {
            return false;
        }
    }
    return true;
}

// Проверка отношения на СИММЕТРИЧНОСТЬ
bool checkSymmetry(int** arr, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Если симметричные включения не равны, то матрица не симметрична
            if (arr[i][j] != arr[j][i]) {
                return false;
            }
        }
    }
    return true;
}

// Проверка отношения на КОСОСИММЕТРИЧНОСТЬ
bool checkSkewSymmetry(int** arr, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Если симметричные включения равны при неравных i и j, то матрица не кососимметрична
            if (arr[i][j] == arr[j][i] && i != j) {
                return false;
            }
        }
    }
    return true;
}

// Проверка отношения на ТРАНЗИТИВНОСТЬ
bool checkTransitivity(int** arr, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Если нашли пару (i, j) равную 1
            if (arr[i][j] == 1) {
                // Поиск пары (j, i) == 1 в строке номер j и проверка пары (i , i).
                // Если есть пара (j, i) равная 1 и пара (i, i) не равна 1, то
                // возвращаем false, потому что пары (i, j) и (j, i) не влекут за собой пару (i, i).
                // Если пара (i, i) равно 1, то проверяем дальше.
                for (int iz = 0; iz < size; ++iz) {
                    if (arr[j][iz] == 1 && arr[i][iz] != 1) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}


int main() {
    setlocale(LC_ALL, "russian");
    int n;
    cout << "Введите размерность матрицы отношения n x n: ";
    cin >> n;

    int** arr = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; ++i) {
        arr[i] = (int*)malloc(sizeof(int) * n);
    }

    scanArr(arr, n);
    printArr(arr, n);

    checkReflexivity(arr, n) ? cout << "Отношение РЕФЛЕКСИВНО" << endl : cout << "Отношение НЕ РЕФЛЕКСИВНО" << endl;
    checkSymmetry(arr, n) ? cout << "Отношение СИММЕТРИЧНО" << endl : cout << "Отношение НЕ СИММЕТРИЧНО" << endl;
    checkSkewSymmetry(arr, n) ? cout << "Отношение КОСОСИММЕТРИЧНО" << endl : cout << "Отношение НЕ КОСОСИММЕТРИЧНО" << endl;
    checkTransitivity(arr, n) ? cout << "Отношение ТРАНЗИТИВНО" << endl : cout << "Отношение НЕ ТРАНЗИТИВНО" << endl;

    return 0;
}