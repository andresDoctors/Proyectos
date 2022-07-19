#include "types.h"
#include "stat.h"
#include "user.h"


int
main(int argc, char *argv[]) 
{
  if (argc < 4) {
      printf(1, "error: too few arguments\n");
  } 
  else 
  {
    int x,y,color;
    x=atoi(argv[1]);
    x=x;
    y=atoi(argv[2]);
    y=y;
    color=atoi(argv[3]);
    color=color;
    plotpixel(x,y,color);
  }
  exit();
}

