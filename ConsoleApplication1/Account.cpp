#include "Account.h"
#include "SaveData.h"
#include "debit—ards.h"
#include "CreditCard.h"
#include <fstream>
#include <iostream>
using namespace std;

Account::Account(string userAccount, string userPassword, Card* userCard, string userName)
    : _userAccount(userAccount), _userPassword(userPassword), _userCard(userCard), _userName(userName)
{
    userCard->generateNumsOfCard();
    SaveData::createFileAndWriteData("data", _userAccount, _userName, _userPassword, _userCard);
}


void Account::showInfo() const {
    cout << "User name: " << _userName << endl;
    cout << "Account: " << _userAccount << endl;
    cout << "Password: " << _userPassword << endl;

    if (_userCard) {
        const int* cardNumbers = _userCard->getNumsOfCard();
        cout << "Card type: " << (_userCard->getCardType() == DEBIT ? "Debit" : "Credit") << endl;  // ŒÚÓ·‡Ê‡ÂÏ ÚËÔ Í‡Ú˚
        cout << "Card numbers: ";
        for (int i = 0; i < 16; ++i) {
            cout << cardNumbers[i];
            if (i < 15) cout << " ";
        }
        cout << endl;
        double balance = SaveData::getBalanceFromFile("data", _userAccount);
        cout << "Balance: " << balance << endl;
        if (auto* creditCard = dynamic_cast<CreditCard*>(_userCard)) {
            cout << "Credit Limit: " << creditCard->getCreditLimit() << endl;
        }

    }
    else {
        cout << "No card associated." << endl;
    }
}
