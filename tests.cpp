#include "set.cpp"

int main() {
    setlocale(LC_ALL, "Russian");

    int* massi1 = new int[10] {1, 2, 3, 4, 5, 6, 6, 6, 9, 10};
   // int* massi2 = new int[5] {1, 2, 3, 4, 5};
    Set<int>set1(massi1, 10);
    Set<int>set2(10);
    cout << "ints * " << set1 + set2 << endl;

    cout << (set1 == set1)<<endl;
    cout << (set1 == set2)<<endl;

    cout << set1[1] << endl;
    set1[1] = 100;
    cout << set1[1] << endl;

    float* massi3 = new float[5] {1.4, 2.3, 3.8, 3.7, 5.4};
    float* massi4 = new float[4] {1.8, 2.3, 3.6, 4.4};
    Set<float>set3(massi3, 5);
    Set<float>set4(massi4, 4);
    cout << "floats  " << set3 + set4 << endl;

    string* massi5 = new string[3]{ "sdfgh","dfg","ssdfghj" };
    string* massi6 = new string[6]{ "rty","ert","rtfgh","ertyu","sdfgh","dfghj" };
    Set<string>set5(massi5, 3);
    Set<string>set6(massi6, 6);
    cout << "strings " << set6 - set5 << endl;

    pair<int, double>* pair_mass1 = new pair<int, double>[3] { {1, 1.1}, { 2, 2.2 }, { 3, 3.3 }};
    Set<pair<int, double>> set_pair1(pair_mass1, 3);
    pair<int, double>* pair_mass2 = new pair<int, double>[2] { { 2, 6.2 }, { 6, 6.6 }};
    Set<pair<int, double>> set_pair2(pair_mass2, 2);
    cout << set_pair1 + set_pair2;
    
    //«јƒј„ј
    cout << endl << endl;
    cout << "«адача" << endl << endl;
    if (is_equal(set3, set4)) {
        cout << "1. Ёлементы одного массива встречаютс€ в другом" << endl;
    }
    else {
        cout << "1. Ёлементы одного массива не встречаютс€ в другом" << endl;
    }


    int* massi7 = new int[11] {5, 2, 1, 4, 3, 7, 6, 8, 9, 10,9};
    int* massi8 = new int[5] {1, 2, 3, 4, 5};
    Set<int>set7(massi7, 10);
    Set<int>set8(massi8, 5);
    if (is_equal(set8, set7)) {
        cout << "2. Ёлементы одного массива встречаютс€ в другом" << endl;
    }
    else {
        cout << "2. Ёлементы одного массива не встречаютс€ в другом" << endl;
    }

    return 0;
}
