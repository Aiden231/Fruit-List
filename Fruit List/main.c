#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996) // strcpy ���� ����

typedef struct {
	char name[100];
} element;

// �ܼ� ���� ����Ʈ
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

// ���Կ��� (ù��°)
ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

// ���Կ���
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

// ���� ����(������)
ListNode* insert_last(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;

	// ��� �ִ� ���
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

// �������� (ù��°)
ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL; // ����Ʈ�� ������ �� ���ư���
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

// ��������
ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

// ����Ʈ ���
void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
	{
		printf("%s -> ", p->data.name);
	}
	printf("NULL\n");

}

// ����Ʈ ���� �Էµ� ������ �ִ��� �˻��ؼ� ������ 1��ȯ ������ 0 ��ȯ
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
	char enter_fruit[100]; // ���� �̸� ���� ����
	int i = 0; // ������ �ʿ��� ��ġ ����

	// ���� ���ϸ���Ʈ 10��
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

	printf("���� ���� 10��\n");
	print_list(head);

	do {
		// �Է°� �ޱ�
		int enter = 0;

		printf("Menu\n");
		printf("(1) ���ο� ���� �߰��ϱ�\n");
		printf("(2) ���� �����ϱ�\n");
		printf("(3) ������ ���� ��� ����\n");
		printf("(4) ����\n");

		printf("�޴��� �������ּ��� : ");
		scanf_s("%d", &enter);

		// 1 �� ������ ���� �߰�
		if (enter == 1)
		{
			printf("�߰��ϰ� ���� ���� �̸� : ");
			scanf_s("%s", enter_fruit, sizeof(enter_fruit));
			
			// ����Ʈ�� ���� ������ ��� �߰�
			if (search_list(head, enter_fruit) == 0)
			{
				strcpy(data.name, enter_fruit);
				head = insert_last(head, data);
				printf("\n���� ����Ʈ\n");
				print_list(head);
				printf("\n");
			}
			//  ����Ʈ�� �̹� �ִ� ������ ��� �߰� ���� ����
			else if (search_list(head,enter_fruit) == 1)
			{
				printf("%s �� �̹� ����Ʈ �ȿ� �ֽ��ϴ�.\n", enter_fruit);
				printf("\n���� ����Ʈ\n");
				print_list(head);
				printf("\n");
			}
		}
		// 2 �� ������ ���� ����
		else if (enter == 2)
		{
			printf("�����ϰ� ���� ���� �̸� : ");
			scanf_s("%s", enter_fruit, sizeof(enter_fruit));

			// ����Ʈ�� ���� ���� ���� ��û ��
			if (search_list(head, enter_fruit) == 0)
			{
				printf("%s�� ����Ʈ�� �������� �ʽ��ϴ�.\n", enter_fruit);
				printf("\n���� ����Ʈ\n");
				print_list(head);
				printf("\n");
			}
			//  ����Ʈ�� �ִ� ���� �� ���� �� ����
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

				printf("\n���� ����Ʈ\n");
				print_list(head);
				printf("\n");
			}
		}
		// 3�� ������ ������ ���� �׸� ���
		else if (enter == 3)
		{
			print_list(delete_list);
			printf("\n");
		}
		// 4 �� ������ ���α׷� ����
		else if (enter == 4)
		{
			break;
		}
		else
		{
			printf("�޴��� 1~4 ������ ���ڷ� �ٽ� �Է����ּ���\n");
		}
		getchar();
	} while (1);

	return 0;
}