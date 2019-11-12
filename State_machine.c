/**
****************************************************************************
* @file			State_machine.c
* @brief 		File general description
* @version		0.1.0
* @date			2016-11-21
****************************************************************************
* @author		Arruabarrena, Aritz
* @copyright
****************************************************************************
* @par Version history
* @par
*  Version   | Date         |  Revised by        |  Description
*  --------- | ------------ | -----------------  | ----------------------------
*    0.1.0   | 2016-11-21   |  aarruabarrena     | Original version
*    0.1.1   | 2016-11-21   |  iallende		     | Functions added
*
****************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      MODULES USED                                     **
 **                                                                       **
 ***************************************************************************/

#include "New_types.h"
#include "State_machine.h"

/***************************************************************************
 **                                                                       **
 **                      DEFINITIONS AND MACROS                           **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      TYPEDEFS AND STRUCTURES                          **
 **                                                                       **
 ***************************************************************************/


/***************************************************************************
 **                                                                       **
 **                      PROTOTYPES OF LOCAL FUNCTIONS                    **
 **                                                                       **
 ***************************************************************************/

 void LIBS_STATE_MACHINE_executeState(TS_STATE *theState , TS_MACHINE *theMachine);

/***************************************************************************
 **                                                                       **
 **                      EXPORTED VARIABLES                               **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      GLOBAL VARIABLES                                 **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      EXPORTED FUNCTIONS                               **
 **                                                                       **
 ***************************************************************************/
void LIBS_STATE_MACHINE_execute(TS_MACHINE *theMachine){
	TS_STATE **Indx;    /* Index number */

	/* if (theMachine->StopCond()){
	 * create in the stateMachine.h a StopAcc and call it here
		return;
	 */

	for (Indx = theMachine->states; *Indx != NULL; ++Indx){
		if (theMachine->idCurrentState == (*Indx)->id){
			LIBS_STATE_MACHINE_executeState(*Indx , theMachine);
			return;
		}
	}
}

/***************************************************************************
 **                                                                       **
 **                      LOCAL FUNCTIONS                                  **
 **                                                                       **
 ***************************************************************************/
void LIBS_STATE_MACHINE_executeState(TS_STATE *theState , TS_MACHINE *theMachine){
	TS_EVEACC *Indx;   /* Index tracking */

	theState->controls(); /* Call to DO functions */

	for (Indx = theState->transitions; Indx->event != NULL; ++Indx){ /* Current state search */
		if (Indx->event() == TRUE){
			if (Indx->action != NULL){ 		/* Check if action is empty */
				Indx->action();
			}
			if (Indx->idNextState != theMachine->idCurrentState){
				if (Indx->exit != NULL){ 	/* Check if action is empty */
					Indx->exit();
				}
				theMachine->idCurrentState = Indx->idNextState;
				//theState = search currentState (in a function and above put the same) and execute ENTRY
				//theMachine->entry();
				return;
			}
		}
	}
}

//Se puede implementar una funcion de busqueda de estado actual -> hecho en STATE_MACHINE_execute

/***************************************************************************
 **                                                                       **
 **                      EOF                                              **
 **                                                                       **
 ***************************************************************************/
