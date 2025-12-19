# Log for C

基于C23的日志库，支持自动类型识别、格式化输出、颜色格式化输出和日志等级格式化输出

## 功能说明

使用C11的 `_Generic`特性实现类型自动识别和格式化输出

### log() - 基础日志输出

自动判断传入参数类型并输出，支持格式化字符串

**支持的参数类型：**

- `bool` - 布尔（要求编译器必须支持C23标准）
- `int` / `long` / `long long` - 整数
- `float` / `double` / `long double` - 浮点数
- `char` - 字符
- `char*` / `const char*` - 字符串
- `wchar_t*` / `const wchar_t*` - 宽字符串

> **注意：** C语言中字符字面量（如 `'A'`）的类型是 `int`，会被当作整数打印。如需打印字符，请使用 `char`类型变量或显式转换 `(char)'A'`

格式化字符串使用 `{}`作为占位符，会自动替换为对应参数的值。支持最多10个格式化变量参数

### clog() / clog_f() - 颜色输出 / 颜色格式化输出

输出带颜色的日志信息（支持格式化）

**参数：**

- `color` - 颜色名称
- `message` - 消息内容
- `format` - 格式化字符串（`clog_f`）

**支持的颜色：**
`red`, `green`, `yellow`, `blue`, `magenta`, `cyan`, `white`, `gray`

### 日志等级输出 / 日志等级格式化输出

带时间戳和颜色的分级日志

**无格式化版本：**

- `logerr(message)` - 错误日志（红色）
- `logok(message)` - 成功日志（绿色）
- `loginfo(message)` - 信息日志（青色）
- `logwarn(message)` - 警告日志（黄色）
- `logdebug(message)` - 调试日志（灰色）

**格式化版本：** `logerr_f()`、`logok_f()`、`loginfo_f()`、`logwarn_f()`、`logdebug_f()`（支持 `{}` 占位符）

格式：`[时间 LEVEL] 消息`

## 使用示例

```c
#include "log.h"

int main() {
    int age = 18;
    float height = 1.75;
    char name[] = "小明";
  
    log("hello");
    log(age);
    log(height);
    log(true);
  
    log("姓名: {}，年龄: {}岁，身高: {}米", name, age, height);
  
    clog("green", "成功");
    clog_f("red", "错误代码: {}", 404);
  
    logerr("MySQL连接失败");
    logok_f("用户 {} 登录成功", "admin");
    loginfo_f("处理了 {} 条记录", 100);
    logwarn_f("内存使用: {}%", 85.5);
    logdebug("调试信息");
  
    return 0;
}
```

## 编译

```bash
gcc -std=c23 -o main test.c log.c
```

> 推荐GCC 13+或其他支持C23标准的编译器，其他版本未测试，可行性不明
