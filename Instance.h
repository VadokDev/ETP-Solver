#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>

typedef std::vector<int> vi;
typedef std::vector<vi> vii;

#define INSTANCES_DIRECTORY "./instances/"

class Instance {
	public:
		int E;
		int L;
		int S;
		vii cMatrix;
		std::string name;
		std::string instancesDir = INSTANCES_DIRECTORY;
		
		void loadExams();
		void genConflictMatrix();
		void loadStudents();
		void showConflictsMatrix();
		Instance(std::string instanceName);
		~Instance();
};

#endif