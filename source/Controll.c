#include "Controll.h"


void ctrl_initElevator(){
    int floor = elevio_floorSensor();
    if (floor != 0) {
        MotorDirection dir = DIRN_DOWN;
        while(floor != 0) {
            floor = elevio_floorSensor();
            elevio_motorDirection(dir);
        }
        elevio_motorDirection(DIRN_STOP);
    }
    elevio_doorOpenLamp(0);
    elevio_stopLamp(0);
    for (int i = 0; i < N_FLOORS; i++) {
        elevio_buttonLamp(i, BUTTON_CAB, 0);
        elevio_buttonLamp(i, BUTTON_HALL_DOWN, 0);
        elevio_buttonLamp(i, BUTTON_HALL_UP, 0);
    }
    g_doorOpenIndicator = 0;
    g_lastDir = DIRN_UP;
}




MotorDirection ctrl_nextDir(int offsetFloor) { 
    
    switch (g_lastDir)
    {
    case DIRN_DOWN:
        if(ord_incompletedOrdersAtFloorAndBelow(offsetFloor) == 1){
            return DIRN_DOWN;
        }
        else if(ord_incompletedOrdersAtFloorAndAbove(offsetFloor) == 1){
            
            return DIRN_UP;
        }
        else {
            return DIRN_UP;
        }
        break;

    case DIRN_UP:
        if(ord_incompletedOrdersAtFloorAndAbove(offsetFloor) == 1){
            return DIRN_UP;
        }
        else if(ord_incompletedOrdersAtFloorAndBelow(offsetFloor) == 1){
            return DIRN_DOWN;
        }
        else {
            return DIRN_DOWN;
        }
        break;

    default:
        break;
    }
    return DIRN_STOP;
}


void ctrl_shouldElevatorStop() {

    int currentFloor = elevio_floorSensor();
    
    if (currentFloor != -1) {

        switch (g_currentDir) {

        case DIRN_DOWN:

            if (ord_incompletedOrdersAtFloorAndBelow(0) == 1) {

                if(g_stopOrders[currentFloor] == 1 || g_stopOrders[currentFloor + 2*N_FLOORS] == 1){
                    g_doorOpenIndicator = 1;
                }
                else if (ord_incompletedOrdersAtFloorAndBelow(1)!=1){
                    g_doorOpenIndicator = 1;
                }
            }
            break;

        case DIRN_UP:

            if (ord_incompletedOrdersAtFloorAndAbove(0) == 1) {

                if(g_stopOrders[currentFloor + N_FLOORS] == 1 || g_stopOrders[currentFloor + 2*N_FLOORS] == 1){
                    g_doorOpenIndicator = 1;
                }
                else if (ord_incompletedOrdersAtFloorAndAbove(1)!=1){
                    g_doorOpenIndicator = 1;
                }
            }
            break;
        }

    }
    
}


