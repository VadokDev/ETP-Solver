#include <bits/stdc++.h>
#include "Instance.h"
#include "FcSolver.h"

using namespace std;

int main(int argc, char const *argv[]) {
	if(argc < 3) {
		cout << "[Main] " << "Error: Missing parameters" << '\n';
		cout << "[Main] " << "Execution example: ./ETPSolver InstanceName 1" << '\n';
		return 0;
	}

	bool showLogs = (bool) stoi(argv[2]);

	Instance etp(argv[1]);
	etp.loadExams();
	etp.genConflictMatrix();
	etp.loadStudents();
	//etp.showConflictMatrix();
	//etp.showStudentExams();

	FcSolver solver(&etp, showLogs);
	solver.doBackTracking(1);

	return 0;
}

