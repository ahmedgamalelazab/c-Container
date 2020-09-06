/*

    today is 6/9/2020
    i'm still in the damn army 
    this is a c++ container with singly linked list 

*/

#ifndef SVECTOR_H
#define SVECTOR_H
#include<algorithm>
template<typename Object>
class SVector{

    private:

    // this is a core of my structure 
    struct Node{
        Object data;
        Node* next;
        Node(const Object& d = Object{} , Node* n = nullptr):data(d),next(n){

        };
    };


    public:

    class const_iterator{
        public:
        const_iterator():current(nullptr){};
        const Object& operator*()const{
            return retrieve();
        };
        const_iterator& operator++(){
            current = current -> next;
            return *this;
        };
        //this is a special code to make the compiler distingauge between ++i and i ++ 
        const_iterator& operator++(int){
            const_iterator old = *this;
            ++(*this);
            return old;
        };

        bool operator == (const const_iterator& rhs){
            return current == rhs.current;
        };

        bool operator != (const const_iterator& rhs){
            return !(*this == rhs);
        };
        protected:
        Node* current ;
        const_iterator(Node* p):current(p){};
        Object& retrieve()const{
            return current->data;
        };
        friend class SVector<Object>;

    };

    //desigining a iterator 
    class iterator : public const_iterator{
        public:
        iterator(){};
        Object& operator*(){
            return const_iterator::retrieve();
        };

        const Object& operator*()const{
            return const_iterator::operator*();
        };

        iterator& operator++(){
            this ->current = this->current->next;
            return *this;
        };
        iterator& operator++(int){
            iterator old = *this;
            ++(*this);
            return old;
        };

        protected:
        iterator(Node* p):const_iterator(p){};
        friend class SVector<Object>;
    };

    int size()const{
        return TheSize;
    };

    bool isEmpty()const{
        return size() == 0;
    };

    void Clear(){
        while(!isEmpty()){
            pop_front();
        };
    };

    // what will happen after the first instantiate 
    SVector(){
        init();
    };

        SVector(const SVector& rhs){
        init();
        for(auto & itr : rhs){
            push_back(itr);
        };
    };

SVector& operator=(const SVector& rhs){
    SVector copy = rhs;
    std::swap(*this , copy);
    return *this;
};

~SVector(){
    Clear();
    delete head;
    delete tail;
};


 void DeleteElement(const Object& x){
      Node* current = head->next; // the first element 
      Node* temp = nullptr;
        //expecting the first element is the element that i wanna to delete ? 
      if(current ->data == x ){
          head->next = current->next;
          delete current;
          TheSize --;
          return ;
      }else{
          //else here mean that the first elemenet not the targetet element 
        while(current ->next != tail){
              //case if i faced the last element is the target element 
          if(current ->next ->next == tail){
              if(current ->next->data == x){
                  temp = current;
                  current = current ->next;
                  temp ->next = current ->next;
                  tail ->next = temp;
                  delete current;
                  TheSize --;
                  return;
                  
              };
          }else{
              //the element that i wanna to delete is in the middle 
              temp = current ;
              current = current ->next;
              if(current ->data == x ){
                  temp ->next = current ->next;
                  delete current ;
                  TheSize --;
                  return ;
              };
          };
        };
      };
 };



    iterator begin(){
        return iterator(head->next);
    };
    const_iterator begin()const{
        return const_iterator(head->next);
    };
    iterator end(){
        return iterator(tail);
    };
    const_iterator end()const{
        return const_iterator(tail);
    };

    void push_back(const Object& x){
        Insert(end() , x);
    };

     void pop_back(){
        Node* current = head ->next;
        Node* temp;
        if(TheSize == 1){
            head ->next = tail;
            tail ->next = head;
            delete current;
            TheSize = 0;
            return;
        };
        while(current ->next->next != tail){
            current = current ->next;
        };
        temp = current ;
        current = current ->next;
        temp ->next = current->next;
        tail ->next = temp;
        // O->O->O->O->O-><-O
        delete current ;
        TheSize --;

    };

    void Print_this_Container(){
        for (auto& itr : *this)
        {
            std::cout<<"Container contains : "<<itr<<std::endl;
        }
        
    };

    private:
    //this section is for special functions // methods
    
    //insertion in the damn list \\ container 
    iterator Insert(iterator itr , const Object& x){
        Node* p = itr.current;
        TheSize++;
        return iterator(p->next = p->next->next = new Node(x , p)); // this will work only from push_baack
    };

    // no iterator -- in this case so it will be void 

   


    private:
    
    int TheSize ; // tracker 
    Node* head; // this is for begin();
    Node* tail; // this is for end () ;
    //creating initail state for my instantiation 
    void init(){
        TheSize = 0;
        head = new Node();
        tail = new Node();
        head ->next = tail;
        tail ->next = head;
        // head O-> <-O tail
    };

    //it's faster to reclaim the memory in o(n) time 
    void pop_front(){
        Node* current = head->next;
        if(TheSize == 1){
            head->next = tail;
            tail->next = head;
            delete current;
            TheSize = 0;
            return;
        };
        head->next = current->next;
        delete current;
        TheSize--;

    };



};

#endif // !SVECTOR_H
