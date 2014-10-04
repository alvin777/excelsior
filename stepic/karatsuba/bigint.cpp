#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <list>

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
    // typedef unsigned char size_type;
    typedef unsigned int size_type;
    // typedef unsigned long long size_type;

    // typedef vector<size_type> container_type;
    typedef list<size_type> container_type;

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

    BigUInt(const string& str, uint base = 10) {
        for (auto c : str) {
            size_type digit = c - '0';

            *this *= BigUInt(base);
            *this += BigUInt(static_cast<uint>(digit));
        }
    }

    BigUInt(const container_type& array) : 
        data(array.begin(), array.end()) 
    {
    }

    string toString(int base = 10) {
        string str;
        BigUInt temp(*this);
        uint rem = 0;
        while (temp.size() > 1 || temp.data.front() > 0) {
            temp.divide(base, &rem);
            string char_str;
            char_str += ('0' + rem);
            str = char_str + str;
        }
        return str.length() ? str : "0";
    }

    template<typename T> 
    T toNumber() {
        T number = 0;

        auto it = data.begin();
        for (int i = 0; i < min(data.size(), sizeof(number)/sizeof(size_type)); ++i, ++it) {
            number |= (static_cast<T>(*it) << (8*i*sizeof(size_type)));
            // D(data[i]); DE(number);
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

        if (sizeof(T) <= sizeof(size_type))  {
            data.push_back(number);
            return;
        }

        while (number) {
            size_type word = number;
            data.push_back(word);
            number >>= sizeof(size_type)*8;
        }
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
            }

            if (carry) {
                *it += carry;
                carry = *it < carry ? 1 : 0;
            }

            if (i < other.size()) {
                *it += *otherIt;
                carry = *it < *otherIt ? 1 : carry;
            }
            ++i;
            ++it;
            ++otherIt;
        }

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

        *this = (xl_yl << 2*halfMaxSize*sizeof(size_type)*8) + ((xl_yr + xr_yl) << (halfMaxSize*sizeof(size_type)*8)) + xr_yr;

        // cout << ind; print_array(ALL(data), "result");

        return *this;
    }

    BigUInt& divide(uint divisor, uint* remainder = nullptr) {
        BigUInt quotent;
        uint rem = 0;
        for (auto it = data.rbegin(); it != data.rend(); ++it)
        {
            ll cur = ((ll)rem << (sizeof(size_type) * 8)) + *it;
            size_type num = cur / divisor;
            rem = cur % divisor;

            quotent <<= sizeof(size_type) * 8;
            quotent += BigUInt(num);
        }

        if (remainder) {
            *remainder = rem;
        }

        *this = quotent;

        if (isZero()) {
            data.clear();
            data.push_back(0);
        }

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

    size_type addWithCarry(size_type a, size_type b, size_type& carry) {
        size_type temp = a + b;
        if (temp < a) {
            carry++;
        }
        return temp;
    }

    BigUInt& multiplyWord(const BigUInt& other) {
        if (data.size() == 0 || other.size() == 0) {
            data.clear();
            return *this;
        }

        size_type thisLh = hi_half(data.front());
        size_type thisRh = lo_half(data.front());

        size_type otherLh = hi_half(other.data.front());
        size_type otherRh = lo_half(other.data.front());

        // D(thisLh); D(thisRh); D(otherLh); DE(otherRh);


        size_type xl_yl = thisLh * otherLh;
        size_type xl_yr = thisLh * otherRh;
        size_type xr_yl = thisRh * otherLh;
        size_type xr_yr = thisRh * otherRh;

        // D(xl_yl); D(xl_yr); D(xr_yl); DE(xr_yr);


        size_type carry = 0;
        size_type lo = xr_yr;
        lo = addWithCarry(lo, lo_half(xl_yr) << (sizeof(size_type)*8/2), carry);
        lo = addWithCarry(lo, lo_half(xr_yl) << (sizeof(size_type)*8/2), carry);

        size_type hi = carry;
        carry = 0;
        hi = addWithCarry(hi, hi_half(xl_yr), carry);
        hi = addWithCarry(hi, hi_half(xr_yl), carry);
        hi = addWithCarry(hi, xl_yl, carry);

        // D(lo); D(hi); DE(carry);

        data.front() = lo;

        if (hi || carry) {
            data.push_back(hi);

            if (carry) {
                data.push_back(carry);
            }
        }

        return *this;
    }

    BigUInt& left_shift(uint count) {
        uint wordsShift = count / (sizeof(size_type)*8);
        uint bitsShift  = count % (sizeof(size_type)*8);
        uint compliment_bits_shift = sizeof(size_type)*8 - bitsShift;

        while (wordsShift--) {
            data.insert(data.begin(), 0);
        }

        if (bitsShift != 0) {
            size_type mask = size_type(-1) >> compliment_bits_shift;

            size_type overflowWord = (data.back() >> compliment_bits_shift) & mask;

            for (auto it = data.rbegin(); it != --data.rend(); ++it) {
                *it = (*it << bitsShift) | ((*next(it) >> compliment_bits_shift) & mask);
            }

            data.front() <<= bitsShift;

            if (overflowWord) {
                data.insert(data.end(), overflowWord);
            }
        }

        return *this;
    }

    bool isZero() const {
        for (auto e : data) {
            if (e != 0) return false;
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
    // DE((BigUInt(0) * BigUInt(5000000000)).toNumber<ull>());
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
            if ((m != 0) && (m < (1LL << 32))) {
                checkEquals(n / m, (BigUInt(n) / m).toNumber<ull>(), "BigUInt(n) / m");
                checkEquals(n % m, (BigUInt(n) % m).toNumber<ull>(), "BigUInt(n) % m");
            }

            if (m < 64) {
                checkEquals((ull)(n << m), (BigUInt(n) << m).toNumber<ull>(), "BigUInt(n) << m");
            }
            checkEquals(n + m, (BigUInt(to_string(n)) + BigUInt(to_string(m))).toNumber<ull>(), "BigUInt(to_string(n)) + BigUInt(to_string(m))");
            checkEquals(n * m, (BigUInt(to_string(n)) * BigUInt(to_string(m))).toNumber<ull>(), "BigUInt(to_string(n)) * BigUInt(to_string(m))");
        }
    }
}
 
int main()
{
    ios::sync_with_stdio(false);

    // test();
    // return 0;

    std::ifstream in("test10000.in");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    string x_str, y_str;
    cin >> x_str >> y_str;

    BigUInt x(x_str);
    BigUInt y(y_str);

    D(x.size());
    return 0;

    // cout << (x * y).toString() << endl;

    return 0;
}