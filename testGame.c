#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "game.h"

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}


#define TEST_DISCIPLINES {STUDENT_BQN, STUDENT_BPS, STUDENT_MMONEY, \
                STUDENT_MJ, STUDENT_MTV, STUDENT_MMONEY, STUDENT_BPS, \
                STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, STUDENT_BQN, \
                STUDENT_MJ, STUDENT_BQN, STUDENT_BQN, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_THD, STUDENT_MT}
#define TEST_DICE {2,3,3,4,4,5,5,6,6,7,8,8,9,9,10,10,11,11,12}

void testThrowDice();
void testGetWhoseTurn ();
void testGetMostARCs ();
void testgetMostPublications ();
void testGetDiscipline ();
void testGetDiceValue ();

int main(int argc, char *argv[]) {

    //TODO:  tests
    testThrowDice ();
    testGetWhoseTurn ();
    testGetMostARCs ();
    testgetMostPublications ();
    testGetDiscipline ();
    testGetDiceValue ();

    /*Checklist:
    
    **** DONE Game newGame (int discipline[], int dice[]); Tested in every function
    **** DONE void disposeGame (Game g); Tested in every function
    ** void makeAction (Game g, action a); Tested in every function. Needs more tests.
    **** void throwDice (Game g, int diceScore); testThrowDice ();
    **** int getDiscipline (Game g, int regionID); testGetDiscipline ();
    **** int getDiceValue (Game g, int regionID); testGetDiceValue ();
    **** int getMostARCs (Game g); testGetMostARCs ();
    **** int getMostPublications (Game g); testgetMostPublications ();
    **** int getTurnNumber (Game g); testThrowDice ();
    **** int getWhoseTurn (Game g); testThrowDice ();
    **** int getCampus(Game g, path pathToVertex);
    int getARC(Game g, path pathToEdge); 
    int isLegalAction (Game g, action a);
    **** int getARCs (Game g, int player);testGetMostARCs ();
    int getGO8s (Game g, int player);
    **** int getCampuses (Game g, int player);
    int getIPs (Game g, int player);
    **** int getPublications (Game g, int player);
    int getStudents (Game g, int player, int discipline); KAYA
    int getExchangeRate (Game g, int player, RUBY
                         int disciplineFrom, int disciplineTo); 
    */

    //clean up: keep your memory beautiful
    //disposeGame(testGame);


    printf("All tests passed!!!\nYou are awesome!");

    return EXIT_SUCCESS;
}

// void testMakeAction () {

// }
 
// This also tests "getWhoseTurn" and "getTurnNumber"
void testThrowDice () {
    int disciplines[NUM_REGIONS] = DEFAULT_DISCIPLINES;
    int dice[NUM_REGIONS] = DEFAULT_DICE;
    Game testGame = newGame(disciplines, dice);

    assert (getWhoseTurn (testGame) == 0);
    assert (getTurnNumber (testGame) == -1);
    throwDice(testGame, 6);
    assert (getWhoseTurn (testGame) == 1);
    assert (getTurnNumber (testGame) == 0);
    throwDice(testGame, 2);
    assert (getWhoseTurn (testGame) == 2);
    assert (getTurnNumber (testGame) == 1);
    throwDice(testGame, 3);
    assert (getWhoseTurn (testGame) == 3);
    assert (getTurnNumber (testGame) == 2);
    throwDice(testGame, 2);
    assert (getWhoseTurn (testGame) == 1);
    assert (getTurnNumber (testGame) == 3);

    disposeGame (testGame);
}

void testGetWhoseTurn () {
    int disciplines[NUM_REGIONS] = DEFAULT_DISCIPLINES;
    int dice[NUM_REGIONS] = DEFAULT_DICE;
    Game testGame = newGame(disciplines, dice);

    assert (getWhoseTurn (testGame) == NO_ONE);
    throwDice (testGame, 3);
    int currentTurn = getWhoseTurn (testGame);
    throwDice (testGame, 1);
    assert (getWhoseTurn (testGame) == (currentTurn + 1) % NUM_UNIS);
    throwDice (testGame, 2);
    assert (getWhoseTurn (testGame) == (currentTurn + 2) % NUM_UNIS);
    throwDice (testGame, 2);
    assert (getWhoseTurn (testGame) == (currentTurn + 3) % NUM_UNIS);

    disposeGame (testGame);
}

