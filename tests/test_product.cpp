#include <gtest/gtest.h>
#include <stdio.h>
extern "C" {
    #include "input.h"
    #include "output.h"
}



TEST(chek_string, WrongFormat) {
    EXPECT_EQ(false, chek_string("Abcd",false));
    EXPECT_EQ(true, chek_string("@#$",false));
}

TEST(get_string, empty_string_stop) {

    FILE* stdinn;
    stdinn = fopen("tests.txt","w") ;
    if (stdinn == NULL) printf ("error\n");
    fprintf (stdinn,"\n");
    
    
    char* prom = get_string(stdinn,' ');
    EXPECT_EQ(NULL, prom);
    free(prom);
    fclose(stdinn);
}

TEST(get_string, one_word) {
    char input[] = {'N','a','m','e','\0'};
    FILE* stdinn;
    stdinn = fmemopen(input, strlen(input), "r");
    
    char* p = (char*)malloc(strlen(input)*sizeof(char));
    strncpy(p, input, strlen(input));    
    
    char* result = get_string(stdinn,' ');
    
    EXPECT_EQ(*(p), *(result));
    
    free(result);
    free(p);
    fclose(stdinn);
}


// позволяет игнорировать оставшиеся данные неправильной записи
TEST(clean_input_product, clean_console_row) {
    char input[] = {'!','\n','m','e','\n','\n'};
    FILE* stdinn;
    stdinn = fmemopen(input, strlen(input), "r");
    
    clean_input_product(stdinn);
    
    EXPECT_EQ( 0, feof(stdinn));
    
    fclose(stdinn);
}


TEST(get_data, rihgt_data) {
    char input[] = {'1','.','0','2','.','2','0','2','2','\n'};
    FILE* stdinn;
    stdinn = fmemopen(input, strlen(input), "r");
    
    size_t* p_temp = get_data(stdinn);
    EXPECT_EQ( 1, p_temp[0]);
    EXPECT_EQ( 2, p_temp[1]);
    EXPECT_EQ( 2022, p_temp[2]);

    free(p_temp);
    fclose(stdinn);
}

TEST(get_product, right_data) {
    char input[] = {'n','\n','c','\n','n','\n','1','.','0','2','.','2','0','2','2','\n'};
    FILE* stdinn;
    stdinn = fmemopen(input, strlen(input), "r");
    
    Product* temp = (Product*)malloc(sizeof(Product));
    get_product(temp,stdinn);


    char pn[] = {'n','\0'};
    char* pname = (char*)malloc(strlen(pn)*sizeof(char));
    strncpy(pname, pn, strlen(pn)); 
    char pcl[] = {'c','\0'};
    char* pclas = (char*)malloc(strlen(pcl)*sizeof(char));
    strncpy(pclas, pcl, strlen(pcl)); 
    char pnu[] = {'n','\0'};
    char* pnum = (char*)malloc(strlen(pnu)*sizeof(char));
    strncpy(pnum, pnu, strlen(pnu)); 

    EXPECT_EQ( *(pname), *(temp->name));
    EXPECT_EQ( *(pclas), *(temp->product_class));
    EXPECT_EQ( *(pnum), *(temp->number));

    free(pname);
    free(pclas);
    free(pnum);

    free_product(temp);
    free(temp);
    fclose(stdinn);
}

TEST(chek_null, return_null_ptr) {
   
    Product* temp = (Product*)malloc(sizeof(Product));
    set_ptr_null(temp);
    temp->name = (char*)malloc(sizeof(char));
    temp->name[0] = 'a';
    Product* p_null = chek_null(temp);
    EXPECT_EQ( NULL , p_null);
    
}

