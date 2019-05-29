#ifndef binarytree_h
#define binarytree_h



template <typename Key,typename Info>
class Dictionary{
private:
    struct Node{
        Key key;
        Info val;
        int balance;    //updates after removal and insertion
        
        Node* lchild;
        Node* rchild;
        Node(Key k, Info v):key(k),val(v),balance(0),lchild(nullptr),rchild(nullptr){};
    };
    
    Node* root;
    
    // Addition
    bool add(Key k, Info v, Node*& p);
    
    // Removal
    bool remove(Node*& n, Key k);
    void remove_branch(Node*& n, bool first = 1);
    
    // Used in removal, helping functions
    Node* get_lowest(Node *n);
    Node* get_highest(Node *n);
    
    //
    Info& get(Key k, Node* n);          // returns reference to value under a given key
    Info pop(Node*& n, Key k);          // return value under a given key and removes the item with it
    
    // Helpers
    int height(Node*);
    int size(Node*);
    bool is_leaf(Node* n);
    bool contains_key(Node* n, Key k);  // checks if there is a given key in the dictionary
    
    int update_balance(Node*&);
    int update_balance_directional(Node*& n, Key k);    //updates balance of the tree
    
    // Rotations
    bool rotate(Node*& n);       // Logic for rotating
    void rotate_right(Node *&);
    void rotate_left(Node *&);
    void rotate_left_right(Node *&);
    void rotate_right_left(Node *&);
    void rotate_double(Node *&, bool left_right);
    
    // Displaying the tree
    void draw_box(Node*,std::vector< std::vector<char> > &,int s, int x, int y, bool dir);
public:
    Dictionary():root(nullptr){}
    ~Dictionary();

    int height();
    int size();
    
    bool add(Key k, Info v);
    
    Info& get(Key k);
    
    bool remove(Key k);
    // Removes the nodes with k and returns it's value
    Info pop(Key k);
    void clear();

    // returns true if the key is found
    bool contains_key(Key k);
    bool is_empty();
    // Displays the tree
    void display();
};


template <typename Key, typename Info>
bool Dictionary<Key,Info>::is_empty(){
    if(root)
        return 0;
    return 1;
}


// Returns reference to value under a given key
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

// Call to recursive function get
template <typename Key, typename Info>
Info& Dictionary<Key,Info>::get(Key k){
    return get(k,root);
}

// Returns true if the given key is found
template <typename Key, typename Info>
bool Dictionary<Key,Info>::contains_key(Node* n, Key k){
    if(!n)
        return 0;
    else if(n->key == k)
        return 1;
    else if(n->key > k)
        return contains_key(n->lchild, k);
    else
        return contains_key(n->rchild, k);
}

// Call to recursive function
template <typename Key, typename Info>
bool Dictionary<Key,Info>::contains_key(Key k){
    if(!root)
        return 0;
    return contains_key(root, k);
}

// Add exception
// Returns lowest value key from the dictionary
template <typename Key, typename Info>
typename Dictionary<Key,Info>::Node* Dictionary<Key,Info>::get_lowest(Node *n){
    if(!n)
        throw std::invalid_argument("Given node doesn't exist");
    if(!n->lchild)
        return n;
    else
        return get_lowest(n->lchild);
}

// Add exception
// Returns highest value key from the dictionary
template <typename Key, typename Info>
typename Dictionary<Key,Info>::Node* Dictionary<Key,Info>::get_highest(Node *n){
    if(!n)
        throw std::invalid_argument("Given node doesn't exist");
    if(!n->rchild)
        return n;
    else
        return get_highest(n->rchild);
}

// Returns true if given node is a leaf
template <typename Key, typename Info>
bool Dictionary<Key,Info>::is_leaf(Node *n){
    if(!n)
        throw std::invalid_argument("Given node doesn't exist");
    if(!n->lchild && !n->rchild)
        return 1;
    return 0;
}

// Destructor calls remove_branch, which is a recursive function
template <typename Key, typename Info>
Dictionary<Key,Info>::~Dictionary(){
    remove_branch(root);
}

