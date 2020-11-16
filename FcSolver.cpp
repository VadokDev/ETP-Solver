#include <bits/stdc++.h>
#include "FcSolver.h"

using namespace std;

FcSolver::FcSolver() {

}

FcSolver::~FcSolver() {
}

void doForwardChecking(int exm) {

}

void resetDomains(int actualExm) {
	for (int i = actualExm + 1; i < D.size(); ++i) {
		fill(D[i].begin(), D[i].end(), 0);
	}
}

void doBackTracking(int actualExm) {
	for (int exm = actualExm; exm < inst->E + 1; ++exm) {
		for (int slot = 0; slot < inst->L; ++slot) {
			if(D[exam][slot])
				continue;

			res[exm] = slot;

			if(!doForwardChecking(exm))
				continue;

			doBackTracking(exm + 1);
			resetDomains(actualExm);
		}
	}
}