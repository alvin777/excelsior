#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

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
    typedef unsigned char word_t;
    // typedef unsigned long long word_t;
    // typedef unsigned int word_t;

    BigUInt() : data(1) {
    }

    BigUInt(const BigUInt& other) : data(other.data) {
    }

    explicit BigUInt(uint number) {
        initFromNumber(number);
    }

    // BigUInt(ll number) {
    //     initFromNumber(number);
    // }

    BigUInt(const string& str, uint base = 10) {
        for (auto c : str) {

            DE(c);
            word_t digit = c - '0';

            *this *= BigUInt(base);
            *this += BigUInt(static_cast<uint>(digit));
        }
    }

    BigUInt(const vector<word_t>& array) {
        data = array;
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

        for (int i = 0; i < min(data.size(), sizeof(number)/sizeof(word_t)); ++i) {
            number |= (data[i] << (8*i*sizeof(word_t)));
            // D(data[i]); DE(number);
        }
        return number;
    }

    word_t getLastWord() {
        return data.size() > 0 ? data.front() : 0;
    }

    BigUInt& operator= (const BigUInt& other) {
        data = other.data;
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
        uint wordsShift = count / (sizeof(word_t)*8);
        uint bitsShift  = count % (sizeof(word_t)*8);

        while (wordsShift--) {
            data.insert(data.begin(), 0);
        }

        if (bitsShift != 0) {
            word_t mask = word_t(-1) >> (sizeof(word_t)*8 - bitsShift);

            word_t overflowWord = (data.back() >> (sizeof(word_t)*8 - bitsShift)) & mask;

            for (auto it = data.rbegin(); it != data.rend() - 1; ++it) {
                *it = (*it << bitsShift) | ((*(it+1) >> (sizeof(word_t)*8 - bitsShift)) & mask);
            }

            data.front() <<= bitsShift;

            if (overflowWord) {
                data.insert(data.end(), overflowWord);
            }
        }

        return *this;
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
            auto middle = data.begin() + (data.end() - data.begin())/2;
            return BigUInt(vector<word_t>(data.begin(), middle));
        }

        vector<word_t> newData(data.begin(), min(data.begin() + totalSize/2, data.end()));
        // print_array(newData.rbegin(), newData.rend(), "newData");
        newData.resize(totalSize/2);
        // print_array(newData.rbegin(), newData.rend(), "newData");
        return BigUInt(newData);
    }

    BigUInt leftHalf(uint totalSize) const {
        if (totalSize < data.size()) throw exception();

        if (totalSize == data.size()) {
            auto middle = data.begin() + (data.end() - data.begin())/2;
            return BigUInt(vector<word_t>(middle, data.end()));
        } 

        if (totalSize >= 2*data.size()) {
            return BigUInt(vector<word_t>((totalSize + 1)/2));
        }

        vector<word_t> newData(data.begin() + totalSize/2, data.end());
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
            word_t chunk = number;
            data.push_back(chunk);
            number >>= sizeof(word_t)*8;
        }
    }

    BigUInt& add(const BigUInt& other) {
        if (other.size() > size()) {
            data.resize(other.size());
        }

        char carry = 0;
        int i = 0;

        while (carry || i < other.size()) { // while carry flag is on or other has any data
            if (i == data.size()) {
                data.push_back(0);
            }

            if (carry) {
                data[i] += carry;
                carry = data[i] < carry ? 1 : 0;
            }

            if (i < other.size()) {
                data[i] += other.data[i];
                carry = data[i] < other.data[i] ? 1 : carry;
            }
            i++;            
        }

        return *this;
    }

    BigUInt& multiply(const BigUInt& other) {

        Indent ind;

        cout << ind << "multiply" << endl;
        cout << ind; print_array(data.begin(), data.end(), "data");
        cout << ind; print_array(other.data.begin(), other.data.end(), "other.data");


        if (isZero() || other.isZero()) {
            data.clear();
            data.push_back(0);
            return *this;
        }

        size_t maxSize = max(size(), other.size());
        uint halfMaxSize = maxSize >> 1;

        if (maxSize == 1) {
            multiplyWord(other);
            cout << ind; print_array(ALL(data), "result");
            return *this;
        }

        BigUInt thisLeftHalf   = leftHalf(maxSize);
        BigUInt thisRightHalf  = rightHalf(maxSize);
        BigUInt otherLeftHalf  = other.leftHalf(maxSize);
        BigUInt otherRightHalf = other.rightHalf(maxSize);


        BigUInt xl_yl = thisLeftHalf  * otherLeftHalf;
        BigUInt xl_yr = thisLeftHalf  * otherRightHalf;
        BigUInt xr_yl = thisRightHalf * otherLeftHalf;
        BigUInt xr_yr = thisRightHalf * otherRightHalf;

        // DE(maxSize); 
        // print_array(data.rbegin(), data.rend(), "data");
        // print_array(thisLeftHalf.data.rbegin(),   thisLeftHalf.data.rend(),  "leftHalf");
        // print_array(thisRightHalf.data.rbegin(),  thisRightHalf.data.rend(), "rightHalf");

        // print_array(other.data.rbegin(), other.data.rend(), "other.data");
        // print_array(otherLeftHalf.data.rbegin(),  otherLeftHalf.data.rend(),  "other.leftHalf");
        // print_array(otherRightHalf.data.rbegin(), otherRightHalf.data.rend(), "other.rightHalf");

        // print_array(xl_yl.data.rbegin(),  xl_yl.data.rend(),  "xl_yl");
        // print_array(xl_yr.data.rbegin(),  xl_yr.data.rend(),  "xl_yr");
        // print_array(xr_yl.data.rbegin(),  xr_yl.data.rend(),  "xr_yl");
        // print_array(xr_yr.data.rbegin(),  xr_yr.data.rend(),  "xr_yr");

        *this = (xl_yl << halfMaxSize*2*8) + ((xl_yr + xr_yl) << (halfMaxSize*8)) + xr_yr;
        // print_array(data.rbegin(), data.rend(), "res data");

        cout << ind; print_array(ALL(data), "result");

        return *this;
    }

    BigUInt& divide(uint divisor, uint* remainder = nullptr) {
        BigUInt quotent;
        uint rem = 0;
        for (auto it = data.rbegin(); it != data.rend(); ++it)
        {
            ll cur = (rem << (sizeof(word_t) * 8)) + *it;
            word_t num = cur / divisor;
            rem = cur % divisor;

            quotent <<= sizeof(word_t) * 8;
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

    word_t addWithCarry(word_t a, word_t b, word_t& carry) {
        word_t temp = a + b;
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

        word_t thisLh = hi_half(data.front());
        word_t thisRh = lo_half(data.front());

        word_t otherLh = hi_half(other.data.front());
        word_t otherRh = lo_half(other.data.front());

        // D(thisLh); D(thisRh); D(otherLh); DE(otherRh);


        word_t xl_yl = thisLh * otherLh;
        word_t xl_yr = thisLh * otherRh;
        word_t xr_yl = thisRh * otherLh;
        word_t xr_yr = thisRh * otherRh;

        // D(xl_yl); D(xl_yr); D(xr_yl); DE(xr_yr);


        word_t carry = 0;
        word_t lo = xr_yr;
        lo = addWithCarry(lo, lo_half(xl_yr) << (sizeof(word_t)*8/2), carry);
        lo = addWithCarry(lo, lo_half(xr_yl) << (sizeof(word_t)*8/2), carry);

        word_t hi = carry;
        carry = 0;
        hi = addWithCarry(hi, hi_half(xl_yr), carry);
        hi = addWithCarry(hi, hi_half(xr_yl), carry);
        hi = addWithCarry(hi, xl_yl, carry);

        // D(lo); D(hi); DE(carry);

        data[0] = lo;

        if (hi || carry) {
            data.push_back(hi);

            if (carry) {
                data.push_back(carry);
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

    vector<word_t> data;

    // friend int main();
};

template<typename T>
void checkEquals(const T& expected, const T& actual, const std::string& message = "Check failed.") {
    if (actual != expected) {
        cout << message << " Expected: " << expected << ", actual: " << actual << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);

    // (BigUInt(1U) + BigUInt(255U)).toNumber<uint>();
    // DE((BigUInt(1U) * BigUInt(65536U)).toString());
    // return 0;

    // const auto numbersList = {0, 1, 2, 5, 10, 50, 100, 255, 256, 500, 511, 512, 64000, 65535, 65536};

    // for(unsigned int i : numbersList) {
    //     checkEquals(i, BigUInt(i).toNumber<uint>(), "BigUInt(i).toNumber<uint>()");
    //     checkEquals(to_string(i), BigUInt(i).toString(), "BigUInt(i).toString()");
    //     checkEquals(i, BigUInt(to_string(i)).toNumber<uint>(), "BigUInt(to_string(i)).toNumber<uint>()");
    // }

    // for(unsigned int i : numbersList) {
    //     for (unsigned int j : numbersList) {
    //         cout << "i: " << i << ", j: " << j << endl;
    //         checkEquals(i + j, (BigUInt(i) + BigUInt(j)).toNumber<uint>(), "BigUInt(i) + BigUInt(j)");
    //         checkEquals(i * j, (BigUInt(i) * BigUInt(j)).toNumber<uint>(), "BigUInt(i) * BigUInt(j)");
    //         if (j != 0) {
    //             checkEquals(i / j, (BigUInt(i) / j).toNumber<uint>(), "BigUInt(i) / j");
    //             checkEquals(i % j, (BigUInt(i) % j).toNumber<uint>(), "BigUInt(i) % j");
    //         }
    //         // checkEquals((ull)(i << j), (BigUInt(i) << j).toNumber<ull>(), "BigUInt(i) << j");
    //         checkEquals(i + j, (BigUInt(to_string(i)) + BigUInt(to_string(j))).toNumber<uint>(), "BigUInt(to_string(i)) + BigUInt(to_string(j))");
    //         checkEquals(i * j, (BigUInt(to_string(i)) * BigUInt(to_string(j))).toNumber<uint>(), "BigUInt(to_string(i)) * BigUInt(to_string(j))");
    //     }
    // }

    string x_str, y_str;
    cin >> x_str >> y_str;

    BigUInt x(x_str);
    BigUInt y(y_str);

    cout << (x * y).toString() << endl;

    return 0;
}