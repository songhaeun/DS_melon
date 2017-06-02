#include<stdio.h>
#include<malloc.h>
typedef struct RBnode {
	int val, color;
	struct RBnode *left;
	struct RBnode *right;
	struct RBnode *parent;
}rbnode;

rbnode*node_alloc(int newval) {
	rbnode*self = (rbnode*)malloc(sizeof(rbnode));
	self->val = newval;
	self->left = NULL;
	self->right = NULL;
	return self;
}

typedef struct RBroot {
	struct RBnode *root;
}rbroot;

rbroot* root_alloc() {
	rbroot* self = (rbroot*)malloc(sizeof(rbroot));
	self->root = NULL;
	return self;
}

void rb_insert(rbroot* self, rbnode* tree, rbnode* n) {
	if (self->root == NULL)
		self->root = n;
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
	rbroot *rbr = root_alloc();
	rb_insert(rbr, rbr->root, node_alloc(21));
	rb_insert(rbr, rbr->root, node_alloc(12));
	rb_insert(rbr, rbr->root, node_alloc(34));
	rb_insert(rbr, rbr->root, node_alloc(31));
	rb_insert(rbr, rbr->root, node_alloc(10));
	rb_insert(rbr, rbr->root, node_alloc(19));
	rb_print(rbr, rbr->root, 0);
	rb_inorder(rbr, rbr->root);
	printf("\n");
}