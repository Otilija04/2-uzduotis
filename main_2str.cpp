#include "Library.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>

bool fileExists(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.good();
}

void generateAndSaveStudents(int numStudents, const std::string& fileName, double& fileCreateDuration) {
    if (!fileExists(fileName)) {
        std::list<Student> students;

        auto fileCreateStart = std::chrono::high_resolution_clock::now();
        generateStudents(numStudents, students);
        saveStudentsToFile(students, fileName);
        auto fileCreateEnd = std::chrono::high_resolution_clock::now();
        fileCreateDuration = std::chrono::duration<double>(fileCreateEnd - fileCreateStart).count();
        std::cout << "studentu kurimas uztruko " << fileCreateDuration << " sec." << std::endl;
    } else {
        std::cout << "File " << fileName << " already exists. Skipping generation." << std::endl;
        fileCreateDuration = 0.0; 
    }
}

void readAndProcessStudents(const std::string& fileName, double& fileReadDuration, double& fileSortDuration) {
    auto fileReadStart = std::chrono::high_resolution_clock::now();
    std::list<Student> students;  

    students = readStudentData(fileName);
    auto fileReadEnd = std::chrono::high_resolution_clock::now();
    fileReadDuration = std::chrono::duration<double>(fileReadEnd - fileReadStart).count();
    std::cout << "studentu nuskaitymas uztruko " << fileReadDuration << " sec." << std::endl;

    auto fileSortStart = std::chrono::high_resolution_clock::now();
    for (auto it = students.begin(); it != students.end(); ++it) {
        int sum = 0;
        for (int grade : it->homeworkGrades) {
            sum += grade;
        }
        it->avg = static_cast<double>(sum) / it->homeworkGrades.size();
    }

    std::list<Student> badStudents, goodStudents;

    for (auto it = students.begin(); it != students.end();) {
        if (it->avg < 5) {
            badStudents.push_back(*it);
            it = students.erase(it);  // Remove from the original list
        } else {
            ++it;
        }
    }

    auto fileSortEnd = std::chrono::high_resolution_clock::now();
    fileSortDuration = std::chrono::duration<double>(fileSortEnd - fileSortStart).count();
    std::cout << "studentu rusiavimas ir trynimas uztruko " << fileSortDuration << " sec." << std::endl;

    saveStudentsToFile(badStudents, "bad" + fileName);
    saveStudentsToFile(students, fileName);
}

int main() {
    int numStudents[] = {1000, 10000, 100000, 1000000, 10000000};
    int numTests = 5;  

    for (int i = 0; i < numTests; ++i) {
        std::string fileName = "kursiokai" + std::to_string(numStudents[i]) + ".txt";
        std::cout << numStudents[i] << " studentu spartos analize:" << "\n";

        double avgFileCreateDuration = 0.0;
        double avgFileReadDuration = 0.0;
        double avgFileSortDuration = 0.0;

        generateAndSaveStudents(numStudents[i], fileName, avgFileCreateDuration);
        readAndProcessStudents(fileName, avgFileReadDuration, avgFileSortDuration);

        avgFileReadDuration /= numTests;
        avgFileSortDuration /= numTests;

        std::cout << "Vidutine failo nuskaitymo trukme: " << avgFileReadDuration << " sec." << std::endl;
        std::cout << "Vidutine rusiavimo ir trynimo trukme: " << avgFileSortDuration << " sec." << std::endl;

        std::cout << "\n\n";
    }

    return 0;
}
