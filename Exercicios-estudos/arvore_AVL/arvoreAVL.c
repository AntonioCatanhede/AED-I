#include <stdio.h>
#include <stdlib.h>

typedef struct avlTreeNode avlTreeNode;
struct avlTreeNode{
  int key;
  int height;
  // unsigned short balanceFactor;
  avlTreeNode *left, *right;
};

void updateHeight (avlTreeNode *n){
    if(!n) return;
    int hl = (n->left) ? n->left->height : -1;
    int hr = (n->right) ? n->right->height : -1;
    n->height = (hl > hr ? hl : hr) + 1;
}

const int leftheavy = -1, balanced = 0, rightheavy = 1;

int balanceFactor(avlTreeNode *n) {
	if (!n)
		return 0;
	int hl = (n->left)  ? n->left->height  : -1,
	    hr = (n->right) ? n->right->height : -1;
	return hl - hr;
}

int isAVL(avlTreeNode *treeRoot){
  if(!treeRoot) return 1;
  if(balanceFactor(treeRoot) < 2)
    if(isAVL(treeRoot->left) && isAVL(treeRoot->right))
      return 1;
  return 0;
}

/* Rotacao simples a direita
*  o desbalanceamento estah a esquerda-esquerda
*  a subarvore esquerda de p estah mais pesada
*/
void caseLLrotateRight(avlTreeNode **pRoot) {
	avlTreeNode *p = *pRoot, *leftChild = p->left;

	p->left = leftChild->right;
	leftChild->right = p;
  *pRoot = leftChild;

	updateHeight(p); // a altura do filho esquerdo se mantem o mesmo
}

/* Rotacao simples a esquerda
*  o desbalanceamento estah a direita-direita
*  a subarvore direita de p estah mais pesada
*/
void caseRRrotateLeft(avlTreeNode **pRoot) {
	avlTreeNode *p = *pRoot, *rightChild = p->right;

  p->right = rightChild->left;
	rightChild->left = p;
  *pRoot = rightChild;

	updateHeight(p);   // a altura do filho direito se mantem o mesmo
}

/* Rotacao dupla a direita
* uma rotacao a esquerda e, depois, uma a direita
* a subarvore esquerda estah mais pesada
*/
void caseLRrotateLeftRight(avlTreeNode **pRoot) {
	avlTreeNode *p = *pRoot, *leftChild = p->left, *rightgrandChild = leftChild->right;
	// Rotacao a esquerda (leftChild)
	leftChild->right = rightgrandChild->left;
	rightgrandChild->left = leftChild;

	// Rotacao a direita (p)
	p->left = rightgrandChild->right;
	rightgrandChild->right = p;

	// atualiza todas as alturas
	updateHeight(p);
	updateHeight(leftChild);
	updateHeight(rightgrandChild);

	*pRoot = rightgrandChild;
}

/* Rotacao dupla a esquerda
*  uma rotacao a direita e, depois, uma a esquerda
*  subarvore direita estah mais pesada
*/
void caseRLrotateRightLeft(avlTreeNode **pRoot) {
	avlTreeNode *p = *pRoot, *rightChild = p->right, *leftgrandChild = rightChild->left;

	// rotacao a direita (rightChild)
	rightChild->left = leftgrandChild->right;
	leftgrandChild->right = rightChild;

	// rotacao a esquerda (p)
	p->right = leftgrandChild->left;
	leftgrandChild->left = p;

	// Atualiza todas a alturas
	updateHeight(p);
	updateHeight(rightChild);
	updateHeight(leftgrandChild);

	*pRoot = leftgrandChild;
}

void avlInsert(avlTreeNode **treeRoot,	int key) {
	if (*treeRoot == NULL) {
    // atualiza a raiz para apontar a um novo nodo
		avlTreeNode *newNode = malloc(sizeof(avlTreeNode));
		*treeRoot = newNode;

    if (!newNode)
      return;

		newNode->key = key;
		newNode->left = newNode->right = NULL;
		newNode->height = 0;
		return;
	}

	if (key == (*treeRoot)-> key)
    return;

	avlTreeNode *tree = *treeRoot;

	if (key < tree->key) { // move-se recursavimanete para a esquerda
		avlInsert(&tree->left, key);

		if (balanceFactor(tree) == 2) {
      // verifica se a insercao deixou lado esquerdo mais pesado
			if (key < tree->left->key)
				caseLLrotateRight(&tree);
			else
        caseLRrotateLeftRight(&tree);
		}
		else updateHeight(tree);
	}
	else { //  move-se recursivamente para a direita
		avlInsert(&tree->right, key);

		if (balanceFactor(tree) == -2) {
      // verifica se a insercao deixou lado direito mais pesado
			if (key > tree->right->key)
				caseRRrotateLeft(&tree);
			else
        caseRLrotateRightLeft(&tree);
		}
		else updateHeight(tree);
	}

	*treeRoot = tree;
}

void avlRemove(avlTreeNode *treeRoot, int key){
  // implementar...
}


