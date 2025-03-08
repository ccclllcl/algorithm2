#include<bits/stdc++.h>
#define LL long long
using namespace std;
class BigInteger {   //封装高精度整数运算
private:
    std::vector<int> digits; // 用于存储每个4位16进制数位
    bool negative = false; // 负数标志

public:
    // 默认构造函数
    BigInteger() : digits(1, 0) {}

    void removeLeadingZeros(BigInteger& it){  // 移除前导零
        while (it.digits.size() > 1 && it.digits.back() == 0) {
            it.digits.pop_back();
        }
    }

    // 使用16进制字符串初始化
    BigInteger(const std::string& hex) {
        if (hex[0] == '-') {
            negative = true;
        }
        for (int i = hex.length() - 1; i >= (negative ? 1 : 0); i -= 4) {
            int end = i;
            int start = std::max(i - 3, (negative ? 1 : 0));
            digits.push_back(std::stoi(hex.substr(start, end - start + 1), nullptr, 16));
        }
        removeLeadingZeros(*this);
    }

    BigInteger(LL val){
        negative=val<0;
        val=abs(val);
        while(val)digits.push_back(val%65536),val/=65536;
        if(digits.empty())digits.push_back(0);
    }

    // 转换为16进制字符串
    std::string toHex() const {
        std::string result = (negative ? "-" : "");
        for (int i = digits.size() - 1; i >= 0; --i) {
            char buffer[5];
            sprintf(buffer, "%04X", digits[i]);
            if(i<digits.size()-1)result += std::string(buffer);
            else{
                string tp=std::string(buffer);
                reverse(tp.begin(),tp.end());
                while(tp.size()>1&&tp.back()=='0')tp.pop_back();
                reverse(tp.begin(),tp.end());
                result+=tp;
            }
        }
        return result;
    }

    // 赋值运算符
    BigInteger& operator=(const BigInteger& other) {
        if (this == &other) return *this;
        digits = other.digits;
        negative = other.negative;
        return *this;
    }

    // 比较运算符
    bool operator==(const BigInteger& other) const {
        return negative == other.negative && digits == other.digits;
    }

    bool operator!=(const BigInteger& other) const {
        return !(*this == other);
    }

    // 比较运算符 '<'
    bool operator<(const BigInteger& other) const {
        if (this->negative != other.negative) {
            return this->negative;
        }

        if (this->digits.size() != other.digits.size()) {
            return (this->digits.size() < other.digits.size()) ^ this->negative;
        }

        for (int i = this->digits.size() - 1; i >= 0; --i) {
            if (this->digits[i] != other.digits[i]) {
                return (this->digits[i] < other.digits[i]) ^ this->negative;
            }
        }

        return false; // 相等的情况
    }

    bool operator>(const BigInteger& other) const {
        return other < *this;
    }

    bool operator<=(const BigInteger& other) const {
        return !(*this > other);
    }

    bool operator>=(const BigInteger& other) const {
        return !(*this < other);
    }


    static BigInteger addDigits(const BigInteger& a, const BigInteger& b, bool negative) {
        std::vector<int> result;
        int carry = 0, sum = 0;
        size_t max_len = std::max(a.digits.size(), b.digits.size());

        for (size_t i = 0; i < max_len || carry; ++i) {
            sum = carry + (i < a.digits.size() ? a.digits[i] : 0) + (i < b.digits.size() ? b.digits[i] : 0);
            carry = sum / 65536; // 16^4
            result.push_back(sum % 65536);
        }

        // 移除前导零
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }

