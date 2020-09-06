/*

this is simple vector written by simple data structure which is array 
this is a simple revision on what i have already finished 
today is 6/9/2020 
i'm still in the damn army 

*/
#ifndef VECTOR_H
#define VECTOR_H
#include<algorithm>
template<typename Object>
class Vector{

    public:

    Vector(int initailVal = 0):TheSize(initailVal),TheCapacity(initailVal+SPARE_CAPACITY),objects(nullptr){
        objects = new Object[TheCapacity];
    };

    Vector(const Vector& rhs):TheSize(rhs.TheSize),TheCapacity(rhs.TheCapacity),objects(nullptr){

        //simple loob to transfare the data
        for (size_t i = 0; i < TheSize; i++)
        {
            objects[i] = rhs.objects[i];
        }
        
    };

    Vector& operator=(const Vector& rhs){
        Vector copy = rhs;
        std::swap(*this , copy);
        return *this;
    };  

    ~Vector(){
        delete [] objects;
    };

    int size()const{
        return TheSize;
    };

    int capacity()const{
        return TheCapacity;
    };

    bool isEmpty()const{
        return size() == 0;
    };

    Object& operator[](int index){
        return objects[index];
    };
    const Object& operator[](int index)const{
        return objects[index];
    };

    void push_back(const Object& x){
        if(TheSize == TheCapacity){
            reserve( 2 * TheCapacity + 1 );
        };
        objects[TheSize ++ ] = x ;
    };

    void pop_back(){
        TheSize --;
    };

    typedef Object* iterator;
    typedef const Object* const_iterator;

    iterator begin(){
        return &objects[0];
    };
    const_iterator begin()const{
        return &objects[0];
    };
    iterator end(){
        return &objects[TheSize];
    };
    const_iterator end()const{
        return &objects[TheSize];
    };

    //special printing function 
    void Print_Vector_container()const{
        for(auto& itr : *this){
            std::cout<<"container contains : "<<itr<<std::endl;
        };
    };

    // the mechanic to do deletion from dynamic array container is :    
    // objects = | 1 | | 2 | | 3 |
    // ... now i wanna delete 2
    // newArr =  | 1 | | 3 | |   |
    // swap ( objects[| 1 | | 2 | | 3 |] , newArr | 1 | | 3 | |   |)
    // theSize -- to make it looks like this 
    // newArr =  | 1 | | 3 | | × | ---->  | 1 | | 3 | 
    // final shap will be like this objects[| 1 | | 2 |] 
       
    void DeleteElement(const Object& x){
        int k_counter = 0;
        Object* newArr = new Object[TheSize];
           for(int i = 0 ; i < TheSize ; i++){
               if(x == objects[i]){
                   i++;
               };
               newArr[k_counter] = objects[i];
                   k_counter++; 
           };
           std::swap(objects , newArr);
           delete [] newArr;
           TheSize--;
    };

    private:
    static const int SPARE_CAPACITY = 16;
    int TheSize;
    int TheCapacity;
    Object* objects; //waiting a chunk of memeory to catch 

    void resize(int newSize){
        if(newSize > TheCapacity){
            reserve( 2 * newSize);
        };
        TheSize = newSize;
    };

    void reserve(int newCapacity){
        if(newCapacity < TheSize){
            return ;
        };

        Object* oldArr = objects;
        objects = new Object[newCapacity];
        for(int i = 0 ; i < size() ; i ++){
            objects = oldArr; //that's mean that i increased the capacity 
        };

        TheCapacity = newCapacity;
        delete [] oldArr;

    };

    

};

#endif // !VECTOR_H
