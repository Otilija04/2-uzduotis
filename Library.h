#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <list>
#include <iomanip>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>
#include <filesystem>
#include <chrono>

class Student {
public:
    std::string firstName;
    std::string lastName;
    std::list<int> homeworkGrades;
    int exam;
    double avg;
    double med;
};

std::list<Student> readStudentData(const std::string& filename);

int generateRandomNumber(int n, int n1);

void generateStudents(int numStudents, std::list<Student>& students);

void saveStudentsToFile(const std::list<Student>& students, const std::string& fileName);

void separateStudentsByAverage(const std::list<Student>& students, std::list<Student>& badStudents, std::list<Student>& goodStudents);

#endif 
