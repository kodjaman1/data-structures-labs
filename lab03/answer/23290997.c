#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int num;
    int prio;
    int time;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int num, int prio, int time) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->num = num;
    newNode->prio = prio;
    newNode->time = time;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}


Node* insertOrdered(Node* head, int num, int prio, int time){

    Node* originalHead = head;

    Node* newNode = createNode(num, prio, time);

    if (head == NULL) {
        return newNode;
    }

    while (newNode->prio >= head->prio){
        if(head->next != NULL){
            head = head->next;
        } else {
            head->next = newNode;
            return originalHead;
        }
    }

    if (head->prev == NULL){
        newNode->next = head;
        head->prev = newNode;
        return newNode;
    } else {
    Node* before = head->prev;
    head->prev = newNode;
    before->next = newNode;
    newNode->prev = before;
    newNode->next = head;
    return originalHead;
    }
}

Node* deleteByPriority(Node* head){
    //en yüksek prio head (ve head'in varsa komşusu (belki komuşları)) olur.
    //eğer komşusu'nun priosu daha büyükse direkt head silinir
    if((head->next != NULL)&&(head->next->prio > head->prio)){
        Node* newHead = head->next;
        newHead->prev = NULL;
        free(head);
        return newHead;
    }
    
    //eğer komşusunun (veya komşularının) priosu eşitse, time'ı küçük olan silinir.
    int smallTime = head->time;
    int deleteID = head->num;
    Node* gezgin = head;
    while(gezgin->next->prio == gezgin->prio){
        gezgin = gezgin->next;
        if (smallTime > gezgin->time){
            smallTime = gezgin->time;
            deleteID = gezgin->num;
        }
    }
    printf("\nsilinmesi gereken id: %d\n", deleteID);

    //şimdi bulduğumuz id'deki agayı silmeliyiz
    //eğer id head'in id'siyse iş kolay
    if(head->num == deleteID){
        Node* newHead = head->next;
        newHead->prev = NULL;
        free(head);
        return newHead;
    }
    //değilse bakalım
    gezgin = head;
    while(gezgin->next->num!=deleteID){
        gezgin = gezgin->next;
    }
    Node* toDelete = gezgin->next;
    gezgin->next = toDelete->next;
    if (toDelete->next != NULL) {
        toDelete->next->prev = gezgin;
    } else {
        // toDelete is the last node
        gezgin->next = NULL;
    }
    free(toDelete);
    return head;
}

Node* printList(Node* head){
    printf("-- %d %d %d\n", head->num, head->prio, head->time);
    while(head->next != NULL){
        head = head->next;
        printf("-- %d %d %d\n", head->num, head->prio, head->time);
    }
}

int main() { 
    Node* head = NULL; 
    int num, prio, time; 
    while (1) { 
        scanf("%d", &num); 
        if (num == -1) 
            break; 
        scanf("%d %d", &prio, &time); 
        head = insertOrdered(head, num, prio, time); 
    } 
    printList(head);  
 
    head = deleteByPriority(head); 
    printf("\n\n");
    printList(head); 
 
    return 0; 
} 