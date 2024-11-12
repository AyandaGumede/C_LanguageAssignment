#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

// Student Node
struct Student {
    int id;
    string name;
    string surname;
};

// Club Node
struct Club {
    string name;
    vector<Student*> members;
};

unordered_map<int, Student> students;
unordered_map<string, Club> clubs;

// Add a student to the system
void addStudent(int id, const string& name, const string& surname) {
    if (students.count(id)) {
        cout << "Error: Student already exists.\n";
        return;
    }
    students[id] = { id, name, surname };
    cout << "Student " << name << " " << surname << " added.\n";
}

// Add a new club
void createClub(const string& name) {
    if (clubs.count(name)) {
        cout << "Error: Club already exists.\n";
        return;
    }
    clubs[name] = { name };
    cout << "Club " << name << " created.\n";
}

// Add a student to a club
void addStudentToClub(int id, const string& clubName) {
    if (!students.count(id) || !clubs.count(clubName)) {
        cout << "Error: Student or club doesn't exist.\n";
        return;
    }
    clubs[clubName].members.push_back(&students[id]);
    cout << students[id].name << " added to " << clubName << ".\n";
}

// Remove student from a club
void removeStudentFromClub(int id, const string& clubName) {
    if (!clubs.count(clubName)) {
        cout << "Error: Club doesn't exist.\n";
        return;
    }
    auto& members = clubs[clubName].members;
    members.erase(remove_if(members.begin(), members.end(), [&](Student* s) { return s->id == id; }), members.end());
    cout << "Removed student from " << clubName << ".\n";
}

// Find clubs for a student
void findClubsOfStudent(int id) {
    if (!students.count(id)) {
        cout << "Error: Student not found.\n";
        return;
    }
    cout << "Clubs for " << students[id].name << ":\n";
    for (auto& pair : clubs) {
        if (any_of(pair.second.members.begin(), pair.second.members.end(), [&](Student* s) { return s->id == id; })) {
            cout << " - " << pair.first << "\n";
        }
    }
}

// Find students in a club
void findStudentsInClub(const string& clubName) {
    if (!clubs.count(clubName)) {
        cout << "Error: Club not found.\n";
        return;
    }
    cout << "Members of " << clubName << ":\n";
    for (auto* member : clubs[clubName].members) {
        cout << " - " << member->name << " " << member->surname << "\n";
    }
}

// Sort students by surname
void sortStudentsAlphabetically() {
    vector<Student*> list;
    for (auto& pair : students) {
        list.push_back(&pair.second);
    }
    sort(list.begin(), list.end(), [](Student* a, Student* b) { return a->surname < b->surname; });
    cout << "Students sorted by last name:\n";
    for (const auto* s : list) {
        cout << " - " << s->name << " " << s->surname << "\n";
    }
}

// Save system state to file
void saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "File error.\n";
        return;
    }
    file << "Students\n";
    for (const auto& pair : students) {
        file << pair.second.id << " " << pair.second.name << " " << pair.second.surname << "\n";
    }
    file << "Clubs\n";
    for (const auto& pair : clubs) {
        file << pair.first << "\n";
        for (auto* member : pair.second.members) {
            file << member->id << "\n";
        }
        file << "end\n";
    }
    cout << "Data saved to " << filename << "\n";
}

// Load system state from file
void loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "File error.\n";
        return;
    }
    students.clear();
    clubs.clear();
    string section;
    while (file >> section) {
        if (section == "Students") {
            int id;
            string first, last;
            while (file >> id >> first >> last) {
                students[id] = { id, first, last };
            }
            // Clear the error state for the file stream to continue reading
            file.clear();
        }
        else if (section == "Clubs") {
            string clubName;
            while (file >> clubName) {
                if (clubName == "end") break; 

                clubs[clubName] = { clubName };
                int memberId;
                while (file >> memberId) {
                    if (memberId == -1) break; 

                    if (students.count(memberId)) {
                        clubs[clubName].members.push_back(&students[memberId]);
                    }
                }
            }
            file.clear();
        }
    }
    cout << "Data loaded from " << filename << "\n";
}

// Display graph
void displayGraph() {
    cout << "Graph:\n";
    if (clubs.empty()) {
        cout << "No clubs found.\n";
    }
    for (const auto& clubPair : clubs) {
        cout << clubPair.first << " club members:\n";
        if (clubPair.second.members.empty()) {
            cout << " - No members in this club.\n";
        }
        for (const auto* member : clubPair.second.members) {
            cout << " - " << member->name << " " << member->surname << "\n";
        }
        cout << endl;
    }
}


int main() {
    addStudent(1, "Alice", "Smith");
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    addStudent(2, "Bob", "Brown");
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    createClub("Coding");
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    addStudentToClub(1, "Coding");
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    addStudentToClub(2, "Coding");
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    findClubsOfStudent(1);
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    findStudentsInClub("Coding");
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    sortStudentsAlphabetically();
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    saveToFile("data.txt");
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    loadFromFile("data.txt");
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;


    displayGraph();
    return 0;
}
