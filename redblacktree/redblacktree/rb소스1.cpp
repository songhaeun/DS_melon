#include <stdio.h>
#include <malloc.h>

typedef struct _node {
	struct _node *left;
	struct _node *right;
	int colour; //���� �����̸� 1, �����̸� 0
	int key;
}node;
void newtree(node **p) {
	//�ʱ�ȭ ���������� ����
	*p = (node*)malloc(sizeof(node));
	(*p)->left = NULL;
	(*p)->right = NULL;
	(*p)->colour = 0;//�ʱ���� ����
}
node *rbtsearch(int key, node *base, size_t *num) {
	//�˻��Լ�
	node *s;
	s = base->left;//s���Ѹ�
	while (key != s->key && s != NULL) {
		if (key, s->key)//������ ��������
			s = s->left;
		else
			s = s->right;
	}
	return s;
}
node *rotation(int key, node *pivot, node *base) {
	//ȸ�� ��������
	node *child;
	//newtree(&child);
	node *gchild;
	//newtree(&gchild);//�ڽ��̶� ����
	if (key < pivot->key || pivot == base) //�Ƶ��� ���ΰ��� ����
		child = pivot->left;
	else
		child = pivot->right;
	if (key < child->key) { //���ڹ��� ����
		gchild = child->left; //����ȸ��
		child->left = gchild->right;
		gchild->right = child;
	}
	else {
		gchild = child->right; //������ȸ��
		child->right = gchild->left;
		gchild->left = child;
	}
	if (key < pivot->key || pivot == base)//�࿡���ڿ���
		pivot->left = gchild;
	else
		pivot->right = gchild;
	return gchild;
}
int rbtinsert(int key, node *base/*, size_t *num*/) {
	node *t, *parent, *gparent, *ggparent; //�ڱ��ڽ� 
	ggparent = gparent = parent = base;
	t = base->left;
	while (t != NULL) {
		if (key == t->key)
			return NULL; // �̹� ���� ���� ����
		if (t->left && t->right && t->left->colour && t->right->colour) {
			t->colour = 1; //����ٲٱ�
			t->left->colour = t->right->colour = 0;
			if (parent->colour) {//�θ� �����̸� ȸ���ؾߵ�
				gparent->colour = 1;
				if (key < gparent->key != key < parent->key)
					parent = rotation(key, gparent, base);//LR RLȸ��
				t = rotation(key, ggparent, base);//LL RRȸ��
				t->colour = 0;
			}
			base->left->colour = 0; //�Ѹ����� ��������
		}
		ggparent = gparent;
		gparent = parent;
		parent = t;
		if (key < t->key)//���ε���~~ã��
			t = t->left;
		else
			t = t->right;
	}
	if ((t = (node*)malloc(sizeof(node))) == NULL)//������
		return NULL;
	t->key = key;
	t->left = NULL;
	t->right = NULL;
	if (key < parent->key || parent == base) //����
		parent->left = t;
	else
		parent->right = t;
	//(*num)++; //�ڷ������, �̰Ŵ��������ɵ�
	t->colour = 1;//���� ���ԵǴ� ���� ����
	if (parent->colour) {//�θ𵵻����̸� ȸ���ؾߵ�
		gparent->colour = 1;
		if (key < gparent->key != key < parent->key)//LR RLȸ��
			parent = rotation(key, gparent, base);
		t = rotation(key, ggparent, base);//LL RRȸ��
		t->colour = 0;
	}
	base->left->colour = 0;
	return 0;
}
void rbtlist(node *p, int level) {//��������Ʈ
	if (p->right != NULL)
		rbtlist(p->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("      ");
	printf("%d[%d]\n", p->key, p->colour);
	if (p->left != NULL)
		rbtlist(p->left, level + 1);

}
node *findseed(int key, node *base) {
	node *del, *seed_parent, *parent;
	seed_parent = NULL;
	parent = base;
	del = base->left;
	while (del != NULL) {
		if (key < del->key) {
			if (del->colour || (del->right&&del->right->colour))
				//������峪 ������ �ڽ��� ������ ã��
				seed_parent = parent;
			parent = del;
			del = del->left;
		}
		else {
			if (del->colour || (del->left && del->left->colour))
				//������峪 ���� �ڽ��� ������
				seed_parent = parent;
			parent = del;
			del = del->right;
		}
	}
	return seed_parent;
}
void makeleafred(int key, node *base) {
	node *seed_parent; //newtree(&seed_parent);
	node *seed; //newtree(&seed);
	node *seed_child; //newtree(&seed_child);
	seed_parent = findseed(key, base);//������ ã��������
	if (seed_parent == NULL) {//�����̾��� ��
		seed_parent = base;
		seed = seed_parent->left;
		seed->colour = 1;//�Ѹ���带 �������� �ϰ� 
	}
	else {
		if (key < seed_parent->key || seed_parent == base)
			seed = seed_parent->left;
		else
			seed = seed_parent->right;
	}
	if (!seed->colour) {//�����̻����̾ƴϸ� ���ڽ��� ������
						//�׷��� ȸ���� �����÷�
		if (key < seed->key)
			seed_child = seed->right;
		else
			seed_child = seed->left;
		seed->colour = 1;
		seed_child->colour = 0;
		seed_parent = rotation(seed_child->key, seed_parent, base);
	}
	while (seed->left&&seed->right) {//�ܺγ�尡 �ƴҵ���
		seed->colour = 0;//������ȯ
		seed->right->colour = 1;
		seed->left->colour = 1;
		if (key < seed->key) {
			if ((seed->right->left || seed->right->right) && (seed->right->left->colour || seed->right->right->colour)) {
				//ȸ���� �ʿ��ϸ� ȸ��
				if (seed->right->left&&seed->right->left->colour) {
					//RLȸ���ʿ�
					seed->right->colour = 0;
					rotation(seed->right->left->key, seed, base);
				}
				else
					seed->right->right->colour = 0;
				rotation(seed->right->key, seed_parent, base);//RR
			}
			seed_parent = seed;
			seed = seed->left;
		}
		else {
			if ((seed->left->left || seed->left->right) && (seed->left->left->colour || seed->left->right->colour)) {
				//ȸ���ʿ��ϸ� �ϱ�
				if (seed->left->right&&seed->left->right->colour) {
					//LR
					seed->left->colour = 0;
					rotation(seed->left->right->key, seed, base);
				}
				else
					seed->left->left->colour = 0;
				rotation(seed->left->key, seed_parent, base);//LL
			}
			seed_parent = seed;
			seed = seed->right;
		}
	}
}
int rbtdelete(int key, node *base) {
	node *parent = base;
	node *del = base->left;
	node *center, *pcenter, *son;

	while (del != NULL && key != del->key) {
		parent = del;
		if (key < del->key)
			del = del->left;
		else
			del = del->right;
	}

	if (del == NULL) {
		key = key*(-1);
		printf("%d - miss �̷��� ����\n", key);
		return 0;
	}
	if (del->right&&del->left) {
		//�ڽ��̵ΰ��ΰ��
		pcenter = del;//�����ҳ�� ��ü�Ұ� ã��
		center = del->right;
		while (center->left != NULL) {
			pcenter = center;
			center = center->left;//���ʹ´�ü��Ű
		}
		del->key = center->key;//������ Ű�� ��ü�� Ű�� �ٲ�
		del = center;//���͸� �����ϰ� ����
		parent = pcenter;
		key = del->key;
	}
	if (del->left || del->right) {
		//�ڽ��� �ϳ��� ���,�´� ��������
		if (del->left)
			son = del->left;
		else
			son = del->right;
		son->colour = 0;
	}
	else if (del->left == NULL && del->right == NULL) {
		//�ڽ��� ���� ��� , �����̸� �׳� ����, �����̸� ��ȯ�ϰ����
		if (!del->colour)
			makeleafred(del->key, base);
		son = NULL;
	}
	base->left->colour = 0;
	if (key < parent->key || parent == base)
		parent->left = son;
	else
		parent->right = son;
	free(del);
	return 0;
}
void inorder(node *base) {

	if (base == NULL)
		return;
	else {
		inorder(base->left);
		printf("%d[%d] ", base->key,base->colour);
		inorder(base->right);
	}
}
int colorinorder(node *base, int check) {
	if (base == NULL)
		return check;
	else {
		colorinorder(base->left, check);
		printf("[%d] ", base->colour);
		colorinorder(base->right, check);
	}
}
int checktotal(node *base) {
	int check = 0;
	if (base != NULL) {
		check = 1 + checktotal(base->left) + checktotal(base->right);
	}
	return check;

}
int checkcolor(node *base) {
	int check = 0;
	if (base != NULL) {
		if (base->colour == 0) {
			check = 1 + checkcolor(base->left) + checkcolor(base->right);
		}
		else
			check = checkcolor(base->left) + checkcolor(base->right);
	}
	return check;
}

int blackHeight(node *base) {
	int height = 0;
	if (base == NULL)
		return height;
	if (base->colour == 0) {
		height = 1;
	}
	else {
		height = 0;
	}
	if (base->left != NULL)
		return height + blackHeight(base->left);
	else if (base->right != NULL)
		return height + blackHeight(base->right);
	else {
		return height;
	}
	return height;
}
int main(void) {
	FILE *fp;
	int data;
	int *arr = NULL;
	int size = 0;
	int total = 0;
	int gotoinsert = 0;
	int gotodelete = 0;


	fp = fopen("C:\\my0531\\test.txt", "r");
	while (fscanf(fp, "%d", &data) != EOF) {//
											//printf("%d->", data);//���Ͽ��ִ°ɹ޾ƿ���
		arr = (int*)realloc(arr, sizeof(int)*(size + 1));
		arr[size] = data;
		size++;//�迭�� �ϳ��� �־���
	}
	fclose(fp);
	/*for (int i = 0; i < size; i++) {
	printf("[%d]->", arr[i]);//�迭�� �ϳ��� ����� ������ Ȯ��
	}*/

	node *head;
	newtree(&head);
	for (int i = 0; i < size; i++) {
		if (arr[i] > 0) {
			rbtinsert(arr[i], head);
			gotoinsert++;
		}
		else if (arr[i] < 0) {
			arr[i] = (-1)*arr[i];
			rbtdelete(arr[i], head);
			gotodelete++;
		}
		else {

			rbtlist(head, 0);
			printf("\n");
			inorder(head);
			printf("\n");
			printf("total: %d\n", checktotal(head) - 1);
			printf("\n");
			printf("bh: %d", blackHeight(head) - 1);
			printf("\n");
			printf("insert: %d", gotoinsert);
			printf("\n");
			printf("delete: %d", gotodelete);
			printf("\n");
			printf("\n");
			printf("\n");
			printf("nb: %d", checkcolor(head) - 1);
			


		}

	}
	//����Ʈ���ذ�





	printf("\nBLACK -0 / RED -1\n");

}