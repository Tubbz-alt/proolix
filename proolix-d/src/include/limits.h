/*      limits.h

        Defines implementation specific limits on type values.

        Copyright (c) Serge Pustovoitoff 1993-1998

*/

#ifndef LIMITS_H

#define LIMITS_H here

/* ������⢥��� ��࠭�祭�� � ��㫨��. � ᪮���� - �������쭮� ���祭��
ᮣ��᭮ �⠭����� POSIX */

#define ARG_MAX 120  /* (4096) ����. ����� ᯨ᪠ ��㬥�⮢ � �।� */
#define MAX_ENV 20    /* ���ᨬ��쭮� �᫮ ��६����� � �।� */
#define CHAR_BIT 8    /* (8) ���� �᫮ ��� � ������ ⨯� char */

/* ���ᨬ��쭮� � �������쭮� ���� ������ ⨯�         char */
#if (((int)((char)0x80)) < 0)
#define CHAR_MAX                        0x7F
#define CHAR_MIN                        0x80
#else
#define CHAR_MAX                        0xFFU
#define CHAR_MIN                        0x00
#endif

#define CHILD_MAX 6 /* (6) ���� �᫮ ������ ��� ����ᮢ � ������ euid */
#define CLK_TCK  18 /* (10) �᫮ ⨪�� � ᥪ㭤� */
        /* On TurboC 2.0 #define CLK_TCK 18.2 */
#define INT_MAX       0x7FFF  /* ( 32767) */
#define INT_MIN ((int)0x8000) /* (-32767) */
#define LINK_MAX 8 /* (8) ���� �᫮ �痢� 䠩�� */
#define LONG_MAX        0x7FFFFFFFL /*  ( 2147483647)  */
#define LONG_MIN ((long)0x80000000L) /* (-2147483647)  */
#define MAX_CANON 255 /* (255) ���� �᫮ ���� � ������� ��।� �ନ���� */
#define MAX_INPUT 255 /* (255) */
#define MB_CUR_MAX 2 /* (MB_LEN_MAX) */
#define MB_LEN_MAX 2 /* (1) */
#define NAME_MAX 14 /* (14) ���� �᫮ ���� � ����� 䠩��, �� ����
                            �������饣� NUL */
#define NGROUPS_MAX 1 /* (0) */

#ifndef OPEN_MAX
#define OPEN_MAX 8 /* (16) ���� �᫮ ������ ������� 䠩��� */
#endif

#ifndef TMP_MAX
#define TMP_MAX 25 /* (25) */
#endif

#define PATH_MAX 120 /* (255) ���� ����� ��� */
#define PIPE_BUF 512 /* (512) */
#define SCHAR_MAX 0x7F /* ���� ���� ������ ⨯� signed char */
#define SCHAR_MIN -128 /* ���. ���� ������ ⨯� signed char */
#define SHRT_MAX       0x7FFF  /* ���� ���� ������ ⨯� short */
#define SHRT_MIN ((int)0x8000) /* ���. ���� ������ ⨯� short */
#define UCHAR_MAX 0xFFU /* ���� ���� ������ ⨯� unsigned char */
#define UINT_MAX  0xFFFFU      /* (     65535) */
#define ULONG_MAX 0xFFFFFFFFUL /* (4294967295) */

#define USHRT_MAX 0xFFFFU /* (65535) */

#define PROC_MAX 4 /* ���ᨬ��쭮� �᫮ ����ᮢ */

/* ��� ᮡ�⢥��� ��࠭�祭��: */

/* ���� - ��࠭�祭�� 祫���� ;) */

/* ���ᨬ��쭠� ����� ��ப� */
#define MAX_LEN_STR 250

#define PassLen 80
#define MAX_ARG 10
#define SECTOR_SIZE 512
#define FAT_SECS 7
#define MAX_LINE 24
#define RETRYES 15
#define BUFFERS 5 /* max 127. ����. ࠧ��� ���୮�� �㫠 - 64�, �����
���� 512+6=518 �, 64� % 518 = 127. */
/* ������, �뤥�塞�� ������� COM-䠩�� (��ࠣ�䮢) */
#define ComMemory 0x1000UL

#endif