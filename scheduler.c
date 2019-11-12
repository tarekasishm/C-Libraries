/*********************************************************************
** 																	**
** project : General Template 										**
** filename : TPL.C 												**
** version : 1 														**
** date : August 02, 2003 											**
** 																	**
**********************************************************************
** 																	**
** Copyright (c) 2003, P.K. van der Vlugt 							**
** All rights reserved. 											**
** 																	**
**********************************************************************
**																	**
**VERSION HISTORY:													**
**----------------													**
**Version : 1														**
**Date : August 02, 2003											**
**Revised by : P.K. van der Vlugt									**
**Description : Original version. 									**
*********************************************************************/

#define _FILE_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
#include "scheduler.h"
/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
**********************************************************************/

/*********************************************************************
** 																	**
** TYPEDEFS AND STRUCTURES 											**
** 																	**
**********************************************************************/

/*********************************************************************
** 																	**
** PROTOTYPES OF LOCAL FUNCTIONS 									**
** 																	**
*********************************************************************/
static void SCHEDULER_deleteTask(int i);
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/
STASK tasks[SCHEDULE_TASK_MAX];
/*********************************************************************
** 																	**
** EXPORTED FUNCTIONS 												**
** 																	**
**********************************************************************/
/**
* @brief Inicializa el array de tareas. Sin implementar el timer.
* @param
* @return
*/
void SCHEDULER_init(){
	//aqui iniciaria el systick. Ya veremos esto.
	int i = 0;
	//125ns
	//SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_8MHZ);


	for (i=0; i < SCHEDULE_TASK_MAX ; i++){
		SCHEDULER_deleteTask(i);
	}
}

/**
* @brief Lanza las tareas disponibles.
*
* Lanza todas las tareas que tengan el flag RunMe mayor que 1.
* No hay ningún tipo de prioridades.
* @param
* @return
*/

void SCHEDULER_schedule(){
	unsigned char Index;
	// Dispatches (runs) the next task (if one is ready)
	for (Index = 0; Index < SCHEDULE_TASK_MAX; Index++)
	{
		if ( tasks[Index].RunMe > 0){
			(*tasks[Index].pFunction)(); // Run the task
			 tasks[Index].RunMe -= 1; // Reset / reduce RunMe flag
			// Periodic tasks will automatically run again
			// - if this is a 'one shot' task, remove it from the array
			if ( tasks[Index].Period == 0){
				SCHEDULER_deleteTask(Index);
			}
		}
	}
	// Report system status
	//SCH_Report_Status();
	// The scheduler enters idle mode at this point
	//SCH_Go_To_Sleep()
}

/**
* @brief Todavía por implementar.
* @param
* @return
*/
void SCHEDULER_backgroundTask(){

}

/**
* @brief Añade otra tarea al array de tareas a planificar.
*
* Actualmente añade tareas sin comprobar si el array está lleno
* pudiendo escribir corromper la memoria.
* @param puntero a función a planificar.
* @param period periodo con el que lanzar la función
* @param delay desfase inicial.
* @return
*/
void SCHEDULER_addTask( void (*pFunction)(void) , int period, int delay){
	unsigned char Index = 0;
	// First find a gap in the array (if there is one)
	while (( tasks[Index].pFunction != 0) && (Index < SCHEDULE_TASK_MAX))
	{
		Index++;
	}
	// Have we reached the end of the list?
	//if (Index == SCHEDULE_TASK_MAX)
	//{
	// Task list is full
	//
	// Set the global error variable
	//Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
	// Also return an error code
	//return SCH_MAX_TASKS;
	//}
	// If we're here, there is a space in the task array
	tasks[Index].pFunction = pFunction;
	tasks[Index].Delay = delay;
	tasks[Index].Period = period;
	tasks[Index].RunMe = 0;
//	return Index; // return position of task (to allow later deletion)
//}
}

/**
* @brief Actualiza los parámetros temporales de cada función
*
* Esta función depende de la frecuencia a la que se programe la interrupción
* del timer.
* @return
*/
void SCHEDULER_update(){
	int i = 0;
	for (i = 0 ; i < SCHEDULE_TASK_MAX ; i++){
		if ( tasks[i].pFunction){
			if ( tasks[i].Delay == 0 ){
				tasks[i].RunMe += 1;
				if (tasks[i].Period ){
					tasks[i].Delay = tasks[i].Period;
				}
			}else{
				tasks[i].Delay -= 1;
			}
		}
	}
}


/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/**
* @brief Elimina una tarea del array.
* @return
*/

static void SCHEDULER_deleteTask(int i){
	tasks[i].Delay = 0;
	tasks[i].Period = 0;
	tasks[i].RunMe = 0;
	tasks[i].pFunction = 0;//NULL
}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/

