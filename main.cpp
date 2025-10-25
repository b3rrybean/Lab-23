#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    list<Goat> trip;
    int choice;
    do {
        choice = main_menu();
        switch (choice) {
            case 1: add_goat(trip, names, colors); break;
            case 2: delete_goat(trip); break;
            case 3: display_trip(trip); break;
            case 4: cout << "Goodbye!\n"; break;
        }
    } while (choice != 4);

    return 0;
}

int main_menu() {
    int choice;
    cout <<"\n --- Goat Manager 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    cin >> choice;

    while (choice < 1 || choice > 4 || cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice. Please try again: ";
        cin >> choice;
    }
    return choice;
}

void add_goat(list<Goat> &trip, string names[], string colors[]) {
    int randName = rand() % SZ_NAMES;
    int randColor = rand() % SZ_COLORS;
    int randAge = rand() % (MAX_AGE + 1);

    Goat g(names[randName], randAge, colors[randColor]);
    trip.push_back(g);

    cout << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ") added to the trip!\n";
}

void display_trip(list<Goat> trip) {
if (trip.empty()) {
        cout << "No goats in the trip yet.\n";
        return;
    }

    cout << "\nCurrent Goats on the Trip:\n";
    int i = 1;
    for (const auto &g : trip) {
        cout << "[" << i++ << "] " << g.get_name() 
             << " (" << g.get_age() << ", " << g.get_color() << ")\n";
    }
}

int select_goat(list<Goat> trip) {
if (trip.empty()) {
        cout << "No goats to delete.\n";
        return -1;
    }

    display_trip(trip);
    cout << "Select a goat number to delete: ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > static_cast<int>(trip.size())) {
        cout << "Invalid choice.\n";
        return -1;
    }
    return choice;

}

void delete_goat(list<Goat> &trip) {
int choice = select_goat(trip);
if (choice == -1) return;

auto it = trip.begin();
advance(it, choice - 1);
cout << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ") removed from the trip.\n";
trip.erase(it);
}