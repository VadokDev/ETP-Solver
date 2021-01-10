import os, json
import pandas as pd

# When I programmed this I was already too tired, sorry for the mess
jsonList = [pos_json for pos_json in os.listdir() if pos_json.endswith('.json')]
dataList = []

for i in range(0, len(jsonList)):
	jsonFile = open(jsonList[i])
	data = json.load(jsonFile)
	jsonFile.close()
	data['x'] = data['students'] // 5
	data['y'] = data['exams']
	dataList.append(data)

dataList = sorted(dataList, key = lambda x: (x['y'], x['x']))

print("[", end = '')
for i in range(0, len(dataList) - 1):
	data = dataList[i]
	data['x'] = data['students'] // 5
	data['y'] = data['exams']
	print(json.dumps(data) + ",")

data = dataList[len(dataList) - 1]
data['x'] = data['students'] // 5
data['y'] = data['exams']
print(json.dumps(data) + ",")
print("]")


print("\\begin{table}[]")
print("\\centering")
print("\\resizebox{\\textwidth}{!}{%")
print("\\begin{tabular}{lllllllllllll}")
print("Instancia & Exámenes & Estudiantes & Asignaciones & Máx. Asignacines por Estudiante & Hrarios & Penalización & Iteraciones & Chequeos & Filtros & Soluciones & Mejoras a la Solución & Tiempo \\\\")
for data in dataList:
	print(data["name"], end=" & ")
	print(data["exams"], end=" & ")
	print(data["students"], end=" & ")
	print(data["assignements"], end=" & ")
	print(data["maxAssignements"], end=" & ")
	print(data["timeslots"], end=" & ")
	print(data["penalization"], end=" & ")
	print(data["iterations"], end=" & ")
	print(data["checks"], end=" & ")
	print(data["removed"], end=" & ")
	print(data["solutions"], end=" & ")
	print(data["bestSolutions"], end=" & ")
	print(data["time"], end=" \\\\ \n")
print("\\end{tabular}%")
print("}")
print("\\caption{}")
print("\\label{tab:my-table}")
print("\\end{table}")
