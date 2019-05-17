//
//  binarytree.h
//  BinaryTree1
//
//  Created by Winky Face on 15/05/2019.
//  Copyright © 2019 Barnaba Krupowicz. All rights reserved.
//

#ifndef binarytree_h
#define binarytree_h

template <typename Key,typename Val>
class BinaryTree{
private:
    struct Node{
        Key key;
        Val val;
        int balance;
        
        Node* parent;
        Node* lchild;
        Node* rchild;
        Node(Key k, Val v, Node* p = nullptr):key(k),val(v),parent(p),balance(0),lchild(nullptr),rchild(nullptr){};
    };
    
    Node* root;
    
    int height(Node*);
    int countleaves(Node*);
    bool radd(Node* p, Key k, Val v);
public:
    BinaryTree():root(nullptr){}
    
    int height();
    int countleaves();
    void add(Key k, Val v);
    bool radd(Key k, Val v);
};

template <class Key, class Val>
int BinaryTree<Key,Val>::height(Node* x){
    if(!x)
        return 0;
    int hleft,hright;
    hleft = height(x->lchild) + 1;
    hright = height(x->rchild) + 1;
    return hleft > hright ? hleft : hright;
}


template <class Key, class Val>
int BinaryTree<Key,Val>::countleaves(){
    return countleaves(root);
}

template <class Key, class Val>
int BinaryTree<Key,Val>::countleaves(Node* x){
    if(!x)
        return 0;
    if(!x->lchild && !x->rchild)
        return 1;
    return countleaves(x->lchild) + countleaves(x->rchild);
}

template <class Key, class Val>
int BinaryTree<Key,Val>::height(){
    return root ? height(root) : 0;
}

template <class Key, class Val>
bool BinaryTree<Key,Val>::radd(Node* p, Key k, Val v){
    if(p->key > k){
        if(p->lchild)
            return radd(p->lchild,k,v);
        else{
            p->lchild = new Node(k,v,p);
            return 0;
        }
    }
    else if(p->key < k){
        if(p->rchild)
            return radd(p->rchild,k,v);
        else{
            p->rchild = new Node(k,v,p);
            return 0;
        }
    }
    return 1;
}


template <class Key, class Val>
bool BinaryTree<Key,Val>::radd(Key k, Val v){
    if(root)
        return radd(root,k, v);
    else{
        root = new Node(k,v);
        return 0;
    }
}
template <class Key, class Val>
void BinaryTree<Key,Val>::add(Key k, Val v){
    if(!root){
        root = new Node(k,v,nullptr);
    }
    else{
        Node* tmp = root;
        int d = 0;
        while(tmp){
            if(k < tmp->key){
                if(tmp->lchild)
                    tmp = tmp->lchild;
                else{
                    tmp->lchild = new Node(k,v,tmp);
                    break;
                }
            }
            else if(tmp->key < k){
                if(tmp->rchild)
                    tmp = tmp->rchild;
                else{
                    tmp->rchild = new Node(k,v,tmp);
                    break;
                    
                }
            }
            d++;
        }
    }
}

#endif /* binarytree_h */
