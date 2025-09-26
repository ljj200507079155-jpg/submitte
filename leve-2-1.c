#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 32

typedef struct MakeRule {
    char target[MAX_NAME_LEN + 1];
    char* command;                  
    char* dependencies;             
    struct MakeRule* next;          
} MakeRule;

MakeRule* createRule(const char* target, const char* dependencies, const char* command) {
    MakeRule* newRule = (MakeRule*)malloc(sizeof(MakeRule));
    if (newRule == NULL) {
        perror("为 MakeRule 分配内存失败");
        return NULL;
    }

    if (strlen(target) > MAX_NAME_LEN) {
        fprintf(stderr, "错误：目标名称 '%s' 超过了最大长度 %d 个字符。\n", target, MAX_NAME_LEN);
        free(newRule);
        return NULL;
    }

    strcpy(newRule->target, target);
    newRule->dependencies = strdup(dependencies);
    newRule->command = strdup(command);
    newRule->next = NULL; 

    return newRule;
}

void parse_makefile_line(char* line, char* target, char* dependencies) {
    if (line == NULL || line[0] == '\0' || line[0] == '#') {
        return;
    }

    if (line[0] == '\t') {
        printf("  - 解析到命令: %s\n", line + 1); 
        return;
    }

    char* colon_pos = strstr(line, ":");
    if (colon_pos != NULL) {
        *colon_pos = '\0'; 
        
        strncpy(target, line, MAX_NAME_LEN);
        target[MAX_NAME_LEN] = '\0';
        strncpy(dependencies, colon_pos + 1, 255);
        dependencies[255] = '\0';
    }
}

char* get_command_fgets() {
    static char command[MAX_NAME_LEN + 1];
    
    printf("请输入命令: ");
    
    if (fgets(command, sizeof(command), stdin) == NULL) {
        return NULL;
    }
    
    command[strcspn(command, "\n")] = '\0';
    
    return command;
}
char* remove_substring(const char *str, const char *sub) {
    if (str == NULL) return NULL;
    if (sub == NULL) return strdup(str);
    
    size_t str_len = strlen(str);
    size_t sub_len = strlen(sub);
    
    char *result = (char *)malloc(str_len + 1);
    if (result == NULL) return NULL;
    
    const char *src = str;
    char *dst = result;
    const char *pos;
    
    while ((pos = strstr(src, sub)) != NULL) {
        size_t copy_len = pos - src;
        memcpy(dst, src, copy_len);
        dst += copy_len;
        src = pos + sub_len;
    }
    strcpy(dst, src);
    return result;
}

int main(int argc, char* argv[]){

    char* line = get_command_fgets();
    MakeRule* firstRule = createRule("app", "main.c utils.c", "gcc -o app main.c utils.c");
    char target[MAX_NAME_LEN + 1] = {0};
    char dependencies[256] = {0};
    for (int i = 0; i < argc; i++) {
        parse_makefile_line(line, target, dependencies);
        MakeRule* newRule = createRule(target, dependencies,"gcc -o app main.c utils.c" );
        if (newRule != NULL) {
            firstRule->next = newRule;
            newRule->next = NULL;
        }
        if (firstRule ->target == newRule ->target && firstRule ->dependencies == newRule ->dependencies) {
            printf("Line4: Duplicate target definition 'app'\n");
        }
        if (firstRule ->target == newRule ->target && firstRule ->dependencies != newRule ->dependencies) {
            char* reast_line = remove_substring(newRule ->dependencies, firstRule ->dependencies);
            printf("Invalid dependency '%s", reast_line);
        }
    }
    return 0;
}
