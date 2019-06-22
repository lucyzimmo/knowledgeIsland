#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

#define NUM_ROWS 11
#define NUM_COLUMNS 6

#define WINNING_KPI_POINTS 120
#define ARC_KPI_POINTS 2
#define CAMPUS_KPI_POINTS 10
#define GO8_KPI_POINTS 20
#define IP_KPI_POINTS 10
#define MOST_ARCS_KPI_POINTS 10
#define MOST_PUBLICATIONS_KPI_POINTS 10

#define NUM_SIDES_ON_HEX 6
#define NUM_DISCIPLINES 9

#define PATH_TO_CAMPUS_A1 ""
#define PATH_TO_CAMPUS_A2 "RLRLRLRLRLL"
#define PATH_TO_CAMPUS_B1 "RRLRL"
#define PATH_TO_CAMPUS_B2 "LRLRLRRLRL"
#define PATH_TO_CAMPUS_C1 "LRLRL"
#define PATH_TO_CAMPUS_C2 "LRLRLLRLRL"

#define DEFAULT_EXCHANGE 3
#define RETRAIN_EXCHANGE 2

#define NUM_VERTICES 54
#define NUM_HEXES_AT_POINT 3

typedef struct _point {
    int hexIndex[NUM_HEXES_AT_POINT];
    int ARCIndex;
    int vertexIndex;
} *Point;

typedef struct _vertex {
    //Stores the arc north of the vertex.
    int arcV;
    //Stores the arc east of the vertex.
    int arcH;
    //Stores the campus on the vertex.
    int campus;
} vertex;

typedef struct _hex {
    int hexIndex;
    int diceValue;
    int student;

    int ARCs[NUM_SIDES_ON_HEX];
    int campuses[NUM_SIDES_ON_HEX];
    int GO8s[NUM_SIDES_ON_HEX];
    Hex borderingHexes[NUM_SIDES_ON_HEX];
    int ARCIndex;
    int vertexIndex;
    int direction;
} *Hex;

typedef struct _player {

    int KPIPoints;
    path ARCs[NUM_VERTICES];
    path campuses[NUM_VERTICES];
    path GO8s[NUM_VERTICES];
    //sum of each player has
    int arcs;
    int numCampuses;
    int numGO8s;
    int ips;
    int publications;

    /// sum of each discipline
    int studentType[NUM_DISCIPLINES];
} *Player;

struct _game {
    Player players[NUM_UNIS];
    Hex hexes[NUM_REGIONS];
    int turnNumber; 
    
    // An 2D array of vertex structs stating location of campuses
    vertex vertices[NUM_COLUMNS][NUM_ROWS];
    int mostARCs;
    int mostPublications;
};

void copyPartOfString (char fullString[], char newString[], 
            int startIndex, int stopIndex);

Point pathToPoint (Game g, path path);

