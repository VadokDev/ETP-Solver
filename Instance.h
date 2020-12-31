#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>

typedef std::vector<int> vi;
typedef std::vector<vi> vii;

#define INSTANCES_DIRECTORY "./instances/"

class Instance {
	public:
		std::string name;	// Nombre de la instancia a resolver
		std::string instancesDir;

		vii sExams;			// Lista de exámenes de cada estudiante			
		vii cMatrix;		// Matriz de conflictos entre exámenes que comparten estudiantes
		int E;				// Cantidad de exámenes
		int L;				// Cantidad de horarios (por defecto, es equivalente a la cantidad de exámenes)
		int S;				// Cantidad de estudiantes
		
		void loadExams();
		void genConflictMatrix();
		void loadStudents();
		void showStudentExams();
		void showConflictMatrix();
		Instance(std::string instanceName);
		~Instance();
};

#endif