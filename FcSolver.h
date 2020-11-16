#ifndef FCSOLVER_H
#define FCSOLVER_H

#include <vector>
#include <string>
#include <Instance.h>

typedef std::vector<bool> vb;
typedef std::vector<vb> vbb;

class FcSolver {
	private:
		Instance* inst;
		vbb D;
		vb sol;

	public:
		FcSolver(Instance* instance);
		~FcSolver();
		int isAssignable(int exm, int slot);
		int doForwardChecking(int exm);
		void resetDomains(int actualExm);
		void checkSolution();
		void doBackTracking(int actualExm);
};

#endif