// Removes whole branch starting from node n
// Updates balance after last operation
template <typename Key, typename Info>
void Dictionary<Key,Info>::remove_branch(Node*& n, bool first){
    if(n){
        remove_branch(n->lchild,0);
        remove_branch(n->rchild,0);
        Key k = n->key;
        delete n;
        n = nullptr;
        if(first)
            update_balance_directional(root,k);
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

// Returns size of the dictionary
template <typename Key, typename Info>
int Dictionary<Key,Info>::size(Node* x){
    if(!x)
        return 0;
    if(!x->lchild && !x->rchild)
        return 1;
    return 1 + size(x->lchild) + size(x->rchild);
}

// Call to recurisve function size
template <typename Key, typename Info>
int Dictionary<Key,Info>::size(){
    return size(root);
}

// Adds a new item to the dictionary
template <typename Key, typename Info>
bool Dictionary<Key,Info>::add(Key k, Info v, Node*& n){
    if(!n){
        n = new Node(k,v);
        return 0;
    }
    if(n->key > k){
        return add(k,v,n->lchild);
    }
    else if(n->key < k){
        return add(k,v,n->rchild);
    }
    else{
        return 1;
    }
}

// Calls recursive function for addition, calls update balance if node was added successfully
template <typename Key, typename Info>
bool Dictionary<Key,Info>::add(Key k, Info v){
    if(root){
        bool r = add(k,v,root);
        if(!r)
            update_balance_directional(root,k);
        return r;
    }
    else{
        root = new Node(k,v);
        return 0;
    }
}

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
        update_balance(root);
    return r;
}

// Removes element and returns value of the removed element
template <typename Key, typename Info>
Info Dictionary<Key,Info>::pop(Node*& n, Key k){
    if(!n)
        throw std::invalid_argument("Given key isn't in the dictionary");
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
    Info tmp = pop(root,k);
    update_balance(root);
    return tmp;
}

// Removes everything from the dictionary
template <typename Key, typename Info>
void Dictionary<Key,Info>::clear(){
    remove_branch(root);
}

// Rotates nodes left right or right left

template <typename Key, typename Info>
void Dictionary<Key,Info>::rotate_double(Node *&n, bool left_right){
    Node* x;
    Node* y;
    Node* z;
    // Saving pointers to nodes we operate on
    if(!left_right){
        z = n;
        x = z->lchild;
        y = x->rchild;
    }
    else{
        x = n;
        z = x->rchild;
        y = z->lchild;
    }
    // Re-attaching children of temporarly-lowest node if they exist
    if(y->lchild){
        x->rchild = y->lchild;
    }
    else{
        x->rchild = nullptr;
    }
    if(y->rchild){
        z->lchild = y->rchild;
    }
    else{
        z->lchild = nullptr;
    }
    // Attaching nodes
    y->lchild = x;
    y->rchild = z;
    n = y;
    
    // Balancing
    // Y was right heave, so the right node is now left heavy
    if(y->balance > 0){
        x->balance = -1;
        z->balance = 0;
    }
    // Balanced
    else if(y->balance == 0){
        x->balance = 0;
        z->balance = 0;
    }
    // Y was left heavy, so the left node is now right heavy
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
    }
    else{
        x->rchild = nullptr;
    }
    // Rotating positions of nodes
    y->lchild = x;
    n = y;
    
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
    }
    else{
        x->lchild = nullptr;
    }
    // Swapping the nodes
    y->rchild = x;
    n = y;
    
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

// Logic for rotating of nodes
template <typename Key, typename Info>
bool Dictionary<Key,Info>::rotate(Node*& n){
    
    if(n->balance == 2 && n->rchild->balance >= 0){
        rotate_left(n);
        return 1;
    }
    else if(n->balance == -2 && n->lchild->balance <= 0){
        rotate_right(n);
        return 1;
    }
    else if(n->balance == 2 && n->rchild->balance == -1){
        rotate_right_left(n);
        return 1;
    }
    else if(n->balance == -2 && n->lchild->balance == 1){
        rotate_left_right(n);
        return 1;
    }
    
    return 0;
}
// Checks all nodes for balance updates
// Used for removal
template <typename Key, typename Info>
int Dictionary<Key,Info>::update_balance(Node*& n){
    if(!n)
        return 0;
    int hleft, hright;
    hleft = update_balance(n->lchild);
    hright = update_balance(n->rchild);
    n->balance = hright - hleft;
    
    if(rotate(n))
        return (hleft > hright ? hleft : hright);
    return (hleft > hright ? hleft : hright) + 1;
}

