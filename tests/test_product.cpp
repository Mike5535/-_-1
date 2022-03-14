#include <gtest/gtest.h>
#include <stdio.h>
extern "C" {
    #include "input.h"
    #include "output.h"
}



TEST(chek_string, WrongFormat) {
    EXPECT_EQ(false, chek_string("abcd",false));
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
    if (stdinn == NULL) printf ("error\n");
    
    
    

    char* p = (char*)malloc(strlen(input)*sizeof(char));
    strncpy(p, input, strlen(input));    
    
    char* result = get_string(stdinn,' ');
    
    EXPECT_EQ(*(p), *(result));
    
    free(result)
    free(p);
    fclose(stdinn);
}