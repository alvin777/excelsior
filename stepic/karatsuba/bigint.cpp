#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <list>
#include <sstream>

#include <assert.h>
#include <math.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi; 

#define REP(k,a) for(int k=0; k < (a); ++k)
#define FOR(i,a,b) for(int i=a; i < (b); ++i)
#define ALL(a) begin(a), end(a)
#define RALL(a) a.rbegin(), a.rend()
#define D(a) cout << #a ": " << a << " ";
#define DE(a) cout << #a ": " << a << endl;
#define COUNT(a) (sizeof(a)/sizeof(a[0]))

const int INF = 1e9;
const int MAX_COUNT = (2<<28)/32;


template<typename T> 
void print_array(T first, T last, const string& label = "") {
    if (label.size()) {
        cout << label << ": ";
    }

    while (first != last) {
        cout << +*first++ << " ";
    }

    cout << endl;
}

class Indent
{
public:
    friend ostream& operator<< (ostream& o, const Indent& indent);

    Indent()  { ++level; }
    ~Indent() { --level; }

private:
    static int level;
};

int Indent::level = -1;

ostream& operator<< (ostream& o, const Indent& indent) {
    return o << string(indent.level*4, ' ');
}


class BigUInt {
public:
    typedef unsigned char size_type;
    // typedef unsigned int size_type;
    // typedef unsigned long long size_type;

    typedef vector<size_type> container_type;
    // typedef list<size_type> container_type;

    BigUInt() : data(1) {
    }

    BigUInt(const BigUInt& other) : data(other.data) {
    }

    BigUInt(const BigUInt&& other) : data(std::move(other.data)) {
    }

    template<typename T>
    explicit BigUInt(T number) {
        initFromNumber(number);
    }

    BigUInt(const string& str) {
        for (auto it = str.crbegin(); it != str.crend(); ++it) {
            size_type digit = *it - '0';
            data.push_back(digit);
        }
    }

    BigUInt(const char* str) : BigUInt(string(str)){
    }

    BigUInt(const container_type& array) : 
        data(array.begin(), array.end()) 
    {
    }

    string toString() {
        string s;
        for (auto it = data.crbegin(); it != data.crend(); ++it) {
            s += (*it + '0');
        }
        return s;
    }

    template<typename T> 
    T toNumber() {
        T number = 0;

        for (auto it = data.crbegin(); it != data.crend(); ++it) {
            number *= 10;
            number += *it;
        }
        return number;
    }

    size_type getLastWord() {
        return data.size() > 0 ? data.front() : 0;
    }

    BigUInt& operator= (const BigUInt& other) {
        data = other.data;
        return *this;
    }

    BigUInt& operator= (const BigUInt&& other) {
        data = std::move(other.data);
        return *this;
    }

    BigUInt operator+ (const BigUInt& other) {
        BigUInt res(*this);
        res += (other);
        return res;
    }

    BigUInt& operator+= (const BigUInt& other) {
        return add(other);
    }

    BigUInt operator- (const BigUInt& other) {
        BigUInt res(*this);
        res -= (other);
        return res;
    }

    BigUInt& operator-= (const BigUInt& other) {
        throw exception();
        return *this;
    }

    BigUInt operator* (const BigUInt& other) {
        BigUInt res(*this);
        res *= (other);
        return res;
    }

    BigUInt& operator*= (const BigUInt& other) {
        // return karatsuba(other);
        multiply(other);
        return *this;
    }

    BigUInt operator<< (uint count) {
        BigUInt res(*this);
        res <<= count;
        return res;
    }

    BigUInt& operator<<= (uint count) {
        return left_shift(count);
    }

    BigUInt operator/ (uint divisor) {
        BigUInt temp(*this);
        temp /= divisor;
        return temp;
    }

    BigUInt& operator/= (uint divisor) {
        return divide(divisor);
    }

    BigUInt operator% (uint divisor) {
        BigUInt temp(*this);
        temp %= divisor;
        return temp;
    }

    BigUInt& operator%= (uint divisor) {
        uint rem = 0;
        divide(divisor, &rem);

        *this = BigUInt(rem);

        return *this;
    }

    BigUInt rightHalf(uint totalSize) const {
        if (totalSize < data.size()) throw exception();

        if (totalSize == data.size()) {
            auto middle = data.begin();
            advance(middle, data.size()/2);
            return BigUInt(container_type(data.begin(), middle));
        }

        auto last = data.begin();
        advance(last, min<uint>(totalSize/2, data.size()));
        container_type newData(data.begin(), last);
        // print_array(newData.rbegin(), newData.rend(), "newData");
        newData.resize(totalSize/2);
        // print_array(newData.rbegin(), newData.rend(), "newData");
        return BigUInt(newData);
    }

    BigUInt leftHalf(uint totalSize) const {
        if (totalSize < data.size()) throw exception();

        if (totalSize == data.size()) {
            auto middle = data.begin();
            advance(middle, data.size()/2);
            return BigUInt(container_type(middle, data.end()));
        } 

        if (totalSize >= 2*data.size()) {
            return BigUInt(container_type((totalSize + 1)/2));
        }

        auto last = data.begin();
        advance(last, totalSize/2);
        container_type newData(last, data.end());
        newData.resize((totalSize + 1)/2);
        return BigUInt(newData);
    }

