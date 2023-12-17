#include "Library.h"

// Default constructor
Student::Student() : exam(0), avg(0.0), med(0.0) {
    // Additional initialization code if needed
}

// Parameterized constructor
Student::Student(const std::string& firstName, const std::string& lastName,
                 const std::list<int>& homeworkGrades, int exam)
    : firstName(firstName), lastName(lastName), homeworkGrades(homeworkGrades),
      exam(exam), avg(0.0), med(0.0) {
    // Additional initialization code if needed
}

// Copy constructor
Student::Student(const Student& other)
    : firstName(other.firstName),
      lastName(other.lastName),
      homeworkGrades(other.homeworkGrades),
      exam(other.exam),
      avg(other.avg),
      med(other.med) {
    // Additional initialization code if needed
}

// Copy assignment operator
Student& Student::operator=(const Student& other) {
    if (this != &other) { // Check for self-assignment
        firstName = other.firstName;
        lastName = other.lastName;
        homeworkGrades = other.homeworkGrades;
        exam = other.exam;
        avg = other.avg;
        med = other.med;
        // Additional assignment code if needed
    }
    return *this;
}

// Destructor
Student::~Student() {
    // Cleanup code if needed
}

std::list<Student> readStudentData(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error: Unable to open the file: " << filename << std::endl;
        exit(1);
    }

    std::list<Student> students;
    std::string header;
    getline(inputFile, header);

    std::string firstName, lastName;
    int exam;
    std::list<int> homeworkGrades;

    while (inputFile >> firstName >> lastName) {
        homeworkGrades.clear();
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(n, n1);
    return dis(gen);
}

void generateStudents(int numStudents, std::list<Student>& students) {
    for (int i = 0; i < numStudents; ++i) {
        students.push_back({ "Vardas" + std::to_string(i), "Pavarde" + std::to_string(i), {}, generateRandomNumber(1, 10) });
        for (int j = 0; j < 7; ++j) {
            students.back().homeworkGrades.push_back(generateRandomNumber(1, 10));
        }
    }
}

void saveStudentsToFile(const std::list<Student>& students, const std::string& fileName) {
    std::ofstream file(fileName);
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

void separateStudentsByAverage(const std::list<Student>& students, std::list<Student>& badStudents, std::list<Student>& goodStudents) {
    for (const Student& student : students) {
        if (student.avg < 5) {
            badStudents.push_back(student);
        }
        else {
            goodStudents.push_back(student);
        }
    }
}
