#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class User {
public:
    int id;
    string name;
    string mobile;
    string pin;
    double balance;
    double jar_balance;
    bool blocked;

    User() {}
    User(int i, string n, string m, string p, double b = 0, double j = 0, bool bl = false) {
        id = i;
        name = n;
        mobile = m;
        pin = p;
        balance = b;
        jar_balance = j;
        blocked = bl;
    }
};

class Transaction {
public:
    int senderID;
    int receiverID;
    double amount;
    string timestamp;

    Transaction() {}
    Transaction(int s, int r, double a, string t) {
        senderID = s;
        receiverID = r;
        amount = a;
        timestamp = t;
    }
};

class FileHandler {
public:
    static void saveUsers(vector<User> &users) {
        ofstream file("users.txt");
        for (auto &u : users) {
             file << u.id << " " << u.name << " " << u.mobile << " "
                  << u.pin << " " << u.balance << " " << u.jar_balance << " " << u.blocked << endl;
        }
    }

    static void loadUsers(vector<User> &users) {
        ifstream file("users.txt");
        int id; string name, mobile, pin;
        double balance, jar_balance; bool blocked;

        while (file >> id >> name >> mobile >> pin >> balance >> jar_balance >> blocked) {
            users.push_back(User(id, name, mobile, pin, balance, jar_balance, blocked));
        }
    }

    static void saveTransactions(vector<Transaction> &transactions) {
        ofstream file("transactions.txt");
        for (auto &t : transactions) {
            file << t.senderID << " " << t.receiverID << " "
                 << t.amount << " " << t.timestamp << endl;
        }
    }

    static void loadTransactions(vector<Transaction> &transactions) {
        ifstream file("transactions.txt");
        int s, r; double a;
        string time;

        while (file >> s >> r >> a) {
            getline(file, time);
            transactions.push_back(Transaction(s, r, a, time));
        }
    }
};

string getTime() {
    time_t now = time(0);
    string t = ctime(&now);
    t.pop_back();
    return t;
}

class Wallet {
public:
    static void addMoney(User &user, double amount) {
        if (amount > 0) {
            user.balance += amount;
        }
    }

    static bool sendMoney(User &sender, User &receiver, double amount, vector<Transaction> &transactions) {
        if (amount <= 0 || sender.balance < amount) return false;

        sender.balance -= amount;
        receiver.balance += amount;

        transactions.push_back(Transaction(sender.id, receiver.id, amount, getTime()));
        return true;
    }
};

vector<User> users;
vector<Transaction> transactions;

User* findUser(string mobile) {
    for (auto &u : users) {
        if (u.mobile == mobile) return &u;
    }
    return nullptr;
}

int generateID() {
    return users.size() + 1;
}

void registerUser() {
    string name, mobile, pin;
    cout << "Name: "; cin >> name;
    cout << "Mobile: "; cin >> mobile;
    cout << "PIN: "; cin >> pin;

    if (findUser(mobile)) {
        cout << "User exists!\n";
        return;
    }

    users.push_back(User(generateID(), name, mobile, pin));
    FileHandler::saveUsers(users);
    cout << "Registered!\n";
}

User* login() {
    string mobile, pin;
    cout << "Mobile: "; cin >> mobile;
    cout << "PIN: "; cin >> pin;

    User* u = findUser(mobile);
    if (!u || u->pin != pin || u->blocked) {
        cout << "Login failed!\n";
        return nullptr;
    }
    return u;
}

