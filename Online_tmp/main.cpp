#include <iostream>
#include <cstdio>

#include "largeint_struct.hpp"

using namespace std;

// const int MAXN = 30000;

// 如果采⽤下⾯⽅式来实现，则可能会得到更⾼的分数

/*
// Declaration
struct LargeInteger {
 LargeInteger(const string& val);
 LargeInteger operator+(const LargeInteger& rhs);
 LargeInteger operator-(const LargeInteger& rhs);
 LargeInteger operator*((const LargeInteger& rhs);
 LargeInteger operator/(const LargeInteger& rhs);
priavate:
 // Underlying data storage
};
*/

// 使用了加分项的方法。 若使⽤此⽅法，请包含头⽂件 largeint_struct.hpp

void print_main_menu() {
    cout << "1. add" << endl;
    cout << "2. minus" << endl;
    cout << "3. multiply" << endl;
    cout << "4. divide" << endl;
}
char a[MAXN], b[MAXN];
char op;
int main(int argc, char const *argv[]) {
  // Print the main menu
  print_main_menu();
  // Please insert your code here...

  int type;

  printf("Please enter your selection: \n");
  printf("choose a function: 1-4: \n");
  std::cin >> type;
  if(type > 4 || type < 1) {
    std::cout << "error input!" << '\n';
    return 0;
  }
  if(type == 1) {
    op = '+';
    std::cout << "module: add" << '\n';
    std::cout << "Please enter the left hand side: ";
    scanf("%s", a);
    std::cout << "Please enter the right hand side: ";
    scanf("%s", b);
    LargeInteger aa(a);
    LargeInteger bb(b);
    //去掉前导零
    aa.cleanLeadZero();
    bb.cleanLeadZero();
    std::cout << "Result: ";
    cout << (aa + bb).str() << endl;
  }
  if(type == 2) {
    op = '-';
    std::cout << "module: minus" << '\n';
    std::cout << "Please enter the left hand side: ";
    scanf("%s", a);
    std::cout << "Please enter the right hand side: ";
    scanf("%s", b);
    LargeInteger aa(a);
    LargeInteger bb(b);
    aa.cleanLeadZero();
    bb.cleanLeadZero();
    std::cout << "Result: ";
    cout << (aa - bb).str() << endl;
  }
  if(type == 3) {
    op = '*';
    std::cout << "module: multiply" << '\n';
    std::cout << "Please enter the left hand side: ";
    scanf("%s", a);
    std::cout << "Please enter the right hand side: ";
    scanf("%s", b);
    LargeInteger aa(a);
    LargeInteger bb(b);
    aa.cleanLeadZero();
    bb.cleanLeadZero();
    std::cout << "Result: ";
    cout << (aa * bb).str() << endl;
  }
  if(type == 4) {
    op = '/';
    std::cout << "module: divide" << '\n';
    std::cout << "Please enter the left hand side: ";
    scanf("%s", a);
    std::cout << "Please enter the right hand side: ";
    scanf("%s", b);
    LargeInteger aa(a);
    LargeInteger bb(b);
    aa.cleanLeadZero();
    bb.cleanLeadZero();
    std::cout << "Result: ";
    cout << (aa / bb).str() << endl;
  }

  return 0;
}
