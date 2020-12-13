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
void print_CLOTHName(const CLOTH* cloth, int num);
void print_CLOTHList(C_Node* head, void(*print)(const CLOTH*, int num));
int deletebyName(const CLOTH* cloth, char* findname);
void delete_CNode(C_Node* head_ptr, int (*Delete)(const CLOTH*, char* dname));

int get_count(int n);
int searchNode(C_Node* head_ptr, char* sname);
OOTD make_ootd(C_Node* head_ptr);
void add_ONode(O_Node* head_ptr, OOTD ootd);
void print_OOTDInfo(const OOTD* ootd);
void print_OOTDList(O_Node* head, void(*print)(const OOTD*));
O_Node* sortNode(O_Node* head_ptr);
void save_txt(O_Node* head_ptr);

int main() {
    C_Node c_head;
    c_head.next = NULL;

    O_Node o_head;
    o_head.next = NULL;

    int num;
    int command;
    while (1) {
        info();
        
    first:
        while (1) {
            printf("CHOICE(1~7): ");
            num = scanf("%d", &command);
            while (getchar() != '\n');
            if (num == 1) 
                break;
        }
        switch (command) {
        case 1:
            add_CNode(&c_head, make_cloth());
            break;
        case 2:
            delete_CNode(&c_head, deletebyName);
            break;
        case 3:
            print_CLOTHList(&c_head, print_CLOTHName);
            break;
        case 4:
            add_ONode(&o_head, make_ootd(&c_head));
            break;
        case 5:
            print_OOTDList(sortNode(&o_head), print_OOTDInfo);
            break;
        case 6:
            save_txt(&o_head);
            break;
        case 7:
            printf("Exit OOTD JANG\n");
            return 0;
        default:
            goto first;
        }
    }
    return 0;
}

void info() {
    printf("--------------------------------------------\n");
    printf("1. Add new cloth\n2. Delete cloth\n3. Show closet\n4. Add OOTD\n5. Show OOTD\n6. Make txt file of OOTD\n7. Exit\n");
    printf("--------------------------------------------\n");
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

void print_CLOTHName(const CLOTH* cloth, int num) {
    if (cloth->type == num)
        printf("%s\n", cloth->name);
}

void print_CLOTHList(C_Node* head, void(*print)(const CLOTH*, int num)) {
    C_Node* cur = head->next;

    int cnt;
    int num;
    while (1) {
        printf("Input number(0. TOP / 1. BOTTOM / 2. EXIT): ");
        cnt = scanf("%d", &num);
        while (getchar() != '\n');
        if (cnt == 1)
            break;
    }
    if (num == 2) {
        printf("Exit\n");
        return;
    }

    char* type[2] = { "TOP", "BOTTOM" };
    printf("\n");
    printf("- - - - - - - - %s - - - - - - - -\n", type[num]);

    while (cur != NULL) {
        print(&cur->cloth, num);
        cur = cur->next;
    }
}

int deletebyName(const CLOTH* cloth, char* dname) {
    if (strcmp(cloth->name, dname) == 0)
        return TRUE;
    else
        return FALSE;
}

void delete_CNode(C_Node* head_ptr, int (*Delete)(const CLOTH*, char* dname)) {
    C_Node* target_ptr = head_ptr->next;
    C_Node* prev_ptr = head_ptr;

    char* dname = (char*)malloc(25 * sizeof(char));
    printf("Input name of cloth you want to delete: ");
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

int get_count(int n) {
    int count = 0;
    while (n != 0) {
        n = n / 10;
        count++;
    }

    return count;
}

int searchNode(C_Node* head_ptr, char* sname) {
    C_Node* cur = head_ptr->next;

    while (cur != NULL) {
        if (strcmp(cur->cloth.name, sname) == 0)
            return TRUE;
        cur = cur->next;
    }
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

    while (1) {
        printf("Input your date(e.g. 20201211, 20210101): ");
        scanf("%d", &o.date);
        if (get_count(o.date) == 8) break;
    }
    getchar();

    printf("Input your activity: "); gets(o.activity);
    
    free(top);
    free(bottom);

    return o;
}

void add_ONode(O_Node* head_ptr, OOTD ootd) {
    O_Node* newNode = (O_Node*)malloc(sizeof(O_Node));

    newNode->ootd = ootd;
    newNode->next = head_ptr->next;
    head_ptr->next = newNode;
}

void print_OOTDInfo(const OOTD* ootd) {
    printf("%d / %s / %s / %s\n", ootd->date, ootd->top, ootd->bottom, ootd->activity);
}

void print_OOTDList(O_Node* head, void(*print)(const OOTD*)) {
    O_Node* cur = head->next;

    printf("  DATE   / TOP / BOTTOM / ACTIVITY\n");
    while (cur != NULL) {
        print(&cur->ootd);
        cur = cur->next;
    }
}

O_Node* sortNode(O_Node* head_ptr) {
    O_Node* cur;
    O_Node* prev_ptr;
    prev_ptr = head_ptr;

    while (prev_ptr->next != NULL) {
        if (prev_ptr->ootd.date > prev_ptr->next->ootd.date)
        {
            cur = prev_ptr->next; 
            prev_ptr->next = prev_ptr->next->next; 
            cur->next = head_ptr; 
            head_ptr = prev_ptr = cur; 
            continue;
        }
        prev_ptr = prev_ptr->next;
    }
    return head_ptr;
}

void save_txt(O_Node* head_ptr) {
    int choice;
    printf("Save OOTD(0. YES / 1. NO): ");
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Not save as txt file\n");
        return;
    }
    
    O_Node* cur = head_ptr->next;
    FILE* fp = fopen("ootd.txt", "w");

    if (fp == NULL) {
        printf("Failed to  open file\n");
        return;
    }

    while (cur != NULL) {
        fprintf(fp, "%d %s %s %s\n", cur->ootd.date, cur->ootd.top, cur->ootd.bottom, cur->ootd.activity);
        cur = cur->next;
    }

    fclose(fp);
    printf("Save as txt file\n");
}