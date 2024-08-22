#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

class BankAccount {
    int accNo;
    string name;
    string Fname;
    string cnic;
    string P_no;
    string email;
    float amount;
    int newAmount;
    string password;
    fstream file, file1;

public:
    int search;

    void createAccount(void);
    void depositAmount(void);
    void withdrawAmount(void);
    void checkInfo(void);
    void modifyAccount(void);
    void viewTransactionHistory(void);
};

void BankAccount::createAccount() {
    srand(time(0));
    accNo = rand() * rand() + rand() * rand();
    
    cout << "Enter Your name :: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter Your Father's name :: ";
    getline(cin, Fname);

    cout << "Enter Your CNIC :: ";
    getline(cin, cnic);
    
    cout << "Enter Your phone number :: ";
    getline(cin, P_no);
    
    cout << "Enter Your email :: ";
    getline(cin, email);
    
    cout << "Enter Your initial amount :: ";
    cin >> amount;
    
    cout << "Set a password for your account :: ";
    cin >> password;
    
    cout << endl << accNo << " This is your account number... \n";
    cout << "Please save it \n\n";
    
    file.open("data.txt", ios::out | ios::app);
    file << accNo << "\t" << name << "\t" << Fname << "\t" << cnic << "\t" << P_no << "\t" << email << "\t" << amount << "\t" << password << endl;
    file.close();
}

void BankAccount::depositAmount() {
    cout << "Enter amount to deposit :: ";
    cin >> newAmount;

    file.open("data.txt", ios::in);
    file1.open("data1.txt", ios::out | ios::app);
    file >> accNo >> name >> Fname >> cnic >> P_no >> email >> amount >> password;

    while (!file.eof()) {
        if (accNo == search) {
            cout << "\nCurrent amount :: " << amount;
            amount += newAmount;
            cout << "\nUpdated amount :: " << amount << endl;
            
            // Log transaction
            fstream historyFile;
            historyFile.open("transaction_history.txt", ios::app);
            historyFile << "Deposit\t" << search << "\t" << newAmount << "\t" << amount << endl;
            historyFile.close();
            
            file1 << accNo << "\t" << name << "\t" << Fname << "\t" << cnic << "\t" << P_no << "\t" << email << "\t" << amount << "\t" << password << endl;
        } else {
            file1 << accNo << "\t" << name << "\t" << Fname << "\t" << cnic << "\t" << P_no << "\t" << email << "\t" << amount << "\t" << password << endl;
        }
        file >> accNo >> name >> Fname >> cnic >> P_no >> email >> amount >> password;
    }

    file.close();
    file1.close();
    remove("data.txt");
    rename("data1.txt", "data.txt");
}

void BankAccount::withdrawAmount() {
    cout << "Enter amount to withdraw :: ";
    cin >> newAmount;

    file.open("data.txt", ios::in);
    file1.open("data1.txt", ios::out | ios::app);
    file >> accNo >> name >> Fname >> cnic >> P_no >> email >> amount >> password;

    while (!file.eof()) {
        if (accNo == search) {
            if (amount >= newAmount) {
                cout << "\nCurrent amount :: " << amount;
                amount -= newAmount;
                cout << "\nUpdated amount :: " << amount << endl;
                
                // Log transaction
                fstream historyFile;
                historyFile.open("transaction_history.txt", ios::app);
                historyFile << "Withdrawal\t" << search << "\t" << newAmount << "\t" << amount << endl;
                historyFile.close();
                
                file1 << accNo << "\t" << name << "\t" << Fname << "\t" << cnic << "\t" << P_no << "\t" << email << "\t" << amount << "\t" << password << endl;
            } else {
                cout << "Insufficient funds!" << endl;
                file1 << accNo << "\t" << name << "\t" << Fname << "\t" << cnic << "\t" << P_no << "\t" << email << "\t" << amount << "\t" << password << endl;
            }
        } else {
            file1 << accNo << "\t" << name << "\t" << Fname << "\t" << cnic << "\t" << P_no << "\t" << email << "\t" << amount << "\t" << password << endl;
        }
        file >> accNo >> name >> Fname >> cnic >> P_no >> email >> amount >> password;
    }

    file.close();
    file1.close();
    remove("data.txt");
    rename("data1.txt", "data.txt");
}

void BankAccount::checkInfo() {
    file.open("data.txt", ios::in);
    if (!file) {
        cout << "File opening error !" << endl;
        return;
    }
    file >> accNo >> name >> Fname >> cnic >> P_no >> email >> amount >> password;
    while (!file.eof()) {
        if (accNo == search) {
            cout << "\n---------------------------\n";
            cout << "\t::: Account Number ::: " << accNo << endl;
            cout << "\t::: User Name      ::: " << name << endl;
            cout << "\t::: Father's Name  ::: " << Fname << endl;
            cout << "\t::: CNIC Number    ::: " << cnic << endl;
            cout << "\t::: Phone Number   ::: " << P_no << endl;
            cout << "\t::: Email          ::: " << email << endl;
            cout << "\t::: Current Amount ::: " << amount << endl;
            cout << "\n---------------------------\n\n";
        }
        file >> accNo >> name >> Fname >> cnic >> P_no >> email >> amount >> password;
    }
    file.close();
}