void printInOrder(avlTreeNode *root)
{
	if (root){
	printInOrder(root->left);
	printf("%d ", root->key);
	printInOrder(root->right);
	}
}


int main() {
	avlTreeNode *root = NULL;

	avlInsert(&root, 100);
	avlInsert(&root, 80);
	avlInsert(&root, 60);
	avlInsert(&root, 40);
	avlInsert(&root, 20);
	avlInsert(&root, 70);
	avlInsert(&root, 30);
	avlInsert(&root, 50);
	avlInsert(&root, 35);
	avlInsert(&root, 45);
  avlInsert(&root, 55);
	avlInsert(&root, 75);
  avlInsert(&root, 65);
	avlInsert(&root, 73);

	printTree(root);

  if(isAVL(root))
    printf("Eh AVL\n\n");
  else
    printf("Nao eh AVL\n\n");

	printf("\nheight: %d \n\n\n", root->height);

	printInOrder(root);
  printf("\n\n");
	return 0;
}




/******************************************
		AVL insertion using the balanceFactor
 ******************************************/

/*
void updateLeftTree(avlTreeNode **pRoot, int *reviseBalanceFactor) {
	avlTreeNode *leftChild = (*pRoot)->left;
	int balanceFactorChild = balanceFactor(leftChild);

	if (balanceFactorChild == leftheavy) {
		// left subtree is also heavy
		caseLLrotateRight(pRoot); // need a single rotation
		*reviseBalanceFactor = 0; // false;
	}
	// is right subtree heavy?
	else if (balanceFactorChild == rightheavy) {
		// make a double rotation
		caseLRrotateLeftRight(pRoot);
		// root is now balanced
		*reviseBalanceFactor = 0; // false;
	}
}

void updateRightTree(avlTreeNode **pRoot, int *reviseBalanceFactor) {
	avlTreeNode *rightChild;
	rightChild = (*pRoot)->right; // left subtree is also heavy
	int balanceFactorChild = balanceFactor(rightChild);

	if (balanceFactorChild == rightheavy) {
		caseRRrotateLeft(pRoot);  // need a single rotation
		*reviseBalanceFactor = 0; // false;
	}
	// is right subtree heavy?
	else if (balanceFactorChild == leftheavy) {
		// make a double rotation
		caseRLrotateRightLeft(pRoot);
		// root is now balanced
		*reviseBalanceFactor = 0; // false;
	}
}

void avlInsert_BF(avlTreeNode **treeRoot,	int key,
								int *reviseBalanceFactor) {
	if (*treeRoot == NULL) {
		// update the root to point at newNode
		avlTreeNode *newNode = malloc(sizeof(avlTreeNode));
		newNode->key = key;
		newNode->left = newNode->right = NULL;
		newNode->height = 0;
		*treeRoot = newNode;

		// balanceFactor must be checked!
		*reviseBalanceFactor = 1; // true;
		return;
	}

	if (key == (*treeRoot)->key){
		*reviseBalanceFactor = 0; // false;
		return;
	}

	avlTreeNode *tree = *treeRoot;
	// indicates a change in node's balanceFactor
	int rebalanceCurrNode, balanceFactorOld = balanceFactor(tree);

	if (key < tree->key) { // recursively move to the left
		avlInsert_BF(&tree->left, key, &rebalanceCurrNode);

		// check if balanceFactor must be updated.
		if (rebalanceCurrNode) {

			// case 3: went left from node that is already heavy
			// on the left. violates AVL condition; rotate
			if (balanceFactorOld == leftheavy)
				updateLeftTree(treeRoot, reviseBalanceFactor);

			// case 1: inserting in the left on previously balanced
			// node that now will be heavy on left
			else if (balanceFactorOld == balanced) {
				*reviseBalanceFactor = 1; // true;
				updateHeight(*treeRoot); // update the height
			}

			// case 2: scanning left from node heavy on the
			// right. The node will be balanced, the height is the same
			else *reviseBalanceFactor = 0; // false;
		}

		// no balancing occurs; do not ask previous nodes
		else *reviseBalanceFactor = 0; // false;
	}

	// otherwise recursively move right
	else {
		avlInsert_BF(&tree->right, key, &rebalanceCurrNode);
		// check if balanceFactor must be updated.
		if (rebalanceCurrNode) {

			// case 2: node becomes balanced
			if (balanceFactorOld == leftheavy) {
				// scanning right subtree. node heavy on left.
				// the node will become balanced
				// the height remains the same
				*reviseBalanceFactor = 0; // false;
			}
			// case 1: node is initially balanced
			else if (balanceFactorOld == balanced) {
				// node is balanced; will become heavy on right
				// tree->balanceFactor = rightheavy;
				*reviseBalanceFactor = 1; // true;

				// update the height
				updateHeight(*treeRoot);
			} else
				// case 3: need to update node
				// scanning right from a node already heavy on
				// the right. this violates the AVL condition
				// and rotations are needed.
				updateRightTree(treeRoot, reviseBalanceFactor);

		} else
			*reviseBalanceFactor = 0; // false;
	}
	}


}

int main(){

  return 0;
}
*/
