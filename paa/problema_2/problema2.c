/***************************************
  Problem 2 - Salvando arquivvos
    Tempo limite: 0.5s (C/C++)
  Gaspar Andrade - 133633
  UCC: PAA Prof. Dr. Reginaldo Kuroshu
  ICT-UNIFESP 2021.1
 ***************************************/
#include <stdio.h>
#include <stdlib.h>

void merge(int *a, int l, int m, int r) {
  int n1, n2; 
  n1 = m - l + 1;
  n2 = r - m;

  int L[n1], R[n2];

  int i, j;
  for (i = 0; i < n1; i++) L[i] = a[l + i];
  for (j = 0; j < n2; j++) R[j] = a[m + 1 + j];

  i = j = 0;

  int k;
  k = l;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      a[k] = L[i];
      i++;
    }
    else {
      a[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    a[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    a[k] = R[j];
    j++;
    k++;
  }
}

void merge_sort(int *a, int l, int r) {
    if (l >= r) return;
    
    int m;
    m = l + (r - l)/2;
    merge_sort(a, l, m);
    merge_sort(a, m + 1, r);
    merge(a, l, m, r);
}

int get_max(int *a, int c, int n) { 
  int max;
  int l, r;

  max = 0;
  l = 0;
  r = n;

  while (l < r) {
    if (a[r] >= c) r--; // caso o valor mais a direita seja >= c
    else {
      if (a[l] + a[r] <= c && a[l] + a[r] > max) // atualiza max
        max = a[l] + a[r];

      if (abs(c - (a[r] + a[l+1])) > abs(c - (a[r-1] + a[l]))) r--;
      else l++;
    }
  }
  return max;
}

int main() {
  int n, c;
  scanf("%d %d", &n, &c);

  int a[n], i;
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  merge_sort(a, 0, n-1); // O(nlogn)

  //for (i = 0; i < n; i++) printf("%d ", a[i]);

  int result;

  result = get_max(a, c, n-1);

  if (result) printf("%d\n", result);
  else printf("NONE\n");

  return 0;
}
