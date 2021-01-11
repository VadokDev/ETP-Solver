import os, json
import pandas as pd
import sys

cosa = sys.argv[1]
print(cosa)

# When I programmed this I was already too tired, sorry for the mess
names = [{ "name": "E10S10", "conflicts": 31}, { "name": "E10S15", "conflicts": 32}, { "name": "E10S20", "conflicts": 30}, { "name": "E10S25", "conflicts": 40}, { "name": "E10S30", "conflicts": 44}, { "name": "E10S35", "conflicts": 43}, { "name": "E10S40", "conflicts": 45}, { "name": "E10S45", "conflicts": 45}, { "name": "E10S50", "conflicts": 45}, { "name": "E10S5", "conflicts": 16}, { "name": "E11S10", "conflicts": 36}, { "name": "E11S15", "conflicts": 45}, { "name": "E11S20", "conflicts": 49}, { "name": "E11S25", "conflicts": 54}, { "name": "E11S30", "conflicts": 55}, { "name": "E11S35", "conflicts": 53}, { "name": "E11S40", "conflicts": 52}, { "name": "E11S45", "conflicts": 55}, { "name": "E11S50", "conflicts": 55}, { "name": "E11S5", "conflicts": 27}, { "name": "E12S10", "conflicts": 38}, { "name": "E12S15", "conflicts": 50}, { "name": "E12S20", "conflicts": 54}, { "name": "E12S25", "conflicts": 64}, { "name": "E12S30", "conflicts": 62}, { "name": "E12S35", "conflicts": 64}, { "name": "E12S40", "conflicts": 66}, { "name": "E12S45", "conflicts": 66}, { "name": "E12S50", "conflicts": 66}, { "name": "E12S5", "conflicts": 30}, { "name": "E13S10", "conflicts": 51}, { "name": "E13S15", "conflicts": 58}, { "name": "E13S20", "conflicts": 62}, { "name": "E13S25", "conflicts": 66}, { "name": "E13S30", "conflicts": 77}, { "name": "E13S35", "conflicts": 77}, { "name": "E13S40", "conflicts": 77}, { "name": "E13S45", "conflicts": 77}, { "name": "E13S50", "conflicts": 77}, { "name": "E13S5", "conflicts": 25}, { "name": "E14S10", "conflicts": 63}, { "name": "E14S15", "conflicts": 67}, { "name": "E14S20", "conflicts": 78}, { "name": "E14S25", "conflicts": 87}, { "name": "E14S30", "conflicts": 89}, { "name": "E14S35", "conflicts": 87}, { "name": "E14S40", "conflicts": 86}, { "name": "E14S45", "conflicts": 91}, { "name": "E14S50", "conflicts": 91}, { "name": "E14S5", "conflicts": 53}, { "name": "E15S10", "conflicts": 52}, { "name": "E15S15", "conflicts": 60}, { "name": "E15S20", "conflicts": 101}, { "name": "E15S25", "conflicts": 97}, { "name": "E15S30", "conflicts": 104}, { "name": "E15S35", "conflicts": 103}, { "name": "E15S40", "conflicts": 105}, { "name": "E15S45", "conflicts": 104}, { "name": "E15S50", "conflicts": 103}, { "name": "E15S5", "conflicts": 51}, { "name": "E2S10", "conflicts": 0}, { "name": "E2S15", "conflicts": 0}, { "name": "E2S20", "conflicts": 0}, { "name": "E2S25", "conflicts": 0}, { "name": "E2S30", "conflicts": 0}, { "name": "E2S35", "conflicts": 0}, { "name": "E2S40", "conflicts": 0}, { "name": "E2S45", "conflicts": 0}, { "name": "E2S50", "conflicts": 0}, { "name": "E2S5", "conflicts": 0}, { "name": "E3S10", "conflicts": 3}, { "name": "E3S15", "conflicts": 2}, { "name": "E3S20", "conflicts": 3}, { "name": "E3S25", "conflicts": 3}, { "name": "E3S30", "conflicts": 3}, { "name": "E3S35", "conflicts": 3}, { "name": "E3S40", "conflicts": 3}, { "name": "E3S45", "conflicts": 3}, { "name": "E3S50", "conflicts": 3}, { "name": "E3S5", "conflicts": 1}, { "name": "E4S10", "conflicts": 0}, { "name": "E4S15", "conflicts": 5}, { "name": "E4S20", "conflicts": 3}, { "name": "E4S25", "conflicts": 6}, { "name": "E4S30", "conflicts": 6}, { "name": "E4S35", "conflicts": 6}, { "name": "E4S40", "conflicts": 6}, { "name": "E4S45", "conflicts": 6}, { "name": "E4S50", "conflicts": 6}, { "name": "E4S5", "conflicts": 1}, { "name": "E5S10", "conflicts": 5}, { "name": "E5S15", "conflicts": 5}, { "name": "E5S20", "conflicts": 5}, { "name": "E5S25", "conflicts": 5}, { "name": "E5S30", "conflicts": 7}, { "name": "E5S35", "conflicts": 8}, { "name": "E5S40", "conflicts": 9}, { "name": "E5S45", "conflicts": 8}, { "name": "E5S50", "conflicts": 10}, { "name": "E5S5", "conflicts": 1}, { "name": "E6S10", "conflicts": 9}, { "name": "E6S15", "conflicts": 11}, { "name": "E6S20", "conflicts": 14}, { "name": "E6S25", "conflicts": 9}, { "name": "E6S30", "conflicts": 11}, { "name": "E6S35", "conflicts": 14}, { "name": "E6S40", "conflicts": 15}, { "name": "E6S45", "conflicts": 15}, { "name": "E6S50", "conflicts": 15}, { "name": "E6S5", "conflicts": 4}, { "name": "E7S10", "conflicts": 20}, { "name": "E7S15", "conflicts": 20}, { "name": "E7S20", "conflicts": 18}, { "name": "E7S25", "conflicts": 21}, { "name": "E7S30", "conflicts": 21}, { "name": "E7S35", "conflicts": 19}, { "name": "E7S40", "conflicts": 20}, { "name": "E7S45", "conflicts": 20}, { "name": "E7S50", "conflicts": 21}, { "name": "E7S5", "conflicts": 6}, { "name": "E8S10", "conflicts": 17}, { "name": "E8S15", "conflicts": 22}, { "name": "E8S20", "conflicts": 26}, { "name": "E8S25", "conflicts": 20}, { "name": "E8S30", "conflicts": 24}, { "name": "E8S35", "conflicts": 28}, { "name": "E8S40", "conflicts": 27}, { "name": "E8S45", "conflicts": 28}, { "name": "E8S50", "conflicts": 28}, { "name": "E8S5", "conflicts": 8}, { "name": "E9S10", "conflicts": 19}, { "name": "E9S15", "conflicts": 26}, { "name": "E9S20", "conflicts": 27}, { "name": "E9S25", "conflicts": 32}, { "name": "E9S30", "conflicts": 29}, { "name": "E9S35", "conflicts": 33}, { "name": "E9S40", "conflicts": 32}, { "name": "E9S45", "conflicts": 35}, { "name": "E9S50", "conflicts": 32}, { "name": "E9S5", "conflicts": 15}]

