#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <limits>
#include <cctype>
#include <iomanip>
using namespace std;

struct Problem
{
    string name;
    string platform;
    string topic;
    string difficulty;
    string status;
    string important;
};

string toLowerCase(string s)
{
    for (char &c : s)
        c = tolower(c);
    return s;
}

string trim(const string &s)
{
    size_t start = s.find_first_not_of(" ");
    size_t end = s.find_last_not_of(" ");
    if (start == string::npos || end == string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

void addProblem()
{
    string problem, platform, topic, difficulty, status, important;
    char markImportant;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Problem Name: ";
    getline(cin, problem);

    cout << "Platform (LeetCode/CodeChef): ";
    getline(cin, platform);

    cout << "Topic: ";
    getline(cin, topic);

    cout << "Difficulty (Easy/Medium/Hard): ";
    getline(cin, difficulty);

    cout << "Status (Solved/Unsolved): ";
    getline(cin, status);

    cout << "Do you want to mark this as important? (y/n): ";
    cin >> markImportant;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    important = (markImportant == 'y' || markImportant == 'Y') ? "IMPORTANT" : "NORMAL";

    ofstream file("data.txt", ios::app);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    file << problem << " | "
         << platform << " | "
         << topic << " | "
         << difficulty << " | "
         << status << " | "
         << important << endl;

    file.close();
    cout << "Problem saved successfully!\n";
}

void viewProblems()
{
    ifstream file("data.txt");
    if (!file)
    {
        cout << "No data found!\n";
        return;
    }

    string line;
    cout << "\n===== ALL PROBLEMS =====\n";
    while (getline(file, line))
    {
        cout << line << endl;
    }
    file.close();
}

void searchProblem()
{
    ifstream file("data.txt");
    if (!file)
    {
        cout << "No data file found!\n";
        return;
    }

    string line, searchName;
    bool found = false;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter problem name to search: ";
    getline(cin, searchName);

    while (getline(file, line))
    {
        if (toLowerCase(line).find(toLowerCase(searchName)) != string::npos)
        {
            cout << "Found: " << line << endl;
            found = true;
        }
    }

    if (!found)
        cout << "Problem not found.\n";
    file.close();
}

void deleteProblem()
{
    ifstream readFile("data.txt");
    ofstream tempFile("temp.txt");
    if (!readFile)
    {
        cout << "No data file found!\n";
        return;
    }

    string line, deleteName;
    bool deleted = false;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter problem name to delete: ";
    getline(cin, deleteName);

    while (getline(readFile, line))
    {
        if (toLowerCase(line).find(toLowerCase(deleteName)) == string::npos)
        {
            tempFile << line << endl;
        }
        else
        {
            deleted = true;
        }
    }

    readFile.close();
    tempFile.close();

    remove("data.txt");
    rename("temp.txt", "data.txt");

    if (deleted)
        cout << "Problem deleted successfully.\n";
    else
        cout << "Problem not found.\n";
}

void viewImportantProblems()
{
    ifstream file("data.txt");
    if (!file)
    {
        cout << "No data file found!\n";
        return;
    }

    string line;
    bool found = false;
    cout << "\n===== IMPORTANT PROBLEMS =====\n";
    while (getline(file, line))
    {
        if (toLowerCase(line).find("important") != string::npos)
        {
            cout << line << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No important problems found.\n";
    file.close();
}

void analytics()
{
    ifstream file("data.txt");
    if (!file)
    {
        cout << "No data found for analytics!\n";
        return;
    }

    string line;
    vector<Problem> problems;
    map<string, int> topicSolved, topicUnsolved;
    int total = 0, solved = 0, unsolved = 0;
    vector<string> importantProblems;

    while (getline(file, line))
    {
        stringstream ss(line);
        string name, platform, topic, difficulty, status, important;
        getline(ss, name, '|');
        getline(ss, platform, '|');
        getline(ss, topic, '|');
        getline(ss, difficulty, '|');
        getline(ss, status, '|');
        getline(ss, important, '|');

        name = trim(name);
        platform = trim(platform);
        topic = trim(topic);
        difficulty = trim(difficulty);
        status = trim(status);
        important = trim(important);

        Problem p = {name, platform, topic, difficulty, status, important};
        problems.push_back(p);

        total++;
        if (toLowerCase(status) == "solved")
        {
            solved++;
            topicSolved[topic]++;
        }
        else
        {
            unsolved++;
            topicUnsolved[topic]++;
        }

        if (toLowerCase(important) == "important")
        {
            importantProblems.push_back(name + " (" + topic + ")");
        }
    }

    cout << "\n===== ANALYTICS =====\n";
    cout << "Total Problems: " << total << "\n";
    cout << "Solved: " << solved << "\n";
    cout << "Unsolved: " << unsolved << "\n\n";

    cout << "Topics Covered:\n";
    for (auto &t : topicSolved)
    {
        double totalTopic = t.second + topicUnsolved[t.first];
        double perc = ((double)t.second / totalTopic) * 100;

        cout << "- " << t.first << ": "
             << t.second << " solved / "
             << topicUnsolved[t.first]
             << " unsolved ("
             << fixed << setprecision(1)
             << perc << "% solved)\n";
    }

    cout << "\nImportant Problems:\n";
    for (auto &ip : importantProblems)
    {
        cout << ip << endl;
    }

    file.close();
}

int main()
{
    int choice;

    while (true)
    {
        cout << "\n===== DSA PRACTICE TRACKER =====\n";
        cout << "1. Add new problem\n";
        cout << "2. View all problems\n";
        cout << "3. Search problem\n";
        cout << "4. Delete problem\n";
        cout << "5. View IMPORTANT problems\n";
        cout << "6. Analytics\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addProblem();
            break;
        case 2:
            viewProblems();
            break;
        case 3:
            searchProblem();
            break;
        case 4:
            deleteProblem();
            break;
        case 5:
            viewImportantProblems();
            break;
        case 6:
            analytics();
            break;
        case 7:
            cout << "Exiting program. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
