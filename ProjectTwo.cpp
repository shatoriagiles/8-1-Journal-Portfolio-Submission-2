#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Course {
    string id;
    string name;
    vector<string> prereq;
};

vector<Course> courseList;

void loadFile(string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    courseList.clear();
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course c;

        getline(ss, c.id, ',');
        getline(ss, c.name, ',');

        while (getline(ss, token, ',')) {
            c.prereq.push_back(token);
        }

        courseList.push_back(c);
    }

    cout << "File loaded successfully" << endl;
}

void printCourses() {
    if (courseList.empty()) {
        cout << "No data loaded" << endl;
        return;
    }

    vector<Course> temp = courseList;

    sort(temp.begin(), temp.end(), [](Course a, Course b) {
        return a.id < b.id;
    });

    for (auto c : temp) {
        cout << c.id << ", " << c.name << endl;
    }
}

Course* findCourse(string id) {
    for (auto &c : courseList) {
        if (c.id == id) {
            return &c;
        }
    }
    return nullptr;
}

void printCourseInfo() {
    if (courseList.empty()) {
        cout << "No data available" << endl;
        return;
    }

    string id;
    cout << "Enter course id: ";
    cin >> id;

    Course* c = findCourse(id);

    if (c == nullptr) {
        cout << "Course not found" << endl;
        return;
    }

    cout << c->id << ", " << c->name << endl;

    if (c->prereq.size() == 0) {
        cout << "No prerequisites" << endl;
    } else {
        cout << "Prerequisites: ";
        for (int i = 0; i < c->prereq.size(); i++) {
            cout << c->prereq[i];
            if (i < c->prereq.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

int main() {
    int choice = 0;
    string fileName;

    while (choice != 9) {
        cout << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter file name: ";
            cin >> fileName;
            loadFile(fileName);
        } else if (choice == 2) {
            printCourses();
        } else if (choice == 3) {
            printCourseInfo();
        } else if (choice == 9) {
            cout << "Exiting program" << endl;
        } else {
            cout << "Invalid option" << endl;
        }
    }

    return 0;
}