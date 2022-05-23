//
// Created by xjf on 5/23/22.
//

#include <iostream>
#include <string.h>
using namespace std;

void getMemory(char **p){

    *p = (char *) malloc(100);

}

void Test(void){

    char *str = NULL;
    getMemory(&str);
    strcpy(str, "hello world");
    cout<<str;
}

int main(){
    Test();
}