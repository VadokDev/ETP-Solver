# Examination Timetabling Problem Solver

El presente proyecto consta de un paper de investigación respecto del estado del arte del Examination Timetabling Problem, así como también, una propuesta de solución basada en la aplicación de los algoritmos Backtracking + Forward Checking, el programa retorna una calendarización de exámenes tal que ningún estudiante tendrá 2 exámenes o más al mismo tiempo y la cantidad de horarios utilizada sea la mínima posible, a su vez, el la solución minimizará la penalización asociada a qué tan juntos quedan los exámenes para cada estudiante, de modo tal de dispersar lo mejor posible éstos siempre manteniento el mínimo uso posible de horarios.

## Archivos del Repositorio

El repositorio cuenta con todo el trabajo desarrollado a lo largo de la investigación, separando el código fuente y los resultados obtenidos de la siguiente manera:

* [estado-del-arte](./estado-del-arte): Carpeta con el código fuente en LaTeX del paper derivado de la investigación del Estado del Arte actual del Examination Timetabling Problem
* [paper-final](./paper-final): Carpeta con el código fuente en LaTeX del paper final, el cual contiene la investigación del paper anterior más los resultados de una propuesta de solución al problema investigado
* [instances](./instances): Carpeta con instancias de prueba del ETP
* [solutions](./solutions): Carpeta con soluciones a algunas de las instancias de prueba del ETP
* El directorio raíz cuenta con el código fuente de la solución propuesta, éste consta de una implementación de Backtracking + FC para resolver el ETP, además, se incluye un generador de instancias en Python.

## Instrucciones de Ejecución

* Compilar el ETPSolver con `make`
* Ejecutar con `./ETPSolver [nombreInstancia] [1 | 0 logs]`
* Ejemplo de ejecución `./ETPSolver Prueba1 1`
* Para eliminar los residuos de compilación, así como el programa, ejecutar `make clean`
* Activar los logs para ver el procedimiento completo
* Nota: No ejecutar instancias muy grandes pues éstas tardarán demasiado

## Instrucciones para el Generador de Instancias

* Ejecutar el comando `python instanceGenerator.py [instanceName] [exams] [students]`
* Ejemplo de ejecución `python instanceGenerator.py Prueba2 15 100`
* Nota: El programa asigna un máximo de exámenes por estudiante igual a la mitad del total de exámenes, para evitar obligar al programa a usar 1 horario por examen como solución

