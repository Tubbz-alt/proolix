// view exe (MZ) header. built under cygwin/64. prool

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFLEN 512


//#include "..\include\limits.h"

struct reloc
  {
  unsigned int offset;
  unsigned int segment;
  };

/* ��������� ������������ EXE ����� (��� � MSDOS) */
struct exe_header
{                     /* ����������� �� [TECH Help!] */
char MZ[2];           /* "�������" ����� .EXE ('MZ') */
unsigned short int PartPag; /* ����� �������� ��������� �������� (������ ������������) */
unsigned short int PageCnt; /* ����� ������ � 512-�������� ���������, ������� ��������� */
unsigned short int ReloCnt; /* ����� ��������� � ������� ����������� */
unsigned short int HdrSize; /* ����� ��������� � 16-�������� ���������� */
unsigned short int MinMem;  /* ������� ��������� ������ �� ������ ��������� (���������) */
unsigned short int MaxMem;  /* �������� ��������� ������ �� ������ ��������� (���������) */
unsigned short int ReloSS;  /* ���������� �������� �������� ����� (��� ��������� SS) */
unsigned short int ExeSP;   /* �������� �������� SP (��������� �����) ��� ������� */
unsigned short int ChkSum;  /* ����������� ����� (������������� ����� ���� ���� � �����) */
unsigned short int ExeIP;   /* �������� �������� IP (��������� ������) ��� ������� */
unsigned short int ReloCS;  /* ���������� �������� �������� �������� (��� ��������� CS) */
unsigned short int TablOff; /* �������� � ����� 1-�� �������� ����������� (����� 001cH) */
unsigned short int Overlay; /* ����� ������� (0 ��� �������� ������) */
struct reloc RelTbl [];
};

void ViewEXE (struct exe_header  *Buf)
{long i, j;
printf("Bytes on last page %04X\n",Buf->PartPag );
printf("Pages in file %04X\n",Buf->PageCnt );
printf("Relocations %04X\n",Buf->ReloCnt );
printf("Paragraph in header %04X\n",Buf->HdrSize );
printf("MinMem %04X par\n",Buf->MinMem  );
printf("MaxMem %04X par\n",Buf->MaxMem  );
printf("SS:SP %04X:%04X\n",Buf->ReloSS,Buf->ExeSP);
printf("CheckSum %04X\n",Buf->ChkSum  );
printf("CS:IP %04X:%04X\n",Buf->ReloCS,Buf->ExeIP);
printf("Relocation table addr %04X\n",Buf->TablOff );
/* printf("Overlay No. %1X\n",Buf->Overlay); */
}
/* �� [TECH Help!]

�============================================================================�
�                        ��������� ��������� ����� EXE                       �
L============================================================================-

����.  ����� ����������
------ ----- -----------------------------------------------------------------
            --------�
 +0      2  �4Dh 5aH� "�������" ����� .EXE ('MZ')
            +---+---+
 +2      2  �PartPag� ����� �������� ��������� �������� (������ ������������)
            +---+---+
 +4      2  �PageCnt� ����� ������ � 512-�������� ���������, ������� ���������
            +---+---+
 +6      2  �ReloCnt� ����� ��������� � ������� �����������
            +---+---+
 +8      2  �HdrSize� ����� ��������� � 16-�������� ����������
            +---+---+
+0aH     2  �MinMem � ������� ��������� ������ �� ������ ��������� (���������)
            +---+---+
+0cH     2  �MaxMem � �������� ��������� ������ �� ������ ��������� (���������)
            +---+---+
+0eH     2  �ReloSS � ���������� �������� �������� ����� (��� ��������� SS)
            +---+---+
+10H     2  �ExeSP  � �������� �������� SP (��������� �����) ��� �������
            +---+---+
+12H     2  �ChkSum � ����������� ����� (������������� ����� ���� ���� � �����)
            +---+---+
+14H     2  �ExeIP  � �������� �������� IP (��������� ������) ��� �������
            +---+---+
+16H     2  �ReloCS � ���������� �������� �������� �������� (��� ��������� CS)
            +---+---+
+18H     2  �TablOff� �������� � ����� 1-�� �������� ����������� (����� 001cH)
            +---+---+
+1aH     2  �Overlay� ����� ������� (0 ��� �������� ������)
            L---+----
1cH         ������ ��������������� ������ ��������� EXE
            --------T-------T - - T-------T-------� ������� �����������. ������
+ ?     4*? � ����.  �������  � ����.  ������� �� �������� [EXE+18H]. �����
            L---+---+---+---+ - - +---+---+---+---- [EXE+6] 4-�������� ��������.
+ ?     ?   ������� �� ������� ���������
+ ?     ?   ������ ������ ���������
--------------------------------------------------------------------------------
��������� EXE-���� ����� ���� �������� � ����� �������, ��� ���������� �������-
��� ������ (FAR CALL, ������� ���������, ������ ���� MOV AX,data_seg) ������
���� ��������� � ������� ������, ��������������� ��������. ���� ��������� ����,
������������ ���������� �������� DOS (������� 4bH ) ��� �������� ����� EXE:

1.  ������� PSP ����������� ������� DOS 26H

2.  ��������� 1cH ���� ����� EXE (��������������� ������ ��������� EXE)
    � ��������� ������� ������

3.  ���������� ������ ������ = ( (PageCnt*512)-(HdrSize*16) ) - PartPag

4.  ���������� �������� �������� ������������ ������ = (HdrSize * 16)

5.  ������� ���������� �����, START_SEG, ��� �������� (������  PSP + 10H)

6.  ������� ������ � ������� ������, ������������ � ������ START_SEG:0000

7.  LSEEK (���. ��������� �����) �� ������ ������� ����������� (TablOff)

8.  ��� ������� �������� ����������� (ReloCnt):
    a. ������� ������� ��� ��� 16-������� ����� (I_OFF,I_SEG)
    b. ��������� RELO_SEG=(START_SEG+I_SEG) (����� ������������ ������)
    c. ������� ����� �� ������ RELO_SEG:I_OFF (��������� ������� ��������)
    d. ��������� START_SEG � ����� ����� (��������� �������� ��������)
    e. ��������� ��������� ������� �� ��� ������ (RELO_SEG:I_OFF)

9.  ������������ ������ ��� ��������� �������� MaxMem � MinMem

10. ���������������� �������� � ��������� ���������:
    a. ES = DS = PSP
    b. AX = �������� ������������ ��������������� ������ � ��������� ������
    c. SS = START_SEG+ReloSS, SP = ExeSP
    d. CS = START_SEG+ReloCS, IP = ExeIP
    (�������: PUSH seg; PUSH offset; RETF)
 */

void ident (void)
{
printf("View EXE (MZ) ver. 0.0.0.2 by Prool, 17-aug-2015, cygwin/64\n\n");
}

void main (int argc, char *argv[])

{char buf [BUFLEN]; int h, i;

#if 0
printf("sizeof int = %i\n", sizeof (int));
printf("sizeof short int = %i\n", sizeof (short int));
#endif

if (argc!=2)
  {
  ident();
  printf("usage: vexe filename");
  }
else
  {
  if ((h=open(argv[1],O_RDONLY | O_BINARY))==-1)
    printf("Can't open %s\n",argv[1]);
  if ((i=read(h,buf,BUFLEN))!=BUFLEN)
    printf("Can't read %s. read()=%i\n",argv[1],i);
  close(h);
  printf("File %s\n\n",argv[1]);
  ViewEXE((void *)buf);
  printf("\n\n");
  ident();
  }
}
