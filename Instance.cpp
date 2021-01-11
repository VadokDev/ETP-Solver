#include <bits/stdc++.h>
#include "Instance.h"

using namespace std;

void Instance::loadExams() {
	char buff[256];

	ifstream exmFile(instancesDir + name + ".exm");
	if (!exmFile.is_open()) {
		throw 20;
	}

	while(exmFile.getline(buff, 255)) {
		if(isdigit(buff[0])) E++;
	}

	exmFile.close();
	cout << "[" << name << "] " << "Loaded " << E << " exams" << '\n';
}

void Instance::genConflictMatrix() {
	cMatrix.resize(E + 1);
	for (int i = 0; i < E + 1; ++i) {
		cMatrix[i].resize(E + 1);
	}
}

void Instance::loadStudents() {
	char buff[256];
	int lastStu, exm, stu = 1, cTotal = 0;

	vi exams(E);
	sExams.push_back(exams);

	ifstream stuFile(instancesDir + name + ".stu");
	if (!stuFile.is_open()) {
		throw 20;
	}

	cin.rdbuf(stuFile.rdbuf());

	while(cin >> buff >> exm) {
		A++;
		lastStu = stu;
		stu = atoi(&buff[1]);

		if(exm > E) {
			exm = 1;
 		}
 		
		if(lastStu != stu) {
			vi studentExams(cTotal);
			
			if(cTotal > L)
				L = cTotal;

			for (int i = 0; i < cTotal; ++i) {
				for (int j = 0; j < cTotal; ++j) {
					if(i == j)
						continue;

					cMatrix[exams[i]][exams[j]] += 1;
				}
				studentExams[i] = exams[i];
			}

			sExams.push_back(studentExams);
			cTotal = 0;
		}

		exams[cTotal++] = exm;
	}

	vi studentExams(cTotal);

	for (int i = 0; i < cTotal; ++i) {
		for (int j = 0; j < cTotal; ++j) {
			if(i == j)
				continue;

			cMatrix[exams[i]][exams[j]] += 1;
		}
		studentExams[i] = exams[i];
	}

	sExams.push_back(studentExams);
	
	if(cTotal > L)
		L = cTotal;

	stuFile.close();
	S = stu;
	cout << "[" << name << "] " << "Loaded " << stu << " students" << '\n';
}

void Instance::showStudentExams() {
	for (int i = 1; i < S + 1; ++i)	{
		cout << "Student " << i << " exams: ";
		for (size_t j = 0; j < sExams[i].size(); ++j) {
			cout << sExams[i][j] << " ";
		}
		cout << '\n';
	}
}

void Instance::showConflictMatrix() {
	for (int i = 1; i < E + 1; ++i) {
		for (int j = 1; j < E + 1; ++j) {
			cout << cMatrix[i][j] << " ";
		}
		cout << '\n';
	}
}

int Instance::countConflicts() {
	int conflicts = 0;
	for (int i = 0; i < E + 1; ++i) {
		for (int j = 0; j < E + 1; ++j) {
			if(i == j)
				continue;

			if(cMatrix[i][j])
				conflicts++;
		}
	}

	return conflicts / 2;
}

Instance::Instance(std::string instanceName) {
	instancesDir = INSTANCES_DIRECTORY;
	name = instanceName;
	S = A = L = E = 0;
}

Instance::~Instance() {
}
