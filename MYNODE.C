#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//定义单向链表的节点结构体
typedef struct Node {
    int data;//数据
    struct Node *next;//指针
} Node;
// 反转链表函数
Node* reverseList(Node* head) {
    Node* prev = NULL; // 前一个节点，初始为NULL
    Node* current = head; // 当前节点，从头开始
    Node* next = NULL; // 下一个节点，用于暂存

    while (current != NULL) {
        next = current->next; // 暂存下一个节点
        current->next = prev; // 反转当前节点的指针
        prev = current; // 移动prev到当前节点
        current = next; // 移动current到下一个节点
    }
    head = prev; // 更新头指针为新的头节点
    return head; // 返回新的头节点
}

Node *createNode(int value) //申请内存
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        return NULL;//创建失败，返回空指针
    }
    newNode->data = value;//新节点赋值
    newNode->next = NULL;
    return newNode;
}

void insertHead(Node **head, int n)
{
    //创建新节点A
    Node *A = createNode(n);
    if (A == NULL)
    {
        return;
    }
    A->next = *head;//让新节点A指向原来的头节点
    *head = A;//再让头指针指向A，A变成新的头节点
}

void insertTail(Node **head, int value) 
{
    //创建要插入的新节点
    Node* newNode = createNode(value);
    //创建失败就退出
    if (newNode == NULL)
     {
        return; // 内存分配失败，直接返回
    }
   Node *p = *head;
   //循环条件：next节点不为空就继续往下走
    if (p == NULL) {
        *head = newNode;
        return;
    }
    while (p->next != NULL) {
        p = p->next;//p指向后一个节点
    }
    p->next = newNode;  
}//尾插法插入新节点
//打印链表函数【不改变头指针指向】
void printList(Node *head)
 {
    //临时指针p遍历，head保持不变
    Node *p = head;
        printf("链表内容: ");
        //p不是NULL就继续往下走
    while (p != NULL)
     {
        printf(" %d", p->data);
        p = p->next;
    }
    printf(" NULL\n");
}
//删除第n个节点
bool deleteNthNode(Node **head, int n) 
{
    //情况1：链表为空，直接false
    if (*head == NULL || n <= 0) {
        printf("链表为空或位置无效\n");
        return false;
    }
    Node *p = *head;//当前节点
    Node *pre = NULL;//前驱节点（p前面的节点）
    int count =1;
    //找到第n个节点，pre停在前一个，p停在待删节点
    while(p != NULL && count < n)
    {
        pre = p;
        p = p->next;
        count++;
    }
//循环结束后 p == NULL，说明节点不够n个
    if (p == NULL) 
    {
        return false;
    }
    //情况2，要删的是第一个节点(头节点，pre=NULL)
    if (pre == NULL)
    {
        *head = p->next;//头指针移到下一个节点
    }
    else
    {
        //情况3：删中间/尾部节点，pre跳过p，指向p的下一个
        pre->next = p->next;
    }
    free(p);//释放节点内内存
    return true;
}
//查找函数，传入head和n
bool searchNode(Node *head, int n)
{
    Node *p = head;
    int count =1;
    while(p != NULL)
    {
        if(p->data == n)
        {
            printf("找到 %d 的,它是第 %d 个节点\n",n,count);
            return true;
        }
        p = p->next;
        count++;
    }
    printf("未找到 %d\n", n);
    return false;
}
void freeList(Node **head)
{
    Node *p = *head; // p从链表第一个节点开始遍历
    while (p != NULL)
    {
        Node *temp = p; // 先用临时变量temp保存当前节点地址，防止free之后找不到下一个节点
        p = p->next;    // 先把p移动到下一个节点！顺序不能颠倒
        free(temp);     // 释放temp指向的节点内存
    }
    *head = NULL; // 全部释放完毕，将头指针置空，防止变成野指针
}
 

int main(void) 
{
    Node *head = createNode(0);

    printf("[初始链表]\n");
    printList(head);

    //头插测试，插入5
    insertHead(&head, 5);
    printf("[插入5后]\n");
    printList(head);

    //尾插测试，插入10,20,30
    insertTail(&head, 10);
    insertTail(&head, 20);
    insertTail(&head, 30);
    printf("原始");
    printList(head);

    printf("\n========删除内容=====\n");
bool ok = deleteNthNode(&head,4);
if(ok)
printf("删除第四个节点成功\n");
else
 printf("删除失败，节点不足\n");
 printList(head);
// 删除第1个节点（5）
    ok = deleteNthNode(&head,1);
    if(ok)
        printf("删除第1个节点成功\n");
    else
        printf("删除失败，节点不足\n");
    printList(head);

    // 尝试删除第10个（节点不够）
    ok = deleteNthNode(&head,10);
    if(ok)
        printf("删除第10个节点成功\n");
    else
        printf("删除失败，节点不足\n");
    printList(head);


    printf("[尾插10,20,30后]\n");
    printList(head);
    // 释放内存
    //测试查找
    printf("\n========查找20=====\n");
    bool ret = searchNode(head, 20);
    if (ret == false) 
    {
        printf("未找到20\n");
    }
    printf("\n========查找100=====\n");
    ret = searchNode(head, 100);
    if (ret == false) 
    {
        printf("未找到100\n");
    }
    
    
    printf("原链表：");
    printList(head);

    head = reverseList(head); // 头指针更新为新链表头

    printf("反转后：");
    printList(head);
    freeList(&head);
    return 0;
}