#include<bits/stdc++.h>
using namespace std;

struct DoublyListNode{
    int val;
    DoublyListNode* prev;
    DoublyListNode* next;
    DoublyListNode(int node_val){
        val = node_val;
        prev = NULL;
        next = NULL;
    }
    DoublyListNode(int node_val,DoublyListNode* prev_node,DoublyListNode* next_node){
        val = node_val;
        prev = prev_node;
        next = next_node;
    }
};


class LRUCache{
    public:
    DoublyListNode* head;
    DoublyListNode* tail;
    map<int,int> key_value;
    map<int,DoublyListNode*> key_pointer;
    int space_remaining;
    
    LRUCache(int capacity);
    
    int get(int key); 
    
    void set(int key, int value);   
};
 
LRUCache::LRUCache(int capacity) {
    DoublyListNode* head = NULL;
    DoublyListNode* tail = NULL;
    space_remaining = capacity;
}

int LRUCache::get(int key) {
    //cout<<"get"<<endl;
    if(key_value.find(key) != key_value.end()){
        if(head->val == key){
            return key_value[key];
        }
        // delete the node from its current position
        DoublyListNode* node = key_pointer[key];
        if(node == tail)
            tail = node->prev;
        if(node->prev)
            (node->prev)->next = node->next;
        if(node->next)
            (node->next)->prev = node->prev;
        // add node at the beginning
        else if(head != NULL){
            DoublyListNode* node = new DoublyListNode(key,NULL,head);
            head->prev = node;
            head = node;
        }
        else{
            DoublyListNode* node = new DoublyListNode(key,NULL,NULL);
            head = node;
            tail = head;
        }
        return key_value[key];
    }
    return -1;
}

void LRUCache::set(int key, int value) {
    //cout<<"set"<<endl;
    if(key_value.find(key) != key_value.end()){ // update an already present key
        // update value
        key_value[key] = value;
        if(head->val == key)return;
        // delete the node from its current position
        DoublyListNode* node = key_pointer[key];
        assert(node!=NULL);
        if(node == tail)
            tail = node->prev;
        if(node->prev)
            (node->prev)->next = node->next;
        if(node->next)
            (node->next)->prev = node->prev;
        // add node at the beginning
        if(head != NULL){
            DoublyListNode* node = new DoublyListNode(key,NULL,head);
            key_pointer[key] = node;
            head->prev = node;
            head = node;
        }
        else{
            DoublyListNode* node = new DoublyListNode(key,NULL,NULL);
            key_pointer[key] = node;
            head = node;
            tail = head;
        }
    }
    else{ // adding  a new value
        key_value[key] = value;
        DoublyListNode* node = new DoublyListNode(key,NULL,head);
        key_pointer[key] = node;
        if(head)
            head->prev = node;
        else
            tail = node;
        head = node;
        if(space_remaining == 0){ // delete tail
            assert(tail != NULL);
            key_value.erase(key_value.find(tail->val));
            if(tail->prev){
                (tail->prev)->next = NULL;
                tail = tail->prev;
            }
        }
        else{
            space_remaining--;
        }
    }
}

int main(){}