// Also tests getARCs
void testGetMostARCs () {
    int disciplines[NUM_REGIONS] = DEFAULT_DISCIPLINES;
    int dice[NUM_REGIONS] = DEFAULT_DICE;
    Game testGame = newGame(disciplines, dice);    

    assert (getMostARCs (testGame) == NO_ONE);
    assert (getARCs (testGame, UNI_A) == 0);

    action createARC;
    createARC.actionCode = OBTAIN_ARC;
    createARC.path = {'L'}; 

    makeAction (testGame, createARC);
    int currentMostARCs = getWhoseTurn (testGame);
    assert (getMostARCs (testGame) == getWhoseTurn (testGame));
    assert (getARCs (testGame, getWhoseTurn (testGame)) == 1);

    throwDice (testGame, 3);

    createARC.path = {'LR'};
    makeAction (testGame, createARC);
    createARC.path = {'LRL'};
    makeAction (testGame, createARC);
    int currentMostARCs = getWhoseTurn (testGame);
    assert (getMostARCs (testGame) == currentMostARCs);
    assert (getARCs (testGame, currentMostARCs) == 2);


    throwDice (testGame, 2);

    createARC.path = {'R'};
    makeAction (testGame, createARC);
    createARC.path = {'RL'};
    makeAction (testGame, createARC);
    assert (getMostARCs (testGame) == currentMostARCs);
    assert (getARCs (testGame, getWhoseTurn (testGame)) == 2);

    createARC.path = {'RLR'};
    makeAction (testGame, createARC);
    assert (getMostARCs (testGame) == getWhoseTurn (testGame));
    assert (getARCs (testGame, getWhoseTurn (testGame)) == 3);

    printf("getMostARCs works\n");

    disposeGame (testGame);
}

// Also tests getPublications
void testgetMostPublications () {
    Game testGame = newGame(disciplines, dice);    
    assert (getMostPublications (testGame) == NO_ONE);
    assert (getPublications (testGame, UNI_A) == 0);

    action obtainPublication;
    obtainPublication.actionCode = OBTAIN_PUBLICATION;
    makeAction (testGame, obtainPublication);
    assert (getMostPublications (testGame) == getWhoseTurn (testGame));
    assert (getPublications (testGame, getWhoseTurn (testGame)) == 1);

    throwDice (testGame, 3);

    makeAction (testGame, obtainPublication);
    makeAction (testGame, obtainPublication);
    int currentMostARCs = getWhoseTurn (testGame);
    assert (getMostPublications (testGame) == currentMostARCs);
    assert (getPublications (testGame, currentMostARCs) == 2);    

    throwDice (testGame, 2);

    makeAction (testGame, obtainPublication);
    makeAction (testGame, obtainPublication);
    assert (getMostPublications (testGame) == currentMostARCs);
    assert (getPublications (testGame, getWhoseTurn (testGame)) == 2);

    makeAction (testGame, obtainPublication);
    assert (getMostPublications (testGame) == getWhoseTurn (testGame));
    assert (getPublications (testGame, getWhoseTurn (testGame)) == 3);  

    disposeGame (testGame);
}

