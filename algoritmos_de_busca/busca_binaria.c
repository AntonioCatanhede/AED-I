// Implementacao do algoritmo de busca binaria
// recursivo e normal
#include <stdio.h>
#include <stdlib.h>

int recBinarySearch(int *arr, int left, int right, int elem){
  if(left > right)
    return -1;      // nao encontrou o elemento

  int mid = left + (right - left)/2;
  if(arr[mid] < elem)
    return recBinarySearch(arr, mid+1, right, elem);
  if(arr[mid] > elem)
    return recBinarySearch(arr, left, mid-1, elem);
  return mid;
}

int BinarySearch(int *arr, int size, int elem){
  int left = 0, right = size - 1, mid;
  while(left < right){
    mid = left + (right - left)/2;
    if(arr[mid] == elem) return mid;
    if(arr[mid] < elem) left = mid + 1;
    else right = mid - 1;
  }
  return -1;
}

int main(){
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int elem = 2;
  int res = recBinarySearch(arr, 0, sizeof(arr)/sizeof(arr[0])-1, elem);
  printf("Resultado da busca binaria recursiva. Posicao: %d, elemento: %d\n", res, arr[res]);

  elem = 9;
  res = BinarySearch(arr, sizeof(arr)/sizeof(arr[0]), elem);
  printf("Resultado da busca binaria normal. Posicao; %d, elemento: %d\n", res, arr[res]);
  return 0;
}
