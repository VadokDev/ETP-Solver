
import sys
import os
from random import randint, sample

if len(sys.argv) < 4:
	print("[Error] Missing parameters, usage: python instanceGenerator.py [instanceName] [exams] [students]")
	print("[Error] Example:  python instanceGenerator.py Prueba2 15 100")
	exit(0)

instancesDir = "instances/"

instanceName = sys.argv[1]
exams = int(sys.argv[2])
students = int(sys.argv[3])

stuFileDir = os.path.join(instancesDir, instanceName + ".stu")
exmFileDir = os.path.join(instancesDir, instanceName + ".exm")

stuFile = open(stuFileDir, 'w')
exmFile = open(exmFileDir, 'w')

for i in range(1, exams + 1):
	exmFile.write(str(i) + " " + str(randint(1, students)) + '\n')

for i in range(1, students + 1):
	studentExams = sample(range(1, exams + 1), randint(1, exams / 2))
	studentExams.sort()
	for j in studentExams:
		stuFile.write("s" + str(i) + " " + str(j) + '\n')

stuFile.close()
exmFile.close()