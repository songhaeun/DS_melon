#include<stdio.h>
#include<malloc.h>
#define BLACK 0
#define RED 1
//BST지우고 교재있는거대로 써보기
//BST를 없애버리고 RBNode *root=NULL로 루트만들기
//typedef struct RBNode* RBNodePtr;
typedef struct RBNode *RBNodePtr;
struct RBNode{
	int val, color;
	RBNodePtr left, right, parent;
};
RBNodePtr rbnode_alloc(int newval) {
RBNodePtr self = (RBNodePtr)malloc(sizeof(struct RBNode));
	self->val = newval;
	self->color = BLACK;
	self->left = NULL;
	self->right = NULL;
	self->parent = NULL;
	return self;
}

typedef struct RBRoot* RBRootPtr;
struct RBRoot {
	RBNodePtr root;
};

RBRootPtr rbroot_alloc() {
	RBRootPtr self = (RBRootPtr)malloc(sizeof(struct RBRoot));
	self->root = NULL;
	return self;
}


void insertRBNode(RBRootPtr tree, RBNodePtr root, RBNodePtr newval);//데이터 삽입
void leftrotation(RBNodePtr root, RBNodePtr newval);
void rightrotation(RBNodePtr root, RBNodePtr newval);
void fixup(RBNodePtr y, RBNodePtr root, RBNodePtr newval);
void print(RBNodePtr root, int level);//출력
//void inorder(RBNodePtr root);
int main(void) {
	//RBNodePtr root = NULL;
	RBRootPtr rbr = rbroot_alloc();
	printf("11");
	insertRBNode(rbr, rbr->root, rbnode_alloc(10));//(root,(10))
	insertRBNode(rbr, rbr->root, rbnode_alloc(20));
	insertRBNode(rbr, rbr->root, rbnode_alloc(30));
	print(rbr->root, 0);
	//inorder(root);
}
void insertRBNode(RBRootPtr tree, RBNodePtr root, RBNodePtr newval) {
	RBNodePtr y = NULL;
	RBNodePtr x = tree->root;
	while (x != NULL) {
		y = x;
		if (newval->val < x->val)
			x = x->left;
		else
			x = x->right;
	}
	newval->parent = y;
	if (y == NULL)
		tree->root = newval;
	else if (newval->val < y->val)
		y->left = newval;
	else
		y->right = newval;
	newval->left = NULL;
	newval->right = NULL;
	newval->color = RED;
	fixup(y,tree->root, newval);
}
void fixup(RBNodePtr y, RBRootPtr tree, RBNodePtr newval) {//RBNodePtr root
	while (newval->parent->color == RED) {
		if (newval->parent == newval->parent->parent->left) {
			y = newval->parent->parent->right;
			if (y->color == RED) {
				newval->parent->color = BLACK;
				y->color = BLACK;
				newval->parent->parent->color = RED;
				newval = newval->parent->parent;
			}
			else if (newval == newval->parent->right) {
				newval = newval->parent;
				leftrotation(tree->root, newval);
			}
			else {
				newval->parent->color = BLACK;
				newval->parent->parent->color = RED;
				rightrotation(tree->root, newval->parent->parent);
			}
		}
		else {
			y = newval->parent->parent->left;
			if (y->color == RED) {
				newval->parent->color = BLACK;
				y->color = BLACK;
				newval->parent->parent->color = RED;
				newval = newval->parent->parent;			
			}
			else if (newval == newval->parent->left) {
				newval = newval->parent;
				rightrotation(tree->root, newval);
			}
			else {
				newval->parent->color = BLACK;
				newval->parent->parent->color = RED;
				leftrotation(tree->root, newval->parent->parent);
			}
		}
	}
	tree->root->color = BLACK;
}
void leftrotation(RBNodePtr root, RBNodePtr newval) {//RBRootPtr tree
	RBNodePtr y = newval->right;
	newval->right = y->left;
	if (y->left != NULL)
		y->left->parent = newval;
	y->parent = newval->parent;
	if (newval->parent == NULL)
		root = y;
	else if (newval == newval->parent->left)
		newval->parent->left = y;
	else
		newval->parent->right = y;
	y->left = newval;
	newval->parent = y;
}
void rightrotation(RBNodePtr root, RBNodePtr newval) {//RBRootPtr tree
	RBNodePtr y = newval->left;
	newval->left = y->right;
	if (y->right != NULL)
		y->right->parent = newval;
	y->parent = newval->parent;
	if (newval->parent == NULL)
		root = y;
	else if (newval == newval->parent->right)
		newval->parent->right = y;
	else
		newval->parent->left = y;
	y->right = newval;
	newval->parent = y;
}
void print(RBNodePtr root, int level) {
	if (root->right != NULL)
		print(root->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("    ");
	printf("%d[%d]\n", root->val, root->color);
	if (root->left != NULL)
		print(root->left, level + 1);
}


/*#include <stdio.h>
#include <malloc.h>
struct TreeNode {
	int key;
	TreeNode *LNode;
	TreeNode *RNode;
};
struct Tree {
	TreeNode *Root;//이런식으로 루트는 줘야하는거 같음! 책바꾼거 루트주기
};*/

 


/*void main() {
	printf("aa");
	BSTPtr bst = bst_alloc();
	printf("bb");
	rb_insert(bst, bst->root, rbnode_alloc(11));
	rb_insert(bst, bst->root, rbnode_alloc(2));
	rb_insert(bst, bst->root, rbnode_alloc(1));
	rb_insert(bst, bst->root, rbnode_alloc(7));
	rb_insert(bst, bst->root, rbnode_alloc(5));
	rb_insert(bst, bst->root, rbnode_alloc(4));
	rb_insert(bst, bst->root, rbnode_alloc(14));
	rb_insert(bst, bst->root, rbnode_alloc(8));
	rb_insert(bst, bst->root, rbnode_alloc(15));
	printf("cc");
	rb_print(bst, bst->root, 0);
	printf("\n");
	rb_inorder(bst, bst->root);
	printf("\n");
	printf("\n[0]-BLACK [1]-RED\n");
	printf("\n");
}
*/


































































/*typedef struct BST* BSTPtr;
struct BST {
	RBNodePtr root;
};

BSTPtr bst_alloc() {
	BSTPtr self = (BSTPtr)malloc(sizeof(struct BST));
	self->root = NULL;
	return self;
}*/

/*void rb_insert_fixup(/*BSTPtr self,*//* RBNodePtr tree, RBNodePtr n);*/
/*void rb_insert(BSTPtr self, RBNodePtr tree, RBNodePtr n) {
	/*RBNodePtr y = NULL;
	RBNodePtr x = self->root;
	while (x != NULL) {
		y = x;
		if (n->val < x->val)
			x = x->left;
		else
			x = x->right;
	}
	n->parent = y;
	if (y == NULL)
		self->root = n;
	else if (n->val < y->val)
		y->left = n;
	else
		y->right = n;
	n->left = NULL;
	n->right = NULL;
	n->color = RED;
	rb_insert_fixup(tree, n);*/
	/*RBNodePtr tmp = self->root;
	while (tmp != NULL) {
		self->root = tmp;
		if (n->val < tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	n->parent = self->root;
	if (self->root == NULL)
		self->root = n;
	else if (n->val < tree->val)
		tree->left = n;
	else
		tree->right = n;
	n->left = NULL;
	n->right = NULL;
	n->color = RED;
	rb_insert_fixup(tree, n);
	/*if (self->root == NULL)
		self->root = n;
	else if (n->val < tree->val) {
		if (tree->left == NULL)
		{
			tree->left = n;
			//tree->left->color = RED;//여기서주면 지나치게 단순해지니까 픽스업/로테이트
		}
		else
			rb_insert(self, tree->left, n);
	}
	else {
		if (tree->right == NULL)
		{
			tree->right = n;
			//tree->right->color = RED;
		}
		else
			rb_insert(self,tree->right, n);
	}
	//rb_insert_fixup(/*self,*///tree, n);
	//--여기서오류/위에색지정한거 
	//지우면 오류 안나는데 색은안들어감//로테이션에서 오류
	//픽스업에서 오류, 로테이션 에서 셀프지우고 pt_지정하는거 하고나서 안먹으 
//}
/*void rb_leftrotation(RBNodePtr tree, RBNodePtr n) {
	RBNodePtr pt_right = n->right;
	n->right = pt_right->left;
	if (pt_right->left != NULL)//n->right != NULL
		pt_right->left->parent = n;//n->right->parent = n;
	pt_right->parent = n->parent;
	if (n->parent == NULL)
		tree=pt_right;
	else if (n == n->parent->left)
		n->parent->left = pt_right;
	else
		n->parent->right = pt_right;
	pt_right->left = n;
	n->parent = pt_right;
}
void rb_rightrotation(RBNodePtr tree, RBNodePtr n) {
	RBNodePtr pt_left = n->left;
	n->left = pt_left->right;
	if (pt_left->right != NULL)//n->left != NULL
		pt_left->right->parent = n;//n->left->parent = n;
	pt_left->parent = n->parent;
	if (n->parent == NULL)
		tree=pt_left;
	else if (n == n->parent->right)
		n->parent->right = pt_left;
	else
		n->parent->left = pt_left;
	pt_left->right = n;
	n->parent = pt_left;
}
void rb_insert_fixup(/*BSTPtr self,*///RBNodePtr tree, RBNodePtr n) {
	/*
	RBNodePtr y = NULL;
	while (n->parent->color == RED) {
		if (n->parent == n->parent->parent->left) {
			y = n->parent->parent->right;
			if (y->color == RED) {
				n->parent->color = BLACK;
				y->color = BLACK;
				n->parent->parent->color = RED;
				n = n->parent->parent;
			}
			else if (n == n->parent->right) {
				n = n->parent;
				rb_leftrotation(tree,n);
			}else{
				n->parent->color = BLACK;
				n->parent->parent->color = RED;
				rb_rightrotation(tree, n->parent->parent);
			}

		}
		else {
			y = n->parent->parent->right;
			if (y->color == RED) {
				n->parent->color = BLACK;
				y->color = BLACK;
				n->parent->parent->color = RED;
				n = n->parent->parent;
			}
			else if (n == n->parent->left) {
				n = n->parent;
				rb_rightrotation(tree, n);
			}
			else {
				n->parent->color = BLACK;
				n->parent->parent->color = RED;
				rb_leftrotation(tree, n->parent->parent);
			}
		}
	}
	tree->color = BLACK;*/
	/*printf("11");
	RBNodePtr rbparent = NULL;
	RBNodePtr rbgparent = NULL;
	printf("111");
	while ((n != tree) && (n->color != BLACK) && (n->parent->color == RED)) {
		rbparent = n->parent;
		rbgparent = n->parent->parent;
		if (rbparent == rbgparent->left) {
			RBNodePtr rbuncle = rbgparent->right;
			if (rbuncle != NULL && rbuncle->color == RED) {
				rbgparent->color = RED;
				rbparent->color = BLACK;
				rbuncle->color = BLACK;
				n = rbgparent;
				printf("22");
			}
			else {
				if (n == rbparent->right) {
					rb_leftrotation(tree,rbparent);
					n = rbparent;
					rbparent = n->parent;
					printf("33");
				}
				rb_rightrotation(tree,rbgparent);
				int tmp = rbparent->color;
				rbparent->color = rbgparent->color;
				rbgparent->color = tmp;
				n = rbparent;
				printf("44");
			}
		}
		else {
			RBNodePtr rbuncle = rbgparent->right;
			if ((rbuncle != NULL) && (rbuncle->color == RED)) {
				rbgparent->color = RED;
				rbparent->color = BLACK;
				rbuncle->color = BLACK;
				n = rbgparent;
				printf("55");
			}
			else {
				if (n == rbparent->left) {
					rb_rightrotation(tree,rbparent);
					n = rbparent;
					rbparent = n->parent;
					printf("66");
				}
				rb_leftrotation(tree,rbgparent);
				int tmp = rbparent->color;
				rbparent->color = rbgparent->color;
				rbgparent->color = tmp;
				printf("77");
			}
		}
	}
	tree->color = BLACK;
	printf("88");
}

void rb_print(BSTPtr self, RBNodePtr tree, int level) {
	if (tree->right != NULL)
		rb_print(self, tree->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("    ");
	printf("%d[%d]\n", tree->val, tree->color);
	if (tree->left != NULL)
		rb_print(self, tree->left, level + 1);
}

void rb_inorder(BSTPtr self, RBNodePtr tree) {
	if (tree == NULL)
		return;
	else {
		rb_inorder(self, tree->left);
		printf("%d ", tree->val);
		rb_inorder(self, tree->right);
	}
}

/*void main() {
	printf("aa");
	BSTPtr bst = bst_alloc();
	printf("bb");
	rb_insert(bst, bst->root, rbnode_alloc(11));
	rb_insert(bst, bst->root, rbnode_alloc(2));
	rb_insert(bst, bst->root, rbnode_alloc(1));
	rb_insert(bst, bst->root, rbnode_alloc(7));
	rb_insert(bst, bst->root, rbnode_alloc(5));
	rb_insert(bst, bst->root, rbnode_alloc(4));
	rb_insert(bst, bst->root, rbnode_alloc(14));
	rb_insert(bst, bst->root, rbnode_alloc(8));
	rb_insert(bst, bst->root, rbnode_alloc(15));
	printf("cc");
	rb_print(bst, bst->root, 0);
	printf("\n");
	rb_inorder(bst, bst->root);
	printf("\n");
	printf("\n[0]-BLACK [1]-RED\n");
	printf("\n");
}*/

/*void rb_insert(rbroot* self, rbnode* tree, rbnode* n) {
	if (self->root == NULL)
		self->root = n;//루트가 비어있으니까 초기상태인경우 걍 값만 ㅍㅍ넣어주면됨 호로로로로로로롤 
	else if (n->val < tree->val) {
		if (tree->left == NULL)
			tree->left = n;
		else
			rb_insert(self, tree->left, n);
	}
	else {
		if (tree->right == NULL)
			tree->right = n;
		else
			rb_insert(self, tree->right, n);
	}
}

void rb_print(rbroot* self, rbnode* tree, int level) {
	if (tree->right != NULL)
		rb_print(self, tree->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("    ");
	printf("%d\n", tree->val);
	if (tree->left != NULL)
		rb_print(self, tree->left, level + 1);
}

void rb_inorder(rbroot* self, rbnode* tree) {
	if (tree == NULL)
		return;
	else {
		rb_inorder(self, tree->left);
		printf("%d ", tree->val);
		rb_inorder(self, tree->right);
	}
}

void main() {
	rbroot *rbr = root_alloc();//root만들기
	rb_insert(rbr, rbr->root, node_alloc(21));
	rb_insert(rbr, rbr->root, node_alloc(12));
	rb_insert(rbr, rbr->root, node_alloc(34));
	rb_insert(rbr, rbr->root, node_alloc(31));
	rb_insert(rbr, rbr->root, node_alloc(10));
	rb_insert(rbr, rbr->root, node_alloc(19));
	rb_print(rbr, rbr->root, 0);
	rb_inorder(rbr, rbr->root);
	printf("\n");
}*/