#include <stdio.h>
#include <stdlib.h>

// conversao no sentido abcdefg em um displayer BCD
char conversao_bcd[16][9] = {" _ | ||_|",
                            "     |  |",
                            " _  _||_ ",
                            " _  _| _|",
                            "   |_|  |",
                            " _ |_  _|",
                            " _ |_ |_|",
                            " _   |  |",
                            " _ |_||_|",
                            " _ |_| _|",
                            " _ |_|| |",
                            "   |_ |_|",
                            " _ |  |_ ",
                            "    _||_|",
                            " _ |_ |_ ",
                            " _ |_ |  "
                          };

void bcd (char* seq, long t_max){
  for(int i = 0; i < 9; i=i+3){
    for(int j = t_max; j + 1; j--){
      printf("%c%c%c ", conversao_bcd[seq[j] - '0'][i], conversao_bcd[seq[j]-'0'][i+1], conversao_bcd[seq[j]-'0'][i+2]);
    }
    printf("\n");
  }
}

void decParaHex (unsigned long long num, long* tamanho){
  long i = 0;
  char* seqHex = (char*) malloc(*tamanho * sizeof(char));

  if(seqHex != NULL){
    do{
      if(i == *tamanho){
        seqHex = realloc(seqHex, *tamanho * sizeof(char) * 2);
        *tamanho *= 2;
        if(seqHex == NULL)
          return;
      }
      seqHex[i] = num%16 + '0';
      num /= 16;
      i++;
    } while(num);

    bcd(seqHex, i-1);
  }
  return;
}


int main(void){
  unsigned long long int num;
  long tamanho = 8;

  printf("Digite seu numero em decimal: ");
  scanf("%llu", &num);

  decParaHex(num, &tamanho);
  return 0;
}
