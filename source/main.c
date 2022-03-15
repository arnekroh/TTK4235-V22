#include <signal.h>
#include "StateMachine.h"



int main(){
    
    elevio_init();
    
    ctrl_initElevator(); //Initialiserer heisen
    fsm_runFiniteStateMachine();  //Heisens operasjonsområde

    return 0;
}