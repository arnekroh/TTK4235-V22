#pragma once

/**
 * @file
 * @brief Dette biblioteket implementerer tilstandsmaskinen til heisen.
 * 
 */

#include "Controll.h"

typedef enum {
    IDLE, DOOR_OPEN, MOVING, STOP
} State;



/**
 * @brief Setter motordirection til @c DIRN_STOP og slår av door open lyset kun hvis heisen befinner seg i en etasje.
 * 
 */
void fsm_StateIdle();

/**
 * @brief Sletter fullført ordre. Setter motordirection til @c DIRN_STOP og slår på door open lyset i 3 sekunder.
 * Tester for stoppknappen og obstruksjonsbryteren. Skrur til slutt av door open lyset.
 * 
 * 
 */
void fsm_StateDoorOpen();

/**
 * @brief Skrur av door open lyset og setter ny motor direction ( @p g_currentDir) og oppdaterer @p g_lastDir. 
 * 
 */
void fsm_StateMoving();

/**
 * @brief Setter motor direction til @c DIRN_STOP og skrur på stop lamp. Sletter alle ordre. 
 * Åpner døren om heisen befinner seg i en etasje og gir beskjed til @c StateDoorOpen() om at døren skal holdes åpen i 3 sekunder etter at stoppknappen slippes. 
 * Når stopknappen slippes skrus stop lamp av.
 * 
 */
void fsm_StateStop();

/**
 * @brief Setter heisen i state @c STOP dersom stopknappen er trykket, @c DOOR_OPEN dersom @p g_doorOpenIndicator er 1, @c MOVING om the finnes uferdige ordre, ellers settes den til @c IDLE.
 * 
 * @return verdi av typen @c States
 */
State fsm_nextState();

/**
 * @brief Heisens operasjonsområde. Switch case som setter heisen i tilstand og utfører tilhørende funksjon.
 * 
 */
void fsm_runFiniteStateMachine();