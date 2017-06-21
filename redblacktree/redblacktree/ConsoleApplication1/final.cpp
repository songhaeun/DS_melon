#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <string.h>
#define BLACK 1
#define RED 0

int nb = 0;

typedef struct node* nodeptr;
struct node {
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;

	int  color;
};

typedef struct rb* rbptr;
struct rb {
	nodeptr root;
	nodeptr nil;
};

nodeptr node_alloc(int newval) {
	nodeptr self = (nodeptr)malloc(sizeof(struct node));
	self->data = newval;
	self->left = NULL;
	self->right = NULL;
	self->parent = NULL;

	return self;
}

rbptr rbt_alloc() {
	rbptr self = (rbptr)malloc(sizeof(struct rb));
	self->nil = (nodeptr)malloc(sizeof(struct node));
	(self->nil)->color = BLACK;
	self->root = self->nil;

	return self;
}

void leftrotation(rbptr rbroot, nodeptr node) {
	nodeptr tmp;

	tmp = node->right;

	node->right = tmp->left;

	if (tmp->left != rbroot->nil) {
		(tmp->left)->parent = node;
	}

	tmp->parent = node->parent;

	if (node->parent == rbroot->nil) {
		rbroot->root = tmp;
	}
	else if (node == (node->parent)->left) {
		(node->parent)->left = tmp;
	}
	else {
		(node->parent)->right = tmp;
	}

	tmp->left = node;
	node->parent = tmp;
}

void rightrotation(rbptr rbroot, nodeptr node) {
	nodeptr tmp;
	tmp = node->left;
	node->left = tmp->right;

	if (tmp->right != rbroot->nil) {
		(tmp->right)->parent = node;
	}

	tmp->parent = node->parent;

	if (node->parent == rbroot->nil) {
		rbroot->root = tmp;
	}
	else if (node == (node->parent)->left) {
		(node->parent)->left = tmp;
	}
	else {
		(node->parent)->right = tmp;
	}

	tmp->right = node;
	node->parent = tmp;
}

void insertfixup(rbptr rbroot, nodeptr node) {
	nodeptr uncle = NULL;

	while ((node->parent)->color == RED) {
		if (node->parent == (node->parent->parent)->left) {
			uncle = (node->parent->parent)->right;

			if (uncle->color == RED) {
				(node->parent)->color = BLACK;
				uncle->color = BLACK;

				(node->parent->parent)->color = RED;

				node = node->parent->parent;
			}
			else {
				if (node == (node->parent)->right) {
					node = node->parent;
					leftrotation(rbroot, node);

				}

				(node->parent)->color = BLACK;
				(node->parent->parent)->color = RED;

				rightrotation(rbroot, (node->parent->parent));

			}
		}
		else {
			uncle = (node->parent->parent)->left;

			if (uncle->color == RED) {
				(node->parent)->color = BLACK;
				uncle->color = BLACK;

				(node->parent->parent)->color = RED;

				node = node->parent->parent;
			}
			else {
				if (node == (node->parent)->left) {
					node = (node->parent);

					rightrotation(rbroot, node);
				}
				(node->parent)->color = BLACK;
				(node->parent->parent)->color = RED;

				leftrotation(rbroot, (node->parent->parent));
			}
		}
	}

	(rbroot->root)->color = BLACK;
}

void insert(rbptr rbroot, int newval) {

	nodeptr newn = (nodeptr)malloc(sizeof(struct node));
	nodeptr tmp = rbroot->root;
	nodeptr snewn = rbroot->nil;

	newn->left = rbroot->nil;
	newn->right = rbroot->nil;
	newn->color = RED;
	newn->data = newval;


	while (tmp != rbroot->nil) {
		snewn = tmp;

		if (newval > tmp->data) {
			tmp = tmp->right;
		}
		else {
			tmp = tmp->left;
		}
	}

	newn->parent = snewn;

	if (snewn == rbroot->nil) {
		rbroot->root = newn;
	}
	else if (newval > snewn->data) {
		snewn->right = newn;
	}
	else {
		snewn->left = newn;
	}

	insertfixup(rbroot, newn);

}

