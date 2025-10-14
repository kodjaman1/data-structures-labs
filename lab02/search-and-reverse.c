#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char title[100];
    int  isbn;
    char author[100];
    struct Node *next;
} Node;

Node* create_node(char *title, int isbn, char *author) {
    Node *n = (Node*)malloc(sizeof(Node));
    strcpy(n->title,  title);
    strcpy(n->author, author);
    n->isbn = isbn;
    n->next = NULL;
    return n;
}


Node* add_beg(Node *head, char *title, int isbn, char *author) {
    Node *n = create_node(title, isbn, author);
    n->next = head;
    return n;
}


Node* add_end(Node *head, char *title, int isbn, char *author) {
    Node *n = create_node(title, isbn, author);
    if (head == NULL) return n;
    Node *cur = head;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return head;
}


Node* del_beg(Node *head) {
    if (head == NULL) return NULL;
    Node *old = head;
    head = old->next;
    free(old);
    return head;
}


void print_list(Node *head) {
    if (head == NULL) { puts("(empty)"); return; }
    int i = 1;
    while (head) {
        printf("%d) %s | %s | %d\n", i, head->title, head->author, head->isbn);
        head = head->next; i++;
    }
}

Node* reverse(Node* head) {
    Node* prev = NULL;
    Node* curr = head;
    Node* next = NULL;

    while (curr!=NULL) {

        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    return prev;
}

Node* search(Node *head, int isbn) {
    Node* cur = head;
    while(cur != NULL){
        if ((*cur).isbn == isbn){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}


int main(void) {
    Node *head = NULL;
    char cmd[32];

    while (scanf("%31s", cmd) == 1) {
        if (strcmp(cmd, "QUIT") == 0) break;

        if (strcmp(cmd, "ADD_BEG") == 0) {
            char title[100], author[100]; int isbn;
            scanf("%99s %d %99s", title, &isbn, author);
            head = add_beg(head, title, isbn, author);

        } else if (strcmp(cmd, "ADD_END") == 0) {
            char title[100], author[100]; int isbn;
            scanf("%99s %d %99s", title, &isbn, author);
            head = add_end(head, title, isbn, author);

        } else if (strcmp(cmd, "DEL_BEG") == 0) {
            head = del_beg(head);

        } else if (strcmp(cmd, "PRINT") == 0) {
            print_list(head);
        
        } else if (strcmp(cmd, "REVERSE")== 0){

            print_list(reverse(head));

        } else if (strcmp(cmd, "SEARCH")== 0){
            int isbn;
            printf("Enter the isbn number: ");
            scanf("%d", &isbn);
            Node* result = search(head, isbn);
            if (result) {
                printf("Found: %s | %s | %d\n", result->title, result->author, result->isbn);
            } else {
                printf("Not found\n");
            }
        }
        
    }

    return 0;
}

