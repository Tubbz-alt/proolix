/* #define DEBUG_ALLOC */
/*****************************************************************************/
static unsigned int parleft(void)
{int CurPar, ret;

struct MemBlk far * MB;

ret=0;
CurPar = FP_SEG(Fin) + (FP_OFF(Fin) >> 4);
MB = MK_FP(CurPar,0);
while (1)
  {
  if (!((*MB).OwnerPar)) if ((*MB).SizePar>ret)ret+=(*MB).SizePar-1;
  if ((*MB).Type != 'M') break;
  CurPar+=(*MB).SizePar;
  MB = MK_FP (CurPar,0);
  }
return ret;
}
/*****************************************************************************/
static unsigned int parxtent(void)
{int CurPar, ret;

struct MemBlk far * MB;

ret=0;
CurPar = FP_SEG(Fin) + (FP_OFF(Fin) >> 4);
MB = MK_FP(CurPar,0);
while (1)
  {
  if (!((*MB).OwnerPar)) if ((*MB).SizePar>ret)ret=(*MB).SizePar-1;
  if ((*MB).Type != 'M') break;
  CurPar+=(*MB).SizePar;
  MB = MK_FP (CurPar,0);
  }
return ret;
}
/*****************************************************************************/
static unsigned long coreleft(void)
{unsigned long l;

l=parleft();
return l<<4;
}
/*****************************************************************************/
static unsigned long int corextent(void)
{unsigned long l;

l=parxtent();
return l<<4;
}
/*****************************************************************************/
void mem(void)
{int CurPar; char c;

struct MemBlk far * MB;

CurPar = FP_SEG(Fin) + (FP_OFF(Fin) >> 4);
MB = MK_FP(CurPar,0);
puts("\nRAM       OwnPar Size");
while (1)
  {
  printf("%4X:0000 %c %4X %4X",CurPar,(c=(*MB).Type)<' '?' ':c,
  (*MB).OwnerPar,(*MB).SizePar);
  if ((*MB).Type != 'M') {puts(""); break;}
  CurPar+=(*MB).SizePar;
  MB = MK_FP (CurPar,0);
  puts("");
  }
printf("Free memory        %li\nMaximum free block %li\n",coreleft(),
corextent());
}
/****************************************************************************/
void far *malloc (size_t size)
{
unsigned int CurPar, NeedPar, RestosPar;
struct MemBlk far * MB;
struct MemBlk far * Rest;
struct MemBlk MB2;

if (size==0) return NULL;
if (size==-1L)
  {
  size=corextent();
  }

NeedPar=(int)(size>>4)+1;
if (size & 0xF) NeedPar++;

#ifdef DEBUG_ALLOC
printf("A1\n");
#endif

CurPar = FP_SEG(Fin) + (FP_OFF(Fin) >> 4);
MB = MK_FP(CurPar,0);
#ifdef DEBUG_ALLOC
printf("A2\n");
#endif

while (1)
  {
  #ifdef DEBUG_ALLOC
  printf("A3\n");
  #endif
  if(!(*MB).OwnerPar)
    /* block is free */
    if ((*MB).SizePar>=NeedPar)
      { /* memory yes */
      #ifdef DEBUG_ALLOC
      printf("A11\n");
      #endif
      MB2.Type=(*MB).Type;
      MB2.SizePar=(*MB).SizePar;
      (*MB).SizePar=NeedPar;
      (*MB).OwnerPar=ProcessPar;
      #ifdef DEBUG_ALLOC
      printf("malloc: ProcessPar=%04X\n",ProcessPar);
      #endif
      if (MB2.SizePar>NeedPar)
        {/* restos of blk */
        #ifdef DEBUG_ALLOC
        printf("A10\n");
        #endif
        (*MB).Type='M';
        RestosPar=CurPar+NeedPar;
        Rest=MK_FP(RestosPar,0);
        (*Rest).OwnerPar=0;
        (*Rest).SizePar=MB2.SizePar-NeedPar;
        (*Rest).Type=MB2.Type;
        }
      #ifdef DEBUG_ALLOC
      printf("A13\n");
      #endif
      return MK_FP(CurPar+1,0);
      }
    else ; /* no memory in this blk */
  else ; /* blk is busy */

  if ((*MB).Type != 'M') break;
  CurPar+=(*MB).SizePar;
  MB = MK_FP (CurPar,0);
  }

#ifdef DEBUG_ALLOC
printf("alloc\n");
#endif

return NULL;
}
/*****************************************************************************/
void free ( void far * block)
{
size_t CurPar;
struct MemBlk far * MB;

if (block==0) return;
block=MK_FP(FP_SEG(block) + (FP_OFF(block)>>4) -1,0); /* normalization */
CurPar = FP_SEG(Fin) + (FP_OFF(Fin) >> 4);
MB = MK_FP(CurPar,0);
while (1)
  {
  if (MB==block) {(*MB).OwnerPar=0;return;}
  if ((*MB).Type != 'M') break;
  CurPar+=(*MB).SizePar;
  MB = MK_FP (CurPar,0);
  }
}
/*****************************************************************************/
unsigned int par_size_of_block ( void far * block)
{
size_t CurPar;
struct MemBlk far * MB;

if (block==0) return 0;
block=MK_FP(FP_SEG(block) + (FP_OFF(block)>>4) -1,0); /* normalization */
CurPar = FP_SEG(Fin) + (FP_OFF(Fin) >> 4);
MB = MK_FP(CurPar,0);
while (1)
  {
  if (MB==block) {return (*MB).SizePar;}
  if ((*MB).Type != 'M') break;
  CurPar+=(*MB).SizePar;
  MB = MK_FP (CurPar,0);
  }
return 0xFFFF;
}
/*****************************************************************************/
int garbage (void)
{int ret=1;
size_t CurPar;
int opt=1;

struct MemBlk far * MB;
struct MemBlk far * MB0;

while(opt)
{
opt=0;
CurPar = FP_SEG(Fin) + (FP_OFF(Fin) >> 4);
MB = MK_FP(CurPar,0);
if (((*MB).Type) != 'M') return 1;
MB0=MB;

while (1)
{
CurPar+=(*MB).SizePar;
MB = MK_FP (CurPar,0);
if ( (((*MB0).OwnerPar)==0) && (((*MB).OwnerPar)==0) )
  {
  (*MB0).Type=(*MB).Type;
  (*MB0).SizePar+=(*MB).SizePar;
  ret=0;
  opt=1;
  }
else MB0=MB;
if ((*MB).Type != 'M') break;
}
}

return ret;
}
/*****************************************************************************/
void far *calloc (size_t nitems, size_t size)
{size_t m, i; void far *Pointer; char huge *Setter;

/* ��� ��. ����� ���� huge ? */

if ((Pointer=malloc(m=nitems*size))!=NULL)
  {
  Setter=Pointer;
  for(i=0;i<m;i++) *Setter++=0;
  }
return Pointer;
}
/*****************************************************************************/
void far*_Cdecl realloc (void far *block, size_t size)
{
size_t CurPar;
struct MemBlk far * MB, far * MB_next, far * MB_kusochek;
unsigned int NeedPar, Delta;

if (block==NULL) return malloc(size);
if (size==0) { free(block); return block; }
else
  {/* ����⪠ �������� ࠧ��� 㦥 �뤥������� ���⪠ ����� */
  block=MK_FP(FP_SEG(block) + (FP_OFF(block)>>4) -1,0); /* normalization */
  CurPar = FP_SEG(Fin) + (FP_OFF(Fin) >> 4);
  MB = MK_FP(CurPar,0);
  while (1)
    {
    if (MB==block)
      {/* ��諨 ���� ����� */
      goto l_found;
      }
    if ((*MB).Type != 'M') break;
    CurPar+=(*MB).SizePar;
    MB = MK_FP (CurPar,0);
    }
  /* ⠪��� ����� ����� ��� */
  return NULL;
  }
l_found:
/* �᫨ ����⪠ �������� ࠧ��� ᢮������� ����� ����� - � �� ��� ��䨣 */
if (!MB->OwnerPar) return NULL;
/* �饬 ᫥���騩 ���� */
if ((*MB).Type != 'M') MB_next=NULL;
CurPar+=(*MB).SizePar;
MB_next = MK_FP (CurPar,0);
/* ��।��塞 ���� ࠧ��� � ��ࠣ��� */
NeedPar=(int)(size>>4)+1;
if (size & 0xF) NeedPar++;

if (MB->SizePar==NeedPar) return block; /* �������� ��������� �� ���� */
if (MB->SizePar>NeedPar)
  {/* 㬥��蠥� ࠧ��� ����� */
  Delta=MB->SizePar-NeedPar;
  MB->SizePar=NeedPar;
  /* ᮧ���� ����-���祪 */
  CurPar = FP_SEG(MB) + (FP_OFF(MB) >> 4);
  CurPar+=MB->SizePar;
  MB_kusochek= MK_FP(CurPar,0);
  MB_kusochek->Type='M';
  MB_kusochek->OwnerPar=0;
  MB_kusochek->SizePar=MB->SizePar-NeedPar-1;
  /* �᫨ ᫥���騩 ���� ⮦� ���⮩, � ����-���祪 �����頥� ��� */
  if (!MB_next->OwnerPar)
    {
    MB_kusochek->SizePar+=(MB_next->SizePar+1);
    }
  }
else
  {/* 㢥��稢��� ࠧ��� ����� */
  /* �᫨ ᫥���騩 ���� ��᢮����� - ��室 */
  if (MB_next->OwnerPar) return NULL;
  /* �᫨ ��� ���� ��᫥���� - ��室 */
  if (MB->Type=='Z') return NULL;
  /* ����塞 ���饭�� ࠧ��� ��襣� ����� */
  Delta=NeedPar-MB->SizePar;
  /* �᫨ ᫥���騩 ���� ����� ����室����� ���饭�� - ��室 */
  if (MB_next->SizePar<Delta) return NULL;
  /* �᫨ ᫥���騩 ���� ࠢ�� ����室����� ���饭��, � �� �祭� */
  /* ����: ��� ���� �����頥� ᮡ�� ᫥���騩 ���� */
  if (MB_next->SizePar==Delta)
    {
    MB->SizePar=NeedPar;
    return block;
    }
  /* ��� ���� ����� ���祪 �� ᫥���饣� ����� */
  MB->SizePar=NeedPar;
  /* */
  CurPar = FP_SEG(MB) + (FP_OFF(MB) >> 4);
  CurPar+=MB->SizePar;
  MB_kusochek= MK_FP(CurPar,0);
  MB_kusochek->Type=MB_next->Type;
  MB_kusochek->OwnerPar=0;
  MB_kusochek->SizePar=MB_next->SizePar-Delta;
  }
return NULL;
}