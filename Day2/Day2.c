#include <stdio.h>
#include <stdlib.h>


typedef struct value
{
  int number;
  struct value * next;
}value;

void printLine(value * head){

  while(head){
    printf("%d ", head->number);
    head = head->next;
  }
  printf("\n");

  return;
}

int processInvalidLine(value * head){
    value *current = head, *prev = NULL;
    value * aux1, *aux2 = NULL;
    int diff = 0;
    int sign = 0;
    int isValid = 1;
    while (current) {
        // Temporarily remove the current node
        if (prev){
          prev->next = current->next; // Bypass the current node
        }else{
          head = current->next;           // Update head if removing the first node
        } 

        // Print the updated list
        isValid = 1;
        aux1 = head;
        if(aux1->number - aux1->next->number < 0){
          sign = 1;
        }else if(aux1->number - aux1->next->number > 0){
          sign = -1;
        }else{
          isValid = 0;
        }
        while (aux1->next != NULL)
        {
          aux2 = aux1->next;
          diff = aux1->number - aux2->number;
          if ((diff < 0 && sign != 1) || (diff > 0 && sign != -1)){
            isValid = 0;
            break;
          }

          if(diff < 0){
            diff = 0-diff;
          }
          if((diff < 1) || (diff > 3)){
            isValid = 0;
            break;
          }


          aux1 = aux1->next;
        }

        if (isValid) {
            return 1;
        }
        
        // Restore the list
        if (prev){
          prev->next = current;
        } 
        else{
          head = current;
        }

        // Move to the next node
        prev = current;
        current = current->next;
    }

  return 0;
}

int main(){

  FILE *fp = fopen("input.txt","r");
  char buffer[100];
  int numReports = 0;

  while(!feof(fp)){
    fgets(buffer,sizeof(buffer),fp);
    numReports++;
  }
  fclose(fp);
  
  value * listReports = (value*) calloc(numReports,sizeof(value));
  value * aux1 = listReports;
  value * aux2 = aux1;
  int trash =0;
  fp = fopen("input.txt","r");
  char * ptr;
  while(!feof(fp)){
    aux2 = aux1;    
    fgets(buffer,sizeof(buffer),fp);
    ptr = buffer;
    while(sscanf(ptr,"%d", &(aux2->number)) == 1){
      while (*ptr && (*ptr == ' ' || *ptr == '\t')) ptr++;
      while (*ptr && ((*ptr >= '0' && *ptr <= '9') || *ptr == '-')) ptr++;
      if (sscanf(ptr, "%d", &trash) == 1) {
        aux2->next = (value*) calloc(1,sizeof(value));
        aux2 = aux2->next;
        aux2->next = NULL;
      }
    }
    aux1++;
  }

  aux1 = listReports;
  for(int i = 0;i<numReports;i++){
    printLine(aux1);
    aux1++;
  }
//##########################
  aux1 = listReports;
  aux2 = aux1;
  int diff = 0;
  int sign = 0; // 1 ascending; -1 descending
  int safeCount = 0;
  int isValid = 1;
  value * aux3 = NULL;  
  for(int i = 0;i<numReports;i++){
    isValid = 1;
    aux2 = aux1;
    if(aux2->number - aux2->next->number < 0){
      sign = 1;
    }else if(aux2->number - aux2->next->number > 0){
      sign = -1;
    }else{
      isValid=0;
    }
    while (aux2->next != NULL)
    {
      aux3 = aux2->next;
      diff = aux2->number - aux3->number;
      if ((diff < 0 && sign != 1) || (diff > 0 && sign != -1)){
        isValid = 0;
        break;
      }

      if(diff < 0){
        diff = 0-diff;
      }
      if((diff < 1) || (diff > 3)){
        isValid = 0;
        break;
      }


      aux2 = aux2->next;
    }

    if (isValid) {
        safeCount++; // Increment only if the line is valid
    }else{
      safeCount += processInvalidLine(aux1);
    }
    aux1++;
  }
    printf("safeCount: %d\n", safeCount);
//###########################

  printf("%d\n",listReports->number);
  printf("%d\n",(listReports + numReports-1)->number);
  printf("number of lines:%d\n",numReports);
  printf("safe count:%d\n",safeCount);
  fclose(fp);
  
  return 0;
}