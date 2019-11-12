/*****************************************************************************
**											  								**
** project 	:  	Project Name					 							**
** filename : 	FILE.h  							  						**
** version 	: 	1 									  						**
** date 	:  	2011-06-05		 		 									**
** 											  								**
******************************************************************************
** 											  								**
** gpl2 license  2011.						  								**
**  								  					                    **
** 											  								**
******************************************************************************
**										        							**
**VERSION HISTORY:									  						**
**----------------									  						**
**Version : 1										  						**
**Date : 2011-06-05										 					**
**Revised by : 	tarek-asis.hamed@alumni.mondragon.edu	  					**
**Description : Original version.							  				**
*****************************************************************************/


#ifndef _SCHEDULER_H
#define _SCHEDULER_H



/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/
#define SCHEDULE_TASK_MAX 10
/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
typedef  struct{
	// Pointer to the task (must be a 'void (void)' function)
	void (*pFunction)(void); //void (*pFunction)(*) callback genérico
	// Delay (ticks) until the function will (next) be run
	// - see SCH_Add_Task() for further details
	int Delay;
	// Interval (ticks) between subsequent runs.
	// - see SCH_Add_Task() for further details
	int Period;
	// Incremented (by scheduler) when task is due to execute
	unsigned char RunMe;
} STASK;

#ifndef _FILE_C
#define PUBLIC extern
#else
#define PUBLIC
#endif

/*****************************************************************************
**								 											**
** EXPORTED VARIABLES 														**
** 																			**
******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif
/*****************************************************************************
**					 														**
** EXPORTED FUNCTIONS 														**
** 																			**
******************************************************************************/
void SCHEDULER_init();
void SCHEDULER_schedule();
void SCHEDULER_backgroundTask();

void SCHEDULER_addTask( void (*pFunction)(void) , int period, int delay);
void SCHEDULER_update();

#ifdef __cplusplus
}
#endif
#endif
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
