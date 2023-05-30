# EvalutionCity<a name="into"></a>

C++ evaluation for City Bank pre-recrutement test. Content:

1. [Memory leak](#leak)
2. [Diamond problem](#diamond)
3. [Friend function](#friend)


# 1/ What is a memory leak? Write a sample of code to and a solution to prevent memory leak <a name="leak"></a>

A memory leak is a type of software bug that occurs when a program fails to release memory that is not needed anymore.

Memory leaks can gradually consume increasing amounts of memory over time, eventually leading to memory exhaustion as the following example.

The solution is to free memory as soon as it is no longer needed or accessible.

The [following C++ code](1_leak.cpp) showcases a memory leak

```cpp
#include <stdio.h>

char* allocate(long size) {
  return new char[size];
}

int main(int argc, char* argv[]){
  for (int i = 0; i < 100000; ++i) {
    char* ptr = allocate(10000000000);
    // delete ptr;  // Uncomment me to fix <--------- HERE
  }
  return 0;
}
```

Compiling and running it with this shell command ...

```sh
g++ 1_leak.cpp -o 1_leak && ./1_leak; echo $?
```

... leads to the following runtime crash:

```text
terminate called after throwing an instance of 'std::bad_alloc'
  what():  std::bad_alloc
Aborted (core dumped)
134
```

But uncommenting the "delete ptr;" line makes it work until the end.


### More on memory leaks

* [Definition of memory leak (Wikipedia)](https://en.wikipedia.org/wiki/Memory_leak)
* [Advices to avoid memory leaks in C++ (GeeksForGeeks)](https://www.geeksforgeeks.org/memory-leak-in-c-and-how-to-avoid-it)


# 2 How do you overcome diamond problem in C++? <a name="diamond"></a>

The diamond problem refers to a situation where a class inherits from two or more classes that have a common base class.
As a result, there can be ambiguity and conflicts when accessing members or methods inherited from the common base class.
This occurs because each intermediate class along the inheritance hierarchy may contain its own copy of the inherited members.

To overcome the diamond problem, the virtual inheritance mechanism is used.
It allows the derived class to inherit the common base class only once, regardless of how many intermediate classes are involved.
The compiler can correctly resolve member access and method calls in the inheritance hierarchy.

The [following C++ code](2_diamond.cpp) showcases a diamond problem

```cpp
#include <iostream>
using namespace std;

class A                          { public: virtual void eat(){ cout<<"A";} }; 
class B: /* virtual */ public A  { public: virtual void eat(){ cout<<"B";} }; 
class C: /* virtual */ public A  { public: virtual void eat(){ cout<<"C";} }; 
class D: public B,C              { public: virtual void eat(){ cout<<"D";} }; 

int main(){ 
    A *a = new D(); 
    a->eat(); 
} 
```

Compiling and running it with this shell command ...

```sh
g++ 2_diamond.cpp -o 2_diamond && ./2_diamond; echo $?
```

... leads to the following compilation error:

```text
2_diamond.cpp: In function ‘int main()’:
2_diamond.cpp:11:18: error: ‘A’ is an ambiguous base of ‘D’
   11 |     A *a = new D();
      |                  ^
1
```

But uncommenting the __two__ "virtual" tokens makes it work and outputs `D`.

### More on diamond problem

* [Definition of the diamond problem (Wikipedia)](https://en.wikipedia.org/wiki/Multiple_inheritance#The_diamond_problem)
* [Source of code (Stackoverflow)](https://stackoverflow.com/questions/2659116/)
# 3 What is a friend function and when should a function be made friend? Please write a simple code as an example of it. <a name="friend"></a>

A friend function defined outside a class scope but with the rights to access all the members of this class, even members with restrictions (private and protected).

Friends functions are used when access to private data of a class are required.

The [following C++ code](3_friend.cpp) showcases a friend class

```cpp
#include <iostream>
#include <string.h>
using namespace std;

class SecretStore {
private:
  char password[0x100];
  friend bool doMatch(const SecretStore ss, const char* reference);
public:
  SecretStore(const char* user_password){
    strcpy(password, user_password);
  }
};

bool doMatch(const SecretStore ss, const char* reference){
  return 0 == strcmp(ss.password, reference);
}

int main(){
  bool ret = false;
  SecretStore* ss = new SecretStore("my password 2");
  ret = doMatch(*ss, "my password 1");
  printf("The first string match? %s\n", ret ? "true" : "false");

  ret = doMatch(*ss, "my password 2");
  printf("The second string match? %s\n", ret ? "true" : "false");

  delete ss;
}
```

Compiling and running it with this shell command ...

```sh
g++ 3_friend.cpp -o 3_friend && ./3_friend; echo $?
```

... leads to the following output:

```text
The first string match? false
The second string match? true
0
``

### More on friend functions

* [Definition of friend function (Wikipedia)](https://en.wikipedia.org/wiki/Friend_function)
