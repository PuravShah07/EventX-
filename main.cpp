#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// ======================= CLASS DEFINITIONS ==========================

class User {
private:
    string userName;
    string password;
    bool isOrganizer;

public:
    void setDetail(string usrNm, string pswd, bool isOrg) {
        userName = usrNm;
        password = pswd;
        isOrganizer = isOrg;
    }

    string getName() const { return userName; }
    string getPassword() const { return password; }
    bool getIsOrganizer() const { return isOrganizer; }

    void saveToFile() {
        ofstream fout("users.txt", ios::app);
        fout << userName << " " << password << " " << isOrganizer << endl;
        fout.close();
    }

    static bool checkCredentials(const string &usrNm, const string &pswd, bool isOrg) {
        ifstream fin("users.txt");
        string u, p;
        bool org;
        while (fin >> u >> p >> org) {
            if (u == usrNm && p == pswd && org == isOrg) {
                fin.close();
                return true;
            }
        }
        fin.close();
        return false;
    }
};

// --------------------------------------------------------------------

class Event {
private:
    string eventName;
    string date;
    int totalTickets;
    int availableTickets;

public:
    Event(string name = "", string dt = "", int total = 0) {
        eventName = name;
        date = dt;
        totalTickets = total;
        availableTickets = total;
    }

    string getName() const { return eventName; }
    string getDate() const { return date; }
    int getAvailableTickets() const { return availableTickets; }

    bool bookTicket(int count) {
        if (availableTickets >= count) {
            availableTickets -= count;
            return true;
        }
        return false;
    }

    void cancelTicket(int count) {
        availableTickets += count;
        if (availableTickets > totalTickets)
            availableTickets = totalTickets;
    }

    void showEvent() const {
        cout << "Event: " << eventName
             << " | Date: " << date
             << " | Available Tickets: " << availableTickets << endl;
    }

    void saveToFile() {
        ofstream fout("events.txt", ios::app);
        fout << eventName << " " << date << " " << totalTickets << " " << availableTickets << endl;
        fout.close();
    }

    static vector<Event> loadFromFile() {
        vector<Event> events;
        ifstream fin("events.txt");
        string name, date;
        int total, available;
        while (fin >> name >> date >> total >> available) {
            Event e(name, date, total);
            e.cancelTicket(total - available); // restore available count
            events.push_back(e);
        }
        fin.close();
        return events;
    }

    static void overwriteFile(const vector<Event> &events) {
        ofstream fout("events.txt", ios::trunc);
        for (auto &e : events) {
            fout << e.getName() << " " << e.getDate() << " "
                 << e.getAvailableTickets() << " " << e.getAvailableTickets() << endl;
        }
        fout.close();
    }
};

// --------------------------------------------------------------------

class Organizer : public User {
public:
    void listEvent() {
        string name, date;
        int tickets;
        cout << "\nEnter Event Name: ";
        cin >> name;
        cout << "Enter Date (DD/MM): ";
        cin >> date;
        cout << "Enter Total Tickets: ";
        cin >> tickets;

        Event e(name, date, tickets);
        e.saveToFile();

        cout << "✅ Event added successfully!\n";
    }

    void viewBooking() {
        cout << "\n--- Listed Events ---\n";
        vector<Event> events = Event::loadFromFile();
        if (events.empty()) {
            cout << "No events listed yet.\n";
            return;
        }
        for (auto &e : events)
            e.showEvent();
    }
};

// ----------------------------------------------------------

class Customer : public User {
private:
    vector<string> myBookings;

public:
    void viewEvents() {
        cout << "\n--- Available Events ---\n";
        vector<Event> events = Event::loadFromFile();
        if (events.empty()) {
            cout << "No events available.\n";
            return;
        }
        for (auto &e : events)
            e.showEvent();
    }

    void bookTickets() {
        vector<Event> events = Event::loadFromFile();
        if (events.empty()) {
            cout << "No events to book!\n";
            return;
        }

        string name;
        cout << "\nEnter Event Name to Book: ";
        cin >> name;

        for (auto &e : events) {
            if (e.getName() == name) {
                if (e.bookTicket(1)) {
                    cout << "🎟️ Ticket booked successfully for " << name << "!\n";
                    myBookings.push_back(name);
                    Event::overwriteFile(events);
                } else {
                    cout << "❌ Tickets sold out!\n";
                }
                return;
            }
        }
        cout << "❌ Event not found!\n";
    }

    void myTicket() {
        cout << "\n--- My Tickets ---\n";
        if (myBookings.empty()) {
            cout << "No tickets booked yet.\n";
            return;
        }
        for (auto &t : myBookings)
            cout << "- " << t << endl;
    }
};

// ====================== MENU & MAIN LOGIC ==========================

int chooseType() {
    int choice;
    cout << "==============================\n";
    cout << "     Welcome to EventX 🎉     \n";
    cout << "==============================\n";
    cout << "Who are you?\n";
    cout << "1. Organizer (Sign In / Sign Up)\n";
    cout << "2. Customer (Sign In / Sign Up)\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// --------------------------------------------------------------------

void login() {
    int c = chooseType();
    string usrNm, pswd;
    bool isOrg = (c == 1);

    cout << "\nEnter Username: ";
    cin >> usrNm;
    cout << "Enter Password: ";
    cin >> pswd;

    bool exists = User::checkCredentials(usrNm, pswd, isOrg);

    if (!exists) {
        cout << "\nNo such user found — creating a new account.\n";
        User u;
        u.setDetail(usrNm, pswd, isOrg);
        u.saveToFile();
        cout << "✅ Account created successfully!\n";
    } else {
        cout << "✅ Login successful! Welcome back, " << usrNm << "!\n";
    }

    Organizer organizer;
    Customer customer;

    if (isOrg) {
        organizer.setDetail(usrNm, pswd, true);
        int choice;
        do {
            cout << "\n===== Organizer Menu =====\n";
            cout << "1. List New Event\n";
            cout << "2. View My Events\n";
            cout << "0. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    organizer.listEvent();
                    break;
                case 2:
                    organizer.viewBooking();
                    break;
                case 0:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } while (choice != 0);
    } 
    else {
        customer.setDetail(usrNm, pswd, false);
        int choice;
        do {
            cout << "\n===== Customer Menu =====\n";
            cout << "1. View Events\n";
            cout << "2. Book Ticket\n";
            cout << "3. My Tickets\n";
            cout << "0. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    customer.viewEvents();
                    break;
                case 2:
                    customer.bookTickets();
                    break;
                case 3:
                    customer.myTicket();
                    break;
                case 0:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } while (choice != 0);
    }
}

// --------------------------------------------------------------------

int main() {
    login();
    cout << "\nThank you for using EventX!\n";
    return 0;
}
