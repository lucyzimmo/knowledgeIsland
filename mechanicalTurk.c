/*
 *  Mr Pass.  Brain the size of a planet!
 *
 *  Proundly Created by Richard Buckland
 *  Share Freely Creative Commons SA-BY-NC 3.0. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Game.h"
#include "mechanicalTurk.h"

#define PATH_TO_CAMPUS_A1 ""
#define PATH_TO_CAMPUS_A2 "RLRLRLRLRLL"
#define PATH_TO_CAMPUS_B1 "RRLRL"
#define PATH_TO_CAMPUS_B2 "LRLRLRRLRL"
#define PATH_TO_CAMPUS_C1 "LRLRL"
#define PATH_TO_CAMPUS_C2 "LRLRLLRLRL"

action decideAction (Game g) {

    int currentPlayer = getWhoseTurn (g);
    
    action nextAction;
    nextAction.actionCode = BUILD_GO8;
    if (currentPlayer == UNI_A) {
        strcpy(nextAction.destination, PATH_TO_CAMPUS_A1);
    } else if (currentPlayer == UNI_B) {
        strcpy(nextAction.destination, PATH_TO_CAMPUS_B1);
    } else {
        strcpy(nextAction.destination, PATH_TO_CAMPUS_C1);
    }
    if (!isLegalAction (g, nextAction)) {
        nextAction.actionCode = START_SPINOFF;
        if (!isLegalAction (g, nextAction)) {
            nextAction.actionCode = PASS;
        }
    }   
    return nextAction;
}