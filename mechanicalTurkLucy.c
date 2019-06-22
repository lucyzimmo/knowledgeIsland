
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include "Game.h"
#include "mechanicalTurk.h"

action decideAction (Game g) {
   

   int studentScores[] = {0, 5, 5, 3, 2, 1};
   
   // Figuring out which player we are
   int player = getWhoseTurn(g);
   
   // Create action for starting spinoff or passing after the end
   action nextAction = {0,"",0,0};
   
   { //check if enough for an arc
      if ((getStudents(g, player, STUDENT_BQN) > 0) &&
   (getStudents(g, player, STUDENT_BPS) > 0)){
         nextAction.actionCode = OBTAIN_ARC;
         if (player == UNI_A){
            // setting a target path for that player to get to
            // a vertex with 3 regions
            path targetPath;
            
            // defining paths of the closest 3-region vertex that is
            // twp arcs away from starting campus
            path path1 = "" "RL";
            path path2 = "RLRLRLRLRLL" "LL";
            
            // also specifying the region ID's at those vertices
            int path1Regions[] = {3, 7, 8};
            int path2Regions[] = {10, 11, 15};
            
            // initialize counter to cycle through the 3 regions at
            // the specified path closest to tripple region
            int a = 0;
            int path1Score = 0;
            int path2Score = 0;
            while (a < 3){
               int student1 = getDiscipline(g, path1Regions[a]);
               int student2 = getDiscipline(g, path2Regions[a]);
               
               path1Score += studentScores[student1];
               path2Score += studentScores[student2];
               a++;
            }
            
            int validPath;
            int i;
            // assign target path to be the path with the highest score
            if (path1Score >= path2Score){
               i = strlen(A_START);
               validPath = getCampus(g, A_START) == UNI_A || getARC(g, A_START) == UNI_A;
               strcpy(targetPath, path1);
            } else {
               i = strlen("RLRLRLRLRLL");
               validPath = getCampus(g, "RLRLRLRLRLL") == UNI_A || getARC(g, "RLRLRLRLRLL") == UNI_A;
               strcpy(targetPath, path2);
            }
            

            while (i < strlen(targetPath) && validPath == TRUE){
               // building the substring
               sprintf(nextAction.destination,"%s",targetPath);
               nextAction.destination[i+1] = '\0';
               
               // checking whether the current substring is a legal path
               // with having arcs along it
               validPath = (getARC(g, nextAction.destination) == UNI_A);
               i++;
            }
         } else if (player == UNI_B){
            // setting a target path for that player to get to
            // a vertex with 3 regions
            path targetPath;
            
            // defining paths of the closest 3-region vertex that is
            // twp arcs away from starting campus
            path path1 = "LRLRLRRLRL" "BL";
            path path2 = "RRLRL"  "LL";
            
            // also specifying the region ID's at those vertices
            int path1Regions[] = {0, 1, 4};
            int path2Regions[] = {14, 17, 18};
            
            // initialize counter to cycle through the 3 regions at
            // the specified path closest to tripple region
            int a = 0;
            int path1Score = 0;
            int path2Score = 0;
            while (a < 3){
               int student1 = getDiscipline(g, path1Regions[a]);
               int student2 = getDiscipline(g, path2Regions[a]);
               
               path1Score += studentScores[student1];
               path2Score += studentScores[student2];
               a++;
            }
            
            int validPath;
            int i;
            // assign target path to be the path with the highest score
            if (path1Score >= path2Score){
               i = strlen("LRLRLRRLRL");
               validPath = getCampus(g, "LRLRLRRLRL") == UNI_B || getARC(g, "LRLRLRRLRL") == UNI_B;
               strcpy(targetPath, path1);
            } else {
               i = strlen("RRLRL" );
               validPath = getCampus(g, "RRLRL" ) == UNI_B || getARC(g, "RRLRL" ) == UNI_B;
               strcpy(targetPath, path2);
            }
            

            while (i < strlen(targetPath) && validPath == TRUE){
               // building the substring
               sprintf(nextAction.destination,"%s",targetPath);
               nextAction.destination[i+1] = '\0';

               validPath = (getARC(g, nextAction.destination) == UNI_B);
               i++;
            }
         } else if (player == UNI_C) {

            path targetPath;
            

            path path1 = C_START "LL";
            path path2 = "LRLRL" "BL";
            

            int path1Regions[] = {2, 5, 6};
            int path2Regions[] = {12, 13, 16};
            

            int a = 0;
            int path1Score = 0;
            int path2Score = 0;
            while (a < 3){
               int student1 = getDiscipline(g, path1Regions[a]);
               int student2 = getDiscipline(g, path2Regions[a]);
               
               path1Score += studentScores[student1];
               path2Score += studentScores[student2];
               a++;
            }
            
            int validPath;
            int i;
            if (path1Score >= path2Score){
               i = strlen(C_START);
               validPath = getCampus(g, C_START) == UNI_C || getARC(g, C_START) == UNI_C;
               strcpy(targetPath, path1);
            } else {
               i = strlen("LRLRL");
               validPath = getCampus(g, "LRLRL") == UNI_C || getARC(g, "LRLRL") == UNI_C;
               strcpy(targetPath, path2);
            }
            
            while (i < strlen(targetPath) && validPath == TRUE){
               sprintf(nextAction.destination,"%s",targetPath);
               nextAction.destination[i+1] = '\0';

               validPath = (getARC(g, nextAction.destination) == UNI_C);
               i++;
            }
         }
      }
      return(nextAction);
   }
   
   
