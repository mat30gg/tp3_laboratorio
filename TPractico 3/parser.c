#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int exito;
	Employee* aux;
	char id[12];
	char nombre[128];
	char horasTrabajadas[4];
	char sueldo[8];
	if(pFile!=NULL)
	{
		fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, horasTrabajadas, sueldo);
		exito = 1;
		while(!feof(pFile))
		{
			fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, horasTrabajadas, sueldo);
			aux = employee_newParametros(id, nombre, horasTrabajadas, sueldo);
			if(aux != NULL)
			{
				ll_add(pArrayListEmployee, aux);
			}
		}
	}
	else
	{
		exito = 0;
	}
    return exito;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee, int cant)
{
	int exito;
	Employee* aux;
	Employee* empleado;
	int x;
	aux = (Employee*) malloc(sizeof(Employee));
	if(pFile!=NULL)
	{
		exito = 1;
		for(x = 0; x < cant-1; x++)
		{
			fread(aux, sizeof(Employee), 1, pFile);
			empleado = employee_new();
			copyEmployee(empleado, *aux);
			if(aux != NULL)
			{
				ll_add(pArrayListEmployee, empleado);
			}
		}
	}
	else
	{
		exito = 0;
	}
	return exito;
}
