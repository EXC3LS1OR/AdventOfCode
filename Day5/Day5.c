#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


typedef struct updateValue{
  int value;
  struct updateValue *next;
  struct updateValue *prev;
}updateValue;

typedef struct rule{
  int A;
  int B;
  struct rule *next;
}rule;

void freeList(void *head, size_t next_offset) {
    void *aux = NULL;

    while (head != NULL) {
        aux = head;
        head = *(void **)((char *)head + next_offset);
        free(aux);
    }

  return;
}

void printRules(rule *head){

  rule *aux = head;

  while(aux != NULL){
    printf("%d|%d\n",aux->A,aux->B);
    aux = aux->next;
  }

}

void printUpdate(updateValue *head){

  updateValue *aux = head;

  while(aux != NULL){
    printf("%d,",aux->value);
    aux = aux->next;
  }
  printf("\n");

}

int findMiddle(updateValue * head, updateValue * tail){

  while(head != tail){

    if(head == NULL || tail == NULL){
      printf("ERROR!!!\n");
      return -1;
    }

    head = head->next;
    tail = tail->prev;

  }
  return head->value;
}


int correctUpdate(updateValue **updateHead, updateValue **updateTail, rule *ruleListHead) {
    if (!updateHead || !*updateHead || !ruleListHead) {
        printf("ERROR!!!\n");
        return -1;
    }
    printf("Incorrect update:\n");
    printUpdate(*updateHead);
    int incorrect = 1;

    while (incorrect) {
        incorrect = 0;

        updateValue *updateAux1 = *updateHead;

        while (updateAux1 && updateAux1->next) {
            updateValue *updateAux2 = updateAux1->next;
            rule *ruleAux = ruleListHead;

            while (ruleAux) {
                if ((ruleAux->A == updateAux2->value) && (ruleAux->B == updateAux1->value)) {
                    incorrect = 1;

                    if (updateAux1->prev) {
                        updateAux1->prev->next = updateAux2;
                    } else {
                        *updateHead = updateAux2;
                    }

                    if (updateAux2->next) {
                        updateAux2->next->prev = updateAux1;
                    } else {
                        *updateTail = updateAux1;
                    }

                    updateAux2->prev = updateAux1->prev;
                    updateAux1->next = updateAux2->next;
                    updateAux2->next = updateAux1;
                    updateAux1->prev = updateAux2;

                    updateAux1 = *updateHead;
                    break;
                }
                ruleAux = ruleAux->next;
            }
            if (incorrect) {
                break;
            }
            updateAux1 = updateAux1->next;
        }
    }

    return findMiddle(*updateHead, *updateTail);
}



int processUpdate(updateValue ** updateHead, updateValue ** updateTail, rule * ruleListHead){
  updateValue * updateAux1 = *updateTail;
  updateValue * updateAux2 = NULL;
  rule * ruleAux = NULL;

  while(updateAux1->prev != NULL){
    updateAux2 = updateAux1->prev;
    while(updateAux2 != NULL){
      ruleAux = ruleListHead;
      while(ruleAux != NULL){
        if((ruleAux->A == updateAux1->value) && (ruleAux->B == updateAux2->value)){
          //printf("Wrong\n");
          return correctUpdate(updateHead, updateTail, ruleListHead);
        }
        ruleAux = ruleAux->next;
      }
      updateAux2 = updateAux2->prev;
    }
    updateAux1 = updateAux1->prev;
  }

  return 0;
}

int getCorrectUpdates(const char * input){

  FILE *fp = NULL;
  char buffer[1024];
  char c;
  int i = 0;
  int sum = 0;
  updateValue * updateHead = NULL;
  updateValue * updateTail = NULL;
  updateValue * aux = NULL;
  rule * ruleListHead = NULL;
  rule * ruleListAux = NULL;
  rule * ruleListAux2 = NULL;


  fp = fopen(input,"r");


  fgets(buffer,1024,fp);
  ruleListHead = (rule *) calloc(1, sizeof(rule));
  ruleListAux = ruleListHead;
  sscanf(buffer,"%d|%d ",&(ruleListAux->A), &(ruleListAux->B));
  ruleListAux->next = NULL;

  do{
    fgets(buffer,1024,fp);
    ruleListAux->next = (rule *) calloc(1, sizeof(rule));
    ruleListAux2 = ruleListAux;
    ruleListAux = ruleListAux->next;
    ruleListAux->next = NULL;
  }while(sscanf(buffer,"%d|%d ",&(ruleListAux->A), &(ruleListAux->B)) == 2);

  ruleListAux2->next = NULL;  
  free(ruleListAux);

  printRules(ruleListHead);

  i = 0;

  updateHead = (updateValue * ) calloc(1, sizeof(updateValue));
  updateTail = updateHead;
  updateHead->next = NULL;
  updateHead->prev = NULL;

  while(!feof(fp)){
    c = fgetc(fp);
    if(c != '\n'){
      if(c == ','){
        i = 0;
        updateTail->next = (updateValue * ) calloc(1, sizeof(updateValue));
        updateTail->next->prev = updateTail;
        updateTail = updateTail->next;
        //printf("Buffer: %s\n", buffer);
        //printf("Buffer_Value: %d\n", atoi(buffer));
        updateTail->value = atoi(buffer);
        updateTail->next = NULL;
      }else{
        buffer[i] = c;
        buffer[i + 1] = '\0';
        i++;
      }
    }else{
      i=0;
      updateTail->next = (updateValue * ) calloc(1, sizeof(updateValue));
      updateTail->next->prev = updateTail;
      updateTail = updateTail->next;
      updateTail->value = atoi(buffer);
      updateTail->next = NULL;
      //delete first and empty block
      aux = updateHead;
      updateHead = updateHead->next;
      updateHead->prev = NULL;
      free(aux);
      //chack validity and get middle element
      printUpdate(updateHead);
      sum += processUpdate(&updateHead, &updateTail, ruleListHead);
      //free update
      freeList(updateHead, offsetof(updateValue, next));
      updateHead = (updateValue * ) calloc(1, sizeof(updateValue));
      updateTail = updateHead;
      updateHead->next = NULL;
      updateHead->prev = NULL;
    }
  }

      updateTail->next = (updateValue * ) calloc(1, sizeof(updateValue));
      updateTail->next->prev = updateTail;
      updateTail = updateTail->next;
      updateTail->value = atoi(buffer);
      updateTail->next = NULL;
      //delete first and empty block
      aux = updateHead;
      updateHead = updateHead->next;
      updateHead->prev = NULL;
      free(aux);
      //chack validity and get middle element
      printUpdate(updateHead);
      sum += processUpdate(&updateHead, &updateTail, ruleListHead);
      //free update
      freeList(updateHead, offsetof(updateValue, next));
      updateHead = (updateValue * ) calloc(1, sizeof(updateValue));
      updateTail = updateHead;
      updateHead->next = NULL;
      updateHead->prev = NULL;

  freeList(updateHead, offsetof(updateValue, next));
  freeList(ruleListHead, offsetof(rule, next));


  fclose(fp);

  return sum;
}

int main(){

  int result = 0;

  //result = findXMAS("input.txt");
  result = getCorrectUpdates("input.txt");


  printf("Final result: %d\n", result);
  return 0;
}