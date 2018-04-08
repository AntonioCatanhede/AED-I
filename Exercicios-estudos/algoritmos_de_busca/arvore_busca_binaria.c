#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode treeNode;
struct treeNode{
  int value;
  treeNode *pLeft, *pRight;
};

treeNode *maxNode(treeNode *t){
  while(t->pRight)
    t = t->pRight;
  return t;
}

treeNode *minNode(treeNode *t){
  while(t->pLeft)
    t = t->pLeft;
  return t;
}
/* Insercao na ABB
* treeNode como argumento, que pode ser nulo
* nesse caso, eh criada a arvore e retornada nessa var pelo ponteiro
*/
treeNode *insertNode(treeNode *t, int value){
  if(!t){   // cria o nodo inicial na ABB
    treeNode *tmp = malloc(sizeof(treeNode));
    if(tmp){
      tmp->value = value;
      tmp->pRight = tmp->pLeft = NULL;
    }
    return tmp;
  }
  if(value < t->value)
    t->pLeft = insertNode(t->pLeft, value);
  else if(value > t->value)
    t->pRight = insertNode(t->pRight, value);
  else
    t->value = value;
  return t;
}

/* Funcao para remover um elemento duma ABB
* Como argumento, ha o proprio nodo a ser removido.
*/
treeNode* deleteNode(struct treeNode* root, int value)
{
    if (!root)
      return root;

    if (value < root->value)
      root->pLeft = deleteNode(root->pLeft, value);
    else if (value > root->value)
      root->pRight = deleteNode(root->pRight, value);
    else
    {
        if (!root->pLeft)
        {
            struct treeNode *tmp = root->pRight;
            free(root);
            return tmp;
        }
        else if (!root->pRight)
        {
            struct treeNode *tmp = root->pLeft;
            free(root);
            return tmp;
        }

        struct treeNode* tmp = minNode(root->pRight);
        root->value = tmp->value;
        root->pRight = deleteNode(root->pRight, tmp->value);
    }
    return root;
}
/*
treeNode *removeNode(treeNode *root, int value){

  treeNode *tmp;
  if(t->pLeft && t->pRight){
    // Caso dificil: se o nodo a remover possui dois filhos,
    // reduzir ao caso fácil: colocar nesse nodo seu sucesso (menor a direita)
    tmp = t->pRight;
    tmp = minNode(tmp);
    t->value = tmp->value;
    free(tmp);
  }
  else{
    // Caso facil: se o nodo a remover n tem zero ou um filho
    // => atualizar o link do pai com null ou f resp.
    if(!t->pLeft && !t->pRight){
      free(t);
      return;
    }
    if(t->pLeft)  tmp = t->pLeft;
    else          tmp = t->pRight;

    t->value = tmp->value;
    t->pLeft = tmp->pLeft;
    t->pRight = tmp->pRight;
    free(tmp);
  }
}*/
/* inOrder
* imprime a chave da raiz de uma subarvore entre a impressao dos valores
* em sua subarvore esquerda e a impressao dos valores em sua subarvore direita
*/
void inOrder(treeNode *t){
  if(!t) return;
  inOrder(t->pLeft);
  printf("%d ", t->value);
  inOrder(t->pRight);
}
/* preOrder
* Imprime a raiz antes dos valores das subarvores
*/
void preOrder(treeNode *t){
  if(!t) return;
  printf("%d ", t->value);
  preOrder(t->pLeft);
  preOrder(t->pRight);
}
/* postOrder
* imprime a raiz depois dos valores em suas subarvores
*/
void postOrder(treeNode *t){
  if(!t) return;
  postOrder(t->pLeft);
  postOrder(t->pRight);
  printf("%d ", t->value);
}

treeNode *searchTreeNode(treeNode *t, int value){
  if(!t) return NULL;
  if(value == t->value) return t;
  if(value < t->value) searchTreeNode(t->pLeft, value);
  else searchTreeNode(t->pRight, value);
}
/* testando o codigo...
/* https://www.cs.usfca.edu/~galles/visualization/BST.html
* site para ter uma boa visualizacao da ABB
*/
int main(){

  int value[11] = {15, 4, 20, 17, 19, 1, 8, 25, 12, 28, 2}, i;
  treeNode *t = NULL, *tmp;
  // Criacao da ABB
  for(i = 0;  i < 11; i++)
    t = insertNode(t, value[i]);

  printf("\ninOrder: "); inOrder(t);
  printf("\npreOrder: "); preOrder(t);
  printf("\npostOrder: ");  postOrder(t);

  printf("\nBusquemos o valor <%d> na ABB... ", value[9]);
  tmp = searchTreeNode(t, value[9]);
  printf("Resultado: <%d>\n", tmp->value);

  treeNode *min = minNode(t), *max = maxNode(t);
  printf("Calculo do max: %d e do min: %d\n", max->value, min->value);

  deleteNode(t, 28);
  printf("\n\nRemovemos o nodo com valor 28. Resultados: \n");
  printf("\ninOrder: "); inOrder(t);
  printf("\npreOrder: "); preOrder(t);
  printf("\npostOrder: ");  postOrder(t);
  min = minNode(t), max = maxNode(t);
  printf("Calculo do max: %d e do min: %d\n", max->value, min->value);
  return 0;
}