void userMenu(User* u) {
    int ch;
    do {
        cout << "\n1.Balance\n2.Add Money\n3.Send Money\n4.Savings Jar\n5.Transaction History\n6.Logout\nChoice: ";
        cin >> ch;

        if (ch == 1) {
            cout << "Balance: " << u->balance << endl;
        }
        else if (ch == 2) {
            double amt;
            cout << "Amount: "; cin >> amt;
            Wallet::addMoney(*u, amt);
            FileHandler::saveUsers(users);
        }
        else if (ch == 3) {
            string mob;
            double amt;
            cout << "Receiver mobile: "; cin >> mob;
            User* r = findUser(mob);

            if (!r) {
                cout << "User not found!\n";
                continue;
            }

            cout << "Amount: "; cin >> amt;

            if (Wallet::sendMoney(*u, *r, amt, transactions)) {
                cout << "Success!\n";
                FileHandler::saveUsers(users);
                FileHandler::saveTransactions(transactions);
            } else {
                cout << "Failed!\n";
            }
        }
        else if (ch == 4) {
            int jCh;
            cout << "\n--- Savings Jar ---\n1.View Jar Balance\n2.Move to Jar\n3.Withdraw from Jar\nChoice: ";
            cin >> jCh;
            if (jCh == 1) {
                cout << "Jar Balance: " << u->jar_balance << endl;
            } else if (jCh == 2) {
                double a; cout << "Amount to move to jar: "; cin >> a;
                if (a > 0 && u->balance >= a) {
                    u->balance -= a;
                    u->jar_balance += a;
                    FileHandler::saveUsers(users);
                    cout << "Moved safely to Jar!\n";
                } else cout << "Invalid amount or insufficient balance!\n";
            } else if (jCh == 3) {
                double a; cout << "Amount to withdraw from jar: "; cin >> a;
                if (a > 0 && u->jar_balance >= a) {
                    u->jar_balance -= a;
                    u->balance += a;
                    FileHandler::saveUsers(users);
                    cout << "Withdrawn from Jar!\n";
                } else cout << "Invalid amount or insufficient jar balance!\n";
            }
        }
        else if (ch == 5) {
            cout << "--- Transaction History ---\n";
            bool found = false;
            for (auto &t : transactions) {
                if (t.senderID == u->id || t.receiverID == u->id) {
                    cout << (t.senderID == u->id ? "Sent: " : "Received: ") << t.amount 
                         << " | Time: " << t.timestamp << endl;
                    found = true;
                }
            }
            if (!found) cout << "No transactions found.\n";
        }

    } while (ch != 6);
}

void adminMenu() {
    string pin;
    cout << "Admin PIN: "; cin >> pin;
    if (pin != "admin123") {
        cout << "Invalid admin PIN!\n";
        return;
    }

    int ch;
    do {
        cout << "\n--- Admin Panel ---\n1.View Users\n2.Block/Unblock User\n3.View All Transactions\n4.Logout\nChoice: ";
        cin >> ch;

        if (ch == 1) {
            cout << "--- All Users ---\n";
            for (auto &u : users) {
                cout << "ID: " << u.id << " | Name: " << u.name << " | Mobile: " << u.mobile
                     << " | Balance: " << u.balance << " | Jar: " << u.jar_balance
                     << " | Blocked: " << (u.blocked ? "Yes" : "No") << endl;
            }
        }
        else if (ch == 2) {
            string mob;
            cout << "Enter User Mobile: "; cin >> mob;
            User* u = findUser(mob);
            if (u) {
                u->blocked = !u->blocked;
                FileHandler::saveUsers(users);
                cout << "User " << (u->blocked ? "Blocked!" : "Unblocked!") << "\n";
            } else {
                cout << "User not found!\n";
            }
        }
        else if (ch == 3) {
            cout << "--- All Transactions ---\n";
            for (auto &t : transactions) {
                cout << "Sender: " << t.senderID << " | Receiver: " << t.receiverID
                     << " | Amount: " << t.amount << " | Time: " << t.timestamp << endl;
            }
        }
    } while (ch != 4);
}

int main() {
    FileHandler::loadUsers(users);
    FileHandler::loadTransactions(transactions);

    int ch;

    do {
        cout << "\n1.Register\n2.Login\n3.Admin Login\n4.Exit\nChoice: ";
        cin >> ch;

        if (ch == 1) registerUser();
        else if (ch == 2) {
            User* u = login();
            if (u) userMenu(u);
        }
        else if (ch == 3) {
            adminMenu();
        }

    } while (ch != 4);

    return 0;
}
