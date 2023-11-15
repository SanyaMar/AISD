#pragma once
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <limits>
#include <iostream>
#include <utility>
#define eps 0.01


using namespace std;
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p)
{
    os << "[" << p.first << ", " << p.second << "]";
    return os;
}
 
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
    Set(Set<T>& other) {                                                       //конструктор копирования
        Set<T> a;
        for (int i = 0;i < other._len;i++) {
            a += other[i];
        }
        swap(a);
    }

    void swap(Set& other) {
        std::swap(_elements, other._elements);
        std::swap(_len, other._len);
    }

    int get_len() {
        return _len;
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
                bool flag = true;
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


    T& operator[](int index) const {                                               //оператор для получения числа по индексу
        if (index < 0 || index >= _len) {
            throw std::out_of_range("Set::operator[], index is out of range");
        }
        return _elements[index];
    }


    friend Set<T> operator+(const Set<T>& first, T other) {                        // добавление числа во множество +
        Set<T> sec = first;
        sec += other;
        return sec;
    }



    
    void operator +=(T other) {                                                    // добавление числа во множество +=
        if (!num_in_set(other)) {
            T* mas = new T[_len + 1];
            for (int i = 0; i < _len; i++) {
                mas[i] = _elements[i];
            }
            mas[_len] = other;
            delete[] _elements;
            _elements = mas;
            _len++;
        }
    }


    friend Set<T> operator-( Set<T>& first, T other) {                         // удаление числа из множества -
        Set<T> sec = first;
        sec -= other;
        return sec;
    }


  
    void operator -=(T other) {                                                    //  удаление числа из множества -=
        if (num_in_set(other)) {
            T* mas = new T[_len - 1];
            int j = 0;
            for (int i = 0; i < _len; i++) {
                if (_elements[i] != other) {
                    mas[j] = _elements[i];
                    j++;
                }
            }
            delete[] _elements;
            _elements = mas;
            _len--;
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


    friend Set<T> operator+(Set<T>& first, Set<T>& other) {           // оператор сложения множеств
        Set<T>new_set(first);
        for (int i = 0;i < other._len; i++) {
            new_set += other[i];
        }
        return new_set;
    }




     friend Set<T> operator-(Set<T>& first, Set<T>& other) {            // оператор вычитания множеств
         Set<T> new_set(first);
         for (int i = 0; i < other._len; i++) {
             new_set -= other[i];
         }
         return new_set;
    
     }


    bool num_in_set(T val) {                                                        // проверка наличия числа в множестве
        T* temp = _elements;
        for (int i = 0;i < _len;i++) {
            if (*temp == val) {
                return true;
            }
            else
            {
                temp++;
            }
        }
        return false;
    }



    friend std::ostream& operator<<(std::ostream& out, const Set<T>& s) {            //оператор вывода
        for (int i = 0; i < s._len; i++) {
            out << s[i] << "  ";
        }
        out << endl;
        return out;
    }

    bool operator==(const Set<T>& s) {
        
        if (_len != s._len) return false;
        for (int i = 0; i < _len; i++)
        {
            if (abs(_elements[i] - s[i])>=eps) return false;
        }
        return true;
    }

    
};
template<typename T>
bool is_equal(Set<T>& first, Set<T>& other) {                                     //возвращает true если каждый элемент в first встречается в other
    if ((first+ other).get_len() == other.get_len()) {
        return true;
    }
    return false;
}





  
