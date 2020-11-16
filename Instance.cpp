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
		if(isdigit(buff[0])) L = ++E;
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
	ifstream stuFile(instancesDir + name + ".stu");
	if (!stuFile.is_open()) {
		throw 20;
	}

	cin.rdbuf(stuFile.rdbuf());

	while(cin >> buff >> exm) {
		lastStu = stu;
		stu = atoi(&buff[1]);
		//cout << "Stu: " << stu << " " << exm << '\n';
		if(exm > E) {
			cout << "exm > E " << exm << '\n';
 		}
		if(lastStu != stu) {
			for (int i = 0; i < cTotal; ++i) {
				for (int j = 0; j < cTotal; ++j) {
					if(i == j)
						continue;

					cMatrix[exams[i]][exams[j]] += 1;
				}
			}

			cTotal = 0;
		}

		exams[cTotal++] = exm;
	}

	stuFile.close();
	cout << "[" << name << "] " << "Loaded " << stu << " students" << '\n';
}

void Instance::showConflictsMatrix() {
	for (int i = 0; i < E + 1; ++i) {
		for (int j = 0; j < E + 1; ++j) {
			if(cMatrix[i][j] != 0)
				cout << cMatrix[i][j] << " ";
		}
		cout << '\n';
	}
}

Instance::Instance(std::string instanceName) {
	name = instanceName;
	E = L = 0;
}

Instance::~Instance() {
}
