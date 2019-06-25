#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "Game.h"
#include "mechanicalTurk.h"

#define WINNING_KPI_POINTS 120
#define ARC_KPI_POINTS 2
#define CAMPUS_KPI_POINTS 10
#define GO8_KPI_POINTS 20
#define IP_KPI_POINTS 10
#define MOST_ARCS_KPI_POINTS 10
#define MOST_PUBLICATIONS_KPI_POINTS 10

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

int getKPI (Game g, int player);
void randomize();
int randomNum (int max);
int rollDice ();

int main () {
    int diciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;

    Game g = newGame (diciplines, dice); 
    int gameOver = FALSE;
    while (gameOver == FALSE) {      
        int diceValue = rollDice();    //simulate throw of two dice - we will discuss how to do this in tutorial
                                   // or you may wish to google it and find out how you could do it! 
        diceValue += rollDice();    //roll second dice DIE!
        
        throwDice(g,diceValue);      
        
        action move; //human or mechanicalTurk(AI) decide what they want to do     
        //loop until player action is PASS or player wins     
        while (gameOver == FALSE && move.actionCode != PASS) { 
            move = decideAction(g);
            assert (isLegalAction (g, move) == TRUE);
            if (move.actionCode == START_SPINOFF) { 
                 //decide if outcome is patent or publication
            }         
            makeAction(g, move);             
        } 

        //Check scores here
        int player0Score = getKPI (g, UNI_A);
        int player1Score = getKPI (g, UNI_B);
        int player2Score = getKPI (g, UNI_C);

        if (player0Score >= WINNING_KPI_POINTS 
                || player1Score >= WINNING_KPI_POINTS
                || player2Score >= WINNING_KPI_POINTS) {
            gameOver = TRUE;
        } 
    }
    
    disposeGame (g);
}

//print statistics 
// free memory

int getKPI (Game g, int player) {
    int totalKPI = 0;
    totalKPI += getARCs (g, player) * ARC_KPI_POINTS;
    totalKPI += getCampuses (g, player) * CAMPUS_KPI_POINTS;
    totalKPI += getGO8s (g, player) * GO8_KPI_POINTS;
    if (getMostARCs (g) == player) {
        totalKPI += MOST_ARCS_KPI_POINTS;
    }
    if (getMostPublications (g) == player) {
        totalKPI += MOST_PUBLICATIONS_KPI_POINTS;
    }
    return totalKPI;
}

void randomize() {
    srand((unsigned)time(NULL)) ;
}

int randomNum (int max) {
    randomize();
    return (rand() % max) + 1;
}

int rollDice () {
    return randomNum (6);
}