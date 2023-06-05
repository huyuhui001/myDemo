// 用面向对象方法实现
// 编译命令：g++ -std=c++11 mgt_new.cpp -o mgt_new.exe
// 输出文件：mgt_new.txt
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

// 收支交易类
class Transaction
{
private:
    int sequence;
    string date;
    string description;
    double amount;
    double balance;
    string currency;
    bool isIncome;

public:
    Transaction(int sequence, const string &date, const string &description, double amount, double balance,
                const string &currency, bool isIncome)
        : sequence(sequence), date(date), description(description), amount(amount), balance(balance),
          currency(currency), isIncome(isIncome) {}

    int getSequence() const { return sequence; }
    const string &getDate() const { return date; }
    const string &getDescription() const { return description; }
    double getAmount() const { return amount; }
    double getBalance() const { return balance; }
    const string &getCurrency() const { return currency; }
    bool isIncomeTransaction() const { return isIncome; }
};

// 收支交易管理类
class TransactionManager
{
private:
    vector<Transaction> transactions;

public:
    void showMainMenu()
    {
        cout << "--------个人收支管理--------" << endl;
        cout << "1. 添加收入" << endl;
        cout << "2. 添加支出" << endl;
        cout << "3. 显示收支明细" << endl;
        cout << "4. 按月统计收支" << endl;
        cout << "5. 按年统计收支" << endl;
        cout << "6. 写入文件" << endl;
        cout << "7. 从文件读取" << endl;
        cout << "0. 退出程序" << endl;
        cout << "请输入操作编号：";
    }

    void addIncome(int sequence, const string &date, const string &description, double amount, double balance,
                   const string &currency)
    {
        Transaction transaction(sequence, date, description, amount, balance, currency, true);
        transactions.push_back(transaction);
    }

    void addExpense(int sequence, const string &date, const string &description, double amount, double balance,
                    const string &currency)
    {
        Transaction transaction(sequence, date, description, amount, balance, currency, false);
        transactions.push_back(transaction);
    }

    void addTransaction(int sequence, const string &date, const string &description, double amount, double balance, const string &currency, bool isIncome)
    {
        Transaction transaction(sequence, date, description, amount, balance, currency, isIncome);
        transactions.push_back(transaction);
    }

    void showTransactionDetails() const
    {
        if (transactions.empty())
        {
            cout << "暂无收支明细记录" << endl;
            return;
        }

        cout << "--------收支明细--------" << endl;
        for (const Transaction &transaction : transactions)
        {
            cout << "顺序号：" << transaction.getSequence() << endl;
            cout << "日期：" << transaction.getDate() << endl;
            cout << "摘要：" << transaction.getDescription() << endl;
            cout << "金额：" << transaction.getAmount() << endl;
            cout << "余额：" << transaction.getBalance() << endl;
            cout << "币种：" << transaction.getCurrency() << endl;
            cout << "类型：" << (transaction.isIncomeTransaction() ? "收入" : "支出") << endl;
            cout << "-----------------------" << endl;
        }
    }

    void showMonthlySummary() const
    {
        if (transactions.empty())
        {
            cout << "暂无收支明细记录" << endl;
            return;
        }

        map<string, pair<double, double>> monthlySummary;

        for (const Transaction &transaction : transactions)
        {
            string month = transaction.getDate().substr(0, 7);

            if (monthlySummary.find(month) == monthlySummary.end())
            {
                monthlySummary[month] = make_pair(0.0, 0.0);
            }

            if (transaction.isIncomeTransaction())
            {
                monthlySummary[month].first += transaction.getAmount();
            }
            else
            {
                monthlySummary[month].second += transaction.getAmount();
            }
        }

        cout << "--------按月统计收支--------" << endl;
        for (const auto &entry : monthlySummary)
        {
            const string &month = entry.first;
            double income = entry.second.first;
            double expense = entry.second.second;

            cout << "月份：" << month << endl;
            cout << "收入：" << income << endl;
            cout << "支出：" << expense << endl;
            cout << "-----------------------" << endl;
        }
    }

