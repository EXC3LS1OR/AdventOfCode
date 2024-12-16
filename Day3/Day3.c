#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int getNumber(int count, char * digit1, char * digit2, char * digit3){
  if( count == 1){
    return atoi(digit1);
  } else if( count == 2){
    return 10*atoi(digit1) + atoi(digit2);
  }else if( count == 3){
    return 100*atoi(digit1) + 10*atoi(digit2) + atoi(digit3);
  }

  return 0;
}

int correctInput(char *input){
  int total = 0;
  int count1 = 0;
  int count2 = 0;
  int A, B = 0;
  char digit1[2] = {'\0'}, digit2[2] = {'\0'}, digit3[2] = {'\0'};
  char c = '\0';
  int enabled = 1;
  FILE *fp = fopen(input,"r");
  if (fp == NULL){
    return -1;
  }

  while(!feof(fp)){
    c = fgetc(fp);
    //printf("%c", c);
    if(c == 'm' && enabled){
      long pos = ftell(fp);
      c = fgetc(fp);
      if(c == 'u'){
        c = fgetc(fp);
        if(c == 'l'){
          c = fgetc(fp);
          if(c == '('){
            count1 = 0;
            count2 = 0;
            c = fgetc(fp);
            if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c == '8' || c == '9'){
              count1++;
              digit1[0] = c;
              c = fgetc(fp);
              if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c == '8' || c == '9'){
                count1++;
                digit2[0] = c;
                c = fgetc(fp);
                if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c == '8' || c == '9'){
                  count1++;
                  digit3[0] = c;
                  c = fgetc(fp);
                  if(c == ','){
                    A = getNumber(count1, digit1, digit2, digit3);
                    printf("numberA: %d\n", A);
                    c = fgetc(fp);
                    if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c == '8' || c == '9'){
                      count2++;
                      digit1[0] = c;
                      c = fgetc(fp);
                      if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c == '8' || c == '9'){
                        count2++;
                        digit2[0] = c;
                        c = fgetc(fp);
                        if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c == '8' || c == '9'){
                          count2++;
                          digit3[0] = c;
                          c = fgetc(fp);
                          if(c == ')'){
                            B = getNumber(count2, digit1, digit2, digit3);
                            total += A*B;
                            printf("numberB: %d\n", B);
                          }
                        }else if(c == ')'){
                          B = getNumber(count2, digit1, digit2, digit3);
                          total += A*B;
                          printf("numberB: %d\n", B);
                        }

                      }else if(c == ')'){
                        B = getNumber(count2, digit1, digit2, digit3);
                        total += A*B;
                        printf("numberB: %d\n", B);
                      }
                    }
                  }
                }else if(c == ','){
                  A = getNumber(count1, digit1, digit2, digit3);
                  printf("numberA: %d\n", A);
                  c = fgetc(fp);
                  if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c == '8' || c == '9'){
                    count2++;
                    digit1[0] = c;
                    c = fgetc(fp);
                    if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c == '8' || c == '9'){
                      count2++;
                      digit2[0] = c;
                      c = fgetc(fp);
                      if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c == '8' || c == '9'){
                        count2++;
                        digit3[0] = c;
                        c = fgetc(fp);
                        if(c == ')'){
                          B = getNumber(count2, digit1, digit2, digit3);
                          total += A*B;
                          printf("numberB: %d\n", B);
                        }
                      }else if(c == ')'){
                        B = getNumber(count2, digit1, digit2, digit3);
                        total += A*B;
                        printf("numberB: %d\n", B);
                      }

                    }else if(c == ')'){
                      B = getNumber(count2, digit1, digit2, digit3);
                      total += A*B;
                      printf("numberB: %d\n", B);
                    }
                  }
                }

              }else if(c == ','){
                A = getNumber(count1, digit1, digit2, digit3);
                printf("numberA: %d\n", A);
                c = fgetc(fp);
                if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c == '8' || c == '9'){
                  count2++;
                  digit1[0] = c;
                  c = fgetc(fp);
                  if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c == '8' || c == '9'){
                    count2++;
                    digit2[0] = c;
                    c = fgetc(fp);
                    if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c =='7' || c == '8' || c == '9'){
                      count2++;
                      digit3[0] = c;
                      c = fgetc(fp);
                      if(c == ')'){
                        B = getNumber(count2, digit1, digit2, digit3);
                        total += A*B;
                        printf("numberB: %d\n", B);
                      }
                    }else if(c == ')'){
                      B = getNumber(count2, digit1, digit2, digit3);
                      total += A*B;
                      printf("numberB: %d\n", B);
                    }

                  }else if(c == ')'){
                    B = getNumber(count2, digit1, digit2, digit3);
                    total += A*B;
                    printf("numberB: %d\n", B);
                  }
                }
              }
            }

          }
        }
      } 
      fseek(fp, pos, SEEK_SET);
    }
    if(c == 'd'){
      long pos = ftell(fp);
      c = fgetc(fp);
      if(c == 'o'){
        c = fgetc(fp);
        if(c == 'n'){
          c = fgetc(fp);
          if(c == '\''){
            c = fgetc(fp);
            if(c == 't'){
              c = fgetc(fp);
              if(c == '('){
                c = fgetc(fp);
                if(c == ')'){
                  enabled = 0;
                } 
              } 
            } 
          } 
        }else{
          if(c == '('){
            c = fgetc(fp);
            if(c == ')'){
              enabled = 1;
            } 
          } 
        }       
      }
      fseek(fp, pos, SEEK_SET);
    }

  }
  fclose(fp);
  return total;
}

int main(){

  int result = 0;

  result = correctInput("input.txt");

  printf("Final result: %d\n", result);
  return 0;
}