void BankAccount::modifyAccount() {
    bool accountFound = false;
    fstream tempFile;

    file.open("data.txt", ios::in);
    tempFile.open("temp.txt", ios::out | ios::app);
    file >> accNo >> name >> Fname >> cnic >> P_no >> email >> amount >> password;

    while (!file.eof()) {
        if (accNo == search) {
            accountFound = true;
            cout << "Enter new details (press Enter to keep current value):\n";
            
            string newName, newFname, newCnic, newP_no, newEmail;
            
            cout << "Current Name: " << name << "\nNew Name: ";
            cin.ignore();
            getline(cin, newName);
            if (!newName.empty()) name = newName;
            
            cout << "Current Father's Name: " << Fname << "\nNew Father's Name: ";
            getline(cin, newFname);
            if (!newFname.empty()) Fname = newFname;
            
            cout << "Current CNIC: " << cnic << "\nNew CNIC: ";
            getline(cin, newCnic);
            if (!newCnic.empty()) cnic = newCnic;
            
            cout << "Current Phone Number: " << P_no << "\nNew Phone Number: ";
            getline(cin, newP_no);
            if (!newP_no.empty()) P_no = newP_no;
            
            cout << "Current Email: " << email << "\nNew Email: ";
            getline(cin, newEmail);
            if (!newEmail.empty()) email = newEmail;

            // Write updated account information to the temp file
            tempFile << accNo << "\t" << name << "\t" << Fname << "\t" << cnic << "\t" << P_no << "\t" << email << "\t" << amount << "\t" << password << endl;
        } else {
            // Write existing account information to the temp file
            tempFile << accNo << "\t" << name << "\t" << Fname << "\t" << cnic << "\t" << P_no << "\t" << email << "\t" << amount << "\t" << password << endl;
        }
        file >> accNo >> name >> Fname >> cnic >> P_no >> email >> amount >> password;
    }

    if (!accountFound) {
        cout << "Account not found!" << endl;
    }

    file.close();
    tempFile.close();
    remove("data.txt");
    rename("temp.txt", "data.txt");
}

void BankAccount::viewTransactionHistory() {
    ifstream historyFile;
    string line;
    bool accountFound = false;

    historyFile.open("transaction_history.txt", ios::in);
    if (!historyFile) {
        cout << "Error opening transaction history file!" << endl;
        return;
    }

    cout << "Transaction History for Account Number " << search << ":\n";
    cout << "-------------------------------------------\n";

    while (getline(historyFile, line)) {
        if (line.find(to_string(search)) != string::npos) {
            cout << line << endl;
            accountFound = true;
        }
    }

    if (!accountFound) {
        cout << "No transaction history found for this account." << endl;
    }

    historyFile.close();
}

int main() {
    BankAccount obj;
    char choice;

    cout << "\n\n\n\t\t......:::Aditya's Bank:::......";
    cout << "\n\t\t:: Press 1 to Login to Account :: ";
    cout << "\n\t\t:: Press 2 to Create Account ::";
    cout << "\n\t\t:: Press 0 to Exit           ::";
    cout << "\n\t\t:: ......................... ::\n\t\t\t\t";
    cin >> choice;
    
    switch(choice) {
        case '1':
            cout << "Enter your account number :: ";
            cin >> obj.search;
            while (1) {
                cout << "\n\n\n\t\t.......:::Aditya's Bank:::.......";
                cout << "\n\t\t:: Press 1 to Deposit Amount  :: ";
                cout << "\n\t\t:: Press 2 to Withdraw Amount ::";
                cout << "\n\t\t:: Press 3 to Check Info     ::";
                cout << "\n\t\t:: Press 4 to Modify Account  ::";
                cout << "\n\t\t:: Press 5 to View Transactions ::";
                cout << "\n\t\t:: Press 0 to Exit Menu      ::";
                cout << "\n\t\t:: ........................... ::\n\t\t\t\t";
                cin >> choice;

                switch (choice) {
                    case '1':
                        obj.depositAmount();
                        break;
                    case '2':
                        obj.withdrawAmount();
                        break;
                    case '3':
                        obj.checkInfo();
                        break;
                    case '4':
                        obj.modifyAccount();
                        break;
                    case '5':
                        obj.viewTransactionHistory();
                        break;
                    case '0':
                        return 0;
                    default:
                        cout << "Invalid Choice...!";
                        break;
                }
                system("pause");
                system("cls");
            }
            break;
        case '2':
            obj.createAccount();
            break;
        case '0':
            exit(0);
        default:
            cout << "\n Invalid choice...! ";
            break;
    }
    return 0;
}
