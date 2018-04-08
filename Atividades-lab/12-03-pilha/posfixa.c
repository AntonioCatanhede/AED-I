#include <stdio.h>
#include <stdlib.h>

typedef struct linkedNode linkedNode;
typedef struct Stack Stack;

struct linkedNode{
  double data;
  linkedNode *next;
};

struct Stack{
  linkedNode *top;
};

Stack *createStack(){
  Stack *tmp = malloc(sizeof(Stack));
  if(!tmp) return NULL;

  tmp->top = malloc(sizeof(linkedNode));
  if(!tmp->top){
    free(tmp);
    return NULL;
  }
  return tmp;
}

void push(Stack *stack, double element){
  linkedNode *new = malloc(sizeof(linkedNode));
  if(!new) return;

  new->data = element;
  new->next = stack->top;
  stack->top = new;
}

// retorna 1 se pilha nao estiver vazia
int pop(Stack *stack, double *element){
  if(!stack->top->next) return 0; // pilha estava vazia

  *element = stack->top->data;
  linkedNode *tmp = stack->top;
  stack->top = stack->top->next;
  free(tmp);

  return 1; // pilha  estava cheia
}

int isEmpty (Stack *stack){
  return !stack->top->next; // retorna 1 se pilha estiver vazia
}

int main(){
  int i, error = 0;
  double v1, v2, v3;
  char expression[1000];

  scanf("%s", expression);
  Stack *myStack = createStack();
  if(myStack->top == NULL)
    printf("cabo");
  for(i = 0; expression[i]!='\0' && !error; i++){
    if(expression[i]>='0' && expression[i]<='9'){
      push(myStack, (double)(expression[i]-'0'));
    }
    else if(expression[i]=='h'){
      if(pop(myStack, &v1)){
        push(myStack, v1*3);
      }
      else
        error = 1;
    }
    else if(expression[i]=='+'){
      if(pop(myStack, &v2) && pop(myStack, &v1))
        push(myStack, v1+v2);
      else
        error = 1;
    }
    else if(expression[i]=='-'){
      if(pop(myStack, &v2) && pop(myStack, &v1))
        push(myStack, v1-v2);
      else
        error = 1;
    }
    else if(expression[i]=='f'){
      if(pop(myStack, &v3) && pop(myStack, &v2) && pop(myStack, &v1))
        push(myStack, (v1*v1) - (v2/2) + v3);
      else
        error = 1;
    }
    else if(expression[i]=='g'){
      if(pop(myStack, &v3) && pop(myStack, &v2) && pop(myStack, &v1))
        push(myStack, (v1*v2) + v3);
      else
        error = 1;
    }
    else
      error = 1;
  }

  if(pop(myStack, &v1) && isEmpty(myStack) && !error)
    printf("%.2lf\n", v1);
  else
    printf("ERRO");
}
