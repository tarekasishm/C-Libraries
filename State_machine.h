/**
****************************************************************************
* @file			State_machine.h
* @brief 		File general description
* @version		0.1.0
* @date			2016-11-21
****************************************************************************
* @author		Arruabarrena, Aritz
* @copyright
****************************************************************************
* @par Version history
* @par
*  Version   | Date         |     Revised by   |  Description
*  --------- | ------------ | ---------------- | ----------------------------
*    0.1.0   | 2016-11-21   |  aarruabarrena    | Original version

****************************************************************************/

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

/***************************************************************************
 **                                                                       **
 **                      MODULES USED                                     **
 **                                                                       **
 ***************************************************************************/


/***************************************************************************
 **                                                                       **
 **                      DEFINITIONS AND MACROS                           **
 **                                                                       **
 ***************************************************************************/


/***************************************************************************
 **                                                                       **
 **                      TYPEDEFS AND STRUCTURE                           **
 **                                                                       **
 ***************************************************************************/

typedef void	 (*TPFN_ACC)(void); /* Pointer to an action function */
typedef BOOLEAN	 (*TPFN_EVE)(void); /* Pointer to an event function */

typedef struct {
	  int		   idNextState;    /* Identifier of next state */
	  char        *name;           /* Name for debug */
	  TPFN_EVE     event;          /* Pointer to an event function */
	  TPFN_ACC     action;         /* Pointer to an action function */
	  TPFN_ACC     exit;           /* Pointer to an action function */
} TS_EVEACC;    //Esto sera la transicion

typedef struct {
	  int		   id;             /* Identifier of state */
	  char        *name;           /* Name for debug */
	  TPFN_ACC     controls;       /* Control function of state (DO) */
	  TS_EVEACC   *transitions;    /* Pointer of the transitions */
}TS_STATE;

typedef struct {
	  int		   id;               /* Identifier of the machine */
	  char        *name;             /* Name for debug */
	  int		   idCurrentState;   /* Actual state identifier */
	  //TPFN_EVE   StopCond;         /* Needed condition for machine ejecution */ //Se puede añadir un StopAcc
	  TS_STATE    **states;          /* array  of pointers to STATES */
} TS_MACHINE;


 /***************************************************************************
 **                                                                       **
 **                      EXPORTED VARIABLES                               **
 **                                                                       **
 ***************************************************************************/

/***************************************************************************
 **                                                                       **
 **                      EXPORTED FUNCTIONS                               **
 **                                                                       **
 ***************************************************************************/

void LIBS_STATE_MACHINE_execute(TS_MACHINE *theMachine);


#endif /* STATE_MACHINE_H_ */

/***************************************************************************
 **                                                                       **
 **                      EOF                                              **
 **                                                                       **
 ***************************************************************************/
