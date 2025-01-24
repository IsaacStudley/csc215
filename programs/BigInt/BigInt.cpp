#include <iostream>
#include <string>
#include "BigInt.h"
#define to_num(c) (c-'0')
#define digit_to_char(d) (d+'0')
using namespace std;

string increment_digit_string(const string &digit_string)
{
    string digits = digit_string;
    int pos = digits.size() - 1;
    char next_digit = digits[pos] + 1;

    while (next_digit > '9' && pos >= 0) {
        digits[pos] = '0';
        next_digit = digits[--pos] + 1;
    }

    if (pos >= 0)
        digits[pos] = next_digit;
    else
        digits = "1" + digits;

    return digits;
}

string sum_common_len_digit_strs(const string &s1, const string &s2)
{
    char digit_sum, carry = 0;
    string sum = s1;

    for (int i = s1.size() - 1; i >= 0; i--) {
        digit_sum = to_num(s1[i]) + to_num(s2[i]) + carry;
        sum[i] = digit_to_char(digit_sum % 10);
        carry = digit_sum > 9 ? 1 : 0;
    }

    return carry ? "c+" + sum : sum;
}


BigInt::BigInt()
{
    negative = false;
    digits = "0";
}

BigInt::BigInt(int i)
{
    negative = (i >= 0) ? false : true;
    digits = (i >= 0) ? std::to_string(i) : std::to_string(-i);
}

BigInt::BigInt(string n)
{
    negative = (n.front() == '-') ? true: false;
    digits = (n.front() == '-') ? n.substr(1, n.size() - 1) : n;
}

string BigInt::to_string() const
{
    return (!negative) ? digits : "-" + digits;
}

bool BigInt::operator==(const BigInt& i2) const
{
    if (digits.size() != i2.digits.size()) return false;
    if (negative != i2.negative) return false;
    for (int i = 0; i < digits.size(); i++)
        if (digits[i] != i2.digits[i])
            return false;
    return true;
}

bool BigInt::operator>(const BigInt& i2) const
{
    if (!negative && i2.negative) return true;
    if (negative && !i2.negative) return false;
    // They have the same sign
    if (digits.size() > i2.digits.size()) {
        return negative ? false : true;
    }
    if (digits.size() < i2.digits.size()) {
        return negative ? true : false;
    }
    // They have the same number of digits 
    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] > i2.digits[i]) {
            return negative ? false : true;
        }
    }
    // They are equal
    return false;
}

bool BigInt::operator!=(const BigInt& i2) const
{
    return !(this->operator==(i2));
}

bool BigInt::operator<=(const BigInt& i2) const
{
    return !(this->operator>(i2));
}

bool BigInt::operator<(const BigInt& i2) const
{
    return !(this->operator==(i2)) && !(this->operator>(i2));
}

bool BigInt::operator>=(const BigInt& i2) const
{
    return (this->operator>(i2)) || (this->operator==(i2));
}

BigInt BigInt::operator+(const BigInt& i2) const
{
    if ((*this).digits.size() == i2.digits.size()) {
        string raw_sum = sum_common_len_digit_strs((*this).digits, i2.digits);
        if (raw_sum[0] == 'c')
            return BigInt("1" + raw_sum.substr(2));
        return BigInt(raw_sum);
    }
        
    // Addends have different numbers of digits
    const BigInt *longer;
    const BigInt *shorter;
    int common, extra;
    string summed_common_digits, leading_digits;

    if ((*this).digits.size() > i2.digits.size()) {
        longer = this;
        shorter = &i2;
    } else {
        longer = &i2;
        shorter = this;
    };

    common = shorter->digits.size();
    extra = longer->digits.size() - common;
    summed_common_digits = sum_common_len_digit_strs(
       shorter->digits, 
       longer->digits.substr(extra)
    );
    leading_digits = longer->digits.substr(0, extra);

    if (summed_common_digits[0] != 'c')
        return BigInt(leading_digits + summed_common_digits);

    return BigInt(increment_digit_string(leading_digits) +
                  summed_common_digits.substr(2));
}

BigInt BigInt::operator-(const BigInt& i2) const
{
    //i2 = BigInt(-i2);
    BigInt i2("-"+i2.digits); // trying to make i2 negative and keep the rest the same
    if ((*this).digits.size() == i2.digits.size()) {
        string raw_sum = sum_common_len_digit_strs((*this).digits, i2.digits);
        if (raw_sum[0] == 'c')
            return BigInt("1" + raw_sum.substr(2));
        return BigInt(raw_sum);
    }
        
    // Addends have different numbers of digits
    const BigInt *longer;
    const BigInt *shorter;
    int common, extra;
    string summed_common_digits, leading_digits;

    if ((*this).digits.size() > i2.digits.size()) {
        longer = this;
        shorter = &i2;
    } else {
        longer = &i2;
        shorter = this;
    };

    common = shorter->digits.size();
    extra = longer->digits.size() - common;
    summed_common_digits = sum_common_len_digit_strs(
       shorter->digits, 
       longer->digits.substr(extra)
    );
    leading_digits = longer->digits.substr(0, extra);

    if (summed_common_digits[0] != 'c')
        return BigInt(leading_digits + summed_common_digits);

    return BigInt(increment_digit_string(leading_digits) +
                  summed_common_digits.substr(2));
}

BigInt BigInt::operator*(const BigInt& i2) const
{
    BigInt i3((*this).digits);
    BigInt final_value(0);
    for (BigInt i = i2.digits; i >= 0; i-1) { // 1/23 something that is just the numerical i2
    final_value = final_value+i3;
    }
    return BigInt(final_value); // 1/24 this may only work right with positive numbers
}