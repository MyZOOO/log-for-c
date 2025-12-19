#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>

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
static inline void _print_uint(unsigned int x) { printf("%u", x); }
static inline void _print_short(short x) { printf("%hd", x); }
static inline void _print_ushort(unsigned short x) { printf("%hu", x); }
static inline void _print_long(long x) { printf("%ld", x); }
static inline void _print_ulong(unsigned long x) { printf("%lu", x); }
static inline void _print_long_long(long long x) { printf("%lld", x); }
static inline void _print_ulong_long(unsigned long long x) { printf("%llu", x); }
static inline void _print_double(double x) { printf("%.2f", x); }
static inline void _print_long_double(long double x) { printf("%.2Lf", x); }
static inline void _print_str(const char* x) { printf("%s", x); }
static inline void _print_char(int x) { printf("%c", x); }
static inline void _print_bool(_Bool x) { printf(x ? "true" : "false"); }
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
    _Bool: _print_bool, \
    short: _print_short, \
    unsigned short: _print_ushort, \
    int: _print_int, \
    unsigned int: _print_uint, \
    long: _print_long, \
    unsigned long: _print_ulong, \
    long long: _print_long_long, \
    unsigned long long: _print_ulong_long, \
    double: _print_double, \
    float: _print_double, \
    long double: _print_long_double, \
    signed char: _print_char, \
    unsigned char: _print_char, \
    char: _print_char, \
    char*: _print_str, \
    const char*: _print_str, \
    wchar_t*: _print_wstr, \
    const wchar_t*: _print_wstr \
)(x)

// log函数重载 - 单参数
#define _log_1(x) do { PRINT_VALUE(x); printf("\n"); } while(0)

// 通用格式化分发（fmt + 0~10 个参数）
#define _fmt_0(fmt) do { printf("%s\n", (fmt)); } while(0)
#define _GET_FMT_ARG(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,NAME,...) NAME
#define _fmt_print(...) _GET_FMT_ARG(__VA_ARGS__, \
    _log_fmt_10, _log_fmt_9, _log_fmt_8, _log_fmt_7, _log_fmt_6, \
    _log_fmt_5, _log_fmt_4, _log_fmt_3, _log_fmt_2, _log_fmt_1, _fmt_0)(__VA_ARGS__)

// log函数重载 - 格式化字符串 + 一个参数
#define _log_fmt_1(fmt, a) do { \
    const char* _p = (fmt); \
    int _done = 0; \
    while (*_p) { \
        if (*_p == '{' && *(_p+1) == '}' && !_done) { \
            PRINT_VALUE(a); \
            _done = 1; \
            _p += 2; \
        } else { \
            putchar(*_p); \
            _p++; \
        } \
    } \
    printf("\n"); \
} while(0)

// log函数重载 - 格式化字符串 + 两个参数
#define _log_fmt_2(fmt, a, b) do { \
    const char* _p = (fmt); \
    int _done = 0; \
    while (*_p) { \
        if (*_p == '{' && *(_p+1) == '}') { \
            if (_done == 0) { PRINT_VALUE(a); _done = 1; } \
            else if (_done == 1) { PRINT_VALUE(b); _done = 2; } \
            _p += 2; \
        } else { \
            putchar(*_p); \
            _p++; \
        } \
    } \
    printf("\n"); \
} while(0)

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
    _log_fmt_5, _log_fmt_4, _log_fmt_3, _log_fmt_2, _log_fmt_1, _log_1)(__VA_ARGS__)

// 颜色log
#define clog(color, msg) do { \
    printf("%s", get_color_code(color)); \
    PRINT_VALUE(msg); \
    printf("%s\n", COLOR_RESET); \
} while(0)

// 颜色log（格式化）
#define clog_f(color, ...) do { \
    printf("%s", get_color_code(color)); \
    _fmt_print(__VA_ARGS__); \
    printf("%s", COLOR_RESET); \
} while(0)

// 日志等级宏
#define logerr(msg) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s ERROR]%s ", COLOR_RED, time_str, COLOR_RESET); \
    PRINT_VALUE(msg); \
    printf("\n"); \
} while(0)

#define logerr_f(...) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s ERROR]%s ", COLOR_RED, time_str, COLOR_RESET); \
    _fmt_print(__VA_ARGS__); \
} while(0)

#define logok(msg) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s OK]%s ", COLOR_GREEN, time_str, COLOR_RESET); \
    PRINT_VALUE(msg); \
    printf("\n"); \
} while(0)

#define logok_f(...) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s OK]%s ", COLOR_GREEN, time_str, COLOR_RESET); \
    _fmt_print(__VA_ARGS__); \
} while(0)

#define loginfo(msg) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s INFO]%s ", COLOR_CYAN, time_str, COLOR_RESET); \
    PRINT_VALUE(msg); \
    printf("\n"); \
} while(0)

#define loginfo_f(...) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s INFO]%s ", COLOR_CYAN, time_str, COLOR_RESET); \
    _fmt_print(__VA_ARGS__); \
} while(0)

#define logwarn(msg) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s WARN]%s ", COLOR_YELLOW, time_str, COLOR_RESET); \
    PRINT_VALUE(msg); \
    printf("\n"); \
} while(0)

#define logwarn_f(...) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s WARN]%s ", COLOR_YELLOW, time_str, COLOR_RESET); \
    _fmt_print(__VA_ARGS__); \
} while(0)

#define logdebug(msg) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s DEBUG]%s ", COLOR_GRAY, time_str, COLOR_RESET); \
    PRINT_VALUE(msg); \
    printf("\n"); \
} while(0)

#define logdebug_f(...) do { \
    char time_str[64]; \
    get_time_string(time_str, sizeof(time_str)); \
    printf("%s[%s DEBUG]%s ", COLOR_GRAY, time_str, COLOR_RESET); \
    _fmt_print(__VA_ARGS__); \
} while(0)

#endif
