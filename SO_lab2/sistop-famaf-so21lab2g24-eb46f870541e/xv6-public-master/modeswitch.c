#include "types.h"
#include "stat.h"
#include "user.h"


int
main(int argc, char *argv[])
{
  if (argc < 2) {
      printf(1, "error: too few arguments\n");
  } else {
      int mode = argv[1][0] - '0';
      mode = mode;
      modeswitch(mode);
  }

  exit();
}

