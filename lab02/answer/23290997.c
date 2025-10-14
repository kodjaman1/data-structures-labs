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


Node* search_isbn(Node *head, int isbn) {
    Node* cur = head;
    while(cur != NULL){
        if (cur->isbn == isbn){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

Node* search_name(Node* head, char* name){
    Node* cur = head;
    while (cur != NULL){
        if(strcmp(cur->title, name) == 0){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

Node* del_isbn(Node *head, int isbn) {
    Node *to_delete = search_isbn(head, isbn);
    if (to_delete == NULL) return head;
    if (to_delete == head) return del_beg(head);
    Node* cur = head;
    while (cur->next != to_delete){
        cur = cur->next;
    }
    cur->next = to_delete->next;
    free(to_delete);
    return head;
}

Node* move_end(Node* head, char *title){
    Node* to_move = search_name(head, title);
    if (to_move == NULL) return head;
    if (to_move->next == NULL) return head;
    Node* cur = head;
    while (cur->next != to_move){
        cur = cur->next;
    }
    cur->next = to_move->next;
    Node* end = to_move;
    while (end->next != NULL){
        end = end->next;
    }
    end->next = to_move;
    to_move->next = NULL;
    return head;
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
        

        } else if (strcmp(cmd, "DEL_ISBN") == 0) {
            int isbn;
            scanf("%d", &isbn);
            head = del_isbn(head, isbn);

        } else if (strcmp(cmd, "MOVE_END") == 0) {
            char title[100];
            scanf("%99s", title);
            head = move_end(head, title);
        }
    }

    return 0;
}

