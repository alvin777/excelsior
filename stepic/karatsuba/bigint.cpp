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

uint multiplyWordCounter = 0;

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

template<typename T>
struct value_type_traits {
    static const T max_number = 0;
    static const unsigned char max_digits = 0;
    // T max_number() { return 0; }
};

// template<>
// struct value_type_traits<unsigned char> {
//     static const ull max_number = 10;
// };

template<>
struct value_type_traits<unsigned char> {
    static const unsigned char max_number = 100;
    static const unsigned char max_digits = 2;
};

template<>
struct value_type_traits<unsigned int> {
    static const unsigned int max_number = 1e9;
    static const unsigned char max_digits = 9;
};

template<>
struct value_type_traits<ull> {
    static const ull max_number = 1e19;
    static const unsigned char max_digits = 19;
};


class BigUInt {
public:
    // typedef unsigned char size_type;
    typedef unsigned int size_type;
    // typedef unsigned long long size_type;

    typedef vector<size_type> container_type;
    // typedef list<size_type> container_type;

    static const size_type max_number = value_type_traits<size_type>::max_number;
    static const size_type max_digits = value_type_traits<size_type>::max_digits;

    BigUInt() : data(1) {
    }

    BigUInt(const BigUInt& other) : data(other.data) {
    }

    // BigUInt(const BigUInt&& other) : data(std::move(other.data)) {
    // }

    template<typename T>
    explicit BigUInt(T number) {
        initFromNumber(number);
    }

    BigUInt(const string& str) {
        initFromString(str);
    }

    BigUInt(const char* s) {
        initFromString(s);
    }

    BigUInt(const container_type& array) : 
        data(array.begin(), array.end()) 
    {
    }

    void swap(BigUInt& other) {
        data.swap(other.data);
    }

    string toString() {
        string s;
        for (container_type::const_reverse_iterator it = data.rbegin(); it != data.rend(); ++it) {
            char buf[max_digits+1];
            unsigned char digits = (it == data.rbegin()) ? 1 : max_digits;
            sprintf(buf, "%0*d", digits, *it);
            s += buf;
        }
        return s;
    }

    template<typename T> 
    T toNumber() {
        T number = 0;

        for (container_type::const_reverse_iterator it = data.rbegin(); it != data.rend(); ++it) {
            number *= max_number;
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

    // BigUInt& operator= (const BigUInt&& other) {
    //     data = std::move(other.data);
    //     return *this;
    // }

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
        return sub(other);
    }

    BigUInt operator* (const BigUInt& other) {
        BigUInt res(*this);
        res *= (other);
        return res;
    }

    BigUInt& operator*= (const BigUInt& other) {
        // return multiply(other);
        return karatsuba_multiply(other);
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
            container_type::const_iterator middle = data.begin();
            advance(middle, data.size()/2);
            return BigUInt(container_type(data.begin(), middle));
        }

        container_type::const_iterator last = data.begin();
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
            container_type::const_iterator middle = data.begin();
            advance(middle, data.size()/2);
            return BigUInt(container_type(middle, data.end()));
        } 

        if (totalSize >= 2*data.size()) {
            return BigUInt(container_type((totalSize + 1)/2));
        }

