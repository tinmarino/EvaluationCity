// From: https://stackoverflow.com/questions/2659116
#include <iostream>
using namespace std;

class A                          { public: virtual void eat(){ cout<<"A";} }; 
class B: virtual public A  { public: virtual void eat(){ cout<<"B";} }; 
class C: virtual public A  { public: virtual void eat(){ cout<<"C";} }; 
class D: public B,C              { public: virtual void eat(){ cout<<"D";} }; 

int main(){ 
    A *a = new D(); 
    a->eat();
} 
