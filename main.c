#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "input.h"
#include "output.h"
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

void main()
{
    Product** all = (Product**)malloc(sizeof(Product*));
    bool f1 = false;  // было ли что-то в потоке
    bool f2 = false;
    all[0] = (Product*)malloc(sizeof(Product));


    size_t i = 0;

    if (get_product(all[i],stdin) == 1)
        f1 = true; // чет
    all[i] = chek_null(all[i]);

    size_t count = 0;

    if (f1 == true)
    {
        do
        {
            if (all[i] != NULL)
            {
                if (all[i]->update_data != NULL)
                {
                    {
                        char c;
                        while ((c = fgetc(stdin)) != '\n')
                            ;
                    }
                }
            }

            all = (Product**)realloc(all, (i + 2) * sizeof(Product*));

            if (count % 2 == 0)
                f2 = false;
            else f1 = false;

            if (all[i] != NULL)
                i++;

            count++;

            all[i] = (Product*)malloc(sizeof(Product));
            if (get_product(all[i],stdin) == 1)
            {
                if (count % 2 == 0)
                    f1 = true;      // между записями одна пустая строка
                else f2 = true;
            }
            all[i] = chek_null(all[i]);
        } while (f1 == true && f2 == true);  // две пустые строки конец записываемых данных
    }

    if (all[0] != NULL)
    {
        my_out(all, i,stdout);
    }


    for (size_t j = 0; j < i; j++)
    {
        if (all[j]->update_data != NULL)
            free(all[j]->update_data);
        free(all[j]->install_data);
        free(all[j]->name);
        free(all[j]->number);
        free(all[j]->product_class);
    }
    free(all);
   
}