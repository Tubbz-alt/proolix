#include <prool.h>
#include <dos.h>

#include <conf.c>

#include "kernel.h"

/* #define DEBUG */

/* NextClu(), NextClu2() - next cluster number compute and load to Cache) */
/* NextClu() - kernel's internal module */
/* NextClu2() - boot manager internal module */

/* �����ᮢ뢠�� NextClu() � NextClu2() ! */

unsigned long NextClu (unsigned long CluNo) /* -1 for eof or error */
{
unsigned long j;
unsigned long nsect;
unsigned int offset, b;
unsigned long i;

if ((CluNo>MaxClusters)||(CluNo==0))
  return -1;

switch (FATMode)
{
case FAT12:
  { /* FAT 12 */
  /* ��।��塞 ����� ���� � ⠡��� FAT-12 */
  j=(CluNo*3)/2;
  /* ��।��塞 ����� ᥪ�� FAT */
  nsect=(unsigned int)(j/SECTOR_SIZE);
  #ifdef DEBUG
  printf("nsect=%i ",nsect);
  #endif
  /* nsect-�⭮�⥫�� ����� ᥪ�� FAT. 0 - ���� ᥪ�� FAT */
  if (nsect>=FatSize) {puts("NextClu: Invalid FAT's computing"); return -1;}
  if ( (b=LoadCache(ResSecs+nsect)) == -1U )
    {puts("\nNextClu: FAT read error"); return -1;}

  offset=(unsigned int)(j%SECTOR_SIZE);
  #ifdef DEBUG
  printf("offset=%i ",offset);
  #endif
  if (offset==(SECTOR_SIZE-1))
    {unsigned char c;
    c=*(unsigned char far *)((*(Cache+b)).M+(SECTOR_SIZE-1));
    if ( (b=LoadCache(ResSecs+nsect+1)) == -1U )
      {puts("\nNextClu: FAT read error"); return -1;}
    #ifdef DEBUG
    printf("c=%04X ",c);
    #endif
    i=((unsigned int)c)|
    (((unsigned int)(*(unsigned char far *)((*(Cache+b)).M)))<<8);
    }
  else
    i=*(int far *)((*(Cache+b)).M+offset);
  #ifdef DEBUG
  printf("word=%04X ",i);
  #endif
  if (CluNo & 1)
    {
    #ifdef DEBUG
    putch('n');
    #endif
    i>>=4;
    }
  else
    {
    #ifdef DEBUG
    putch('c');
    #endif
    i&=0xfff;
    }
  if (i>0xff0) return -1;
  }
break;
case FAT16:
  { /* FAT 16 */
  /* ��।��塞 ����� ���� � ⠡��� FAT-16 */
  j=((long)CluNo)*2;
  /* ��।��塞 ����� ᥪ�� FAT */
  nsect=(unsigned int)(j/SECTOR_SIZE);
  /* nsect-�⭮�⥫�� ����� ᥪ�� FAT. 0 - ���� ᥪ�� FAT */
  if (nsect>=FatSize) {puts("NextClu: Invalid FAT's computing"); return -1;}
  if ( (b=LoadCache(ResSecs+nsect)) == -1U )
    {puts("\nNextClu: FAT read error"); return -1;}

  offset=(unsigned int)(j%SECTOR_SIZE);
  i=*(int far *)((*(Cache+b)).M+offset);
  if (i>0xfff0) return -1;
  }
break;
case FAT32:
case FAT32LBA:
  {
  /* ��।��塞 ����� ���� � ⠡��� FAT-32 */
  j=CluNo*4;
  /* ��।��塞 ����� ᥪ�� FAT */
  nsect=j/SECTOR_SIZE;
  /* nsect-�⭮�⥫�� ����� ᥪ�� FAT. 0 - ���� ᥪ�� FAT */
  if (nsect>=FatSize) {puts("NextClu: Invalid FAT's computing"); return -1;}
  if ( (b=LoadCache(ResSecs+nsect)) == -1U )
    {puts("\nNextClu: FAT read error"); return -1;}

  offset=(unsigned int)(j%SECTOR_SIZE);
  i=*(long far *)((*(Cache+b)).M+offset);
  if (i>0xfffffff0L) return -1;
  i=i&0x3FFFFFFFL;
  }
break;
default: ;
}

#if 0
printf("%i->%i ",CluNo,i);
#endif

return i;
}