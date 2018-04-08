#include <stdio.h>
#include <stdlib.h>

int *createSeq(int size){
  int *first = malloc(size * sizeof(int)), i;
  if(first != NULL){
    printf("Digite sua sequencia:\n");
    for(i = 0; i < size; i++){
      scanf("%d", first+i);
    }
  }
  return first;
}

int printSubseq (int *seq, int size, int k){
  int i, j, consec;
  for(i = 0; i < size; i++){
    //sempre olha para a variavel de tras
    consec = 1; // enquanto for consecutivo
    for(j = 1; consec && j < k && i + j < size; j++){
      if(*(seq + i + j - 1) == *(seq + i + j) - 1){
        // verifica atual com anterior
        if(j == 1)
          printf("\n%d ", *(seq + i + j -1));
        printf("%d ", *(seq + i + j));
      }
      else consec = 0;
    }
    if(*(seq + i + j - 1) != *(seq + i + j) - 1)  // se a prox nao eh consec, pega ultimo elemento
      i = i + j - 1;
  }
}


int main(){
  int k, M;

  printf("Tamanho M da sequencia a digitar: ");
  scanf("%d", &M);
  printf("Maior tamanho k das subsequencias: ");
  scanf("%d", &k);

  int *seq = createSeq(M);
  printSubseq(seq, M, k);
  return 0;
}
