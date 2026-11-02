#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int s(int x) {
    if (x == 1 || x == 0) {
        return 0;
    }
    int sum = 1;
    for (int i = 2; i*i <= x; i++) {
        if (x % i  == 0) {
            sum += i;
            if ( i != x/i) {
                sum += x/i;
            }
        }
    }
    return sum;
}


int main() {
    cout << "Оберіть задачу (a-d)" << endl;;
    char choice;
    cin >> choice;
    switch (choice) {
        case 'a': {
            cout << "Введіть перший елемент" << endl;
            int firstElement;
            cin >> firstElement;
            int n, x = firstElement, y, z, i = 0;
            cout << "Введіть номер елементу" << endl;
            cin >> n;
            while (true){
                if (i == n) {
                    cout << "a_n = " << x;
                    return 0;
                }
                y = s(x);
                if (s(y) == 1) {
                    z = 5*y + 1;
                }else {
                    z = y;
                }
                x = z;
                i++;
            }
        }
        case 'b': {
            cout << "Введіть перший елемент" << endl;
            int firstElement;
            cin >> firstElement;
            int aMax = firstElement, aMin = firstElement, aMaxTask;
            cout << "Введіть максимальне значення" << endl;
            cin >> aMaxTask;
            int x = firstElement, i = 0, y, z;
            vector<int> elements;
            while (true) {
                if (x > aMaxTask) {
                    cout << "Кількість кроків = " << i << endl;
                    cout << "Максимальний елемент = " <<  aMax << endl;
                    cout << "Мінімальний елемент = " << aMin << endl;
                    return 0;
                }
                for (int j = 0; j < elements.size(); ++j) {
                    if (x == elements[j]) {
                        cout << "Кількість кроків = " << i << endl;
                        cout << "Максимальний елемент = " <<  aMax << endl;
                        cout << "Мінімальний елемент = " << aMin << endl;
                        return 0;
                    }
                }
                y = s(x);
                if (s(y) == 1) {
                    z = 5*y + 1;
                }else {
                    z = y;
                }
                if (z > aMax) {aMax = z;}
                if (z < aMin) {aMin = z;}
                elements.push_back(x);
                x = z;
                i++;
            }
        }
        case 'c': {
            cout << "Введіть a - початок послідовності та b - кінець послідовності" << endl;
            int a ,b, aMaxTask;
            cin >> a;
            cin >> b;
            cout << "Введіть максимальне значення" << endl;
            cin >> aMaxTask;
            for (int t = a; t <= b; ++t) {
                int aMax = t, aMin = t;
                int x = t, i = 0, y, z;
                vector<int> elements;
                while (true) {
                    if (x > aMaxTask) {
                        cout << "Кількість кроків = " << i << endl;
                        cout << "Максимальний елемент = " <<  aMax << endl;
                        cout << "Мінімальний елемент = " << aMin << endl;
                        break;
                    }
                    bool cycle = false;
                    for (int j = 0; j < elements.size(); ++j) {
                        if (x == elements[j]) {
                            cout << "Кількість кроків = " << i << endl;
                            cout << "Максимальний елемент = " <<  aMax << endl;
                            cout << "Мінімальний елемент = " << aMin << endl;
                            cycle = true;
                            break;
                        }
                    }
                    if (cycle) {
                        break;
                    }
                    y = s(x);
                    if (s(y) == 1) {
                        z = 5*y + 1;
                    }else {
                        z = y;
                    }
                    if (z > aMax) {aMax = z;}
                    if (z < aMin) {aMin = z;}
                    elements.push_back(x);
                    x = z;
                    i++;
                }
            }
        }
        case 'd': {
            cout << "Введіть a - початок послідовності та b - кінець послідовності" << endl;
            int a ,b, aMaxTask;
            cin >> a;
            cin >> b;
            cout << "Введіть максимальне значення" << endl;
            cin >> aMaxTask;
            set<std::vector<int>> uniqueCycles;
            vector<int> allMaxValues;
            vector<int> allSteps;
            int over = 0;
            for (int t = a; t <= b; ++t) {
                int aMax = t, aMin = t;
                int x = t, i = 0, y, z;
                vector<int> elements;

                while (true) {
                    if (x > aMaxTask) {
                        cout << "Кількість кроків = " << i << endl;
                        cout << "Максимальний елемент = " <<  aMax << endl;
                        cout << "Мінімальний елемент = " << aMin << endl;
                        over++;
                        allMaxValues.push_back(aMax);
                        allSteps.push_back(i);
                        break;
                    }
                    bool foundCycle = false;
                    for (int j = 0; j < elements.size(); ++j) {
                        if (x == elements[j]) {
                            cout << "Кількість кроків = " << i << endl;
                            cout << "Максимальний елемент = " <<  aMax << endl;
                            cout << "Мінімальний елемент = " << aMin << endl;
                            vector<int> cycle(elements.begin() + j, elements.end());
                            auto minIt = min_element(cycle.begin(), cycle.end());
                            rotate(cycle.begin(), minIt, cycle.end());
                            uniqueCycles.insert(cycle);
                            allMaxValues.push_back(aMax);
                            allSteps.push_back(i);
                            foundCycle = true;
                            break;
                        }
                    }
                    if (foundCycle) {
                        break;
                    }
                    y = s(x);
                    if (s(y) == 1) {
                        z = 5*y + 1;
                    }else {
                        z = y;
                    }
                    if (z > aMax) {aMax = z;}
                    if (z < aMin) {aMin = z;}
                    elements.push_back(x);
                    x = z;
                    i++;
                }
            }
            cout << "\nКількість елементів, що призвели до переповнення: " << over<< endl;
            cout << "Знайдені унікальні цикли (" << uniqueCycles.size() << "):" << endl;
            for (const auto& cycle : uniqueCycles) {
                cout << "[ ";
                for (int num : cycle) {
                    cout << num << " ";
                }
                cout << "]" << endl;
            }
            sort(allMaxValues.rbegin(), allMaxValues.rend());
            cout << "\nТоп найбільших значень елементів (до 26):" << endl;
            int limit26 = min(26, (int)allMaxValues.size());
            for (int k = 0; k < limit26; ++k) {
                cout << allMaxValues[k] << " ";
            }
            cout << endl;
            sort(allSteps.rbegin(), allSteps.rend());
            cout << "\nТоп найбільших кількостей кроків (до 42):" << endl;
            int limit42 = min(42, (int)allSteps.size());
            for (int k = 0; k < limit42; ++k) {
                cout << allSteps[k] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}