#include<stdio.h>
#include<malloc.h>
#define BLACK 0
#define RED 1

typedef struct RBnode {
	int val, color;
	RBnode *left;
	RBnode *right;
	RBnode *parent;
	RBnode(int newval) {
		val = newval;
		left = right = parent = NULL;
	}
}rbnode;
typedef struct RBtree {
	rbnode *root;
	void leftrotation(rbnode *&, rbnode*&);
	void rightrotation(rbnode *&, rbnode*&);
	void rbfixup(rbnode *&, rbnode*&);
	RBtree() {
		root = NULL;
	}
	void insert(int newval);
	void print();
	void inorder();
}rbtree;
void inorderhelper(rbnode *node) {
	if (node == NULL)
		return;
	inorderhelper(node->left);
	printf("%d[%d]", node->val, node->color);
	inorderhelper(node->right);
}
rbnode *bstinsert(rbnode*tree, rbnode *ttree) {
	if (tree == NULL)
		return ttree;
	if (ttree->val < tree->val) {
		tree->left = bstinsert(tree->left, ttree);
		tree->left->parent = tree;
	}
	else if (ttree->val >tree->val) {
		tree->right = bstinsert(tree->right, ttree);
		tree->right->parent = tree;
	}
	return tree;
}

void leftrotation(rbnode*&tree, rbnode*&ttree) {
	rbnode *newtree = ttree->right;
	ttree->right = newtree->left;
	if (ttree->right != NULL) //!=nil로 책은레프트
		ttree->right->parent = ttree;//책레프트
	newtree->parent = ttree->parent;
	if (ttree->parent == NULL)
		tree = newtree;
	else if (ttree == ttree->parent->left)
		ttree->parent->left = newtree;
	else
		ttree->parent->right = newtree;
	newtree->left = ttree;
	ttree->parent = newtree;
}
void rightrotation(rbnode*&tree, rbnode*&ttree) {
	rbnode*newtree = ttree->left;
	ttree->right = newtree->left;
	if (ttree->right != NULL)
		ttree->right->parent = ttree;
	newtree->parent = ttree->parent;
	if (ttree->parent == NULL)
		tree = newtree;
	else if (ttree == ttree->parent->left)
		ttree->parent->left = newtree;
	else
		ttree->parent->right = newtree;
	newtree->left = ttree;
	ttree->parent = newtree;
}
void rbfixup(rbnode *&tree, rbnode*&ttree) {
	rbnode *parent = NULL;
	rbnode *gparent = NULL;
	while ((ttree != tree) && (ttree->color != BLACK) && (ttree->parent->color == RED)) {
		parent = ttree->parent;
		gparent = ttree->parent->parent;
		if (parent == gparent->right) {
			rbnode*uncle = gparent->right;
			if (uncle != NULL && uncle->color == RED) {
				gparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				ttree = gparent;
			}
			else {
				if (ttree == parent->right) {
					rightrotation(tree, parent);
					ttree = parent;
					parent = ttree->parent;
				}
				leftrotation(tree, gparent);
				int tmp = parent->color;
				parent->color = gparent->color;
				gparent->color = tmp;
				//swap(parent->color, gparent->color);
				ttree = parent;
			}
		}
		else {
			rbnode *uncle = gparent->left;
			if ((uncle != NULL) && (uncle->color == RED)) {
				gparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				ttree = gparent;
			}
			else {
				if (ttree == parent->left) {
					rightrotation(tree, parent);
					ttree = parent;
					parent = ttree->parent;
				}
				leftrotation(tree, gparent);
				int tmp = parent->color;
				parent->color = gparent->color;
				gparent->color = tmp;
				ttree = parent;
			}
		}
	}
	tree->color = BLACK;
}
void rbinsert(int newval) {
	rbnode *newtree = new rbnode(newval);
	rbnode *newroot=  NULL;

	newroot = bstinsert(newroot, newtree);
	rbfixup(newroot, newtree);
}
/*void rbprint(rbtree *&root, rbnode *&tree, int level) {
	if (tree->right == NULL)
		rbprint(root, tree->right, level + 1);
	for (int i = 0; i < level; i++) 
		printf(" ");
	printf("%d [%s]\n", tree->val, tree->color);
	if (tree->left == NULL)
		rbprint(root, tree->left, level + 1);
	printf("뿌엑");
}*/
void rbprint( rbtree * root, rbnode *&tree, int level) {
	if (tree->right == NULL)
		rbprint( root,tree->right, level + 1);
	for (int i = 0; i < level; i++)
		printf(" ");
	printf("%d [%s]\n", tree->val, tree->color);
	if (tree->left == NULL)
		rbprint(root, tree->left, level + 1);
	printf("뿌엑");
}

int main(void) {
	printf("ff");
	RBtree tree;
	printf("gg");
	rbinsert(1);
	rbinsert(2);
	rbinsert(7); 
	rbinsert(5); 
	rbinsert(4); 
	rbinsert(8); 
	rbinsert(15);
	rbinsert(11);
	rbinsert(14);
	printf("hh");
	inorderhelper((&tree)->root);
	printf("jj");
	rbprint(&tree,(&tree)->root, 0);
}

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