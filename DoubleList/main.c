#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[100];
} element;

typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

DListNode* current;

void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
	current = phead;
}

void move(DListNode* head, DListNode** current, char ch) {
	if (ch == 'p') {
		if (*current != head) {
			*current = (*current)->llink;
		}
		else {
			*current = (*current)->llink->llink;
		}
	}
	else if (ch == 'n') {
		if ((*current)->rlink != head) {
			*current = (*current)->rlink;
		}
		else {
			*current = (*current)->rlink->rlink;
		}

	}
}

void print_list(DListNode* phead) {
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (p == current) {
			printf("%s[O]\n", p->data.name);
		}
		else {
			printf("%s\n", p->data.name);
		}
	}
	printf("\n");
}

void insert(DListNode* before, const char* data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	strcpy_s(newnode->data.name, sizeof(newnode->data.name), data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

void delete(DListNode* head, DListNode* removed) {
	if (removed == head) return;

	if (removed == current) {
		current = current->rlink;
	}
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

void print_menu(void) {
	printf("\nMenu\n");
	printf("n) next fruit\n");
	printf("p) previous fruit\n");
	printf("d) delete the current fruit\n");
	printf("i) insert fruit after current fruit\n");
	printf("o) output the fruit list(Output [0] at the end of the currently sellected fruit)\n");
	printf("e) exit the program\n");
	printf("=================================\n");
	printf("Select a menu: ");
}

int main() {
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);
	char choice;
	element value;

	while (1) {
		print_menu();
		scanf_s(" %c", &choice, 1);

		switch (choice) {
		case 'n':
			move(head, &current, choice);
			break;

		case'p':
			move(head, &current, choice);
			break;

		case'd':
			delete(head, current);
			break;

		case'i':
			printf("Enter the name of the fruit add: ");
			scanf_s("%s", value.name, 100);
			insert(current, value.name);
			current = current->rlink;
			break;

		case'o':
			print_list(head);
			break;

		case'e':
			printf("Exit the program.\n");
			free(head);
			exit(0);

		default:
			printf("Invalid menu. Please select again. \n");
			while (getchar() != '\n');
			break;
		}

	}
	return 0;
}