TEST(innput, right_data) {
    char input[] = {'n','\n','c','\n','n','\n','1','.','0','2','.','2','0','2','2','\n','\n','a','\n','c','\n','n','\n','1','.','0','2','.','2','0','2','2','\n','\n','\n'};
    FILE* stdinn;
    stdinn = fmemopen(input, strlen(input), "r");
    

    size_t* pi = (size_t*)malloc(sizeof(size_t));
    Product** temp = innput(stdinn,pi);
    


    char pn[] = {'n','\0'};
    char* pname = (char*)malloc(strlen(pn)*sizeof(char));
    strncpy(pname, pn, strlen(pn)); 
    char pcl[] = {'c','\0'};
    char* pclas = (char*)malloc(strlen(pcl)*sizeof(char));
    strncpy(pclas, pcl, strlen(pcl)); 
    char pnu[] = {'n','\0'};
    char* pnum = (char*)malloc(strlen(pnu)*sizeof(char));
    strncpy(pnum, pnu, strlen(pnu)); 

    EXPECT_EQ( *(pname), *(temp[0]->name));
    EXPECT_EQ( *(pclas), *(temp[0]->product_class));
    EXPECT_EQ( *(pnum), *(temp[0]->number));

    char pn1[] = {'a','\0'};
    char* pname1 = (char*)malloc(strlen(pn1)*sizeof(char));
    strncpy(pname1, pn1, strlen(pn1)); 
    char pcl1[] = {'c','\0'};
    char* pclas1 = (char*)malloc(strlen(pcl1)*sizeof(char));
    strncpy(pclas1, pcl1, strlen(pcl1)); 
    char pnu1[] = {'n','\0'};
    char* pnum1 = (char*)malloc(strlen(pnu1)*sizeof(char));
    strncpy(pnum1, pnu1, strlen(pnu1)); 

    EXPECT_EQ( *(pname1), *(temp[1]->name));
    EXPECT_EQ( *(pclas1), *(temp[1]->product_class));
    EXPECT_EQ( *(pnum1), *(temp[1]->number));

    free(pname);
    free(pclas);
    free(pnum);

    free(pname1);
    free(pclas1);
    free(pnum1);

    for (size_t j = 0; j < pi[0]; j++)
    {

        free_product(temp[j]);
        free(temp[j]);
    }
    free(pi);
    free(temp);

    fclose(stdinn);
}

TEST(innput, semi_right_data) {
    char input[] = {'n','\n','c','\n','n','\n','1','.','0','2','.','2','0','2','2','\n','\n','a','\n','@','\n','n','\n','1','.','0','2','.','2','0','2','2','\n','\n','\n'};
    FILE* stdinn;
    stdinn = fmemopen(input, strlen(input), "r");
    

    size_t* pi = (size_t*)malloc(sizeof(size_t));
    Product** temp = innput(stdinn,pi);
    


    char pn[] = {'n','\0'};
    char* pname = (char*)malloc(strlen(pn)*sizeof(char));
    strncpy(pname, pn, strlen(pn)); 
    char pcl[] = {'c','\0'};
    char* pclas = (char*)malloc(strlen(pcl)*sizeof(char));
    strncpy(pclas, pcl, strlen(pcl)); 
    char pnu[] = {'n','\0'};
    char* pnum = (char*)malloc(strlen(pnu)*sizeof(char));
    strncpy(pnum, pnu, strlen(pnu)); 

    EXPECT_EQ( *(pname), *(temp[0]->name));
    EXPECT_EQ( *(pclas), *(temp[0]->product_class));
    EXPECT_EQ( *(pnum), *(temp[0]->number));


    EXPECT_EQ( NULL, temp[1]);

    free(pname);
    free(pclas);
    free(pnum);

    for (size_t j = 0; j < pi[0]; j++)
    {

        free_product(temp[j]);
        free(temp[j]);
    }
    free(pi);
    free(temp);

    fclose(stdinn);
}

TEST(print_data, rihgt) {
    
    FILE* stdinn = tmpfile();
    
    
    size_t* temp = (size_t*)malloc(3*sizeof(size_t));
    temp[0] = 1;
    temp[1] = 2;
    temp[2] = 2022;
    print_data(stdinn, temp);

    fseek(stdinn,0,SEEK_SET);

    size_t* p_temp = get_data(stdinn);
    EXPECT_EQ( 1, p_temp[0]);
    EXPECT_EQ( 2, p_temp[1]);
    EXPECT_EQ( 2022, p_temp[2]);

    free(p_temp);
    free(temp);
}

