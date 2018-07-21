# Notes
## 理性分析 C++(-O2) 和 JS 的性能差距.
### Test1：
#### 最后一行：时间(ms)
```
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[]) {
  int t = clock();
  int a = 1000000000,b = 1;
   while(a) {
     b <<= 1;
     a--;
   }
  printf("%d ms\n",clock() - t);
  return 0;
}

// 0 ms
```

```
var t;
t = new Date;
var a = 1000000000,
    b = 1;
while(a) {
    b <<= 1;
    a--;
}
console.log(new Date - t + "ms");

// 915ms
```
### Test2：
```
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
int a[10000100];
void quick_sort(int a[], int l, int r) {
    if (l < r) {
        int i = l, j = r, x = a[l];
        while (i < j) {
            while(i < j && a[j] >= x) j--;
            if(i < j) a[i++] = a[j];
            while(i < j && a[i] < x) i++;
            if(i < j) a[j--] = a[i];
        }
        a[i] = x;
        quick_sort(a, l, i - 1);
        quick_sort(a, i + 1, r);
    }
}
int main(int argc, char const *argv[]) {
  srand((int)time(0));
  for(int i = 0;i < 10000000; i++) {
    a[i] = rand();
  }
  int t = clock();
  quick_sort(a,0,10000000);
  printf("%d ms\n",clock() -t);
  return 0;
}

// 1738 ms
```
```
function quick_sort(a,l,r) {
    if (l < r) {
        var i = l, j = r, x = a[l];
        while (i < j) {
            while(i < j && a[j] >= x) j--;
            if(i < j) a[i++] = a[j];
            while(i < j && a[i] < x) i++;
            if(i < j) a[j--] = a[i];
        }
        a[i] = x;
        quick_sort(a, l, i - 1);
        quick_sort(a, i + 1, r);
    }
}
var s,i,t;
for(i=0,s=[];i<10000000;i++) s.push(Math.random()*1E7|0);
t = new Date;
quick_sort(s,0,10000000);
console.log(new Date - t + " ms");

// 3080 ms
```
### Test3：
```
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
const int maxn = 50000000;
int a[maxn];
int p[maxn],m[maxn];
int pc;
int main(int argc, char const *argv[]) {
  int t = clock();
  for(int i = 2; i < maxn; i++) {
    if(m[i] == 0) {
      p[++pc] = m[i] = i;
    }
    int k = 0;
    for(int j = 1; j <= pc && p[j] <= m[i] && (k = p[j] * i) < maxn; j++) {
      m[k] = p[j];
    }
  }
  int ans = 0;
  for(int i = 1; i <= pc; i++) {
    ans ^= p[i];
  }
  printf("%d\n", ans);
  printf("%d ms\n",clock() - t);
  return 0;
}

// 338 ms
```
```
var pc = 0;

var m = [];
var p = [];
function solve() {
    // console.log("ok");
    var i;
    for(i = 2 ;i < 50000000;i++) {
        if(m[i] == null) {
            // console.log(i);
            p[++pc]  = m[i] = i;
        }
        var k = 0;
        var j ;
        for(j = 1; j <= pc && p[j] <= m[i] && (k = p[j] * i) < 50000000; j++) {
            m[k] = p[j];
        }
    }
    // console.log("pc = " + pc);
    var ans = 0;
    for(var i = 1; i <= pc; i++) {
        ans ^= p[i];
    }
    console.log("ans= " +  ans);
}
t = new Date;
solve();
console.log(new Date - t + " ms");

// 8096 ms

```
### Test4：
```
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000;

int G[1000][1000];
int sed = 0;
inline int getRand()
{
  return sed = (sed * sed * 73 + sed * 233 + 19260817) & 0x0000ffff;
}
int main(int argc, char const *argv[]) {
  int t = clock();
  for(int i = 0; i < maxn; i++) {
    for(int j = 0; j < maxn; j++) {
      G[i][j] = getRand();
    }
  }
  for(int i = 0; i < maxn; i++) {
    for(int j = 0; j < maxn; j++) {
      for(int k = 0; k < maxn; k++) {
        if(G[j][k] > G[j][i] + G[i][k]) {
          G[j][k] = G[j][i] + G[i][k];
        }
      }
    }
  }
  int ans = 0;
  for(int i = 0; i < maxn; i++) {
    for(int j = 0; j < maxn; j++) {
      ans ^= G[i][j];
    }
  }
  printf("%d\n", ans);
  printf("%d ms\n",clock() - t);
  return 0;
}

// 1718 ms
```
```
var sed = 0;
var G = new Array();
function getRand() {
    var res = sed = (sed * sed * 73 + sed * 233 + 19260817) & 0x0000ffff;
    // console.log("res = " +  res);
    return res;
}
function solve() {
    // console.log("ok");
    for(var i = 0; i < 1000; i++) {
        G[i] = new Array();
        for(var j = 0; j < 1000; j++) {
            G[i][j]  = getRand();
        }
    }
    for(var i = 0; i < 1000; i++) {
        for(var j = 0; j < 1000; j++) {
            for(var k = 0; k < 1000; k++) {
                if(G[j][k] > G[j][i] + G[i][k]) {
                    G[j][k] = G[j][i] + G[i][k];
                }
            }
        }
    }
    var ans = 0;
    for(var i = 0; i < 1000; i++) {
        for(var j = 0; j < 1000; j++) {
            ans ^= G[i][j];
        }
    }
    console.log("ans= " +  ans);
}
t = new Date;
solve();
console.log(new Date - t + " ms");

// 3440 ms

```
### Test5：
```
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000000000; // 1e9
typedef unsigned long long ull;
int P = 1000000007;

int main(int argc, char const *argv[]) {
  int t = clock();
  ull ans = 1;
  for(int i = 1; i < maxn; i++) {
    ans = ans * i % P;
  }
  printf("%llu\n",ans);
  printf("%d ms\n",clock() - t);
  return 0;
}

// 11953 ms
```
```
var P = 1000000007;
var maxn = 1000000000;// 1e9
function solve() {
    // console.log("ok");
    var ans =  1;
    for(var i = 1; i < maxn; i++) {
        ans = ans * i % P;
    }
    console.log("ans= " +  ans);
}
t = new Date;
solve();
console.log(new Date - t + " ms");

// 32175 ms
```
