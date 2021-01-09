#ifndef FCSOLVER_H
#define FCSOLVER_H

#include <vector>
#include <string>
#include <Instance.h>

#define SOLUTIONS_DIRECTORY "./test/"

class FcSolver {
	private:
		Instance* inst;				// Instancia a resolver
		vii D;						// Matriz de horarios disponibles para asignar a los exámenes
		vi sol;						// Solución actual del backtracking
		vi bestSol;					// Mejor solución encontrada durante el proceso
		std::string solutionsDir;	// Directorio con las soluciones encontradas

		long double bestSolPenalty;	// Penalización asociada a la mejor solución encontrada
		double totalTime;			// Tiempo total de ejecución del algoritmo
		int totalSols;				// Cantidad de soluciones válidas encontradas
		int totalBests;				// Cantidad de soluciones que mejoran la solución anterior
		int totalSteps;				// Cantidad de iteraciones
		int totalChecks;			// Cantidad de chequeos realizados
		int totalRemoved;			// Cantidad de horarios filtrados por FC

		int maxSlots;				// Cantidad de slots a usar
		bool logs;					// Mostrar o no el proceso de búsqueda de soluciones
		bool minSlotsFound;			// Flag que indica si se encontró la mínima cantidad de slots

	public:
		FcSolver(Instance* instance, bool showLogs);
		~FcSolver();
		long double examsPenalization(int e1, int e2);
		long double getSolutionPenalty();
		bool compareExams(int e1, int e2);
		int isAssignable(int exm, int slot);
		int doForwardChecking(int exm);
		void doMaxTimeSlotsAdjustment();
		void resetDomains(int actualExm);
		void checkSolution();
		void writeSolution();
		void showSolution();
		void doBackTracking(int actualExm);
		void showDomains();
		void writeStatsToJson();
};

#endif