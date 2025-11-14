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
// Function prototypes for extra functions
Node* insertAfter(Node* head, int afterValue, int newValue);
Node* deleteByValue(Node* head, int value);
Node* reverseList(Node* head);
int countNodes(Node* head);
void searchValue(Node* head, int value);
void printReverse(Node* head);
Node* sortList(Node* head);
Node* removeEven(Node* head);
Node* mergeLists(Node* h1, Node* h2);
void freeList(Node* head);
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

    // 1. Insert after value
    printf("Insert 99 after 5\n");
    head = insertAfter(head, 5, 99);
    printList(head);

    // 2. Delete by value
    printf("Delete node with value 99\n");
    head = deleteByValue(head, 99);
    printList(head);

    // 3. Reverse list
    printf("Reverse list\n");
    head = reverseList(head);
    printList(head);

    // 4. Count nodes
    printf("Node count: %d\n", countNodes(head));

    // 5. Search for value
    searchValue(head, 5);

    // 6. Print reverse
    printReverse(head);

    // 7. Sort list (ascending)
    head = sortList(head);
    printList(head);

    // 8. Remove even values
    head = removeEven(head);
    printList(head);

    // 9. Merge two lists
    printf("Merging with list2: 7 8 9\n");
    Node* list2 = NULL;
    list2 = addEnd(list2, 7);
    list2 = addEnd(list2, 8);
    list2 = addEnd(list2, 9);
    head = mergeLists(head, list2);
    printList(head);

    // 10. Free list
    freeList(head);
    printf("List freed.\n");
    return 0;
}

// 1. Insert after value
Node* insertAfter(Node* head, int afterValue, int newValue) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == afterValue) {
            Node* n = createNode(newValue);
            n->next = temp->next;
            n->prev = temp;
            if (temp->next) temp->next->prev = n;
            temp->next = n;
            break;
        }
        temp = temp->next;
    }
    return head;
}

// 2. Delete by value
Node* deleteByValue(Node* head, int value) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value) {
            if (temp->prev) temp->prev->next = temp->next;
            else head = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            free(temp);
            break;
        }
        temp = temp->next;
    }
    return head;
}

// 3. Reverse list
Node* reverseList(Node* head) {
    Node* temp = NULL;
    Node* current = head;
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL)
        head = temp->prev;
    return head;
}

// 4. Count nodes
int countNodes(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

// 5. Search for value
void searchValue(Node* head, int value) {
    int pos = 1, found = 0;
    Node* temp = head;
    while (temp) {
        if (temp->data == value) {
            printf("Value %d found at position %d\n", value, pos);
            found = 1;
        }
        temp = temp->next;
        pos++;
    }
    if (!found) printf("Value %d not found\n", value);
}

// 6. Print reverse
void printReverse(Node* head) {
    if (!head) { printf("Liste bos.\n"); return; }
    Node* temp = head;
    while (temp->next) temp = temp->next;
    printf("Reverse: ");
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

// 7. Sort list (ascending)
Node* sortList(Node* head) {
    if (!head) return head;
    Node* i = head;
    while (i) {
        Node* j = i->next;
        while (j) {
            if (i->data > j->data) {
                int t = i->data; i->data = j->data; j->data = t;
            }
            j = j->next;
        }
        i = i->next;
    }
    return head;
}

// 8. Remove even values
Node* removeEven(Node* head) {
    Node* temp = head;
    while (temp) {
        Node* next = temp->next;
        if (temp->data % 2 == 0) {
            if (temp->prev) temp->prev->next = temp->next;
            else head = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            free(temp);
        }
        temp = next;
    }
    return head;
}

// 9. Merge two lists
Node* mergeLists(Node* h1, Node* h2) {
    if (!h1) return h2;
    Node* temp = h1;
    while (temp->next) temp = temp->next;
    temp->next = h2;
    if (h2) h2->prev = temp;
    return h1;
}

// 10. Free list
void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}



