#include "log.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// 获取颜色代码
const char* get_color_code(const char* color_name) {
    if (strcmp(color_name, "red") == 0) return COLOR_RED;
    if (strcmp(color_name, "green") == 0) return COLOR_GREEN;
    if (strcmp(color_name, "yellow") == 0) return COLOR_YELLOW;
    if (strcmp(color_name, "blue") == 0) return COLOR_BLUE;
    if (strcmp(color_name, "magenta") == 0) return COLOR_MAGENTA;
    if (strcmp(color_name, "cyan") == 0) return COLOR_CYAN;
    if (strcmp(color_name, "white") == 0) return COLOR_WHITE;
    if (strcmp(color_name, "gray") == 0) return COLOR_GRAY;
    return COLOR_RESET;
}

// 获取当前时间字符串
void get_time_string(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}
