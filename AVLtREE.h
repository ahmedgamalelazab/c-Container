/*

    today is 6/9/2020
    i'm still in the damn army 
    this is a c++ container with singly linked list 

*/

#ifndef AVLTREE_H
#define AVLTREE_H
#include<algorithm>
template<typename Object>
class AVLTREE{

    //the core of the application 
    private:

    struct Node{
        Object data ;
        Node * left ;
        Node* right;
        int height = 0;
        Node(const Object& d = Object{}, Node* le = nullptr , Node* ri = nullptr , int h = 0):
        data(d),left(le),right(ri),height(h){
        };
    };

    public:
    AVLTREE():root(nullptr){};
    AVLTREE(const AVLTREE& rhs ){
        root = Clone(rhs.root);
    };
    AVLTREE& operator = (const AVLTREE& rhs){
        AVLTREE copy = rhs;
        std::swap(*this , copy);
        return *this;
    };
    ~AVLTREE(){
        if(!isEmpty()){
            MakeEmpty(root);
        };
    };
    bool isEmpty()const{
        return root == nullptr;
    }

    void insert(const Object& x){
        Insert(x , root);
    };

    void remove(const Object& x){
        deleteElement(x , root);
    };

    void Print_this_tree_Container(){
        PrintTree(root);
    };



    private:
    Node* root ;
    void Insert(const Object& x , Node*& t){
        if(t == nullptr){
            t = new Node(x , nullptr , nullptr);
        }else if(x < t->data){
            Insert(x , t->left);
        }else if (x > t->data){
            Insert(x , t->right);
        }else{
            //duplicate do nothing 
        };
        balance(t);
    };

    int height(Node* t)const{
        return (t == nullptr)? -1 : t->height;
    };

    int max(int lhs , int rhs){
        return (lhs>rhs)? lhs : rhs;
    };

    //section of rotation bulding 

    void RotateWithLeftChild(Node* & k2){
        Node* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) +1;
        k1->height = max(height(k1->left), k2->height) +1;
        k2 = k1; 
    };

    void RotateWithRightChild(Node*& k1){
        Node* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left),height(k1->right)) +1;
        k2->height = max(height(k2->right),k1->height)+1;
        k1 = k2;
    };
    
    void DoubleRotateWithLeftChild(Node* & k3){
        RotateWithRightChild(k3->left);
        RotateWithLeftChild(k3);
    };

    void DoubleRotateWithRightChild(Node* & k4){
        RotateWithLeftChild(k4->right);
        RotateWithRightChild(k4);
    };

    Node* Clone(Node* t){
        if(t == nullptr){
            return nullptr;
        }else{
            return new Node(t->data , Clone(t->left),Clone(t->right),t->height);
        };
    };

    void PrintTree(Node* t){
        if(t != nullptr){
            PrintTree(t->left);
            std::cout<<" Tree Contains : "<<t->data<<std::endl;
            std::cout<<" Tree Locaion in memeory  : "<<t<<std::endl;
            std::cout<<" Tree Left Locaion in memeory  : "<<t->left<<std::endl;
            std::cout<<" Tree right Locaion in memeory  : "<<t->right<<std::endl;
            std::cout<<" Tree height  : "<<t->height<<std::endl;
            PrintTree(t->right);
        };
    };

    void MakeEmpty(Node* & t){
        if(t !=nullptr){
            MakeEmpty(t->left);
            MakeEmpty(t->right);
            delete t;
        };
        t = nullptr;
    };

static const int IMBALANC_ALLOWED = 1;

    void balance(Node *& t){
        if(t == nullptr ){
            return ;
        };
        if(height(t->left) - height(t->right) > IMBALANC_ALLOWED){
            if(height(t->left->left) > height(t->left->right)){
                RotateWithLeftChild( t );
            }else{
                DoubleRotateWithLeftChild( t );
            };
        }else if (height(t->right) - height(t->left)> IMBALANC_ALLOWED){
            if(height(t->right->right) > height(t->right->left)){
                RotateWithRightChild( t );
            }else{
                DoubleRotateWithRightChild( t );
            };
        };

        t->height = max(height(t->left), height(t->right)) +1;
    };

    void deleteElement(const Object& x,Node*& t){
        if(t == nullptr ){
            return;
        }else if (x < t->data){
            deleteElement(x , t->left);
        }else if(x > t->data){
            deleteElement(x , t->right);
        }else if( t->left != nullptr && t->right != nullptr){
            t->data = findMin(t->right)->data;
            deleteElement(t->data , t->right);
        }else{
            Node* oldNode = t;
            t = (t->left!=nullptr)? t->left : t->right;
            delete oldNode;
        };
    };


    Node* findMin(Node* t)const{
    if(t == nullptr){
        return nullptr;
        };  
        if(t ->left !=nullptr){
            findMin(t->left);
        };
        return t; 
    };

     Node* findMax(Node* t)const{
    if(t == nullptr){
        return nullptr;
        };  
        if(t ->right !=nullptr){
            findMin(t->right);
        };
        return t; 
    };




};





#endif // !AVLTREE_H
