#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int type;
    char name[25];
} CLOTH;

typedef struct _node {
    CLOTH cloth;
    struct _node* next;
}Node;

CLOTH make_cloth() {

    CLOTH c;

    printf("input your cloth type (0. top / 1.bottom): "); scanf("%d", &c.type);
    getchar();
    printf("input your cloth name(less than 25 letter): "); gets_s(c.name, 25);

    return c;
}

void addNode(Node* head_ptr, CLOTH cloth) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->cloth = cloth;
    newNode->next = head_ptr->next;
    head_ptr->next = newNode;
   
}

void printCLOTHList(Node* head, void(*print)(const CLOTH*, int num)) {
    Node* cur = head->next;

    int num;
    printf("Input number(0. TOP / 1. BOTTOM): ");
    scanf("%d", &num);

    char* type[2] = { "TOP", "BOTTOM" };
    printf("%s\n", type[num]);
    printf("\n");

    while (cur != NULL) {
        print(&cur->cloth, num); // (), 함수호출(), [] . ->
        cur = cur->next;
    }
}

void printCLOTHInfo(const CLOTH* cloth, int num) {

    if (cloth->type == num)
        printf("%s\n", cloth->name);
}

void deleteNode(Node* head_ptr, int (*Delete)(const CLOTH*, char* findname)) { 
    Node* target_ptr = head_ptr->next;
    Node* prev_ptr = head_ptr;

    char* findname = (char*)malloc(25 * sizeof(char));
    printf("input name of cloth you want to delete: ");
    scanf("%s", findname);

    while (target_ptr != NULL) {
        if (Delete(&target_ptr->cloth, findname) == 1) break;
        else {
            prev_ptr = target_ptr;
            target_ptr = target_ptr->next;
        }
    }

    if (target_ptr == NULL) return;

    prev_ptr->next = target_ptr->next;

    free(findname);
    free(target_ptr);
}

int deletebyName(const CLOTH* cloth, char* findname) {

    if (strcmp(cloth->name, findname) == 0)
        return 1;
    else 
        return 0;
}

void info() {
    printf("1. Add new cloth\n2. Delete cloth\n3. Show closet\n4. Add OOTD\n5. Show OOTD\n6. Make txt file of OOTD\n7. Exit\n");
    printf("CHOICE(1~7): ");
}

int main() {
    Node head;
    head.next = NULL;

    CLOTH c1 = make_cloth();
    addNode(&head, c1);

    CLOTH c2 = make_cloth();
    addNode(&head, c2);

    printCLOTHList(&head, printCLOTHInfo);

    deleteNode(&head, deletebyName);

    printf("after deleting\n");
    printCLOTHList(&head, printCLOTHInfo);

    return 0;
}