    // in words
    int size() const {
        return data.size();
    }

private:
    template<typename T>
    void initFromNumber(T number) {
        if (number == 0) {
            data.push_back(0);
            return;
        }

        while (number) {
            data.push_back(number % 10);
            number /= 10;
        }
        // print_array(RALL(data), "data");
    }

    BigUInt& add(const BigUInt& other) {
        if (other.size() > size()) {
            data.resize(other.size());
        }

        char carry = 0;
        int i = 0;
        auto it = data.begin();
        auto otherIt = other.data.begin();

        while (carry || i < other.size()) { // while carry flag is on or other has any data
            if (i == data.size()) {
                data.push_back(0);
                it = prev(data.end());
            }

            // DE((uint)*it);
            // DE((uint)*otherIt);
            // DE((uint)carry);

            if (carry) {
                *it += carry;
                *it %= 10;
                carry = *it < carry ? 1 : 0;
            }

            if (i < other.size()) {
                *it += *otherIt;
                *it %= 10;
                carry = *it < *otherIt ? 1 : carry;
            }

            // DE((uint)*it);
            // DE((uint)carry);

            ++i;
            ++it;
            ++otherIt;
        }

        // print_array(RALL(data), "data");

        assert(isValid());

        return *this;
    }

    BigUInt& multiply(const BigUInt& other) {
        // Indent ind;

        // cout << ind << "multiply" << endl;
        // cout << ind; print_array(data.rbegin(), data.rend(), "data");
        // cout << ind; print_array(other.data.rbegin(), other.data.rend(), "other.data");

        if (isZero() || other.isZero()) {
            data.clear();
            data.push_back(0);
            return *this;
        }

        size_t maxSize = max(size(), other.size());
        uint halfMaxSize = maxSize >> 1;

        // cout << ind; DE(maxSize); 

        if (maxSize == 1) {
            multiplyWord(other);
            // cout << ind; print_array(ALL(data), "result");
            return *this;
        }

        BigUInt thisLeftHalf   = leftHalf(maxSize);
        BigUInt thisRightHalf  = rightHalf(maxSize);
        BigUInt otherLeftHalf  = other.leftHalf(maxSize);
        BigUInt otherRightHalf = other.rightHalf(maxSize);


        BigUInt xl_yl = thisLeftHalf;  xl_yl.multiply(otherLeftHalf);
        BigUInt xl_yr = thisLeftHalf;  xl_yr.multiply(otherRightHalf);
        BigUInt xr_yl = thisRightHalf; xr_yl.multiply(otherLeftHalf);
        BigUInt xr_yr = thisRightHalf; xr_yr.multiply(otherRightHalf);

        // cout << ind; DE(maxSize); 
        // cout << ind; print_array(data.rbegin(), data.rend(), "data");
        // cout << ind; print_array(thisLeftHalf.data.rbegin(),   thisLeftHalf.data.rend(),  "leftHalf");
        // cout << ind; print_array(thisRightHalf.data.rbegin(),  thisRightHalf.data.rend(), "rightHalf");

        // cout << ind; print_array(other.data.rbegin(), other.data.rend(), "other.data");
        // cout << ind; print_array(otherLeftHalf.data.rbegin(),  otherLeftHalf.data.rend(),  "other.leftHalf");
        // cout << ind; print_array(otherRightHalf.data.rbegin(), otherRightHalf.data.rend(), "other.rightHalf");

        // cout << ind; print_array(xl_yl.data.rbegin(),  xl_yl.data.rend(),  "xl_yl");
        // cout << ind; print_array(xl_yr.data.rbegin(),  xl_yr.data.rend(),  "xl_yr");
        // cout << ind; print_array(xr_yl.data.rbegin(),  xr_yl.data.rend(),  "xr_yl");
        // cout << ind; print_array(xr_yr.data.rbegin(),  xr_yr.data.rend(),  "xr_yr");

        *this = (xl_yl << 2*halfMaxSize) + ((xl_yr + xr_yl) << (halfMaxSize)) + xr_yr;

        // cout << ind; print_array(ALL(data), "result");

        assert(isValid());

        return *this;
    }

    BigUInt& divide(uint divisor, uint* remainder = nullptr) {
        // BigUInt quotent;
        // uint rem = 0;
        // for (auto it = data.rbegin(); it != data.rend(); ++it)
        // {
        //     ll cur = ((ll)rem << (sizeof(size_type) * 8)) + *it;
        //     size_type num = cur / divisor;
        //     rem = cur % divisor;

        //     quotent <<= sizeof(size_type) * 8;
        //     quotent += BigUInt(num);
        // }

        // if (remainder) {
        //     *remainder = rem;
        // }

        // *this = quotent;

        // if (isZero()) {
        //     data.clear();
        //     data.push_back(0);
        // }

        throw std::exception();

        return *this;
    }

