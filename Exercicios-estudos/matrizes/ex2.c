#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char nome[30];
  long telefone;
  char email[30];
}Contato;

Contato agenda[50];
int tam = 0;

void buscarNome(char* nome){
  int cmp = 1, i;
  for(i = 0; i < tam && cmp != 0 ; i++){
    cmp = strcmp(nome, agenda[i].nome);
  }
  if(cmp == 0){
    printf("Nome: %s\nTelefone: %ld\nEmail: %s\n\n", agenda[i-1].nome, agenda[i-1].telefone, agenda[i-1].email);
  }
  else{
    printf("Nao ha nenhum contato com esse nome :( \n\n");
  }
}

void buscarTelefone(long telefone){
  int i = 0;
  for(i = 0; i < tam && telefone != agenda[i].telefone ; i++);
  if(telefone == agenda[i].telefone){
    printf("Nome: %s\nTelefone: %ld\nEmail: %s\n\n", agenda[i].nome, agenda[i].telefone, agenda[i].email);
  } else{
    printf("Nao ha nenhum contato com esse nuero de telefone :(\n\n");
  }
}

void mostrarAgenda(){
  int i;
  for(i = 0; i < tam; i++){
    printf("Nome: %s\nTelefone: %ld\nEmail: %s\n\n", agenda[i].nome, agenda[i].telefone, agenda[i].email);
  }
}

int main(void){
  int opcao = 1;
  char buscastr[30];
  long buscatel;

  printf("Agenda de Contatos");
  while(opcao){
    printf("O que deseja fazer?\n");
    printf("1- Inserir um contato no final da agenda\n");
    printf("2- Buscar dados pelo Nome\n");
    printf("3- Buscar dados pelo Telefone\n");
    printf("4- Mostrar agenda\n");
    printf("5- Sair\n\n");
    scanf("%d", &opcao);

    switch(opcao){
      case 1:
        printf("Nome:");
        scanf("%s", agenda[tam].nome);
        printf("\nTelefone:");
        scanf("%ld", &agenda[tam].telefone);
        printf("\nEmail:");
        scanf("%s", agenda[tam].email);
        tam++;
        break;

      case 2:
        printf("Buscar por qual nome: ");
        scanf("%s", buscastr);
        buscarNome(buscastr);
        break;

      case 3:
        printf("Buscar por qual telefone: ");
        scanf("%ld", &buscatel);
        buscarTelefone(buscatel);
        break;

      case 4:
        mostrarAgenda();
        break;

      case 5:
        opcao = 0;
        break;
    }
  }
  return 0;
}
