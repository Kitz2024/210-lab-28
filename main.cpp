//Kit Pollinger
// 210 - lab - 28 | Algorithm 

// 210 - Lab 24 Forking

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <set>
#include <algorithm>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string[], string[]);
void display_trip(list<Goat> trip);
int main_menu();
void sort_by_age(list<Goat>& trip);
void sort_by_name(list<Goat>& trip);
Goat find_oldest_goat(const list<Goat>& trip);
Goat find_youngest_goat(const list<Goat>& trip);
int count_goats_by_color(const list<Goat>& trip, const string& color);
void reverse_goat_list(list<Goat>& trip);
void unique_goat_names(const list<Goat>& trip);
void clear_goat_list(list<Goat>& trip);

int main() {
    srand(time(0));

    // Read and populate arrays for names and colors
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

    // Create and populate a trip of Goats using std::list with random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }

    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                sort_by_age(trip);
                cout << "Goats sorted by age:\n";
                display_trip(trip);
                break;
            case 5:
                sort_by_name(trip);
                cout << "Goats sorted by name:\n";
                display_trip(trip);
                break;
            case 6:
                cout << "Oldest goat: " << find_oldest_goat(trip).get_name() << endl;
                break;
            case 7:
                cout << "Youngest goat: " << find_youngest_goat(trip).get_name() << endl;
                break;
            case 8: {
                string color;
                cout << "Enter a color: ";
                cin >> color;
                int count = count_goats_by_color(trip, color);
                cout << "Number of goats with color " << color << ": " << count << endl;
                break;
            }
            case 9:
                reverse_goat_list(trip);
                cout << "Reversed goat list:\n";
                display_trip(trip);
                break;
            case 10:
                cout << "Unique goat names:\n";
                unique_goat_names(trip);
                break;
            case 11:
                clear_goat_list(trip);
                cout << "Goat list cleared.\n";
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats by age\n";
    cout << "[5] Sort goats by name\n";
    cout << "[6] Find the oldest goat\n";
    cout << "[7] Find the youngest goat\n";
    cout << "[8] Count goats by color\n";
    cout << "[9] Reverse the goat list\n";
    cout << "[10] Unique goat names\n";
    cout << "[11] Clear goat list\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index - 1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt : trp)
        cout << "\t"
             << "[" << i++ << "] "
             << gt.get_name()
             << " (" << gt.get_age()
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void sort_by_age(list<Goat>& trip) {
    trip.sort([](const Goat& a, const Goat& b) { return a.get_age() < b.get_age(); });
}

void sort_by_name(list<Goat>& trip) {
    trip.sort([](const Goat& a, const Goat& b) { return a.get_name() < b.get_name(); });
}

Goat find_oldest_goat(const list<Goat>& trip) {
    return *max_element(trip.begin(), trip.end(), [](const Goat& a, const Goat& b) { return a.get_age() < b.get_age(); });
}

Goat find_youngest_goat(const list<Goat>& trip) {
    return *min_element(trip.begin(), trip.end(), [](const Goat& a, const Goat& b) { return a.get_age() < b.get_age(); });
}

int count_goats_by_color(const list<Goat>& trip, const string& color) {
    return count_if(trip.begin(), trip.end(), [color](const Goat& g) { return g.get_color() == color; });
}

void reverse_goat_list(list<Goat>& trip) {
    trip.reverse();
}

void unique_goat_names(const list<Goat>& trip) {
    set<string> unique_names;
    for (const Goat& g : trip) {
        unique_names.insert(g.get_name());
    }
    for (const string& name : unique_names) {
        cout << name << endl;
    }
}

void clear_goat_list(list<Goat>& trip) {
    trip.clear();
}
