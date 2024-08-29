// SaveData.h

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Card.h"

using namespace std;

class SaveData {
public:
    static bool validateLoginAndPassword(const string& directory, const string& userAccount, const string& userPassword) {
        string filePath = "data/" + userAccount + ".txt";

        ifstream inFile(filePath);
        if (inFile.is_open()) {
            string line;
            string storedPassword;
            while (getline(inFile, line)) {
                if (line.find("Password: ") != string::npos) {
                    storedPassword = line.substr(10);
                    break;
                }
            }
            inFile.close();
            return storedPassword == userPassword;
        }
        else {
            cerr << "Account with login " << userAccount << " does not exist." << endl;
            return false;
        }
    }

    static void createFileAndWriteData(const string& directory, const string& userAccount, const string& userName, const string& userPassword, Card* userCard) {
        string filePath = directory + "/" + userAccount + ".txt";

        ofstream outFile(filePath);
        if (outFile.is_open()) {
            outFile << "User name: " << userName << endl;
            outFile << "Account: " << userAccount << endl;
            outFile << "Password: " << userPassword << endl;
            if (userCard) {
                outFile << "Card type: " << (userCard->getCardType() == DEBIT ? "Debit" : "Credit") << endl;
                outFile << "Card number: ";
                const int* cardNumbers = userCard->getNumsOfCard();
                for (int i = 0; i < 16; ++i) {
                    outFile << cardNumbers[i];
                    if (i < 15) outFile << " ";
                }
                outFile << endl;
                outFile << "Balance: " << userCard->getBalance() << endl;
                /*if (dynamic_cast<CreditCard*>(userCard)) {
                    CreditCard* creditCard = static_cast<CreditCard*>(userCard);
                    cout << "Credit Limit: " << creditCard->getCreditLimit() << endl;
                }*/
            }
            else {
                outFile << "No card associated." << endl;
            }
            outFile.close();
        }
        else {
            cerr << "Unable to open file for writing: " << filePath << endl;
        }
    }


    static void analyzeAndPrintFile(const string& filePath) {
        ifstream inFile(filePath);
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        }
        else {
            cerr << "Unable to open file for reading: " << filePath << endl;
        }
    }

    static void appendDataToFile(const string& filePath, const string& data) {
        ofstream outFile(filePath, ios::app);
        if (outFile.is_open()) {
            outFile << data << endl;
            outFile.close();
        }
        else {
            cerr << "Unable to open file for appending: " << filePath << endl;
        }
    }
    
    static double getBalanceFromFile(const string& directory, const string& userAccount) {
        string filePath = directory + "/" + userAccount + ".txt";

        ifstream inFile(filePath);
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                // Ищем строку, начинающуюся с "Balance: "
                size_t pos = line.find("Balance: ");
                if (pos != string::npos) {
                    // Извлекаем значение баланса
                    // Позиция после "Balance: " начинается с pos + 9
                    string balanceStr = line.substr(pos + 9);
                    // Преобразуем строку в число
                    double balance = 0.0;
                    try {
                        balance = stod(balanceStr); // stod преобразует строку в double
                    }
                    catch (const invalid_argument& e) {
                        cerr << "Invalid balance format in file: " << filePath << endl;
                    }
                    inFile.close();
                    return balance;
                }
            }
            inFile.close();
        }
        else {
            cerr << "Unable to open file for reading: " << filePath << endl;
        }
        return 0.0; // Возвращаем 0, если файл не удалось открыть или не найдено значение баланса
    }
};
