#include <stdio.h>
#include <stdlib.h>


typedef struct ID
{
  int id;
  struct ID *next;
}ID;


void splitList(ID *head, ID **front, ID **back) {
    ID *slow = head;
    ID *fast = head->next;

    // Advance fast by two and slow by one to find the middle
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = head;
    *back = slow->next;
    slow->next = NULL;
}

// Helper function to merge two sorted lists
ID *mergeSortedLists(ID *a, ID *b) {
    if (!a) return b;
    if (!b) return a;

    ID *result = NULL;
    if (a->id <= b->id) {
        result = a;
        result->next = mergeSortedLists(a->next, b);
    } else {
        result = b;
        result->next = mergeSortedLists(a, b->next);
    }
    return result;
}

// Main merge sort function
void mergeSort(ID **headRef) {
    ID *head = *headRef;
    if (!head || !head->next) return;

    ID *front = NULL;
    ID *back = NULL;

    // Split the list into two halves
    splitList(head, &front, &back);

    // Sort each half recursively
    mergeSort(&front);
    mergeSort(&back);

    // Merge the sorted halves
    *headRef = mergeSortedLists(front, back);
}

void printList(ID *head) {
    while (head) {
        printf("ID: %d\n", head->id);
        head = head->next;
    }
}

void freeList(ID *head) {
    ID *temp;
    while (head != NULL) {
        temp = head;      // Store the current node
        head = head->next; // Move to the next node
        free(temp);        // Free the current node
    }
}

int main(){

  FILE *fp = fopen("input.txt","r");

  ID *list1 = NULL;
  ID *list2 = NULL;
  ID *aux1 = NULL;
  ID *aux2 = NULL;

  list1 = (ID*)calloc(1, sizeof(ID));
  aux1=list1;
  list2 = (ID*)calloc(1, sizeof(ID));
  aux2=list2;
  
  fscanf(fp, "%d %d ", &(aux1->id), &(aux2->id));


  while(!feof(fp)){
    
    aux1->next = (ID*)calloc(1, sizeof(ID));
    aux1=aux1->next;
    aux2->next = (ID*)calloc(1, sizeof(ID));
    aux2=aux2->next;    

    fscanf(fp, "%d %d ", &(aux1->id), &(aux2->id));

  }

  mergeSort(&list1);
  mergeSort(&list2);

  aux1=list1;
  aux2=list2;
  int sum=0;
  int diference=0;
  int count=0;
  while(aux1){
    aux2 = list2;
    count=0;
    while(aux2){
        if(aux1->id == aux2->id){
            count++;
        }
        aux2=aux2->next;
    }
    sum += count*aux1->id;


    aux1=aux1->next;
  }

  printf("Sum: %d\n", sum);
  freeList(list1);
  freeList(list2);

  fclose(fp);
  return 0;
}