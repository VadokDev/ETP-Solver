#include <bits/stdc++.h>
#include "FcSolver.h"

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

FcSolver::FcSolver(Instance* instance) {
	inst = instance;
	bestSolPenalty = INT_MAX;
	sol.resize(inst->E + 1);
	sol.resize(inst->E + 1);
	bestSol.resize(inst->E + 1);
	D.resize(inst->E + 1);
	for (int i = 0; i < inst->E + 1; ++i) {
		D[i].resize(inst->E + 1);
	}
}

FcSolver::~FcSolver() {

}

int FcSolver::doForwardChecking(int exm) {
	int remain = 0;
	//cout << "Start Forward Checking from Exam: " << exm << '\n';  
	for (int i = exm + 1; i < inst->E + 1; ++i) {
		//cout << "Exam: " << i << '\n';  
		//showDomains();
		//cout << "..." << '\n';
		
		//if(D[i][sol[exm]])
		//	continue;

		if(inst->cMatrix[exm][i] && !D[i][sol[exm]]) {
			D[i][sol[exm]] = exm;
			//cout << "Removed " << sol[exm] << " from Exam " << i << " by " << exm << '\n';
			//continue;
		}

		remain += count(D[i].begin(), D[i].end(), 0);
	}

	//cout << "Final Domains: " << '\n';
	showDomains();
	//cout << "End Forward Checking from Exam: " << exm << '\n';  

	return remain;
}

void FcSolver::resetDomains(int actualExm) {
	for (int i = actualExm + 1; i < inst->L + 1; ++i) {
		//cout << "Exam " << i << " domain reset" << " by " << actualExm << '\n';
		replace(D[i].begin(), D[i].end(), actualExm, 0);
	}
}

void FcSolver::checkSolution() {
/*
	cout << "-------------" << '\n';
	for (int i = 1; i < inst->L + 1; ++i) {
		cout << sol[i] << " ";
	}
	cout << '\n';
*/

	int pen = getSolutionPenalty();
	if(bestSolPenalty > pen) {
		for (int i = 1; i < inst->L + 1; ++i) {
			bestSol[i] = sol[i];
			bestSolPenalty = pen / inst->S;
		}

		cout << "-------------" << '\n';
		for (int i = 1; i < inst->L + 1; ++i) {
			cout << sol[i] << " ";
		}
		cout << '\n';

		cout << "penalización: " << pen << '\n';
		cout << "promedio: " << pen / inst->S << '\n';
	}
	
}

int FcSolver::getSolutionPenalty() {
	int penaltyTotal = 0;
/*
	for (int i = 1; i < inst->E + 1; ++i) {
		sol[sol[i]] = i;
	}
*/
	for (int i = 1; i < inst->S + 1; ++i) {
		sort(inst->sExams[i].begin(), inst->sExams[i].end(), [this](int e1, int e2) -> bool {
			return this->compareExams(e1, e2);
		});
		
/*
		cout << "Student " << i << " exams: ";
		for (size_t j = 0; j < inst->sExams[i].size(); ++j) {
			cout << inst->sExams[i][j] << " ";

		}
		cout << '\n';
*/
		for (size_t j = 1; j < inst->sExams[i].size(); ++j) {
			penaltyTotal += examsPenalization(inst->sExams[i][j - 1], inst->sExams[i][j]);
		}
		

	}

	return penaltyTotal;
}

int FcSolver::examsPenalization(int e1, int e2) {
	int diff = sol[e2] - sol[e1];
	//cout << e2 << " " << e1 << " - " << sol[e2] << " " << sol[e1] << " | ";
	if(diff == 0) 		return 0;
	else if(diff == 1)	return 16;
	else if(diff == 2)	return 8;
	else if(diff == 3)	return 4;
	else if(diff == 4)	return 2;
	else if(diff == 5)	return 1;
	
	return 0;
}

bool FcSolver::compareExams(int e1, int e2) {
	return sol[e1] < sol[e2];
}

void FcSolver::showDomains() {
	for (int i = 1; i < inst->E + 1; ++i) {
		//cout << "Examen [" << i << "]: ";
		for (int j = 1; j < inst->E + 1; ++j) {
			if(!D[i][j]) {
				//cout << j;
				if(j != inst->E) {
					//cout << " - ";
				}
			}

		}
		//cout << " ";
	}
	//cout << '\n';
}

void FcSolver::doBackTracking(int exm) {
		for (int slot = 1; slot < inst->L + 1; ++slot) {
			if(D[exm][slot])
				continue;

			//showDomains();
			sol[exm] = slot;
			//cout << "BT EXM: " << exm << " Assigned: " << slot << '\n';

			if(exm == inst->E) {
				checkSolution();
				continue;
			} 

			if(!doForwardChecking(exm)) {
				//cout << "No available domains" << '\n';
				
				continue;
			}

			doBackTracking(exm + 1);
			resetDomains(exm);
		}
}