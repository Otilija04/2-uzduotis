#include "Library.h"
#include <chrono>

int main() {
	int numStudents[] = { 1000, 10000, 100000, 1000000, 10000000 };
	vector<Student> students;

	for (int i = 0; i < 5; ++i) {
		cout << numStudents[i] << " studentu spartos analize:" << "\n";

		auto fileCreateStart = chrono::high_resolution_clock::now();

		generateStudents(numStudents[i], students);
		saveStudentsToFile(students, "kursiokai" + to_string(numStudents[i]) + ".txt");

		auto fileCreateEnd = chrono::high_resolution_clock::now();
		chrono::duration<double> fileCreateDuration = fileCreateEnd - fileCreateStart;
		cout << "studentu kurimas uztruko " << fileCreateDuration.count() << " sec." << endl;




		auto fileReadStart = chrono::high_resolution_clock::now();

		readStudentData("kursiokai" + to_string(numStudents[i]) + ".txt");

		auto fileReadEnd = chrono::high_resolution_clock::now();
		chrono::duration<double> fileReadDuration = fileReadEnd - fileReadStart;
		cout << "studentu nuskaitymas uztruko " << fileReadDuration.count() << " sec." << endl;



		auto fileSortStart = chrono::high_resolution_clock::now();

		for (Student& student : students) {
			int sum = 0;
			for (int grade : student.homeworkGrades) {
				sum += grade;
			}
			student.avg = static_cast<double>(sum) / student.homeworkGrades.size();
		}

		vector<Student> badStudents, goodStudents;
		separateStudentsByAverage(students, badStudents, goodStudents);

		auto fileSortEnd = chrono::high_resolution_clock::now();
		chrono::duration<double> fileSortDuration = fileSortEnd - fileSortStart;
		cout << "studentu rusiavimas i dvi grupes uztruko " << fileSortDuration.count() << " sec." << endl;




		auto fileSaveStart = chrono::high_resolution_clock::now();

		saveStudentsToFile(badStudents, "badstudents" + std::to_string(numStudents[i]) + ".txt");
		saveStudentsToFile(goodStudents, "goodstudents" + std::to_string(numStudents[i]) + ".txt");

		auto fileSaveEnd = chrono::high_resolution_clock::now();
		chrono::duration<double> fileSaveDuration = fileSaveEnd - fileSaveStart;
		cout << "studentu idejimas i du naujus failus uztruko " << fileSaveDuration.count() << " sec." << endl << "\n\n";




		students.clear();
	}

	return 0;
}