    BigUInt& karatsuba_multiply(const BigUInt& other) {

        uint maxSize = max(size(), other.size());
        uint halfMaxSize = maxSize >> 1;

        if (maxSize == 1) {
            return multiplyWord(other);
        }

        BigUInt p1 = leftHalf(maxSize)  * other.leftHalf(maxSize);
        BigUInt p2 = rightHalf(maxSize) * other.rightHalf(maxSize);
        BigUInt p3 = (leftHalf(maxSize) + rightHalf(maxSize))*(other.leftHalf(maxSize) + other.rightHalf(maxSize));

        *this = (p1 << 2*(halfMaxSize*8)) + ((p3 - p1 - p2) << halfMaxSize*8) + p2;
        return *this;
    }

    template<typename T> 
    T lo_half(T number) {
        const unsigned char shiftHalf = sizeof(T)*8/2;
        T mask = static_cast<T>(-1) >> shiftHalf;

        return number & mask;
    }

    template<typename T> 
    T hi_half(T number) {
        const unsigned char shiftHalf = sizeof(T)*8/2;
        T mask = static_cast<T>(-1) >> shiftHalf;

        return (number >> shiftHalf) & mask;
    }

    BigUInt& multiplyWord(const BigUInt& other) {
        if (data.size() == 0 || other.size() == 0) {
            data.clear();
            data.push_back(0);
            return *this;
        }

        unsigned char res = data.front() * other.data.front();
        unsigned char digit = res % 10;
        unsigned char carry = res / 10;

        // D((uint)res); D((int)digit); DE((int)carry);

        if (digit || carry) {
            data.front() = digit;

            if (carry) {
                data.push_back(carry);
            }
        }

        return *this;
    }

    BigUInt& left_shift(uint count) {

        while (count--) {
            data.insert(data.begin(), 0);
        }

        return *this;
    }

    bool isZero() const {
        for (auto e : data) {
            if (e != 0) return false;
        }

        return true;
    }

    bool isValid() const {
        for (auto e : data) {
            if (e > 10) {
                return false;
            }
        }

        return true;
    }

    container_type data;
};

template<typename T>
void checkEquals(const T& expected, const T& actual, const std::string& message = "Check failed.") {
    if (actual != expected) {
        cout << message << " Expected: " << expected << ", actual: " << actual << endl;
    }
}

void test() {
    // DE(BigUInt(100).toString());
    // DE(BigUInt("100").toNumber<uint>());
    // DE((BigUInt(65535) + BigUInt(65535)).toNumber<ull>());
    // DE((BigUInt(1) * BigUInt(1)).toNumber<ull>());
    // D(BigUInt(5000000000).size());
    // return;

    const unsigned long long numbersList[] = {0, 1, 2, 5, 10, 50, 100, 255, 256, 500, 511, 512, 64000, 65535, 65536, 5000000000};

    for(auto n : numbersList) {
        DE(n);
        checkEquals(n, BigUInt(n).toNumber<ull>(), "BigUInt(n).toNumber<ull>()");
        checkEquals(to_string(n), BigUInt(n).toString(), "BigUInt(n).toString()");
        checkEquals(n, BigUInt(to_string(n)).toNumber<ull>(), "BigUInt(to_string(n)).toNumber<ull>()");
    }

    for(auto n : numbersList) {
        for (auto m : numbersList) {
            D(n); DE(m);
            checkEquals(n + m, (BigUInt(n) + BigUInt(m)).toNumber<ull>(), "BigUInt(n) + BigUInt(m)");
            checkEquals(n * m, (BigUInt(n) * BigUInt(m)).toNumber<ull>(), "BigUInt(n) * BigUInt(m)");
            // if ((m != 0) && (m < (1LL << 32))) {
            //     checkEquals(n / m, (BigUInt(n) / m).toNumber<ull>(), "BigUInt(n) / m");
            //     checkEquals(n % m, (BigUInt(n) % m).toNumber<ull>(), "BigUInt(n) % m");
            // }

            if (m < 19) {
                checkEquals((ull)(n * pow(10, m)), (BigUInt(n) << m).toNumber<ull>(), "BigUInt(n) << m");
            }
            checkEquals(n + m, (BigUInt(to_string(n)) + BigUInt(to_string(m))).toNumber<ull>(), "BigUInt(to_string(n)) + BigUInt(to_string(m))");
            // checkEquals(n * m, (BigUInt(to_string(n)) * BigUInt(to_string(m))).toNumber<ull>(), "BigUInt(to_string(n)) * BigUInt(to_string(m))");
        }
    }
}
 
int main()
{
    ios::sync_with_stdio(false);

    // test();
    // return 0;

    // std::ifstream in("test10000.in");
    // std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    // std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    string x_str, y_str;
    cin >> x_str >> y_str;

    BigUInt x(x_str);
    BigUInt y(y_str);

    // D(x.size());
    // return 0;

    cout << (x * y).toString() << endl;

    return 0;
}