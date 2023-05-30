#include <stdio.h>

char* allocate(long size) {
  // Allocate arg1 bytes
  char* ptr = new char[size];
  return ptr;
}

int main(int argc, char* argv[]){
  for (int i = 0; i < 100000; ++i) {
    printf("Loop: %d\n", i);
    char* ptr = allocate(10000000000);
    // delete ptr;  // Uncomment me to fix <--------- HERE
  }
  return 0;
}
