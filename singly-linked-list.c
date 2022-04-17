/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;					//노드의 데이터를 저장할 변수
	struct Node* link;			//다음 노드를 가리키는 포인터
} listNode;

typedef struct Head {
	struct Node* first;			//headNode의 포인터인 first 가장 첫 노드를 가리키는 포인터
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);		//headNode에 메모리를 할당해주고 아직 노드가 없는 상태니까 first는 NULL로 초기화
int freeList(headNode* h);				//쓰지 않는 노드를 메모리해제해주는 함수

int insertFirst(headNode* h, int key);	//노드의 가장 앞 부분에 새로운 노드를 추가해주는 함수
int insertNode(headNode* h, int key);	//node끼리 데이터 크기를 비교하여 새로운 node를 추가하는 함수
int insertLast(headNode* h, int key);	//node의 가장 뒷부분에 새로운 노드를 추가해주는 함수

int deleteFirst(headNode* h);			//가장 앞 부분의 node를 삭제시켜주는 함수
int deleteNode(headNode* h, int key);	//사용자로부터 입력받은 데이터값과 같은 데이터값을 저장하고 있는 node를 삭제시켜주는 함수
int deleteLast(headNode* h);			//가장 뒷 부분의 node를 삭제시켜주는 함수
int invertList(headNode* h);			//오름차순 정리되어있는 node들을 내림차순 정렬 시키는 함수

void printList(headNode* h);			//현재 list의 상태를 출력해주는 함수

int main()
{
	printf("[-----[Seo han bit]   [2019038043]-----]\n");

	char command;
	int key;
	headNode* headnode=NULL;			

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);		//headnode로 list 초기화
			break;
		case 'p': case 'P':
			printList(headnode);					//리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);						//사용자로부터 data를 입력받음
			insertNode(headnode, key);				//리스트에 데이터 추가
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);						//데이터 입력받음
			deleteNode(headnode, key);				//같은 값의 데이터가 들어있는 node 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);				//입력받은 데이터를 리스트의 맨 뒤에 추가시켜줌
			break;
		case 'e': case 'E':
			deleteLast(headnode);					//맨 뒤 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);				//데이터를 리스트의 맨 앞에 추가
			break;
		case 't': case 'T':
			deleteFirst(headnode);					//맨 앞 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);					//리스트 내림차순 정렬
			break;
		case 'q': case 'Q':
			freeList(headnode);						//리스트 메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);					//headNode에 연결되어있는 리스트 해제
	}
	free(h);						//마지막 headNode도 메모리 해제
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));				//listNode 구조체의 node에 메모리 할당
	node->key = key;													//새로운 node에 데이터 값 저장

	node->link = h->first;												//node가 first가 가리키고 있던 장소를 가르키고
	h->first = node;													//first가 node를 가리킴으로써 맨 앞에 노드 추가

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));                //추가할 노드에 메모리할당
	node->key = key;													 //추가할 노드의 key에 사용자로부터 입력받은 key 저장
	node->link = NULL;													 //추가할 노드의 link를 NULL로 초기화

	if (h->first == NULL)												 //first가 NULL이라면 그냥 node를 가리킴으로 노드 하나 추가
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {												//사용자로부터 입력받은 데이터가 리스트 안의 노드의 데이터보다 작거나 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {											//n이 가리키는 곳과 first가 가리키는 곳이 같으면
				h->first = node;										//first가 node를 가르키게 하고 
				node->link = n;											//node의 link가 n이 가리키는곳을 가리키게 함
			} 
			else { /* 중간이거나 마지막인 경우 */
				node->link = n;											//중간에 넣을때는 node의 link가 n을 가리키게하고
				trail->link = node;										//n을 가리키던 trail이 node를 가리키게 해서 추가
			}
			return 0;
		}

		trail = n;														//trail이 n을 가리키게하고 n이 다음 노드를 가리키게함
		n = n->link;
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;													//trail이 맨 마지막을 가리키게 되면 더 뒤에 node가 없으므로 맨 뒤에 새로운 node 추가
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {
		n = n->link;			//리스트의 맨 뒤로 가기위해 n->link가 NULL이 될때까지 반복
	}
	n->link = node;				//그 후 n->link가 NULL값이 되면 n->link가 node를 가리키게 함
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {


	if (h->first == NULL)
	{
		printf("nothing to delete.\n");		//first가 NULL값이면 node가 하나도 없다는 말 출력
		return 0;
	}
	listNode* n = h->first;					//n에 first가 가리키는 곳의 주소를 저장

	h->first = n->link;						//first가 가리키는 곳을 n이 가리키는 곳으로 바꿔주고 
	free(n);								//n을 해제

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;									//n에 first가 가리키는 곳의 node를 저장
	listNode* trail = NULL;									//trail을 NULL로 초기화

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) {									//사용자가 입력한 데이터값과 n의 데이터값이 같을 경우
			if(n == h->first) {								//n이 first가 가리키는 곳이 맞으면
				h->first = n->link;							//first가 가리키는 곳을 n->link로 바꿔주고 
			} 
			else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;						//trail의 link를 n이 가리키고 있던 노드로 바꿔주고
			}
			free(n);										//n을 메모리 해제
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);		//못 찾으면 데이터 값이 같은게 없다고 출력
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {									//node가 하나밖에 없는 경우 first도 NULL로 초기화하고
		h->first = NULL;
		free(n);											//n을 메모리 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {								//n->link가 NULL이 될때까지 = 맨 마지막 노드까지
		trail = n;											
		n = n->link;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;										//n이 맨 마지막 node가 되면 n을 삭제 해야하므로 trail의 link를 NULL로 초기화해주고
	free(n);												//n을 메모리 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if(h->first == NULL) {
		printf("nothing to invert...\n");					//node가 없으면 바꿀게 없다고 출력
		return 0;
	}
	listNode *n = h->first;									//n이 first가 가리키는 node가 되게함
	listNode *trail = NULL;									//trail과 middle을 NULL로 초기화
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;										//지금 까지 오름차순으로 -> -> -> 이렇게 가리키고 있었다면 내림차순 정렬은 <- <- <-이렇게 가리키는 곳을 반대로 해주는것
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;										//마지막에 n이 NULL이면 first가 middle을 가리키게 하고 정렬 완료

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");			//node가 없으면 출력할게 없다고 출력
		return;
	}

	p = h->first;									//p가 제일 첫 노드가 되게하고

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);			//리스트의 상태를 출력
		p = p->link;								//p가 다음 노드가 되게 함
		i++;
	}

	printf("  items = %d\n", i);					//node의 개수를 출력
}

