#include "Order.h"


void ord_setStopOrders(){
 
    for(int i = 0; i <=3; i++){
        if(elevio_callButton(i, BUTTON_CAB)){
            g_stopOrders[i+ 2*N_FLOORS] = 1;
            elevio_buttonLamp(i, BUTTON_CAB, 1);
        }
        else if (elevio_callButton(i, BUTTON_HALL_UP))
        {
            g_stopOrders[i+N_FLOORS] = 1;
            elevio_buttonLamp(i, BUTTON_HALL_UP, 1);
        }
        else if (elevio_callButton(i, BUTTON_HALL_DOWN)) 
        {
            g_stopOrders[i] = 1;
            elevio_buttonLamp(i, BUTTON_HALL_DOWN, 1);
        }  
    }
}


void ord_deleteCompletedOrder() {
    int floor = elevio_floorSensor();

    g_stopOrders[floor] = 0;
    g_stopOrders[floor+N_FLOORS] = 0;
    g_stopOrders[floor+2*N_FLOORS] = 0;

    elevio_buttonLamp(floor, BUTTON_CAB, 0);
    elevio_buttonLamp(floor, BUTTON_HALL_DOWN, 0);
    elevio_buttonLamp(floor, BUTTON_HALL_UP, 0);
}


void ord_clearAllOrders() {
    
    for (int i = 0; i < 3*N_FLOORS; i++) {
        g_stopOrders[i] = 0;
    }

    for (int i = 0; i < N_FLOORS; i++) {
        elevio_buttonLamp(i, BUTTON_CAB, 0);
        elevio_buttonLamp(i, BUTTON_HALL_DOWN, 0);
        elevio_buttonLamp(i, BUTTON_HALL_UP, 0);
    }
}


void ord_updateLastKnownFloor(){

    int floor = elevio_floorSensor();
    if (floor != -1)
    {
        g_lastKnownFloor = floor;
    }
}


int ord_checkForIncompletedOrders() { 
    for (int i =0; i<3*N_FLOORS; i++) {
        if (g_stopOrders[i] == 1) {
            return 1;
        }
    }
    return 0;
}


int ord_incompletedOrdersAtFloorAndAbove(int offsetFloor) {
    for (int i = g_lastKnownFloor+offsetFloor; i < N_FLOORS; i++) {
        if ( g_stopOrders[i] == 1 || g_stopOrders[i + N_FLOORS] == 1 || g_stopOrders[i + 2*N_FLOORS] == 1){
            return 1;
        }
    }
    return 0;
}


int ord_incompletedOrdersAtFloorAndBelow(int offsetFloor) {
    for (int i = g_lastKnownFloor-offsetFloor; i >= 0; i--){ 
        if ( g_stopOrders[i] == 1 || g_stopOrders[i + N_FLOORS] == 1 || g_stopOrders[i + 2*N_FLOORS] == 1){
            return 1;
        }
    }
    return 0;
}