#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>

typedef std::vector<int> vi;
typedef std::vector<vi> vii;

#define INSTANCES_DIRECTORY "./experiments/"

class Instance {
	public:
		std::string name;			// Nombre de la instancia a resolver
		std::string instancesDir;	// Directorio con las soluciones encontradas

		vii sExams;					// Lista de exámenes de cada estudiante			
		vii cMatrix;				// Matriz de conflictos entre exámenes que comparten estudiantes
		int S;						// Cantidad de estudiantes
		int A;						// Cantidad de exámenes asignados
		int L;						// Cantidad de máxima de exámenes que un estudiante debe rendir
		int E;						// Cantidad de exámenes
		
		void loadExams();  
		void genConflictMatrix();
		void loadStudents();
		void showStudentExams();
		void showConflictMatrix();
		Instance(std::string instanceName);
		~Instance();
};

#endif