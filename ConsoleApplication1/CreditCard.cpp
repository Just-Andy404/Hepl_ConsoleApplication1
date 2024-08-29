
#include "CreditCard.h"
#include "SaveData.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void CreditCard::addMoney(const Account& acc) {
    double money = 0.0;
    cout << "How much money do you want to add to the credit card: ";
    cin >> money;
    cout << endl;

    // ���������� ������� (���������, ��� ������ ����� ���� ������������� ��� ��������� �����)
    _balance += money;

    // ���� � �����
    string fileName = "data/" + acc.getUserAccount() + ".txt";

    // ������ �������� ����������� �����
    ifstream inFile(fileName);
    string fileContent;
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            fileContent += line + "\n";
        }
        inFile.close();
    }
    else {
        cerr << "Unable to open file for reading." << endl;
        return;
    }

    // ������ ������������ ������� � ��� �� ����, �������� �������
    ofstream outFile(fileName, ios::out | ios::trunc);
    if (outFile.is_open()) {
        string updatedFileContent;
        istringstream fileStream(fileContent);
        string line;
        while (getline(fileStream, line)) {
            if (line.find("Balance:") != string::npos) {
                line = "Balance: " + to_string(_balance);
            }
            updatedFileContent += line + "\n";
        }

        outFile << updatedFileContent;
        outFile.close();
        cout << "New balance saved successfully." << endl;
    }
    else {
        cerr << "Unable to open file for writing." << endl;
    }
}


void CreditCard::payment(const Account& acc) {
    double amount = 0.0;
    string date;
    string category;

    // ���� ������
    cout << "Enter the amount you spent: ";
    cin >> amount;

    cout << "Enter the date (format YYYY-MM-DD): ";
    cin >> date;

    cout << "Enter the category of the expense: ";
    cin.ignore();
    getline(cin, category);

    // ���� � �����
    string fileName = "data/" + acc.getUserAccount() + ".txt";

    // ������ �������� ������� � ������� �� �����
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Unable to open file for reading." << endl;
        return;
    }

    double currentBalance = 0.0;
    string fileContent;
    string line;
    while (getline(inFile, line)) {
        if (line.find("Balance:") != string::npos) {
            currentBalance = stod(line.substr(line.find(":") + 1));
        }
        fileContent += line + "\n";
    }
    inFile.close();

    //// �������� �� ���������� ���������� ������ ����� ����� �������� �������
    //if (amount > currentBalance + _creditLimit) {
    //    cout << "Insufficient funds. Transaction denied." << endl;
    //    return;
    //}

    // ���������� ������� (������ ����� ���� �������������)
    double newBalance = currentBalance - amount;

    // ������ ������������ ������� � ����
    ofstream outFile(fileName, ios::out | ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Unable to open file for writing." << endl;
        return;
    }

    istringstream fileStream(fileContent);
    while (getline(fileStream, line)) {
        if (line.find("Balance:") != string::npos) {
            line = "Balance: " + to_string(newBalance);
        }
        outFile << line << "\n";
    }
    outFile.close();

    cout << "Payment processed successfully. New balance saved." << endl;

    // ������ ���������� � ������� � ����
    logExpense(amount, date, category, acc.getUserAccount());
}

