#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>
#include "BigInt.h"
using namespace std;

TEST_CASE("Test can create and render BigInts") {
    BigInt bi;
    CHECK(bi.to_string() == "0");
    BigInt bi2(42);
    CHECK(bi2.to_string() == "42");
    BigInt bi3(-42);
    CHECK(bi3.to_string() == "-42");
    BigInt bi4("123456789012345678901234567890");
    CHECK(bi4.to_string() == "123456789012345678901234567890");
    BigInt bi5("-923456789012345678901234567890");
    CHECK(bi5.to_string() == "-923456789012345678901234567890");
}

TEST_CASE("Test can compare BigInts for equality") {
    BigInt i1("12345");
    BigInt i2("54321");
    BigInt i3("123456");
    BigInt i4("-654321");
    BigInt i5("54321");
    BigInt i6("-54321");
    CHECK((i2 == i5) == true);
    CHECK((i1 == i2) == false);
    CHECK((i1 == i3) == false);
    CHECK((i2 == i6) == false);
}

TEST_CASE("Test can compare BigInts for inequality") {
    BigInt i1("12345");
    BigInt i2("54321");
    BigInt i3("123456");
    BigInt i4("-654321");
    BigInt i5("54321");
    BigInt i6("-54321");
    CHECK((i2 > i5) == false);
    CHECK((i2 > i1) == true);
    CHECK((i4 > i1) == false);
    CHECK((i6 > i4) == true);
}

TEST_CASE("Test can compare BigInts for inequality") {
    BigInt i1("12345");
    BigInt i2("54321");
    BigInt i3("123456");
    BigInt i4("-654321");
    BigInt i5("54321");
    BigInt i6("-54321");
    CHECK((i2 != i5) == false);
    CHECK((i2 >= i1) == true);
    CHECK((i4 < i1) == true);
    CHECK((i6 >= i4) == true);
}

TEST_CASE("Test can add BigInts") {
    BigInt i1("123");
    BigInt i2("321");
    BigInt i3("43210");
    BigInt i4("9999");
    BigInt i5("1");
    CHECK((i1 + i2).to_string() == "444");
    CHECK((i1 + i3).to_string() == "43333");
}