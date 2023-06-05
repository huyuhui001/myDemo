#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// 定义结构体类型用于存储收支信息
struct Transaction
{
    int sequenceNumber;
    string date;
    string description;
    double amount;
    double balance;
    string currency;
    bool isIncome;
};

// 函数原型
void showMainMenu();
void addIncome(vector<Transaction> &transactions);
void addExpense(vector<Transaction> &transactions);
void showTransactionDetails(const vector<Transaction> &transactions);
void showMonthlySummary(const vector<Transaction> &transactions);
void showYearlySummary(const vector<Transaction> &transactions);
void writeToFile(const vector<Transaction> &transactions);
void readFromFile(vector<Transaction> &transactions);

int main()
{
    vector<Transaction> transactions;

    // 读取文件中的数据
    readFromFile(transactions);

    // 主循环，显示主操作界面
    int choice = 0;
    while (choice != 7)
    {
        showMainMenu();
        cin >> choice;
        cin.ignore(); // 忽略输入缓冲区中的换行符

        switch (choice)
        {
        case 1:
            addIncome(transactions);
            break;
        case 2:
            addExpense(transactions);
            break;
        case 3:
            showTransactionDetails(transactions);
            break;
        case 4:
            showMonthlySummary(transactions);
            break;
        case 5:
            showYearlySummary(transactions);
            break;
        case 6:
            writeToFile(transactions);
            break;
        case 7:
            writeToFile(transactions);
            cout << "程序已退出。" << endl;
            break;
        default:
            cout << "无效的选择，请重新输入。" << endl;
            break;
        }
    }

    return 0;
}

// 显示主操作界面
void showMainMenu()
{
    cout << "个人收支管理" << endl;
    cout << "1. 收入功能" << endl;
    cout << "2. 支出功能" << endl;
    cout << "3. 明细表" << endl;
    cout << "4. 查询与统计（按月）" << endl;
    cout << "5. 查询与统计（按年）" << endl;
    cout << "6. 写入文件" << endl;
    cout << "7. 退出程序" << endl;
    cout << "请选择操作：";
}

// 添加收入
void addIncome(vector<Transaction> &transactions)
{
    Transaction newTransaction;

    cout << "请输入收入信息：" << endl;
    cout << "顺序号：";
    cin >> newTransaction.sequenceNumber;
    cout << "日期：";
    cin >> newTransaction.date;
    cin.ignore(); // 忽略输入缓冲区中的换行符
    cout << "摘要：";
    getline(cin, newTransaction.description);
    cout << "金额：";
    cin >> newTransaction.amount;
    cout << "余额：";
    cin >> newTransaction.balance;
    cout << "币种：";
    cin >> newTransaction.currency;
    newTransaction.isIncome = true;

    transactions.push_back(newTransaction);

    cout << "收入信息添加成功！" << endl;
}

// 添加支出
void addExpense(vector<Transaction> &transactions)
{
    Transaction newTransaction;

    cout << "请输入支出信息：" << endl;
    cout << "顺序号：";
    cin >> newTransaction.sequenceNumber;
    cout << "日期：";
    cin >> newTransaction.date;
    cin.ignore(); // 忽略输入缓冲区中的换行符
    cout << "摘要：";
    getline(cin, newTransaction.description);
    cout << "金额：";
    cin >> newTransaction.amount;
    cout << "余额：";
    cin >> newTransaction.balance;
    cout << "币种：";
    cin >> newTransaction.currency;
    newTransaction.isIncome = false;

    transactions.push_back(newTransaction);

    cout << "支出信息添加成功！" << endl;
}

// 显示明细表
void showTransactionDetails(const vector<Transaction> &transactions)
{
    cout << "收支明细表：" << endl;

    for (const Transaction &transaction : transactions)
    {
        cout << "顺序号：" << transaction.sequenceNumber << endl;
        cout << "日期：" << transaction.date << endl;
        cout << "摘要：" << transaction.description << endl;
        cout << "金额：" << transaction.amount << endl;
        cout << "余额：" << transaction.balance << endl;
        cout << "币种：" << transaction.currency << endl;
        cout << "类型：" << (transaction.isIncome ? "收入" : "支出") << endl;
        cout << endl;
    }
}

// 按月查询与统计
void showMonthlySummary(const vector<Transaction> &transactions)
{
    string month;
    cout << "请输入要查询的月份(格式:YYYY-MM):";
    cin >> month;

    double totalIncome = 0.0;
    double totalExpense = 0.0;

    for (const Transaction &transaction : transactions)
    {
        if (transaction.date.substr(0, 7) == month)
        {
            if (transaction.isIncome)
            {
                totalIncome += transaction.amount;
            }
            else
            {
                totalExpense += transaction.amount;
            }
        }
    }

    cout << month << "月份的总收入为：" << totalIncome << endl;
    cout << month << "月份的总支出为：" << totalExpense << endl;
}

// 按年查询与统计
void showYearlySummary(const vector<Transaction> &transactions)
{
    string year;
    cout << "请输入要查询的年份(格式:YYYY):";
    cin >> year;

    double totalIncome = 0.0;
    double totalExpense = 0.0;

    for (const Transaction &transaction : transactions)
    {
        if (transaction.date.substr(0, 4) == year)
        {
            if (transaction.isIncome)
            {
                totalIncome += transaction.amount;
            }
            else
            {
                totalExpense += transaction.amount;
            }
        }
    }

    cout << year << "年的总收入为：" << totalIncome << endl;
    cout << year << "年的总支出为：" << totalExpense << endl;
}

// 将数据写入文件
void writeToFile(const vector<Transaction> &transactions)
{
    string filename;
    cout << "请输入文件名：";
    cin >> filename;

    ofstream outputFile(filename);

    if (outputFile.is_open())
    {
        for (const Transaction &transaction : transactions)
        {
            outputFile << transaction.sequenceNumber << ","
                       << transaction.date << ","
                       << transaction.description << ","
                       << transaction.amount << ","
                       << transaction.balance << ","
                       << transaction.currency << ","
                       << (transaction.isIncome ? "收入" : "支出") << endl;
        }

        cout << "数据已成功写入文件！" << endl;

        outputFile.close();
    }
    else
    {
        cout << "无法打开文件！" << endl;
    }
}

// 从文件中读取数据
void readFromFile(vector<Transaction> &transactions)
{
    string filename;
    cout << "请输入文件名：";
    cin >> filename;

    ifstream inputFile(filename);

    if (inputFile.is_open())
    {
        transactions.clear();

        string line;
        while (getline(inputFile, line))
        {
            Transaction transaction;

            size_t pos = 0;
            string token;
            int count = 0;

            while ((pos = line.find(",")) != string::npos)
            {
                token = line.substr(0, pos);

                switch (count)
                {
                case 0:
                    transaction.sequenceNumber = stoi(token);
                    break;
                case 1:
                    transaction.date = token;
                    break;
                case 2:
                    transaction.description = token;
                    break;
                case 3:
                    transaction.amount = stod(token);
                    break;
                case 4:
                    transaction.balance = stod(token);
                    break;
                case 5:
                    transaction.currency = token;
                    break;
                case 6:
                    transaction.isIncome = (token == "收入");
                    break;
                }

                line.erase(0, pos + 1);
                count++;
            }

            transactions.push_back(transaction);
        }

        cout << "数据已成功从文件中读取！" << endl;

        inputFile.close();
    }
    else
    {
        cout << "无法打开文件！" << endl;
    }
}