        return BigInteger(result, negative);
    }

    static BigInteger subtractDigits(const BigInteger& a, const BigInteger& b, bool negative) {
        std::vector<int> result;
        int borrow = 0, diff = 0;
        for (size_t i = 0; i < a.digits.size(); ++i) {
            diff = a.digits[i] - (i < b.digits.size() ? b.digits[i] : 0) - borrow;
            borrow = (diff < 0) ? 1 : 0;
            if (borrow) diff += 65536;
            result.push_back(diff);
        }

        // 移除前导零
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }

        return BigInteger(result, negative);
    }

    BigInteger operator+(const BigInteger& other) const {
        if (this->negative == other.negative) {
            // 相同符号，简单的数字加法
            return BigInteger::addDigits(*this, other, this->negative);
        } else if(this->negative){
            // 不同符号，需要比较大小决定结果的符号和进行减法
            if (BigInteger::absGreater(*this, other)) {
                return BigInteger::subtractDigits(*this, other, this->negative);
            } else {
                return BigInteger::subtractDigits(other, *this, other.negative);
            }
        }else{
            if (BigInteger::absGreater(other, *this)) {
                return BigInteger::subtractDigits(other, *this, other.negative);
            } else {
                return BigInteger::subtractDigits(*this, other, this->negative);
            }
        }
    }

    // 加法赋值运算符
    BigInteger& operator+=(const BigInteger& other) {
        return (*this)=(*this)+other;
    }

    // 减法运算
    BigInteger operator-(const BigInteger& other) const {
        return (*this)+ Negative(other);
    }

    // 减法赋值运算符
    BigInteger& operator-=(const BigInteger& other) {
        return (*this)=(*this)-other;
    }


    BigInteger operator*(long long multiplier) const {
        bool resultNegative = (this->negative != (multiplier < 0));
        long long absMultiplier = std::abs(multiplier);

        std::vector<int> resultDigits(digits.size() + (std::to_string(absMultiplier).length() / 4 + 1), 0);
        long long carry = 0;

        for (size_t i = 0; i < digits.size(); ++i) {
            carry = 0;
            for (size_t j = 0; j < resultDigits.size(); ++j) {
                long long product = (j < i + 1 ? digits[i] * (j == i ? absMultiplier : 0) : 0) + carry + resultDigits[i + j];
                carry = product / 65536;
                resultDigits[i + j] = product % 65536;
            }
        }

        while (resultDigits.size() > 1 && resultDigits.back() == 0) {
            resultDigits.pop_back();
        }

        return BigInteger(resultDigits, resultNegative);
    }

    // 乘法运算
    BigInteger operator*(const BigInteger& other) const {
        BigInteger result;
        result.digits = std::vector<int>(this->digits.size() + other.digits.size(), 0);
        for (size_t i = 0; i < this->digits.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < other.digits.size() || carry; ++j) {
                long long sum = result.digits[i + j] + (LL)(this->digits[i]) * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                carry = int(sum / 65536);
                result.digits[i + j] = int(sum % 65536);
            }
        }
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }
        result.negative = this->negative != other.negative;
        return result;
    }

    // 乘法赋值运算符
    BigInteger& operator*=(long long other) {
        return (*this)=(*this)*other;
    }

    // 乘法赋值运算符
    BigInteger& operator*=(const BigInteger& other) {
        return (*this)=(*this)*other;
    }

    BigInteger operator/(long long divisor) const {
        if (divisor == 0) {
            throw std::runtime_error("Division by zero");
        }

        bool resultNegative = (this->negative != (divisor < 0));
        long long absDivisor = std::abs(divisor);
        long long remainder = 0;
        std::vector<int> resultDigits(digits.size(), 0);

        for (int i = digits.size() - 1; i >= 0; --i) {
            remainder = remainder * 65536 + digits[i];
            resultDigits[i] = int(remainder / absDivisor);
            remainder %= absDivisor;
        }

        // 清除前导零
        while (resultDigits.size() > 1 && resultDigits.back() == 0) {
            resultDigits.pop_back();
        }

        return BigInteger(resultDigits, resultNegative);
    }

    // 除法运算
    BigInteger operator/(const BigInteger& other) const {
        if (other == BigInteger("0")) {
            throw std::runtime_error("Division by zero");
        }

        BigInteger divisor = other;
        divisor.negative = false; // 用绝对值计算
        BigInteger remainder(digits, false);
        std::vector<int> resultDigits;
        if(absGreater(divisor,remainder))return BigInteger("0");

        BigInteger l("1"),r(remainder);
        while(l<r){
            BigInteger m=(l+r+1)/2;
            if(m*divisor<=remainder)l=m;
            else r=m-1;
        }
        return l;

        BigInteger temp("0");
        for (int i = remainder.digits.size() - 1; i >= 0; --i) {
            temp.digits.insert(temp.digits.begin(), remainder.digits[i]); // 将被除数的数位下移
            int count = 0;
            while (temp >= divisor) {
                temp = temp - divisor;
                ++count;
            }
            resultDigits.insert(resultDigits.begin(), count);
        }

        // 移除前导零
        while (resultDigits.size() > 1 && resultDigits.back() == 0) {
            resultDigits.pop_back();
        }

        return BigInteger(resultDigits, this->negative != other.negative);
    }

    BigInteger& operator/=(long long other){
        return (*this)=(*this)/other;
    }

    // 除法赋值运算符
    BigInteger& operator/=(const BigInteger& other) {
        return (*this)=(*this)/other;
    }

    // 取模运算
    BigInteger operator%(const BigInteger& other) const {
        return (*this)-(((*this)/other)*other);
    }
    // 取模赋值运算符
    BigInteger operator%=(const BigInteger& other){
        return (*this)=(*this%other);
    }

    // 快速幂运算
    static BigInteger modExp(const BigInteger& base, const BigInteger& exp, const BigInteger& mod) {
        BigInteger result(1), b = base % mod, e = exp;
        while (e > 0) {
            if (e.digits[0] % 2 != 0) result = (result * b) % mod;
            e /= 2;
            b = (b * b) % mod;
        }
        return result;
    }

    static bool absGreater(const BigInteger& a, const BigInteger& b) {
        if (a.digits.size() != b.digits.size()) {
            return a.digits.size() > b.digits.size();
        }
        for (int i = a.digits.size() - 1; i >= 0; --i) {
            if (a.digits[i] != b.digits[i]) {
                return a.digits[i] > b.digits[i];
            }
        }
        return false; // 相等的情况
    }

    static BigInteger Negative(const BigInteger& num) {
        BigInteger result(num);
        if(num.digits.size()==1&&num.digits[0]==0)return num;
        result.negative = !num.negative;
        return result;
    }