    void showYearlySummary() const
    {
        if (transactions.empty())
        {
            cout << "暂无收支明细记录" << endl;
            return;
        }

        map<string, pair<double, double>> yearlySummary;

        for (const Transaction &transaction : transactions)
        {
            string year = transaction.getDate().substr(0, 4);

            if (yearlySummary.find(year) == yearlySummary.end())
            {
                yearlySummary[year] = make_pair(0.0, 0.0);
            }

            if (transaction.isIncomeTransaction())
            {
                yearlySummary[year].first += transaction.getAmount();
            }
            else
            {
                yearlySummary[year].second += transaction.getAmount();
            }
        }

        cout << "--------按年统计收支--------" << endl;
        for (const auto &entry : yearlySummary)
        {
            const string &year = entry.first;
            double income = entry.second.first;
            double expense = entry.second.second;

            cout << "年份：" << year << endl;
            cout << "收入：" << income << endl;
            cout << "支出：" << expense << endl;
            cout << "-----------------------" << endl;
        }
    }

    void writeToFile(const string &filename) const
    {
        ofstream file(filename);

        if (!file)
        {
            cout << "无法打开文件：" << filename << endl;
            return;
        }

        for (const Transaction &transaction : transactions)
        {
            file << transaction.getSequence() << "," << transaction.getDate() << "," << transaction.getDescription()
                 << "," << transaction.getAmount() << "," << transaction.getBalance() << "," << transaction.getCurrency()
                 << "," << (transaction.isIncomeTransaction() ? "1" : "0") << endl;
        }

        file.close();

        cout << "数据已成功写入文件：" << filename << endl;
    }

    void readFromFile(const string &filename)
    {
        ifstream file(filename);

        if (!file)
        {
            cout << "无法打开文件：" << filename << endl;
            return;
        }

        transactions.clear();
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string sequenceStr, date, description, amountStr, balanceStr, currency, isIncomeStr;

            getline(ss, sequenceStr, ',');
            getline(ss, date, ',');
            getline(ss, description, ',');
            getline(ss, amountStr, ',');
            getline(ss, balanceStr, ',');
            getline(ss, currency, ',');
            getline(ss, isIncomeStr, ',');

            int sequence = stoi(sequenceStr);
            double amount = stod(amountStr);
            double balance = stod(balanceStr);
            bool isIncome = (isIncomeStr == "1");

            addTransaction(sequence, date, description, amount, balance, currency, isIncome);
        }

        file.close();

        cout << "从文件读取数据成功：" << filename << endl;
    }
};

int main()
{
    TransactionManager manager;
    int choice;

    do
    {
        manager.showMainMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // 添加收入
            int sequence;
            string date, description, currency;
            double amount, balance;
            cout << "请输入顺序号：";
            cin >> sequence;
            cout << "请输入日期：";
            cin >> date;
            cout << "请输入摘要：";
            cin.ignore();
            getline(cin, description);
            cout << "请输入金额：";
            cin >> amount;
            cout << "请输入余额：";
            cin >> balance;
            cout << "请输入币种：";
            cin >> currency;
            manager.addIncome(sequence, date, description, amount, balance, currency);
            break;
        }
        case 2:
        {
            // 添加支出
            int sequence;
            string date, description, currency;
            double amount, balance;
            cout << "请输入顺序号：";
            cin >> sequence;
            cout << "请输入日期：";
            cin >> date;
            cout << "请输入摘要：";
            cin.ignore();
            getline(cin, description);
            cout << "请输入金额：";
            cin >> amount;
            cout << "请输入余额：";
            cin >> balance;
            cout << "请输入币种：";
            cin >> currency;
            manager.addExpense(sequence, date, description, amount, balance, currency);
            break;
        }
        case 3:
            // 显示收支明细
            manager.showTransactionDetails();
            break;
        case 4:
            // 按月统计收支
            manager.showMonthlySummary();
            break;
        case 5:
            // 按年统计收支
            manager.showYearlySummary();
            break;
        case 6:
        {
            // 写入文件
            string filename;
            cout << "请输入文件名：";
            cin >> filename;
            manager.writeToFile(filename);
            break;
        }
        case 7:
        {
            // 从文件读取
            string filename;
            cout << "请输入文件名：";
            cin >> filename;
            manager.readFromFile(filename);
            break;
        }
        case 0:
            // 退出程序
            cout << "感谢使用个人收支管理程序！" << endl;
            break;
        default:
            cout << "无效的操作编号，请重新输入" << endl;
            break;
        }

        cout << endl;

    } while (choice != 0);

    return 0;
}
