#include <iostream>
#include <set>
#include <algorithm>

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
        auto it = elements.begin();
        std::advance(it, index);
        return *it;
    }

    Set operator+(const Set& other) const {
        Set result = *this;
        result.elements.insert(other.elements.begin(), other.elements.end());
        return result;
    }

    Set operator-(const Set& other) const {
        Set result = *this;
        for (const auto& element : other.elements) {
            result.elements.erase(element);
        }
        return result;
    }

    Set operator+(const T& value) const {
        Set result = *this;
        result.elements.insert(value);
        return result;
    }

    Set operator-(const T& value) const {
        Set result = *this;
        result.elements.erase(value);
        return result;
    }

    bool contains(const T& value) const {
        return elements.find(value) != elements.end();
    }

    friend std::ostream& operator<<(std::ostream& os, const Set& set) {
        for (const auto& element : set.elements) {
            os << element << " ";
        }
        return os;
    }
};

int main() {
    Set<int> intSet = { 1, 2, 3, 4, 5 };
    std::cout << "intSet: " << intSet << std::endl;

    Set<float> floatSet = { 1.1f, 2.2f, 3.3f };
    std::cout << "floatSet: " << floatSet << std::endl;

    Set<std::string> stringSet = { "Hello", "World" };
    std::cout << "stringSet: " << stringSet << std::endl;

    Set<std::pair<int, double>> pairSet = { {1, 1.1}, {2, 2.2} };
    std::cout << "pairSet: " << pairSet << std::endl;

   
    return 0;
}