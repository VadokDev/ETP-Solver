from collections import defaultdict 

instance = "Prueba1"

stu = open(f"{instance}.stu").read().split("\n")[:-1]
stu_dic = defaultdict(list) 
for line in stu: 
    student, exam = line.strip().split()
    stu_dic[student].append(int(exam))

res = open(f"{instance}.sol").read().split("\n")[:-1]
print(f"Load {len(stu_dic)} Students & {len(res)} Exams")

schedule = [[] for _ in range(len(res))]
schedule_dic = {}
for line in res:
    exam, slot = line.strip().split()
    schedule_dic[int(exam)] = int(slot)

costo = 0

for sujeto, examenes in stu_dic.items():
    if len(examenes)==1: continue
    # print(sujeto, examenes)
    for i in range(len(examenes)):
        for j in range(i+1, len(examenes)):
            exam1, slot1 = examenes[i], schedule_dic[examenes[i]]
            exam2, slot2 = examenes[j], schedule_dic[examenes[j]]
            diff = abs(slot1 - slot2)
            # print(f"  Comparando {exam1}(slot{slot1}) con {exam2}(slot{slot2}), diff={diff}")
            if diff == 0: print("invalid schedule exiting"); exit()
            if diff in [1,2,3,4,5]:  costo += 2**(5-diff)

print(f"costo total: {costo}, costo promedio: {costo/len(stu_dic)}")