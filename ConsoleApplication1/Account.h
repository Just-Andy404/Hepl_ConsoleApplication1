#pragma once
#include <iostream>
#include <cstdlib>  // Для rand() и srand()
#include <ctime>    // Для time()
using namespace std;
class Card;
class Account
{
private:
    string _userName;
    string _userAccount;
    string _userPassword;
    Card* _userCard;
public:
    // Конструктор по умолчанию
    Account() : _userAccount(""), _userName(""), _userPassword(""), _userCard(nullptr) { }

    // Конструктор с параметрами
    Account(string userAccount, string userPassword, Card* userCard, string userName);

    // Методы для установки значений
    void setUserAccount(const string& userAccount) {
        _userAccount = userAccount;
    }

    void setUserName(const string& userName) {
        _userName = userName;
    }

    void setUserPassword(const string& userPassword) {
        _userPassword = userPassword;
    }

    void setWhichOfCard(Card* userCard) {
        _userCard = userCard;
    }

    // Методы для получения значений
    string getUserAccount() const {
        return _userAccount;
    }

    string getUserName() const {
        return _userName;
    }
    string getUserPassword() const {
        return _userPassword;
    }

    Card* getWhichOfCard() const {
        return _userCard;
    }

    // Проверка пароля
    bool checkPassword(const string& password) const {
        return _userPassword == password;
    }

    // Показ информации
    void showInfo() const;

};
