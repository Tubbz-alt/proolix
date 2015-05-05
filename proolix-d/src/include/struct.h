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

        �7�6�5�4�3�2�1�0� 1st byte  (sector)
         � � ������������� Sector offset within cylinder
         ���������������� High order bits of cylinder #

        �7�6�5�4�3�2�1�0� 2nd byte  (cylinder)
         ������������������ Low order bits of cylinder #
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

/* ������� ⠡���� ����ᮢ */
#include <setjmp.h>
struct processes
  {
  int pid;
  int status; /* 1 - ��⨢��, 0 - ����⨢�� (��� ����) */
  int wait; /* pid ����� (���), ����� ���� ����砭�� �⮣� �����
               ��� 0, �᫨ ���� �� ���� */
  jmp_buf control_point;
  char huge *mem0;
  };

/* ����� ���୮�� �㫠 */
struct BufPool
  {
  unsigned long Sec;
  unsigned int Status; /* ����� ����:
    0 - ᢮�����, 1 - ����������, 2 - ��������� */
  unsigned int Counter;
  unsigned char M [SECTOR_SIZE];
  };

struct reloc
  {
  unsigned int offset;
  unsigned int segment;
  };

/* ��������� �ᯮ��塞��� EXE 䠩�� (��� � MSDOS) */
struct exe_header
{                     /* �������ਨ �� [TECH Help!] */
char MZ[2];           /* "�������" 䠩�� .EXE ('MZ') */
unsigned int PartPag; /* ����� �������� ��᫥���� ��࠭��� (���筮 ����������) */
unsigned int PageCnt; /* ����� ��ࠧ� � 512-���⮢�� ��࠭���, ������ ��������� */
unsigned int ReloCnt; /* �᫮ ����⮢ � ⠡��� ��६�饭�� */
unsigned int HdrSize; /* ����� ��������� � 16-���⮢�� ��ࠣ��� */
unsigned int MinMem;  /* ������ �ॡ㥬�� ����� �� ���殬 �ணࠬ�� (��ࠣ���) */
unsigned int MaxMem;  /* ���ᨬ� �ॡ㥬�� ����� �� ���殬 �ணࠬ�� (��ࠣ���) */
unsigned int ReloSS;  /* ᥣ���⭮� ᬥ饭�� ᥣ���� �⥪� (��� ��⠭���� SS) */
unsigned int ExeSP;   /* ���祭�� ॣ���� SP (㪠��⥫� �⥪�) �� ����᪥ */
unsigned int ChkSum;  /* ����஫쭠� �㬬� (����⥫쭠� �㬬� ��� ᫮� � 䠩��) */
unsigned int ExeIP;   /* ���祭�� ॣ���� IP (㪠��⥫� ������) �� ����᪥ */
unsigned int ReloCS;  /* ᥣ���⭮� ᬥ饭�� �������� ᥣ���� (��� ��⠭���� CS) */
unsigned int TablOff; /* ᬥ饭�� � 䠩�� 1-�� ����� ��६�饭�� (��� 001cH) */
unsigned int Overlay; /* ����� ���૥� (0 ��� �������� �����) */
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