void testGetDiscipline () {
    int disciplines[NUM_REGIONS] = DEFAULT_DISCIPLINES;
    int dice[NUM_REGIONS] = DEFAULT_DICE;
    Game testGame = newGame(disciplines, dice);  

    assert (getDiscipline (testGame, 0) == DEFAULT_DISCIPLINES[0]);
    assert (getDiscipline (testGame, 1) == DEFAULT_DISCIPLINES[1]);
    assert (getDiscipline (testGame, 2) == DEFAULT_DISCIPLINES[2]);
    assert (getDiscipline (testGame, 3) == DEFAULT_DISCIPLINES[3]);
    assert (getDiscipline (testGame, 4) == DEFAULT_DISCIPLINES[4]);
    assert (getDiscipline (testGame, 5) == DEFAULT_DISCIPLINES[5]);
    assert (getDiscipline (testGame, 6) == DEFAULT_DISCIPLINES[6]);
    assert (getDiscipline (testGame, 7) == DEFAULT_DISCIPLINES[7]);
    assert (getDiscipline (testGame, 9) == DEFAULT_DISCIPLINES[9]);
    assert (getDiscipline (testGame, 10) == DEFAULT_DISCIPLINES[10]);
    assert (getDiscipline (testGame, 11) == DEFAULT_DISCIPLINES[11]);
    assert (getDiscipline (testGame, 12) == DEFAULT_DISCIPLINES[12]);
    assert (getDiscipline (testGame, 13) == DEFAULT_DISCIPLINES[13]);
    assert (getDiscipline (testGame, 14) == DEFAULT_DISCIPLINES[14]);
    assert (getDiscipline (testGame, 15) == DEFAULT_DISCIPLINES[15]);
    assert (getDiscipline (testGame, 16) == DEFAULT_DISCIPLINES[16]);
    assert (getDiscipline (testGame, 17) == DEFAULT_DISCIPLINES[17]);
    assert (getDiscipline (testGame, 18) == DEFAULT_DISCIPLINES[18]);
    assert (getDiscipline (testGame, 19) == DEFAULT_DISCIPLINES[19]);

    disposeGame (testGame);

    disciplines[] = TEST_DISCIPLINES;
    dice[] = TEST_DICE;
    Game testGame2 = newGame(disciplines, dice);  

    assert (getDiscipline (testGame2, 0) == DEFAULT_DISCIPLINES[0]);
    assert (getDiscipline (testGame2, 1) == DEFAULT_DISCIPLINES[1]);
    assert (getDiscipline (testGame2, 2) == DEFAULT_DISCIPLINES[2]);
    assert (getDiscipline (testGame2, 3) == DEFAULT_DISCIPLINES[3]);
    assert (getDiscipline (testGame2, 4) == DEFAULT_DISCIPLINES[4]);
    assert (getDiscipline (testGame2, 5) == DEFAULT_DISCIPLINES[5]);
    assert (getDiscipline (testGame2, 6) == DEFAULT_DISCIPLINES[6]);
    assert (getDiscipline (testGame2, 7) == DEFAULT_DISCIPLINES[7]);
    assert (getDiscipline (testGame2, 9) == DEFAULT_DISCIPLINES[9]);
    assert (getDiscipline (testGame2, 10) == DEFAULT_DISCIPLINES[10]);
    assert (getDiscipline (testGame2, 11) == DEFAULT_DISCIPLINES[11]);
    assert (getDiscipline (testGame2, 12) == DEFAULT_DISCIPLINES[12]);
    assert (getDiscipline (testGame2, 13) == DEFAULT_DISCIPLINES[13]);
    assert (getDiscipline (testGame2, 14) == DEFAULT_DISCIPLINES[14]);
    assert (getDiscipline (testGame2, 15) == DEFAULT_DISCIPLINES[15]);
    assert (getDiscipline (testGame2, 16) == DEFAULT_DISCIPLINES[16]);
    assert (getDiscipline (testGame2, 17) == DEFAULT_DISCIPLINES[17]);
    assert (getDiscipline (testGame2, 18) == DEFAULT_DISCIPLINES[18]);
    assert (getDiscipline (testGame2, 19) == DEFAULT_DISCIPLINES[19]);

    disposeGame (testGame2);

}


