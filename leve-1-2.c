#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "clean.cpp" 

#define INPUT_FILE "Makefile"
#define OUTPUT_FILE "Minimake_cleared.mk"


#define BUFFER_SIZE 1024//缓冲区大小

int main(int argc, char* argv[]) {
    bool verbose_mode = false;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose_mode = true;
            break;
        }
    }

    FILE* input_file = fopen(INPUT_FILE, "r");
    if (input_file == NULL) {
        fprintf(stderr, "错误: 无法打开文件 '%s'. 请确保它存在于当前目录。\n", INPUT_FILE);
        return 1;
    }

    FILE* output_file = fopen(OUTPUT_FILE, "w");
    if (output_file == NULL) {
        fprintf(stderr, "错误: 无法创建文件 '%s'.\n", OUTPUT_FILE);
        fclose(input_file);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    
    while (fgets(buffer, BUFFER_SIZE, input_file) != NULL) {
        clean_line(buffer); 

        if (strlen(buffer) > 0) {
            fputs(buffer, output_file);
            fputc('\n', output_file); 
            if (verbose_mode) {
                printf("%s\n", buffer);
            }
        }
    }

    fclose(input_file);
    fclose(output_file);

    printf("\n文件预处理完成！\n");
    printf("清理后的内容已保存到 '%s' 文件中。\n", OUTPUT_FILE);

    return 0;
}
//strcmp strcmp(aoieue,aoieue) == 0(第三项加数字就是比两字符串前几位相等)
//isspace((unsigned char)line[len - 1])  //判断是否为空格
//strchr(line, '#')  //查找#在字符串中的位置 并返回该位置的指针
//FILE* input_file = fopen(INPUT_FILE, "r");  //打开文件 读模式 文件指针
//fgets(buffer, BUFFER_SIZE, input_file)  //从文件中读取一行到buffer中
//fputs(buffer, output_file);  //将buffer中的内容写入到output_file中
//fputc('\n', output_file); //fputs 不会自动添加换行符 需要手动添加
//fclose(input_file);  //关闭文件