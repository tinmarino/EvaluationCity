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
