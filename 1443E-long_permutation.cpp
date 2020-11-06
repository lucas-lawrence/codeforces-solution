#include <bits/stdc++.h>
using namespace std;
void next(int p[], int n, int k);
void reverseSubArray(int p[], int i, int j);

int main() {
  // the two lines below allow a much faster input and output
  // when using cin and cout
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  int p[n];
  for (int i = 0; i < n; i++) {
    p[i] = i+1;
  }
  
  int a, x, y;
  for (int i = 0; i<q; i++) {
    cin >> a;
    if (a == 1) {
      cin >> x >> y;
      unsigned long long int sum = 0;
      for (int j = x-1; j<y; j++){
        sum += p[j];
      }
      cout << sum << endl;
    } else {
      cin >> x;
      next(p,n,x);
    }
  }
}

void next(int p[], int n, int k) {
  if (k > 0) {
    unsigned long long int num = 1;
    int j = 1;
    while (num <= k){
      j = j + 1;
      num *= j;
    }
    num = num/j;
    j = j - 1;

    int x = n, i, max = n+1;

    for (i = n-j; i < n; i++) {
      if (p[n-j-1] < p[i] && p[i] < max) {
        x = i;
        max = p[x];
      } else if (x==n && p[i-1] < p[i]) {
        x = i;
        max = 0;
        break;
      }
    }

    if (max != n+1 && max != 0 && x < n) {
      int b = p[n-j-1];
      p[n-j-1] = p[x];
      p[x] = b;
      next(p, n, k-num);
    } else if (!max && x < n) {
      for (i = j; i > n-x; i--) {
        num = num/i;
      }

      int y, max = n+1;
      for (i = x; i < n; i++) {
        if (p[x-1] < p[i] && p[i] < max) {
          y = i;
          max = p[y];
        }
      }

      int b = p[x-1];
      p[x-1] = p[y];
      p[y] = b;
      next(p, n, k-num);
    } else if (x == n) {
      x = n-j-1;
      for (i = n-j-2; i > -1; i--) {
        if (p[i] > p[x]) {
          x = i;
        } else {
          x = i;
          break;
        }
      }

      int y, max = n+1;
      for (i = x; i < n; i++) {
        if (p[x] < p[i] && p[i] < max) {
          y = i;
          max = p[y];
        }
      }

      int b = p[x];
      p[x] = p[y];
      p[y] = b;
      reverseSubArray(p, x+1, n);
      reverseSubArray(p, n-j, n);
      next(p, n, k-num);
    }
  }
}

void reverseSubArray(int p[], int x, int y) {
  int d = (y-x+1)/2;
  for (int i = 0; i < d; i++){
    int b = p[x+i];
    p[x+i] = p[y-i-1];
    p[y-i-1] = b;
  }
}
