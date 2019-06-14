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
void isLegalAction();
void testGetARC();
void testGetGO8s();

int main(int argc, char *argv[]) {

    //TODO:  tests
    testThrowDice ();
    testGetWhoseTurn ();
    testGetMostARCs ();
    testgetMostPublications ();
    testGetDiscipline ();
    testGetDiceValue ();
    isLegalAction();
    testGetARC();
    testGetGO8s();

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

void testGetMostARCs () {
    int disciplines[NUM_REGIONS] = DEFAULT_DISCIPLINES;
    int dice[NUM_REGIONS] = DEFAULT_DICE;
    Game testGame = newGame(disciplines, dice);    
    fillResources (testGame);

    assert (getMostARCs (testGame) == NO_ONE);
    assert (getARCs (testGame, UNI_A) == 0);

    action createARC;
    createARC.actionCode = OBTAIN_ARC;
    createARC.path = {"L"}; 

    makeAction (testGame, createARC);
    int currentMostARCs = getWhoseTurn (testGame);
    assert (getMostARCs (testGame) == getWhoseTurn (testGame));
    assert (getARCs (testGame, getWhoseTurn (testGame)) == 1);

    throwDice (testGame, 3);

    createARC.path = {"LR"};
    makeAction (testGame, createARC);
    createARC.path = {"LRL"};
    makeAction (testGame, createARC);
    int currentMostARCs = getWhoseTurn (testGame);
    assert (getMostARCs (testGame) == currentMostARCs);
    assert (getARCs (testGame, currentMostARCs) == 2);


    throwDice (testGame, 2);

    createARC.path = {"R"};
    makeAction (testGame, createARC);
    createARC.path = {"RL"};
    makeAction (testGame, createARC);
    assert (getMostARCs (testGame) == currentMostARCs);
    assert (getARCs (testGame, getWhoseTurn (testGame)) == 2);

    createARC.path = {"RLR"};
    makeAction (testGame, createARC);
    assert (getMostARCs (testGame) == getWhoseTurn (testGame));
    assert (getARCs (testGame, getWhoseTurn (testGame)) == 3);

    printf("getMostARCs works\n");

    disposeGame (testGame);
}

// Also tests getPublications
void testgetMostPublications () {
    Game testGame = newGame(disciplines, dice); 
    fillResources ();

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

    while (i < 20) {
        assert (getDiscipline (testGame2, i) == DEFAULT_DISCIPLINES[i]);
        i ++;
    }
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
    fillResources (testGame)   

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

    assert (getStudents (testGame, UNI_B, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_B, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_B, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MMONEY) == 1);

    assert (getStudents (testGame, UNI_C, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_C, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MMONEY) == 1);

    throwDice (testGame, 11);

    assert (getStudents (testGame, UNI_A, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_A, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MTV) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MMONEY) == 1);

    assert (getStudents (testGame, UNI_B, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_B, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_B, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MMONEY) == 1);

    assert (getStudents (testGame, UNI_C, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_C, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MMONEY) == 1);

    while (getWhoseTurn (testGame) != UNI_B) {
        throwDice (testGame, 12);
    }
    
    assert (getWhoseTurn (testGame) == UNI_B);    

    action createARC;
    createARC.actionCode = OBTAIN_ARC;

// This path is invalid!
    createARC.path = {"LLRLRR"};
    makeAction (createARC);
// This path is invalid!
    createARC.path = {"LLRLRRL"};
    makeAction (createARC);

    action createCampus;
    createCampus.actionCode = OBTAIN_CAMPUS;
// This path is invalid!
    createCampus.path = {"LLRLRRL"}
    makeAction (createCampus);

    assert (getCampuses (testGame, UNI_B) == 3);
    assert (getARCs (testGame, UNI_B) == 2);

    assert (getStudents (testGame, UNI_A, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_A, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MJ) == 2);
    assert (getStudents (testGame, UNI_A, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MTV) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MMONEY) == 1);

    assert (getStudents (testGame, UNI_B, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BPS) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BQN) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_MJ) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_MT) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MMONEY) == 1);

    assert (getStudents (testGame, UNI_C, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_C, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MMONEY) == 1);

    throwDice (testGame, 6);

    assert (getWhoseTurn (testGame) == UNI_C);

    assert (getStudents (testGame, UNI_A, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_A, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MJ) == 2);
    assert (getStudents (testGame, UNI_A, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MTV) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MMONEY) == 1);

    assert (getStudents (testGame, UNI_B, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BPS) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BQN) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MT) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MMONEY) == 1);

    assert (getStudents (testGame, UNI_C, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_C, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MMONEY) == 1);

    throwDice (10)
    assert (getWhoseTurn (testGame) == UNI_A);
    throwDice (10)
    assert (getWhoseTurn (testGame) == UNI_B);
    throwDice (6)
    assert (getWhoseTurn (testGame) == UNI_C);

    while (getWhoseTurn (testGame) != UNI_B) {
        throwDice (testGame, 12);
    }
    
    assert (getWhoseTurn (testGame) == UNI_B);  

    assert (getStudents (testGame, UNI_A, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_A, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MJ) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MTV) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MMONEY) == 1);

    assert (getStudents (testGame, UNI_B, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BPS) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BQN) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_MJ) == 2);
    assert (getStudents (testGame, UNI_B, STUDENT_MT) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MMONEY) == 3);

    assert (getStudents (testGame, UNI_C, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_C, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MMONEY) == 1);

    action createGO8;
    createGO8.actionCode = BUILD_GO8;