Game newGame (int discipline[], int dice[]) {
    // Actually modify structs and do specifics
    
    Game g = malloc (sizeof(Game));
    
    //setting up mostPublications and mostArcs
    g->mostPublications = NO_ONE;
    g->mostARCs = NO_ONE;
    // Setting up players 
    int i = 0; 
    while (i <= NUM_UNIS) {
       Player currentPlayer = g->players[i];
       currentPlayer->KPIPoints = 2 * CAMPUS_KPI_POINTS;
    }
    Player uniA = g->players[UNI_A-1]; //UNI_A is 1 not 0, so to convert it to indexes you need to subtract 1
    uniA->campuses = {PATH_TO_CAMPUS_A1, PATH_TO_CAMPUS_A2};

    Player uniB = g->players[UNI_B-1];
    uniB->campuses = {PATH_TO_CAMPUS_B1, PATH_TO_CAMPUS_B2};

    Player uniC = g->players[UNI_C-1];
    uniC->campuses = {PATH_TO_CAMPUS_C1, PATH_TO_CAMPUS_C2};



    // Setting up hexes
    i = 0;
    while (i < NUM_REGIONS) {
        Hex currentHex = g->hexes[i];
        currentHex->hexIndex = i;
        currentHex->diceValue = dice[i];
        currentHex->student = discipline[i];
        currentHex->ARCs = {0, 0, 0, 0, 0, 0};
        currentHex->GO8s = {0, 0, 0, 0, 0, 0};
        if (i != 0 && i != 2 && i != 7 && i != 11 && i != 16 && i != 18) {
            currentHex->campuses = {0, 0, 0, 0, 0, 0};
        }
    }

    g->hexes[0]->campuses = {0, 0, 0, 0, 0, UNI_B};
    g->hexes[2]->campuses = {0, 0, 0, 0, UNI_C, 0};
    g->hexes[7]->campuses = {UNI_A, 0, 0, 0, 0, 0};
    g->hexes[11]->campuses = {0, 0, 0, UNI_A, 0, 0};
    g->hexes[16]->campuses = {0, UNI_C, 0, 0, 0, 0};
    g->hexes[18]->campuses = {0, 0, UNI_B, 0, 0, 0};
    
    g->hexes[0]->borderingHexes = {NULL, g->hexes[3], g->hexes[4], g->hexes[1], NULL, NULL};
    g->hexes[1]->borderingHexes = {g->hexes[0], g->hexes[4], g->hexes[5], g->hexes[2], NULL, NULL};
    g->hexes[2]->borderingHexes = {g->hexes[1], g->hexes[5], g->hexes[6], NULL, NULL, NULL};
    g->hexes[3]->borderingHexes = {NULL, g->hexes[7], g->hexes[8], g->hexes[4], g->hexes[0], NULL};
    g->hexes[4]->borderingHexes = {g->hexes[3], g->hexes[8], g->hexes[9], g->hexes[5], g->hexes[1], g->hexes[0]};
    g->hexes[5]->borderingHexes = {g->hexes[4], g->hexes[9], g->hexes[10], g->hexes[6], g->hexes[2], g->hexes[1]};
    g->hexes[6]->borderingHexes = {g->hexes[5], g->hexes[10], g->hexes[11], NULL, NULL, g->hexes[2]};
    g->hexes[7]->borderingHexes = {NULL, NULL, g->hexes[12], g->hexes[8], g->hexes[3], NULL};
    g->hexes[8]->borderingHexes = {g->hexes[7], g->hexes[12], g->hexes[13], g->hexes[9], g->hexes[4], g->hexes[3]};
    g->hexes[9]->borderingHexes = {g->hexes[8], g->hexes[13], g->hexes[14], g->hexes[10], g->hexes[5], g->hexes[4]};
    g->hexes[10]->borderingHexes = {g->hexes[9], g->hexes[14], g->hexes[15], g->hexes[11], g->hexes[6], g->hexes[5]};
    g->hexes[11]->borderingHexes = {g->hexes[10], g->hexes[15], NULL, NULL, NULL, g->hexes[6]};
    g->hexes[12]->borderingHexes = {NULL, NULL, g->hexes[16], g->hexes[13], g->hexes[8], g->hexes[7]};
    g->hexes[13]->borderingHexes = {g->hexes[12], g->hexes[16], g->hexes[17], g->hexes[14], g->hexes[9], g->hexes[8]};
    g->hexes[14]->borderingHexes = {g->hexes[13], g->hexes[17], g->hexes[18], g->hexes[15], g->hexes[10], g->hexes[9]};
    g->hexes[15]->borderingHexes = {g->hexes[14], g->hexes[18], NULL, NULL, g->hexes[12], g->hexes[10]};
    g->hexes[16]->borderingHexes = {NULL, NULL, NULL, g->hexes[17], g->hexes[13], g->hexes[12]};
    g->hexes[17]->borderingHexes = {g->hexes[16], NULL, NULL, g->hexes[18], g->hexes[14], g->hexes[13]};
    g->hexes[18]->borderingHexes = {g->hexes[17], NULL, NULL, NULL, g->hexes[15], g->hexes[14]};
    
    int x = 0;
    while (x < NUM_COLUMNS) {
        int y = 0;
        while (y < NUM_ROWS) {
            g->vertices[x][y].arcV = VACANT_ARC;
            g->vertices[x][y].arcH = VACANT_ARC;
            g->vertices[x][y].campus = VACANT_VERTEX;
            y++;
        }
     x++;
   }
   // then initialize the starting campuses
   g->vertices[2][10].campus = CAMPUS_A;
   g->vertices[3][0].campus = CAMPUS_A;
   g->vertices[0][7].campus = CAMPUS_B;
   g->vertices[5][3].campus = CAMPUS_B;
   g->vertices[0][2].campus = CAMPUS_C;
   g->vertices[5][8].campus = CAMPUS_C;
   
   return g;
}

