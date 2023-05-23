#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996) // strcpy 오류 무시

typedef struct {
	char name[100];
} element;

// 단순 연결 리스트
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

// 삽입연산 (첫번째)
ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

// 삽입연산
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

// 삽입 연산(마지막)
ListNode* insert_last(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;

	// 비어 있는 경우
	if (head == NULL)
	{
		head = p;
	}
	else
	{
		ListNode* q = head;
		while (q->link != NULL)
		{
			q = q->link;
		}
		q->link = p;
	}
	return head;
}

// 삭제연산 (첫번째)
ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL; // 리스트가 공백일 때 돌아가기
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

// 삭제연산
ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

// 리스트 출력
void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
	{
		printf("%s -> ", p->data.name);
	}
	printf("NULL\n");

}

// 리스트 내에 입력된 과일이 있는지 검색해서 있으면 1반환 없으면 0 반환
int search_list(ListNode* head, const element x[100])
{
	ListNode* p = head;

	while (p != NULL) {
		if (strcmp(p->data.name,x) == 0) return 1;
		else p = p->link;
	}
	
	return 0;
}

int main()
{
	ListNode* head = NULL;
	ListNode* delete_list = NULL;
	element data;
	char enter_fruit[100]; // 과일 이름 저장 변수
	int i = 0; // 삭제시 필요한 위치 변수

	// 최초 과일리스트 10개
	strcpy(data.name, "Peach");
	head = insert_first(head, data);
	strcpy(data.name, "Banana");
	head = insert_first(head, data);
	strcpy(data.name, "Raspberry");
	head = insert_first(head, data);
	strcpy(data.name, "Guava");
	head = insert_first(head, data);
	strcpy(data.name, "Plum");
	head = insert_first(head, data);
	strcpy(data.name, "Cherry");
	head = insert_first(head, data);
	strcpy(data.name, "Grape");
	head = insert_first(head, data);
	strcpy(data.name, "Apple");
	head = insert_first(head, data);
	strcpy(data.name, "Orange");
	head = insert_first(head, data);
	strcpy(data.name, "Mango");
	head = insert_first(head, data);

	printf("최초 과일 10개\n");
	print_list(head);

	do {
		// 입력값 받기
		int enter = 0;

		printf("Menu\n");
		printf("(1) 새로운 과일 추가하기\n");
		printf("(2) 과일 삭제하기\n");
		printf("(3) 삭제한 과일 목록 보기\n");
		printf("(4) 종료\n");

		printf("메뉴를 선택해주세요 : ");
		scanf_s("%d", &enter);

		// 1 이 들어오면 과일 추가
		if (enter == 1)
		{
			printf("추가하고 싶은 과일 이름 : ");
			scanf_s("%s", enter_fruit, sizeof(enter_fruit));
			
			// 리스트에 없는 과일의 경우 추가
			if (search_list(head, enter_fruit) == 0)
			{
				strcpy(data.name, enter_fruit);
				head = insert_last(head, data);
				printf("\n현재 리스트\n");
				print_list(head);
				printf("\n");
			}
			//  리스트에 이미 있는 과일인 경우 추가 하지 않음
			else if (search_list(head,enter_fruit) == 1)
			{
				printf("%s 는 이미 리스트 안에 있습니다.\n", enter_fruit);
				printf("\n현재 리스트\n");
				print_list(head);
				printf("\n");
			}
		}
		// 2 이 들어오면 과일 삭제
		else if (enter == 2)
		{
			printf("삭제하고 싶은 과일 이름 : ");
			scanf_s("%s", enter_fruit, sizeof(enter_fruit));

			// 리스트에 없는 과일 삭제 요청 시
			if (search_list(head, enter_fruit) == 0)
			{
				printf("%s는 리스트에 존재하지 않습니다.\n", enter_fruit);
				printf("\n현재 리스트\n");
				print_list(head);
				printf("\n");
			}
			//  리스트에 있는 과일 시 삭제 후 저장
			else if (search_list(head, enter_fruit) == 1)
			{
				int index = 0;
				ListNode* p = head;
				ListNode* prev = NULL;

				while (p != NULL)
				{
					if (strcmp(p->data.name, enter_fruit) == 0)
					{
						if (prev == NULL)
						{
							head = delete_first(head);
						}
						else
						{
							head = delete(head, prev);
						}
						element deleted_element;
						strcpy(deleted_element.name, enter_fruit);
						delete_list = insert_first(delete_list, deleted_element);
						break;
					}
					prev = p;
					p = p->link;
					index++;
				}

				printf("\n현재 리스트\n");
				print_list(head);
				printf("\n");
			}
		}
		// 3이 들어오면 삭제된 과일 항목 출력
		else if (enter == 3)
		{
			print_list(delete_list);
			printf("\n");
		}
		// 4 이 들어오면 프로그램 종료
		else if (enter == 4)
		{
			break;
		}
		else
		{
			printf("메뉴를 1~4 사이의 숫자로 다시 입력해주세요\n");
		}
		getchar();
	} while (1);

	return 0;
}