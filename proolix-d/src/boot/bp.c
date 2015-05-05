#define VER "Boot Processor Feb'2006 by S.Pustovoitoff"

/* $Id: BP.C,v 1.4 2006/02/05 21:53:53 Pr00l Exp $ */

/* �����:
0.1.8  31-Aug-2003 - ��ࠢ���� �訡�� �� �뢮�� ����஢ ᥪ�஢ � 樫���஢
0.1.7  28-May-2003
0.1.6   2-Nov-99 - ������⢥��� (��ᬥ��᪨�) ����䨪�樨
0.1.5  10-Mar-98
0.1.4  24-Feb-98 - ᤥ���� ࠡ�� � ������᫥��묨 extended partition
0.1.3  16-Jan-98 - ᤥ���� ࠡ�� � extended partition
0.1.2  11-Jan-98
0.1.1   7-Jan-98
0.1.0  28-Dec-97 - add bootread() instead of absread(), add outMBR,
                   add bootwrite() instead of abswrite()
0.0.20 32-Aug-97 - fixed small bug
0.0.19 24-Aug-97 - MSDOS/Proolix version
0.0.18 22-Aug-97
0.0.17 27-Apr-97
0.0.16 26-Apr-97
0.0.15  3-Apr-96
0.0.14 24-Sep-95
0.0.14 24-Sep-95
0.0.13 16-Sep-95
0.0.13 15-Sep-95 - ��ࠢ���� ������� �訡�� �� ࠡ�� � ���⪨�� ��᪠��
0.0.12 21-Mar-95 - ������� ��ᬥ⨪� �� ᮢ��� Mike Aizatsky, 2:461/21.100
0.0.11 26-Nov-94 - �ࠫ progname(). H�䨣� ��� �뫠 �㦭�!?
0.0.10 19-Nov-94 - ��᫥ -d �������� �� ᨬ���
0.0.9   5-Sep-94 - -y switch
0.0.8   3-Sep-94 - �뢮� ����� 䠩�� InName
0.0.7  26-Jan-94
0.0.6  10-Jan-94 putch__()
0.0.5  23-Dec-93
0.0.4  11 Dec 93 rename to BP - Boot Processor
0.0.3
0.0.2   7 Dec 93
0.0.1   6 Dec 93 add out_boot(), -d switch
0.0.0   2 dec 93

�� �⮣� �� Buffered MonoPIP 2.04 22 Nov 93

*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <conio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dos.h>

#undef OPEN_MAX
#undef TMP_MAX

#include "..\include\prool.h"

#if     !defined(__FAT_CODES_)
#define __FAT_CODES_

#define FAT12           0
#define FAT16           1
#define NO_FAT          2
#define FAT32           3
#define FAT32LBA        4

#endif

#define __TIME_DATE_
#define _FTIME_
#include "..\include\conf.c"
#include "..\include\limits.h"
#include "..\include\struct.h"

#define SECSIZE 512
#define _HDD_ 0x80

                    /* Global definitions */

char buf [SECSIZE], bufboot[SECSIZE];
char    FlagR = 0;
char    FlagI = 0;
char    FlagY = 0;
char    FlagT = 0;
char    dev = 0xF0;
int NextDrive=2;
int NextDOSDrive='C';
struct DeviceStruct Devices [LASTDRIVE];
  /*
        Devices [0] - disk A: sec=0 if not present
        Devices [1] - disk B: sec=0 if not present
        Devices [2] - disk C: sec=0 if not present
        Devices [3] - disk D: sec=0 if not present
        ...
        */
int active=-1;

int bootread0 (int dev, void far * buf);
int bootwrite (int dev, void far * buf);
int ReadPhysSec (unsigned char drive, unsigned char sec, unsigned char head,
                 unsigned char trk /* or cyl */, char *Buffer);
int WritePhysSec (unsigned char drive, unsigned char sec, unsigned char head,
                 unsigned char trk /* or cyl */, char *Buffer);

#include "..\kernel\out_os.c"
#include "..\kernel\out_mbr.c"

int bootread (int Dev, void *Buf)
{int i, err;
char InternalBuffer [SECTOR_SIZE];
for (i=0; i<RETRYES; i++)
  {
  err = bootread0 (Dev,InternalBuffer);
  if (!err)
    {
    memcpy(Buf,InternalBuffer,SECTOR_SIZE);
    return 0;
    }
  }
return -1;
}

int ReadPhysSec2 (unsigned char drive, unsigned char sec, unsigned char head,
                  unsigned char trk /* or cyl */,
                  void *Buf)

{int i, err;

for (i=0; i<RETRYES; i++)
  {
  err = ReadPhysSec (drive, sec, head, trk, Buf);
  if (!err) return 0;
  }
return -1;
}

char *sector_type (int dev)
{
if (dev==0xFF) return "master boot";
return "boot";
}

