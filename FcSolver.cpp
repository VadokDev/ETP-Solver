#include <bits/stdc++.h>
#include "FcSolver.h"

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

FcSolver::FcSolver(Instance* instance, bool showLogs) {
	bestSolPenalty = FLT_MAX;
	inst = instance;
	logs = showLogs;

	totalSols = 0;
	maxSlots = 1;
	minSlotsFound = false;

	bestSol.resize(inst->E + 1);
	sol.resize(inst->E + 1);
	D.resize(inst->E + 1);
	
	for (int i = 0; i < inst->E + 1; ++i) {
		D[i].resize(inst->E + 1);
	}
}

FcSolver::~FcSolver() { }

int FcSolver::doForwardChecking(int exm) {
	// Cantidad restante de horarios posibles en el dominio de todos los exámenes, a partir del examen actual
	int remain = 0;

	if(logs) cout << "[Forward Checking] " << "Starting Forward Checking from Exam: " << exm << '\n';  
	
	// Avanzar en el espacio de soluciones para ir descartando
	for (int i = exm + 1; i < inst->E + 1; ++i) {
		if(logs) { 
			cout << "[Forward Checking] " << "Exam: " << i << '\n';  
			// Descomentar para mostrar los dominios durante el filtrado
			// showDomains();
		}
		
		// Si el examen tiene conflicto con el examen actual,
		// entonces debe eliminarse el horario del espacio,
		// de soluciones del examen, para cumplir la restricción dura.

		if(inst->cMatrix[exm][i] && !D[i][sol[exm]]) {
			D[i][sol[exm]] = exm;
			if(logs) cout << "[Forward Checking] " << "Removed slot " << sol[exm] << " from Exam " << i << " by Exam " << exm << '\n';
		}

		// Contar la cantidad de valores disponibles en el dominio de los exámenes
		if(!count(D[i].begin(), D[i].begin() + maxSlots + 1, 0))
			return 0;
	}

	if(logs) {
		cout << "[Forward Checking] " << "Final Domains: " << remain << '\n';
		showDomains();
		cout << "[Forward Checking] " << "End Forward Checking from Exam: " << exm << '\n';  
	}

	// Retornar tamaño del dominio de horarios disponibles para los exámenes
	return 1;//remain;
}

void FcSolver::resetDomains(int actualExm) {
	// Reiniciar los dominios de los exámenes posteriores al actual
	for (int i = actualExm + 1; i < inst->E + 1; ++i) {
		replace(D[i].begin(), D[i].end(), actualExm, 0);
	}
}

void FcSolver::checkSolution() {
	// Calcular la penalización de la solución actual
	long double penalty = getSolutionPenalty();

	// Reemplazar la solución en caso de ser mejor
	if(bestSolPenalty > penalty) {
		totalSols++;

		for (int i = 1; i < maxSlots + 1; ++i) {
			bestSol[i] = sol[i];
			bestSolPenalty = penalty / inst->S;
		}

		showSolution();

		cout << "penalización: " << penalty << '\n';
		cout << "promedio: " << penalty / inst->S << '\n';
		writeSolution();
	}
}

void FcSolver::showSolution() {
	int timeSlots = 0;
	vii tempSol(inst->E + 1);

	for (int i = 1; i < inst->E + 1; ++i) {
		tempSol[sol[i]].push_back(i);
	}

	for (int i = 1; i < inst->E + 1; ++i) {
		if(!tempSol[i].size())
			continue;

		timeSlots++;
		cout << "[Solution " << totalSols << "] " << "Timeslot " << i << " exams:";

		for (size_t j = 0; j < tempSol[i].size(); ++j) {
			cout << " " << tempSol[i][j];
		}

		cout << '\n';
	}
}

