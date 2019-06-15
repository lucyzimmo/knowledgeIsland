#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

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

struct _point {
    int hexIndex[NUM_HEXES_AT_POINT];
    int ARCIndex;
    int vertexIndex;
}* Point;

typedef struct _vertex {
   //Stores the arc north of the vertex.
   int arcV;
   //Stores the arc east of the vertex.
   int arcH;
   //Stores the campus on the vertex.
   int campus;
} vertex;

struct _game {
    Player players[NUM_UNIS];
    Hex hexes[NUM_Regions];
    int turnNumber; 
    
   // An 2D array of vertex structs stating location of campuses
   vertex vertices[NUM_COLUMNS][NUM_ROWS];
   int mostARCs;
   int mostPublications;
   int dice[NUM_REGIONS]; //dice number for each region 
}

typedef struct _hex {
    int hexIndex
    int diceValue;
    int student;
    int ARCs[NUM_SIDES_ON_HEX];
    int campuses[NUM_SIDES_ON_HEX];
    int GO8s[NUM_SIDES_ON_HEX];
    Hex borderingHexes[NUM_SIDES_ON_HEX];
}*Hex;

typedef struct _player {
    int KPIPoints;
    Path ARCs[NUM_VERTICES];
    Path campuses[NUM_VERTICES];
    Path GO8s[NUM_VERTICES];
    //sum of each player has
    int arcs;
    int campuses;
    int GO8s;
    int ips;
    int publications;
    /// sum of each discipline
    int studentType[NUM_DISCIPLINES]
} *Player;

Game newGame (int discipline[], int dice[]) {
    // Actually modify structs and do specifics
    
    Game g = malloc (sizeof(Game))
    
    //setting up mostPublications and mostArcs
    g->mostPublications = NO_ONE;
    g->mostARCs = NO_ONE;
    // Setting up players 
    int i = 0; 
    while (i <= NUM_UNIS) {
        Player currentPlayer = g->players[i];
        currentPlayer->KPIPoints = 2 * CAMPUS_KPI_POINTS;
    }
    Player uniA g->players[UNI_A-1]; //UNI_A is 1 not 0, so to convert it to indexes you need to subtract 1
    uniA->campuses[] = {PATH_TO_CAMPUS_A1, PATH_TO_CAMPUS_A2};

    Player uniB g->players[UNI_B-1];
    uniB->campuses[] = {PATH_TO_CAMPUS_B1, PATH_TO_CAMPUS_B2};

    Player uniC g->players[UNI_C-1];
    uniC->campuses[] = {PATH_TO_CAMPUS_C1, PATH_TO_CAMPUS_C2};



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
    

   //initialize students and players
   int playerID = 0;
   while (playerID < NUM_UNIS) {
      g->players[playerID].students[STUDENT_THD] = 0;
      g->players[playerID].students[STUDENT_BPS] = 3;
      g->players[playerID].students[STUDENT_BQN] = 3;
      g->players[playerID].students[STUDENT_MJ] = 1;
      g->players[playerID].students[STUDENT_MTV] = 1;
      g->players[playerID].students[STUDENT_MMONEY] = 1;
      g->players[playerID].campuses = 2;
      g->players[playerID].go8s = 0;
      g->players[playerID].arcs = 0;
      g->players[playerID].publications = 0;
      g->players[playerID].patents = 0;
      playerID++;
   }
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
    return g->players[player].ips;
}

int getARCs(Game g, int player) {
    int total = 0;
    for (int i = 0; i < g->arcCount; i++) {
        if (g->arcs[i].owner == player) {
            total++;
        }
    }
    return total;
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
        
   } else if (a.actionCode == BUILD_CAMPUS) {
      //0,0 is okay because in line below we are setting new position for current player
      g->vertices[x][y].campus = currentPlayer; 
      g->players[currentPlayer-1].campuses++;
      // remove studentType
      g->players[currentPlayer-1].studentType[STUDENT_BPS]--;
      g->players[currentPlayer-1].studentType[STUDENT_BQN]--;
      g->players[currentPlayer-1].studentType[STUDENT_MJ]--;
      g->players[currentPlayer-1].studentType[STUDENT_MTV]--;
   } else if (a.actionCode == BUILD_GO8) { 
      g->vertices[x][y].campus = currentPlayer + 3; //add to account for GO8
      g->players[currentPlayer-1].campuses--; //remove campus as GO8 replaces campus
      g->players[currentPlayer-1].go8s++;
      // remove studentType
      g->players[currentPlayer-1].studentType[STUDENT_MJ] -= 2; //to account for cost of GO8
      g->players[currentPlayer-1].studentType[STUDENT_MMONEY] -= 3;

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
      g->players[currentPlayer-1].arcs++;
      // remove studentType
      g->players[currentPlayer-1].studentType[STUDENT_BPS]--;
      g->players[currentPlayer-1].studentType[STUDENT_BQN]--;
       
      //calculating MostArcs
      if (g->mostARCs == 0 || g->players[currentPlayer - 1].arcs > g->players[g->mostARCs - 1].arcs) {
         g->mostARCs = currentPlayer;
      }

      
   } else if (a.actionCode == OBTAIN_PUBLICATION) {
      g->players[currentPlayer].publications++;
      
      //update mostPublications
      if (g->mostPublications == 0 || g->players[currentPlayer - 1].publications > g->players[g->mostPublications - 1].publications) {
         g->mostPublications = currentPlayer;
      }
      
      // remove studentType
      g->players[currentPlayer-1].studentType[STUDENT_MJ]--;
      g->players[currentPlayer-1].studentType[STUDENT_MTV]--;
      g->players[currentPlayer-1].studentType[STUDENT_MMONEY]--;
   } else if (a.actionCode == OBTAIN_IP_PATENT) {
      g->players[currentPlayer-1].ips++;
      
      // remove studentType
      g->players[currentPlayer-1].studentType[STUDENT_MJ]--;
      g->players[currentPlayer-1].studentType[STUDENT_MTV]--;
      g->players[currentPlayer-1].studentType[STUDENT_MMONEY]--;
   } else if (a.actionCode == RETRAIN_STUDENTS) {
      int rate = getExchangeRate(g, currentPlayer, a.disciplineFrom, a.disciplineTo);
      g->players[currentPlayer-1].studentType[a.disciplineFrom] -= rate;
      g->players[currentPlayer-1].studentType[a.disciplineTo] += 1;
   }
}
int getPublications(Game g, int player) {
   int publications = g->players[player-UNI_A].publications;
   return publications;
}

