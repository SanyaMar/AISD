#include "set.cpp"

int main() {
    int* m = new int[8] {2, 2, 3, 4, 5, 1, 3, 3};
    Set<int> a(m, 6);
    cout << a;

    int* m1 = new int[3] {1, 2, 3};
    Set<int>b(m1, 3);

    int* m2 = new int[4] {4, 3, 6, 1};
    Set<int> c(m2, 4);

    cout << b + c;

    cout << Set<int>(5);

    int* m4 = new int[3] {1, 2, 3};
    Set<int>e(m4, 3);

    int* m5 = new int[4] {4, 3, 6, 1};
    Set<int> f(m5, 4);
    cout << e * f;
    cout << e.num_in_set(3);
    return 0;
}
