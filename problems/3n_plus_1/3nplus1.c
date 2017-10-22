#include <stdio.h>
#include <stdlib.h>

int is_odd(int n){
  return n%2;
}

int cycle_length(int number){
  int count=1;
  while(number > 1){
    if(is_odd(number))
      number = 3*number +1;
    else
      number = number/2;
    count++;
  }
  return count;
}
int main(int argc, const char * argv[]){
  if(argc != 3){
    printf("Devem ser passados dois números como parâmetro.");
    return 1;
  }
  int i = strtol(argv[1], NULL, 10);
  int j = strtol(argv[2], NULL, 10);
  printf("i = %d\n", i);
  int aux;
  int max_c_l = cycle_length(i); // Maximum cycle length
  for(i=i+1;i<=j;i++){
    aux = cycle_length(i);
    if(max_c_l < aux)
      max_c_l = aux;
  }
  printf("%s %s %d", argv[1], argv[2], max_c_l);
  return 0;
}
