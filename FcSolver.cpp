#include <bits/stdc++.h>
#include <sys/time.h>
#include "FcSolver.h"

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

FcSolver::FcSolver(Instance* instance, bool showLogs) {
	bestSolPenalty = FLT_MAX;
	solutionsDir = SOLUTIONS_DIRECTORY;
	inst = instance;
	logs = showLogs;

	totalSols = 0;
	totalBests = 0;
	totalSteps = 0;
	totalChecks = 0;
	totalRemoved = 0;
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
		
		// No revisar si el horario ya fue removido del examen
		if(!D[i][sol[exm]]) {
			totalChecks++;
			if(inst->cMatrix[exm][i]) {
				totalRemoved++;
				D[i][sol[exm]] = exm;
				if(logs) cout << "[Forward Checking] " << "Removed slot " << sol[exm] << " from Exam " << i << " by Exam " << exm << '\n';
			}
		}

		// Contar la cantidad de valores disponibles en el dominio de los exámenes
		if(!count(D[i].begin(), D[i].begin() + maxSlots + 1, 0))
			return 0;
	}

	if(logs) {
		cout << "[Forward Checking] " << "Final domains (no empty domains were generated):" << '\n';
		showDomains();
		cout << "[Forward Checking] " << "End Forward Checking from Exam: " << exm << '\n';  
	}

	// Retornar 1 para indicar que no quedaron dominios de variables vacíos
	return 1;
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

	totalSols++;
	// Reemplazar la solución en caso de ser mejor
	if(bestSolPenalty > penalty) {
		totalBests++;
		for (int i = 1; i < maxSlots + 1; ++i) {
			bestSol[i] = sol[i];
			bestSolPenalty = penalty / (long double) inst->S;
		}

		writeSolution();
		showSolution();
		cout << "penalización: " << bestSolPenalty << '\n';
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
		resFile.open(solutionsDir + inst->name + ".res", ofstream::app);
		penFile.open(solutionsDir + inst->name + ".pen", ofstream::app);
		solFile.open(solutionsDir + inst->name + ".sol", ofstream::app);
		resFile << "========================END SOLUTION" << '\n';
		penFile << "========================END SOLUTION" << '\n';
		solFile << "========================END SOLUTION" << '\n';
	} else {
		resFile.open(solutionsDir + inst->name + ".res");
		penFile.open(solutionsDir + inst->name + ".pen");
		solFile.open(solutionsDir + inst->name + ".sol");
	}

	resFile << (long double) maxSlots << '\n';
	penFile << (long double) bestSolPenalty << '\n';
	
	resFile.close();
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
		
		for (size_t j = 0; j < inst->sExams[i].size() - 1; ++j) {
			for (size_t k = j + 1; k < inst->sExams[i].size(); ++k) {
				penaltyTotal += examsPenalization(inst->sExams[i][j], inst->sExams[i][k]);
			}
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

void FcSolver::writeStatsToJson() {
	ofstream jsonFile;
	jsonFile.open(solutionsDir + inst->name + ".json");
    jsonFile.setf(ios::fixed);
    jsonFile.precision(4);
	jsonFile << "{" << '\n'
		<< "     \"name\": " 	<< "\"" << inst->name << "\"" 	<< "," << '\n'
		<< "     \"students\": " 		<< inst->S				<< "," << '\n'
		<< "     \"assignements\": " 	<< inst->A				<< "," << '\n'
		<< "     \"maxAssignements\": "<< inst->L				<< "," << '\n'
		<< "     \"exams\": " 			<< inst->E				<< "," << '\n'
		<< "     \"timeslots\": " 		<< maxSlots				<< "," << '\n'
		<< "     \"penalization\": "	<< bestSolPenalty		<< "," << '\n'
		<< "     \"iterations\": " 		<< totalSteps			<< "," << '\n'
		<< "     \"checks\": " 			<< totalChecks			<< "," << '\n'
		<< "     \"removed\": " 		<< totalRemoved			<< "," << '\n'
		<< "     \"solutions\": " 		<< totalSols			<< "," << '\n'
		<< "     \"bestSolutions\": "	<< totalBests			<< "," << '\n'
		<< "     \"time\": " 			<< totalTime			<< '\n'
		<< "}" << '\n';
	jsonFile.close();
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
    struct timeval start, end;		// Marcas de tiempo
    gettimeofday(&start, 0);	
	// Explorar el espacio de búsqueda aumentando los slots hasta encontrar la mínima cantidad necesaria
	for (maxSlots = inst->L; (maxSlots < inst->E + 1) && !minSlotsFound; ++maxSlots) {
		cout << "[TimeSlots] Solving with " << maxSlots << " timeslots" << '\n';
		doBackTracking(1);
		resetDomains(0);
	}
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    totalTime = seconds + microseconds*1e-6;
}

void FcSolver::doBackTracking(int exm) {
	if(logs && exm == 1) cout << "[Backtracking] " << "Starting" << '\n';

	// Evaluamos cada posible horario a usar para el examen actual
	for (int slot = 1; slot < maxSlots + 1; ++slot) {
		totalSteps++;
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