int reply(char *str)
{
int c,i;
  while (1)
  {c=getche() & 0xdf;
  for (i=0; str[i]!='\0';)
    if ((char)c==str[i++])
      {putch(13);putch(10);return i;}
  putch(7);
  }
}

void ident(void)
{
printf(VER);
}

void help(void)
{
puts("\n\nusage: bp -d<drive_char> [filename] [-r] [-i] [-a<digit>] [-y]\n\
-r - reverse copy (file->boot/master boot sector),\n\
DEFAULT (without '-r') - boot/master boot sector->file\n\
\n\
-i - install file to boot/master boot sector,\n\
     BPB and partition table not change!\n\
-d<char> - drive:\n\
           @ - master boot record of 1st HDD\n\
           Boot records:\n\
           0 - drive 0 (floppy drive A:)\n\
           1 - drive 1 (floppy drive B:)\n\
           2 - drive 2 (1st partition of 1st HDD)\n\
           ...\n\
-a<digit> - set active partition (for extended partition only)\n\
-t - print partitions and nothing\n\
-y - assume 'y' on all queries\n");
}

putch__(char c)
{
switch (c)
  {
  case 0: c=' '; break;
  default: if (c<' ') c='.';
  }
return putch(c);
}

void out_devices(void)
{int i;
unsigned int j;

printf("\nDev  Head Sec Trk/cyl Partition");
printf("\n-------------------------------");
for (i=0;i<LASTDRIVE;i++)
  {
  if (Devices[i].sec)
    {
    printf("\n%2i ",i);
    printf("   ");
    switch (i)
      {
      case 0:
      case 1:  printf("floppy drive"); break;
      default: /* printf("%i ",Devices[i].FileSystem); */ /* FAT12, FAT16 */
               printf("%4i ",Devices[i].head);
               printf("%3i ",(j=Devices[i].sec) & 0x3F);
               j = (j & 0xC0)<<2;
               printf("%4i     ",Devices[i].trk | j);
               out_os(Devices[i].system_indicator);
               printf(" (%02X)",(unsigned char)Devices[i].system_indicator);
               if (Devices[i].dos_disk!=' ')
                 {
                 printf(" %c:",Devices[i].dos_disk);
                 switch (Devices[i].FileSystem)
                   {
                   case FAT12: printf(" FAT-12"); break;
                   case FAT16: printf(" FAT-16"); break;
                   default: ;
                   }
                 }
               /* printf("%6lu ",Devices[i].ResSecs); */
               /* printf("%6lu",Devices[i].MaxSectors); */
      }
    }
  }
printf("\n");
}

void out_boot(void far *buf)

{int i;
unsigned long DiskSize;
unsigned long TrueSectors;
struct BootStru far *b;
b=buf;
printf("Jump command %02X %02X %02X  \n",(*b).Jmp[0],(*b).Jmp[1],(*b).Jmp[2]);
printf("OEM name     %-8s\n\
OEM name     ",(*b).OEM);

for(i=0;i<8;) printf("%02X ",(*b).OEM[i++]);

#if 1
printf("\nSector size                      %4i bytes Cluster size                %1i sect\n",(*b).SectSiz,(*b).ClustSiz);
printf("Reserved sectors (before 1st FAT)  %2i       FAT counter                 %1i\n",(*b).ResSecs,(*b).FatCnt);
printf("Root directory entries           %4i       Total sectors         %7u\n",(*b).RootSiz,(*b).TotSecs);
printf("Media descr                        %02X       FAT size                %5i sect\n",(*b).Media,(*b).FatSize);
printf("Track size                         %2i sec   Heads                     %3i\n",(*b).TrkSecs,(*b).HeadCnt);
printf("Hidden sectors                %7li       Big Number Of Sectors %7li\n",(*b).HidnSec,(*b).BigSect);
printf("Physical Drive No                  %02X       ",(*b).DriveNo);
printf("Reserved byte              %02X \n",(*b).Thing);
printf("Extended Boot Signature            %02X       ",(*b).BootSign);
printf("Volume Serial No %04X-%04X",
(*b).SerialNo[1],
(*b).SerialNo[0]);
#endif

printf("\nVolume Label (in boot)  ");
for(i=0;i<11;)putch__((*b).VolLbl[i++]);
printf("\n                        ");
for(i=0;i<11;)printf("%02X ",(*b).VolLbl[i++]);
printf("\nFile system Id          ");
for(i=0;i<8;)putch__((*b).FileSysId[i++]);
printf("\n                        ");
for(i=0;i<8;)printf("%02X ",(*b).FileSysId[i++]);

if ((*b).TotSecs==0) TrueSectors=(*b).BigSect;
else TrueSectors=(*b).TotSecs;

DiskSize=((long) (*b).SectSiz * TrueSectors)/1024l;

if (DiskSize>5000)
  {
  DiskSize/=1024;
  printf("\nDisk size %li Mb\n",DiskSize);
  }
else
  {
  printf("\nDisk size %li Kb\n",DiskSize);
  }

}

