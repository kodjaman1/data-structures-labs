#include <stdio.h>
#include <stdlib.h>

// Çift bağlı liste düğüm yapısı
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Yeni düğüm oluşturma fonksiyonu
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Başa ekleme
Node* addBeg(Node* head, int value) {
    Node* n = createNode(value);
    if (head == NULL)
        return n;
    n->next = head;
    head->prev = n;
    head = n;
    return head; // yeni head
}

// Sona ekleme (Add to end)
Node* addEnd(Node* head, int value) {
    Node* newNode = createNode(value);
    if (head == NULL) {
        return newNode; // Liste boşsa yeni düğüm head olur
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Baştan silme (Delete from beginning)
Node* deleteBeg(Node* head) {
    if (head == NULL) {
        printf("Liste zaten bos.\n");
        return NULL;
    }
    Node* temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    free(temp);
    return head;
}

// Sondan silme
Node* delEnd(Node* head) {
    if (head == NULL)
        return NULL;
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->prev->next = NULL;
    free(temp);
    return head;
}

// Listeyi yazdırma
void printList(Node* head) {
    if (head == NULL) {
        printf("Liste bos.\n");
        return;
    }
    Node* temp = head;
    printf("Liste: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


int main() {
    Node* head = NULL;
    int num;

    while (1) {
        scanf("%d", &num);
        if (num == -1)
            break;
        head = addEnd(head, num);
    }
    
    head = addBeg(head, 5);

    printList(head); 

    // Baştan sil
    head = deleteBeg(head);

    printList(head); 

    return 0;
}

