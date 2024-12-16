#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void createCharArray(char *** arrayPointer,int numLines, int numCols){

  (*arrayPointer) = (char **) calloc(numLines,sizeof(char *));
  for(int i=0; i<numLines;i++){
    (*arrayPointer)[i] = (char *) calloc(numCols,sizeof(char));
  } 

  return;
}

void freeCharArray(char *** arrayPointer, int numLines, int numCols){

  for(int i=0; i<numLines;i++){
    free((*arrayPointer)[i]);
  }
  free(*arrayPointer);

  return;
}

void printCharArray(char ** arrayPointer, int numLines, int numCols){
  
  printf("Printing char array:\n");
  for(int i=0; i<numLines;i++){
    for(int j=0; j<numCols;j++){
      printf("%c",arrayPointer[i][j]);
    }
    printf("\n");
  } 

  return;
}

int checkVerticals(char ** arrayPointer, int numLines, int numCols, int x, int y){

  int count = 0;

  if(x >=3){
    if(arrayPointer[x - 1][y] == 'M' && arrayPointer[x - 2][y] == 'A' && arrayPointer[x - 3][y] == 'S'){
      count++;
    }
  }

  if(x <= numLines - 4){
    if(arrayPointer[x + 1][y] == 'M' && arrayPointer[x + 2][y] == 'A' && arrayPointer[x + 3][y] == 'S'){
      count++;
    }

  }

  return count;
}

int checkHorizontals(char ** arrayPointer, int numLines, int numCols, int x, int y){

  int count = 0;

  if(y >=3){
    if(arrayPointer[x][y - 1] == 'M' && arrayPointer[x][y - 2] == 'A' && arrayPointer[x][y - 3] == 'S'){
      count++;
    }
  }

  if(y <= numCols - 4){
    if(arrayPointer[x][y + 1] == 'M' && arrayPointer[x][y + 2] == 'A' && arrayPointer[x][y + 3] == 'S'){
      count++;
    }

  }

  return count;
}

int checkDiagonals(char ** arrayPointer, int numLines, int numCols, int x, int y){

  int count = 0;

  if(x >=3 && y >=3){
    if(arrayPointer[x - 1][y - 1] == 'M' && arrayPointer[x - 2][y - 2] == 'A' && arrayPointer[x - 3][y - 3] == 'S'){
      count++;
    }
  }

  if(x >=3 && y <= numCols - 4){
    if(arrayPointer[x - 1][y + 1] == 'M' && arrayPointer[x - 2][y + 2] == 'A' && arrayPointer[x - 3][y + 3] == 'S'){
      count++;
    }

  }

  if(x <= numLines - 4 && y >=3){
    if(arrayPointer[x + 1][y - 1] == 'M' && arrayPointer[x + 2][y - 2] == 'A' && arrayPointer[x + 3][y - 3] == 'S'){
      count++;
    }
  }

  if(x <= numLines - 4 && y <= numCols - 4){
    if(arrayPointer[x + 1][y + 1] == 'M' && arrayPointer[x + 2][y + 2] == 'A' && arrayPointer[x + 3][y + 3] == 'S'){
      count++;
    }

  }

  return count;
}

int validX_MAS(char ** arrayPointer, int numLines, int numCols, int x, int y){

  int MAS_count = 0;

  if( x == 0 || y == 0 || x == numLines - 1 || y == numCols - 1){
    return 0;
  }

  if(arrayPointer[x - 1][y - 1] == 'M' && arrayPointer[x + 1][y + 1] == 'S'){
    MAS_count++;
  }
  if(arrayPointer[x - 1][y - 1] == 'S' && arrayPointer[x + 1][y + 1] == 'M'){
    MAS_count++;
  }
  if(arrayPointer[x + 1][y - 1] == 'M' && arrayPointer[x - 1][y + 1] == 'S'){
    MAS_count++;
  }
  if(arrayPointer[x + 1][y - 1] == 'S' && arrayPointer[x - 1][y + 1] == 'M'){
    MAS_count++;
  }

  if(MAS_count == 2){
    return 1;
  }

  return 0;

}


int findXMAS(const char * input){

  FILE * fp = fopen(input,"r");
  char c = 0;
  char buffer[1024];
  int numLines = 0;
  int sizeLine = 0;
  char ** letters = NULL;
  int sum = 0;

  while (!feof(fp)){
    fgets(buffer,1024,fp);
    numLines++;
  }
  sizeLine = strlen(buffer);
  printf("Line size: %d\n",sizeLine);
  printf("num lines: %d\n",numLines);

  fclose(fp);	

  createCharArray(&letters, numLines, sizeLine);
  
  fp = fopen(input,"r");
  int i = 0, j = 0;
  while(!feof(fp)){
    c = fgetc(fp);
    if(c != '\n'){
      letters[i][j] = c;
      j++;
    }else{
      j=0;
      i++;
    }
  }
  fclose(fp);

  //printCharArray(letters, numLines, sizeLine);

  for(int i = 0; i < numLines; i++){
    for(int j = 0; j < sizeLine; j++){
      if(letters[i][j] == 'X'){
        sum += checkVerticals(letters, numLines, sizeLine, i, j);
        sum += checkHorizontals(letters, numLines, sizeLine, i, j);
        sum += checkDiagonals(letters, numLines, sizeLine, i, j);
        
      }
    }
  }


  freeCharArray(&letters, numLines, sizeLine);
  return sum;
}

int findX_MAS(const char * input){

  FILE * fp = fopen(input,"r");
  char c = 0;
  char buffer[1024];
  int numLines = 0;
  int sizeLine = 0;
  char ** letters = NULL;
  int sum = 0;

  while (!feof(fp)){
    fgets(buffer,1024,fp);
    numLines++;
  }
  sizeLine = strlen(buffer);
  printf("Line size: %d\n",sizeLine);
  printf("num lines: %d\n",numLines);

  fclose(fp);	

  createCharArray(&letters, numLines, sizeLine);
  
  fp = fopen(input,"r");
  int i = 0, j = 0;
  while(!feof(fp)){
    c = fgetc(fp);
    if(c != '\n'){
      letters[i][j] = c;
      j++;
    }else{
      j=0;
      i++;
    }
  }
  fclose(fp);

  //printCharArray(letters, numLines, sizeLine);

  for(int i = 0; i < numLines; i++){
    for(int j = 0; j < sizeLine; j++){
      if(letters[i][j] == 'A'){
        if(validX_MAS(letters, numLines, sizeLine, i, j)){

          sum ++;

        }
      }
    }
  }


  freeCharArray(&letters, numLines, sizeLine);
  return sum;
}

int main(){

  int result = 0;

  //result = findXMAS("input.txt");
  result = findX_MAS("input.txt");


  printf("Final result: %d\n", result);
  return 0;
}