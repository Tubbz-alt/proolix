#include <prool.h>

#include <conf.c>
#include "kernel.h"

int Int13perror(unsigned err);
/****************************************************************************/
/* #define DEBUG */
/* ����室��� ���㬠�� � ⮬, �� ���뢠�� � ��᪮� ����� �� ��ᥪ�୮,   */
/* � 楫묨 ��஦����. �� �㤥� ����॥.                                   */
/****************************************************************************/
extern unsigned char NearBuffer [SECTOR_SIZE]; /* defined in c0.asm */
/****************************************************************************/
int secread (int drive, unsigned long AbsSec, char *Buffer)
{/* Read absolute sectors
Input:
drive (for int 13h Fn=2)
abs sec number
buffer

Output: return!=0 if error
*/
int Track, SecNoOnCyl, i;
char Head, SecOnTrk;

Track=(int)(AbsSec/SectorsOnCyl); /*SectorsOnCyl=HeadCnt*TrkSecs,Track==Cyl */
SecNoOnCyl=(int)(AbsSec%SectorsOnCyl);
Head=SecNoOnCyl/TrkSecs;
SecOnTrk=SecNoOnCyl%TrkSecs+1;
       /*
       2 bytes are combined to a word similar to INT 13:

       �7�6�5�4�3�2�1�0� 1st byte  (sector)
        � � ������������� Sector offset within cylinder
        ���������������� High order bits of cylinder #

       �7�6�5�4�3�2�1�0� 2nd byte  (cylinder)
        ������������������ Low order bits of cylinder #
        */
if ((i=Track &0x0300)!=0)
  {
  SecOnTrk = (SecOnTrk & 0x3F) | (int)(i>>2);
  }
return ReadPhysSec(drive, SecOnTrk, Head, Track, Buffer);
}
/****************************************************************************/
int absread (int drive, int nsects, unsigned long lsect, void far *FarBuffer)
{
int i, j, k;
unsigned err;

#ifdef DEBUG
printf("absread: lsect=%lu ",lsect);
#endif

for (i=0;i<nsects;i++,lsect++)
  {
  if (lsect>=MaxSectors)
    {
    #if 0
    printf("absread: lsect >=MaxSectors. lsect=%lu ",lsect);
    printf("MaxSectors=%lu\n",MaxSectors);
    #endif
    return -1;
    }
  while(1)
    {
    #ifdef DEBUG
    /* �� �஢�ઠ �� ������祭�� ���ᮬ �࠭��� 64�. ���� �⥭��/
    ������ 䫮��� ����� (DMA overload) */
    /* ���� �������� H� ������� !!! �� 㤫������ ���� �� ����� ����㯨�
    ����祭�� �࠭��� � ����� ���� �㤥� NearBuffer �㤠-� ��६���� */
    /* printf("absread: NearBuffer = %lX ",(long)NearBuffer); */
    #endif
    err=1;
    for (j=0;j<RETRYES;j++)
      if ((err=secread (drive, lsect, NearBuffer))==0) break;
    if (err)
      {err>>=8;
      printf("absread: error %2X in sec %li: ",err,lsect);
      Int13perror(err);
      printf(" Ignore (i), retry (r) or abort (a) ? ");
      j=getchar();
      puts("");
      if (j=='r') continue;
      else if (j=='a') return -1;
      else /* ignore */ break;
      }
    else
      break;
    }

  #if 1
  for (k=0;k<SECTOR_SIZE;k++)
    {
    *((char far *)FarBuffer)++=NearBuffer[k];
    /* putch('.'); */
    }
  #else
  memcpy(FarBuffer, NearBuffer, SECTOR_SIZE);
  #endif

  /* FarBuffer = (char huge *) FarBuffer + SECTOR_SIZE; */
  }
return 0;
}

#if 0
int far ff (int p)
{
return p;
}
#endif