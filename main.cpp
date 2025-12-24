#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    int choice;
    string problem, platform, difficulty, status;

    ofstream file("data.txt", ios::app);

    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    cout << "DSA Practice Tracker\n";
    cout << "1. Add new problem\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "Problem Name: ";
        getline(cin, problem);

        cout << "Platform (LeetCode/CodeChef): ";
        getline(cin, platform);

        cout << "Difficulty (Easy/Medium/Hard): ";
        getline(cin, difficulty);

        cout << "Status (Solved/Unsolved): ";
        getline(cin, status);

        file << problem << " | "
             << platform << " | "
             << difficulty << " | "
             << status << endl;

        cout << "Problem saved successfully!\n";
    }

    file.close();
    return 0;
}
