#include <stdio.h>
#include <malloc.h>

typedef struct _node {
	struct _node *left;
	struct _node *right;
	int red; //노드색 빨강이면 1, 검정이면 0
	int key;
}node;
void init_tree(node **p) {
	//초기화 나무시작점 생성
	*p = (node*)malloc(sizeof(node));
	(*p)->left = NULL;
	(*p)->right = NULL;
	(*p)->red = 0;//초기색은 검정
}
node *rbti_search(int key, node *base, size_t *num) {
	//검색함수
	node *s;
	s = base->left;//s가뿌리
	while (key != s->key && s != NULL) {
		if (key, s->key)//작으면 왼쪽으로
			s = s->left;
		else
			s = s->right;
	}
	return s;
}
node *rotate(int key, node *pivot, node *base){
	//회전 돌려돌려
	node *child, *gchild; //자식이랑 손자
	if (key < pivot->key || pivot == base) //아들은 어디로갈까 결정
		child = pivot->left;
	else
		child = pivot->right;
	if (key < child->key) { //손자방향 결정
		gchild = child->left; //왼쪽회전
		child->left = gchild->right;
		gchild->right = child;
	}
	else {
		gchild = child->right; //오른쪽회전
		child->right = gchild->left;
		gchild->left = child;
	}
	if (key < pivot->key || pivot == base)//축에손자연결
		pivot->left = gchild;
	else
		pivot->right = gchild;
	return gchild;
}
node *rbti_insert(int key, node *base/*, size_t *num*/) {
	node *t, *parent, *gparent, *ggparent; //자기자신 
	ggparent = gparent = parent = base;
	t = base->left;
	while (t != NULL) {
		if (key == t->key)
			return NULL; // 이미 같은 값이 있음
		if (t->left && t->right && t->left->red && t->right->red) {
			t->red = 1; //색깔바꾸기
			t->left->red = t->right->red = 0;
			if (parent->red) {//부모가 빨강이면 회전해야됨
				gparent->red = 1;
				if (key < gparent->key != key < parent->key)
					parent = rotate(key, gparent, base);//LR RL회전
				t = rotate(key, ggparent, base);//LL RR회전
				t->red = 0;
			}
			base->left->red = 0; //뿌리노드는 검정으로
		}
		ggparent = gparent;
		gparent = parent;
		parent = t;
		if (key < t->key)//어디로들어갈까~~찾기
			t = t->left;
		else
			t = t->right;
	}
	if ((t = (node*)malloc(sizeof(node))) == NULL)//노드생성
		return NULL;
	t->key = key;
	t->left = NULL;
	t->right = NULL;
	if (key < parent->key || parent == base) //삽입
		parent->left = t;
	else
		parent->right = t;
	//(*num)++; //자료수증가, 이거는지워도될듯
	t->red = 1;//새로 삽입되는 노드는 빨강
	if (parent->red) {//부모도빨강이면 회전해야됨
		gparent->red = 1;
		if (key < gparent->key != key < parent->key)//LR RL회전
			parent = rotate(key, gparent, base);
		t = rotate(key, ggparent, base);//LL RR회전
		t->red = 0;
	}
	base->left->red = 0;
	return t;
}
void rbtr_list(node *p, void(*fprt)(void*, int)) {//나무프린트
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