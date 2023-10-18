#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>
#include <filesystem>
#include <chrono>

using namespace std;

struct Student {
    string firstName;
    string lastName;
    vector<int> homeworkGrades;
    int exam;
    double avg;
    double med;
};

vector<Student> readStudentData(const string& filename) {
    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error: Unable to open the file: " << filename << endl;
        exit(1);
    }

    vector<Student> students;


    string header;
    getline(inputFile, header);


    string firstName, lastName;
    int exam;
    vector<int> homeworkGrades;

    while (inputFile >> firstName >> lastName) {
        homeworkGrades.clear(); // Clear the previous homework grades
        int grade;


        for (int i = 0; i < 7; ++i) {
            inputFile >> grade;
            homeworkGrades.push_back(grade);
        }


        inputFile >> exam;


        students.push_back({ firstName, lastName, homeworkGrades, exam });
    }

    inputFile.close();
    return students;
}

int generateRandomNumber(int n, int n1) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(n, n1);
    return dis(gen);
}

void generateStudents(int numStudents, vector<Student>& students) {
    students.resize(numStudents);

    for (int i = 0; i < numStudents; ++i) {
        students[i].firstName = "Vardas" + to_string(i);
        students[i].lastName = "Pavarde" + to_string(i);

        for (int j = 0; j < 7; ++j) {
            students[i].homeworkGrades.push_back(rand() % 10 + 1); // Random grade between 1 and 10
        }

        students[i].exam = rand() % 10 + 1; // Random exam grade between 1 and 10
    }
}

void saveStudentsToFile(const vector<Student>& students, const string& fileName) {
    ofstream file(fileName);
    file << setw(10) << "Vardas" << setw(10) << "Pavarde";
    for (int j = 1; j <= 7; ++j) {
        file << setw(10) << "ND" + to_string(j);
    }
    file << setw(10) << "Egz." << endl;

    for (const Student& student : students) {
        file << setw(10) << student.firstName << setw(10) << student.lastName;
        for (int grade : student.homeworkGrades) {
            file << setw(10) << grade;
        }
        file << setw(10) << student.exam << endl;
    };
}

void separateStudentsByAverage(const std::vector<Student>& students, std::vector<Student>& badStudents, std::vector<Student>& goodStudents) {
    for (const Student& student : students) {
        if (student.avg < 5) {
            badStudents.push_back(student);
        }
        else {
            goodStudents.push_back(student);
        }
    }
}

#endif
