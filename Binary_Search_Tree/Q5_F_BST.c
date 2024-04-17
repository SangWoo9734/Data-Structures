//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 3:
			printf("Input an integer that you want to delete from the Binary Search Tree: ");
			scanf("%d", &i);
			root = removeNodeFromTree(root, i); // You need to code this function
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root)
{
	Stack stack = { NULL };
	Stack *stack_pointer = &(stack);

	Stack saved_stack = { NULL };
	Stack *saved_stack_pointer = &(stack);


	push(stack_pointer, root);

	while(isEmpty(stack_pointer) == 0) {
		BSTNode * node = pop(stack_pointer);

		if (peek(saved_stack_pointer) == node) {
			pop(saved_stack_pointer);
			printf("%d ", node -> item);
		}
		else {
			push(saved_stack_pointer, node);

			push(stack_pointer, node);
			if (node -> right != NULL) { push(stack_pointer, node -> right); }
			if (node -> left != NULL) { push(stack_pointer, node -> left); }
		}
	}
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
BSTNode* removeNodeFromTree(BSTNode *root, int value)
{	
	BSTNode *root_pointer = root;
	
	// 노드가 NULL인 경우
	if (root == NULL) {
		return root;
	}

	// 노드 삭제
	// 깊이 체크
	// 작은 수 중 가장 큰 수( find while root -> left is NULL after root = root -> right )
	if (root -> item == value) {
		BSTNode * alter = root;
		
		BSTNode * left_pre_alter = root;
		BSTNode * right_pre_alter = root;
		BSTNode * left_alter = root;
		BSTNode * right_alter = root;

		int left_height = 0;
		int right_height = 0;


		// 오른쪽 ( 큰 수 탐색) - 큰 수 중에 가장 왼쪽에 있는 수
		if (alter -> right != NULL ) {
			right_alter = right_alter -> right;
				right_height += 1;
			while (right_alter -> left != NULL) {
				right_pre_alter = right_alter;
				right_alter = right_alter -> left;
				right_height += 1;
			}
		}
		// 왼쪽 ( 작은 수 탐색 ) - 작은 수 중에 가장 오른쪽에 있는 수
		if (alter -> left != NULL ) {
			left_alter = left_alter -> left;
				left_height += 1;
			while (left_alter -> right != NULL) {
				left_pre_alter = left_alter;
				left_alter = left_alter -> right;
				left_height += 1;
			}
		}

		// 오른쪽이 더 깊은 경우 : 현재 노드의 이전노드와 현재 노드의 오른쪽을 연결하고,
		// 현재 노드의 오른쪽, 왼쪽에 root 노드의 오른쪽. 왼쪽을 연결한다.
		if (right_height > left_height ) {
			right_pre_alter-> left = right_alter -> right;

			right_alter -> right = root_pointer -> right;
			right_alter -> left = root_pointer -> left;

			free(root_pointer);

			return right_alter;
		}
		// 왼쪽이 더 깊은 경우 : 현재 노드의 이전노드와 현재 노드의 왼쪽을 연결하고,
		// 현재 노드의 오른쪽, 왼쪽에 root 노드의 오른쪽. 왼쪽을 연결한다.
		else {
			left_pre_alter -> right = left_alter -> left;

			left_alter -> right = root_pointer -> right;
			left_alter -> left = root_pointer -> left;

			free(root_pointer);

			return left_alter;
		}
	} else {
			
	// 좌우 트리 탐색
		BSTNode * left = removeNodeFromTree(root -> left, value);
		BSTNode * right = removeNodeFromTree(root -> right, value);

		// 새로운 트리 결합
		root_pointer -> left = left;
		root_pointer -> right = right;

		return root_pointer;
	}
}
///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
