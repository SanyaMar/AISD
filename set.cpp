#pragma once
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <limits>
#include <iostream>


template<typename T>
std::uniform_int_distribution<T> getDice(std::true_type)
{
    return std::uniform_int_distribution<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}


template<typename T>
std::uniform_real_distribution<T> getDice(std::false_type)
{
    return std::uniform_real_distribution<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}


template<typename T>
T random()
{
    std::random_device randomDevice;
    std::mt19937_64 generator(randomDevice());
    auto dice = getDice<T>(std::integral_constant<bool, std::numeric_limits<T>::is_integer>());
    return dice(generator);
}


using namespace std;

class SetPair {
private:
    int* _val1;
    double* _val2;
public:
    SetPair() :_val1(nullptr), _val2(nullptr) {};
    SetPair(int val1, double val2) : _val1(new int(val1)), _val2(new double(val2)) {};
    ~SetPair() {
        delete _val1;
        delete _val2;
    }
    SetPair(const SetPair& p) {
        _val1 = new int(*p._val1);
        _val2 = new double(*p._val2);
    }
    friend std::ostream& operator<<(std::ostream& out, const SetPair& s) {            //оператор вывода
        cout << *s._val1 << ", "<<*s._val2;
        cout << endl;
        return out;
    }
};


template<typename T>
class Set {
private:
    T* _elements;
    int _len;
public:
    Set() {                                                                   // конструктор по умолчанию
        _elements = nullptr;
        _len = 0;
    }


    Set(const T* values, int l) {                                             // конструктор со значениями
        _len = 0;
        _elements = new T[l];
        for (int i = 0; i < l; i++) {
            bool flag = true;
            for (int j = 0; j < _len; j++) {
                if (_elements[j] == values[i]) {
                    flag = false;
                }
            }
            if (flag == true) {
                _elements[_len] = values[i];
                _len++;
            }
        }
    }


    Set(int len) {                                                              // конструктор с рандомными значениями
        _len = 0;
        _elements = new T[len];
        for (int i = 0; i < len; i++) {
            T val;
            while (true) {
                int flag = true;
                val = random<T>();
                for (int j = 0; j < _len; j++) {
                    if (_elements[j] == val) {
                        flag = false;
                    }
                }
                if (flag == true) {
                    break;
                }
            }
            _elements[i] = val;
            _len++;
        }
    }


    T operator[](int index) const {                                               //оператор для получения числа по индексу
        if (index < 0 || index >= _len) {
            throw out_of_range("[T operator[]] Index is out of range.");
        }
        return *(_elements + index);
    }


    friend Set<T> operator+(const Set<T>& first, T other) {                        // добавление числа во множество +
        Set<T> sec = first;
        sec += other;
        return sec;
    }



    
    void operator +=(T other) {                                                    // добавление числа во множество +=
        for (int i = 0; i < _len; i++) {
            if (_elements[i] == other) {
                return;
            }
        }
        T* mas = new T[_len + 1];
        for (int i = 0; i < _len; i++) {
            mas[i] = _elements[i];
        }
        mas[_len] = other;
        delete[] _elements;
        _elements = mas;
        _len++;
    }


    friend Set<T> operator-(const Set<T>& first, T other) {                         // удаление числа из множества -
        Set<T> sec = first;
        sec -= other;
        return sec;
    }


    void operator-=( T other) {                                                     // удаление числа из множества -=
        for (int i = 0; i < _len; i++) {
            if (_elements[i] == other) {
                for (int j = i; j < _len - 1; j++) {
                     _elements[j] = _elements[j + 1];
                }
            _len--;
             break;
            }
        }
    }


    friend Set<T> operator*(const Set<T>& first, const Set<T>& other) {            // оператор пересечения множеств
        T* mas = new T[first._len + other._len];
        int index = 0;
        for (int i = 0; i < first._len; i++) {
            for (int j = 0; j < other._len; j++) {
                if (first[i] == other[j]) {
                    mas[index] = other[i];
                    index++;
                }
            }
        }
        return Set<T>(mas, index);
    }


    


     Set<T> operator-(const Set<T>& other) {            // оператор вычитания множеств
        int k=(_len - other._len);
        T* mas = new T[k];
        int index = 0;
        int n = abs(_len - other._len);
        for (int i = 0; i < _len; i++) {
            bool found = false;
            for (int j = 0; j < other._len; j++) {
                if (_elements[i] == other._elements[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                mas[index] = _elements[i];
                index++;
            }
        }
        return Set<T>(mas, index);
     }


    bool num_in_set(T val) {                                                        // проверка наличия числа в множестве
        for (int i = 0;i < _len;i++) {
            if (*_elements == val) {
                return true;
            }
            else
            {
                _elements++;
            }
        }
        return false;
    }



    friend std::ostream& operator<<(std::ostream& out, const Set<T>& s) {            //оператор вывода
        for (int i = 0; i < s._len; i++) {
            cout << s[i] << ", ";
        }
        cout << endl;
        return out;
    }


    friend bool checkArrays(const Set<T>& set1, const Set<T>& set2) {
        for (int i = 0; i < set1._len; i++) {
            if (!set2.num_in_set(set1[i])) {
                return false;
            }
        }
        return true;
    }
};






  