int getIPs(Game g, int player) {
    return g->players[player-1]->ips;
}

int getARCs(Game g, int player) {
    return g->players[player-1]->arcs;
}

int getDiceValue(Game g, int regionID) {
    return g->hexes[regionID]->diceValue;
}

void disposeGame(Game g) {
    free(g);
}
int getDiscipline(Game g, int regionID) {
    return g->hexes[regionID]->student;
}

void makeAction (Game g, action a) {
    int currentPlayer = getWhoseTurn(g);
    int x = 0;
    int y = 0;
    int direction = 0;
   
    if (a.actionCode == PASS) {
        //do nothing
    } else if (a.actionCode == BUILD_CAMPUS) {
        g->vertices[x][y].campus = currentPlayer;
        g->players[currentPlayer-1]->numCampuses++;
        // remove studentType
        g->players[currentPlayer-1]->studentType[STUDENT_BPS]--;
        g->players[currentPlayer-1]->studentType[STUDENT_BQN]--;
        g->players[currentPlayer-1]->studentType[STUDENT_MJ]--;
        g->players[currentPlayer-1]->studentType[STUDENT_MTV]--;
    } else if (a.actionCode == BUILD_GO8) { 
        g->vertices[x][y].campus = currentPlayer + 3; //add to account for GO8
        g->players[currentPlayer-1]->numCampuses--; //remove campus as GO8 replaces campus
        g->players[currentPlayer-1]->numGO8++;
        // remove studentType
        g->players[currentPlayer-1]->studentType[STUDENT_MJ] -= 2; //to account for cost of GO8
        g->players[currentPlayer-1]->studentType[STUDENT_MMONEY] -= 3;

    } else if (a.actionCode == OBTAIN_ARC) {      
        // get the correct arc based on direction
        // add arc to map
        if (direction == 'U') {
            g->vertices[x][y].arcV = currentPlayer;
        } else if (direction == 'D') {
            g->vertices[x][y-1].arcV = currentPlayer;
        } else if (direction == 'L') {
            g->vertices[x-1][y].arcH = currentPlayer;
        } else if (direction == 'R') {
            g->vertices[x][y].arcH = currentPlayer;
        }
     
        // add arc to player
        g->players[currentPlayer-1]->arcs++;
        // remove studentType
        g->players[currentPlayer-1]->studentType[STUDENT_BPS]--;
        g->players[currentPlayer-1]->studentType[STUDENT_BQN]--;
          
        //calculating MostArcs
        if (g->mostARCs == 0 || g->players[currentPlayer - 1]->arcs > g->players[g->mostARCs - 1]->arcs) {
            g->mostARCs = currentPlayer;
        }

    } else if (a.actionCode == OBTAIN_PUBLICATION) {
        g->players[currentPlayer]->publications ++;
        
        //update mostPublications
        if (g->mostPublications == 0 
                || g->players[currentPlayer - 1]->publications 
                > g->players[g->mostPublications - 1]->publications) {
           g->mostPublications = currentPlayer;
        }
        
        // remove studentType
        g->players[currentPlayer-1]->studentType[STUDENT_MJ]--;
        g->players[currentPlayer-1]->studentType[STUDENT_MTV]--;
        g->players[currentPlayer-1]->studentType[STUDENT_MMONEY]--;
    } else if (a.actionCode == OBTAIN_IP_PATENT) {
        g->players[currentPlayer-1]->ips++;

        // remove studentType
        g->players[currentPlayer-1]->studentType[STUDENT_MJ]--;
        g->players[currentPlayer-1]->studentType[STUDENT_MTV]--;
        g->players[currentPlayer-1]->studentType[STUDENT_MMONEY]--;
    } else if (a.actionCode == RETRAIN_STUDENTS) {
        int rate = getExchangeRate(g, currentPlayer, a.disciplineFrom, a.disciplineTo);
        g->players[currentPlayer-1]->studentType[a.disciplineFrom] -= rate;
        g->players[currentPlayer-1]->studentType[a.disciplineTo] += 1;
    }
}

