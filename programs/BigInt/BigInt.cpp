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

// BigInt BigInt::operator-(const BigInt& i2) const
// {
//     BigInt i1(i2.digits); // trying to make i2 negative and keep the rest the same
//     i1.negative = true;
//     if (i2.negative == true){
//         i1.negative = false;  // 1/24 accounting for negative numbers
//     }
//     BigInt i3((*this).digits);
//     i3 = i3+i1;
//     return(BigInt(i3.digits));
// }

BigInt BigInt::operator-(const BigInt &b2) const {
    if (this->negative && !b2.negative) return -((-*this) + b2);
    if(!this->negative && b2.negative) return *this + (-b2);
    if (this->negative && b2.negative) return (-b2) - (-*this);
    if (*this < b2) return  -(b2 - *this);

    
    string n1 = this->digits;
    string n2 = b2.digits;
    string r = "";

    while (n1.size() < n2.size()){
        n1.insert(n1.begin(), '0');
    }

    while (n2.size() < n1.size()){
        n2.insert(n2.begin(), '0');
    }

    int c = 0;
    for (int i = n1.size() -1; i >= 0; i--){
        int d = (n1[i] - '0') - (n2[i] - '0') - c;
        if (d < 0){
            d += 10;
            c = 1; // setting the carry to 1 when the subtraction is too large
        }else{
            c = 0;
        }
        r.insert(r.begin(), d + '0'); //finalizingi the result before loop

    }

    while(r.size() > 1 && r.front() == '0'){
        r.erase(r.begin());
    }
    return BigInt(r);

}

BigInt BigInt::operator-() const{
    BigInt result = *this;
    result.negative =!negative;
    return result;
}

BigInt BigInt::operator*(const BigInt& i2) const
{
  //  return BigInt(0); 
    BigInt i3((*this).digits);
    BigInt final_value(0);
    for (BigInt i = i2.digits; i >= 1; i = i-1) { // 1/23 something that is just the numerical i2
    final_value = final_value+i3;
    }
    if (i2.negative != (*this).negative){
        final_value.negative = true; // 1/24 accounting for negative numbers
    }
    return BigInt(final_value); 
}

BigInt BigInt::operator/(const BigInt& i2) const // 1/24 this is division with truncation
{
    BigInt limit((*this).digits);
    BigInt final_value(0);
    BigInt counter(0);
    BigInt ment(i2.digits);
    limit = limit*2;
    while (counter<limit) { // 1/24 adds i over and over and sees how many times it takes to equal *this
    final_value = final_value+2;
    counter = counter+ment;
    }
   // final_value = final_value-1; // 1/25 fixing so it actually truncates down
    if (i2.negative != (*this).negative){
        final_value.negative = true; // 1/24 accounting for negative numbers
    }
    return BigInt(final_value); 
}

BigInt BigInt::operator^(const BigInt& i2) const 
{
    BigInt final_value(0);                 
    BigInt counter = (*this).digits;
    BigInt counter2 = (*this).digits;
    BigInt i3 = i2.digits;
    
    for (BigInt i = i3; i >= 1; i-1) {
    counter = counter*counter2;
    }

    final_value = counter;
    if(i3%2 == 1 && (*this).negative == true){
    final_value.negative = true;
    }

    return BigInt(final_value);
}

BigInt BigInt::operator%(const BigInt& i2) const 
{
                                            // 1/25 This function replicates how the % operater
                                            // normally works in C++, which is different than the
                                            // mathmatical definition when dealing with negatives
    BigInt final_value(0);                 
    BigInt counter(0);
    
    counter = (*this)/i2;
    counter = counter*i2;
    counter = (*this)-counter;
    final_value = counter;

    return BigInt(final_value); 
}

BigInt BigInt::operator!() const  
{
if ((*this)<=1){
return BigInt(1);  // 1/25 if a negative number is ! it will return 1 as this seems to be standard in programming
}
    BigInt final_value(0);                 
    BigInt counter = (*this).digits;
    
    for (BigInt i = counter-1; i >= 1; i-1) {
    counter = counter*i;
    }

    final_value = counter;

    return BigInt(final_value); 
}