#include <bits/stdc++.h>
#include <cstring>
using namespace std;
class String {
public:
  String(const char *str = NULL); // 普通构造函数
  String(const String &other); // 拷贝构造函数
  ~String(void); // 析构函数
  String & operator =(const String &other); // 赋值函数
private:
  char *data; // 用来保存字符串
};

// 普通构造函数
String::String(const char *str) {
  if(str == NULL) {
    data = new char[1];
    *data = '\0'; // 结束标志'\0'
  }
  else {
    int length = strlen(str);
    data = new char[length + 1];
    strcpy(data,str);
  }
}
// 析构函数
String::~String(void) {
  delete []data;
}
// 拷贝构造函数
String::String(const String &other) {
  int length = strlen(other.data);
  data = new char[length + 1];
  strcpy(data,other.data);
}
// 赋值函数
String &String::operator =(const String &other) {
  if(this == &other) { // 检查自赋值
    return *this;
  }
  delete []data;
  int length = strlen(other.data);
  data = new char[length + 1];
  strcpy(data, other.data);
  return *this; // 返回本对象的引用
}

int main(int argc, char const *argv[]) {
  String s = "asdasd";
  String a;
  String b("abc");
  // printf("%s\n", b.data); // 因为定义了private,封装了所以访问不了
  return 0;
}