// Updates balance values of a tree from node to the given key
// Used for addition
template <typename Key, typename Info>
int Dictionary<Key,Info>::update_balance_directional(Node*& n, Key k){
    if(!n){
        return 0;
    }
    int h = 0;  // height
    // Going over nodes affected by addition removal of k
    if(n->key < k){
        h = update_balance_directional(n->rchild,k);
        n->balance = h - height(n->lchild);
    }
    if(n->key > k){
        h = update_balance_directional(n->lchild,k);
        n->balance = height(n->rchild) - h;
    }
    // Rotations
    if(rotate(n))
        return h;
    return h+1;
}


// Recursive function that draws a node and a line from it's parent to it
// Takes as arguments: Node, 2D matrix containing the structure to be displayed,
// size of the box that the function is currently drawing in
// x and y positions of start of the box, direction in which the node is "going" (left for 0, right for 1)
template <typename Key, typename Info>
void Dictionary<Key,Info>::draw_box(Node* n,std::vector< std::vector<char> > &arr,int s, int x, int y, bool dir){
    if(s > 1 && n){
        int nx,ny;      // those values determine the place where value will be displayed
        ny = y+s-1;
        if(dir){
            // Right side
            for(int i=0;i<s-1;i++){
                arr[y+i][x+i] = '\\';
            }
            nx = x+s-2;
        }
        else{
            // Left side
            for(int i=0;i<s-1;i++){
                arr[y+i][x-i] = '/';
            }
            nx = x-s+1;
        }
        int bal = n->balance;
        if(bal==0){
            arr[ny][nx] = '0';
            arr[ny][nx+1] = '0';
        }
        else if(bal<0){
            arr[ny][nx] = '-';
            arr[ny][nx+1] = '1';
        }
        else{
            arr[ny][nx] = '+';
            arr[ny][nx+1] = '1';
        }
        // Different next box posistions for left and right
        if(dir){
            draw_box(n->lchild, arr, s/2, x+s-3, y+s, 0);
            draw_box(n->rchild, arr, s/2, x+s, y+s, 1);
        }
        else{
            draw_box(n->lchild, arr, s/2, x-s, y+s, 0);
            draw_box(n->rchild, arr, s/2, x-s+3, y+s, 1);
        }
    }
}


// Displays tree structure with balance values on nodes
// Makes base preparations for node
// Calls the draw_box function
template <typename Key, typename Info>
void Dictionary<Key,Info>::display(){
    int h = height();
    if(h != 0){
        // Calculating base values for array
        int max_leaves = pow(2,h-1);
        int width = max_leaves * 4 - 2;
        int height = pow(2,h)-1;
        
        // Initialization of the matrix
        std::vector< std::vector<char> > arr (height);
        for(int i=0; i < height; i++){
            arr[i].resize(width);
            for(int k=0; k < width; k++){
                arr[i][k] = ' ';
            }
        }
        // Inserting first element
        int b = root->balance;
        if(b==0){
            arr[0][width/2-1] = '0';
            arr[0][width/2] = '0';
        }
        else if(b<0){
            arr[0][width/2-1] = '-';
            arr[0][width/2] = '1';
        }
        else{
            arr[0][width/2-1] = '+';
            arr[0][width/2] = '1';
        }
        // Recursivly drawing nodes
        draw_box(root->lchild, arr, max_leaves, width/2-2, 1, 0);
        draw_box(root->rchild, arr, max_leaves, width/2+1, 1, 1);
        for(int i=0; i < height; i++){
            for(int k=0; k < width; k++){
                std::cout << arr[i][k];
            }
            std::cout << std::endl;
        }
    }
}
#endif /* binarytree_h */
