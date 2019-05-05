#include<stdio.h>
#include <string.h>
#include<malloc.h>

struct Item{
    char data[20];
    struct Item *next;
};

struct List{
    int size;
    struct Item *phead;
    struct Item *pend;
    void (*add)(List* _this,char data[]);
    void (*push)(List* _this,char data[]);
    void (*cut_in)(List* _this,char data[],int index);
    void (*del)(List* _this,int index);
    char* (*get)(List*_this,int index);
    void (*pri)(List* _this);
};

static void add(List* _this,char data[]);

static void push(List* _this,char data[]);

static void cut_in(List* _this,char data[],int index);

static void del(List* _this,int index);

char* get(List*_this,int index);

static void pri(List* _this);

struct List* new_List();



int main(){
    struct List *list=new_List();

    for(int i=0;i<5;i++){
        char data[20];
        scanf("%s",data);
        list->add(list,data);
    }
   // list->del(list,3);
    printf("%s",list->get(list,4));
    //list->pri(list);
}

static void add(List* _this,char data[]){
    struct Item *now=(struct Item *)malloc(sizeof(struct Item));
    strcpy(now->data,data);
    (*_this).size++;
    if((*_this).size==1){
        _this->pend=now;
        _this->phead=now;
        _this->phead->next=nullptr;
    }else{
        _this->phead->next=now;
        _this->phead=now;
        _this->phead->next=nullptr;
    }
}

static void push(List* _this,char data[]){
    struct Item *now=(struct Item *)malloc(sizeof(struct Item));
    strcpy(now->data,data);
    (*_this).size++;
    if((*_this).size==1){
        _this->pend=now;
        _this->phead=now;
        _this->phead->next=nullptr;
    }else{
        now->next=_this->pend;
        _this->pend=now;
    }
}

static void cut_in(List* _this,char data[],int index){
    if(index>(*_this).size)
        return;
    struct Item *i=_this->pend;
    int j=0;
    while(i!=nullptr&&++j<index){
        i=i->next;
    }
    struct Item *item=(struct Item*)malloc(sizeof(struct Item));
    strcpy(item->data,data);
    item->next=i->next;
    i->next=item;
}

static void del(List* _this,int index){
    if(index>(*_this).size)
        return;
    struct Item *i=_this->pend;
    struct Item *last=nullptr;
    int j=0;
    while(i!=nullptr&&++j<index){
        last=i;
        i=i->next;
    }
    struct Item *cp=i;
    last->next=i->next;
    (*_this).size--;
    free(cp);
}

char* get(List*_this,int index){
    if(index>(*_this).size)
        return nullptr;
    struct Item *i=_this->pend;
    int j=0;
    while(i!=nullptr&&++j<index){
        i=i->next;
    }
    return i->data;
}

static void pri(List* _this){
    struct Item *i=_this->pend;
    while(i!=nullptr){
        printf("%s\n",i->data);
        i=i->next;
    }
}

struct List* new_List(){
    struct List *_this=(struct List *)malloc(sizeof(struct List));
    (*_this).size=0;
    _this->add=add;
    _this->push=push;
    _this->cut_in=cut_in;
    _this->del=del;
    _this->get=get;
    _this->pri=pri;
    return _this;
}