        container_type::const_iterator last = data.begin();
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
            data.push_back(number % max_number);
            number /= max_number;
        }
        // print_array(RALL(data), "data");
    }

    void initFromString(const string& str) {
        const int base = 10;
        size_type value = 0;
        unsigned char currentRank = 0;
        for (string::const_reverse_iterator it = str.rbegin(); it != str.rend(); ++it) {
            value += (*it - '0') * pow(base, currentRank);

            currentRank++;
            currentRank %= max_digits;

            // DE((uint)value);
            
            if (currentRank == 0) {
                data.push_back(value);
                value = 0; 
            }
        }
        if (value) {
            data.push_back(value);
        }
        // print_array(RALL(data), "data");
    }

    BigUInt& add(const BigUInt& other) {
        if (other.size() > size()) {
            data.resize(other.size());
        }

        char carry = 0;
        int i = 0;
        container_type::iterator it = data.begin();
        container_type::const_iterator otherIt = other.data.begin();

        while (carry || i < other.size()) { // while carry flag is on or other has any data
            if (i == data.size()) {
                data.push_back(0);
                it = --data.end();
            }

            // DE((uint)*it);
            // DE((uint)*otherIt);
            // DE((uint)carry);

            if (carry) {
                *it += carry;
                *it %= max_number;
                carry = *it < carry ? 1 : 0;
            }

            if (i < other.size()) {
                *it += *otherIt;
                *it %= max_number;
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

    BigUInt& sub(const BigUInt& other) {

        if (other.isZero()) {
            return *this;
        }

        // cout << "sub" << endl;
        // print_array(RALL(data), "data");
        // print_array(RALL(other.data), "other.data");

        char carry = 0;
        int i = 0;
        container_type::iterator it = data.begin();
        container_type::const_iterator otherIt = other.data.begin();

        while (carry || i < other.size()) { // while carry flag is on or other has any data
            if (i == data.size()) {
                data.push_back(0);
                it = --data.end();
            }

            // D((uint)*it); D((uint)*otherIt); DE((uint)carry);

            if (carry) {
                size_type prevValue = *it;
                *it += (max_number - carry);
                *it %= max_number;
                carry = *it > prevValue ? 1 : 0;
            }

            if (i < other.size()) {
                size_type prevValue = *it;
                *it += (max_number - *otherIt);
                *it %= max_number;
                carry = *it > prevValue ? 1 : carry;
            }

            // D((uint)*it); DE((uint)carry);

            ++i;
            ++it;
            ++otherIt;
        }

        // print_array(RALL(data), "data");

        assert(isValid());

        // cout << "<< sub" << endl;

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

    BigUInt& karatsuba_multiply(const BigUInt& other) {
        // Indent ind;

        // cout << ind << "karatsuba_multiply" << endl;
        // cout << ind; print_array(RALL(data), "data");
        // cout << ind; print_array(RALL(other.data), "other.data");

        if (isZero() || other.isZero()) {
            data.clear();
            data.push_back(0);
            return *this;
        }

        uint maxSize = max(size(), other.size());
        uint halfMaxSize = maxSize >> 1;

        if (maxSize == 1) {
            return multiplyWord(other);
        }

        BigUInt thisLeftHalf   = leftHalf(maxSize);
        BigUInt thisRightHalf  = rightHalf(maxSize);
        BigUInt otherLeftHalf  = other.leftHalf(maxSize);
        BigUInt otherRightHalf = other.rightHalf(maxSize);

        BigUInt p1 = thisLeftHalf; p1.karatsuba_multiply(otherLeftHalf);
        BigUInt p2 = thisRightHalf; p2.karatsuba_multiply(otherRightHalf);
        BigUInt p3 = (thisLeftHalf + thisRightHalf); p3.karatsuba_multiply(otherLeftHalf + otherRightHalf);

        p1.normalize();
        p2.normalize();
        p3.normalize();

        // cout << ind; DE(maxSize); 
        // cout << ind; print_array(RALL(data), "data");
        // cout << ind; print_array(RALL(thisLeftHalf.data),  "leftHalf");
        // cout << ind; print_array(RALL(thisRightHalf.data), "rightHalf");

        // cout << ind; print_array(RALL(other.data), "other.data");
        // cout << ind; print_array(RALL(otherLeftHalf.data),  "other.leftHalf");
        // cout << ind; print_array(RALL(otherRightHalf.data), "other.rightHalf");

        // cout << ind; print_array(RALL(p1.data),  "p1 (aL * bL)");
        // cout << ind; print_array(RALL(p2.data),  "p2 (aR * bR)");
        // cout << ind; print_array(RALL(p3.data),  "p3 (aL + aR)(bL + bR)");

        *this = (p1 << 2*halfMaxSize) + ((p3 - p1 - p2) << halfMaxSize) + p2;
        return *this;
    }

    BigUInt& multiplyWord(const BigUInt& other) {

        // multiplyWordCounter++;

        if (data.size() == 0 || other.size() == 0) {
            data.clear();
            data.push_back(0);
            return *this;
        }

        ull res = (ull)data.front() * other.data.front();
        size_type digit = res % max_number;
        size_type carry = res / max_number;

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


    BigUInt& divide(uint divisor, uint* remainder = NULL) {
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

    void normalize() {
        // auto lastNonZeroIt = find_if(data.rbegin(), data.rend(), [](const size_type& el){ return el > 0; });
        // if (lastNonZeroIt != data.rend()) {
        //     cout << "data.erase" << endl;
        //     data.erase(std::next(lastNonZeroIt).base(), data.end());
        //     cout << "<< data.erase" << endl;
        // }

        // print_array(RALL(data), "data");

        container_type::iterator it = data.begin();
        container_type::iterator lastZeroSequenceBeginIt = data.end();
        for (; it != data.end(); ++it) {
            if (*it == 0 && lastZeroSequenceBeginIt == data.end()) {
                lastZeroSequenceBeginIt = it;
            }
            if (*it != 0) {
                lastZeroSequenceBeginIt = data.end();
            }
        }

        data.erase(lastZeroSequenceBeginIt, data.end());

        // print_array(RALL(data), "data");

        if (data.size() == 0) {
            data.push_back(0);
        }
    }

    bool isZero() const {
        for (container_type::const_iterator it = data.begin(); it != data.end(); ++it) {
            if (*it != 0) return false;
        }

        return true;
    }

    bool isValid() const {
        for (container_type::const_iterator it = data.begin(); it != data.end(); ++it) {
            if (*it > max_number) {
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

// void test() {
//     // DE((BigUInt(10) - BigUInt(1)).toNumber<ull>());
//     // DE((BigUInt(65536) * BigUInt(65536)).toNumber<ull>());
//     // D(BigUInt(5000000000).size());
//     // return;

//     const unsigned long long numbersList[] = {0, 1, 2, 5, 10, 50, 100, 255, 256, 500, 511, 512, 64000, 65535, 65536, 5000000000};

//     for (int i = 0; i < COUNT(numbersList); i++) {
//         ull n = numbersList[i];
//         DE(n);
//         checkEquals(n,            BigUInt(n).toNumber<ull>(), "BigUInt(n).toNumber<ull>()");
//         checkEquals(to_string(n), BigUInt(n).toString(), "BigUInt(n).toString()");
//         checkEquals(n,            BigUInt(to_string(n)).toNumber<ull>(), "BigUInt(to_string(n)).toNumber<ull>()");
//     }

//     for (int i = 0; i < COUNT(numbersList); i++) {
//         ull n = numbersList[i];
//         for (int j = 0; j < COUNT(numbersList); j++) {
//             ull m = numbersList[j];

//             D(n); DE(m);
//             checkEquals(n + m, (BigUInt(n) + BigUInt(m)).toNumber<ull>(), "BigUInt(n) + BigUInt(m)");
//             checkEquals(n * m, (BigUInt(n) * BigUInt(m)).toNumber<ull>(), "BigUInt(n) * BigUInt(m)");

//             if (n >= m) {
//                 checkEquals(n - m, (BigUInt(n) - BigUInt(m)).toNumber<ull>(), "BigUInt(n) - BigUInt(m)");
//             }
//             // if ((m != 0) && (m < (1LL << 32))) {
//             //     checkEquals(n / m, (BigUInt(n) / m).toNumber<ull>(), "BigUInt(n) / m");
//             //     checkEquals(n % m, (BigUInt(n) % m).toNumber<ull>(), "BigUInt(n) % m");
//             // }

//             if (m < 19) {
//                 checkEquals((ull)(n * pow(100, m)), (BigUInt(n) << m).toNumber<ull>(), "BigUInt(n) << m");
//             }
//             // checkEquals(n + m, (BigUInt(to_string(n)) + BigUInt(to_string(m))).toNumber<ull>(), "BigUInt(to_string(n)) + BigUInt(to_string(m))");
//             // checkEquals(n * m, (BigUInt(to_string(n)) * BigUInt(to_string(m))).toNumber<ull>(), "BigUInt(to_string(n)) * BigUInt(to_string(m))");
//         }
//     }
// }
 
int main()
{
    ios::sync_with_stdio(false);

    // test();
    // return 0;

    // std::ifstream in("test50000.in");
    // std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    // std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    string x_str, y_str;
    cin >> x_str >> y_str;

    BigUInt x(x_str);
    BigUInt y(y_str);

    // D(x.size());
    // return 0;

    cout << (x * y).toString() << endl;

    // DE(multiplyWordCounter);

    return 0;
}