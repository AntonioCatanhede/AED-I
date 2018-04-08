#include <stdio.h>
#include <stdlib.h>

// Quais os valores de x, y, z, p e pp ao final da funcao abaixo?
// Indagacoes: 
// z nao foi inicializado. Seu valor nao deveria ser aleatorio?!
// quando p eh decrementado, ele nao aponta para x? Ora, y eh declarado apos x
	
void f(){
	int x, y, z, *p, **pp;
	y = 0; 
	p = &y;		// p aponta para o y
	pp = &p;	// pp aponta para p
	x = *p;		// y = 0 => x = 0
	x += 4;		// x = 4
	(*p)++;		// y++ => y = 1
	--x;		// x-- => x = 3
	(*p) += x;	// y = y + x => y = 4
	p--;		// p aponta para algum outro espaco da memoria
	(*p) += x;	// modifica esse espaco
	p++;		// p aponta para y novamente
	(**pp) += 3*x;	// pp aponta para p que aponta para y. Assim: **pp = 4 + 3*3 = 13
			// assim, temos **pp = 13 => *p = 13 => y = 13, x = 4  

	printf("Valor de x: %d, y: %d, z: %d, p: %d e pp: %d", x, y, z, *p, **pp);
	// printf confirmado!
}

int main(void){
	f();

	return 0;
}