TEST(print_product, right) {
    
    FILE* stdinn = tmpfile();
    
    
    Product* p_temp = (Product*)malloc(sizeof(Product));
    set_ptr_null(p_temp);
    p_temp->name = (char*)malloc(2*sizeof(char));
    p_temp->name[0] = 'n';
    p_temp->name[1] = '\0';
    p_temp->product_class = (char*)malloc(2*sizeof(char));
    p_temp->product_class[0] = 'c';
    p_temp->product_class[1] = '\0';
    p_temp->number = (char*)malloc(2*sizeof(char));
    p_temp->number[0] = '1';
    p_temp->number[1] = '\0';
    p_temp->install_data = (size_t*)malloc(3*sizeof(size_t));
    p_temp->install_data[0] = 10;
    p_temp->install_data[1] = 2;
    p_temp->install_data[2] = 2022;

    print_product(stdinn,p_temp);
    fseek(stdinn,0,SEEK_SET);
    Product* temp = (Product*)malloc(sizeof(Product));
    get_product(temp,stdinn);


    char pn[] = {'n','\0'};
    char* pname = (char*)malloc(strlen(pn)*sizeof(char));
    strncpy(pname, pn, strlen(pn)); 
    char pcl[] = {'c','\0'};
    char* pclas = (char*)malloc(strlen(pcl)*sizeof(char));
    strncpy(pclas, pcl, strlen(pcl)); 
    char pnu[] = {'1','\0'};
    char* pnum = (char*)malloc(strlen(pnu)*sizeof(char));
    strncpy(pnum, pnu, strlen(pnu)); 

    EXPECT_EQ( *(pname), *(temp->name));
    EXPECT_EQ( *(pclas), *(temp->product_class));
    EXPECT_EQ( *(pnum), *(temp->number));

    free(pname);
    free(pclas);
    free(pnum);

    free_product(p_temp);
    free(p_temp);

    free_product(temp);
    free(temp);
    
}

TEST(print_products, alphabet_sorted_print) {
    
    FILE* stdinn = tmpfile();

    Product** p_temp = (Product**)malloc(2*sizeof(Product*));
    p_temp[0] = (Product*)malloc(sizeof(Product));
    set_ptr_null(p_temp[0]);
    p_temp[0]->name = (char*)malloc(sizeof("n"));
    p_temp[0]->name[0] = 'n';
    p_temp[0]->name[1] = '\0';
    p_temp[0]->product_class = (char*)malloc(sizeof("c"));
    p_temp[0]->product_class[0] = 'c';
    p_temp[0]->product_class[1] = '\0';
    p_temp[0]->number = (char*)malloc(sizeof("1"));
    p_temp[0]->number[0] = '1';
    p_temp[0]->number[1] = '\0';
    p_temp[0]->install_data = (size_t*)malloc(3*sizeof(size_t));
    p_temp[0]->install_data[0] = 10;
    p_temp[0]->install_data[1] = 11;
    p_temp[0]->install_data[2] = 2022;
    p_temp[0]->update_data = NULL; 


    p_temp[1] = (Product*)malloc(sizeof(Product));
    set_ptr_null(p_temp[1]);
    p_temp[1]->name = (char*)malloc(sizeof("a"));
    p_temp[1]->name[0] = 'a';
    p_temp[1]->name[1] = '\0';
    p_temp[1]->product_class = (char*)malloc(sizeof("c"));
    p_temp[1]->product_class[0] = 'c';
    p_temp[1]->product_class[1] = '\0';
    p_temp[1]->number = (char*)malloc(sizeof("1"));
    p_temp[1]->number[0] = '1';
    p_temp[1]->number[1] = '\0';
    p_temp[1]->install_data = (size_t*)malloc(3*sizeof(size_t));
    p_temp[1]->install_data[0] = 10;
    p_temp[1]->install_data[1] = 11;
    p_temp[1]->install_data[2] = 2022;
    p_temp[1]->update_data = NULL;

    
    print_products(p_temp, 2 ,stdinn);
    
    fseek(stdinn,0,SEEK_SET);

    size_t* pi = (size_t*)malloc(sizeof(size_t));
    Product** temp = innput(stdinn,pi);
    char pn[] = {'a','\0'};
    char* pname = (char*)malloc(strlen(pn)*sizeof(char));
    strncpy(pname, pn, strlen(pn)); 
    char pcl[] = {'c','\0'};
    char* pclas = (char*)malloc(strlen(pcl)*sizeof(char));
    strncpy(pclas, pcl, strlen(pcl)); 
    char pnu[] = {'1','\0'};
    char* pnum = (char*)malloc(strlen(pnu)*sizeof(char));
    strncpy(pnum, pnu, strlen(pnu)); 

    EXPECT_EQ( *(pname), *(temp[0]->name));
    EXPECT_EQ( *(pclas), *(temp[0]->product_class));
    EXPECT_EQ( *(pnum), *(temp[0]->number));
    EXPECT_EQ(10, temp[0]->install_data[0]);

    char pn1[] = {'n','\0'};
    char* pname1 = (char*)malloc(strlen(pn1)*sizeof(char));
    strncpy(pname1, pn1, strlen(pn1)); 
    char pcl1[] = {'c','\0'};
    char* pclas1 = (char*)malloc(strlen(pcl1)*sizeof(char));
    strncpy(pclas1, pcl1, strlen(pcl1)); 
    char pnu1[] = {'1','\0'};
    char* pnum1 = (char*)malloc(strlen(pnu1)*sizeof(char));
    strncpy(pnum1, pnu1, strlen(pnu1)); 

    EXPECT_EQ( *(pname1), *(temp[1]->name));
    EXPECT_EQ( *(pclas1), *(temp[1]->product_class));
    EXPECT_EQ( *(pnum1), *(temp[1]->number));

    free(pname);
    free(pclas);
    free(pnum);

    free(pname1);
    free(pclas1);
    free(pnum1);

    for (size_t j = 0; j < 2; j++)
    {

        free_product(p_temp[j]);
        free(p_temp[j]);
    }
    free(p_temp);


    for (size_t j = 0; j < pi[0]; j++)
    {

        free_product(temp[j]);
        free(temp[j]);
    }
    free(pi);
    free(temp);

    
}


