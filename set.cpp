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
template<typename T, typename R>
class SetPair {
private:
    T* _val1;
    R* _val2;
public:
    SetPair() :_val1(nullptr), _val2(nullptr) {};
    SetPair(T* val1, R* val2) : _val1(val1), _val2(val2) {};
    ~SetPair() {
        delete _val1;
        delete _val2;
    }
    SetPair(const SetPair& p) {
        _val1 = new T(*p._val1);
        _val2 = new R(*p._val2);
    }
};


template<typename T>
class Set {
private:
    T* _elements;
    int _len;
public:
    Set() {                  // конструктор по умолчанию
        _elements = nullptr;
        _len = 0;
    }


    Set(const T* values, int l) {             // конструктор со значениями
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

    Set(int len) {                                         // конструктор с рандомными значениями
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

    T operator[](int index) const {                          //оператор для получения числа по индексу
        return *(_elements + index);
    }

   

    friend Set<T> operator+(const Set<T>& first, const Set<T>& other) {           // оператор сложения множеств
        T* mas = new T[first._len + other._len];
        int index = 0;
        for (int i = 0; i < first._len; i++) {
            mas[index] = first[i];
            index++;
        }
        for (int i = 0; i < other._len; i++) {
            mas[index] = other[i];
            index++;
        }
        return Set<T>(mas, index);
    }


    friend Set<T> operator*(const Set<T>& first, const Set<T>& other) {         // оператор пересечения множеств
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
    /*friend Set<T> operator-(const Set<T>& first, const Set<T>& other) {             // оператор вычитания множеств
        int k=(first._len - other._len);
        T* mas = new T[k];
        int index = 0;
        int n = abs(first._len - other._len);
        for (int i = 0; i < first._len; i++) {
            if(
            mas[index] = first[i];
            index++;
        }
        for (int i = 0; i < other._len; i++) {
            mas[index] = other[i];
            index++;
        }
        return Set<T>(mas, index);
    }*/
    bool num_in_set(T val) {                                            // проверка наличия числа в множестве
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



    friend std::ostream& operator<<(std::ostream& out, const Set<T>& s) {             //
        for (int i = 0; i < s._len; i++) {
            cout << s[i] << ", ";
        }
        cout << endl;
        return out;
    }

};




   

    //Set operator-(const Set& other) const {     //разность множеств
    //    Set result = *this;
    //    for (const auto& element : other.elements) {
    //        result.elements.erase(element);
    //    }
    //    return result;
    //}

    //Set operator+(const T& value) const {      //сложения множества с числом
    //    Set result = *this;
    //    result.elements.insert(value);
    //    return result;
    //}

    //Set operator-(const T& value) const {          //вычитание из множества числа
    //    Set result = *this;
    //    result.elements.erase(value);
    //    return result;
    //}

    //string contains(const T& value) const {             // проверка наличия числа во множестве
    //    if (elements.find(value) != elements.end())
    //        return "True";
    //    else                              
    //        return"False";
    //}
   

