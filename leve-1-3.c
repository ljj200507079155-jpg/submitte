#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define FILENAME "Makefile"

void trim_whitespace(char *str) {
    if (!str) return;

    int len = strlen(str);
    while (len > 0 && isspace((char)str[len - 1])) {
        len--;
    }
    str[len] = '\0';

    int i = 0;
    while (isspace((char)str[i])) {
        i++;
    }
    if (i > 0) {
        memmove(str, str + i, len - i + 1);
    }
}

int main() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("文件无法打开");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        trim_whitespace(line);

        if (strlen(line) == 0 || line[0] == '#') {
            continue;
        }

        if (line[0] == '\t') {
        } else {
            if (strchr(line, ':') == NULL) {
                fprintf(stderr, "Line%d: :Missing colon in target definition\n", line_number);
                fclose(file);
                return 1;
            }
        }
    }

    printf("Syntax check passed: No errors found in Makefile.\n");

    fclose(file);
    return 0;
}

//memmove 是把 str + i 位置的内容往前移动 i 个位置，len - i + 1 是为了把字符串结尾的 '\0' 也一起移动过去(一共移动的位数)
