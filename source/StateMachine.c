#include "StateMachine.h"


void fsm_StateIdle(){
    
    if (elevio_floorSensor() != -1){
        elevio_motorDirection(DIRN_STOP);
        elevio_doorOpenLamp(0);
    } 
}



void fsm_StateDoorOpen() {

    ord_deleteCompletedOrder();
    
    clock_t timeCheck = clock();
    clock_t timer = (clock()-timeCheck)/CLOCKS_PER_SEC;

    elevio_motorDirection(DIRN_STOP);
    elevio_doorOpenLamp(1); 


    while( timer < 2){
        if (elevio_stopButton() == 1) {
            fsm_StateStop();
            timeCheck = clock();
        }


        while (elevio_obstruction() == 1) {
            if (elevio_stopButton() == 1) {
                fsm_StateStop();
                timeCheck = clock();
            }
            timeCheck = clock();
            ord_setStopOrders();
        }
        ord_setStopOrders();
        timer = (clock()-timeCheck)/CLOCKS_PER_SEC;
    }
    g_doorOpenIndicator = 0;
    elevio_doorOpenLamp(0);
}




void fsm_StateMoving(){

    elevio_doorOpenLamp(0);

    if (g_stopIndicator == 0){
        g_currentDir = ctrl_nextDir(0);
    }

    else if (g_stopIndicator == 1){
        g_currentDir = ctrl_nextDir(1);
        g_stopIndicator = 0;
    } 


    elevio_motorDirection(g_currentDir);
    g_lastDir = g_currentDir;
}




void fsm_StateStop(){

    elevio_motorDirection(DIRN_STOP);
    elevio_stopLamp(1);
    ord_clearAllOrders();


    while (elevio_stopButton() == 1) {
       
        if (elevio_floorSensor() != -1){
            elevio_doorOpenLamp(1);
            g_doorOpenIndicator = 1;
        }
    }

    g_stopIndicator = 1;
    elevio_stopLamp(0);
}



State fsm_nextState() {


    if (elevio_stopButton() == 1) {
        return STOP;
    }

    if (g_doorOpenIndicator == 1) {
        return DOOR_OPEN;
    }
   
    if (ord_checkForIncompletedOrders() != 0) {
        return MOVING;
    }

    return IDLE;

}


void fsm_runFiniteStateMachine(){
    while (1)
    {
        ord_updateLastKnownFloor(); //Oppdaterer forrige etasje
        ord_setStopOrders(); //Tar i mot en ordre
        elevio_floorIndicator(g_lastKnownFloor); //Setter etasjelys

        State currentState = fsm_nextState(); //Setter heis i neste state

        switch (currentState)
        {
        case IDLE:
            fsm_StateIdle();
            break;

        case DOOR_OPEN:
            fsm_StateDoorOpen();
            break;

        case MOVING:
            fsm_StateMoving();
            ctrl_shouldElevatorStop();
            break;

        case STOP:
            fsm_StateStop();
            break;

        default:
            break;
        };
            
    }
    
}