jsonList = [pos_json for pos_json in os.listdir() if pos_json.endswith('.json')]
dataList = []

for i in range(0, len(jsonList)):
	jsonFile = open(jsonList[i])
	data = json.load(jsonFile)
	jsonFile.close()
	data['x'] = data['students'] // 5 - 1
	data['y'] = data['exams'] - 2
	data["iterations"] = data["iterations"] if data["iterations"] >= 0 else (data["iterations"]*-1 + (2**32 - 1))
	data["checks"] = data["checks"] if data["checks"] >= 0 else (data["checks"]*-1 + (2**32 - 1))
	data["removed"] = data["removed"] if data["removed"] >= 0 else (data["removed"]*-1 + (2**32 - 1))
	data['value'] = data[cosa]
	data['conflicts'] = [i["conflicts"] for i in names if i["name"] == data["name"]][0]
	dataList.append(data)

dataList = sorted(dataList, key = lambda x: (x['y'], x['x']))

print("[", end = '')
for i in range(0, len(dataList) - 1):
	data = dataList[i]
	data['x'] = data['students'] // 5 - 1
	data['y'] = data['exams'] - 2
	data["iterations"] = data["iterations"] if data["iterations"] >= 0 else (data["iterations"]*-1 + (2**32 - 1))
	data["checks"] = data["checks"] if data["checks"] >= 0 else (data["checks"]*-1 + (2**32 - 1))
	data["removed"] = data["removed"] if data["removed"] >= 0 else (data["removed"]*-1 + (2**32 - 1))
	data['value'] = data[cosa]
	data['conflicts'] = [i["conflicts"] for i in names if i["name"] == data["name"]][0]
	if data['exams'] < 14:
		print(json.dumps(data) + ",", end='')

data = dataList[len(dataList) - 1]
data['x'] = data['students'] // 5 - 1
data['y'] = data['exams'] - 2
data["iterations"] = data["iterations"] if data["iterations"] >= 0 else (data["iterations"]*-1 + (2**32 - 1))
data["checks"] = data["checks"] if data["checks"] >= 0 else (data["checks"]*-1 + (2**32 - 1))
data["removed"] = data["removed"] if data["removed"] >= 0 else (data["removed"]*-1 + (2**32 - 1))
data['value'] = data[cosa]
if data['exams'] < 14:
	print(json.dumps(data), end='')
print("]")

exit()

print("\\begin{table}[]")
print("\\centering")
print("\\resizebox{\\textwidth}{!}{%")
print("\\begin{tabular}{llllllllllllll}")
print("Instancia & Exámenes & Estudiantes & Conflictos & Asignaciones & Máx. Asignacines por Estudiante & Horarios & Penalización & Iteraciones & Chequeos & Filtros & Soluciones & Mejoras a la Solución & Tiempo \\\\")
for data in dataList:
	print(data["name"], end=" & ")
	print(data["exams"], end=" & ")
	print(data["students"], end=" & ")
	print(data["conflicts"], end=" & ")
	print(data["assignements"], end=" & ")
	print(data["maxAssignements"], end=" & ")
	print(data["timeslots"], end=" & ")
	print(data["penalization"], end=" & ")
	print(data["iterations"] if data["iterations"] >= 0 else (data["iterations"]*-1 + (2**32 - 1)), end=" & ")
	print(data["checks"] if data["checks"] >= 0 else (data["checks"]*-1 + (2**32 - 1)), end=" & ")
	print(data["removed"] if data["removed"] >= 0 else (data["removed"]*-1 + (2**32 - 1)), end=" & ")
	print(data["solutions"], end=" & ")
	print(data["bestSolutions"], end=" & ")
	print(data["time"], end=" \\\\ \n")
print("\\end{tabular}%")
print("}")
print("\\caption{}")
print("\\label{tab:my-table}")
print("\\end{table}")
