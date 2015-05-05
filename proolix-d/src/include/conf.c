/*      conf.c

        Configuration file for Proolix

        Serge Pustovoitoff 1994-2004

*/

/* ��।������ ����� DOSKEY ������砥� ����ᠭ�� �� ��ᥬ���� shell ��������
� ।���஢����� ��������� ��ப�, �����⢨� ������ - ��⮤��ᠫ�� 襫�,
����ᠭ�� ���� �� � (��� ।���஢����, ⮫쪮 � �����襩 Break */
/* #define DOSKEY */

/* �������� */

/* �᫨ ��।����� CMOS - �����, � ��設� ���� CMOS � RTC - Real Time Clock
(AT � ����, ��� �뢠�� � XT � CMOS RTC ) */
#define CMOS

/* �᫨ DEBUG ��।�����, � �㤥� �뤠������ �⫠��筠� ���ଠ�� */
/* #define DEBUG */

/* �᫨ _RC_ ��।�����, � �� ����㧪� ��㫨�� �㤥� �믮������� 䠩�
_RC_ */
#define _RC_ "rc.com"

/* ���墠� ��� ���뢠��� - ����� (���� ��⠢�塞 ���祭�� ����� ��
ROM BIOS */
/* #define CHANGE_INTS */

/* ���墠� int 5 - ����� (���� ��⠢�塞 ���祭�� ����� �� ROM BIOS */
/* #define CHANGE_INT5 */

/* ���墠� int 1B (ctrl-break) */
#define CHANGE_INT_1B

/* ���⪠ �࠭� �� ����㧪� ��㫨�� */
/* #define CLRSCR */

/* ��������� */
#define _VGA_ /*_DEFAULT_VIDEO_ _MDA_ _HERCULES_ _CGA_ _EGA_ _VGA_ */
#ifdef _HERCULES_
        /* #define _MSHERC_ */ /* �� ��᭥� */
#endif
/* �����०�� */
#define _VIDEO_ASCII_ /* _VIDEO_ASCII_ _VIDEO_GRAPH_ */
/* ������ 梥⭮�/�����஬�� */
#define _MON_MONO_ /* _MON_COL_ _MON_MONO_ */
/* ���� ����� ᥣ����*/
#define VIDEO_SEG 0xB800 /* 0xB000 0xB800 */
/* Main text char attribute */
#define MAIN_TEXT_ATTR 7

/* putch */
#define PutchBIOS putch0 /* putch0 putch1 putch2 putch3 */
/* putch0 - asm-program, use int 10h Fn=E (emulate tty)
   putch1 - asm-program, use int 10h Fn=9 (put sym & attr)
   putch2 - asm-program (direct write to video RAM). putch2 maked from putch3
     (compiled from C to asm manually (like manual sunset ;))
     Debugged under MSDOS (into HCAT2 program). Worked under MSDOS.
     Not worked under Proolix
   putch3 - C-program (direct write to video RAM). Debugged under MSDOS
     (into HCAT program). Worked under MSDOS. Not worked under Proolix :(
 */

#if defined(_HERCULES_) && defined(_VIDEO_GRAPH_)
  #ifdef PutchBIOS
  #undef PutchBIOS
  #endif
#define PutchBIOS putch1
#endif

/* Proolix System Call Interrupt Number */
/* MSDOS have number 21h ! See [Interrupt List] for search free & unusable
interrupt no */
/* #define INT_NO 0x83 */ /* Old syscall */
#define INT_NO 0x84 /* New syscall */

/* Use processor definition library by B-coolWare.
�������� �����祢 2:5028/52.6 bob@ymz.yaroslavl.su */

/* #define B_COOLWARE */

#define HDD_READ_ONLY 0 /* 0 - HDD mounted read/write,
                           1 - HDD mounted read only */
#define LASTDRIVE 16 /* max drives */

#define _STANDARD_ 0
#define _RUSSIAN_ 1

#define CODETABLE _RUSSIAN_

#define FONT_DIR "/bin"
#define HOME_DIR "/"