void FcSolver::writeSolution() {
	ofstream resFile;
	ofstream penFile;
	ofstream solFile;

	// Si se ha encontrado una solución mejor que la anterior, se alade al archivo sin sobreescribirlo
	if(totalSols > 1) {
		resFile.open(inst->name + ".res", ofstream::app);
		penFile.open(inst->name + ".pen", ofstream::app);
		solFile.open(inst->name + ".sol", ofstream::app);
		resFile << "========================END SOLUTION" << '\n';
		penFile << "========================END SOLUTION" << '\n';
		solFile << "========================END SOLUTION" << '\n';
	} else {
		resFile.open(inst->name + ".res");
		penFile.open(inst->name + ".pen");
		solFile.open(inst->name + ".sol");
	}

	resFile << maxSlots << '\n';
	resFile.close();

	penFile << bestSolPenalty << '\n';
	penFile.close();


	for (int i = 1; i < inst->E + 1; ++i) {
		solFile << i << " " << sol[i] << '\n';
	}

	solFile.close();
}

long double FcSolver::getSolutionPenalty() {
	long double penaltyTotal = 0.0;

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

long double FcSolver::examsPenalization(int e1, int e2) {
	// Calcular la penalización entre 2 exámenes según sus horarios asignados
	int diff = sol[e2] - sol[e1];

	// Los valores están indicados en el paper
	if(diff == 0) 		return 0.0;
	else if(diff == 1)	return 16.0;
	else if(diff == 2)	return 8.0;
	else if(diff == 3)	return 4.0;
	else if(diff == 4)	return 2.0;
	else if(diff == 5)	return 1.0;
	
	return 0.0;
}

bool FcSolver::compareExams(int e1, int e2) {
	// Comparar exámenes según su precedencia en la solución
	return sol[e1] < sol[e2];
}

void FcSolver::showDomains() {
	// Iterar por los horarios válidos que se pueden asignar a los exámenes
	cout << "[Domains] " << "Showing actual valid domain for all variables" << '\n';
	for (int i = 1; i < inst->E + 1; ++i) {
		cout << "[Domains] " << "Examen [" << i << "]: ";
		for (int j = 1; j < maxSlots + 1; ++j) {
			if(!D[i][j]) {
				cout << j;
				if(j != inst->E) {
					cout << " - ";
				}
			}

		}
		cout << '\n';
	}
}

void FcSolver::doMaxTimeSlotsAdjustment() {
	// Explorar el espacio de búsqueda aumentando los slots hasta encontrar la mínima cantidad necesaria
	for (maxSlots = inst->L; (maxSlots < inst->E + 1) && !minSlotsFound; ++maxSlots) {
		cout << "[TimeSlots] Solving with " << maxSlots << " timeslots" << '\n';
		doBackTracking(1);
		resetDomains(0);
	}
}

void FcSolver::doBackTracking(int exm) {
	if(logs && exm == 1) cout << "[Backtracking] " << "Starting" << '\n';

	// Evaluamos cada posible horario a usar para el examen actual
	for (int slot = 1; slot < maxSlots + 1; ++slot) {
		// Si el horario no está en el dominio de horarios posibles para el examen actual, se sigue
		if(D[exm][slot])
			continue;

		// Descomentar para mostrar los dominios de los exámenes durante el Backtracking
		// if(logs) showDomains();

		// Asignamos el horario al examen actual
		sol[exm] = slot;

		if(logs) cout << "[Backtracking] " << "Exam: " << exm << " Assigned to slot " << slot << '\n';

		// Si se asigna el último examen
		if(exm == inst->E) {
			// Se valida la solución creada y se corta la hoja actual del bt
			checkSolution();

			// Se determina que ésta es la mínima cantidad de slots necesaria
			minSlotsFound = true;
			continue;
		} 

		// Se realiza el FC, si retorna 0 es porque se acabaron los dominios de las variables
		if(!doForwardChecking(exm)) {
			if(logs) cout << "[Backtracking] "<< "No available domains" << '\n';
			continue;
		}

		// Continuar el camino del BT para asignar un horario al siguiente examen
		doBackTracking(exm + 1);

		// Cuando termine el BT recursivo, se reinician los dominios eliminados por el FC.
		resetDomains(exm);
	}
}