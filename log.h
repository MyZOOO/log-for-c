#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

// ANSI颜色代码
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"
#define COLOR_GRAY    "\033[90m"

// 辅助函数声明
const char* get_color_code(const char* color_name);
void get_time_string(char* buffer, size_t size);

// 内部打印函数
static inline void _print_int(int x) { printf("%d", x); }
static inline void _print_double(double x) { printf("%.2f", x); }
static inline void _print_str(const char* x) { printf("%s", x); }
static inline void _print_char(int x) { printf("%c", x); }
static inline void _print_wstr(const wchar_t* x) { 
    static int locale_set = 0;
    if (!locale_set) {
        setlocale(LC_ALL, "");
        locale_set = 1;
    }
    wprintf(L"%ls", x); 
}

// 类型自动打印（使用C23的_Generic）
#define PRINT_VALUE(x) _Generic((x), \
    int: _print_int, \
    long: _print_int, \
    double: _print_double, \
    float: _print_double, \
    char: _print_char, \
    char*: _print_str, \
    const char*: _print_str, \
    wchar_t*: _print_wstr, \
    const wchar_t*: _print_wstr \
)(x)

// log函数重载 - 单参数
static inline void _log_int(int x) {
    printf("%d\n", x);
}

static inline void _log_double(double x) {
    printf("%.2f\n", x);
}

static inline void _log_str(const char* x) {
    printf("%s\n", x);
}

// log函数重载 - 格式化字符串 + 一个参数
static inline void _log_fmt_int(const char* fmt, int b) {
    const char* p = fmt;
    int done = 0;
    while (*p) {
        if (*p == '{' && *(p+1) == '}' && !done) {
            printf("%d", b);
            done = 1;
            p += 2;
        } else {
            putchar(*p);
            p++;
        }
    }
    printf("\n");
}

// log函数重载 - 格式化字符串 + 两个参数
static inline void _log_fmt_2(const char* fmt, int b, double c) {
    const char* p = fmt;
    int done = 0;
    while (*p) {
        if (*p == '{' && *(p+1) == '}') {
            if (done == 0) {
                printf("%d", b);
                done = 1;
            } else if (done == 1) {
                printf("%.2f", c);
                done = 2;
            }
            p += 2;
        } else {
            putchar(*p);
            p++;
        }
    }
    printf("\n");
}

// 格式化字符串 + 三个参数
#define _log_fmt_3(fmt, a, b, c) do { \
    const char* _p = (fmt); \
    int _done = 0; \
    while (*_p) { \
        if (*_p == '{' && *(_p+1) == '}') { \
            if (_done == 0) { PRINT_VALUE(a); _done = 1; } \
            else if (_done == 1) { PRINT_VALUE(b); _done = 2; } \
            else if (_done == 2) { PRINT_VALUE(c); _done = 3; } \
            _p += 2; \
        } else { \
            putchar(*_p); \
            _p++; \
        } \
    } \
    printf("\n"); \
} while(0)

// 格式化字符串 + 四个参数
#define _log_fmt_4(fmt, a, b, c, d) do { \
    const char* _p = (fmt); \
    int _done = 0; \
    while (*_p) { \
        if (*_p == '{' && *(_p+1) == '}') { \
            if (_done == 0) { PRINT_VALUE(a); _done = 1; } \
            else if (_done == 1) { PRINT_VALUE(b); _done = 2; } \
            else if (_done == 2) { PRINT_VALUE(c); _done = 3; } \
            else if (_done == 3) { PRINT_VALUE(d); _done = 4; } \
            _p += 2; \
        } else { \
            putchar(*_p); \
            _p++; \
        } \
    } \
    printf("\n"); \
} while(0)

