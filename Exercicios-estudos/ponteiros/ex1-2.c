#include <stdio.h>
#include <stdlib.h>

// funcoes corrigidas da lista de exercicio
// comentado dentro da funcao eh a parte modificada. Comentarios retratam ex antes da modificacao

// Item a) 
// eh melhor usar uma variavel inteira do que um ponteiro como variavel auxiliar para guardar o valor de i
void trocaMin (int *i, int *j){
	if(i < j) return;
	int temp;	//int *temp
	temp = *i;	//*temp = *i;
	*i = *j;	
	*j = temp;	//*j = *temp
}

// Item b)
// mesmo caso do ex anterior
void main(){
	char *a = "trem", *b = "carro";
	if (*a < *b)	// if(*a < *b)
		printf("%s vem antes de %s no dicionario\n", a, b);
	else
		printf("%s vem depois de %s no dicionario\n", a, b);
}

// item c)
// devemos incrementar o ponteiro c para mostrar os elementos!
void xxx(char *v, int n, int k){
	char *c;
	for(c = v; c < v + n; c += k) //for(c = v; c < v + n; v += k)
		printf("%c", *c);
}
