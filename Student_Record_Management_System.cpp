#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int roll;
    string name;
    string course;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();  // to clear newline from buffer
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() {
        cout << "Roll: " << roll << "\nName: " << name << "\nCourse: " << course << "\n";
        cout << "---------------------------\n";
    }
};

void addStudent() {
    Student s;
    ofstream fout("students.txt", ios::app);
    s.input();
    fout << s.roll << "," << s.name << "," << s.course << "\n";
    fout.close();
    cout << "✅ Student added successfully.\n";
}

void displayAll() {
    ifstream fin("students.txt");
    Student s;
    string line;
    bool found = false;

    while (getline(fin, line)) {
        found = true;
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        s.roll = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.course = line.substr(pos2 + 1);
        s.display();
    }

    if (!found) {
        cout << "⚠️ No student records found.\n";
    }

    fin.close();
}

void searchStudent() {
    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;

    ifstream fin("students.txt");
    Student s;
    string line;
    bool found = false;

    while (getline(fin, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        int r = stoi(line.substr(0, pos1));

        if (r == roll) {
            s.roll = r;
            s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            s.course = line.substr(pos2 + 1);
            cout << "✅ Student found:\n";
            s.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "❌ Student not found.\n";
    }

    fin.close();
}

void deleteStudent() {
    int roll;
    cout << "Enter roll number to delete: ";
    cin >> roll;

    ifstream fin("students.txt");
    ofstream temp("temp.txt");
    string line;
    bool deleted = false;

    while (getline(fin, line)) {
        size_t pos1 = line.find(",");
        int r = stoi(line.substr(0, pos1));

        if (r == roll) {
            deleted = true;
            continue;  // skip writing this record
        }
        temp << line << "\n";
    }

    fin.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (deleted) {
        cout << "✅ Student deleted successfully.\n";
    } else {
        cout << "❌ Student not found.\n";
    }
}

void updateStudent() {
    int roll;
    cout << "Enter roll number to update: ";
    cin >> roll;

    ifstream fin("students.txt");
    ofstream temp("temp.txt");
    string line;
    bool updated = false;
    Student s;

    while (getline(fin, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        int r = stoi(line.substr(0, pos1));

        if (r == roll) {
            cout << "Enter new details:\n";
            s.input();
            temp << s.roll << "," << s.name << "," << s.course << "\n";
            updated = true;
        } else {
            temp << line << "\n";
        }
    }

    fin.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (updated) {
        cout << "✅ Student updated successfully.\n";
    } else {
        cout << "❌ Student not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n🎓 Student Record Management System\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: displayAll(); break;
        case 3: searchStudent(); break;
        case 4: deleteStudent(); break;
        case 5: updateStudent(); break;
        case 6: cout << "👋 Exiting...\n"; break;
        default: cout << "❌ Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