// 格式化字符串 + 五个参数
#define _log_fmt_5(fmt, a, b, c, d, e) do { \
    const char* _p = (fmt); \
    int _done = 0; \
    while (*_p) { \
        if (*_p == '{' && *(_p+1) == '}') { \
            if (_done == 0) { PRINT_VALUE(a); _done = 1; } \
            else if (_done == 1) { PRINT_VALUE(b); _done = 2; } \
            else if (_done == 2) { PRINT_VALUE(c); _done = 3; } \
            else if (_done == 3) { PRINT_VALUE(d); _done = 4; } \
            else if (_done == 4) { PRINT_VALUE(e); _done = 5; } \
            _p += 2; \
        } else { \
            putchar(*_p); \
            _p++; \
        } \
    } \
    printf("\n"); \
} while(0)

// 格式化字符串 + 六个参数
#define _log_fmt_6(fmt, a, b, c, d, e, f) do { \
    const char* _p = (fmt); \
    int _done = 0; \
    while (*_p) { \
        if (*_p == '{' && *(_p+1) == '}') { \
            if (_done == 0) { PRINT_VALUE(a); _done = 1; } \
            else if (_done == 1) { PRINT_VALUE(b); _done = 2; } \
            else if (_done == 2) { PRINT_VALUE(c); _done = 3; } \
            else if (_done == 3) { PRINT_VALUE(d); _done = 4; } \
            else if (_done == 4) { PRINT_VALUE(e); _done = 5; } \
            else if (_done == 5) { PRINT_VALUE(f); _done = 6; } \
            _p += 2; \
        } else { \
            putchar(*_p); \
            _p++; \
        } \
    } \
    printf("\n"); \
} while(0)

// 格式化字符串 + 七个参数
#define _log_fmt_7(fmt, a, b, c, d, e, f, g) do { \
    const char* _p = (fmt); \
    int _done = 0; \
    while (*_p) { \
        if (*_p == '{' && *(_p+1) == '}') { \
            if (_done == 0) { PRINT_VALUE(a); _done = 1; } \
            else if (_done == 1) { PRINT_VALUE(b); _done = 2; } \
            else if (_done == 2) { PRINT_VALUE(c); _done = 3; } \
            else if (_done == 3) { PRINT_VALUE(d); _done = 4; } \
            else if (_done == 4) { PRINT_VALUE(e); _done = 5; } \
            else if (_done == 5) { PRINT_VALUE(f); _done = 6; } \
            else if (_done == 6) { PRINT_VALUE(g); _done = 7; } \
            _p += 2; \
        } else { \
            putchar(*_p); \
            _p++; \
        } \
    } \
    printf("\n"); \
} while(0)

// 格式化字符串 + 八个参数
#define _log_fmt_8(fmt, a, b, c, d, e, f, g, h) do { \
    const char* _p = (fmt); \
    int _done = 0; \
    while (*_p) { \
        if (*_p == '{' && *(_p+1) == '}') { \
            if (_done == 0) { PRINT_VALUE(a); _done = 1; } \
            else if (_done == 1) { PRINT_VALUE(b); _done = 2; } \
            else if (_done == 2) { PRINT_VALUE(c); _done = 3; } \
            else if (_done == 3) { PRINT_VALUE(d); _done = 4; } \
            else if (_done == 4) { PRINT_VALUE(e); _done = 5; } \
            else if (_done == 5) { PRINT_VALUE(f); _done = 6; } \
            else if (_done == 6) { PRINT_VALUE(g); _done = 7; } \
            else if (_done == 7) { PRINT_VALUE(h); _done = 8; } \
            _p += 2; \
        } else { \
            putchar(*_p); \
            _p++; \
        } \
    } \
    printf("\n"); \
} while(0)

