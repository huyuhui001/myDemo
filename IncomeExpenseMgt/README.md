# 个人收支管理系统详细设计

## 1. 课程设计目的和要求

本课程设计旨在通过使用 C++ 编程语言来设计和实现一个个人收支管理系统。主要目的和要求如下：

1. 巩固和加深对 C++ 语言课程的基本知识的理解和掌握。
2. 掌握 C++ 语言编程和程序调试的基本技能。
3. 利用 C++ 语言进行基本的软件设计。
4. 掌握书写程序设计说明文档的能力。
5. 提高运用 C++ 语言解决实际问题的能力。

## 2. 课程设计任务内容

本课程设计的任务是设计和实现一个个人收支管理系统，包括以下主要功能：

- 收入功能：添加收入信息，包括顺序号、日期、摘要、金额、余额和币种。
- 支出功能：添加支出信息，包括顺序号、日期、摘要、金额、余额和币种。
- 明细表：显示收支明细，包括顺序号、日期、摘要、金额、余额、币种和类型（收入或支出）。
- 查询与统计（按月）：按指定月份统计总收入和总支出。
- 查询与统计（按年）：按指定年份统计总收入和总支出。
- 写入文件：将查询与统计结果和当前数据（明细表）写入文件。
- 读取文件：从文件中读取已写入的数据并加载到内存中。

## 3. 详细设计说明

### 3.1 结构体定义

在代码中定义了一个名为 `Transaction` 的结构体类型，用于存储收支信息。结构体包含以下成员：

- `sequenceNumber`：顺序号，表示收支记录的编号。
- `date`：日期，表示收支记录的日期。
- `description`：摘要，表示收支记录的描述。
- `amount`：金额，表示收支记录的金额。
- `balance`：余额，表示收支记录的余额。
- `currency`：币种，表示收支记录的货币类型。
- `isIncome`：收入或支出标志，表示收支记录是收入还是支出。

### 3.2 主函数设计

主函数包含一个主循环，显示主操作界面，并根据用户的选择调用相应的功能函数。

### 3.3 功能函数设计

根据需求分析中的功能要求，设计了以下功能函数：

- `addIncome()`：用于添加收入信息。
- `addExpense()`：用于添加支出信息。
- `showTransactionDetails()`：用于显示收支明细表。
- `showMonthlySummary()`：用于按月查询与统计收支信息。
- `showYearlySummary()`：用于按年查询与统计收支信息。
- `writeToFile()`：用于将数据写入文件。
- `readFromFile()`：用于从文件中读取数据。

### 3.4 输入和输出设计

程序通过标准输入和输出流与用户进行交互。用户可以在命令行界面输入指定的操作选项和参数，程序会根据输入的内容进行相应的处理，并将结果输出到标准输出流中。

## 4. 软件使用说明

### 4.1 编译和执行

要编译和执行程序，按照以下步骤操作：

4.1.1. 确保已经安装了合适的 C++ 编译器（如 g++）并配置了开发环境。

4.1.2. 将代码保存到一个名为 `mgt.cpp` 的文件中。

4.1.3. 使用命令行界面进入保存 `mgt.cpp` 文件的目录。

4.1.4. 运行以下命令进行编译：

```bash
g++ -std=c++11 mgt.cpp -o mgt.exe
```

这将生成一个名为 `mgt.exe` 的可执行文件。

4.1.5. 运行以下命令来执行程序：

- 在 Windows 上：

```bash
mgt.exe
```

- 在 macOS 或 Linux 上：

```bash
./mgt.exe
```

程序执行时会首先要求读入外部保存文件，这里是mgt.txt文件，此程序使用此文件保存收支记录。

### 4.2 操作指南

在程序运行后，会显示主操作界面，根据提示进行相应的操作：

- 输入 `1`：添加收入信息。
- 输入 `2`：添加支出信息。
- 输入 `3`：显示收支明细表。
- 输入 `4`：按月查询与统计收支信息。
- 输入 `5`：按年查询与统计收支信息。
- 输入 `6`：将数据写入文件。
- 输入 `7`：从文件中读取数据。
- 输入 `0`：退出程序。

根据需要选择相应的操作选项，并按照提示输入参数。

## 5. 课程设计总结

通过完成本课程设计，学生能够巩固和加深对 C++ 语言的理解和掌握，掌握 C++ 语言编程和程序调试的基本技能，并通过实际设计和开发一个个人收支管理系统来提高运用 C++ 语言解决实际问题的能力。在设计过程中，学生需要进行需求分析、设计功能模块、定义合适的数据结构等步骤，同时还需要编写课程设计报告和整理源代码。

## 6. 附录

### 6.1 参考文献

- [C++ Reference](https://en.cppreference.com/)

### 6.2 程序清单

- `mgt.cpp`：包含完整的程序代码，实现了个人收支管理系统的各项功能。