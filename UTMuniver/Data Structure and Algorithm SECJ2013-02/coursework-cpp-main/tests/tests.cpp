#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <sstream>
#include <fstream>

#define CATCH_CONFIG_MAIN

#include "../src/number/number.h"

using namespace std;

TEST_CASE("Number Constructors", "[constructors]") {
  SECTION("Default Constructor") {
    Number n;
    CHECK(n.is_negative() == false);
    CHECK(n.get_digits() == vector<int>{0});
  }

  SECTION("String Constructor") {
    Number n("123");
    CHECK(n.is_negative() == false);
    CHECK(n.get_digits() == vector<int>{3, 2, 1});
  }

  SECTION("Negative String Constructor") {
    Number n("-123");
    CHECK(n.is_negative() == true);
    CHECK(n.get_digits() == vector<int>{3, 2, 1});
  }

  SECTION("Invalid String Constructor") {
    // Non numeric string
    CHECK_THROWS_AS(Number("abc"), invalid_argument);
    CHECK_THROWS_AS(Number("abc123"), invalid_argument);
    CHECK_THROWS_AS(Number("123abc"), invalid_argument);
    CHECK_THROWS_AS(Number("a123bc"), invalid_argument);
    // Empty string
    CHECK_THROWS_AS(Number(""), invalid_argument);
    CHECK_THROWS_AS(Number(" "), invalid_argument);
    CHECK_THROWS_AS(Number("-"), invalid_argument);
    // Leading zeros (allowed)
    CHECK_NOTHROW(Number("000123"));
    CHECK_NOTHROW(Number("-000123"));
    // Negative zero
    CHECK_THROWS_AS(Number("-0"), invalid_argument);
    CHECK_THROWS_AS(Number("-000"), invalid_argument);
    // Negative sign in invalid position
    CHECK_THROWS_AS(Number("1-23"), invalid_argument);
    CHECK_THROWS_AS(Number("-1-23"), invalid_argument);
    CHECK_THROWS_AS(Number("123-"), invalid_argument);
  }

  SECTION("uint64 Constructor") {
    Number n1(0);
    CHECK(n1.is_negative() == false);
    CHECK(n1.get_digits() == vector<int>{0});
    Number n2(123);
    CHECK(n2.is_negative() == false);
    CHECK(n2.get_digits() == vector<int>{3, 2, 1});
    Number n3(-123);
    CHECK(n3.is_negative() == true);
    CHECK(n3.get_digits() == vector<int>{3, 2, 1});
  }

  SECTION("Vector Constructor") {
    Number n(vector<int>{3, 2, 1});
    CHECK(n.is_negative() == false);
    CHECK(n.get_digits() == vector<int>{3, 2, 1});
  }

  SECTION("Negative Vector Constructor") {
    Number n(vector<int>{3, 2, 1}, true);
    CHECK(n.is_negative() == true);
    CHECK(n.get_digits() == vector<int>{3, 2, 1});
  }

  SECTION("Invalid Vector Constructor") {
    // Empty vector
    CHECK_THROWS_AS(Number(vector<int>{}), invalid_argument);
    // Vector with leading zeros (allowed)
    CHECK_NOTHROW(Number(vector<int>{0, 0, 1, 2, 3}));
    // Vector with negative zero
    CHECK_THROWS_AS(Number(vector<int>{0}, true), invalid_argument);
    CHECK_THROWS_AS(Number(vector<int>{0, 0, 0}, true), invalid_argument);
    // Vector with not base 10 digits
    CHECK_THROWS_AS(Number(vector<int>{10}), invalid_argument);
    CHECK_THROWS_AS(Number(vector<int>{-1}), invalid_argument);
  }

  SECTION("Copy Constructor") {
    Number n1("123");
    Number n2(n1);
    CHECK(n2.is_negative() == false);
    CHECK(n2.get_digits() == vector<int>{3, 2, 1});
  }

  SECTION("Move Constructor") {
    Number n1("123");
    Number n2(move(n1));
    CHECK(n2.is_negative() == false);
    CHECK(n2.get_digits() == vector<int>{3, 2, 1});
  }
}

TEST_CASE("Number Getters", "[getters]") {
  SECTION("is_negative") {
    CHECK(Number("123").is_negative() == false);
    CHECK(Number("-123").is_negative() == true);
  }

  SECTION("get_digits") {
    CHECK(Number("123").get_digits() == vector<int>{3, 2, 1});
    CHECK(Number("-123").get_digits() == vector<int>{3, 2, 1});
  }

  SECTION("to_string") {
    CHECK(Number("123").to_string() == "123");
    CHECK(Number("-123").to_string() == "-123");
  }

  SECTION("size") {
    CHECK(Number("0").size() == 1);
    CHECK(Number("123").size() == 3);
    CHECK(Number("-123").size() == 3);
  }

  SECTION("operator[]") {
    Number n("123");
    CHECK(n[0] == 3);
    CHECK(n[1] == 2);
    CHECK(n[2] == 1);
  }

  SECTION("operator<<") {
    Number n("0"), n1("123"), n2("-123");
    stringstream s, s1, s2;
    s << n, s1 << n1, s2 << n2;
    CHECK(s.str() == "0");
    CHECK(s1.str() == "123");
    CHECK(s2.str() == "-123");
  }
}

TEST_CASE("Number Setters", "[setters]") {
  SECTION("set") {
    Number n;
    n.set("123");
    CHECK(n.is_negative() == false);
    CHECK(n.get_digits() == vector<int>{3, 2, 1});
  }
}

TEST_CASE("Number Save & Load", "[file_io]") {
  SECTION("write") {
    Number n("123456789123456789123456789");
    n.save("test.txt");
    ifstream f("test.txt");
    string s;
    f >> s;
    CHECK(s == "123456789123456789123456789");
  }

  SECTION("read") {
    Number n;
    n.load("test.txt");
    CHECK(n.is_negative() == false);
    CHECK(n.to_string() == "123456789123456789123456789");
  }
}

TEST_CASE("Number Multiplication", "[multiplication]") {
  auto n1 = GENERATE(0LL, 123LL, -123LL, 1234567890LL, -1234567890LL);
  auto n2 = GENERATE(0LL, 123LL, -123LL, 1234567890LL, -1234567890LL);
  auto res = n1 * n2;

  SECTION("fft_multiply") {
    CHECK(fft_multiply(Number(n1), Number(n2)) == Number(res));
  }

  SECTION("column_multiply") {
    CHECK(column_multiply(Number(n1), Number(n2)) == Number(res));
  }
}

TEST_CASE("Numbers Benchmark", "[!benchmark]") {
  auto random_string = [](int len) -> string {
    string s;
    for (int i = 0; i < len; i++)
      s += "0123456789"[rand() % (i ? 10 : 9) + (i == 0)];
    return s;
  };

  auto n = GENERATE(0, 2, 4, 8, 10, 12, 14);
  int len1 = 1 << n, len2 = 1 << n;
  auto n1 = random_string(len1);
  auto n2 = random_string(len2);

  BENCHMARK("fft multiply: " + to_string(len1) + " x " + to_string(len2)) {
    return fft_multiply(Number(n1), Number(n2));
  };

  BENCHMARK("column multiply: " + to_string(len1) + " x " + to_string(len2)) {
    return column_multiply(Number(n1), Number(n2));
  };
}