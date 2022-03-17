#include "input.h"
#include "output.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef PRODUCT_H
#define PRODUCT_H
#define size 3
typedef struct {
  char *name;
  char *product_class;
  char *number;
  size_t *install_data;
  size_t *update_data;
} Product;
#endif

void main() {
  size_t *i = (size_t *)malloc(sizeof(size_t));

  Product **al = innput(stdin, i);

  if (al[0] != NULL) {
    my_out(al, i[0], stdout);
  }

  for (size_t j = 0; j < i[0]; j++) {
    free_product(al[j]);
    free(al[j]);
  }
  free(i);

  free(al);
}
