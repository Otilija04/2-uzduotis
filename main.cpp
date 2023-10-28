#include "lib.h"
#include <chrono>
#include <fstream>

bool fileExists(const std::string& fileName) {
    std::ifstream file(fileName.c_str());
    return file.good();
}

void generateAndSaveStudents(int numStudents, const std::string& fileName, double& fileCreateDuration) {
    if (!fileExists(fileName)) {
        std::vector<Student> students;

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
    std::vector<Student> students = readStudentData(fileName);

    auto fileSortStart = std::chrono::high_resolution_clock::now();

    for (Student& student : students) {
        int sum = 0;
        for (int grade : student.homeworkGrades) {
            sum += grade;
        }
        student.avg = static_cast<double>(sum) / student.homeworkGrades.size();
    }

    std::vector<Student> badStudents, goodStudents;
    separateStudentsByAverage(students, badStudents, goodStudents);

    auto fileSortEnd = std::chrono::high_resolution_clock::now();
    fileSortDuration = std::chrono::duration<double>(fileSortEnd - fileSortStart).count();

    std::cout << "studentu rusiavimas i dvi grupes uztruko " << fileSortDuration << " sec." << std::endl;

    auto fileReadEnd = std::chrono::high_resolution_clock::now();
    fileReadDuration = std::chrono::duration<double>(fileReadEnd - fileReadStart).count();
    std::cout << "studentu nuskaitymas uztruko " << fileReadDuration << " sec." << std::endl;

    saveStudentsToFile(badStudents, "bad" + fileName);
    saveStudentsToFile(goodStudents, "good" + fileName);
}

int main() {
    int numStudents[] = {1000, 10000, 100000, 1000000, 10000000};

    for (int i = 0; i < 5; ++i) {
        std::string fileName = "kursiokai" + std::to_string(numStudents[i]) + ".txt";
        std::cout << numStudents[i] << " studentu spartos analize:" << "\n";

        double fileCreateDuration, fileReadDuration, fileSortDuration;
        generateAndSaveStudents(numStudents[i], fileName, fileCreateDuration);
        readAndProcessStudents(fileName, fileReadDuration, fileSortDuration);

        std::cout << "studentu idejimas i du naujus failus uztruko " << fileCreateDuration + fileSortDuration + fileReadDuration << " sec." << std::endl;
        std::cout << "\n\n";
    }

    return 0;
}
