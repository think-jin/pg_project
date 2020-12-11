#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 25
#define FALSE 0
#define TRUE 1

typedef struct {
    int type;
    char name[SIZE];
} CLOTH;

typedef struct _node {
    CLOTH cloth;
    struct _node* next;
} C_Node;

typedef struct {
    char top[SIZE];
    char bottom[SIZE];
    int date;
    char activity[SIZE];
} OOTD;

typedef struct __node {
    OOTD ootd;
    struct __node* next;
} O_Node;

void info();
CLOTH make_cloth();
void add_CNode(C_Node* head_ptr, CLOTH cloth);
void printCLOTHList(C_Node* head, void(*print)(const CLOTH*, int num));
void printCLOTHInfo(const CLOTH* cloth, int num);
void deleteNode(C_Node* head_ptr, int (*Delete)(const CLOTH*, char* dname));
int deletebyName(const CLOTH* cloth, char* findname);

OOTD make_ootd(C_Node* head_ptr);
void add_ONode(O_Node* head_ptr, OOTD ootd);
int searchNode(C_Node* head_ptr, char* searchname);
void printOOTDList(O_Node* head, void(*print)(const OOTD*));
void printOOTDInfo(const OOTD* ootd);

int main() {
    C_Node head;
    head.next = NULL;

    O_Node head2;
    head2.next = NULL;

    int num;
    int command;
    //int type;
    while (1) {
        info();

    first:
        while (1) { //숫자 이외의 입력을 받으면 다시 입력받게함
            printf("CHOICE(1~7): ");
            num = scanf("%d", &command);
            while (getchar() != '\n');
            if (num == 1)
                break;
        }
        switch (command) {
        case 1:
            add_CNode(&head, make_cloth());
            break;
        case 2:
            deleteNode(&head, deletebyName);
            break;
        case 3:
            printCLOTHList(&head, printCLOTHInfo);
            break;
        case 4:
            add_ONode(&head2, make_ootd(&head));
            break;
        case 5:
            printOOTDList(&head2, printOOTDInfo);
            break;
        case 6:
            break;
        case 7:
            printf("Exit OOTD JANG");
            return 0;
        default:
            goto first; // 1~7 사이의 숫자가 아닌 숫자가 들어오면 goto문을 사용해 상단으로 이동한다.
        }
    }
    return 0;
}

void info() {
    printf("-----------------------------\n");
    printf("1. Add new cloth\n2. Delete cloth\n3. Show closet\n4. Add OOTD\n5. Show OOTD\n6. Make txt file of OOTD\n7. Exit\n");
    printf("-----------------------------\n");
}

CLOTH make_cloth() {
    CLOTH c;

    printf("Input your cloth type(0. TOP / 1. BOTTOM): "); scanf("%d", &c.type);
    getchar();
    printf("Input your cloth name(less than 25 letter): "); gets(c.name);

    return c;
}

void add_CNode(C_Node* head_ptr, CLOTH cloth) {
    C_Node* newNode = (C_Node*)malloc(sizeof(C_Node));

    newNode->cloth = cloth;
    newNode->next = head_ptr->next;
    head_ptr->next = newNode;
}

void printCLOTHList(C_Node* head, void(*print)(const CLOTH*, int num)) {
    C_Node* cur = head->next;

    int cnt;
    int num;
    while (1) {
        printf("Input number(0. TOP / 1. BOTTOM): ");
        cnt = scanf("%d", &num);
        while (getchar() != '\n');
        if (cnt == 1)
            break;
    }

    char* type[2] = { "TOP", "BOTTOM" };
    printf("\n");
    printf("- - - - - - %s - - - - - -\n", type[num]);

    while (cur != NULL) {
        print(&cur->cloth, num);
        cur = cur->next;
    }
}

void printCLOTHInfo(const CLOTH* cloth, int num) {

    if (cloth->type == num)
        printf("%s\n", cloth->name);
}

void deleteNode(C_Node* head_ptr, int (*Delete)(const CLOTH*, char* dname)) {
    C_Node* target_ptr = head_ptr->next;
    C_Node* prev_ptr = head_ptr;

    char* dname = (char*)malloc(25 * sizeof(char));
    printf("input name of cloth you want to delete: ");
    scanf("%s", dname);

    int exist = FALSE;

    while (target_ptr != NULL) {
        if (Delete(&target_ptr->cloth, dname) == TRUE) {
            exist = TRUE;
            break;
        }
        else {
            exist = FALSE;
            prev_ptr = target_ptr;
            target_ptr = target_ptr->next;
        }
    }

    if (exist == TRUE) printf("[%s] deleted\n", dname);
    else printf("[%s] does not exist\n", dname);

    if (target_ptr == NULL) return;

    prev_ptr->next = target_ptr->next;

    free(dname);
    free(target_ptr);
}

int deletebyName(const CLOTH* cloth, char* dname) {

    if (strcmp(cloth->name, dname) == 0)
        return TRUE;

    else
        return FALSE;
}

OOTD make_ootd(C_Node* head_ptr) {
    OOTD o;

    char* top = (char*)malloc(SIZE * sizeof(char));
    char* bottom = (char*)malloc(SIZE * sizeof(char));

    while (1) {
        printf("Input your top: "); gets(top);
        if (searchNode(head_ptr, top) == TRUE)
            break;
    }
    strcpy(o.top, top);

    while (1) {
        printf("Input your bottom: "); gets(bottom);
        if (searchNode(head_ptr, bottom) == TRUE)
            break;
    }
    strcpy(o.bottom, bottom);

    printf("Input your date( ex) 20201211, 20210101 ): "); scanf("%d", &o.date);
    getchar();
    printf("Input your activity: "); gets(o.activity);

    free(top);
    free(bottom);

    return o;
}

int searchNode(C_Node* head_ptr, char* searchname) {
    C_Node* cur = head_ptr->next;

    while (cur) {
        if (strcmp(cur->cloth.name, searchname) == 0)
            return TRUE;
        cur = cur->next;
    }
    return FALSE;
}

void add_ONode(O_Node* head_ptr, OOTD ootd) {
    O_Node* newNode = (O_Node*)malloc(sizeof(O_Node));

    newNode->ootd = ootd;
    newNode->next = head_ptr->next;
    head_ptr->next = newNode;
}

void printOOTDList(O_Node* head, void(*print)(const OOTD*)) {
    O_Node* cur = head->next;

    printf("DATE / TOP / BOTTOM / ACTIVITY\n");
    while (cur != NULL) {
        print(&cur->ootd);
        cur = cur->next;
    }
}

void printOOTDInfo(const OOTD* ootd) {
    printf("%d / %s / %s / %s\n", ootd->date, ootd->top, ootd->bottom, ootd->activity);
}

