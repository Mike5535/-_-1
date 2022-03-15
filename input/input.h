#ifndef INPUT_H
#define INPUT_H
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


char* get_string(FILE * ptemp,char end);
void clean_input_product(FILE* ptemp);
bool chek_string(char* temp, bool f ); // включение флага даёт проверку только на цифры
size_t* get_data(FILE* pfile);
bool get_product(Product* temp,FILE* pfile);
Product* chek_null(Product* temp);
#endif // INPUT_H