// This path is invalid!
    createGO8.path = {"LLRLRRL"}

    makeAction (testGame, createGO8);

    assert (getStudents (testGame, UNI_A, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_A, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MJ) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MTV) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MMONEY) == 1);

    assert (getStudents (testGame, UNI_B, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BPS) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BQN) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_MJ) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_MT) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MMONEY) == 0);

    assert (getStudents (testGame, UNI_C, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_C, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MMONEY) == 1);

    assert (getGO8s (testGame, UNI_B));

    throwDice (9);

    assert (getStudents (testGame, UNI_A, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_A, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MJ) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MTV) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MMONEY) == 1);

    assert (getStudents (testGame, UNI_B, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BPS) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BQN) == 2);
    assert (getStudents (testGame, UNI_B, STUDENT_MJ) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_MT) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MMONEY) == 0);

    assert (getStudents (testGame, UNI_C, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_C, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MT) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MMONEY) == 1);

    disposeGame (testGame);
}

void fillResources (Game testGame) {
    while (i <= 12) {
        if (i != 7) {
            while (j < 30) {
                throwDice (testGame, i);
                j ++;
            }
        }
        i ++;
    }
}

void isLegalAction() {		
    printf("Testing retraining.\n");		
         action retraining = { RETRAIN_STUDENTS, "",		
            STUDENT_BPS, STUDENT_THD };		
         while (retraining.disciplineFrom < STUDENT_MMONEY) {		
            assert(isLegalAction(testGame, retraining));		
            ++retraining.disciplineFrom;		
         }		
         assert(!isLegalAction(testGame, retraining));		
         printf("You can't retrain THDs :(\n");		
         retraining.disciplineFrom = STUDENT_THD;		
         retraining.disciplineTo = STUDENT_MMONEY;		
         assert(!isLegalAction(testGame, retraining));		
    		
    printf("Testing pass.\n");		
    throwDice(testGame, 8);		
    action pass = { PASS, "", 0, 0 };		
    assert(isLegalAction(testGame, pass));		
      }		
    //testing illegality of upgrading campus		
    action makeGO8 = { BUILD_GO8, "", 0, 0 };		
    assert(!isLegalAction(testGame, makeGO8));		
    //testing illegality of upgrading campus to GO8		
    action makeGO8 = { BUILD_GO8, B_START "BLL", 0, 0 };		
    assert(isLegalAction(testGame, makeGO8));		
    makeAction(testGame, makeGO8);		
}
void testGetGO8s(void) {		
   		
   printf("Begin testGetGO8s test.\n");		
   Game testGame = NULL;		
   int i;		
   		
   // initialise game		
   int disciplines[NUM_REGIONS];		
   int dice[NUM_REGIONS];		
   i = 0;		
   while (i < NUM_REGIONS) {		
      disciplines[i] = STUDENT_BPS;		
      dice[i] = 6;		
      ++i;		
   }		
   testGame = newGame(disciplines, dice);		
   		
   // give everyone lots of resources		
   i = 0;		
   while (i < 3000) {		
      // firstly give everyone lots of STUDENT_BPS		
      throwDice(testGame, 6);		
      i++;		
   }		
   i = 0;		
   while (i < 3) {		
      // then retrain some of the STUDENT_BPS to other disciplines		
      throwDice(testGame, 6);		
      int j = 0;		
      while (j < 100) {		
         action retrain = { RETRAIN_STUDENTS, "", STUDENT_BPS, -1 };		
         retrain.disciplineTo = STUDENT_BQN;		
         makeAction(testGame, retrain);		
         retrain.disciplineTo = STUDENT_MJ;		
         makeAction(testGame, retrain);		
         retrain.disciplineTo = STUDENT_MTV;		
         makeAction(testGame, retrain);		
         retrain.disciplineTo = STUDENT_MMONEY;		
         makeAction(testGame, retrain);		
         j++;		
      }		
      i++;		
   }		
   		
   // Terra Nullis condition		
   // At the start, no one has any arcs		
   assert(getGO8s (testGame, UNI_A) == 0);		
   assert(getGO8s (testGame, UNI_B) == 0);		
   assert(getGO8s (testGame, UNI_C) == 0);		
   		
   // Start with Player A's turn. Player A will make 2 arc grants and		
   // build a campus		
   throwDice(testGame, 6);		
   // Making first arc		
   {		
      action makeARC = { OBTAIN_ARC, "L", 0 , 0 };		
      makeAction(testGame, makeARC);		
   }		
   // Second arc, then campus then convert to GO8		
   {		
      action makeARC = { OBTAIN_ARC, "LR", 0 , 0 };		
      makeAction(testGame, makeARC);		
      		
      action buildCampus = { BUILD_CAMPUS, "LR", 0 , 0 };		
      makeAction(testGame, buildCampus);		
      assert(getGO8s (testGame, UNI_A) == 0);		
      assert(getGO8s (testGame, UNI_B) == 0);		
      assert(getGO8s (testGame, UNI_C) == 0);		
   }		
   {		
      action buildGO8 = { BUILD_GO8, "LR", 0 , 0 };		
      makeAction(testGame, buildGO8);		
      assert(getGO8s (testGame, UNI_A) == 1);		
      assert(getGO8s (testGame, UNI_B) == 0);		
      assert(getGO8s (testGame, UNI_C) == 0);		
   }		
   		
   // Now go to player B's turn. Player B will build 4 arcs, with a		
   // campus at each secone one, and then convert them into GO8s		
   // after creating each campus		
   throwDice(testGame, 6);		
   // Making first arc		
   {		
      action makeARC = { OBTAIN_ARC, B_START "B", 0 , 0 };		
      makeAction(testGame, makeARC);		
   }		
   // Second arc, then campus then convert to GO8		
   {		
      action makeARC = { OBTAIN_ARC, B_START "BL", 0 , 0 };		
      makeAction(testGame, makeARC);		
      		
      action buildCampus = { BUILD_CAMPUS, B_START "BL", 0 , 0 };		
      makeAction(testGame, buildCampus);		
      assert(getGO8s (testGame, UNI_A) == 1);		
      assert(getGO8s (testGame, UNI_B) == 0);		
      assert(getGO8s (testGame, UNI_C) == 0);		
   }		
   // Now converting it to GO8		
   {		
      action buildGO8 = { BUILD_GO8, B_START "BL", 0 , 0 };		
      makeAction(testGame, buildGO8);		
      assert(getGO8s (testGame, UNI_A) == 1);		
      assert(getGO8s (testGame, UNI_B) == 1);		
      assert(getGO8s (testGame, UNI_C) == 0);		
   }		
   // Making next 2 arcs		
   {		
      action makeARC = { OBTAIN_ARC, B_START "BLR", 0 , 0 };		
      makeAction(testGame, makeARC);		
   }		
   // Second arc, then campus then convert to GO8		
   {		
      action makeARC = { OBTAIN_ARC, B_START "BLRL", 0 , 0 };		
      makeAction(testGame, makeARC);		
      		
      action buildCampus = { BUILD_CAMPUS, B_START "BLRL", 0 , 0 };		
      makeAction(testGame, buildCampus);		
      assert(getGO8s (testGame, UNI_A) == 1);		
      assert(getGO8s (testGame, UNI_B) == 1);		
      assert(getGO8s (testGame, UNI_C) == 0);		
      		
      action buildGO8 = { BUILD_GO8, B_START "BLRL", 0 , 0 };		
      makeAction(testGame, buildGO8);		
      assert(getGO8s (testGame, UNI_A) == 1);		
      assert(getGO8s (testGame, UNI_B) == 2);		
      assert(getGO8s (testGame, UNI_C) == 0);		
   }		
   		
   // Now on to C's turn. C will make 3 arcs, and then a campus		
   // then convert it to a GO8		
   throwDice(testGame, 6);		
   {		
      action makeARC = { OBTAIN_ARC, C_START "L", 0 , 0 };		
      makeAction(testGame, makeARC);		
   }		
   // Second arc, then campus then convert to GO8		
   {		
      action makeARC = { OBTAIN_ARC, C_START "LL", 0 , 0 };		
      makeAction(testGame, makeARC);		
      		
      action buildCampus = { BUILD_CAMPUS, C_START "LL", 0 , 0 };		
      makeAction(testGame, buildCampus);		
      assert(getGO8s (testGame, UNI_A) == 1);		
      assert(getGO8s (testGame, UNI_B) == 2);		
      assert(getGO8s (testGame, UNI_C) == 0);		
      		
      action buildGO8 = { BUILD_GO8, C_START "LL", 0 , 0 };		
      makeAction(testGame, buildGO8);		
      assert(getGO8s (testGame, UNI_A) == 1);		
      assert(getGO8s (testGame, UNI_B) == 2);		
      assert(getGO8s (testGame, UNI_C) == 1);		
   }		
   		
   // Finally, converting A's primary campus into a GO8		
   throwDice(testGame, 6);		
   {		
      action buildGO8 = { BUILD_GO8, "", 0 , 0 };		
      makeAction(testGame, buildGO8);		
      assert(getGO8s (testGame, UNI_A) == 2);		
      assert(getGO8s (testGame, UNI_B) == 2);		
      assert(getGO8s (testGame, UNI_C) == 1);		
   }		
   				
   disposeGame(testGame);		
   printf("All tests passed - You are awesome!\n");		
}		

