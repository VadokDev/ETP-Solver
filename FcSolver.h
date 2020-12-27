#ifndef FCSOLVER_H
#define FCSOLVER_H

#include <vector>
#include <string>
#include <Instance.h>

class FcSolver {
	private:
		Instance* inst;
		vii D;
		vi sol;
		vi bestSol;
		vi examPositions;
		int bestSolPenalty;
	public:
		FcSolver(Instance* instance);
		~FcSolver();
		bool compareExams(int e1, int e2);
		int isAssignable(int exm, int slot);
		int doForwardChecking(int exm);
		void resetDomains(int actualExm);
		void checkSolution();
		void doBackTracking(int actualExm);
		void showDomains();
		int examsPenalization(int e1, int e2);
		int getSolutionPenalty();
};

#endif