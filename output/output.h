#ifndef OUTPUT_H
#define OUTPUT_H
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef PRODUCT_H
#define PRODUCT_H
#define size 3
typedef struct
{
    char* name;
    char* product_class;
    char* number;
    size_t* install_data;
    size_t* update_data;
}Product;
#endif

void print_data(FILE* p_out, size_t* data);
void print_product(FILE* p_out,Product* temp);
void print_products(Product** one_class, size_t size_temp, FILE* pfile);
void my_out(Product** all, size_t size_all,FILE* pfile);
#endif // OUTPUT_H