int getPublications(Game g, int player) {
    int publications = g->players[player-UNI_A]->publications;
    return publications;
}

int getStudents(Game g, int player, int discipline) {
    int studentAmount = g->players[player-UNI_A]->students[discipline];
    return studentAmount;
}

int getMostARCs(Game g) {
    return g->mostARCs;
  
}

int getMostPublications(Game g) {
    return g->mostPublications; 
}

// return the current turn number of the game -1,0,1, ..
int getTurnNumber (Game g) {
    return g->turnNumber;    
}

// return the player id of the player whose turn it is 
// the result of this function is NO_ONE during Terra Nullis
int getWhoseTurn (Game g) {
    if (turnNumber == TERRA_NULLIS) {
        int returnVal = 0;
    } else {
        int returnVal = (getTurnNumber (g) + 1) % NUM_UNIS;
    }
    return returnVal;
}

// return the number of GO8 campuses the specified player currently has
int getGO8s (Game g, int player) {
    return g->players[player]->numGO8s;
}

int isLegalpath (Game g, path path) {
    int pathLen = strlen (path);
    char currentString[path_LIMIT];
    int isLegal = TRUE;
    if (path[0] == 'B') {
        isLegal = FALSE;
    }
    if (pathLen > 150) {
        isLegal = FALSE;
    }

    int i = 1; // i starts at 1 becasue we already dealt with 0
    while (i < pathLen && isLegal == TRUE) {
        copyPartOfString (path, currentString, 0, i); // updates currentString
        Point currentPoint = pathToPoint (currentString);
        if (isLegalTurn (g, currentPoint, currentString[i]) == FALSE) {
            isLegal = FALSE;
        } 
    }
    return isLegal;
}

int isLegalTurn (Game g, Point point, char nextTurn) {
    int currentARCIndex = currentPoint->ARCIndex;
    int currentVertexIndex = currentPoint->vertexIndex;
    int currentHexIndex = currentPoint->hexIndexes[0];
    currentHex = g->hexes[currentHexIndex];
    Hex currentBorderingHex = currentHex->borderingHexes[currentARC];
    int currentDirection = currentPoint->direction;
    int isLegal = TRUE;
    if (nextTurn == 'R') {
        // if the vertex is clockwise "in front" of the edge
        if (currentDirection == ANTICLOCKWISE) {
            if (currentBorderingHex == NULL && currentPoint->hexIndexes[3] == NULL) {
                isLegal = FALSE;
            }
        } 
    } else if (nextTurn == 'L') {
        // if the vertex is clockwise "behind" the edge
        if (currentDirection == CLOCKWISE) {
            if (currentBorderingHex == NULL && currentPoint->hexIndexes[3] == NULL) {
                isLegal = FALSE;
            }
        }
    // if the current letter is not 'R', 'L' or 'B'
    } else if (nextTurn != 'B') {
        isLegal = FALSE;
    }
    return isLegal;
}

void copyPartOfString (char fullString[], char newString[], 
            int startIndex, int stopIndex) {
    int i = 0;
    int j = 0;
    while (i < stopIndex) {
        if (i >= startIndex) {
            newString[j] = fullString[i];
            j ++;
        }
        i ++;
    }
    newString[j] = '\n';

}

