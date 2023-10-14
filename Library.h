

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

using namespace std;

struct Student {
    string firstName;
    string lastName;
    vector<int> homeworkGrades;
    int exam;
    double avg;
    double med;
};
double calculateMedian(vector<int>& grades) {
    size_t n = grades.size();
    if (n == 0) {
        return 0.0;
    }

    sort(grades.begin(), grades.end());

    if (n % 2 == 0) {
        
        return (grades[n / 2 - 1] + grades[n / 2]) / 2.0;
    } else {
       
        return grades[n / 2];
    }
}

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

       
        students.push_back({firstName, lastName, homeworkGrades, exam});
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

void generateStudents(int numStudents, std::vector<Student>& students) {
    students.resize(numStudents);

    for (int i = 0; i < numStudents; ++i) {
        students[i].firstName = "Vardas" + std::to_string(i);
        students[i].lastName = "Pavarde" + std::to_string(i);

        for (int j = 0; j < 7; ++j) {
            students[i].homeworkGrades.push_back(rand() % 10 + 1); // Random grade between 1 and 10
        }

        students[i].exam = rand() % 10 + 1; // Random exam grade between 1 and 10
    }
}

void saveStudentsToFile(const std::vector<Student>& students, int numStudents) {
    std::ofstream file("kursiokai" + std::to_string(numStudents) + ".txt");
    file << std::setw(10) << "Vardas" << std::setw(10) << "Pavarde";
    for (int j = 1; j <= 7; ++j) {
        file << std::setw(10) << "ND" + std::to_string(j);
    }
    file << std::setw(10) << "Egz." << std::endl;

    for (const Student& student : students) {
        file << std::setw(10) << student.firstName << std::setw(10) << student.lastName;
        for (int grade : student.homeworkGrades) {
            file << std::setw(10) << grade;
        }
        file << std::setw(10) << student.exam << std::endl;
    }
}

#endif 