private:
    BigInteger(const std::vector<int>& digits, bool negative) : digits(digits), negative(negative) {
        removeLeadingZeros(*this);
    }
};

string plainfile,nfile,efile,dfile,cipherfile;
string n_hex,e_hex,d_hex,c_hex,p_hex;
bool sign=false;
bool crypto=false;
void read(string& buffer,const string& path){
    ifstream file(path);
    if(!file){
        cerr<<"Unable to open file: "<<path<<endl;
        exit(0);
    }
    getline(file,buffer);
}
void write(const string& buffer,const string& path){
    ofstream file(path);
    file<<buffer;
}
signed main(int argc,char* argv[]){
    //IOS;
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-pp")==0){
            plainfile=argv[++i];
        }else if(strcmp(argv[i],"-n")==0){
            nfile=argv[++i];
        }else if(strcmp(argv[i],"-e")==0){
            efile=argv[++i];
        }else if(strcmp(argv[i],"-d")==0){
            dfile=argv[++i];
        }else if(strcmp(argv[i],"-c")==0){
            cipherfile=argv[++i];
        }else if(strcmp(argv[i],"-s")==0){
            sign=true;
        }
    }
    if(sign){
        if(!efile.empty())crypto=false;
        else if(!dfile.empty())crypto=true;
        else{
            cerr<<"Wrong mode!"<<endl;
            exit(0);
        }
        if(crypto){
            read(d_hex,dfile);
            read(p_hex,plainfile);
            read(n_hex,nfile);
            BigInteger d(d_hex),p(p_hex),n(n_hex);
            auto res=BigInteger::modExp(p,d,n);
            write(res.toHex(),cipherfile);
        }else{
            read(e_hex,efile);
            read(c_hex,cipherfile);
            read(n_hex,nfile);
            BigInteger e(e_hex),c(c_hex),n(n_hex);
            auto res=BigInteger::modExp(c,e,n);
            write(res.toHex(),plainfile);
        }
    }else{
        if(!efile.empty())crypto=true;
        else if(!dfile.empty())crypto=false;
        else{
            cerr<<"Wrong mode!"<<endl;
            exit(0);
        }
        if(crypto){
            read(e_hex,efile);
            read(p_hex,plainfile);
            read(n_hex,nfile);
            BigInteger e(e_hex),p(p_hex),n(n_hex);
            auto res=BigInteger::modExp(p,e,n);
            write(res.toHex(),cipherfile);
        }else{
            read(d_hex,dfile);
            read(c_hex,cipherfile);
            read(n_hex,nfile);
            BigInteger d(d_hex),c(c_hex),n(n_hex);
            auto res=BigInteger::modExp(c,d,n);
            write(res.toHex(),plainfile);
        }
    }
}
