#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
//template<typename T,typename R>
//class SetPair {
//private:
//    std::set<T, R> elements;
//
//};



template<typename T>
class Set {
private:
    std::set<T> elements;
public:
    Set() {}

    Set(const std::initializer_list<T>& values) {
        for (const auto& value : values) {
            elements.insert(value);
        }
    }

    T operator[](int index) const {
        // return elements[index];

        auto it = elements.begin();
        std::advance(it, index);
        return *it;
    }

    Set operator+(const Set& other) const {     //объединение множеств
        Set result = *this;
        result.elements.insert(other.elements.begin(), other.elements.end());
        return result;
    }

    Set operator-(const Set& other) const {     //разность множеств
        Set result = *this;
        for (const auto& element : other.elements) {
            result.elements.erase(element);
        }
        return result;
    }

    Set operator+(const T& value) const {      //сложения множества с числом
        Set result = *this;
        result.elements.insert(value);
        return result;
    }

    Set operator-(const T& value) const {          //вычитание из множества числа
        Set result = *this;
        result.elements.erase(value);
        return result;
    }

    string contains(const T& value) const {             // проверка наличия числа во множестве
        if (elements.find(value) != elements.end())
            return "True";
        else                              
            return"False";
    }
    friend ostream& operator<< (ostream& os, const Set<T>& set) {
        for (const auto& element : set.elements) {
            cout << element << " ";
        }
        cout << endl;
        return os;
    }
};

int main() {
    Set<int> intSetf = { 1, 2, 3, 4, 5 };
    cout << "intSet: " << intSetf;

    Set<int> intSets = { 5, 8, 7, 6, 9 };
    cout << "intSet: " << intSets;

    Set<int> intSett = { 6,7,8};
    cout << "intSet: " << intSett;

    Set<float> floatSet = { 1.1f, 2.2f, 3.3f };
    cout << "floatSet: " << floatSet;

    Set<std::string> stringSet = { "Hello ", "World" };
    cout << "stringSet: " << stringSet;
    Set<int> unSet = (intSetf - 2);
    cout << "unSet: " << unSet;

    cout << intSetf[2];
    

   /* Set<std::pair<int, double>> pairSet = { {1, 1.1}, {2, 2.2} };
    std::cout << "pairSet: " << pairSet << std::endl;*/

   
    return 0;
}