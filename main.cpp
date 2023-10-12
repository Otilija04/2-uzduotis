#include "Library.h"

bool compareByName(const Student& a, const Student& b) {
	return a.firstName < b.firstName;
}

void sortStudents(vector<Student> group) {
	sort(group.begin(), group.end(), compareByName);
}

void printResult(int choice, const Student& student) {
	cout << left << setw(15) << student.firstName << setw(15) << student.lastName << fixed
		<< setprecision(2);

	try {
		switch (choice) {
		case 1:
			cout << student.avg;
			break;
		case 2:
			cout << student.med;
			break;
		default:
			throw ("nepalaikomas pasirinkimas");
		}
	}
	catch (const char* msg) {
		cout << msg;
		exit(1);
	}

	cout << endl;
};

void populateGradesManual(Student& student) {
	int gradesCount;

	cout << "Kiek ND pazymiu turi studentas? ";
	cin >> gradesCount;

	for (int i = 0; i < gradesCount; i++) {
		int grade;
		cout << "Iveskite " << i + 1 << " ND pazymi: ";
		cin >> grade;
		student.homeworkGrades.push_back(grade);
	}
	cout << "Iveskite egzamino rezultata: ";
	cin >> student.exam;
}

void populateGradesRandom(Student& student) {
	int gradesCount = generateRandomNumber(1, 15);

	for (int i = 0; i < gradesCount; i++) {
		int grade = generateRandomNumber(1, 10);
		student.homeworkGrades.push_back(grade);
	}

	student.exam = generateRandomNumber(1, 10);
}

void addAvarageAndMedian(Student& student) {
	double sum = 0;
	for (int i = 0; i < student.homeworkGrades.size(); i++) {
		sum += student.homeworkGrades[i];
	}
	double avg = sum / student.homeworkGrades.size();

	student.avg = 0.4 * avg + 0.6 * student.exam;

	student.med =
		0.4 * calculateMedian(student.homeworkGrades) + 0.6 * student.exam;

	student.homeworkGrades.clear();
}

void populateStudent(vector<Student>& students) {
	Student student;
	int choice;

	cout << "Iveskite varda: ";
	cin >> student.firstName;
	cout << "Iveskite pavarde: ";
	cin >> student.lastName;

	cout << "Pasirinkite kaip generuoti pazymius ir egzamina : 1 - Atsitiktinai, 2 - Rankiniu budu:";
	cin >> choice;

	try {
		switch (choice) {
		case 1:
			populateGradesRandom(student);
			break;
		case 2:
			populateGradesManual(student);
			break;
		default:
			throw ("nepalaikomas pasirinkimas");
		}
	}
	catch (const char* msg) {
		cout << msg;
		exit(1);
	}

	addAvarageAndMedian(student);
	students.push_back(student);
}

void populateFromFile(vector<Student>& students) {
	students = readStudentData("kursiokai.txt");
	for (Student& student : students) {
		addAvarageAndMedian(student);
	}
};

void populateManual(vector<Student>& students) {
	int studentCount;
	cout << "Iveskite, kiek studentu duomenis norite ivesti: ";
	cin >> studentCount;

	for (int j = 0; j < studentCount; j++) {
		populateStudent(students);
	}
};


int main() {
	int readChoice;

	cout << "Pasirinkite studentu irasyma: 1 - Irasyti is kursiokai.txt, 2 - Irasyti rankomis: ";
	cin >> readChoice;

	vector<Student> students;
	try {
		switch (readChoice) {
		case 1:
			populateFromFile(students);
			break;
		case 2:
			populateManual(students);
			break;
		default:
			throw ("nepalaikomas pasirinkimas");
		}
	}
	catch (const char* msg) {
		cout << msg;
		exit(1);
	}

	sortStudents(students);

	int resultTypeChoice;
	cout << "Pasirinkite rezultato tipa: 1 - Vidurkis, 2 - Mediana: ";
	cin >> resultTypeChoice;

	string label = (resultTypeChoice == 1) ? "Galutinis (Vid.)" : "Galutinis (Med.)";

	cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15)
		<< label << endl;

	for (const auto& student : students) {
		printResult(resultTypeChoice, student);
	}

	system("pause");

	return 0;
}
