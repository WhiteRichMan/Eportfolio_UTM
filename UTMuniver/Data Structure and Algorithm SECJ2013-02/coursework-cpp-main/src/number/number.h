#pragma once

#include <iostream>
#include <vector>

class Number {
 private:
  std::vector<int> digits;
  bool negative = false;

 public:
  Number();
  Number(const std::string &s);
  Number(const int64_t &n);
  Number(const std::vector<int> &v, bool n = false);

  size_t size() const;
  bool is_negative() const;
  uint16_t operator[](const size_t &i) const;
  std::string to_string() const;
  std::vector<int> get_digits() const;

  void set(const std::string &s);
  void load(const std::string &filename);
  void save(const std::string &filename);

  friend std::ostream &operator<<(std::ostream &out, const Number &n);
  bool operator==(const Number &n) const;

  friend Number fft_multiply(const Number &a, const Number &b);
  friend Number column_multiply(const Number &a, const Number &b);
};

Number fft_multiply(const Number &a, const Number &b);
Number column_multiply(const Number &a, const Number &b);