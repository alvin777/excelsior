#include <iostream>
#include <string>
#define PR(a...)    std::cout << #a << ": "; pr,a; std::cout << '\n';

struct print {
    template <typename T>  
    print& operator,(const T& v) {
        std::cout << v << ", ";
        return *this;
    }
} pr;

int main()
{
    int a = 3;
    float b = 5.1;
    std::string s = "asd";

    PR(a, b, s);
}