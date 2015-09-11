#include <prool.h>

#include <conf.c>
#include "kernel.h"
/****************************************************************************/
/* #define DEBUG */
/****************************************************************************/
char DirName [11];
/****************************************************************************/
int PathToDir(const char far *path, struct dirent far *Dir)
{
const char far *cc;
const char far *point;
int Counter, MsDos, i, len=2, NameLen, ExtLen, Up;

#ifdef DEBUG
printf(" P2D: path=`%s' ",path);
#endif

if (path==NULL) return -1;
/* �஢�ઠ path �� MSDOS ᮢ���⨬���� */
/* ��� ᮢ���⨬��� ���� ������ ᮤ�ঠ�� �� ����� ����� �窨,
�� �窨 ������ ���� �� ����� 8 ᨬ�����, ��᫥ �窨 - �� ����� 3,
�� ����᪠���� � ����� ������ ���. �㪢 */
cc=path;
Up=0;
Counter=0;
MsDos=1;
if (strcmp(path,"..")==0) MsDos=2; /* 2 == ".." */
else
  {
  while(*cc)
    {
    if (*cc=='.')
      {
      point=cc;
      Counter++;
      }
    else
      {
      if (isupper(*cc)) Up=1;
      }
    cc++;
    }
  if (Up) MsDos=0;
  len=(int)(cc-path);
  if (MsDos)
    {
    if (Counter) {NameLen=(int)(point-path); ExtLen=(int)(len-NameLen-1);}
    else {NameLen=len; ExtLen=0;}
    if (Counter>1) {MsDos=0;}
    else if (NameLen>8) {MsDos=0;}
    else if (ExtLen>3) {MsDos=0;}
    }
  }
/* �८�ࠧ������ ����� 䠩�� � ������ � ��⠫��� */
if (Dir!=NULL)
  {
  for (i=0;i<11;i++) DirName[i]=' ';
  if (MsDos==1)
    {
    memcpy(DirName,path,NameLen);
    memcpy(DirName+8,point+1,ExtLen);
    for (i=0;i<11;i++) DirName[i]=toupper(DirName[i]);
    }
  else
    {
    memcpy(DirName,path,(len>11)?11:len);
    }
  #ifdef DEBUG
  printf(" DirName=`%s' ", DirName);
  #endif

  memcpy((*Dir).filename,DirName,11);
  (*Dir).attrib.B.Attr1=!MsDos;
  }
#ifdef DEBUG
printf(" dir=`%Fs' ",(*Dir).filename);
#endif

return MsDos;
}