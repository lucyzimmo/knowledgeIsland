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

    //clean up: keep your memory beautiful
    disposeGame(testGame);

    //TODO: all tests passed message :)

    printf("All tests passed!!!\nYou are awesome!");

    return EXIT_SUCCESS;
}

void testThrowDice () {
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game testGame = newGame(disciplines, dice);

    assert (getTurn (testGame) == -1);
    throwDice(testGame, 6);
    assert (getTurn (testGame) == 0);   
    throwDice(testGame, 2);
    assert (getTurn (testGame) == 1);

    disposeGame (testGame);
}

void testGetWhoseTurn () {
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
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

void testGetMostARCs () {
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game testGame = newGame(disciplines, dice);    

    assert (getMostARCs (testGame) == NO_ONE);
    
    action createARC;
    createARC.actionCode = OBTAIN_ARC;
    createARC.path = {L}; 

    makeAction (testGame, OBTAIN_ARC);
    int currentMostARCs = getWhoseTurn (testGame);
    assert (getMostARCs (testGame) == getWhoseTurn (testGame));

    throwDice (testGame, 3);

    // WARNING: I just realised makeAction requires actionCode and destination, so this won't work
    makeAction (testGame, OBTAIN_ARC);
    makeAction (testGame, OBTAIN_ARC);
    int currentMostARCs = getWhoseTurn (testGame);
    assert (getMostARCs (testGame) == currentMostARCs);

    throwDice (testGame, 2);

    // WARNING: I just realised makeAction requires actionCode and destination, so this won't work
    makeAction (testGame, OBTAIN_ARC);
    makeAction (testGame, OBTAIN_ARC);
    assert (getMostARCs (testGame) == currentMostARCs);

    // WARNING: I just realised makeAction requires actionCode and destination, so this won't work
    makeAction (testGame, OBTAIN_ARC);
    assert (getMostARCs (testGame) == getWhoseTurn (testGame));    
    printf("getMostARCs works\n");

    disposeGame (testGame);
}

void testgetMostPublications () {
    Game testGame = newGame(disciplines, dice);    
    assert (getMostPublications (testGame) == NO_ONE);

    action obtainPublication;
    obtainPublication.actionCode = OBTAIN_PUBLICATION;
    makeAction (testGame, obtainPublication);
    assert (getMostPublications (testGame) == getWhoseTurn (testGame));

    throwDice (testGame, 3);

    makeAction (testGame, obtainPublication);
    makeAction (testGame, obtainPublication);
    int currentMostARCs = getWhoseTurn (testGame);
    assert (getMostPublications (testGame) == currentMostARCs);

    throwDice (testGame, 2);

    makeAction (testGame, obtainPublication);
    makeAction (testGame, obtainPublication);
    assert (getMostPublications (testGame) == currentMostARCs);

    makeAction (testGame, obtainPublication);
    assert (getMostPublications (testGame) == getWhoseTurn (testGame));    

    disposeGame (testGame);
}

void testGetDiscipline () {
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
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
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
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