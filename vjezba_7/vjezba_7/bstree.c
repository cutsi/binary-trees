#include <stdio.h>
#include <malloc.h>
#include "bstree.h"
#include <ctype.h>
BSTree NewBSTree()
{
	// Novo prazno stablo
	return NULL;
}
Node* newNode(int data)
{
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->word = data;
	temp->left = temp->right = NULL;
	return temp;
}
void PrintByCriteria(BSTree bst) {
	if (bst == NULL) {
		return;
	}
	if (bst->word[0] == 'l')
	{
		printf("Criteria %s \n", bst->word);
	}
	PrintByCriteria(bst->left);
	PrintByCriteria(bst->right);

}

void PrintLeafs(BSTree bst) {
	if (bst == NULL) {
		return;
	}
	if (bst->left && bst->right) {
		printf("%s\n", bst->word);
	}
	PrintLeafs(bst->left);
	PrintLeafs(bst->right);
}

void DeleteLeafs(BSTree bst) {
	if (bst == NULL) {
		return;
	}
	if (!bst->left && !bst->right) {
		if (bst->word[0] == 'l') {
			free(bst);
			return;
		}
	}

	DeleteLeafs(bst->left);
	DeleteLeafs(bst->right);
	
	
}
char* LongestWord(BSTree bst) {
	if (bst == NULL) {
		return;
	}
	char* word = (bst)->word;
	char* lword = LongestWord((bst)->left);
	char* rword = LongestWord((bst)->right);
	if (strlen(lword) > strlen(word)) {
		word = lword;		
	}
	if (strlen(rword)  > strlen(word)) {
		word = rword;
	}
	return word;
}

void AddNode(BSTree *bst, char *word)
{

	if (*bst == NULL) {
		*bst = InsertNewNode(word);
		return;
	}
	else if (strcmp((*bst)->word, word) == 0)
		return;

	else if (strcmp((*bst)->word, word) > 0) {
		AddNode(&(*bst)->left, word);
	} 
	else
		AddNode(&(*bst)->right, word);

	// Rekurzivno se traži mjesto za novi èvor u stablu. Ako rijeè postoji u stablu, ne dodaje se.
	// bst parametar je dvostruki pokazivaè.
}
Node* InsertNewNode(char* word) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->word = strdup(word);
	newNode->right = NULL;
	newNode->left = NULL;
	return newNode;
}

int BSTHeight(BSTree bst)
{
	if (bst == NULL) {
		return 0;
	}
	else
		return 1 + max(BSTHeight(bst->left),BSTHeight(bst->right));
	// Rekurzivno se prolazi cijelo stablo da bi se pronašla najduža grana (visina stabla).

}
int max(int a, int b) {
	if (a >= b)
		return a;
	return b;
}

void PrintBSTree(BSTree bst)
{
	if (bst != NULL) {
		printf("%s\n", bst->word);

		PrintBSTree(bst->left);
		PrintBSTree(bst->right);
		
	}
	
	// Ispisuje rijeèi u stablu na ekran po abecednom redu.
	// In-order šetnja po stablu (lijevo dijete, èvor, desno dijete)

}

void SaveBSTree(BSTree bst, FILE *fd)
{
	// Snima rijeè po rijeè iz stabla u tekstualnu datoteku. Rijeèi su odvojene razmakom.
	// Pre-order šetnja po stablu (ttenutni èvor pa djeca)
	if (bst == NULL) {
		
		return;
	}	
	fputs(bst->word, fd);
	fputs(" ", fd);
	SaveBSTree(bst->left, fd);	
	//printf("%s\n", bst->word);
	SaveBSTree(bst->right, fd);
	
}

void DeleteBSTree(BSTree bst)
{
	// Briše stablo (string word i sam èvor) iz memorije.
	// Post-order šetnja po stablu (prvo djeca pa trenutni èvor)
	if (bst == NULL) {
		return;
	}
	
	DeleteBSTree(bst->right);
	DeleteBSTree(bst->left);
	//free(bst->word);
	free(bst);

}

BSTree LoadBSTree(FILE *fd)
{
	// Uèitava rijeè po rijeè iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rijeè duplicirati sa strdup().
	BSTree dict = NewBSTree();
	//int word_count = 0;
	char s[100];

	while (fscanf(fd, "%s", s) > 0)
	{
		AddNode(&dict, s);
		//word_count++;
	}
	//printf("%d", word_count);
	return dict;
}