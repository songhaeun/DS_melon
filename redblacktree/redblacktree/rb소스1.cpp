#include <stdio.h>
#include <malloc.h>

typedef struct _node {
	struct _node *left;
	struct _node *right;
	int colour; //노드색 빨강이면 1, 검정이면 0
	int key;
}node;
void newtree(node **p) {
	//초기화 나무시작점 생성
	*p = (node*)malloc(sizeof(node));
	(*p)->left = NULL;
	(*p)->right = NULL;
	(*p)->colour = 0;//초기색은 검정
}
node *rbtsearch(int key, node *base, size_t *num) {
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
node *rotation(int key, node *pivot, node *base) {
	//회전 돌려돌려
	node *child;
	//newtree(&child);
	node *gchild;
	//newtree(&gchild);//자식이랑 손자
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
int rbtinsert(int key, node *base/*, size_t *num*/) {
	node *t, *parent, *gparent, *ggparent; //자기자신 
	ggparent = gparent = parent = base;
	t = base->left;
	while (t != NULL) {
		if (key == t->key)
			return NULL; // 이미 같은 값이 있음
		if (t->left && t->right && t->left->colour && t->right->colour) {
			t->colour = 1; //색깔바꾸기
			t->left->colour = t->right->colour = 0;
			if (parent->colour) {//부모가 빨강이면 회전해야됨
				gparent->colour = 1;
				if (key < gparent->key != key < parent->key)
					parent = rotation(key, gparent, base);//LR RL회전
				t = rotation(key, ggparent, base);//LL RR회전
				t->colour = 0;
			}
			base->left->colour = 0; //뿌리노드는 검정으로
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
	t->colour = 1;//새로 삽입되는 노드는 빨강
	if (parent->colour) {//부모도빨강이면 회전해야됨
		gparent->colour = 1;
		if (key < gparent->key != key < parent->key)//LR RL회전
			parent = rotation(key, gparent, base);
		t = rotation(key, ggparent, base);//LL RR회전
		t->colour = 0;
	}
	base->left->colour = 0;
	return 0;
}
void rbtlist(node *p, int level) {//나무프린트
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
				//빨간노드나 오른쪽 자식이 빨간거 찾음
				seed_parent = parent;
			parent = del;
			del = del->left;
		}
		else {
			if (del->colour || (del->left && del->left->colour))
				//빨간노드나 왼쪽 자식이 빨간거
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
	seed_parent = findseed(key, base);//빨강을 찾으러가자
	if (seed_parent == NULL) {//빨강이없음 ㅠ
		seed_parent = base;
		seed = seed_parent->left;
		seed->colour = 1;//뿌리노드를 빨강으로 하고 
	}
	else {
		if (key < seed_parent->key || seed_parent == base)
			seed = seed_parent->left;
		else
			seed = seed_parent->right;
	}
	if (!seed->colour) {//씨앗이빨강이아니면 그자식이 빨강이
						//그래서 회전을 빨강올려
		if (key < seed->key)
			seed_child = seed->right;
		else
			seed_child = seed->left;
		seed->colour = 1;
		seed_child->colour = 0;
		seed_parent = rotation(seed_child->key, seed_parent, base);
	}
	while (seed->left&&seed->right) {//외부노드가 아닐동안
		seed->colour = 0;//역색상변환
		seed->right->colour = 1;
		seed->left->colour = 1;
		if (key < seed->key) {
			if ((seed->right->left || seed->right->right) && (seed->right->left->colour || seed->right->right->colour)) {
				//회전이 필요하면 회전
				if (seed->right->left&&seed->right->left->colour) {
					//RL회전필요
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
				//회전필요하면 하기
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
		printf("%d - miss 이런건 없음\n", key);
		return 0;
	}
	if (del->right&&del->left) {
		//자식이두개인경우
		pcenter = del;//삭제할노드 대체할거 찾기
		center = del->right;
		while (center->left != NULL) {
			pcenter = center;
			center = center->left;//센터는대체할키
		}
		del->key = center->key;//삭제할 키를 대체할 키로 바꿈
		del = center;//센터를 삭제하게 조정
		parent = pcenter;
		key = del->key;
	}
	if (del->left || del->right) {
		//자식이 하나인 경우,걔는 빨간색임
		if (del->left)
			son = del->left;
		else
			son = del->right;
		son->colour = 0;
	}
	else if (del->left == NULL && del->right == NULL) {
		//자식이 없는 경우 , 빨강이면 그냥 삭제, 검정이면 변환하고삭제
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
											//printf("%d->", data);//파일에있는걸받아오고
		arr = (int*)realloc(arr, sizeof(int)*(size + 1));
		arr[size] = data;
		size++;//배열에 하나씩 넣어줌
	}
	fclose(fp);
	/*for (int i = 0; i < size; i++) {
	printf("[%d]->", arr[i]);//배열에 하나씩 제대로 들어갔는지 확인
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
	//딜리트만해결





	printf("\nBLACK -0 / RED -1\n");

}