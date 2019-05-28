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
        int balance;    //updates after removal and insertion
        
        Node* parent;
        Node* lchild;
        Node* rchild;
        Node(Key k, Info v, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr):key(k),val(v),balance(0),parent(p),lchild(l),rchild(r){};
    };
    
    Node* root;
    
    bool add(Key k, Info v, Node* p);   //done, recursive
    
    bool remove(Node*& n, Key k);       //done, recursive
    void remove_branch(Node*& n, bool first = 1);        //done, recursive
    
    int height(Node*);                  //done, recursive
    int countleaves(Node*);             //done, recursive
    Node* get_lowest(Node *n);          //done, recrusive, add exception
    Node* get_highest(Node *n);         //done, recurisve, add exception
    
    Info& get(Key k, Node* n);          //done, recurisve
    Info pop(Node*& n, Key k);          //done
    bool is_leaf(Node* n);              //done
    
    int update_balance(Node*& n, Key k);    //done
    
    void rotate_right(Node *&);             //done
    void rotate_left(Node *&);              //done
    void rotate_left_right(Node *&);        //done
    void rotate_right_left(Node *&);        //done
    void rotate_double(Node *&, bool left_right);   //done
public:
    Dictionary():root(nullptr){}        // done
    ~Dictionary();                      // done
    
    int height();                       // done
    int countleaves();                  // done
    
    bool add(Key k, Info v);            // done
    bool remove(Key k);                 // done
    
    bool find_by_key(Key k);            // returns true if the key is found
    bool find_by_value(Info v);         // returns true if the value is found
    Info update(Key k, Info v);         // Finds node with Key k and exchanges the value of it with V, return previous value if existed, if not adds new returns new
    Info& get(Key k);        //done, recursive
    
    void clear();           //done, calls recursion
    Info pop(Key k);        //returns value under a given key and removes it
    
    Key get_highest_key();      //done
    Key get_lowest_key();       //done
    
    void draw();            //??????
};



// Rotates nodes left right or right left
template <typename Key, typename Info>
void Dictionary<Key,Info>::rotate_double(Node *&n, bool left_right){
    Node* x;
    Node* y;
    Node* z;
    if(left_right){
        z = n;
        x = z->lchild;
        y = x->rchild;
    }
    else{
        x = n;
        z = x->rchild;
        y = z->lchild;
    }
    
    if(y->lchild){
        x->rchild = y->lchild;
        x->rchild->parent = x;
    }
    else{
        x->rchild = nullptr;
    }
    if(y->rchild){
        z->lchild = y->rchild;
        z->lchild->parent = z;
    }
    else{
        z->lchild = nullptr;
    }
    y->lchild = x;
    y->rchild = z;
    y->parent = x->parent;
    x->parent = z->parent = y;
    n = y;
    // Balancing
    if(y->balance > 0){
        x->balance = -1;
        z->balance = 0;
    }
    else if(y->balance == 0){
        x->balance = 0;
        z->balance = 0;
    }
    else{
        x->balance = 0;
        z->balance = 1;
    }
    y->balance = 0;
}

// Calls double rotation function for left right variant
template <typename Key, typename Info>
void Dictionary<Key,Info>::rotate_left_right(Node *&n){
    rotate_double(n, 0);
}

// Calls double rotation function for right left variant
template <typename Key, typename Info>
void Dictionary<Key,Info>::rotate_right_left(Node *&n){
    rotate_double(n, 1);
}

// Rotates nodes to the left
template <typename Key, typename Info>
void Dictionary<Key,Info>::rotate_left(Node *&n){
    Node* x = n;
    Node* y = n->rchild;
    
    // Dealing with inner child of lower node
    if(y->lchild){
        x->rchild = y->lchild;
        x->rchild->parent = x;
    }
    else{
        x->rchild = nullptr;
    }
    // Rotating positions of nodes
    y->lchild = x;
    n = y;
    // Parents swap
    y->parent = x->parent;
    x->parent = y;

    // Balance value updates
    if(y->balance == 0){
        y->balance = 1;
        x->balance = 1;
    }
    else{
        y->balance = 0;
        x->balance = 0;
    }
}

// Rotates nodes to the right
template <typename Key, typename Info>
void Dictionary<Key,Info>::rotate_right(Node *&n){
    Node* x = n;
    Node* y = x->lchild;
    
    // Dealing with inner child of lower node
    if(y->rchild){
        x->lchild = y->rchild;
        x->lchild->parent = x;
    }
    else{
        x->lchild = nullptr;
    }
    // Swapping the nodes
    y->rchild = x;
    n = y;
    // Parents swap
    y->parent = x->parent;
    x->parent = y;
    
    // Balance value updates
    if(y->balance == 0){
        y->balance = 1;
        x->balance = -1;
    }
    else{
        y->balance = 0;
        x->balance = 0;
    }
}

// Updates balance values of a tree from leaf, good for insertions
template <typename Key, typename Info>
int Dictionary<Key,Info>::update_balance(Node*& n, Key k){
    if(!n){
        return 0;
    }
    int h = 0;
    if(n->key < k){
        h = update_balance(n->rchild,k);
        n->balance = h - height(n->lchild);
    }
    if(n->key > k){
        h = update_balance(n->lchild,k);
        n->balance = height(n->rchild) - h;
    }
    if(n->balance == 2 && n->rchild->balance >= 0){
        rotate_left(n);
    }
    else if(n->balance == -2 && n->lchild->balance <= 0){
        rotate_right(n);
    }
    else if(n->balance == 2 && n->rchild->balance == -1){
        rotate_right_left(n);
    }
    else if(n->balance == -2 && n->lchild->balance == 1){
        rotate_right_left(n);
    }
    return h+1;
}


