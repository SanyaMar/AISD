#include "set.cpp"

int main() {
    setlocale(LC_ALL, "Russian");
    string* m = new string[3] {"asd","fghj","kl"};
    Set<string> a(m, 3);
    cout << a;

    string* m1 = new string[5] {"xc","zvb","asg","dfg","xcv"};
    Set<string>b(m1, 5);
    cout << a+b;

    SetPair ar(2,3.3);
    cout << ar;
   // Set<SetPair> arsen(ar);
   // cout <<"Я тут" << arsen;
    cout << Set<int>(5);

    int* m4 = new int[6] {1, 2, 3, 4, 5, 6};
    Set<int>e(m4, 6);
    cout << e + 10;
    int* m5 = new int[4] {4, 7, 6, 8};
    Set<int> f(m5, 4);

    //задача
    int* massi1 = new int[4] {9, 2, 6, 4};
    int* massi2 = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Set<int>set1(massi1, 4);
    Set<int>set2(massi2, 10);
    f= checkArrays(set1, set2);
    cout << f;
    return 0;
}