int getStudents(Game g, int player, int discipline) {
    int studentAmount = g->players[player-UNI_A].students[discipline];
    return studentAmount;
}

int getMostARCs(Game g) {
    return g->mostARCs;
  
}

int getMostPublications(Game g) {
    return g->mostPublications; 
}

Point pathToPoint (Game g, Path path) {
    int pathLen = strlen (path);
    // Set up starting point
    Hex currentHex = g->hexes[7][0];
    Point currentPoint;
    currentPoint->hexIndexes = 7;
    if (path[0] == 'R') {
        currentPoint->ARCIndex = [5];
        currentPoint->vertexIndex = [5]
    } else if (path[0] == 'L') {
        currentPoint->ARCIndex = [0];
        currentPoint->vertexIndex = [1]
    } else {
        currentPoint->ARCIndex = [0];
        currentPoint->vertexIndex = [0]
    }

    int i = 1; 
    // i starts at 1 because we have already done path[0] in setup
    while (i < pathLen) {
        int currentARC = currentPoint->ARCIndex;
        int currentVertex = currentPoint->vertexIndex;
        int currentHex = currentPoint->hexIndexes;
        if (path[i] == 'R') {
            if (currentPoint->ARCIndex < currentPoint->vertexIndex) {
                currentPoint->ARCIndex = (currentARC + 1)
                        % NUM_SIDES_ON_HEX;
                currentPoint->vertexIndex = (currentVertex + 1)
                        % NUM_SIDES_ON_HEX;
            } else {
                currentPoint->hexIndexes = g->hexes[currentHex]->
                                borderingHexes[currentARC]->hexIndex;
                currentPoint->ARCIndex = (currentPoint->ARCIndex 
                        + (NUM_SIDES_ON_HEX/2)) % NUM_SIDES_ON_HEX;
                currentPoint->vertexIndex = 
                        (currentPoint->ARCIndex + 1);
            } 
        } else if (path[i] == 'L') {
            if (currentPoint->ARCIndex == currentPoint->vertexIndex) {
                currentPoint->ARCIndex = (currentARC + 1) 
                                    % NUM_SIDES_ON_HEX;
                currentPoint->vertexIndex = (currentVertex + 1)  
                                               % NUM_SIDES_ON_HEX;
            } else {
                currentPoint->hexIndexes = g->hexes[currentHex]->
                                borderingHexes[currentARC]->hexIndex;
                currentPoint->ARCIndex = (currentPoint->ARCIndex + 
                            (NUM_SIDES_ON_HEX/2)) % NUM_SIDES_ON_HEX;
                currentPoint->vertexIndex = 
                            (currentPoint->ARCIndex + 1);
            }
        } else {
            if (currentPoint->ARCIndex < currentPoint->vertexIndex) {
                currentPoint->vertexIndex --;
            } else {
                currentPoint->vertexIndex ++;
            }
        }
        i ++;
    }
    // seting the other hexes it borders
    currentPoint->hexIndexes[1] = g->hexes[currentPoint->hexIndexes]->
                                borderingHexes[currentPoint->ARCIndex];
    if (currentPoint->ARCIndex == currentPoint->vertexIndex) {
        int indexBorderingThirdHex = (currentPoint->ARCIndex-1) 
                                            % NUM_SIDES_ON_HEX;
        currentPoint->hexIndexes[2] = g->hexes[currentPoint->hexIndexes]
                    ->borderingHexes[indexBorderingThirdHex]->hexIndex;
    }
    return currentPoint;
}

// return the current turn number of the game -1,0,1, ..
int getTurnNumber (Game g) {
    return g->turnNumber;    
}

// return the player id of the player whose turn it is 
// the result of this function is NO_ONE during Terra Nullis
int getWhoseTurn (Game g) {
    if (turnNumber == -1) {
        int returnVal = 0;
    } else {
        int returnVal = (getTurnNumber (g) + 1) % NUM_UNIS;
    }
    return returnVal;
}

// return the number of GO8 campuses the specified player currently has
int getGO8s (Game g, int player) {
    return g->players[player]->GO8s;
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
