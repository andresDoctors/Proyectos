#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{

  modeswitch(0);

  int j=0,i=0;
  for(j=0;j<320;++j)
    for(i=0; i<200; ++i)
      plotpixel(j,i,0);

  for(j=111;j<130;++j)//mochila
    for(i=50; i<110; ++i)
      plotpixel(j,i,4);

  for(j=135;j<208;++j)//torso
    for(i=14; i<166; ++i)
      plotpixel(j,i,4);

  for(j=170;j<180;++j)//limpiar
    for(i=140; i<166; ++i)
      plotpixel(j,i,0);

  for(j=135;j<140;++j)//limpiar
    for(i=14; i<19; ++i)
      plotpixel(j,i,0);

  for(j=204;j<209;++j)//limpiar
    for(i=14; i<19; ++i)
      plotpixel(j,i,0);

  for(j=179;j<226;++j)//visor
    for(i=33; i<53; ++i)
      plotpixel(j,i,3);

  for(j=105;j<111;++j)//contorno #1
    for(i=59; i<110; ++i)
      plotpixel(j,i,7);

  for(j=111;j<115;++j)//contorno #2
    for(i=50; i<59; ++i)
      plotpixel(j,i,7);

  for(j=111;j<130;++j)//contorno #3
    for(i=110; i<115; ++i)
      plotpixel(j,i,7);

  for(j=115;j<130;++j)//contorno #4
    for(i=46; i<50; ++i)
      plotpixel(j,i,7);

  for(j=130;j<135;++j)//contorno #5
    for(i=33; i<140; ++i)
      plotpixel(j,i,7);

  for(j=135;j<140;++j)//contorno #6
    for(i=19; i<33; ++i)
      plotpixel(j,i,7);

  for(j=135;j<141;++j)//contorno #7
    for(i=140; i<166; ++i)
      plotpixel(j,i,7);

  for(j=140;j<145;++j)//contorno #8
    for(i=14; i<23; ++i)
      plotpixel(j,i,7);

  for(j=145;j<150;++j)//contorno #9
    for(i=10; i<19; ++i)
      plotpixel(j,i,7);

  for(j=150;j<193;++j)//contorno #10
    for(i=10; i<15; ++i)
      plotpixel(j,i,7);

  for(j=193;j<198;++j)//contorno #11
    for(i=10; i<19; ++i)
      plotpixel(j,i,7);

  for(j=198;j<204;++j)//contorno #12
    for(i=14; i<23; ++i)
      plotpixel(j,i,7);

  for(j=204;j<209;++j)//contorno #13
    for(i=19; i<29; ++i)
      plotpixel(j,i,7);

  for(j=175;j<179;++j)//contorno #14
    for(i=33; i<53; ++i)
      plotpixel(j,i,7);

  for(j=179;j<183;++j)//contorno #15
    for(i=29; i<36; ++i)
      plotpixel(j,i,7);

  for(j=183;j<221;++j)//contorno #16
    for(i=29; i<33; ++i)
      plotpixel(j,i,7);

  for(j=221;j<225;++j)//contorno #17
    for(i=29; i<36; ++i)
      plotpixel(j,i,7);

  for(j=225;j<230;++j)//contorno #18
    for(i=33; i<53; ++i)
      plotpixel(j,i,7);

  for(j=179;j<183;++j)//contorno #19
    for(i=50; i<57; ++i)
      plotpixel(j,i,7);

  for(j=183;j<221;++j)//contorno #20
    for(i=53; i<57; ++i)
      plotpixel(j,i,7);

  for(j=221;j<230;++j)//contorno #21
    for(i=50; i<53; ++i)
      plotpixel(j,i,7);

  for(j=208;j<213;++j)//contorno #22
    for(i=57; i<119; ++i)
      plotpixel(j,i,7);

  for(j=203;j<208;++j)//contorno #23
    for(i=119; i<166; ++i)
      plotpixel(j,i,7);

  for(j=142;j<163;++j)//contorno #24
    for(i=166; i<173; ++i)
      plotpixel(j,i,7);

  for(j=163;j<170;++j)//contorno #25
    for(i=134; i<166; ++i)
      plotpixel(j,i,7);

  for(j=170;j<193;++j)//contorno #26
    for(i=134; i<140; ++i)
      plotpixel(j,i,7);

  for(j=180;j<186;++j)//contorno #27
    for(i=140; i<166; ++i)
      plotpixel(j,i,7);

  for(j=186;j<203;++j)//contorno #28
    for(i=166; i<172; ++i)
      plotpixel(j,i,7);

      

  exit();
}

