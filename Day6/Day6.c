#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef enum direction{
  UP,
  RIGHT,
  DOWN,
  LEFT
}direction;

typedef struct past{
  int x;
  int y;
  direction direction;
  struct past* next;
}past;


void printMap(int ** map, int numLines, int numCols){

  printf("Map:");
  for(int i = 0; i < numLines;i++){
    for(int j = 0; j < numCols; j++){
      printf("%d", map[i][j]);
    }
    printf("\n");
  }

  return;
}

void freeList(past * head){

  past * aux = head;

  while(head != NULL){
    head = head->next;
    free(aux);
    aux = head;
  } 

  return;
}

int checkHistory(past * head, int posX, int posY, direction facing){

  past * aux = head;

  while(aux != NULL){

    if(aux->x == posX && aux->y == posY && aux->direction == facing){
      return 1;
    }

    aux = aux->next;
  }

  return 0;

}

int walk(int ** map, int numLines, int numCols, int posX, int posY, direction facing) {

  int inside = 1;
  int directionSize = 4;
  int numberOfTurns = 0;

  past * obstacleHistory = NULL;
  past * aux = NULL;

  while(inside){

    if(facing == 0 && posY == 0){
      inside = 0;
      break;
    }else if(facing == 1 && posX == numCols-1){
      inside = 0;
      break;
    }else if(facing == 2 && posY == numLines-1){
      inside = 0;
      break;
    }else if(facing == 3 && posX == 0){
      inside = 0;
      break;
    }

    if(facing == 0){
      if(map[posY - 1][posX] != -1){
        posY -= 1;
        //map[posY][posX] = 1;
      }else{
        facing = (facing + 1) % directionSize;
        if(obstacleHistory == NULL){
          obstacleHistory = (past *) calloc(1, sizeof(past));
          aux = obstacleHistory;
          aux->x = posX;
          aux->y = posY - 1;
          aux->direction = facing;
          aux->next = NULL;
        }else{
          if(checkHistory(obstacleHistory, posX, posY -1, facing)){
            freeList(obstacleHistory);
            return 1;
          }
          aux->next = (past *) calloc(1, sizeof(past));
          aux = aux->next;
          aux->x = posX;
          aux->y = posY - 1;
          aux->direction = facing;
          aux->next = NULL;
        }

      }
    }else if(facing == 1){
      if(map[posY][posX + 1] != -1){
        posX += 1;
        //map[posY][posX] = 1;
      }else{
        facing = (facing + 1) % directionSize;
        if(obstacleHistory == NULL){
          obstacleHistory = (past *) calloc(1, sizeof(past));
          aux = obstacleHistory;
          aux->x = posX + 1;
          aux->y = posY;
          aux->direction = facing;
          aux->next = NULL;
        }else{
          if(checkHistory(obstacleHistory, posX + 1, posY, facing)){
            freeList(obstacleHistory);
            return 1;
          }
          aux->next = (past *) calloc(1, sizeof(past));
          aux = aux->next;
          aux->x = posX + 1;
          aux->y = posY;
          aux->direction = facing;
          aux->next = NULL;
        }
      }
    }else if(facing == 2){
      if(map[posY + 1][posX] != -1){
        posY += 1;
       //map[posY][posX] = 1;
      }else{
        facing = (facing + 1) % directionSize;
        if(obstacleHistory == NULL){
          obstacleHistory = (past *) calloc(1, sizeof(past));
          aux = obstacleHistory;
          aux->x = posX;
          aux->y = posY + 1;
          aux->direction = facing;
          aux->next = NULL;
        }else{
          if(checkHistory(obstacleHistory, posX, posY + 1, facing)){
            freeList(obstacleHistory);
            return 1;
          }
          aux->next = (past *) calloc(1, sizeof(past));
          aux = aux->next;
          aux->x = posX;
          aux->y = posY + 1;
          aux->direction = facing;
          aux->next = NULL;
        }
      }
    }else if(facing == 3){
      if(map[posY][posX - 1] != -1){
        posX -= 1;
        //map[posY][posX] = 1;
      }else{
        facing = (facing + 1) % directionSize;
        if(obstacleHistory == NULL){
          obstacleHistory = (past *) calloc(1, sizeof(past));
          aux = obstacleHistory;
          aux->x = posX - 1;
          aux->y = posY;
          aux->direction = facing;
          aux->next = NULL;
        }else{
          if(checkHistory(obstacleHistory, posX - 1, posY, facing)){
            freeList(obstacleHistory);
            return 1;
          }
          aux->next = (past *) calloc(1, sizeof(past));
          aux = aux->next;
          aux->x = posX - 1;
          aux->y = posY;
          aux->direction = facing;
          aux->next = NULL;
        }
      }
    }


  }

  return 0;
}

int countSteps(int ** map, int numLines, int numCols){

  int steps = 0;

  for(int i = 0; i < numLines;i++){
    for(int j = 0; j < numCols; j++){
      if(map[i][j] == 1){
        steps++;
      }
    }
  }

  return steps;
}

int tryObstacles(int ** map, int numLines, int numCols, int posX, int posY){

  int correctObstacles = 0;
  direction facing = UP;
  int obstacleCount = 0;

  for(int i = 0; i < numLines; i++){
    for(int j = 0; j < numCols; j++){
      if(map[i][j] == 0){
        map[i][j] = -1;

        obstacleCount++;
        printf("Obstacle count = %d\n", obstacleCount);
        printf("Correct Obstacles: %d\n", correctObstacles);
        facing = UP;

        correctObstacles += walk(map, numLines, numCols, posX, posY, facing);

        map[i][j] = 0;
      }
    }
  }

  return correctObstacles;

}


int createGuardPath(const char * input){

  int ** map = NULL;  
  FILE * fp = NULL;
  char c = '\0';
  int numLines = 0;
  int numCols = 0;
  int counter = 0;
  int posX = 0, posY = 0;
  int result = 0;
  

  fp = fopen(input,"r");

  while(!feof(fp)){
    c = fgetc(fp);
    if(c=='\n' || c == EOF){
      numLines++;
      numCols=counter;
      counter = 0;
    }else{
      counter++;
    }
  }
  fclose(fp);

  map = (int **) calloc(numLines, sizeof(int *));
  for(int i=0; i<numCols; i++){
    map[i] = (int *) calloc(numCols, sizeof(int));
  }

  fp = fopen(input,"r");

  int i = 0;
  int j = 0;
  while(!feof(fp)){
    c = fgetc(fp);
    if(c=='\n' || c == EOF){
      i++;
      j=0;
    }else{
      if(c == '.'){
        map[i][j] = 0;
      }else if(c == '#'){
        map[i][j] = -1;
      }else if(c == '^'){
        map[i][j] = 1;
        posX = j;
        posY = i;
      }else{
        //printf("char: %c\nI:%d\nJ:%d\n", c,i,j);
        //printf("EXCEPTION: Invalid\n");
      }
      j++;
    }
  }
  fclose(fp);

  result = tryObstacles(map, numLines, numCols, posX, posY);

  //printMap(map, numLines, numCols);
  
  for(int i=0; i<numCols; i++){
    free(map[i]);
  }
  free(map);

  printf("Number of lines: %d\nNumber of cols: %d\n", numLines, numCols);
  return result;
}


int main(){

  int result = 0;

  //result = findXMAS("input.txt");
  result = createGuardPath("input.txt");


  printf("Final result: %d\n", result);
  return 0;
}