void testGetARC() {		
   printf("testing GetArc.\n");		
   Game testing;		
   {		
      int disciplines[] = DEFAULT_DISCIPLINES;		
      int dice[] = {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};		
      testing = newGame(disciplines, dice);		
   }		
   {		
      char* startingPaths[6] = { "RB", "RLRLRLRLRLLLB",		
         "RRLRLLB", "LRLRLRRLRL",		
         "RRLRLLRLRLLB","LRLRL"} ;		
      int i = 0;		// }
      while (i < 6) {		
         char path[PATH_LIMIT];		
         		
         sprintf(path, "%s%s", startingPaths[i], "R"); //adds startingPaths[i] and "R" to path = creates path		
         assert(getARC(testing, path) == VACANT_ARC);		
         sprintf(path, "%s%s", startingPaths[i], "B");		
         assert(getARC(testing, path) == VACANT_ARC);		
         ++i;		
      }		
      		
      throwDice(testing, 8);		
      //three paths test 		
      {		
         action makeARC = { OBTAIN_ARC, "", 0, 0 };		
         strcat(makeARC.destination, startingPaths[0]);		
         i = 0;		
         while (i < 3) {		
            strcat(makeARC.destination, "R");		
            assert(getARC(testing, makeARC.destination) == VACANT_ARC);		
            makeAction(testing, makeARC);		
            assert(getARC(testing, makeARC.destination) == ARC_A);		
            ++i;		
         }		
      }		
      		
      i = 1;		
      while (i < 6) {		
         char path[PATH_LIMIT];		
         		
         sprintf(path, "%s%s", startingPaths[i], "R"); //adds startingPaths[i] and "R" to path = creates path		
         assert(getARC(testing, path) == VACANT_ARC);		
         sprintf(path, "%s%s", startingPaths[i], "B");		
         assert(getARC(testing, path) == VACANT_ARC);		
         ++i;		
      }		
      		
      throwDice(testing, 8);		
      		
      //Player B		
      {		
         action makeARC = { OBTAIN_ARC, "", 0, 0 };		
         strcat(makeARC.destination, startingPaths[3]);		
         i = 0;		
         while (i < 3) {		
            sprintf(makeARC.destination, "R");		
            assert(getARC(testing, makeARC.destination) == VACANT_ARC);		
            makeAction(testing, makeARC);		
            assert(getARC(testing, makeARC.destination) == ARC_B);		
            ++i;		
         }		
      }		
      		
      throwDice(testing, 8);		
      //observing other player paths		
      {		
         char path[PATH_LIMIT];		
         sprintf(path, "%s", startingPaths[0]);		
         i = 0;		
         while (i < 3) {		
            strcat(path, "R"); //add's R to path		
            assert(getARC(testing, path) == ARC_A);		
            ++i;		
         }		
         sprintf(path, "%s", startingPaths[3]);		
         i = 0;		
         while (i < 3) {		
            strcat(path, "R");		
            assert(getARC(testing, path) == ARC_B);		
            ++i;		
         }		
      }		
   }		
   disposeGame(testing);		
   printf("getArc works.\n");		
}
