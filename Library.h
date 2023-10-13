

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

    // Read and discard the header line
    string header;
    getline(inputFile, header);

    // Read data for each student
    string firstName, lastName;
    int exam;
    vector<int> homeworkGrades;

    while (inputFile >> firstName >> lastName) {
        homeworkGrades.clear(); // Clear the previous homework grades
        int grade;

        // Read the homework grades
        for (int i = 0; i < 7; ++i) {
            inputFile >> grade;
            homeworkGrades.push_back(grade);
        }

        // Read the exam grade
        inputFile >> exam;

        // Create a Student struct and add it to the vector
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


#endif /* LIBRARY_H */