void testGetDiceValue () {
    int disciplines[NUM_REGIONS] = DEFAULT_DISCIPLINES;
    int dice[NUM_REGIONS] = DEFAULT_DICE;
    Game testGame = newGame(disciplines, dice);  

    assert (getDiceValue (testGame, 0) == DEFAULT_DICE[0]);
    assert (getDiceValue (testGame, 1) == DEFAULT_DICE[1]);
    assert (getDiceValue (testGame, 2) == DEFAULT_DICE[2]);
    assert (getDiceValue (testGame, 3) == DEFAULT_DICE[3]);
    assert (getDiceValue (testGame, 4) == DEFAULT_DICE[4]);
    assert (getDiceValue (testGame, 5) == DEFAULT_DICE[5]);
    assert (getDiceValue (testGame, 6) == DEFAULT_DICE[6]);
    assert (getDiceValue (testGame, 7) == DEFAULT_DICE[7]);
    assert (getDiceValue (testGame, 9) == DEFAULT_DICE[9]);
    assert (getDiceValue (testGame, 10) == DEFAULT_DICE[10]);
    assert (getDiceValue (testGame, 11) == DEFAULT_DICE[11]);
    assert (getDiceValue (testGame, 12) == DEFAULT_DICE[12]);
    assert (getDiceValue (testGame, 13) == DEFAULT_DICE[13]);
    assert (getDiceValue (testGame, 14) == DEFAULT_DICE[14]);
    assert (getDiceValue (testGame, 15) == DEFAULT_DICE[15]);
    assert (getDiceValue (testGame, 16) == DEFAULT_DICE[16]);
    assert (getDiceValue (testGame, 17) == DEFAULT_DICE[17]);
    assert (getDiceValue (testGame, 18) == DEFAULT_DICE[18]);
    assert (getDiceValue (testGame, 19) == DEFAULT_DICE[19]);

    disposeGame (testGame);

    disciplines[] = TEST_DISCIPLINES;
    dice[] = TEST_DICE;
    Game testGame2 = newGame(disciplines, dice);  

    assert (getDiceValue (testGame2, 0) == DEFAULT_DICE[0]);
    assert (getDiceValue (testGame2, 1) == DEFAULT_DICE[1]);
    assert (getDiceValue (testGame2, 2) == DEFAULT_DICE[2]);
    assert (getDiceValue (testGame2, 3) == DEFAULT_DICE[3]);
    assert (getDiceValue (testGame2, 4) == DEFAULT_DICE[4]);
    assert (getDiceValue (testGame2, 5) == DEFAULT_DICE[5]);
    assert (getDiceValue (testGame2, 6) == DEFAULT_DICE[6]);
    assert (getDiceValue (testGame2, 7) == DEFAULT_DICE[7]);
    assert (getDiceValue (testGame2, 9) == DEFAULT_DICE[9]);
    assert (getDiceValue (testGame2, 10) == DEFAULT_DICE[10]);
    assert (getDiceValue (testGame2, 11) == DEFAULT_DICE[11]);
    assert (getDiceValue (testGame2, 12) == DEFAULT_DICE[12]);
    assert (getDiceValue (testGame2, 13) == DEFAULT_DICE[13]);
    assert (getDiceValue (testGame2, 14) == DEFAULT_DICE[14]);
    assert (getDiceValue (testGame2, 15) == DEFAULT_DICE[15]);
    assert (getDiceValue (testGame2, 16) == DEFAULT_DICE[16]);
    assert (getDiceValue (testGame2, 17) == DEFAULT_DICE[17]);
    assert (getDiceValue (testGame2, 18) == DEFAULT_DICE[18]);
    assert (getDiceValue (testGame2, 19) == DEFAULT_DICE[19]);

    disposeGame (testGame2);

}

// This also tests getCampuses
void testGetCampus () {
    int disciplines[NUM_REGIONS] = DEFAULT_DISCIPLINES;
    int dice[NUM_REGIONS] = DEFAULT_DICE;
    Game testGame = newGame(disciplines, dice);    

    path currentPoint = "R";
    assert (getCampus (testGame, currentPoint) == VACANT_VERTEX);
    assert (GetCampuses (testGame, UNI_A) == 2);

    action createCampus;
    createCampus.actionCode = OBTAIN_CAMPUS;
    createCampus.path = "R"; 
    makeAction (createCampus);
    int currentTurn = getWhoseTurn (testGame);
    assert (getCampus (testGame, currentPoint) == currentTurn);
    assert (GetCampuses (testGame, currentTurn) == 3);

    currentPoint = "L";
    assert (getCampus (testGame, currentPoint) == VACANT_VERTEX);

    throwDice (testGame, 8);

    currentPoint = "R";
    assert (getCampus (testGame, currentPoint) == currentTurn);
    assert (GetCampuses (testGame, getWhoseTurn (testGame)) == 1);


    createCampus.path = "RL"; 
    makeAction (createCampus);
    currentTurn = getWhoseTurn (testGame);
    assert (getCampus (testGame, currentPoint) == currentTurn);
    assert (GetCampuses (testGame, currentTurn) == 2);

    printf("getMostARCs works\n");

    disposeGame (testGame);
}

void testGetStudents () {
    int disciplines[NUM_REGIONS] = DEFAULT_DISCIPLINES;
    int dice[NUM_REGIONS] = DEFAULT_DICE;
    Game testGame = newGame(disciplines, dice);

    assert (getStudents (testGame, UNI_A, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_A, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MMONEY) == 1);

    throwDice (testGame, 10);

    assert (getStudents (testGame, UNI_A, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_A, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MMONEY) == 2);

    disposeGame (testGame);
}
