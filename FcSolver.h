#ifndef FCSOLVER_H
#define FCSOLVER_H

#include <vector>
#include <string>
#include <Instance.h>

class FcSolver {
	private:
		Instance* inst;				// Instancia a resolver
		vii D;						// Matriz de horarios disponibles para asignar a los exámenes
		vi sol;						// Solución actual del backtracking
		vi bestSol;					// Mejor solución encontrada durante el proceso
		int bestSolPenalty;			// Penalización asociada a la mejor solución encontrada
		int totalSols;				// Cantidad de soluciones válidas encontradas
		bool logs;					// Mostrar o no el proceso de búsqueda de soluciones

	public:
		FcSolver(Instance* instance, bool showLogs);
		~FcSolver();
		bool compareExams(int e1, int e2);
		int isAssignable(int exm, int slot);
		int doForwardChecking(int exm);
		int examsPenalization(int e1, int e2);
		int getSolutionPenalty();
		void resetDomains(int actualExm);
		void checkSolution();
		void writeSolution();
		void showSolution();
		void doBackTracking(int actualExm);
		void showDomains();
};

#endif