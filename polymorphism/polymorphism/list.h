#pragma once
#ifndef __LIST_H
#define __LIST_H


// Data* newData(int val, char* name);

typedef struct NODE Node, * PNode;
struct NODE
{
    void* data;
    Node* next;
    int size;
    // Node* pre;
};
//定义链表
typedef struct LIST
{
    Node* tail;
    Node* head;
}List, * pList;

List* CreateList();
//创建新的结点
Node* NewNode(void* data);

//i销毁结点
void Delete(PNode node);

//销毁链表数据
void Destory(List* list);

//添加数据
Node* Add(List* list, void* data);
//查找
Node* Get(List* list, int idx);

//定位
int in(List* list, void* data);
//删除
void Remove(List* list, int idx);
//插入链表
Node* insert(List* list, int idx, void* data);
#endif // !__LIST_H