Point pathToPoint (Game g, path path) {
    int pathLen = strlen (path);
    // Set up starting point
    Hex currentHex = g->hexes[7];
    Point currentPoint;
    currentPoint->hexIndexes[0] = 7;
    currentPoint->borderingHexes[0] = currentHex;
    if (path[0] == 'R') {
        currentPoint->ARCIndex = [5];
        currentPoint->vertexIndex = [5]
        currentPoint->borderingHexes[1] = NULL;
        currentPoint->borderingHexes[2] = g->hexes[3];
        currentPoint->direction = ANTICLOCKWISE;
    } else if (path[0] == 'L') {
        currentPoint->ARCIndex = [0];
        currentPoint->vertexIndex = [1]
        currentPoint->borderingHexes[1] = NULL;
        currentPoint->borderingHexes[2] = NULL;
        currentPoint->direction = CLOCKWISE;
    } else {
        currentPoint->ARCIndex = [0];
        currentPoint->vertexIndex = [0]
        currentPoint->borderingHexes[1] = NULL;
        currentPoint->borderingHexes[2] = NULL;
    }

    int i = 1; 
    // i starts at 1 because we have already done path[0] in setup
    int currentARCIndex = currentPoint->ARCIndex;
    int currentVertexIndex = currentPoint->vertexIndex;
    int currentHexIndex = currentPoint->hexIndexes[0];
    currentHex = g->hexes[currentHexIndex];
    Hex currentBorderingHex = currentHex->borderingHexes[currentARC];
    int currentDirection = currentPoint->direction;
    while (i < pathLen) {
        if (path[i] == 'R') {
            // if the vertex is clockwise "in front" of the edge
            if (currentDirection == CLOCKWISE) {
                currentPoint->ARCIndex = (currentARC + 1) 
                    % NUM_SIDES_ON_HEX;
                currentPoint->vertexIndex = (currentVertex + 1)
                    % NUM_SIDES_ON_HEX;

            // if the vertex is anticlockwise to the edge
            } else {
                if (currentBorderingHex == NULL) {
                    currentPoint->hexIndexes[0] = currentHex->
                            borderingHexes[(currentARCIndex - 1) 
                            % NUM_SIDES_ON_HEX];
                    currentPoint->ARCIndex = (currentARCIndex 
                       + 2) % NUM_SIDES_ON_HEX;
                    currentPoint->vertexIndex = (currentARCIndex - 1);
                    currentPoint->direction = ANTICLOCKWISE;
                } else {
                    currentPoint->hexIndexes[0] = currentBorderingHex->hexIndex;
                    currentPoint->ARCIndex = (currentARCIndex
                        + (NUM_SIDES_ON_HEX/2) + 1) % NUM_SIDES_ON_HEX;
                
                    currentPoint->vertexIndex = (currentARCIndex + 1);
                    currentPoint->direction = CLOCKWISE;
                } 

            } 
        } else if (path[i] == 'L') {
            // if the vertex is anticlockwise "in front" of the edge
            if (currentDirection == ANTICLOCKWISE) {
                currentPoint->ARCIndex = (currentARC + 1) % NUM_SIDES_ON_HEX;
                currentPoint->vertexIndex = (currentVertex + 1)  
                                      % NUM_SIDES_ON_HEX;
            
            // if the vertex is clockwise "in front" of the edge
            } else {
                if (currentBorderingHex == NULL) {
                    currentPoint->hexIndexes[0] = currentHex->
                            borderingHexes[(currentARCIndex - 1) 
                            % NUM_SIDES_ON_HEX];
                    currentPoint->ARCIndex = (currentARCIndex 
                       + 1) % NUM_SIDES_ON_HEX;
                    currentPoint->vertexIndex = (currentARCIndex + 1);
                    currentPoint->direction = CLOCKWISE;
                else {
                    currentPoint->hexIndexes[0] = currentBorderingHex->hexIndex;
                    currentPoint->ARCIndex = (currentARCIndex 
                           + (NUM_SIDES_ON_HEX/2) + 1) % NUM_SIDES_ON_HEX;
                    currentPoint->vertexIndex = (currentARCIndex - 1);
                    currentPoint->direction = ANTICLOCKWISE;
                }
            }
        // if the current letter is "B"
        } else {
            if (currentDirection == CLOCKWISE) {
                currentPoint->vertexIndex --;
                currentPoint->direction = ANTICLOCKWISE;
            } else {
                currentPoint->vertexIndex ++;
                currentPoint->direction = CLOCKWISE;
            }
        }
        currentARCIndex = currentPoint->ARCIndex;
        currentVertexIndex = currentPoint->vertexIndex;
        currentHexIndex = currentPoint->hexIndexes[0] 
        currentHex = g->hexes[currentHexIndex];
        currentBorderingHex = currentHex->borderingHexes[currentARC];
        currentDirection = currentPoint->direction;
        i ++;
    }
    // seting the other hexes it borders
    Hex borderingHex1 = currentHex->borderingHexes[currentARCIndex];
    if (borderingHex1 == NULL) {
        currentPoint->hexIndexes[1] = NONE;
    } else {
        currentPoint->hexIndexes[1] = borderingHex1->hexIndex;
    }
    if (currentDirection == ANTICLOCKWISE) {
        int indexBorderingThirdHex = (currentARCIndex - 1) % NUM_SIDES_ON_HEX;
    } else {
        int indexBorderingThirdHex = (currentARCIndex + 1) % NUM_SIDES_ON_HEX;
    }
    Hex borderingHex2 = currentHex->borderingHexes[indexBorderingThirdHex];
    if (borderingHex2 == NULL) {
        currentPoint->hexIndexes[2] = NONE; 
    } else {
        currentPoint->hexIndexes[2] = borderingHex2->hexIndex;
    }
    return currentPoint;
}
}

