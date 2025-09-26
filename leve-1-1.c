#include <stdio.h>
#include <string.h>
#include "help.c"


int main(int argc, char* argv[]){
    if(argc==1){
        printf("参数缺失，需要帮助请输入 --help\n");
        return 0;
    }
    for (int i = 1; i < argc; i++){
        if(strcmp(argv[i],"--vision")==0){
            printf("version 1.0.0\n");
        }else if(strcmp(argv[i],"--help")==0){
            help();
        }else{
            printf("格式错误，需要帮助请输入 --help: %s\n",argv[i]);
        }

    }
    
    return 0;
}