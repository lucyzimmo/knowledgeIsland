#define WINNING_KPI_POINTS 120
#define NUM_SIDES_ON_HEX 6
#define NUM_DISCIPLINES 6
#define PATH_TO_CAMPUS_A 1 ""
#define PATH_TO_CAMPUS_A 2 "RLRLRLRLRLL"
#define PATH_TO_CAMPUS_B 1 "RRLRL"
#define PATH_TO_CAMPUS_B 2 "LRLRLRRLRL"
#define PATH_TO_CAMPUS_C 1 "LRLRL"
#define PATH_TO_CAMPUS_C 2 "LRLRLLRLRL"

struct _point {
    int hexIndex;
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
    
   // An 2D array of structs that indicate whether an arc or campus
   // exists at that index
   vertex vertices[NUM_COLUMNS][NUM_ROWS];
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
    Path ARCs[];
    Path campuses[];
    Path GO8s[];
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
    
    Game g;
    
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
        //idek
   } else if (a.actionCode == BUILD_CAMPUS) {
      g->vertices[x][y].campus = currentPlayer;
      g->players[currentPlayer].campuses++;
      // remove studentType
      g->players[currentPlayer].studentType[STUDENT_BPS]--;
      g->players[currentPlayer].studentType[STUDENT_BQN]--;
      g->players[currentPlayer].studentType[STUDENT_MJ]--;
      g->players[currentPlayer].studentType[STUDENT_MTV]--;
   } else if (a.actionCode == BUILD_GO8) {
      g->vertices[x][y].campus = currentPlayer + 3; //add to account for GO8
      g->players[currentPlayer].campuses--; //remove campus as GO8 replaces campus
      g->players[currentPlayer].go8s++;
      // remove studentType
      g->players[currentPlayer].studentType[STUDENT_MJ] -= 2; //to account for cost of GO8
      g->players[currentPlayer].studentType[STUDENT_MMONEY] -= 3;

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
      g->players[currentPlayer].arcs++;
      // remove studentType
      g->players[currentPlayer].studentType[STUDENT_BPS]--;
      g->players[currentPlayer].studentType[STUDENT_BQN]--;

      
   } else if (a.actionCode == OBTAIN_PUBLICATION) {
      g->players[currentPlayer].publications++;
      
      // remove studentType
      g->players[currentPlayer].studentType[STUDENT_MJ]--;
      g->players[currentPlayer].studentType[STUDENT_MTV]--;
      g->players[currentPlayer].studentType[STUDENT_MMONEY]--;
   } else if (a.actionCode == OBTAIN_IP_PATENT) {
      g->players[currentPlayer].ips++;
      
      // remove studentType
      g->players[currentPlayer].studentType[STUDENT_MJ]--;
      g->players[currentPlayer].studentType[STUDENT_MTV]--;
      g->players[currentPlayer].studentType[STUDENT_MMONEY]--;
   } else if (a.actionCode == RETRAIN_STUDENTS) {
      int rate = getExchangeRate(g, currentPlayer, a.disciplineFrom, a.disciplineTo);
      g->players[currentPlayer].studentType[a.disciplineFrom] -= rate;
      g->players[currentPlayer].studentType[a.disciplineTo] += 1;
   }
}