void transplant(rbptr rbroot, nodeptr node, nodeptr snode) {
	if (node->parent == rbroot->nil) {
		rbroot->root = snode;
	}
	else if (node == (node->parent)->left) {
		(node->parent)->left = snode;
	}
	else {
		(node->parent)->right = snode;
	}

	snode->parent = node->parent;
}

void deletefixup(rbptr rbroot, nodeptr node) {
	nodeptr bro = NULL;

	while ((node != rbroot->root) && (node->color == BLACK)) {
		if (node == (node->parent)->left) {
			bro = (node->parent)->right;

			if (bro->color == RED) {
				bro->color = BLACK;
				(node->parent)->color = RED;
				leftrotation(rbroot, node->parent);

				bro = (node->parent)->right;
			}

			if ((bro->left)->color == BLACK && (bro->right)->color == BLACK) {
				bro->color = RED;
				node = node->parent;
			}
			else if ((bro->left)->color == RED && (bro->right)->color == BLACK) {
				bro->color = RED;
				(bro->left)->color = BLACK;
				rightrotation(rbroot, bro);

				bro = (node->parent)->right;
			}

			if ((bro->right)->color == RED) {
				bro->color = (node->parent)->color;
				(bro->right)->color = BLACK;
				(node->parent)->color = BLACK;
				leftrotation(rbroot, node->parent);

				node = rbroot->root;
			}
		}
		else {
			bro = (node->parent)->left;

			if (bro->color == RED) {
				bro->color = BLACK;
				(node->parent)->color = RED;
				rightrotation(rbroot, node->parent);

				bro = (node->parent)->left;
			}

			if ((bro->left)->color == BLACK && (bro->right)->color == BLACK) {
				bro->color = RED;
				node = node->parent;
			}

			else if ((bro->right)->color == RED && (bro->left)->color == BLACK) {
				bro->color = RED;
				(bro->right)->color = BLACK;
				leftrotation(rbroot, bro);

				bro = (node->parent)->left;
			}

			if ((bro->left)->color == RED) {
				bro->color = (node->parent)->color;
				(bro->left)->color = BLACK;
				(node->parent)->color = BLACK;
				rightrotation(rbroot, node->parent);

				node = rbroot->root;
			}
		}
	}

	node->color = BLACK;
}

void deletedelete(rbptr rbroot, int todo) {
	nodeptr target = rbroot->root;
	nodeptr temp = NULL;
	nodeptr x = NULL;
	int original;


	while (todo != target->data) {
		if (target->data > todo) {
			target = target->left;
		}
		else {
			target = target->right;
		}
	}
	original = target->color;

	if (target->left == rbroot->nil) {
		x = target->right;
		transplant(rbroot, target, target->right);
	}
	else if (target->right == rbroot->nil) {
		x = target->left;
		transplant(rbroot, target, target->left);
	}
	else {
		temp = target->right;

		while (temp->left != rbroot->nil) {
			temp = temp->left;
		}

		original = temp->color;
		x = temp->right;

		transplant(rbroot, temp, temp->right);
		temp->right = target->right;
		(temp->right)->parent = temp;

		transplant(rbroot, target, temp);
		temp->left = target->left;
		(temp->left)->parent = temp;
		temp->color = target->color;
	}

	if (original == BLACK) {
		deletefixup(rbroot, x);
	}

	free(target);
}

int search(rbptr rbroot, int todo) {
	nodeptr current = rbroot->root;
	int check = 1;

	if (current == rbroot->nil) {
		check = 0;
		return check;
	}
	while (current->data != todo) {
		if (current->data > todo) {
			if (current->left != rbroot->nil) {
				current = current->left;
			}
			else {
				check = 0;
				return check;
			}
		}
		else {
			if (current->right != rbroot->nil) {
				current = current->right;
			}
			else {
				check = 0;
				return check;
			}
		}
	}

	return check = 1;
}
int checktotal(rbptr rbroot, nodeptr tree) {
	int check = 0;
	if (tree != rbroot->nil) {
		check = 1 + checktotal(rbroot, tree->left) + checktotal(rbroot, tree->right);
	}
	return check;

}
int blackheight(rbptr rbroot, nodeptr tree) {
	int height = 0;
	if (tree == rbroot->nil)
		return height;
	if (tree->color == 0)
		height = 0;
	else
		height = 1;
	if (tree->left != rbroot->nil)
		return height + blackheight(rbroot, tree->left);
	else if (tree->right != rbroot->nil)
		return height + blackheight(rbroot, tree->right);
	else
		return height;
	return height;
}

