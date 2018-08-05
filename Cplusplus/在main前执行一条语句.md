```
#include <iostream>
#include <stdlib.h>
#include <functional>

using namespace std;

// lambda expression
auto a = []() {
  std::cout << "before main" << '\n';
  return 0;
}();

// function<int(void)> b = [](){
//     cout << "ok" << endl;
//     return 0;
// };
int main(int argc, char const *argv[]) {
  std::cout << "main" << '\n';
  return 0;
}

```
