/*      struct.h

        Proolix Kernel structures (struct)

        Copyright (c) Serge Pustovoitoff 1994, 1995

*/

#ifndef LIMITS_H
#include "limits.h"
#endif

#ifndef _IO_H
#include <io.h>
#endif

#if     !defined(__TIME_DATE_)
#define __TIME_DATE_

struct  time    {
        unsigned char   ti_min;         /* Minutes */
        unsigned char   ti_hour;        /* Hours */
        unsigned char   ti_hund;        /* Hundredths of seconds */
        unsigned char   ti_sec;         /* Seconds */
};

struct  date    {
        int             da_year;        /* Year - 1980 */
        char            da_day;         /* Day of the month */
        char            da_mon;         /* Month (1 = Jan) */
};
#endif

#ifndef STRUCT_H
#define STRUCT_H

struct MemBlk
{
char Type;
unsigned int  OwnerPar;
unsigned int  SizePar;
};

/*
struct TimeField
{
unsigned int Sec2     : 5;
unsigned int Min      : 6;
unsigned int Hour     : 5;
};

struct DateField
{
unsigned int Day      : 5;
unsigned int Month    : 4;
unsigned int Year     : 7;
};
  */

struct BootStru /* structure of boot sector of FAT12 and FAT16*/
  {
  unsigned char Jmp [3];
  unsigned char OEM [8];
  int  SectSiz;
  char ClustSiz;
  int  ResSecs;
  char FatCnt;
  int  RootSiz;
  unsigned int  TotSecs;
  unsigned char Media;
  int  FatSize;
  int  TrkSecs;
  int  HeadCnt;
  unsigned long HidnSec;
  unsigned long BigSect;
  unsigned char DriveNo;
  unsigned char Thing;
  unsigned char BootSign;
  int  SerialNo [2];
  unsigned char VolLbl [11];
  unsigned char FileSysId [8];
  /*
  int  FATaddr;
  int  StartClu;
  int  RootSize;
  */
  };

struct BootStru32 /* structure of boot sector of FAT32*/
  {
  unsigned char Jmp [3];
  unsigned char OEM [8];
  int  SectSiz;
  char ClustSiz;
  int  ResSecs;
  char FatCnt;
  int  RootSiz;
  unsigned int  TotSecs;
  unsigned char Media;
  int  FatSize;
  int  TrkSecs;
  int  HeadCnt;
  unsigned long HidnSec;
  unsigned long BigSect;
  unsigned long BigFATSize;
  unsigned int ExtendedFlags;
  unsigned int FilesystemVer;
  unsigned long RootBegClu;
  unsigned int AuxSector;
  unsigned int CopySector;
  unsigned char Reserved[12];
  unsigned char String[8];
  };

struct Partition_stru
  {
  unsigned char   indicator;
        /*
        00  - non-bootable partition
        80  - bootable partition (one partition only)
        */
  unsigned char   begin_head;
  unsigned char   begin_sec; /* and 2 high bits of cylinder # */
  unsigned char   begin_cyl; /* low order bits of cylinder # */
        /*
        2 bytes are combined to a word similar to INT 13:

        񽼖񽔼񼭢񼆈� 1st byte  (sector)
         � � 滥聊聊聊聊聊� Sector offset within cylinder
         滥聊哪哪哪哪哪哪 High order bits of cylinder #

        񽼖񽔼񼭢񼆈� 2nd byte  (cylinder)
         滥聊聊聊聊聊聊哪哪 Low order bits of cylinder #
         */
  unsigned char   system_indicator;
  unsigned char   end_head;
  unsigned char   end_sec; /* and 2 high bits of cylinder # */
  unsigned char   end_cyl; /* low order bits of cylinder # */
  unsigned long   preceding_sec;
  unsigned long   total_sec;
  };

struct MBRstru
  {
  char master_boot_loader [0x1BE];
  struct Partition_stru Partition [4];
  unsigned int Signature; /* 55AA */
  };

struct DevRecord
  {
  char *Name;
  int   Major;
  int   Minor;
  char  Byte; /* 1 - byte-oriented device, 0 - block-oriented */
  };

struct DevByte
  {
  void (*dev_open)  ();
  void (*dev_close) ();
  void (*dev_read)  ();
  void (*dev_write) ();
  void (*dev_ioctl) ();
  };

struct DevBlock
  {
  void (*dev_open)     ();
  void (*dev_close)    ();
  void (*dev_strategy) ();
  };

/* 戔嚆汔� 鉅～ㄦ� メ岙� */
#include <setjmp.h>
struct processes
  {
  int pid;
  int status; /* 1 - 牚猕ⅴ�, 0 - 牚猕ⅴ� (ǐ� Δモ) */
  int wait; /* pid メ釥 (鏍), 猱嚯� Δモ 鐮� 礅� メ釥
               ǐ� 0, メ �  Δモ */
  jmp_buf control_point;
  char huge *mem0;
  };

/* 慝ガキ� °浈喹� 珷 */
struct BufPool
  {
  unsigned long Sec;
  unsigned int Status; /* 戔犫汜 °浈酄:
    0 - 幄�, 1 - キ�, 2 - ě氅 */
  unsigned int Counter;
  unsigned char M [SECTOR_SIZE];
  };

struct reloc
  {
  unsigned int offset;
  unsigned int segment;
  };

/* ．� ㄡ铳． EXE 錉┇� (獱� � MSDOS) */
struct exe_header
{                     /* キ鉅啜� ě [TECH Help!] */
char MZ[2];           /* "くㄡ�" 錉┇� .EXE ('MZ') */
unsigned int PartPag; /* かō�  岖イ� 徕酄骐 (腌 ǎ啜嚆モ犸) */
unsigned int PageCnt; /* かō� 酄 � 512-┾脲 徕酄鏍�, ⅹ鐮� ．� */
unsigned int ReloCnt; /* 绋岖� 慝ガキ猱� � 鉅～ㄦ� 啷楗� */
unsigned int HdrSize; /* かō� ．ⅹ� � 16-┾脲 癄酄｀犱犲 */
unsigned int MinMem;  /* � 忄ァ悭� 癄猕   酄� (癄酄｀犱�) */
unsigned int MaxMem;  /* 瑺ì悻 忄ァ悭� 癄猕   酄� (癄酄｀犱�) */
unsigned int ReloSS;  /* 幞，キ猸 岈ラキē 幞，キ鉅 徕オ� (か� 汜鉅ⅹ� SS) */
unsigned int ExeSP;   /* Л犵キē 啷（徕酄 SP (悛牕犫カ� 徕オ�) � 岐� */
unsigned int ChkSum;  /* 喈瓲� 徙� (啜鏍猊瓲� 徙� ⑨ュ 岖 � 錉┇�) */
unsigned int ExeIP;   /* Л犵キē 啷（徕酄 IP (悛牕犫カ� 瑺) � 岐� */
unsigned int ReloCS;  /* 幞，キ猸 岈ラキē ぎ． 幞，キ鉅 (か� 汜鉅ⅹ� CS) */
unsigned int TablOff; /* 岈ラキē � 錉┇� 1-． 慝ガキ鉅 啷楗� (鐮徕� 001cH) */
unsigned int Overlay; /* � ム� (0 か� ＋牏． ゃ) */
struct reloc RelTbl [];
};

struct DeviceStruct
  {
  char FileSystem;
  int head;
  int sec;
  int trk;
  unsigned long ResSecs;
  unsigned long MaxSectors;
  char dos_disk; /* 'A' 'B' 'C' 'D' ... */
  char system_indicator;
  };

#endif