#pragma once
#include "Order.h"

/**
 * @file
 * @brief Dette biblioteket håndterer initialisering og styringssystemet til heisen.
 *  
 * 
 */



MotorDirection g_lastDir;
MotorDirection g_currentDir;

int g_doorOpenIndicator;
int g_stopIndicator;



/**
 * @brief Initialiserer heisen ved å kjøre den til første etasje. Tar ikke imot ordre under initialiseringen og skrur av lys.
 * 
 */
void ctrl_initElevator();

/**
 * @brief Sjekker om heisen skal stoppe i etasje på bakgrunn av heisens retning og om det er et stopkall i etasjen den passerer. 
 * 
 */
void ctrl_shouldElevatorStop();

/**
 * @brief Beregner neste Motordirection. Funksjonen sjekker hva @p g_lastDir er satt til og om det finnes uferdig ordre over eller under nåværende etasje.
 * @return Neste MotorDirection til heisen.
 */
MotorDirection ctrl_nextDir(int offsetFloor);

