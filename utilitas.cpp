#include <iostream>
#include <string>
#include <limits>

using namespace std;

void cls() {
    cout << "\033[2J\033[H";
}

void pause() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.get();
}