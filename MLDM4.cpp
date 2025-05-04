#include <iostream>
#include <vector>
#include <locale>
#include <string>
#include <map>
using namespace std;

// ориентированный, парой элементов

int main() {
    setlocale(LC_ALL, "russian");
    int nV;
    cout << "ВВедите количество вершин: ";
    cin >> nV;
    vector<char>v(nV);
    cout << "Введите вершины: ";
    for (int i = 0; i < nV; ++i) {
        cin >> v[i];
    }

    int nE;
    cout << "Введите количество дуг: ";
    cin >> nE;

    map<string, int> arcs;
    cout << "Введите дуги и их вес в формате \"дуга вес\": ";
    for (int i = 0; i < nE; ++i) {
        string arc;
        cin >> arc;
        int weight;
        cin >> weight;
        arcs[arc] = weight;
    }

    for (auto i : arcs) {
        cout << i.first << " : " << i.second << endl;
    }

    // "a" : (weight, prev)
    map<char, pair<int, string>> paths;
    for (int i = 0; i < nV; ++i) {
        pair <int, string> wp;
        wp.first = -1;
        wp.second = '-';
        paths[v[i]] = wp;
    }

    for (auto i : paths) {
        cout << i.first << " : " << i.second.first << " " << i.second.second << endl;
    }

    char start;
    char finish;
    cout << "Введите начальную вершину: ";
    cin >> start;
    cout << "Введите конечную вершину: ";
    cin >> finish;
    
    paths[start].first = 0;
    
    vector<char> marked;
    marked.push_back(start);

    while (!marked.empty()) {
        for (auto i : arcs) {
            if (marked[0] == i.first[0]) {
                marked.push_back(i.first[1]);
                if ((paths[i.first[1]].first == -1) || ((i.second + paths[marked[0]].first) < paths[i.first[1]].first)) {
                    paths[i.first[1]].first = i.second + paths[marked[0]].first; //weight
                    paths[i.first[1]].second = marked[0]; // prev
                }
            }
        }
        marked.erase(marked.begin());
    }

    for (auto i : paths) {
        cout << i.first << " : " << i.second.first << " " << i.second.second << endl;
    }

    int weight = paths[finish].first;
    string path = " "; 
    path[0] = finish;
    while (paths[finish].second != "-") {
        path = paths[finish].second + path;
        finish = paths[finish].second[0];
    }

    cout << endl;
    cout << path << " : " << weight;
    return 0;
}
