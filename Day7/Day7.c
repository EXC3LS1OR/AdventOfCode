#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>


long long tryOperators(long long * values, int size, long long limit){

  if(limit >= pow(2, size - 2)){
    return 0;
  }
  //printf("%ld", limit);
  long long total = values[1];
  int operation = 0;
  long long temp = limit;
  for(int i = 2; i < size; i++){

    operation = temp & 1;
    temp = temp >> 1;
    //printf("Operation:%d\n", operation);
    if(operation == 0){

      total = total + values[i];

    }else if(operation == 1){

      total = total * values[i];

    }

  }

  if(total == values[0]){
    return values[0];
  }

  return tryOperators(values, size, limit + 1);
}

long long createInput(const char *input){

  long long total = 0;
  FILE *fp = NULL;
  long long * values = NULL;
  char buffer[1024];
  char aux[1024];
  int count = 0;
  int j = 0;

  fp = fopen(input,"r");

  while(fgets(aux,1024,fp)){
    strcpy(buffer,aux);

    char * token = strtok(aux, ":");
    count++;

    char *temp = strtok(NULL, " ");
    while(temp){
      count++;
      temp = strtok(NULL, " ");
    }

    values = (long long *) calloc(count, sizeof(long long));

    token = strtok(buffer, ":");
    values[0] = atol(token);

    temp = strtok(NULL, " ");
    j=1;
    while(temp){
      values[j] = atol(temp);
      temp = strtok(NULL, " ");
      j++;
    }

    for(int i=0; i< count; i++){
      printf("%lld ", values[i]);
    }
    printf("\n");
    total += tryOperators(values, count, 0ll);

    free(values);
    count = 0;
  }

  fclose(fp);


  return total;
}


int main(){

  long long result = 0;

  result = createInput("input.txt");


  printf("Final result: %lld\n", result);
  return 0;
}