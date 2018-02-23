#include <stdio.h>
#include <stdlib.h>

int *lerSeq(int tamanho){
	int *sequencia = malloc(tamanho * sizeof(int));
	if(sequencia != NULL){
			for(int i = 0; i < tamanho; i++)
				scanf("%d", sequencia+i);
	}
	return sequencia;
}

void imprimirSubseq (int *seq, int tamanho, int k){
	int i, j;
	printf("\n\nSubsequencias:\n");
	for(i = 0; i < tamanho - 1; i++){
		for(j =  0; j < k-1 && *(seq+i+j) < *(seq+i+j+1); j++){
				if(j == 0){
					printf("%d ", *(seq+i));
				}
				printf("%d ", *(seq + i + 1));
		}
		if(j > 0)
			printf("\n");
	}
}

int main(void){
	int k, M;	// k maior tamanho das subsequencias, M tamanho na sequencia

	printf("Tamanho M da sequencia a digitar: ");
	scanf("%d", &M);
	printf("Maior tamanho k das subsequencias: ");
	scanf("%d", &k);

	int *seq = lerSeq(M);
	imprimirSubseq(seq, M, k);
	return 0;
}
