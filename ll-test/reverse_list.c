#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
struct ListNode {
    int data;
    struct ListNode* next;
};

// 反转链表函数
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* current = head;
    struct ListNode* next = NULL;
    
    while (current != NULL) {
        next = current->next; // 记录下一个节点
        current->next = prev;  // 反转当前节点的指针
        prev = current;        // 将前驱节点移到当前节点
        current = next;        // 将当前节点移到下一个节点
    }
    
    return prev;  // 返回新的头节点
}

// 创建新节点
struct ListNode* createNode(int data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 打印链表
void printList(struct ListNode* head) {
    struct ListNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    // 创建链表 1 -> 2 -> 3 -> 4 -> NULL
    struct ListNode* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    
    printf("Original List:\n");
    printList(head);

    // 反转链表
    head = reverseList(head);
    
    printf("Reversed List:\n");
    printList(head);

    return 0;
}
