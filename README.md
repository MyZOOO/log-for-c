# Log for C

基于C23的日志库，支持自动类型识别、格式化输出、颜色和日志等级

## 功能说明

使用C11的 `_Generic`特性实现类型自动识别和格式化输出

### log() - 基础日志输出

自动判断传入参数类型并输出，支持格式化字符串

**支持的参数类型：**

- `int` - 整数
- `long` - 长整数
- `double` - 双精度浮点数
- `float` - 单精度浮点数
- `char*` / `const char*` - 字符串
- `wchar_t*` / `const wchar_t*` - 宽字符串
- `char` - 字符

> **注意：** C语言中字符字面量（如 `'A'`）的类型是 `int`，会被当作整数打印。如需打印字符，请使用 `char`类型变量或显式转换 `(char)'A'`

**使用方式：**

```c
log(value)                    // 单个值输出
log(format, arg1)             // 一个占位符
log(format, arg1, arg2)       // 两个占位符
...                           // 最多支持10个占位符
log(format, arg1, ..., arg10) // 十个占位符
```

格式化字符串使用 `{}`作为占位符，会自动替换为对应参数的值。支持最多10个格式化变量参数

### clog() - 颜色输出

输出带颜色的日志信息

**参数：**

- `color` (string) - 颜色名称
- `message` - 要输出的内容（支持所有log()支持的类型）

**支持的颜色：**
`red`, `green`, `yellow`, `blue`, `magenta`, `cyan`, `white`, `gray`

### 日志等级函数

带时间戳和颜色的日志等级输出

**logerr(message)** - 错误日志，红色输出，格式：`[时间 ERROR] 消息`

**logok(message)** - 成功日志，绿色输出，格式：`[时间 OK] 消息`

**loginfo(message)** - 信息日志，青色输出，格式：`[时间 INFO] 消息`

**logwarn(message)** - 警告日志，黄色输出，格式：`[时间 WARN] 消息`

**参数：**

- `message` - 要输出的消息（支持所有log()支持的类型）

## 使用

```c
#include "log.h"

int main() {
    int i = 18;
    double f = 1.75;
    log("hello");
    log(i);
    log(f);
    char name[] = "小明";
    log("他的名字是{}年龄是{}岁, 身高是{}米，他的身份是{}，他最近的考试成绩是{}", name, i, f, L"大学生", (char)'A');
    clog("red", "world");
    logerr("MySQL连接失败");
    logok("MySQL连接成功");
    loginfo("已插入数据");
    logwarn("测试失败");
    return 0;
}
```

## 编译

```bash
gcc -std=c2x -o main test.c log.c
```

> 推荐GCC 13+或其他支持C23标准的编译器，其他版本未测试，可行性不明
