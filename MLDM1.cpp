#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

// Определение структуры для хранения элемента массива
struct Element {
    char letter;     // Первый - символ (b) (elem[1] >= 'a' && elem[1] <= 'z')
    char notEvenNumber;    // Второй - нечетное число (j) (elem[2] >= '0' && elem[2] <= '9') && (elem[2] - '0') % 2 == 1
    char number; // Третий - число (c) (elem[0] >= '0' && elem[0] <= '9')
    char evenNumber;    // Четвертый - чётное число (i) (elem[2] >= '0' && elem[2] <= '9') && (elem[2] - '0') % 2 == 0
};


bool validation(string elem) {
    if (elem.length() == 4 &&
        (elem[0] >= 'a' && elem[0] <= 'z') &&
        (elem[1] >= '0' && elem[1] <= '9') && (elem[1] - '0') % 2 == 1 &&
        (elem[2] >= '0' && elem[2] <= '9') &&
        (elem[3] >= '0' && elem[3] <= '9') && (elem[3] - '0') % 2 == 0) {
        return true;
    }
    else {
        return false;
    }
}

void printArray(const vector<Element>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        cout << "Элемент " << i + 1 << ": " << arr[i].letter << arr[i].notEvenNumber << arr[i].number << arr[i].evenNumber << endl;
    }
    cout << endl;
}

void inputArray(vector<Element>& arr, int size) {
    Element elem;

    cout << "Введите элементы множества (bjci): " << endl;
    // Ввод элемента
    for (int i = 0; i < size; ++i) {
        cout << i + 1 << ": ";
        string input;
        cin >> input;

        // Проверка корректности ввода
        if (validation(input)) {
            elem.letter = input[0];
            elem.notEvenNumber = input[1];
            elem.number = input[2];
            elem.evenNumber = input[3];
            arr.push_back(elem);
        }
        else {
            cout << "Ошибка ввода, перезапустите программу" << endl;
            // i--;
            break;
        }
    }
}

// Удаление дублирующих элементов
void removeNonUnique(vector<Element>& arr) {
    vector<Element> uniqueElements;

    // Проходим по каждому элементу в векторе
    for (int i = 0; i < arr.size(); ++i) {
        bool isUnique = true;

        // Проверяем, встречается ли элемент в uniqueElements
        for (int j = 0; j < uniqueElements.size(); ++j) {
            if (arr[i].number == uniqueElements[j].number &&
                arr[i].notEvenNumber == uniqueElements[j].notEvenNumber &&
                arr[i].evenNumber == uniqueElements[j].evenNumber &&
                arr[i].letter == uniqueElements[j].letter) {
                isUnique = false;
                break;
            }
        }

        // Если элемент уникален, добавляем его в uniqueElements
        if (isUnique) {
            uniqueElements.push_back(arr[i]);
        }
    }

    // Очищаем оригинальный вектор и заполняем его уникальными элементами
    arr.clear();
    for (size_t i = 0; i < uniqueElements.size(); ++i) {
        arr.push_back(uniqueElements[i]);
    }
}

// Объединение двух массивов
void unionArrays(vector<Element>& result, vector<Element>& arr1, vector<Element>& arr2) {
    for (int i = 0; i < arr1.size(); ++i)
        result.push_back(arr1[i]);

    for (int i = 0; i < arr2.size(); ++i)
        result.push_back(arr2[i]);

    removeNonUnique(result);
}

// Пересечение массивов
void crossingArrays(vector<Element>& result, vector<Element>& arr1, vector<Element>& arr2) {
    // Проходим по каждому элементу в первом массиве
    for (int i = 0; i < arr1.size(); ++i) {
        // Проверяем, встречается ли элемент из первого массива во втором
        for (int j = 0; j < arr2.size(); ++j) {
            if (arr1[i].number == arr2[j].number &&
                arr1[i].notEvenNumber == arr2[j].notEvenNumber &&
                arr1[i].evenNumber == arr2[j].evenNumber &&
                arr1[i].letter == arr2[j].letter) {
                result.push_back(arr1[i]);
            }
        }

    }
}

// Дополнение второго массива до первого
void additionSecondArrayToFirst(vector<Element>& result, vector<Element>& arr1, vector<Element>& arr2) {
    // Проходим по каждому элементу в первом массиве
    for (int i = 0; i < arr1.size(); ++i) {
        bool isLocatedIn2 = false;
        // Проверяем, встречается ли элемент из первого массива во втором
        for (int j = 0; j < arr2.size(); ++j) {
            if (arr1[i].number == arr2[j].number &&
                arr1[i].notEvenNumber == arr2[j].notEvenNumber &&
                arr1[i].evenNumber == arr2[j].evenNumber &&
                arr1[i].letter == arr2[j].letter) {
                isLocatedIn2 = true;
                break;
            }
        }

        // Если элемент первого массива не находится во втором, то добавляем в результирующий массив
        if (!isLocatedIn2) {
            result.push_back(arr1[i]);
        }

    }
}

// Симметрическая разность массивов
void symmetricalDifference(vector<Element>& result, vector<Element>& arr1, vector<Element>& arr2) {
    // Создаем массив общих элементов
    vector<Element> unionArr;
    unionArrays(unionArr, arr1, arr2);

    // Создаем массив объединенных элементов
    vector<Element> crossingArr;
    crossingArrays(crossingArr, arr1, arr2);

    // Массив разности объединенных элементов и общих элементов, т. е. симметрическая разность
    additionSecondArrayToFirst(result, unionArr, crossingArr);
}

int main() {
    setlocale(LC_ALL, "russian");
    int size1, size2;
    vector<Element> arr1;
    vector<Element> arr2;

    // Ввод элементов 1 массива
    cout << "Введите размер первого множества: ";
    cin >> size1;
    inputArray(arr1, size1);
    cout << "\n";

    // Ввод элементов 2 массива
    cout << "Введите размер второго множества: ";
    cin >> size2;
    inputArray(arr2, size2);
    cout << "\n";

    // Удаление неуникальных элементов массивов
    removeNonUnique(arr1);
    removeNonUnique(arr2);
    cout << "ВЖВЖВЖ удаление неуникальных элементов из множеств ВЖВЖВЖ " << endl;


    cout << "Элементы первого множества: " << endl;
    printArray(arr1);
    cout << "\n";

    cout << "Элементы второго множества: " << endl;
    printArray(arr2);
    cout << "\n";

    // Объединение двух массивов
    vector<Element> arrUnion;
    unionArrays(arrUnion, arr1, arr2);
    cout << "1. Элементы операции объединения множеств: " << endl;
    printArray(arrUnion);

    vector<Element> arrCrossing;
    crossingArrays(arrCrossing, arr1, arr2);
    cout << "2. Элементы операции пересечения множеств: " << endl;
    printArray(arrCrossing);

    vector<Element> arrAdditionSecondArrayToFirst;
    additionSecondArrayToFirst(arrAdditionSecondArrayToFirst, arr1, arr2);
    cout << "3. Элементы операции дополнения второго множества до первого: " << endl;
    printArray(arrAdditionSecondArrayToFirst);

    vector<Element> arrSymmetricalDifference;
    symmetricalDifference(arrSymmetricalDifference, arr1, arr2);
    cout << "4. Элементы операции симметрической разности множеств: " << endl;
    printArray(arrSymmetricalDifference);

    return 0;
}