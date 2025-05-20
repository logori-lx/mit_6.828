#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int i;
  for(i = 1; i < argc; i++){
    write(1, argv[i], strlen(argv[i]));
    // if there are still params need to be printed out
    // print a space after param
    if(i + 1 < argc){
      write(1, " ", 1);
    // if all the params have been printed out
    // print a new line after the param
    } else {
      write(1, "\n", 1);
    }
  }
  exit(0);
}
