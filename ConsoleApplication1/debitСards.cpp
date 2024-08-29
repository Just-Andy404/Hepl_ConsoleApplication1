#include <fstream>
#include "debitСards.h"
#include "SaveData.h"
#include <sstream>

using namespace std;

void DebitCard::addMoney(const Account& acc) {
    double Money = 0.0;
    std::cout << "How much money do you want to add: ";
    std::cin >> Money;
    std::cout << std::endl;

    // Путь к файлу
    std::string fileName = "data/" + acc.getUserAccount() + ".txt";

    // Чтение текущего баланса и истории из файла
    std::ifstream inFile(fileName);
    double currentBalance = 0.0;
    std::string fileContent;
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.find("Balance:") != std::string::npos) {
                currentBalance = std::stod(line.substr(line.find(":") + 1));
            }
            fileContent += line + "\n";
        }
        inFile.close();
    }
    else {
        std::cerr << "Unable to open file for reading." << std::endl;
        return;
    }

    // Обновление баланса
    _balance = currentBalance + Money;

    // Запись обновленного баланса в тот же файл, сохраняя историю
    std::ofstream outFile(fileName, std::ios::out | std::ios::trunc);
    if (outFile.is_open()) {
        std::string updatedFileContent;
        std::istringstream fileStream(fileContent);
        std::string line;
        while (std::getline(fileStream, line)) {
            if (line.find("Balance:") != std::string::npos) {
                line = "Balance: " + std::to_string(_balance);
            }
            updatedFileContent += line + "\n";
        }

        outFile << updatedFileContent;
        outFile.close();
        std::cout << "New balance saved successfully." << std::endl;
    }
    else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}




void DebitCard::payment(const Account& acc) {
    double amount = 0.0;
    string date;
    string category;

    cout << "Enter the amount you spent: ";
    cin >> amount;

    cout << "Enter the date (format YYYY-MM-DD): ";
    cin >> date;

    cout << "Enter the category of the expense: ";
    cin.ignore();
    getline(cin, category);

    // Проверка баланса перед записью
    if (amount > _balance) {
        cout << "Insufficient funds!" << endl;
        return;
    }

    _balance -= amount;

    // Путь к файлу
    string fileName = "data/" + acc.getUserAccount() + ".txt";

    // Открываем файл для чтения
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Unable to open file for reading." << endl;
        return;
    }

    // Создаем строки для записи данных
    string userInfo;
    string expenseHistory;
    string line;
    bool balanceFound = false;

    // Читаем данные из файла и обновляем информацию
    while (getline(inFile, line)) {
        if (line.find("Balance:") != string::npos) {
            // Запоминаем строку с балансом, но не записываем ее сразу
            if (!balanceFound) {
                // Обновляем строку с балансом
                userInfo += "Balance: " + to_string(_balance) + "\n";
                balanceFound = true;
            }
        }
        else if (!balanceFound) {
            // Собираем основную информацию о пользователе до строки с балансом
            userInfo += line + "\n";
        }
        else {
            // Собираем историю расходов
            expenseHistory += line + "\n";
        }
    }
    inFile.close();

    // Записываем обновленные данные в файл
    ofstream outFile(fileName, ios::out | ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Unable to open file for writing." << endl;
        return;
    }

    // Записываем основную информацию о пользователе
    outFile << userInfo;

    // Добавляем старую историю расходов
    outFile << expenseHistory;

    outFile.close();
    cout << "Payment recorded successfully. New balance: " << _balance << endl;

    // Запись информации о платеже в файл
    logExpense(amount, date, category, acc.getUserAccount());
}

double DebitCard::getHowMuchMoney(const string& filename) {
    double number = 0.0;
    ifstream in(filename, ios::binary | ios::in);
    if (in.is_open()) {
        in.read(reinterpret_cast<char*>(&number), sizeof(number));
        in.close();
    }
    else {
        cerr << "Unable to open file for reading" << endl;
    }
    return number;
}
