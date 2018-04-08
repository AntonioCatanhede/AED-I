#include <stdio.h>
#include <stdlib.h>

void reverseVector(int *v, int size){
  int i, tmp;
  for (i = 0; i < size/2; i++){
    tmp = v[i];
    v[i] = v[size - 1 - i];
    v[size - 1 -i] = tmp;
  }
  printf("\n");
}

int* posOccurrence (char *string, int size, char letter){
  int i = 0, oc_size = 0, *occurence = malloc(size * sizeof(int));
  int *tmp = occurence;
  if (occurence == NULL) return NULL;

  while((*string) != '\0'){
    if(*string == letter){
      *tmp = i;
      tmp++;
      oc_size++;
    }
    i++;
    string++;
  }
  while(oc_size < size){
    occurence[oc_size++] = -1;
  }
  return occurence;
}

// Indagacoes:
// eu incrementei os ponteiros w1 e w2.
// pq isso nao modifica o vetor do main?
char *concString(char* w1, char *w2, int s1, int s2){
  char *word = malloc((s1+s2 - 2) * sizeof(char));
  if(word == NULL) return NULL;
  char *first = word;

  while(*w1 != '\0'){
    *word = *w1;
    word++;
    w1++;
  }
  while(*w2 != '\0'){
    *word = *w2;
    word++;
    w2++;
  }
  *word = '\0';
  return first;
}

int main(){
  int i, v[5] = {1, 2, 3, 4, 5};
  char letter = 'l';

  reverseVector(v, sizeof(v)/sizeof(v[0]));
  for(i = 0; i < sizeof(v)/sizeof(v[0]); i++)
    printf("%d ", v[i]);

  char word1[6] = "Hello\0", word2[6] = "world\0";
  char *word = concString(word1, word2, sizeof(word1)/sizeof(word1[0]), sizeof(word2)/sizeof(word2[0]));
  printf("Primeira palavra: %s\nSegunda palavra: %s\nConcatenado: %s\n", word1, word2, word);

  int *pos_occurrence = posOccurrence(word1, sizeof(word1)/sizeof(word[0]), letter);
  printf("Posicoes de %c na palavra %s: ", letter, word1);
  for(i = 0; pos_occurrence[i] != -1; i++)
    printf("%d ", pos_occurrence[i]);
  return 0;
}