int getExchangeRate (Game g, int player, int disciplineFrom, int disciplineTo) {
    int exchangerate = DEFAULT_EXCHANGE; //checks if campuses are on retrain areas, if they are sets it lower
    if (((getCampus(g,"R") == player) 
            || (getCampus(g,"RR") == player)) 
            && (disciplineFrom == STUDENT_MTV)) {
        exchangerate = RETRAIN_EXCHANGE;
    } else if (((getCampus(g,"LL") == player) 
            || (getCampus(g,"LLL") == player)) 
            && (disciplineFrom == STUDENT_MMONEY)) {
        exchangerate = RETRAIN_EXCHANGE;
    } else if (((getCampus(g,"RRRLRLRLR") == player)
            || (getCampus(g,"RRRLRLRLRL") == player)) 
            && (disciplineFrom==STUDENT_BPS)) {
        exchangerate = RETRAIN_EXCHANGE;
    } else if (((getCampus(g,"LLLLRLRLRL") == player)
            || (getCampus(g,"LLLLRLRLRLR") == player)) 
            && (disciplineFrom == STUDENT_MJ)) {
        exchangerate = RETRAIN_EXCHANGE;
    } else if (((getCampus(g,"RRRLRR") == player) 
            || (getCampus(g,"RRRLRRR") == player)) 
            && (disciplineFrom == STUDENT_BQN)){
        exchangerate = RETRAIN_EXCHANGE;
    }
    return exchangerate;
}

// return the contents of the given vertex (ie campus code or 
// VACANT_VERTEX)
int getCampus(Game g, path pathToVertex) {
    Point campusPoint = pathToPoint (pathToVertex);
    return g->hexes[campusPoint->hexIndexes[0]]->campuses[campusPoint->vertexIndex];
}

// the contents of the given edge (ie ARC code or vacent ARC)
int getARC(Game g, path pathToEdge) {
    Point ARCPoint = pathToPoint (pathToEdge);
    return g->hexes[ARCPoint->hexIndexes[0]]->ARCs[ARCPoint->ARCIndex];
}

