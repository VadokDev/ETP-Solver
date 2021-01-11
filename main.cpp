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

    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.setf(ios::fixed);
    cout.precision(4);

	bool showLogs = (bool) stoi(argv[2]);

	// Cargar instancia
	Instance etp(argv[1]);
	etp.loadExams();
	etp.genConflictMatrix();
	etp.loadStudents();
	
	//etp.countConflicts();
	//etp.showConflictMatrix();
	//etp.showStudentExams();

	// Resolver instancia
	FcSolver solver(&etp, showLogs);
	solver.doMaxTimeSlotsAdjustment();
	solver.writeStatsToJson();
	return 0;
}

