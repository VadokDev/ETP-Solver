#include <bits/stdc++.h>
#include "FcSolver.h"

using namespace std;

FcSolver::FcSolver(Instance* instance) {
	inst = instance;

	sol.resize(inst->E + 1);
	D.resize(inst->E + 1);
	for (int i = 0; i < inst->E + 1; ++i) {
		D[i].resize(inst->E + 1);
	}
}

FcSolver::~FcSolver() {

}

int FcSolver::doForwardChecking(int exm) {
	int remain = 0;

	for (int i = exm + 1; i < inst->E + 1; ++i) {
		if(D[i][sol[exm]])
			continue;

		if(inst->cMatrix[sol[exm]][i]) {
			D[i][sol[exm]] = 1;
			continue;
		}

		remain ++;
	}

	return remain;
}

void FcSolver::resetDomains(int actualExm) {
	for (int i = actualExm + 1; i < inst->L + 1; ++i) {
		fill(D[i].begin(), D[i].end(), 0);
	}
}

void FcSolver::checkSolution() {
	for (int i = 1; i < inst->L + 1; ++i) {
		cout << "Timeslot " << i << ": " << sol[i] << '\n';
	}
}

void FcSolver::doBackTracking(int actualExm) {
	for (int exm = actualExm; exm < inst->E + 1; ++exm) {
		for (int slot = 1; slot < inst->L + 1; ++slot) {
			if(D[exm][slot])
				continue;

			sol[exm] = slot;

			if(exm == inst->E) {
				break;
			}

			if(!doForwardChecking(exm))
				continue;

			doBackTracking(exm + 1);
			resetDomains(actualExm);
		}
	}
}