void throwDice (Game g, int diceScore){
    g->currentTurn++; //increases current turn

    // need to check which dice scores correspond to which region

    // below is an array for the hexes coordinates -> will each hex classify based on vertexes at bottom left
    // thus this array stores the x and y coordinates of the vertex to the bottom left of
    // the region and represents each region e.g. 0,6 represents one hex
    int hexX[] = { 0,0,0, 1,1,1,1, 2,2,2,2,2, 3,3,3,3, 4,4,4 };
    int hexY[] = { 6,4,2, 7,5,3,1, 8,6,4,2,0, 7,5,3,1, 6,4,2 };

    // campuses around the campus(coordinatesa: x,y) have coordinates:x/x-1, y/y-1/y-2
    int regionNum = 0;
    while (regionNum < NUM_REGIONS) {
        if (g->dice[regionNum] == diceScore) {
        // give resources to the campuses around campus
            int studentType = g->discipline[regionNum];
            int campusX = hexX[regionNum];
            while (campusX <= hexX[regionNum] + 1) {
                int campusY = hexY[regionNum];
                    while (campusY <= hexY[regionNum] + 2) {
                    int campusType = g->vertices[campusX][campusY].campus;
                    //checking for campus specific discipline and adding to it 
                    if (campusType == 1) {
                        g->players[0]->students[studentType] += 1;
                    } else if (campusType == 2) {
                        g->players[1]->students[studentType] += 1;
                    } else if (campusType == 3) {
                        g->players[2]->students[studentType] += 1;
                    } else if (campusType == 4) {
                        g->players[0]->students[studentType] += 2;
                    } else if (campusType == 5) {
                        g->players[1]->students[studentType] += 2;
                    } else if (campusType == 6) {
                        g->players[2]->students[studentType] += 2;
                    }
                    campusY++;
                    }
                campusX++;
            }
        }
        regionNum++;
    }
    //special case: 7 is rolled as per rules:
    // Whenever a 7 is thrown, immediately after any new students are produced, 
    // all MTV and M$ students of all universities decide to switch to ThD's.
    if (diceScore == 7) {
        int whichPlayer = 0;
        while (whichPlayer < NUM_UNIS) {
            g->players[whichPlayer]->students[STUDENT_THD] += g->players[whichPlayer]->students[STUDENT_MTV];
            g->players[whichPlayer]->students[STUDENT_MTV] = 0;
            g->players[whichPlayer]->students[STUDENT_THD] += g->players[whichPlayer]->students[STUDENT_MMONEY];
            g->players[whichPlayer]->students[STUDENT_MMONEY] = 0;
            whichPlayer++;
        }
    }
}
int isLegalAction(Game g, action a) {
    int isLegal;
    int whoseTurn = getwhoseTurn(g);
    int ispathLegal = TRUE;
    if (a.actionCode == OBTAIN_ARC 
                || a.actionCode == BUILD_CAMPUS 
                || a.actionCode == BUILD_GO8) {
        ispathLegal = isLegalpath (a.destination);
    }
    if (whoseTurn != NO_ONE || ispathLegal == FALSE) {
        if (a.actionCode == PASS) {
            isLegal = 1;
        } else if (a.actionCode == BUILD_CAMPUS) {
            //special set of variables for this function 
            int x, y, dir;
            int checkConnectingArc; 
            // first check if resources are there
            if ((g->players[whoseTurn - 1]->students[STUDENT_BPS] >= 1) 
                    && (g->players[whoseTurn - 1]
                    ->students[STUDENT_BQN] >= 1) 
                    && (g->players[whoseTurn - 1]
                    ->students[STUDENT_MJ ] >= 1) 
                    && (g->players[whoseTurn - 1]
                    ->students[STUDENT_MTV] >= 1)) {
                //then check if campus is not there
                if (g->vertices[x][y].campus == VACANT_VERTEX) {
                    if ((g->vertices[x][y].arcH == whoseTurn) 
                            || (g->vertices[x][y].arcV == whoseTurn) 
                            || ((x > 0) 
                            && (g->vertices[x-1][y].arcH == whoseTurn)) 
                            || ((y > 0) 
                            && (g->vertices[x][y-1].arcV == whoseTurn))) {
                        //make sure there are no campuses around location and that the arc connecting location is valid
                        checkConnectingArc = ((x + y) % 2) * 2 - 1;
                    }
                    if (((y == 10) 
                            || (g->vertices[x][y+1].campus 
                            == VACANT_VERTEX)) && ((y ==  0) 
                            || (g->vertices[x][y-1].campus 
                            == VACANT_VERTEX)) 
                            && ((checkConnectingArc ==  1) 
                            || (x == 10) 
                            || (g->vertices[x+1][y].campus 
                                == VACANT_VERTEX)) && ((checkConnectingArc == -1) 
                            || (x ==  0) 
                            || (g->vertices[x-1][y].campus 
                                == VACANT_VERTEX))) {
                        //finally
                        isLegal = 1;
                    }
                }
            }
        } else if (a.actionCode == BUILD_GO8) {
            //check if resources and if campus belongs to them
            isLegal = (g->players[whoseTurn - 1]->students[STUDENT_MJ] 
                    >= 2) 
                && (g->players[whoseTurn - 1]->students[STUDENT_MMONEY] 
                    >= 3) 
                && (g->vertices[x][y].campus == whoseTurn) 
                && ((getGO8s(g,UNI_A) 
                    + getGO8s(g,UNI_B) 
                    + getGO8s(g,UNI_C)) < 8);
        } else if (a.actionCode == START_SPINOFF) {
            isLegal = (g->players[whoseTurn - 1]->students[STUDENT_MJ]
                    >= 1) 
                && (g->players[whoseTurn - 1]->students[STUDENT_MMONEY] 
                    >= 1) 
                && (g->players[whoseTurn - 1]->students[STUDENT_MTV] 
                    >= 1);
            //no need to check if obtain publication or obtain ip patent because always false
        } else if (a.actionCode == OBTAIN_ARC) {
            //If they have the resources. 
            if ((g->players[whoseTurn - 1]->students[STUDENT_BPS] >= 1) 
                    && (g->players[whoseTurn - 1]->students[STUDENT_BQN] 
                        >= 1)) {
                //have to add to paths so we can lead them to adjacent arcs
                char adj[4][path_LIMIT + 2];
                sprintf(adj[0], "%sL", a.destination);
                sprintf(adj[1], "%sR", a.destination);
                sprintf(adj[2], "%sBL", a.destination);
                sprintf(adj[3], "%sBR", a.destination);

                //have to add to paths to account for two campuses at end of an arc
                char ends[2][path_LIMIT+1];
                sprintf(ends[0], "%s", a.destination);
                sprintf(ends[1], "%sB", a.destination);
            }
            //now check if arc is empty
            if (getARC(g, a.destination) == NO_ONE) {
                //if they own a campus at end of an edge
                if (getCampus(g, ends[0]) == whoseTurn 
                        || getCampus(g, ends[0]) == whoseTurn + 3 
                        || getCampus(g, ends[1]) == whoseTurn 
                        || getCampus(g, ends[1]) == whoseTurn + 3) {
                    // it's legal
                    isLegal = 1;
                }
                //or if they own a path at end of edge and no owners of a campus there exist
                if ((getARC(g, adj[0]) == whoseTurn) 
                        || (getARC(g, adj[1]) == whoseTurn)) {
                    if (getCampus(g, ends[0]) == NO_ONE) {
                        isLegal = 1;
                    }
                }
                if ((getARC(g, adj[2]) == whoseTurn) 
                        || (getARC(g, adj[3]) == whoseTurn)) {
                    if (getCampus(g, ends[1]) == NO_ONE) {
                        isLegal = 1;
                    }
                }
            }
        } else if (a.actionCode == RETRAIN_STUDENTS) {
            int currentPlayer = getWhoseTurn (g);
            int exchangeRate = getExchangeRate (g, currentPlayer, 
                a.disciplineFrom, a.disciplineTo);
            if (g->players[currentPlayer]->studentType[a.disciplineFrom] >= exchangeRate) {
                isLegal = TRUE;
            }
        }
    }
    return isLegal;
}
