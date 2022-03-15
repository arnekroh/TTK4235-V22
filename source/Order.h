#pragma once

/**
 * @file
 * @brief Dette biblioteket håndterer ordre, hvordan disse lagres og slettes. 
 * I tillegg utføres tester på om det finnes ubetjente ordre.
 * 
 */

#ifndef elevio
#define elevio
#include "driver/elevio.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int g_stopOrders[3*N_FLOORS]; //[Down 0-3, Up 4-7, CAB 8-11]
int g_lastKnownFloor;

/**
 * @brief Registrerer ordre fra knapp og sender til @p g_stopOrders arrayen
 * 
 */
void ord_setStopOrders();

/**
 * @brief Sletter en fullført ordre
 * 
 */
void ord_deleteCompletedOrder();

/**
 * @brief Sletter alle ordre fra @p g_stopOrders arrayen
 * 
 */
void ord_clearAllOrders();

/**
 * @brief Oppdaterer den globale variabelen @p g_lastKnownFloor som sier hvilken etasje heisen befant deg i sist.
 * 
 */
void ord_updateLastKnownFloor();

/**
 * @brief Sjekker om det finnes en ubetjent ordre
 * 
 * @return 1 dersom det finnes aktive ordre , ellers 0.   
 */
int ord_checkForIncompletedOrders();

/**
 * @brief sjekker om det finnes en ubetjent ordre over eller i heisens nåværende etasje
 * 
 * @param[in] offsetFloor brukes for å la være å sjekke i nåværende etasje
 * @return 1 dersom det finnes ordre i etasjene over og etasjen heisen nå befinner seg i, ellers 0.  
 */
int ord_incompletedOrdersAtFloorAndAbove(int offsetFloor);

/**
 * @brief Sjekker om det finnes en ubetjent ordre under eller i heisens nåværende etasje
 * 
 * @param[in] offsetFloor brukes for å la være å sjekke i nåværende etasje
 * @return 1 dersom det finnes ordre i etasjene under og etasjen heisen nå befinner seg i, ellers 0. 
 */
int ord_incompletedOrdersAtFloorAndBelow(int offsetFloor);
