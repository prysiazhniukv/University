#include <stdio.h>

#define BASE (18 * 1111)

typedef struct {
  int Size;
  short *Coef;
} LongInt;


void Add(const LongInt *A, const LongInt *B, LongInt *C) {
  long i;
  long temp;
  const short *a = A->Coef, *b = B->Coef;
  short *c = C->Coef;
  short carry = 0;

  if (A->Size < B->Size) {
    Add(B, A, C);
    return;
  }

  for (i = 0; i < B->Size; i++) {
    temp = a[i] + b[i] + carry;
    if (temp >= BASE) {
      c[i] = temp - BASE;
      carry = 1;
    } else {
      c[i] = temp;
      carry = 0;
    }
  }

  for (; i < A->Size; i++) {
    temp = a[i] + carry;
    if (temp >= BASE) {
      c[i] = temp - BASE;
      carry = 1;
    } else {
      c[i] = temp;
      carry = 0;
    }
  }

  if (carry) {
    c[i] = carry;
    C->Size = A->Size + 1;
  } else {
    C->Size = A->Size;
  }
}

int main() {
  short a[] = {9999, 9999, 9999};
  short b[] = {1};
  short c[4] = {0};  // Одне додаткове місце для можливого перенесення

  LongInt A = {3, a};
  LongInt B = {1, b};
  LongInt C = {0, c};

  Add(&A, &B, &C);

  printf("Result: ");
  for (int i = 0; i < C.Size; i++) {
    printf("%d ", C.Coef[i]);
  }
  printf("\n");

  return 0;
}
