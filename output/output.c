#include "output.h"

void print_data(FILE* p_out, size_t* data)
{
    if (data[0] < 10)
    {
        fprintf(p_out, "%u.%u.%u\n", data[0], data[1], data[2]);
        return;
    }
    if (data[1] < 10)
    {
        fprintf(p_out, "%u.%u.%u\n", data[0], data[1], data[2]);
        return;
    }
    if (data[0] < 10 && data[1] < 10)
    {
        fprintf(p_out, "%u.%u.%u\n", data[0], data[1], data[2]);
        return;
    }
    fprintf(p_out, "%u.%u.%u\n", data[0], data[1], data[2]);
}

void print_product(FILE* p_out,Product* temp)
{
    fprintf(p_out,"%s\n", temp->name);
    fprintf(p_out,"%s\n", temp->product_class);
    fprintf(p_out, "%s\n", temp->number);
    print_data(stdout,temp->install_data);
    if (temp->update_data != NULL) print_data(stdout, temp->update_data);
    fprintf(p_out, "\n");
}

void print_products(Product** one_class, size_t size_temp)
{
    if (one_class == NULL)
        return;
    size_t i, j, str_echo;
    for(i = 1; i < size_temp; i++)
        for (j = 0; j < size_temp - i; j++)
        {
            str_echo = strcmp(one_class[j + 1]->name, one_class[j]->name);
            if (str_echo < 0)
            {
                Product* temp = one_class[j];
                one_class[j] = one_class[j + 1];
                one_class[j + 1] = temp;
            }
        }
    for (i = 0; i < size_temp; i ++ ) print_product(stdout, one_class[i]);
}



void my_out(Product** all, size_t size_all)
{
    char** unique_clas = (char**)malloc(sizeof(char*));
    size_t size_unique_clas = 1;
    unique_clas[0] = all[0]->product_class;

    
    for (size_t j = 0; j < size_all; j++)
    {
        bool flag_unique = false;
        for (size_t k = 0; k < size_unique_clas; k++)
        {
            if (strcmp(all[j]->product_class, unique_clas[k]) == 0)
                flag_unique = true;
        }
        if (flag_unique == false)
        {
            
            unique_clas = (char**)realloc(unique_clas,(size_unique_clas + 1)*sizeof(char*));

            unique_clas[size_unique_clas] = all[j]->product_class;

            size_unique_clas++;
        }
    }

    for (size_t i = 0; i < size_unique_clas; i++)
    {
        Product** buff = NULL;
        size_t count = 0;
        for (size_t l = 0; l < size_all; l++)
        {
            
            if (strcmp(all[l]->product_class, unique_clas[i]) == 0 && (all[l]->update_data == NULL || (all[l]->update_data[0] == all[l]->install_data[0] && all[l]->update_data[1] == all[l]->install_data[1] && all[l]->update_data[2] == all[l]->install_data[2])))
            {
                buff = (Product**)realloc(buff,(count + 1) * sizeof(Product*));
                buff[count] = all[l];
                count++;
            }
      
        }
        print_products(buff, count);
        free(buff);
    }
    free(unique_clas);
}