TEST(my_out, alphabet_sorted_print_one_class) {
    
    FILE* stdinn = tmpfile();

    Product** p_temp = (Product**)malloc(3*sizeof(Product*));
    p_temp[0] = (Product*)malloc(sizeof(Product));
    set_ptr_null(p_temp[0]);
    p_temp[0]->name = (char*)malloc(sizeof("n"));
    p_temp[0]->name[0] = 'n';
    p_temp[0]->name[1] = '\0';
    p_temp[0]->product_class = (char*)malloc(sizeof("b"));
    p_temp[0]->product_class[0] = 'b';
    p_temp[0]->product_class[1] = '\0';
    p_temp[0]->number = (char*)malloc(sizeof("1"));
    p_temp[0]->number[0] = '1';
    p_temp[0]->number[1] = '\0';
    p_temp[0]->install_data = (size_t*)malloc(3*sizeof(size_t));
    p_temp[0]->install_data[0] = 10;
    p_temp[0]->install_data[1] = 11;
    p_temp[0]->install_data[2] = 2022;
    p_temp[0]->update_data = NULL; 


    p_temp[1] = (Product*)malloc(sizeof(Product));
    set_ptr_null(p_temp[1]);
    p_temp[1]->name = (char*)malloc(sizeof("a"));
    p_temp[1]->name[0] = 'a';
    p_temp[1]->name[1] = '\0';
    p_temp[1]->product_class = (char*)malloc(sizeof("c"));
    p_temp[1]->product_class[0] = 'c';
    p_temp[1]->product_class[1] = '\0';
    p_temp[1]->number = (char*)malloc(sizeof("1"));
    p_temp[1]->number[0] = '1';
    p_temp[1]->number[1] = '\0';
    p_temp[1]->install_data = (size_t*)malloc(3*sizeof(size_t));
    p_temp[1]->install_data[0] = 10;
    p_temp[1]->install_data[1] = 11;
    p_temp[1]->install_data[2] = 2022;
    p_temp[1]->update_data = NULL;


    p_temp[2] = (Product*)malloc(sizeof(Product));
    set_ptr_null(p_temp[2]);
    p_temp[2]->name = (char*)malloc(sizeof("d"));
    p_temp[2]->name[0] = 'd';
    p_temp[2]->name[1] = '\0';
    p_temp[2]->product_class = (char*)malloc(sizeof("b"));
    p_temp[2]->product_class[0] = 'b';
    p_temp[2]->product_class[1] = '\0';
    p_temp[2]->number = (char*)malloc(sizeof("1"));
    p_temp[2]->number[0] = '1';
    p_temp[2]->number[1] = '\0';
    p_temp[2]->install_data = (size_t*)malloc(3*sizeof(size_t));
    p_temp[2]->install_data[0] = 10;
    p_temp[2]->install_data[1] = 11;
    p_temp[2]->install_data[2] = 2022;
    p_temp[2]->update_data = NULL;

    
    my_out(p_temp, 3 ,stdinn);
    
    fseek(stdinn,0,SEEK_SET);

    size_t* pi = (size_t*)malloc(sizeof(size_t));
    Product** temp = innput(stdinn,pi);
    char pn[] = {'d','\0'};
    char* pname = (char*)malloc(strlen(pn)*sizeof(char));
    strncpy(pname, pn, strlen(pn)); 
    char pcl[] = {'b','\0'};
    char* pclas = (char*)malloc(strlen(pcl)*sizeof(char));
    strncpy(pclas, pcl, strlen(pcl)); 
    char pnu[] = {'1','\0'};
    char* pnum = (char*)malloc(strlen(pnu)*sizeof(char));
    strncpy(pnum, pnu, strlen(pnu)); 

    EXPECT_EQ( *(pname), *(temp[0]->name));
    EXPECT_EQ( *(pclas), *(temp[0]->product_class));
    EXPECT_EQ( *(pnum), *(temp[0]->number));
    EXPECT_EQ(10, temp[0]->install_data[0]);

    char pn1[] = {'n','\0'};
    char* pname1 = (char*)malloc(strlen(pn1)*sizeof(char));
    strncpy(pname1, pn1, strlen(pn1)); 
    char pcl1[] = {'b','\0'};
    char* pclas1 = (char*)malloc(strlen(pcl1)*sizeof(char));
    strncpy(pclas1, pcl1, strlen(pcl1)); 
    char pnu1[] = {'1','\0'};
    char* pnum1 = (char*)malloc(strlen(pnu1)*sizeof(char));
    strncpy(pnum1, pnu1, strlen(pnu1)); 

    EXPECT_EQ( *(pname1), *(temp[1]->name));
    EXPECT_EQ( *(pclas1), *(temp[1]->product_class));
    EXPECT_EQ( *(pnum1), *(temp[1]->number));

    char pn2[] = {'a','\0'};
    char* pname2 = (char*)malloc(strlen(pn2)*sizeof(char));
    strncpy(pname2, pn2, strlen(pn2)); 
    char pcl2[] = {'c','\0'};
    char* pclas2 = (char*)malloc(strlen(pcl2)*sizeof(char));
    strncpy(pclas2, pcl2, strlen(pcl2)); 
    char pnu2[] = {'1','\0'};
    char* pnum2 = (char*)malloc(strlen(pnu2)*sizeof(char));
    strncpy(pnum2, pnu2, strlen(pnu2)); 

    EXPECT_EQ( *(pname2), *(temp[2]->name));
    EXPECT_EQ( *(pclas2), *(temp[2]->product_class));
    EXPECT_EQ( *(pnum2), *(temp[2]->number));

    free(pname);
    free(pclas);
    free(pnum);

    free(pname1);
    free(pclas1);
    free(pnum1);

    free(pname2);
    free(pclas2);
    free(pnum2);

    for (size_t j = 0; j < 3; j++)
    {

        free_product(p_temp[j]);
        free(p_temp[j]);
    }
    free(p_temp);


    for (size_t j = 0; j < pi[0]; j++)
    {

        free_product(temp[j]);
        free(temp[j]);
    }
    free(pi);
    free(temp);

    
}