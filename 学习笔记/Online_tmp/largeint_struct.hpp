#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAXN = 30000;

struct LargeInteger {
 public:
  // 去除前导零
  void cleanLeadZero();
  // 乘以10的n次方
  void multiplyTen(int n);
  // 除以10的n次方
  void divisionTen(int n);
  // 将结果转换成字符串
  string str() const;

  LargeInteger();
  LargeInteger(int);
  LargeInteger(const char *);
  // 截取整数的前n位数
  LargeInteger getSub(int n) const;

  LargeInteger operator=(const char *);
  LargeInteger operator=(int num);

  LargeInteger operator+(const LargeInteger &) const;
  LargeInteger operator-(const LargeInteger &) const;
  LargeInteger operator*(const LargeInteger &) const;
  LargeInteger operator/(const LargeInteger &) const;
  LargeInteger operator%(const LargeInteger &) const;
  LargeInteger operator-=(const LargeInteger &);
  LargeInteger operator+=(const LargeInteger &);
  LargeInteger operator*=(const LargeInteger &);
  LargeInteger operator/=(const LargeInteger &);
  // 重载比较运算符
  bool operator<(const LargeInteger &) const;
  bool operator>(const LargeInteger &) const;
  bool operator<=(const LargeInteger &) const;
  bool operator>=(const LargeInteger &) const;
  bool operator==(const LargeInteger &) const;
  // 重载输入输出流
  friend istream &operator>>(istream &, LargeInteger &);
  friend ostream &operator<<(ostream &, LargeInteger &);

private:
 int s[MAXN];
 int len;
};

void LargeInteger::cleanLeadZero() {
  while (len > 1 && !s[len - 1]) len--;
}

void LargeInteger::divisionTen(int n) {
  int i;
  if (n > len) {
    while (len >= 1) s[len--] = 0;
  } else {
    for (i = 0; i < len - n; i++) {
      s[i] = s[i + n];
    }
    len -= n;
  }
}

void LargeInteger::multiplyTen(int n) {
  if (n > 0) {
    int i;
    for (i = len - 1; i >= 0; i--) {
      s[i + n] = s[i];
    }
    for (i = 0; i < n; i++) {
      s[i] = 0;
    }
    len += n;
  }
}

string LargeInteger::str() const {
  string res = "";
  // 每个位的数逆序添加到str末尾。
  for (int i = 0; i < len; i++) {
    res = (char)(s[i] + '0') + res;
  }
  if (res == "") res = "0";
  return res;
}

LargeInteger::LargeInteger() {
  memset(s, 0, sizeof(s));
  len = 1;
}

LargeInteger::LargeInteger(int num) { *this = num; }

LargeInteger::LargeInteger(const char *num) { *this = num; }

LargeInteger LargeInteger::getSub(int n) const {
  LargeInteger c;
  c.len = 0;
  for (int i = 0; i < n; i++) {
    c.s[c.len++] = s[len - n + i];
  }
  return c;
}

LargeInteger LargeInteger::operator=(const char *num) {
  len = strlen(num);
  for (int i = 0; i < len; i++) {
    s[i] = num[len - i - 1] - '0';
  }
  return *this;
}

LargeInteger LargeInteger::operator=(int num) {
  char s[MAXN];
  sprintf(s, "%d", num);
  *this = s;
  return *this;
}

LargeInteger LargeInteger::operator+(const LargeInteger &x) const {
  LargeInteger r;
  r.len = 0;

  int i, up;
  int maxLen = max(len, x.len);
  for (i = 0, up = 0; up || i < maxLen; i++) {
    int temp = up;
    if (i < len) temp += s[i];
    if (i < x.len) temp += x.s[i];
    up = temp / 10;
    r.s[r.len++] = temp % 10;
  }
  // 去除前导零
  r.cleanLeadZero();
  return r;
}


LargeInteger LargeInteger::operator-(const LargeInteger &b) const {
  LargeInteger c;
  c.len = 0;
  int i;
  // 保存退位
  int down;
  for (i = 0, down = 0; i < len; i++) {
    int temp = s[i] - down;
    if (i < b.len) temp -= b.s[i];
    if (temp >= 0)
      down = 0;
    else {
      down = 1;
      temp += 10;
    }
    c.s[c.len++] = temp;
  }
  c.cleanLeadZero();
  return c;
}

LargeInteger LargeInteger::operator*(const LargeInteger &b) const {
  int i, j;
  LargeInteger c;
  c.len = len + b.len;
  for (i = 0; i < len; i++) {
    for (j = 0; j < b.len; j++) {
      c.s[i + j] += s[i] * b.s[j];
    }
  }

  for (i = 0; i < c.len - 1; i++) {
    c.s[i + 1] += c.s[i] / 10;
    c.s[i] %= 10;
  }
  c.cleanLeadZero();
  return c;
}

LargeInteger LargeInteger::operator/(const LargeInteger &b) const {
  int i, j;
  LargeInteger r;
  r.len = 0;
  // 模拟除法的过程
  // 先取blen - 1位
  LargeInteger temp = this->getSub(b.len - 1);
  for (i = len - b.len; i >= 0; i--) {
    temp = temp * 10 + s[i];
    if (temp < b) {
      r.s[r.len++] = 0;
    } else {
      for (j = 1; j <= 10; j++) {
        if (b * j > temp) break;
      }
      r.s[r.len++] = j - 1;
      temp = temp - (b * (j - 1));
    }
  }
  for (i = 0; i < r.len / 2; i++) {
    int temp = r.s[i];
    r.s[i] = r.s[r.len - 1 - i];
    r.s[r.len - 1 - i] = temp;
  }
  r.cleanLeadZero();
  return r;
}

LargeInteger LargeInteger::operator%(const LargeInteger &b) const {
  LargeInteger r;
  r = *this / b;
  r = *this - r * b;
  return r;
}

LargeInteger LargeInteger::operator+=(const LargeInteger &b) {
  *this = *this + b;
  return *this;
}

LargeInteger LargeInteger::operator-=(const LargeInteger &b) {
  *this = *this - b;
  return *this;
}

LargeInteger LargeInteger::operator*=(const LargeInteger &b) {
  *this = *this * b;
  return *this;
}

LargeInteger LargeInteger::operator/=(const LargeInteger &b) {
  *this = *this / b;
  return *this;
}

bool LargeInteger::operator<(const LargeInteger &b) const {
  if (len != b.len)
    return len < b.len;
  else {
    for (int i = len - 1; i >= 0; i--) {
      if (s[i] != b.s[i]) return s[i] < b.s[i];
    }
  }
  return false;
}

bool LargeInteger::operator>(const LargeInteger &b) const { return b < *this; }

bool LargeInteger::operator<=(const LargeInteger &b) const { return !(b > *this); }

bool LargeInteger::operator>=(const LargeInteger &b) const { return !(*this < b); }

bool LargeInteger::operator==(const LargeInteger &b) const {
  return !(b < *this) && !(b > *this);
}

istream &operator>>(istream &in, LargeInteger &x) {
  string s;
  in >> s;
  x = s.c_str();
  return in;
}

ostream &operator<<(ostream &out, LargeInteger &x) {
  out << x.str();
  return out;
}
