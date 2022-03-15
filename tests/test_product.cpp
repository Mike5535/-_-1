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

TEST(get_data, rihgt_data) {
    char input[] = {'N','\n','C','l','a','s',\n','n','u','m','1',\n','1','.','0','2','.','2','0','2','2','\n'};
    FILE* stdinn;
    stdinn = fmemopen(input, strlen(input), "r");
    
    Product* temp = NULL;
    get_product(temp,stdinn);

    char* pname = (char*)malloc(strlen("N")*sizeof(char));
    strncpy(pname, "N", strlen("N")); 
    char* pclas = (char*)malloc(strlen("Clas")*sizeof(char));
    strncpy(pclas, "Clas", strlen("Clas")); 
    char* pnum = (char*)malloc(strlen("num1")*sizeof(char));
    strncpy(pnum, "num1", strlen("num1")); 

    EXPECT_EQ( *(pname)), temp->name);
    EXPECT_EQ( "Clas", temp->product_class);
    EXPECT_EQ( "num1", temp->number);

    
    fclose(stdinn);
}