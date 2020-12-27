#include <bits/stdc++.h>
#include "Instance.h"
#include "FcSolver.h"

using namespace std;

int main(int argc, char const *argv[]) {
	/*
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.setf(ios::fixed);
	cout.precision(5);
*/
	Instance etp(argv[1]);
	etp.loadExams();
	etp.genConflictMatrix();
	etp.loadStudents();
	//etp.showConflictMatrix();
	//etp.showStudentExams();

	FcSolver solver(&etp);
	solver.doBackTracking(1);

	return 0;
}