#define EXTEND 5
#define EXTEND2 0xF

int extended_partition(int dev)
{
if (dev==0xFF) return 1;
if ((Devices[dev].system_indicator==EXTEND ) ||
    (Devices[dev].system_indicator==EXTEND2)    )
   return 1;
return 0;
}

void out_boot_or_mbr (int dev, void far *buf)
{
if (extended_partition(dev)) outMBR(buf);
else                         out_boot(buf);
}

#include "..\kernel\ppt.c"

void test_devices (void)
{unsigned int i;
struct MBRstru *MBR;
char MBRBuf [SECTOR_SIZE];

for (i=0;i<LASTDRIVE;i++)
  {
  Devices[i].sec=0;
  Devices[i].dos_disk=' ';
  }

/* �� [Tech Help]

����������������������������������������������������������������������������ͻ
�                             ���᮪ ����㤮�����                            �
����������������������������������������������������������������������������ͼ
��� ᯨ᮪ ����뢠�� ��⠭�������� ��� ��⨢��� ����㤮�����. �� �����頥���
���뢠���� INT 11H (� AX) � �࠭���� �।� ������ BIOS �� ����� 0:0410.
 1 1 1 1 1 1
�5�4�3�2�1�0�9�8�7�6�5�4�3�2�1�0�  �맮��� INT 11H ��� �������� ᫮�� 0:0410
�prt� �j� aux � �drv�vid�RAM� � �
�������������������������������ҽ ���                                  ��᪠
 �˼ � � ���ͼ � �˼ �˼ �˼ � ��> 0: 0 = ��� ��᪮��� ���ன��    (AX & 0001H)
  �  � �   �   �  �   �   �  ����> 1: 8087 ᮯ����� (���������)
  �  � �   �   �  �   �   �������> 2-3: ���ਭ᪠� ���� RAM       (AX & 0eH)
  �  � �   �   �  �   �                 01H=16K; 04H=32K; 0eH=64K (��� �����)
  �  � �   �   �  �   �����������> 4-5: ��砫��/��⨢�� ०��    (AX & 0030H)
  �  � �   �   �  �                     10H=40-��� 梥�; 20H=80-��� 梥�;
  �  � �   �   �  �                     30H=TTL �����஬��� ����
  �  � �   �   �  ���������������> 6-7: �ᥣ� ��᪮����� -1         (AX & 00c0H)
  �  � �   �   �                        00H=1; 40H=2; 80H=3; c0H=4
  �  � �   �   ������������������> 8: DMA ���������              (AX & 0100H)
  �  � �   ����������������������> 9-11: RS232 �����                (AX & 0e00H)
  �  � �                                 000H=���; 200H=1; 400H=2; ... e00H=7
  �  � ��������������������������>12: 1=��஢�� ������ ���������(AX & 1000H)
  �  ����������������������������>13: 1=��᫥�.�ਭ�� (PC/Jr ⮫쪮)
  �������������������������������>14-15: ��⠭������ �ਭ�஢      (AX & c000H)
                                         0000H=���; 4000H=1; 8000H=2; c000H=3

�����: ���� �ᯮ������ ��� �஢�ન ०��� �����. �᫨ (AX & 30H) = 30H, �
       ������ �����஬���Ģ���� ᥣ���� RAM �� ����� 0b000H, ���� 0b800H.

*/

i=((*(unsigned int far *)MK_FP(0,0x410) & 0xC0)>>6)+1;
if (i) Devices[0].sec=-1;
if (i>1) Devices[1].sec=-1;

if (bootread0 (_HDD_, MBRBuf))
  printf ("test_devices: MBR read error\n");

process_partition_table (MBRBuf);

}

int read_boot_or_mbr (int dev, char *buf)
{
int sec;

if ((dev==0)||(dev==1))
  { /* A: or B: */
  return bootread(dev,buf);
  }
if (dev==0xFF)
  {
  return bootread(_HDD_,buf);
  }
sec=Devices[dev].sec;
if (sec==0) return -1;
return ReadPhysSec (_HDD_,sec,Devices[dev].head,Devices[dev].trk,buf);
}

int write_boot_or_mbr (int dev, void *buf)
{
int sec;

if ((dev==0)||(dev==1))
  { /* A: or B: */
  return bootwrite(dev,buf);
  }
if (dev==0xFF)
  {
  return bootwrite(_HDD_,buf);
  }
sec=Devices[dev].sec;
if (sec==0) return -1;
return WritePhysSec (_HDD_,sec,Devices[dev].head,Devices[dev].trk,buf);
}

