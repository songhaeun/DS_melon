#include <stdio.h>
#include <malloc.h>

typedef struct _node {
	struct _node *left;
	struct _node *right;
	int red; //���� �����̸� 1, �����̸� 0
	int key;
}node;
void init_tree(node **p) {
	//�ʱ�ȭ ���������� ����
	*p = (node*)malloc(sizeof(node));
	(*p)->left = NULL;
	(*p)->right = NULL;
	(*p)->red = 0;//�ʱ���� ����
}
node *rbti_search(int key, node *base, size_t *num) {
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
node *rotate(int key, node *pivot, node *base){
	//ȸ�� ��������
	node *child, *gchild; //�ڽ��̶� ����
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
node *rbti_insert(int key, node *base/*, size_t *num*/) {
	node *t, *parent, *gparent, *ggparent; //�ڱ��ڽ� 
	ggparent = gparent = parent = base;
	t = base->left;
	while (t != NULL) {
		if (key == t->key)
			return NULL; // �̹� ���� ���� ����
		if (t->left && t->right && t->left->red && t->right->red) {
			t->red = 1; //����ٲٱ�
			t->left->red = t->right->red = 0;
			if (parent->red) {//�θ� �����̸� ȸ���ؾߵ�
				gparent->red = 1;
				if (key < gparent->key != key < parent->key)
					parent = rotate(key, gparent, base);//LR RLȸ��
				t = rotate(key, ggparent, base);//LL RRȸ��
				t->red = 0;
			}
			base->left->red = 0; //�Ѹ����� ��������
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
	t->red = 1;//���� ���ԵǴ� ���� ����
	if (parent->red) {//�θ𵵻����̸� ȸ���ؾߵ�
		gparent->red = 1;
		if (key < gparent->key != key < parent->key)//LR RLȸ��
			parent = rotate(key, gparent, base);
		t = rotate(key, ggparent, base);//LL RRȸ��
		t->red = 0;
	}
	base->left->red = 0;
	return t;
}
void rbtr_list(node *p, void(*fprt)(void*, int)) {//��������Ʈ
	int i;
	static int x = 0;
	if (p != NULL) {
		x += 2;
		rbtr_list(p->right, fprt);
		for (i = 2; i < x; i++)
			printf(" ");
		fprt(p + 1, p ->red);
		rbtr_list(p->left, fprt);
		x -= 2;
	}

}
int main(void) {
	node *head = NULL;
	rbti_insert(10, head);
	rbti_insert(20, head);
	rbti_insert(15, head);
	rbti_insert(11, head);
	rbti_insert(31, head);
	rbtr_list(head, 0);

}