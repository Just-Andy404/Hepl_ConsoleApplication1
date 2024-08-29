#include "Account.h"
#include "Card.h"
#include "CreditCard.h"
#include "debitСards.h"
#include "SaveData.h"
using namespace std;

int WelcomeMenu()
{
    while (true)
    {
        int choice = 0;
        cout << "Welcome to our bank !" << endl;
        cout << "1) Login" << endl;
        cout << "2) Registrate an account" << endl << "choice: ";
        cin >> choice;
        cout << endl;
        if (choice == 1 || choice == 2)
        {
            return choice;
        }
        else
        {
            cout << "Input coorect choice" << endl;
        }
    }
}

Account LoginMenu() {
    string login, password;

    cout << "Login: ";
    cin >> login;

    cout << "Password: ";
    cin >> password;

    if (SaveData::validateLoginAndPassword("data", login, password)) {
        cout << "Login successful!" << endl;

        Account account;
        Card* userCard = nullptr;
        ifstream inFile("data/" + login + ".txt");

        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                if (line.find("User name: ") != string::npos) {
                    account.setUserName(line.substr(11));
                }
                else if (line.find("Account: ") != string::npos) {
                    account.setUserAccount(line.substr(9));
                }
                else if (line.find("Password: ") != string::npos) {
                    account.setUserPassword(line.substr(10));
                }
                else if (line.find("Card type: ") != string::npos) {
                    string cardType = line.substr(11);
                    if (cardType == "Debit") {
                        userCard = new DebitCard();
                    }
                    else if (cardType == "Credit") {
                        userCard = new CreditCard();
                    }
                }
                else if (line.find("Card number: ") != string::npos && userCard != nullptr) {
                    string cardNumbers = line.substr(13); // Извлекаем строку с номерами
                    int cardDigits[16] = { 0 }; // Массив для хранения номеров карты
                    size_t pos = 0;
                    int index = 0;

                    // Проходим по строке и извлекаем числа
                    while ((pos = cardNumbers.find(' ')) != string::npos && index < 16) {
                        cardDigits[index] = stoi(cardNumbers.substr(0, pos));
                        cardNumbers.erase(0, pos + 1);
                        index++;
                    }

                    // Последнее число
                    if (index < 16) {
                        cardDigits[index] = stoi(cardNumbers);
                    }

                    userCard->setCardNumber(cardDigits);
                }

            }
            inFile.close();
        }
        else {
            cerr << "Unable to open file for reading." << endl;
        }

        account.setWhichOfCard(userCard);
        return account;
    }
    else {
        cout << "Invalid login or password." << endl;
        return Account();  // Возвращаем пустой аккаунт при неудачном логине
    }
}



Card* WhichOneCards(Account& Acc) {
    Card* card = Acc.getWhichOfCard();

    if (!card) {
        cout << "No valid card associated with the account." << endl;
        return nullptr;
    }

    if (CreditCard* creditCard = dynamic_cast<CreditCard*>(card)) {
        cout << "Credit card selected." << endl;
        return creditCard;
    }
    else if (DebitCard* debitCard = dynamic_cast<DebitCard*>(card)) {
        cout << "Debit card selected." << endl;
        return debitCard;
    }
    else {
        cout << "Unknown card type associated with the account." << endl;
        return nullptr;
    }
}

Account RegisterateMenu() {
    string login, password, name;
    int choice;

    // Проверка корректности логина
    while (true) {
        cout << "Login (should end with @gmail.com): ";
        cin >> login;

        if (login.size() >= 10 && login.rfind("@gmail.com") == login.size() - 10) {
            break;
        }
        else {
            cout << "Invalid login. It must end with '@gmail.com'. Please try again." << endl;
        }
    }

    cout << "Password: ";
    cin >> password;

    cout << "What's your name: ";
    cin >> name;

    cout << "Which card do you want to use?\n1) Debit card\n2) Credit card\nChoice: ";
    cin >> choice;

    Card* userCard = nullptr;

    if (choice == 1) {
        userCard = new DebitCard();  // Создаем объект DebitCard
    }
    else if (choice == 2) {
        double creditLimit;
        cout << "Enter your desired credit limit: ";
        cin >> creditLimit;
        if (creditLimit > 0)
        {
            creditLimit *= -1;
        }
        userCard = new CreditCard(creditLimit);  // Создаем объект CreditCard с лимитом
    }

    Account account(login, password, userCard, name);
    return account;
}

void Menu(Account& Acc) {
    int WelcomeMenuChoice = WelcomeMenu();

    if (WelcomeMenuChoice == 1)
    {
        Acc = LoginMenu();
    }
    else if (WelcomeMenuChoice == 2)
    {
        Acc = RegisterateMenu();
    }
    int choice;
    Card* card = WhichOneCards(Acc);

    while (true)
    {
        cout << "Welcome " << Acc.getUserName() << endl;
        cout << "1) Show info" << endl;
        cout << "2) Add money" << endl;
        cout << "3) Pay" << endl;
        cout << "4) Generate reports on expenses and categories" << endl;
        cout << "5) Top 3 expenses" << endl;
        cout << "6) TOP 3 categories" << endl;
        cout << "0) Exit" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            Acc.showInfo();
            break;
        case 2:
            if (DebitCard* debitCard = dynamic_cast<DebitCard*>(card)) {
                debitCard->addMoney(Acc);
            }
            else if (CreditCard* creditCard = dynamic_cast<CreditCard*>(card)) {
                creditCard->addMoney(Acc);
            }
            break;
        case 3:
            if (DebitCard* debitCard = dynamic_cast<DebitCard*>(card)) {
                debitCard->payment(Acc); // Вызов метода payment() для дебетовой карты
            }
            else if (CreditCard* creditCard = dynamic_cast<CreditCard*>(card)) {
                creditCard->payment(Acc); // Вызов метода payment() для кредитной карты
            }
            break;
        case 4:
            if (DebitCard* debitCard = dynamic_cast<DebitCard*>(card)) {
                debitCard->reportsExpensesCategories(); // Вызов метода payment() для дебетовой карты
            }
            else if (CreditCard* creditCard = dynamic_cast<CreditCard*>(card)) {
                creditCard->reportsExpensesCategories(); // Вызов метода payment() для кредитной карты
            }
            break;
        case 5:
            cout << "e" << endl;
        case 6:
            cout << "e" << endl;
        case 0:
            exit(0);
        default:
            cout << "Invalid choice!" << endl;
            break;
        }

    }
}
