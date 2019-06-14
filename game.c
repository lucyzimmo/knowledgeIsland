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

struct _game {
    Player players[NUM_UNIS];
    Hex hexes[NUM_Regions];
    int turnNumber; 
}
typedef struct _hex {
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