template <typename Key, typename Info>
Info& Dictionary<Key,Info>::get(Key k, Node* r){
    if(r->key == k){
        return r->val;
    }
    else if(r->key > k){
        return get(k,r->lchild);
    }
    else{
        return get(k,r->rchild);
    }
}

// Calls recursive get function
template <typename Key, typename Info>
Info& Dictionary<Key,Info>::get(Key k){
    return get(k,root);
}
// returns true if the key is found
template <typename Key, typename Info>
bool Dictionary<Key,Info>::find_by_key(Key k){
    
}

// Add exception
// Returns lowest value key from the dictionary
template <typename Key, typename Info>
typename Dictionary<Key,Info>::Node* Dictionary<Key,Info>::get_lowest(Node *n){
//    if(!n)
//        raise
    if(!n->lchild)
        return n;
    else
        return get_lowest(n->lchild);
}

// Add exception
// Returns highest value key from the dictionary
template <typename Key, typename Info>
typename Dictionary<Key,Info>::Node* Dictionary<Key,Info>::get_highest(Node *n){
    //    if(!n)
    //        raise
    if(!n->rchild)
        return n;
    else
        return get_highest(n->rchild);
}

// Returns true if given node is a leaf
template <typename Key, typename Info>
bool Dictionary<Key,Info>::is_leaf(Node *n){
    if(!n)
        return 0;
    if(!n->lchild && !n->rchild)
        return 1;
    return 0;
}

// Yikers
template <typename Key, typename Info>
void Dictionary<Key,Info>::draw(){
    
}

// Destructor calls remove_branch, which is a recursive function
template <typename Key, typename Info>
Dictionary<Key,Info>::~Dictionary(){
    remove_branch(root);
}

// Removes whole branch starting from node n
template <typename Key, typename Info>
void Dictionary<Key,Info>::remove_branch(Node*& n, bool first){
    if(n){
        remove_branch(n->lchild,0);
        remove_branch(n->rchild,0);
        Key k = n->key;
        delete n;
        n = nullptr;
        if(first)
            update_balance(root,k);
    }
}



// Returns height of a tree
template <typename Key, typename Info>
int Dictionary<Key,Info>::height(Node* x){
    if(!x)
        return 0;
    int hleft,hright;
    hleft = height(x->lchild) + 1;
    hright = height(x->rchild) + 1;
    return hleft > hright ? hleft : hright;
}

// Call to recurisve function height
template <typename Key, typename Info>
int Dictionary<Key,Info>::height(){
    return root ? height(root) : 0;
}

// Counts number of leaves on the given tree
template <typename Key, typename Info>
int Dictionary<Key,Info>::countleaves(Node* x){
    if(!x)
        return 0;
    if(!x->lchild && !x->rchild)
        return 1;
    return countleaves(x->lchild) + countleaves(x->rchild);
}

// Call to recurisve function countleaves
template <typename Key, typename Info>
int Dictionary<Key,Info>::countleaves(){
    return countleaves(root);
}

// Adds a new leaf to the dictionary tree
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

// Calls recursive function for addition, calls update balance if node was added successfully
template <typename Key, typename Info>
bool Dictionary<Key,Info>::add(Key k, Info v){
    if(root){
        bool r = add(k,v,root);
        if(!r)
            update_balance(root,k);
        return r;
    }
    else{
        root = new Node(k,v);
        return 0;
    }
}

// ?????? UPDATE_BALANCE
// Removes a node with given key from a dictionary
template <typename Key, typename Info>
bool Dictionary<Key,Info>::remove(Node*& n, Key k){
    if(!n)
        return 1;
    if(n->key > k)
        return remove(n->lchild,k);
    if(n->key < k)
        return remove(n->rchild,k);
    
    Node* tmp = n;
    // 3 cases
    // 1. It's a leaf
    if(is_leaf(n)){
        n = nullptr;
        delete tmp;
    }
    // 2. 1 branch swap with it
    else if(!n->rchild && n->lchild){
        n = n->lchild;
        delete tmp;
    }
    else if(n->rchild && !n->lchild){
        n = n->rchild;
        delete tmp;
    }
    // 3. 2 branches, find lowest element in left branch to replace the new element
    else if(n->lchild && n->rchild){
        tmp = get_lowest(n->rchild);
        n->key = tmp->key;
        n->val = tmp->val;
        remove(n->rchild,tmp->key);
    }
    else{
        return 1;
    }
    return 0;
}

// Calls recursive remove function
template <typename Key, typename Info>
bool Dictionary<Key,Info>::remove(Key k){
    if(!root)
        return 1;
    bool r = remove(root,k);
    if(!r)
        update_balance(root, k);
    return r;
}

// Removes element and returns value of the removed element
template <typename Key, typename Info>
Info Dictionary<Key,Info>::pop(Node*& n, Key k){
    if(!n){
        return 5;
    }
    else{
        if(n->key < k)
            return pop(n->rchild,k);
        else if(n->key > k)
            return pop(n->lchild,k);
        else{
            Info x = n->val;
            remove(n,k);
            return x;
        }
    }
    
}

// Call to recurisve private function
template <typename Key, typename Info>
Info Dictionary<Key,Info>::pop(Key k){
    return pop(root,k);
}

// Removes everything from the dictionary
template <typename Key, typename Info>
void Dictionary<Key,Info>::clear(){
    remove_branch(root);
}

#endif /* binarytree_h */