// 格式化字符串 + 九个参数
#define _log_fmt_9(fmt, a, b, c, d, e, f, g, h, i) do { \
    const char* _p = (fmt); \
    int _done = 0; \
    while (*_p) { \
        if (*_p == '{' && *(_p+1) == '}') { \
            if (_done == 0) { PRINT_VALUE(a); _done = 1; } \
            else if (_done == 1) { PRINT_VALUE(b); _done = 2; } \
            else if (_done == 2) { PRINT_VALUE(c); _done = 3; } \
            else if (_done == 3) { PRINT_VALUE(d); _done = 4; } \
            else if (_done == 4) { PRINT_VALUE(e); _done = 5; } \
            else if (_done == 5) { PRINT_VALUE(f); _done = 6; } \
            else if (_done == 6) { PRINT_VALUE(g); _done = 7; } \
            else if (_done == 7) { PRINT_VALUE(h); _done = 8; } \
            else if (_done == 8) { PRINT_VALUE(i); _done = 9; } \
            _p += 2; \
        } else { \
            putchar(*_p); \
            _p++; \
        } \
    } \
    printf("\n"); \
} while(0)

// 格式化字符串 + 十个参数
#define _log_fmt_10(fmt, a, b, c, d, e, f, g, h, i, j) do { \
    const char* _p = (fmt); \
    int _done = 0; \
    while (*_p) { \
        if (*_p == '{' && *(_p+1) == '}') { \
            if (_done == 0) { PRINT_VALUE(a); _done = 1; } \
            else if (_done == 1) { PRINT_VALUE(b); _done = 2; } \
            else if (_done == 2) { PRINT_VALUE(c); _done = 3; } \
            else if (_done == 3) { PRINT_VALUE(d); _done = 4; } \
            else if (_done == 4) { PRINT_VALUE(e); _done = 5; } \
            else if (_done == 5) { PRINT_VALUE(f); _done = 6; } \
            else if (_done == 6) { PRINT_VALUE(g); _done = 7; } \
            else if (_done == 7) { PRINT_VALUE(h); _done = 8; } \
            else if (_done == 8) { PRINT_VALUE(i); _done = 9; } \
            else if (_done == 9) { PRINT_VALUE(j); _done = 10; } \
            _p += 2; \
        } else { \
            putchar(*_p); \
            _p++; \
        } \
    } \
    printf("\n"); \
} while(0)

// 主log宏 - 支持最多11个参数（格式化字符串 + 10个变量）  
#define _GET_11TH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, N, ...) N

#define log(...) _GET_11TH_ARG(__VA_ARGS__, \
    _log_fmt_10, _log_fmt_9, _log_fmt_8, _log_fmt_7, _log_fmt_6, \
    _log_fmt_5, _log_fmt_4, _log_fmt_3, _log_2, _log_1, _log_1)(__VA_ARGS__)

#define _log_1(x) _Generic((x), \
    int: _log_int, \
    double: _log_double, \
    char*: _log_str, \
    const char*: _log_str \
)(x)

#define _log_2(a, b) _Generic((b), \
    int: _log_fmt_int \
)(a, b)

#define _log_3(a, b, c) _Generic((b), \
    int: _log_fmt_2 \
)(a, b, c)

// 颜色log
#define clog(color, msg) do { \
    printf("%s", get_color_code(color)); \
    PRINT_VALUE(msg); \
    printf("%s\n", COLOR_RESET); \
} while(0)

// 日志等级宏
#define logerr(msg) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s ERROR]%s ", COLOR_RED, time_str, COLOR_RESET); \
    PRINT_VALUE(msg); \
    printf("\n"); \
} while(0)

#define logok(msg) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s OK]%s ", COLOR_GREEN, time_str, COLOR_RESET); \
    PRINT_VALUE(msg); \
    printf("\n"); \
} while(0)

#define loginfo(msg) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s INFO]%s ", COLOR_CYAN, time_str, COLOR_RESET); \
    PRINT_VALUE(msg); \
    printf("\n"); \
} while(0)

#define logwarn(msg) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s WARN]%s ", COLOR_YELLOW, time_str, COLOR_RESET); \
    PRINT_VALUE(msg); \
    printf("\n"); \
} while(0)

#endif
