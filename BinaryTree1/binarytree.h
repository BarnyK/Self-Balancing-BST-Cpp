//
//  binarytree.h
//  BinaryTree1
//
//  Created by Winky Face on 15/05/2019.
//  Copyright © 2019 Barnaba Krupowicz. All rights reserved.
//

#ifndef binarytree_h
#define binarytree_h

template <typename Key,typename Info>
class Dictionary{
private:
    struct Node{
        Key key;
        Info val;
        int balance;
        
        Node* parent;
        Node* lchild;
        Node* rchild;
        Node(Key k, Info v, Node* p = nullptr):key(k),val(v),parent(p),balance(0),lchild(nullptr),rchild(nullptr){};
    };
    
    Node* root;
    
    int height(Node*);                  //recursive
    int countleaves(Node*);             //recursive
    bool add(Key k, Info v, Node* p);   //recursive
    void remove_branch(Node *n);        //recursive
public:
    Dictionary():root(nullptr){}
    ~Dictionary();
    
    int height();
    int countleaves();
    
    bool add(Key k, Info v);
    void remove(Key k);
    
    bool find_by_key(Key k);            // returns true if the key is found
    bool find_by_value(Info v);         // returns true if the value is found
    Info update(Key k, Info v);         // Finds node with Key k and exchanges the value of it with V, return previous value if existed, if not adds new returns new
    
    
    void clear();
    Info get(Key k);        // returns value under a given key
    Info pop(Key k);        // returns value under a given key and removes it
    
    void draw();
};

template <typename Key, typename Info>
Dictionary<Key,Info>::~Dictionary(){
    remove_branch(root);
    root = nullptr;
}

template <typename Key, typename Info>
void Dictionary<Key,Info>::remove_branch(Node* n){
    if(n){
        remove_branch(n->lchild);
        remove_branch(n->rchild);
        delete n;
    }
}

template <typename Key, typename Info>
void Dictionary<Key,Info>::remove(Key k){
    
}

template <typename Key, typename Info>
int Dictionary<Key,Info>::height(Node* x){
    if(!x)
        return 0;
    int hleft,hright;
    hleft = height(x->lchild) + 1;
    hright = height(x->rchild) + 1;
    return hleft > hright ? hleft : hright;
}


template <typename Key, typename Info>
int Dictionary<Key,Info>::countleaves(){
    return countleaves(root);
}

template <typename Key, typename Info>
int Dictionary<Key,Info>::countleaves(Node* x){
    if(!x)
        return 0;
    if(!x->lchild && !x->rchild)
        return 1;
    return countleaves(x->lchild) + countleaves(x->rchild);
}

template <typename Key, typename Info>
int Dictionary<Key,Info>::height(){
    return root ? height(root) : 0;
}

template <typename Key, typename Info>
bool Dictionary<Key,Info>::add(Key k, Info v, Node* p){
    if(p->key > k){
        if(p->lchild)
            return add(k,v,p->lchild);
        else{
            p->lchild = new Node(k,v,p);
            return 0;
        }
    }
    else if(p->key < k){
        if(p->rchild)
            return add(k,v,p->rchild);
        else{
            p->rchild = new Node(k,v,p);
            return 0;
        }
    }
    return 1;
}


template <typename Key, typename Info>
bool Dictionary<Key,Info>::add(Key k, Info v){
    if(root)
        return add(k, v, root);
    else{
        root = new Node(k,v);
        return 0;
    }
}


#endif /* binarytree_h */
