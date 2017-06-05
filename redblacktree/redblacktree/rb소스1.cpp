#include<stdio.h>
#include<malloc.h>
#define BLACK 1;
#define RED 2;

typedef struct RBNode *RBNodePtr;
struct RBNode{
	int val, colour;
	RBNodePtr left, right, parent;
}rbnode;
typedef struct RBRoot *RBRootPtr;
struct RBRoot {
	RBNodePtr root;
	RBNodePtr nil;
}rbroot;

RBNodePtr node_alloc(int newval);
RBRootPtr rbroot_alloc();
RBRootPtr make_nil(RBRootPtr rbroot);
void rbroot_insert(RBRootPtr self, RBNodePtr tree, RBNodePtr nil, RBNodePtr n);
void rbnode_insert(RBRootPtr self, RBNodePtr tree, RBNodePtr nil, RBNodePtr n);
RBNodePtr tree_search(RBRootPtr self, RBNodePtr tree, int newval);
RBNodePtr tree_minimum(RBRootPtr self, RBNodePtr tree);
void transplant(RBRootPtr self, RBNodePtr tree, RBNodePtr n);
void rbnode_delete(RBRootPtr self, RBNodePtr tree, RBNodePtr n);
void leftrotation(RBRootPtr self, RBNodePtr tree);
void rightrotation(RBRootPtr self, RBNodePtr tree);

RBNodePtr node_alloc(int newval) {
	RBNodePtr tree = (RBNodePtr)malloc(sizeof(struct rbnode));
	tree->val = newval;
	tree->left = NULL;
	tree->right = NULL;
	tree->parent = NULL;
	return tree;
}
RBRootPtr rbroot_alloc() {
	RBRootPtr root = (RBRootPtr)malloc(sizeof(struct rbroot));
	root->root = NULL;
	return root;
}
RBRootPtr make_nil(RBRootPtr rbroot) {
	rbroot->nil = (RBNodePtr)malloc(sizeof(rbnode));
	rbroot->nil->val = NULL;
	rbroot->nil->left = NULL;
	rbroot->nil->right = NULL;
	rbroot->nil->colour = BLACK;
	rbroot->root = rbroot->nil;
	return rbroot;
}

void rbroot_insert(RBRootPtr self, RBNodePtr tree, RBNodePtr nil, RBNodePtr n) {
	if (tree == nil) {//트리가 비어있는 경우 
		self->root = n;
		n->parent = nil;
	}
	else if (n->val < tree->val) {
		n->parent = tree;
		if (tree->left = nil) {
			tree->left = n;
			n->parent = tree;
		}
		else
			rbroot_insert(self, tree->left, nil, n);
	}
	else {
		n->parent = tree;
		if (tree->right = nil) {
			tree->right = n;
			n->parent = tree;
		}
		else
			rbroot_insert(self, tree->right, nil, n);
	}
	n->left = nil;
	n->right = nil;
}
void rbnode_insert(RBRootPtr self, RBNodePtr tree, RBNodePtr nil, RBNodePtr n) {
	rbroot_insert(self, tree, nil, n);
	n->colour = RED;
	RBNodePtr temp;//temp로 노드 만듬
	while ((n != tree) && n->parent->colour == RED) {
		if (n->parent == n->parent->parent->left) {
			temp = n->parent->parent->right;
			if (temp->colour == RED) {
				n->parent->colour = BLACK;
				temp->colour = BLACK;
				n->parent->parent->colour = RED;
				n = n->parent->parent;
			}
			else {
				if (n == n->parent->right) {
					n = n->parent;
					leftrotation(self, n);
				}
				n->parent->colour = BLACK;
				n->parent->parent->colour = RED;
				rightrotation(self, n->parent->parent);
			}
		}
		else {
			temp = n->parent->parent->left;
			if (temp->colour == RED) {
				n->parent->colour = BLACK;
				temp->colour = BLACK;
				n->parent->parent->colour = RED;
				n = n->parent->parent;
			}
			else {
				if (n == n->parent->left) {
					n = n->parent;
					rightrotation(self, n);
				}
				n->parent->colour = BLACK;
				n->parent->parent->colour = RED;
				leftrotation(self, n->parent->parent);
			}
		}
	}
	self->root->colour = BLACK;
}

RBNodePtr tree_search(RBRootPtr self, RBNodePtr tree, int newval) {
	if (tree == NULL || newval == tree->val)
		return tree;
	if (newval < tree->val)
		return tree_search(self, tree->left, newval);
	else
		return tree_search(self, tree->right, newval);
}
RBNodePtr tree_minimum(RBRootPtr self, RBNodePtr tree) {
	while (tree->left != NULL) {
		tree = tree->left;
	}
	return tree;
}

void transplant(RBRootPtr self, RBNodePtr tree, RBNodePtr n) {
	if (tree->parent == NULL)
		self->root = n;
	else if (tree == tree->parent->left)
		tree->parent->left = n;
	else
		tree->parent->right = n;
	if (n != NULL)
		n->parent = tree->parent;

}
void rbnode_delete(RBRootPtr self, RBNodePtr tree, RBNodePtr n);
void leftrotation(RBRootPtr self, RBNodePtr tree) {
	RBNodePtr y = tree->right;
	tree->right = y->left;
	if (y->left != self->nil)
		y->left->parent = tree;
	y->parent = tree->parent;
	if (tree->parent == self->nil)
		self->root = y;
	else if (tree == tree->parent->left)
		tree->parent->right = y;
	else
		tree->parent->right = y;
	y->left = tree;
	tree->parent = y;
}
void rightrotation(RBRootPtr self, RBNodePtr tree) {
	RBNodePtr y = tree->left;
	tree->left = y->right;
	if (y->right != self->nil)
		y->right->parent = tree;
	y->parent = tree->parent;
	if (tree->parent == self->nil)
		self->root = y;
	else if (tree == tree->parent->right)
		tree->parent->right = y;
	else
		tree->parent->left = y;
	y->right = tree;
	tree->parent = y;
}
void print(RBRootPtr self, RBNodePtr tree, int level) {
	if (tree->right != self->nil)
		print(self, tree->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("         ");
	printf("%d[%d]\n", tree->val, tree->colour);
	if (tree->left != self->nil)
		print(self, tree->left, level + 1);
}
void inorder(RBRootPtr self, RBNodePtr tree) {
	if (tree == self->nil)
		return;
	else{
		inorder(self, tree->left);
		printf("%d[%d]->", tree->val, tree->colour);
		inorder(self, tree->right);
	}
}

void main() {
	FILE *fp;
	int data;
	int *arr = NULL;
	int size = 0;

	fp = fopen("C:\\my0531\\test.txt", "r");
	while (fscanf(fp, "%d", &data) != EOF) {//
		printf("%d\n", data);//파일에있는걸받아오고
		arr = (int*)realloc(arr, sizeof(int)*(size + 1));
		arr[size] = data;
		size++;//배열에 하나씩 넣어줌
	}
	fclose(fp);
	for (int i = 0; i < size; i++) {
		printf("[%d]\n", arr[i]);//배열에 하나씩 제대로 들어갔는지 확인
	}
	RBRootPtr root = rbroot_alloc();
	make_nil(root);
	for (int i = 0; i < size; i++) {
		rbnode_insert(root, root->root, root->nil, node_alloc(arr[i]));
	}
	print(root,root->root, 0);
	inorder(root, root->root);



}