#include <stdio.h>
#include <stdlib.h>

typedef struct node {  //구조체
	int key;  //데이터 변수
	struct node *left; 
	struct node *right;
} Node;

//함수
int initializeBST(Node** h);

void inorderTraversal(Node* ptr);	
void preorderTraversal(Node* ptr);  
void postorderTraversal(Node* ptr);	  
int insert(Node* head, int key); 
int deleteLeafNode(Node* head, int key);
Node* searchRecursive(Node* ptr, int key);  
Node* searchIterative(Node* head, int key);  
int freeBST(Node* head);



int main()
{
	char command;
	int key;
	Node* head = NULL;  //헤드 초기화
	Node* ptr = NULL;

    printf("김민서 2022040010");	

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //명령 문자 입력

		switch(command) {  //케이스에 따른 함수 실행
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {  //BST초기화

	if(*h != NULL)  //트리가 NULL이 아니면 메모히 할당 해제
		freeBST(*h);

	*h = (Node*)malloc(sizeof(Node));  //헤드에 메모히 할당
	(*h)->left = NULL;	
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)  //오름차순 순서대로 
{
	if(ptr) {
		inorderTraversal(ptr->left);  //재귀 왼쪽 출력
		printf(" [%d] ", ptr->key);  //최상위 노드 출력
		inorderTraversal(ptr->right);  //재귀 오른쪽 출력
	}
}

void preorderTraversal(Node* ptr)  //최상위노드부터 
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)  //최하위노드부터
{
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)  //노드 삽입
{
	Node* newNode = (Node*)malloc(sizeof(Node));  //메모리 할당
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left;  

	Node* parentNode = NULL;
	while(ptr != NULL) {

		if(ptr->key == key) return 1;

		parentNode = ptr;  //부모노드 계속 추적

		if(ptr->key < key)  //비교해서 크면 오른쪽 작으면 왼쪽
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)  //하위 노드 삭제
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* ptr = head->left;


	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				if(parentNode == head)
					head->left = NULL;

				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);  //left노드가 아니면 삭제 불가
			}
			return 1;
		}

		parentNode = ptr;

		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)  //Recursive탐색
{
	if(ptr == NULL)
		return NULL;

	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	return ptr;

}
Node* searchIterative(Node* head, int key)  //Iterative탐색
{

	Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr;

		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}