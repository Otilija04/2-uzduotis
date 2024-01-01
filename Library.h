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

// isankstine deklaracija person klases
class Person;

// Abstrakti Person klase
class Person {
public:
    std::string firstName;
    std::string lastName;

    // konstruktorius
    Person() {}
    Person(const std::string& first, const std::string& last) : firstName(first), lastName(last) {}

    
    virtual ~Person() {}
};

class Student : public Person {
public:
    std::list<int> homeworkGrades;
    int exam;
    double avg;
    double med;

    // konstruktoriai
    Student() : exam(0), avg(0.0), med(0.0) {}
    Student(const std::string& first, const std::string& last, const std::list<int>& grades, int e, double a, double m)
        : Person(first, last), homeworkGrades(grades), exam(e), avg(a), med(m) {}
};

std::list<Student> readStudentData(const std::string& filename);

int generateRandomNumber(int n, int n1);

void generateStudents(int numStudents, std::list<Student>& students);

void saveStudentsToFile(const std::list<Student>& students, const std::string& fileName);

void saveStudentsToFile2(const std::list<Student>& students, const std::string& fileName);

void separateStudentsByAverage(const std::list<Student>& students, std::list<Student>& badStudents, std::list<Student>& goodStudents);

#endif