void inorder(rbptr rbroot, nodeptr tree) {
	if (tree == rbroot->nil) {
		return;
	}
	else {
		inorder(rbroot, tree->left);
		printf("%d[%c]\n", tree->data, tree->color == 1 ? 'B' : 'R');
		inorder(rbroot, tree->right);
	}
}

int checkcolor(rbptr rbroot, nodeptr tree) {
	int check = 0;
	if (tree != rbroot->nil) {
		if (tree->color == 1) {
			check = 1 + checkcolor(rbroot, tree->left) + checkcolor(rbroot, tree->right);
		}
		else
			check = checkcolor(rbroot, tree->left) + checkcolor(rbroot, tree->right);
	}
	return check;
}

void main(int argc, char **argv) {
	FILE *fp;
	char filename[] = "test.txt";

	WIN32_FIND_DATA ffd;
	TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	int data;
	int *arr = NULL;
	int size = 0;
	int total = 0;
	int gotoinsert = 0;
	int miss = 0;
	int gotodelete = 0;

	rbptr rbt = rbt_alloc();

	fp = fopen("C:\\my0531\\test.txt", "r");
	while (fscanf(fp, "%d", &data) != EOF) {
		arr = (int*)realloc(arr, sizeof(int)*(size + 1));
		arr[size] = data;
		size++;
	}
	fclose(fp);
	for (int i = 0; i < size; i++) {
		if (arr[i] == 0)break;
		else if (arr[i] > 0) {
			insert(rbt, arr[i]);
			gotoinsert += 1;
		}
		else {
			arr[i] = (-1)*arr[i];
			if (search(rbt, arr[i]) == 1) {
				deletedelete(rbt, arr[i]);
				gotodelete += 1;
			}
			else {
				miss += 1;
			}


		}

	}

	StringCchCopy(szDir, MAX_PATH, TEXT("."));

	//_tprintf(TEXT("\nTarget directory is %s\n\n"), szDir);

	// Prepare string for use with FindFile functions.  First, copy the
	// string to a buffer, then append '\*' to the directory name.


	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	// Find the first file in the directory.

	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		printf("Error: FindFirstFile\n");

	}

	// List all the files in the directory with some info about them.

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
		}
		else
		{
			_tprintf(TEXT("filename = %s\n"), ffd.cFileName);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		printf("Error: FindFirstFile\n");
	}

	FindClose(hFind); 

	//printf("filename = %s \n", filename);

	printf("total: %d\n", checktotal(rbt, rbt->root));
	printf("bh: %d\n", blackheight(rbt, rbt->root));
	printf("insert: %d\n", gotoinsert);
	printf("delete: %d\n", gotodelete);
	printf("miss: %d\n", miss);
	printf("nb = %d \n", checkcolor(rbt, rbt->root));

	inorder(rbt, rbt->root);


//
	FILE *newfp;
	int newdata;
	int *newarr=NULL;
	int newsize = 0;
	newfp = fopen("C:\\my0531\\search.txt","r");
	while (fscanf(newfp, "%d", &newdata) != EOF) {
		newarr = (int*)realloc(newarr, sizeof(int)*(newsize + 1));
		newarr[newsize] = newdata;
		newsize++;
	}
	fclose(newfp);
	for (int i = 0; i < newsize; i++) {
		if (search(rbt, newarr[i]) == 1)
		{
			printf("%d찾음\n", newarr[i]);

		}
		else if(search(rbt,newarr[i])==0 && newarr[i]!=0)
			printf("%d못찾음\n", newarr[i]);
		else if (newarr[i] == 0)break;
	}
	return;
}