int main (int argc, char *argv[] /* , char *env[] */)
{
int i;
int  FileNameCounter;
char InName [80];
int  h;
struct MBRstru *mbr_p;

#if 1
clrscr();
#else
for (i=0;i<25;i++)puts("");
#endif

ident();

if (argc==1)
        {
        help();
        return 1;
        }

FileNameCounter=0;
for(i=1;i<argc;i++)
  {
  if(argv[i][0]=='-')
      switch (argv[i][1])
        {
        case 'r': FlagR++; break;
        case 'i': FlagI++; break;
        case 'y': FlagY++; break;
        case 't': FlagT++; break;
        case 'd':   {char c;
                    c=argv[i][2];
                    if (c=='@') dev=0xFF;
                    else dev=c-'0';
                    }
                  break;
        case 'a': active=argv[i][2]-'0'; break;
        default : printf("\nInvalid switch"); help(); return 1;
        }
    else
      if (FileNameCounter==0)
        {
        strcpy(InName,argv[i]);
        FileNameCounter++;
        }
  }

if (FileNameCounter==0)
  strcpy(InName,"/dev/nul");

test_devices();

out_devices();

if (FlagT) return 0;

if (FlagI)
 { /* Install Boot or MBR */
 if (read_boot_or_mbr(dev,bufboot)==-1) {printf("Disk read error\n"); return 2; }
 out_boot_or_mbr(dev,bufboot);
 for(i=0;i<SECSIZE;) buf[i++]=0;
 if((h=open(InName,O_RDONLY|O_BINARY))==-1) {printf("Boot image open error in file %s\n",InName); return 2;}
 if((i=(int)read(h,buf,SECSIZE))==-1) {printf("Boot image read error\n"); return 2;}
 printf("Read %i bytes",i); if (i>=SECSIZE) printf(" or more\n"); else printf("\n");
 if (i>SECSIZE) {printf("Not enough memory in boot sector\n");return 2;}
 else if (i>510) printf("Warning! Last 1-2 bytes lost!\n");
 close(h);

 if (extended_partition(dev))
   { /* MBR or extended partition */
   for (i=0;i<0x1BE;i++)bufboot[i]=buf[i]; /* bootloader */
   if ((active>=0)&&(active<4))
     { /* set active partition */
     mbr_p=(void *)bufboot;
     mbr_p->Partition[active].indicator=0x80;
     out_boot_or_mbr(dev,bufboot);
     }
   }
 else
   { /* plain boot sector */
   for (i=0;i<3+8;i++)bufboot[i]=buf[i]; /* JMP and OEM name */
   for (i=0x26; i<SECSIZE-2; i++) bufboot[i]=buf[i]; /* bootloader */
   }
 bufboot[SECSIZE-2]=0x55;
 bufboot[SECSIZE-1]=0xaa;

 if (!FlagY)
   {
   printf("File %s -> %s sector %i:\n\nOverwrite %s sector (y/n) ? ",
   InName,sector_type(dev),dev,sector_type(dev));
   if (reply("YN")!=1) return 1;
   }
 printf("\nFile %s -> %s sector %i: !\n",
        InName,sector_type(dev),dev);

 if (write_boot_or_mbr(dev,bufboot)){printf("Disk write error\n"); return 2;}

 }
else if (!FlagR)
 { /* boot -> file */
 printf("%s sector %i: -> file %s\n",sector_type(dev),dev,InName);
 if(read_boot_or_mbr(dev,buf)==-1){printf("Disk read error\n"); return 2;}
 out_boot_or_mbr(dev,buf);
 if((h=open(InName,O_CREAT|O_WRONLY|O_BINARY,S_IWRITE))==-1)
   {printf("Boot image open/creat error in file %s\n",InName); return 2;}
 if(write(h,buf,SECSIZE)!=SECSIZE)
   {printf("Boot image write error\n"); return 2;}
 if(close(h)) {printf("Boot image close error\n"); return 2;}
 }
else
 { /* file -> boot */
 if (!FlagY)
   {
   printf("File %s -> %s sector %i:\n\nOverwrite %s sector (y/n) ? ",
   InName,sector_type(dev),dev,sector_type(dev));
   if(reply("YN")!=1)return 1;
   }
 printf("\nFile %s -> %s sector %i: !\n",
        InName,sector_type(dev),dev);
 if((h=open(InName,O_RDONLY|O_BINARY))==-1)
   {printf("Boot image open error in file %s\n",InName); return 2;}
 if(read(h,buf,SECSIZE)!=SECSIZE)
   {printf("Boot image read error\n"); return 2;}
 out_boot_or_mbr(dev,buf);
 if(close(h)) {printf("Boot image close error\n"); return 2;}
 if(write_boot_or_mbr(dev,buf)){printf("Disk write error\n"); return 2;}
 }

return 0;
}