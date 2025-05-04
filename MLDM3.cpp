#include <iostream>
#include <locale>
#include <vector>

using namespace std;

struct Pair {
    char x;
    char y;
};

void inputArr(vector<char>& arr, int size) {
    cout << "Введите элементы: ";
    for (int i = 0; i < size; ++i) {
        char elem;
        cin >> elem;
        arr.push_back(elem);
    }
}

void printArr(vector<char>& arr) {
    // cout << "Вывод массива: " << endl;
    for (int i = 0; i < arr.size(); ++i) {
        cout << i + 1 << " элемент: " << arr[i] << endl;
    }
}

bool hasElem(char elem, vector<char>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == elem) {
            return true;
        }
    }
    return false;
}

void makeUnique(vector<char>& arr) {
    vector<char> cache;
    for (int i = 0; i < arr.size(); ++i) {
        if (!hasElem(arr[i], cache)) {
            cache.push_back(arr[i]);
        }
    }
    arr.clear();
    for (int i = 0; i < cache.size(); ++i) {
        arr.push_back(cache[i]);
    }
}

void inputRS(vector<Pair>& arr, int size) {
    cout << "Ввод пар отношения: " << endl;
    for (int i = 0; i < size; ++i) {
        Pair elem;
        cout << "Введите " << i + 1 << " пару(x, y): ";
        cin >> elem.x;
        cin >> elem.y;
        arr.push_back(elem);
    }
}

void printRS(vector<Pair>& arr) {
    cout << "Отношение: " << endl;
    for (int i = 0; i < arr.size(); ++i) {
        cout << i + 1 << " пара: (" << arr[i].x << ", " << arr[i].y << ")" << endl;
    }
}

bool isFunc(vector<Pair>& arrRS, vector<char>& arr1, vector<char>& arr2) {
    if (arrRS.size() != arr1.size()) {
        return false;
    }
    for (int i = 0; i < arrRS.size(); ++i) {
        if (!hasElem(arrRS[i].x, arr1) || !hasElem(arrRS[i].y, arr2)) {
            return false;
        }
    }
    for (int i = 0; i < arrRS.size() - 1; ++i) {
        for (int j = i + 1; j < arrRS.size(); ++j) {
            if (arrRS[i].x == arrRS[j].x && arrRS[i].y != arrRS[j].y) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "russian");
    
    vector<char> arr1;
    int size1;
    cout << "Введите количество элементов 1 множества: ";
    cin >> size1;
    inputArr(arr1, size1);

    vector<char> arr2;
    int size2;
    cout << "Введите количество элементов 2 множества: ";
    cin >> size2;
    inputArr(arr2, size2);

    makeUnique(arr1);
    makeUnique(arr2);
    
    cout << "Элементы 1 множества: " << endl;
    printArr(arr1);
    cout << "Элементы 2 множества: " << endl;
    printArr(arr2);

    vector<Pair> arrRS;
    int sizeRS;
    cout << "Введите количество пар отношения: ";
    cin >> sizeRS;
    inputRS(arrRS, sizeRS);
    printRS(arrRS);
    isFunc(arrRS, arr1, arr2) ? cout << "Отношение ЯВЛЯЕТСЯ функцией" : cout << "Отношение НЕ ЯВЛЯЕТСЯ функцией";



    return 0;
}

