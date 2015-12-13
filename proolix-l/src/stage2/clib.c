// proolix-l c library

#include <limits.h>

 // for printf
#define MAX_LEN_STR 256 
#define EOF (-1)

#if 0
void two_parameters(int *i, int *j) // see translated text in .s file
{
*i=getch();
*j=getch();
}
#endif

int toupper (int ch)
{
if ((ch>='a')&&(ch<='z'))return ch + 'A' - 'a'; else return ch;
}

char *strchr (const char *str, int c)
{
/* if (str==NULL) return NULL; */
while (*str)
  if (*str==c)
    return (char *) str;
  else str++;
return NULL;
}

size_t strlen (const char *s)
{
size_t i;
/* if (s==NULL) return NULL; */
i=0;
while (*s++)i++;
return i;
}

char  *strcpy (char  *dest, const char  *src)
{char  *cc;
/* if (dest==NULL) return NULL; */
/* if (src==NULL) return NULL; */
cc=dest;
  do *dest++ = *src;
  while (*src++);
return cc;
}

void cls(void)
{
cls_();
setpos(0,0);
}

void putch(char c)
{char g_col,g_row;
g_row=get_row();
g_col=get_col();
switch(c)
	{
	case '\r': g_col=0; setpos(g_row,g_col); break;
	case '\n': if (g_row==24)
			scroll();
		   else
			{g_row++; setpos(g_row,g_col);}
		   break;
	default:
		putch_color(c,get_color());
		g_col++;
		setpos(g_row,g_col);
	}
}

void puts0(char *s)
{
    while (*s)
	putch(*s++);
//	putch(*s++);
}


void test (void)
{int i,j;

setpos(0,0);

puts0("stroka 1\r\n");
puts0("stroka 2\r\n");                                                                                                       
puts0("stroka 3\r\n");

//for (i=0;i<256;i++) {global_color=i; putch('W');}

//putch('a');

#if 0
setpos(0,0);putch_color('1',2);
setpos(0,1);putch_color('2',3);
setpos(0,2);putch_color('3',4);
#endif
}

void ascii(void)
{int i;
for (i=0;i<256;i++) putch(i);
}

char *getsn(char *str, int len)
{char c; int i;
i=0;
while(1)
	{
	c=getch(); putch(c);
	if (c==0x0DU) {*str=0; return str;}
	*str=c;
	if (++i>=(len-1)) {*str=0; return str;}
	str++;
	}
}

void puthex1(char c)
{
if (c>9) putch('A'+c-10);
else putch('0'+c);
}

void puthex_b(char c)
{
puthex1((c>>4)&0xFU);
puthex1(c&0xFU);
}

void puthex(int c)
{
puthex_b((c>>8) & 0xFFU);
puthex_b(c&0xFFU);
}

void puthex_l(int c)
{
puthex ((c>>16)&0xFFFFU);
puthex (c & 0xFFFFU);
}

void putdec (int w)
{int r,i,trail_zeroes;
trail_zeroes=1;
int Divisor10 [10] = {1000000000,100000000,10000000,1000000,100000,10000, 1000, 100, 10, 1};

if (w<0) {putch('-'); w=-w;}
if (w==0) {putch('0'); return;}

            for (i=0;i<10;i++)
              {
              r=w/Divisor10[i];
              w%=Divisor10[i];
              if (r!=0)
            	    {
            	    putch('0'+r);
            	    trail_zeroes=0;
            	    }
              else // r==0
            	    if (trail_zeroes)
            		{// nothing
            		}
            	    else
            		{
            		putch('0');
            		}
              }
}

void putdec2 (int w, int digits, int zeroes)
{int r,i,trail_zeroes,j;
trail_zeroes=1;
int Divisor10 [10] = {1000000000,100000000,10000000,1000000,100000,10000, 1000, 100, 10, 1};

if ((digits<1)||(digits>10)) return;

if (w<0) {putch('-'); w=-w;}
if (w==0) {putch('0'); return;}

            for (i=10-digits;i<10;i++)
              {
              r=w/Divisor10[i];
              w%=Divisor10[i];
              if (r>9)
        	    {// overflow
        	    for (j=0;j<digits;j++) putch('*');
        	    return;
        	    }
              if (r!=0)
            	    {
            	    putch('0'+r);
            	    trail_zeroes=0;
            	    }
              else // r==0
            	    if (trail_zeroes)
            		{if (zeroes==0) putch('0');
			else putch(' ');
            		}
            	    else
            		{
            		putch('0');
            		}
              }
}

#if 0
void puts0(char *s)
{
    while (*s)
	putch(*s++);
}
#endif

void putch0(char c)
{
/*
VIDEO - TELETYPE OUTPUT

AH = 0Eh
AL = character to write
BH = page number
BL = foreground color (graphics modes only)
*/
__asm__ volatile("movb $0x0E,%ah");
__asm__ volatile("movb %0,%%al"::"r"(c):"%al");
__asm__ volatile("xorb %bh,%bh");
__asm__ volatile("int $0x10");

}

void stop(void)
{
__asm__ volatile("int $0x20");
}

int getch(void)
{
/*
AH = 00h

Return:
AH = BIOS scan code
AL = ASCII character
*/
__asm__ volatile("xor %ah,%ah");
__asm__ volatile("int $0x16");
__asm__ volatile("xor %ah,%ah");
}

int strcmp (const char  *s1, const char  *s2)
{char c1,c2;

/* if (s1==NULL) return 0; */
/* if (s2==NULL) return 0; */
do  {c1=*s1++; c2=*s2++; if (c1>c2) return 1; else if (c1<c2) return -1;}
while (c1&&c2);
return 0;
}

#if 0 // ����� �������, ������� ���� �� ������������

/****************************************************************************/
char  *stpcpy (char  *dest, const char  *src)
{
/* if (dest==NULL) return NULL; */
/* if (src==NULL) return NULL; */
  do *dest++ = *src;
  while (*src++);
return dest-1;
}
/****************************************************************************/
size_t strcspn(const char  *s1, const char  *s2)
{
size_t i;

/* if (s1==NULL) return NULL; */
/* if (s2==NULL) return NULL; */
i=0;
while(*s1)
  {
  if (strchr(s2,*s1)!=NULL)break;
  i++;
  s1++;
  }
return i;
}
/****************************************************************************/
char  *strcat (char  *dest, const char  *src)
{
char  *cc;
/* if (dest==NULL) return NULL; */
/* if (src==NULL) return NULL; */
cc=dest;
while(*dest++);
strcpy(--dest,src);
return cc;
}
/****************************************************************************/
int stricmp(const char  *s1, const char  *s2)
{char c1,c2;

/* if (s1==NULL) return 0; */
/* if (s2==NULL) return 0; */
do
  {
  c1=*s1++;
  c2=*s2++;
  if (isalpha(c1) && isalpha(c2))
    {
    c1=toupper(c1);
    c2=toupper(c2);
    }
  if (c1>c2) return 1;
  else if (c1<c2) return -1;
  }
while (c1&&c2);
return 0;
}
/****************************************************************************/
char  *strlwr(char  *s)
{
char  *cc;
/* if (s==NULL) return NULL; */
cc=s;
while(*s)
  {
  *s=tolower(*s);
  s++;
  }
return cc;
}
/****************************************************************************/
char  *strncat (char  *dest, const char  *src, size_t maxlen)
{
char  *cc;
/* if (dest==NULL) return NULL; */
/* if (src==NULL) return NULL; */
cc=dest;
while(*dest++);
strncpy(--dest,src,maxlen);
return cc;
}
/****************************************************************************/
int strncmp(const char  *s1, const char  *s2, size_t maxlen)
{char c1,c2;
size_t i;

/* if (s1==NULL) return 0; */
/* if (s2==NULL) return 0; */
for(i=0;i<maxlen;i++)
 {
 c1=*s1++;
 c2=*s2++;
 if (c1>c2) return 1;
 else if (c1<c2) return -1;
 if(!(c1&&c2))break;
 }
return 0;
}
/****************************************************************************/
char  * strncpy (char  * dest, const char  * src, size_t maxlen)
{char  * cc; size_t i;
/* if (dest==NULL) return NULL; */
/* if (src==NULL) return NULL; */
cc=dest;
for(i=0;(i<maxlen);i++) {*dest++=*src; if (!*src++) break;}

return cc;
}
/****************************************************************************/
int strnicmp(const char  *s1, const char  *s2, size_t maxlen)
{char c1,c2;
size_t i;

/* if (s1==NULL) return 0; */
/* if (s2==NULL) return 0; */
for(i=0;i<maxlen;i++)
 {
 c1=*s1++;
 c2=*s2++;
 if (isalpha(c1)&&isalpha(c2))
   {
   c1=toupper(c1);
   c2=toupper(c2);
   }
 if (c1>c2) return 1;
 else if (c1<c2) return -1;
 if(!(c1&&c2))break;
 }
return 0;
}
/****************************************************************************/
char  *strnset(char  *s, int c, size_t n)
{size_t i;
char  *ret;
ret=s;
/* if (s==NULL) return NULL; */
for(i=0;i<n;i++)
  {
  if (!*(s+(unsigned int)i)) break;
  *s=c;
  }
return ret;
}
/****************************************************************************/
char  *strpbrk(const char  *s1, const char  *s2)
{
/* if (s1==NULL) return NULL; */
/* if (s2==NULL) return NULL; */
while(*s1)
  {
  if (strchr(s2,*s1)!=NULL) break;
  s1++;
  }
return (char  *)s1;
}
/****************************************************************************/
char  *strrchr(const char  *s, int c)
{
char  *cc;
/* if (s==NULL) return NULL; */
cc=NULL;
while(*s)
  {
  if (*s==c) cc=(char  *)s;
  s++;
  }
return cc;
}
/****************************************************************************/
char  *strset(char  *s, int c)
{char  *cc;
/* if (s==NULL) return NULL; */
cc=s;
while(*s)
  {
  *s=c;
  s++;
  }
return cc;
}
/****************************************************************************/
size_t strspn(const char  *s1, const char  *s2)
{
size_t i;
/* if (s1==NULL) return NULL; */
/* if (s2==NULL) return NULL; */
i=0;
while(*s1)
  {
  if (strchr(s2,*s1)==NULL)break;
  i++;
  s1++;
  }
return i;
}
/****************************************************************************/
char  *strstr(const char  *s1, const char  *s2)
{
size_t l;
/* if (s1==NULL) return NULL; */
/* if (s2==NULL) return NULL; */
l=strlen(s2);
while(*s1)
  {
  if (!strncmp(s1,s2,l))return (char  *)s1;
  s1++;
  }
return NULL;
}
/****************************************************************************/
static char  *strtok_ptr;
/****************************************************************************/
char  *strtok(char  *s1, const char  *s2)
{
char  *cc;

if (s1==NULL) if((s1=strtok_ptr)==NULL) return NULL;

/* ������� ��������-������������ � ������ ������ */
while(*s1)
  {
  if (strchr(s2,*s1)==NULL)break;
  s1++;
  }
if(!*s1)return NULL;
cc=s1; /* ��� ������ ������ */
/* ����� ����� ������ */
while(*s1)
  {
  if (strchr(s2,*s1)!=NULL) break;
  s1++;
  }
if (*s1) {*s1=0; strtok_ptr=s1;} else strtok_ptr=NULL;
return cc;
}
/****************************************************************************/
char  *strupr(char  *s)
{
char  *cc;
/* if (s==NULL) return NULL; */
cc=s;
while(*s)
  {
  *s=toupper(*s);
  s++;
  }
return cc;
}
/****************************************************************************/
char  * strrev  (char  *str)
{size_t i1, i2; char Bolvan,  *ret;
ret=str;
/* if (str==NULL) return NULL; */
i1=1;
i2=(int)strlen(str);
while(i1<i2)
  {
  /* swap str[i1] str[i2] */
  /* ����������� ����� ��������� ��� ������ �������
  (C) �.�����, "��� ����������" */
  Bolvan=*(str+(unsigned int)i1);
  *(str+(unsigned int)i1++)=*(str+(unsigned int)i2);
  *(str+(unsigned int)i2--)=Bolvan;
  }
return ret;
}

/****************************************************************************/

int tolower (int ch)
{
if ((ch>='A')&&(ch<='Z'))return ch + 'a' - 'A'; else return ch;
}
/****************************************************************************/

/****************************************************************************/
int isgraph(int c)
{
return ((c) >= 0x21 && (c) <= 0x7e);
}
/****************************************************************************/
int isprint(int c)
{
return ((c) >= 0x20 && (c) <= 0x7e);
}
/****************************************************************************/
int isalnum (int c) {return isdigit(c)||isalpha(c);}
int isalpha (int c) {return islower(c)||isupper(c);}
int iscntrl (int c) {return c<' ';}
int isdigit (int c) {return (c>='0')&&(c<='9');}
int islower (int c) {return (c>='a')&&(c<='z');}
int ispunct (int c)
{
switch(c)
  {
  /*  (C)  ������ �������� ���������� ���� �� ��������� Connect �.������ � ��.
  Copyright by KHEMZ, Inc. 1991, 1994 */
  case '.':
  case ',':
  case '!':
  case '"':
  case '\'':
  case '(':
  case ')':
  case '*':
  case '+':
  case '-':
  case '/':
  case ':':
  case ';':
  case '<':
  case '=':
  case '>':
  case '?':
  case '[':
  case '\\':
  case ']':
  case '^':
  case '{':
  case '|':
  case '}':
  case '~': return 1;
  default:  return 0;
  }
}
/****************************************************************************/
int isspace (int c) {if ((c==' ')||(c=='\t')) return 1; else return 0;}
int isupper (int c) {return (c>='A')&&(c<='Z');}
int isxdigit(int c)
  {return ((c>='0')&&(c<='9'))||((c>='a')&&(c<='f'))||((c>='A')&&(c<='F'));}

#endif

/****************************************************************************/
void  *memcpy(void  *dest, const void  *src, size_t n)
{size_t i; void  *ret;
/* if (dest==NULL) return NULL; */
/* if (src==NULL) return NULL; */
ret=dest;
for (i=0;i<n;i++)
	{
	*((char  *)dest)=*((char  *)src);
	(char *)dest++;
	(char *)src++;
	}
return ret;
}
/****************************************************************************/
void  *memccpy(void  *dest, const void  *src, int c, size_t n)
{size_t i;
/* if (dest==NULL) return NULL; */
/* if (src==NULL) return NULL; */
for (i=0;i<n;i++)
  {
  *((char  *)dest)=*((char  *)src);
  (char *)dest++;
  if (*((char  *)src)==c) {return (char  *)src;}
  (char *)src++;
  }
return NULL;
}
/****************************************************************************/
int memcmp (const void  *s1, const void  *s2, size_t n)
{char c1,c2; size_t i;

/* if (s1==NULL) return 0; */
/* if (s2==NULL) return 0; */
for(i=0;i<n;i++)
  {
  c1=*((char  *)s1+(unsigned int)i);
  c2=*((char  *)s2+(unsigned int)i);
  if (c1>c2) return 1;
  else if (c1<c2) return -1;
  }
return 0;
}
/****************************************************************************/
int memicmp (const void  *s1, const void  *s2, size_t n)
{char c1,c2; size_t i;

/* if (s1==NULL) return 0; */
/* if (s2==NULL) return 0; */
for(i=0;i<n;i++)
  {
  c1=toupper(*((char  *)s1+(unsigned int)i));
  c2=toupper(*((char  *)s2+(unsigned int)i));
  if (c1>c2) return 1;
  else if (c1<c2) return -1;
  }
return 0;
}
/****************************************************************************/
void  *memchr (const void  *str, int c, size_t n)
{size_t i;
/* if (str==NULL) return NULL; */
for(i=0;i<n;i++)
  if (*((char  *)str+(unsigned int)i)==c)
    return (char  *)str+(unsigned int)i;
return NULL;
}
/****************************************************************************/
void  *memset  (void  *str, int c, size_t n)
{size_t i;
/* if (str==NULL) return NULL; */
for(i=0;i<n;i++) *((char  *)str+(unsigned int)i)=c;
return str;
}

#if 0 // printf package

int printf (const char  *format, ...)
{
va_list v; int counter;
char new_printf_buf[MAX_LEN_STR];

/* Called functions: vsprintf(), puts0() */

/* ������������� � �������� ������ ������� printf_buf, ����������� ��
malloc (��. � kernel.c) �������� ����� (���������).
� ������������� � �������� ������
���������� ������� new_printf_buf ������ �� ��������. ��� ��������. */

va_start(v,0);
counter=vsprintf(new_printf_buf,format,v);
puts0(new_printf_buf);
return counter;
}
/****************************************************************************/
int vsprintf (char  *str, const char  *format, va_list v)
{
int i, counter=0, width, prec, Modifier, Type,
  FlagMinus, FlagPlus, FlagBlank, FlagDiez, FlagZero;
char c, *cc,  *fcc;
unsigned int segment;
int len; char  *ss; long L;
/* char Clipboard [MAX_LEN_STR]; */
char new_printf_buf[MAX_LEN_STR]; /* ��. ���������� � ������ �-��� printf */

while(*format)
  {
  if (*format!='%')
    {
    *str++=*format;
    counter++;
    }
  else
    {char s [] = "printf: Flag '%c' is not realized now :( ";
    /* �������� ������ '%' */
    /* % [FLAG] [WIDTH] [.PREC] [MODIFIER] TYPE */
    /*
                                TYPE:
       d signed dec int
       i "
       o unsigned oct int
       u unsigned dec int
       x unsigned hex int lowercase
       X "                uppercase
       f float
       e float with Exponent
       g f or e
       E e
       G g
       c 1 char
       s string
       % %
       p pointer
       n char counter (?)

                                FLAG:
       none right, 0 or blank
       - left
       + sign + or -
       blank sign - only
       # oct - 0 hex - 0x 0X
                                WIDTH:
       n
       0n 0 fill
       * next arg - width
                                PREC:
       none
       .0
       .n
       * - next arg
                                MODIFIER:
       F far
       N near
       h short int
       l long int
       L long double
     */
    /* ������������ ����� */
    /* % [FLAG] [WIDTH] [.PREC] [MODIFIER] TYPE */
    FlagMinus=0; FlagPlus=0; FlagBlank=0; FlagDiez=0; FlagZero=0;
    while(strchr("-+ #0",c=*++format)!=NULL)
      switch (c)
      {
      /* ������ ��������� ������ ���� "var=1; if (var)" ������������ ��� ����,
      ����� �� ���� ��������� ����������� "variable not used". ����� ����,
      ��� ��������� ������ ����� �����������, ��������� ��������� �����,
      �����������, ������� */
        case '-': FlagMinus=1; break;
        case '+': FlagPlus =1; if (FlagPlus ) printf(s,c); break;
        case ' ': FlagBlank=1; if (FlagBlank) printf(s,c); break;
        case '#': FlagDiez =1; if (FlagDiez ) printf(s,c); break;
        case '0': FlagZero =1;
      }
    if (c==0) break;
    /* ������������ ������ */
    /* % [FLAG] [WIDTH] [.PREC] [MODIFIER] TYPE */
    if (isdigit(*format))
      {width=atoi(format);while(isdigit(c=*++format));
      }
    else width=0;
    if (c==0) break;
    if (c=='.')
      {
      prec=atoi(format+1);
      while(isdigit(c=*++format));
      if (c==0) break;
      }
    else prec=0;
    if (prec) printf("printf: prec is not realized now :( ");
    /* ������������ modifier */
    /* % [FLAG] [WIDTH] [.PREC] [MODIFIER] TYPE */
    if (strchr("FNhlL",c=*format)!=NULL)
      {Modifier=c; format++;
      switch(Modifier)
        {
        case 'F':
        case 'N':
        case 'h':
        case 'l': break;
        case 'L':
          printf("printf: Modifier '%c' is invalid\n",Modifier);
        }
      }
    else Modifier=0;
    if (c==0) break;
    if (strchr("diouxXfeEgGcspn%",c=*format)==NULL)
      {Type=0; printf("printf: invalid type '%c'",c);}
    else
      {
      Type=c;
      /* ����� ��������� */
      switch(Type)
        {
        case '%': *str++='%'; counter++; break;
        case 'u': /* unsigned int */
        case 'i': /* signed int */
        case 'd': /* signed int */
                  if (Type=='u')
                    if (Modifier=='l') L=va_arg(v,unsigned long);
                    else L=va_arg(v,unsigned int);
                  else
                    if (Modifier=='l') L=va_arg(v,long);
                    else L=va_arg(v,int);

                  #ifdef DEBUG
                  printf("printf: L=%08lX\n",L);
                  #endif

                  if (Type!='u') if (L<0) {*str++='-'; width--; L=-L;}

                  if (Type=='u')
                    if (Modifier=='l') ultoa(L,new_printf_buf,10);
                    else ultoa(L,new_printf_buf,10);
                  else
                    if (Modifier=='l') ltoa(L,new_printf_buf,10);
                    else itoa((int)L,new_printf_buf,10);

                  #ifdef DEBUG
                  printf("printf: new_printf_buf=%s\n",new_printf_buf);
                  #endif
                  len=(int)strlen(new_printf_buf);
                  /* ��������� ���������� ���� */
                  if (L)
                    {
                    ss=new_printf_buf;
                    if (*ss=='-')ss++;
                    while(*ss=='0')*ss++=' ';
                    fcc=ss;
                    }
                  else
                    fcc="0";
                  goto l_s;
        case 'x':
        case 'X': if (Modifier=='l')
                    {
                    if (width==0) width=8;
                    ltoa(va_arg(v,long),new_printf_buf,16);
                    }
                  else
                    {
                    if (width==0) width=4;
                    itoa(va_arg(v,int),new_printf_buf,16);
                    }
                  if ((len=(int)strlen(new_printf_buf))>width)
                    {
                    fcc=new_printf_buf;
                    fcc+=len-width;
                    }
                  else
                    fcc=new_printf_buf;
                  goto l_s;
        case 'p': if (width<5)
                    {itoa(va_arg(v,int),new_printf_buf,10);
                    strcpy(str,new_printf_buf);
                    counter+=(i=(int)strlen(new_printf_buf));
                    str+=i;}
                  else
                    {
                    itoa(va_arg(v,int),new_printf_buf,10);
                    strcpy(str,new_printf_buf);
                    counter+=(i=(int)strlen(new_printf_buf));
                    str+=i;
                    *str++=':'; counter++;
                    itoa(va_arg(v,int),new_printf_buf,10);
                    strcpy(str,new_printf_buf);
                    counter+=(i=(int)strlen(new_printf_buf));
                    str+=i;
                    }
                  break;
        case 'c': *str++=(char)va_arg(v,int); counter++; break;
        case 'o': if (Modifier=='l') {ltoa(va_arg(v,long),new_printf_buf,8);}
                  else {itoa(va_arg(v,int),new_printf_buf,8);}
                  fcc=new_printf_buf;
                  goto l_s;
        case 's':
                  #if 0 // 1 - proolix-d, 0 -proolix-l
                  if (Modifier=='F')
                    {fcc=va_arg(v, char  *);
                    if (fcc==(char  *)NULL) fcc="(null)";
                    }
                  else
                    {cc=va_arg(v,char *);
                    if (cc==(char *)NULL) fcc="(null)";
                    else
                      {
                      #ifdef BOOT /* compile printf for Boot Manager */
                        asm mov ax,DS; /* SS ? */
                        asm mov segment,ax;
                        fcc = MK_FP (segment, cc);
                      #else /* Compile printf for Proolix Kernel */
                      if (User)
                        {
                        asm mov ax,ProcessPar;
                        asm mov segment,ax;
                        fcc = MK_FP (segment, cc);
                        }
                      else
                        {
                        asm mov ax,DS; /* SS ? */
                        asm mov segment,ax;
                        fcc = MK_FP (segment, cc);
                        }
                      #endif
                      }
                    }
                  #else
                    fcc=va_arg(v, char  *);
                    if (fcc==(char  *)NULL) fcc="(null)";
                  #endif
                  #ifdef DEBUG
                  puts0("printf: fcc="); puts0(fcc);
                  #endif
                  l_s:
                  i=(int)strlen(fcc);
                  if (width>i)
                    {
                    if (FlagMinus)
                      {
                      strcpy(str,fcc);
                      memset(str+i,' ',width-i);
                      }
                    else
                      {int j;char c;
                      if (Type=='s') c=' ';
                      else if (FlagZero) c='0';
                      else c=' ';
                      memset(str,c,j=width-i);
                      strcpy(str+j,fcc);
                      }
                    str+=width; counter+=width;
                    }
                  else
                    {
                    strcpy(str,fcc);
                    counter+=i; str+=i;
                    }
                  break;
        case 'f':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'n':
        default: printf("printf: type '%c' not supported in this realisation",
                        Type);
        }
      }
    }
  format++;
  }
*str=0;
return counter;
}
/****************************************************************************/
int sprintf(char  *str, const char  *format, ...)
{va_list v;
va_start(v,0);
return vsprintf(str, format, v);
}

#endif // printf package

#if 0
int vprintf(const char  *format, va_list v)
{
int counter;
/* char str[MAX_LEN_STR]; */
char new_printf_buf[MAX_LEN_STR]; /* ��. ���������� � ������ �-��� printf */

va_start(v,0);
counter=vsprintf(new_printf_buf,format,v);
if(puts0(new_printf_buf)==EOF)return EOF;
return counter;
}
#endif

#if 0 // global variables NOT PERMIT!!!!!!!!!
char HexDigit [] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int Divisor8  [] = {0100000, 010000, 01000, 0100, 010, 1};
long Divisor10L [] = {1000000000L,
                      100000000L,
                       10000000L,
                        1000000L,
                         100000L,
                          10000L,
                           1000L,
                            100L,
                             10L,
                              1L};

long Divisor8L [] = {010000000000L,
                     01000000000L,
                      0100000000L,
                       010000000L,
                        01000000L,
                         0100000L,
                          010000L,
                           01000L,
                            0100L,
                             010L,
                              01L};

#endif

int htoi(const char  *s)
{
int i; char c;
i=0;
while (*s)
  {
  i<<=4;
  c=toupper(*s++);
  if ((c>='0')&&(c<='9')) i+=c-'0';
  else if ((c>='A')&&(c<='F')) i+=c+10-'A';
  else return 0;
  }
return i;
}
/****************************************************************************/
long htol(const char  *s)
{
long i; char c;
i=0;
while (*s)
  {
  i<<=4;
  c=toupper(*s++);
  if ((c>='0')&&(c<='9')) i+=c-'0';
  else if ((c>='A')&&(c<='F')) i+=c+10-'A';
  else return 0;
  }
return i;
}
/****************************************************************************/
int atoi(const char  *s)
{
int i; char c;
i=0;
if (*s=='+') s++;
else if(*s=='-')return-atoi(++s);
while (*s)
  {
  c=*s++;
  if (isdigit(c)) {i=i*10; i+=c-'0';}
  else break;
  }
return i;
}
/****************************************************************************/
long atol(const char  *s)
{
long i; char c;
i=0;
if (*s=='+') s++;
else if(*s=='-')return-atol(++s);
while (*s)
  {
  c=*s++;
  if (isdigit(c)) {i=i*10; i+=c-'0';}
  else break;
  }
return i;
}
/****************************************************************************/
#if 0
void fuck1(void)
{
int Divisor [] = {10000, 1000, 100, 10, 1};

printf("fuck1 = %04X\n",Divisor[0]);

}
#endif

#if 0 // itoa package
char  *itoa (int w, char  *str, int radix)
{
char  *ret;
int i, r, power, n;
int Divisor10 [] = {10000, 1000, 100, 10, 1};

/* printf("itoa = %04X\n",Divisor10[0]); */

if (radix>34) radix=34;

ret=str;
if (w<0) if (radix==10) {*str++='-'; itoa(-w,str,-10); return ret;}

switch(radix)
  {
  case   2: for (i=0;i<16;i++) {*str++='0'+ w & 0x8000; w<<=1;} break;
  case   8: for (i=0;i<6;i++)
              {r=w/Divisor8[i]; w%=Divisor8[i]; *str++='0'+r;}
            break;
  case  16: for (i=0;i<4;i++) {*str++=HexDigit[(w&0xF000)>>12];w<<=4;} break;
  case  10: *str++='0';
            for (i=0;i<5;i++)
              {r=w/Divisor10[i]; w%=Divisor10[i]; *str++='0'+r;
              #ifdef DEBUG
              printf("itoa: Divisor10[i]=%04X r=%04X w=%04X\n",
                Divisor10[i],r,w);
              #endif
              }
            break;
  case -10: for (i=0;i<5;i++)
              {r=w/Divisor10[i]; w%=Divisor10[i]; *str++='0'+r;
              }
            break;
  default:  power=UINT_MAX;
            for (i=1;i<16;i++) {power/=radix; if (power>0) break;}
            n=i; power=1;
            for (i=1;i<n;i++,power*=radix);
            for (i=0;i<n;i++)
              {power/=radix; r=w/power; w%=power; *str++=HexDigit[r];}
            break;
  }
*str=0;
return ret;
}
/****************************************************************************/
char  *ltoa (long w, char  *str, int radix)
{
char  *ret;
int i, n;
long r, power;

if (radix>34) radix=34;

ret=str;
if (w<0) if (radix==10) {*str++='-'; ltoa(-w,str,-10); return ret;}

switch(radix)
  {
  case  2: for (i=0;i<32;i++) {*str++='0'+ w & 0x8000; w<<=1;} break;
  case  8: for (i=0;i<11;i++)
             {r=w/Divisor8L[i]; w%=Divisor8L[i]; *str++='0'+r;}
           break;
  case 16: for (i=0;i<8;i++)
             {*str++=HexDigit[(int)((w&0xF0000000L)>>28)];w<<=4;}
           break;
  case 10: *str++='0';
           for (i=0;i<10;i++)
             {r=w/Divisor10L[i]; w%=Divisor10L[i]; *str++='0'+r;
             }
           break;
  case -10: for (i=0;i<10;i++)
              {r=w/Divisor10L[i]; w%=Divisor10L[i]; *str++='0'+r;
              }
            break;
  default: power=ULONG_MAX;
           for (i=1;i<32;i++) {power/=radix; if (power>0) break;}
           n=i; power=1;
           for (i=1;i<n;i++,power*=radix);
           for (i=0;i<n;i++)
             {power/=(long)radix; r=w/power; w%=power; *str++=HexDigit[(int)r];}
           break;
  }
*str=0;
return ret;
}
/****************************************************************************/
char  *ultoa (unsigned long w, char  *str, int radix)
{
char  *ret;
int i, n;
long r, power;

if (radix>34) radix=34;

ret=str;

switch(radix)
  {
  case  2: for (i=0;i<32;i++) {*str++='0'+ w & 0x8000; w<<=1;} break;
  case  8: for (i=0;i<11;i++)
             {r=w/Divisor8L[i]; w%=Divisor8L[i]; *str++='0'+r;}
           break;
  case 16: for (i=0;i<8;i++)
             {*str++=HexDigit[(int)((w&0xF0000000L)>>28)];w<<=4;}
           break;
  case 10: *str++='0';
           for (i=0;i<10;i++)
             {r=w/Divisor10L[i]; w%=Divisor10L[i]; *str++='0'+r;
             }
           break;
  case -10: for (i=0;i<10;i++)
              {r=w/Divisor10L[i]; w%=Divisor10L[i]; *str++='0'+r;
              }
            break;
  default: power=ULONG_MAX;
           for (i=1;i<32;i++) {power/=radix; if (power>0) break;}
           n=i; power=1;
           for (i=1;i<n;i++,power*=radix);
           for (i=0;i<n;i++)
             {power/=(long)radix; r=w/power; w%=power; *str++=HexDigit[(int)r];}
           break;
  }
*str=0;
return ret;
}
#endif // itoa package

void process_boot (void *buf)
{int i;
struct BootStru *b;

  b=buf;
#if 0
  HeadCnt=b->HeadCnt;
  TrkSecs=b->TrkSecs;
  SectorsOnCyl=HeadCnt*TrkSecs;
#endif

  if ((i=b->ResSecs)!=0) ResSecs=i; ResSecs=b->HidnSec+1;
  if ((i=b->TotSecs)!=0) MaxSectors=i;
  else MaxSectors=b->BigSect+b->HidnSec;

  CluSize=b->ClustSiz;
  CluSizeBytes=CluSize * 512;
  FatSize=b->FatSize;
  RootBeg = ResSecs + 2 * b->FatSize; // 2 - FatCnt
  RootEnd = RootBeg + ( ( b->RootSiz * 32 ) / b->SectSiz ) - 1;
  DataStart = RootEnd+1;
  MaxClusters=((MaxSectors-DataStart)/CluSize+1);
//  puts0("process_boot end\r\n");
}

void ls (void)
{
char buf[512];
unsigned char *pp;
int i,j,k, sec;
struct dirent16 *d;

puts0("RootBeg=");putdec(RootBeg);
puts0("\r\nFilename    Flags    Date                Size 1stClu 1stSector\r\n");

for(i=RootBeg;i<RootEnd;i++)
    {
    for (k=0;k<512;k++) buf[k]=0;
    secread(0,i,buf);
    pp=buf;
    for (j=0;j<16;j++)
	{
	d=(void *)pp;
	if ((*pp==0x0E5)||(*pp==0)||(d->AttrByte&8)) {pp+=32; continue;}
	for (k=0;k<11;k++) putch(d->d_name[k]);
	putch(' ');
#if 1
	if (d->AttrByte&128)	putch('*'); else putch('.');
	if (d->AttrByte& 64)	putch('*'); else putch('.');
	if (d->AttrByte& 32)	putch('A'); else putch('.');
	if (d->AttrByte& 16)	putch('D'); else putch('.');
	if (d->AttrByte&  8)	putch('L'); else putch('.');
	if (d->AttrByte&  4)	putch('S'); else putch('.');
	if (d->AttrByte&  2)	putch('H'); else putch('.');
	if (d->AttrByte&  1)	putch('R'); else putch('.');
#endif

// time 0000 0000 0000 0000
//      hhhh hmmm mmms ssss
// date 0000 0000 0000 0000
//      yyyy yyym mmmd dddd

	putch(' ');
	putdec2((d->FileDate&0x0001FU),2,0); // day
	putch('-');
	putdec2((d->FileDate&0x001E0U)>>5,2,0); // month
	putch('-');
	putdec2(((d->FileDate&0x0FE00U)>>9)+1980,4,0); // year

	putch(' ');
	putdec2((d->FileTime&0x0F800U) >> 11,2,0); // heur
	putch(':');
	putdec2((d->FileTime&0x007E0U) >> 5,2,0); // min
	putch(':');
	putdec2((d->FileTime&0x0001FU) * 2,2,0); // sec
	putch(' ');
	putdec2(d->Size,5,1); // filesize
	putch(' ');
	putdec2(sec=((d->d_fileno)&0xFFFFU),4,1); // 1st cluster
	putch(' ');
	putdec(SecForClu(sec)); // 1st sector
	puts0("\r\n");
	pp+=32;
	}
    }
}

void out_boot(void *buf)
{int i;
unsigned long DiskSize;
unsigned long TrueSectors;
struct BootStru *b;
b=buf;
puts0("Jump command ");
puthex_b((*b).Jmp[0]);
puthex_b((*b).Jmp[1]);
puthex_b((*b).Jmp[2]);

puts0("\r\nOEM name     ");
puts0((*b).OEM);

for(i=0;i<8;) {puthex_b((*b).OEM[i++]); putch(' ');}
puts0("\r\nSector size                      ");putdec((*b).SectSiz);puts0(" bytes Cluster size                ");putdec((*b).ClustSiz);
puts0(" sect\r\n");
puts0("Reserved sectors (before 1st FAT)  ");putdec((*b).ResSecs);puts0("       FAT counter                 ");putdec((*b).FatCnt);
puts0("\r\nRoot directory entries           ");putdec((*b).RootSiz);puts0("       Total sectors               ");putdec((*b).TotSecs);
puts0("\r\nMedia descr                       ");puthex_b((*b).Media);puts0("       FAT size                    ");putdec((*b).FatSize);
puts0("\r\nTrack size                        ");putdec((*b).TrkSecs);puts0(" sec   Heads                       ");putdec((*b).HeadCnt);
puts0("\r\nHidden sectors                     ");putdec((*b).HidnSec);puts0("       Big Number Of Sectors       ");putdec((*b).BigSect);
puts0("\r\nPhysical Drive No                 ");puthex_b(b->DriveNo);
//puts0(" Reserved byte              ");puthex_b((*b).Thing);
//puts0("\r\nExtended Boot Signature            ");puthex_b((*b).BootSign);
puts0("       Volume Serial No            ");puthex((*b).SerialNo[1]);putch('-');puthex((*b).SerialNo[0]);
puts0("\r\nVolume Label (in boot)  ");
for(i=0;i<11;)putch((*b).VolLbl[i++]);
puts0("\r\n                        ");
for(i=0;i<11;) puthex_b((*b).VolLbl[i++]);
puts0("\r\nFile system Id          ");
for(i=0;i<8;)putch((*b).FileSysId[i++]);
puts0("\r\n                        ");
for(i=0;i<8;)puthex_b((*b).FileSysId[i++]);
if ((*b).TotSecs==0) TrueSectors=(*b).BigSect;
else TrueSectors=(*b).TotSecs;
DiskSize=((long) (*b).SectSiz * TrueSectors)/1024l;

if (DiskSize>5000)
  {
  DiskSize/=1024;
  puts0("\r\nDisk size ");putdec(DiskSize);puts0(" Mb\r\n");
  }
else
  {
  puts0("\r\nDisk size ");putdec(DiskSize);puts0(" Kb\r\n");
  }

puts0("\r\n0 - boot sector; 1 - "); // %i - FAT\n%i-%i - root dir\n%i-%i - data area\n");
putdec(RootBeg-1);
puts0(" - FAT; ");
putdec(RootBeg);
puts0(" - ");
putdec(DataStart-1);
puts0(" - root dir; ");
putdec(DataStart);
puts0(" - ");
putdec(MaxSectors-1);
puts0(" - data area\r\n");
}

void system(void)
{
puts0("\r\nsize of int ");putdec(sizeof(int));
puts0("\r\nsize of long int ");putdec(sizeof(long int));
puts0("\r\nsize of short int ");putdec(sizeof(short int));
puts0("\r\nsize of char ");putdec(sizeof(char));
}

void memmap(void)
{
puts0("\
Memory map for Proolix-l (real mode)\r\n\
0 - 1FF  Vectors\r\n\
200 - 3FF free area (stack of boot sector)\r\n\
400 - 4FF ROM BIOS data: 475: count of HDD\r\n\
600 =0060:0000 - load kernel address (see src/stage2/boot.S, KernelSeg constant)\r\n\
end of Kernel (CT) 0060:");
puthex(end_of());
puts0("\r\n07C00 =0:7C00 (=0070:7500) Boot sector (stage1)\r\n\
07E00                      Boot sector end\r\n\
30500 (=3050:0000) stage2 (see src/boot-sector/boots.S, stage2_seg constant)\r\n\
MemTop (f.e. 9FFFF)\r\n\
A0000 EGA (in graph modes)\r\n\
B0000 MDA, Hercules 1st videopage\r\n\
B8000 CGA, EGA, VGA 1st videopage (mode=3, symbol mode)\r\n\
C8000 Additional ROM modules (2K blocks)\r\n\
E0000 Bg  AT ROM BIOS\r\n\
EFFFF End AT ROM BIOS\r\n\
F6000 ROM Basic\r\n\
FE000 ROM BIOS, POST\r\n\
FFFF0 JMP - COLD REBOOT\r\n\
FFFF5 BIOS version/date (ASCII)\r\n\
FFFFE PC/XT/AT identefication byte\r\n\
");
}

void help(void)
{
puts0("Proolix-l shell command\r\n\r\n\
test - test\r\n\
help, ? - this help\r\n\
ascii - write ascii table\r\n\
cls - clearscreen\r\n\
off - screensaver (clear screen and wait of press any key\r\n\
palette - print color palette\r\n\
system - print system parameters\r\n\
memd0 - memory dump for extended processor mode\r\n\
memd - memory dump for real mode\r\n\
memmap - print memory map\r\n\
basic - call ROM BASIC (if exist)\r\n\
diskd0 - disk dump #1 (sector/head/track)\r\n\
diskd - disk dump #2 (absolute sector)\r\n\
testdisk - test of disk\r\n\
mount - mount disk\r\n\
ls - ls\r\n\
exit, quit - exit\r\n\
");
}

void memd0(void)
{char str[MAX_LEN_STR];
int a,i,line,c;

puts0("adr? ");
getsn(str,MAX_LEN_STR);
a=(htoi(str));
//puts0("\r\nAddress = ");
//puthex_l(a);

puts0("\r\n");

#define MEMD_STEP 16

for (line=0;line<23;line++)
    {
    puthex_l(a); putch(' ');
    for (i=0;i<MEMD_STEP;i++)
	{
	c=peek(a+i);
	puthex_b(c);
	putch(' ');
	}
    for (i=0;i<MEMD_STEP;i++)
	{
	c=(peek(a+i))&0xFFU;
	if (c<' ') putch('.');
	else putch(c);
	}
    a+=MEMD_STEP;
    puts0("\r\n");
    }	
}

void memd(void)
{
char c;
int i;
char Option = 'M';
short int segm, off;
char cmd [MAX_LEN_STR];

/* Adr0 = (char *) 0; */
segm = 0;
off = 0;

puts0("Use /? command for help\r\n");

while (1)
  {
  puthex(segm);
  putch(':');
  puthex(off);
  putch(' ');
  switch (Option)
    {
    case 'A': for(i=0;i<16;i++)
                            {
                                if ((c=peek2(segm,off+i))>=' ') putch(c);
                                else putch('.');
                            }
	break;
    case 'M':
    	for(i=0;i<16;i++){puthex_b(peek2(segm,off+i));putch(' ');}
    	for(i=0;i<16;i++)
                            {
                                if ((c=peek2(segm,off+i))>=' ') putch(c);
                                else putch('.');
                            }
	break;
    case 'H': for(i=0;i<16;i++){puthex_b(peek2(segm,off+i));putch(' ');}
                          break;
    }
  puts0("\r\n");
  putch(':');
  getsn(cmd, MAX_LEN_STR);

  i=0; while (cmd[i]) if (cmd[i]=='\r') {cmd[i]=0; break;} else i++;

  if (cmd[0]=='/')
    {
    switch (c=toupper(cmd[1]))
      {
      case 'Q': puts0("\r\n"); return;
      case 'A':
      case 'H':
      case 'M': Option=c; break;
      case 'S': segm=htoi(cmd+2); break;
      case 'O': off=htoi(cmd+2); break;
      case 'K': memmap(); break;
      case 'Z': poke(htoi(cmd+2),segm,off); break;
      case '?':puts0(
"Commands:\r\n\
/Q - Quit\r\n\
/A - Ascii mode\r\n\
/H - Hex mode\r\n\
/M - Mix (hex & ascii) mode\r\n\
/S<hex_value> - set Segment\r\n\
/O<hex_value> - set Offset\r\n\
/K - print memory map\r\n\
Enter - next string\r\n\
/Z<hex_value> - poke hex_value to memory\r\n"); break;
      default: puts0("Invalid command\r\n");
      }
    puts0("\r\n");
    }
  else if (!cmd[0]) {off+=16;}
  else ;
  }
}

void diskd0(void)
{char Buffer [512];
char str[MAX_LEN_STR];
int drive, sec, head, trk, i, ii, c, line;

puts0("Drive, hex? ");
getsn(str,MAX_LEN_STR);
drive=htoi(str);

puts0("\r\nsec? (1-..., hex) ");
getsn(str,MAX_LEN_STR);
sec=htoi(str);

puts0("\r\nhead, hex? ");
getsn(str,MAX_LEN_STR);
head=htoi(str);

puts0("\r\ntrk (cyl), hex? ");
getsn(str,MAX_LEN_STR);
trk=htoi(str);

puts0("\r\nDrive = 0x");
puthex_b(drive);
puts0(" sec = 0x");
puthex(sec);
puts0(" head = 0x");
puthex(head);
puts0(" trk = 0x");
puthex(trk);

for(i=0;i<512;i++) Buffer[i]=0;

i=readsec0(drive, sec, head, trk /* or cyl */, Buffer);

if (i==1) puts0(" OK");
else {
puts0(" err code = ");
puthex(i);
}
puts0("\r\n");

ii=0;
for (line=0;line<32;line++)
    {
    if (line==15) {puts0(" press any key "); getch();putch('\r');}
    for (i=0;i<MEMD_STEP;i++)
	{
	c=Buffer[ii++];
	puthex_b(c);
	putch(' ');
	}
    ii=ii-MEMD_STEP;
    for (i=0;i<MEMD_STEP;i++)
	{
	c=(Buffer[ii++])&0xFFU;
	if (c<' ') putch('.');
	else putch(c);
	}
    puts0("\r\n");
    }	
}

void print_drive_type(char i)
{
puts0("\r\nDrive code ");
puthex_b(i);
puts0(", type ");
switch(i)
	{
	case 1: puts0("360K"); break;
	case 2: puts0("1.2M"); break;
	case 3: puts0("720K"); break;
	case 4: puts0("1.44M"); break;
	case 5: puts0("2.88M?"); break;
	case 6: puts0("2.88M"); break;
	case 7: puts0("HDD?"); break;
	case 0x10: puts0("ATAPI removable media"); break;
	default: puts0("unknown");
	}
puts0("\r\n");
}

int mount_disk(unsigned char drive)
{
puts0("\r\nmount drive ");
puthex_b(drive);
int i=GetDriveParam(drive);
if (i)
	{
	puts0("\r\n error code = ");
	puthex(i);
	puts0("\r\n");
	return -1;
	}

print_drive_type(reg_bx & 0xFFU);

int cyl = (((reg_cx & 0xFF00U)>>8)&0xFFU) | ((reg_cx & 0xC0U)<<2);

puts0(" cyl = ");
putdec(cyl);

int sec = reg_cx &0x3FU;

puts0(" sec = ");
putdec(sec);

int heads = ((reg_dx & 0xFF00U) >> 8)&0xFFU;

puts0(" heads = ");
putdec(heads);

puts0(" number of drives = ");
putdec(reg_dx & 0xFFU);

puts0(" size = ");
putdec(sec*(heads+1)*(cyl+1)/2);
puts0("K\r\n");

  HeadCnt=heads+1;
  TrkSecs=sec;
  SectorsOnCyl=HeadCnt*TrkSecs;
  MaxCyl=cyl;

return 0;
}

void mount(void)
{
char str[MAX_LEN_STR];
char drive;

puts0("drive (0-FDD1, 1-FDD2, 80-HDD1, 81-HDD2) ? ");
getsn(str,MAX_LEN_STR);
drive=htoi(str);

puts0("\r\ndrive = ");
puthex_b(drive);
puts0("\r\n");

mount_disk(drive);
}

void testdisk(void)
{
char str[MAX_LEN_STR];
char drive;

puts0("drive (0-FDD1, 1-FDD2, 80-HDD1, 81-HDD2) ? ");
getsn(str,MAX_LEN_STR);
drive=htoi(str);

puts0("\r\ndrive = ");
puthex_b(drive);
int i=GetDriveParam(drive);
if (i)
	{
	puts0("\r\n error code = ");
	puthex(i);
	puts0("\r\n");
	return;
	}

#if 0
puts0(" ax = ");
puthex(reg_ax);
puts0(" bx = ");
puthex(reg_bx);
puts0(" cx = ");
puthex(reg_cx);
puts0(" dx = ");
puthex(reg_dx);
puts0(" es = ");
puthex(reg_es);
puts0(" di = ");
puthex(reg_di);
#endif

print_drive_type(reg_bx & 0xFFU);

int cyl = (((reg_cx & 0xFF00U)>>8)&0xFFU) | ((reg_cx & 0xC0U)<<2);

puts0(" cyl = ");
putdec(cyl);

int sec = reg_cx &0x3FU;

puts0(" sec = ");
putdec(sec);

int heads = ((reg_dx & 0xFF00U) >> 8)&0xFFU;

puts0(" heads = ");
putdec(heads);

puts0(" number of drives = ");
putdec(reg_dx & 0xFFU);

puts0(" size = ");
putdec(sec*(heads+1)*(cyl+1)/2);
puts0("K\r\n");
}

void diskd(void)
{
unsigned char Buffer [512];
char str[MAX_LEN_STR];
int drive, sec, ii, c, line;
short int i;
struct MBRstru *MBR;

puts0("drive (hex, 0-FDD1, 1-FDD2, 80-HDD1, 81-HDD2) ? ");
getsn(str,MAX_LEN_STR);
drive=htoi(str);

puts0("\r\nabs sec (0-..., dec) ? ");
getsn(str,MAX_LEN_STR);
sec=atoi(str);

int quit=0;

while(!quit)

{// while
puts0("\r\ndrive = 0x");
puthex_b(drive);
puts0(" sec = ");
putdec(sec);

for(i=0;i<512;i++) Buffer[i]=0;

i=secread(drive, sec, Buffer);

if (i==1) puts0(" OK");
else {
puts0(" err code = ");
puthex(i);
}
puts0("\r\n");

ii=0;
for (line=0;line<32;line++)
    {
    if (line==15) {puts0(" press any key "); getch();putch('\r');}
    for (i=0;i<MEMD_STEP;i++)
	{
	c=Buffer[ii++];
	puthex_b(c);
	putch(' ');
	}
    ii=ii-MEMD_STEP;
    for (i=0;i<MEMD_STEP;i++)
	{
	c=(Buffer[ii++])&0xFFU;
	if (c<' ') putch('.');
	else putch(c);
	}
    puts0("\r\n");
    }
puts0("Next sector (q - quit, r - retry, b - back, V - view MBR, B - view boot, other key - next) ? \r\n");
char c=getch();
switch(c)
    {
    case 'q': quit=1; break;
    case 'r': break;
    case 'b': sec--; break;
    case 'V': 	// view_mbr begin

		puts0("System    ----Begin----       ----End-----  Prec. sec Total sec\r\n");
		puts0("          head sec  cyl       head sec cyl\r\n");
		int ii=446;
		for (i=0;i<4;i++)
		{
		switch(Buffer[ii++])
		    {
		    case 0: putch('N'); break; // no active partition
		    case 0x80U: putch('A'); break; // active partititon
		    default: putch('E'); // error
		    }

		puts0("         ");
		putdec(Buffer[ii++]); // head
		puts0("    ");
		putdec(Buffer[ii]&0x3FU); // sector
		puts0("    ");
		short int cyl=((short int)(Buffer[ii+1])) | ((Buffer[ii]&0xC0U)<<2);
		putdec(cyl); // cyl
		ii+=2;
		puts0(" ");

		out_os(Buffer[ii++]); // OS type
		puts0("     ");

		putdec(Buffer[ii++]); // head
		puts0(" ");
		putdec(Buffer[ii]&0x3FU); // sector
		puts0(" ");
		cyl=((short int)(Buffer[ii+1])) | ((Buffer[ii]&0xC0U)<<2);
		putdec(cyl); // cyl
		ii+=2;
		puts0("  ");
		
		// Horner algorythm
		long l=Buffer[ii+3]&0xFFUL;
		l=(l<<8) | Buffer[ii+2];
		l=(l<<8) | Buffer[ii+1];
		l=(l<<8) | Buffer[ii];
		putdec(l);
		puts0("  ");
		ii+=4;

		// Horner algorythm #2
		l=Buffer[ii+3]&0xFFUL;
		l=(l<<8) | Buffer[ii+2];
		l=(l<<8) | Buffer[ii+1];
		l=(l<<8) | Buffer[ii];
		putdec(l);
		ii+=4;
		puts0("\r\n");
		} // end for
		// view_mbr end
		break;
    case 'B':
		puts0("View boot not implemented yet...\r\n");
		break;
    default: sec++;
    }	
} // while
}

unsigned short int secread (int drive, unsigned AbsSec, char *Buffer)
{/* Read absolute sectors
Input:
drive (for int 13h Fn=2)
abs sec number
buffer

Output: return!=0 if error
*/
int Track, SecNoOnCyl, i;
char Head, SecOnTrk;

Track=(AbsSec/SectorsOnCyl); /*SectorsOnCyl=HeadCnt*TrkSecs,Track==Cyl */
SecNoOnCyl=(AbsSec%SectorsOnCyl);
Head=SecNoOnCyl/TrkSecs;
SecOnTrk=SecNoOnCyl%TrkSecs+1;
       /*
       2 bytes are combined to a word similar to INT 13:

        7 6 5 4 3 2 1 0  1st byte  (sector)
        | | -------------Sector offset within cylinder
        +-+--------------High order bits of cylinder #

        7 6 5 4 3 2 1 0  2nd byte  (cylinder)
        -----------------Low order bits of cylinder #
        */
if ((i=Track &0x0300)!=0)
  {
  SecOnTrk = (SecOnTrk & 0x3F) | (short int)(i>>2);
  }
return readsec0(drive, SecOnTrk, Head, Track, Buffer);
}

int SecForClu (int CluNo)
{unsigned long l;
/*
Sector=ResSecs + FatCnt*FatSize + (RootSiz*32)/SectSiz + ((CluNo-2)*ClustSiz)
       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
       DataStart
*/
if ((CluNo>MaxClusters)||(CluNo<2))
  {
  #if 0
  printf("SecForClu: Invalid cluster number. CluNo=%u, MaxClusters=%u",
  CluNo,MaxClusters);
  #endif
  return -1;
  }
l=DataStart + ( (CluNo-2) * CluSize );
#ifdef DEBUG
printf("sec4clu: return %li ",l);
#endif
return l;
}

void off (void)
{int i;
for (i=0;i<25;i++) puts0("\r\n");
getch();
}

void out_os (unsigned char c)
{
switch(c)
  { /*          Values for operating system indicator:                 */

  case 0x00: puts0("none   "); break; /* 00h    empty */
  case 0x01: puts0("FAT-12 "); break; /* 01h    DOS 12-bit FAT */
  #if 0
  case 0x02: puts0("XENIX /"); break; /* 02h    XENIX root file system */
  case 0x03: puts0("XENIX u"); break; /* 03h    XENIX /usr file system (obsolete) */
  #endif
  case 0x04: puts0("FAT-16 "); break; /* 04h    DOS 16-bit FAT < 32M */
  case 0x05: puts0("EXTEND "); break; /* 05h    DOS 3.3+ extended partition */
  case 0x06: puts0("LARGE  "); break; /* 06h    DOS 3.31+ Large File System (16-bit FAT >= 32M), "Big DOS" */
  case 0x07: puts0("HPFS/NT"); break; /* 07h    QNX */
                                       /* 07h    OS/2 HPFS */
                                       /* 07h    Windows NT NTFS */
                                       /* 07h    Advanced Unix */
  #if 0
  case 0x08: puts0("OS2 AIX"); break; /* 08h    OS/2 (v1.0-1.3 only) */
                                       /* 08h    AIX bootable partition, SplitDrive */
                                       /* 08h    Commodore DOS */
                                       /* 08h    DELL partition spanning multiple drives */
  case 0x09: puts0("AIX    "); break; /* 09h    AIX data partition */
                                       /* 09h    Coherent filesystem */
  case 0x0A: puts0("OS2 Coh"); break; /* 0Ah    OS/2 Boot Manager */
                                       /* 0Ah    OPUS */
                                       /* 0Ah    Coherent swap partition */
  #endif
  case 0x0B: puts0("FAT-32 "); break; /* 0Bh    Windows95 with 32-bit FAT */
  case 0x0C: puts0("FAT32LB"); break; /* 0Ch    Windows95 with 32-bit FAT (using LBA-mode INT 13 extensions) */
  case 0x0E: puts0("VFATLBA"); break; /* 0Eh    logical-block-addressable VFAT (same as 06h but using LBA-mode INT 13) "FAT-16 LBA" */
  case 0x0F: puts0("EXTENDL"); break; /* 0Fh    logical-block-addressable VFAT (same as 05h but using LBA-mode INT 13) "FAT-32 extended LBA" */
  #if 0
  case 0x10: puts0("OPUS   "); break; /* 10h    OPUS */
  case 0x11: puts0("OS/2   "); break; /* 11h    OS/2 Boot Manager, hidden DOS 12-bit FAT */
  case 0x12: puts0("Compaq "); break; /* 12h    Compaq Diagnostics (config) partition */
  case 0x14: puts0("OS/2   "); break; /* 14h    (resulted from using Novell DOS 7.0 FDISK to delete Linux Native part) */
                                       /* 14h    OS/2 Boot Manager hidden sub-32M 16-bit FAT partition */
  case 0x16: puts0("OS/2   "); break; /* 16h    OS/2 Boot Manager hidden over-32M 16-bit FAT partition */
  case 0x17: puts0("OS/2   "); break; /* 17h    OS/2 Boot Manager hidden HPFS partition */
  case 0x18: puts0("WinSwap"); break; /* 18h    AST special Windows swap file ("Zero-Volt Suspend" partition) */
  case 0x19: puts0("Photon "); break; /* 19h    Willowtech Photon coS */
  case 0x1E: puts0("Hiden95"); break; /* 1Eh    Hidden FAT95 */
  case 0x20: puts0("Willow "); break; /* 20h    Willowsoft Overture File System (OFS1) */
  case 0x21: puts0("reserv "); break; /* 21h    officially listed as reserved */
  case 0x23: puts0("reserv "); break; /* 23h    officially listed as reserved */
  case 0x24: puts0("NEC    "); break; /* 24h    NEC MS-DOS 3.x */
  case 0x26: puts0("reserv "); break; /* 26h    officially listed as reserved */
  case 0x31: puts0("reserv "); break; /* 31h    officially listed as reserved */
  case 0x33: puts0("reserv "); break; /* 33h    officially listed as reserved */
  case 0x34: puts0("reserv "); break; /* 34h    officially listed as reserved */
  case 0x36: puts0("reserv "); break; /* 36h    officially listed as reserved */
  case 0x38: puts0("Theos  "); break; /* 38h    Theos */
  case 0x3C: puts0("PQMagic"); break; /* 3Ch    PowerQuest PartitionMagic recovery partition */
  case 0x40: puts0("VENIX  "); break; /* 40h    VENIX 80286 */
  case 0x41: puts0("Linux  "); break; /* 41h    Linux, Personal RISC Boot */
  case 0x42: puts0("LinuxSw"); break; /* 42h    SFS (Secure File System) by Peter Gutmann */
                                       /*        Linux swap (sharing disk with DRDOS) */
  case 0x43: puts0("Linux  "); break; /* 43h    Linux native (sharing disk with DRDOS) */
  case 0x50: puts0("OnTrack"); break; /* 50h    OnTrack Disk Manager, read-only partition */
  case 0x51: puts0("NOVEL  "); break; /* 51h    OnTrack Disk Manager, read/write partition */
                                       /* 51h    NOVEL */
  case 0x52: puts0("CP/M   "); break; /* 52h    CP/M */
                                       /* 52h    Microport System V/386 */
  case 0x53: puts0("OnTrack"); break; /* 53h    OnTrack Disk Manager */
  case 0x54: puts0("OnTrack"); break; /* 54h    OnTrack Disk Manager (Dynamic Drive Overlay) */
  case 0x55: puts0("EZ     "); break; /* 55h    EZ-Drive */
  case 0x56: puts0("GoldenB"); break; /* 56h    GoldenBow VFeature */
  case 0x5C: puts0("Priam  "); break; /* 5Ch    Priam EDisk */
  case 0x61: puts0("SpeedSt"); break; /* 61h    SpeedStor */
  case 0x63: puts0("SysV386"); break; /* 63h    Unix SysV/386, 386/ix (SCO, ISC UNIX, UnixWare, ...) */
                                       /* 63h    Mach, MtXinu BSD 4.3 on Mach */
                                       /* 63h    GNU HURD */
  case 0x64: puts0("Novell "); break; /* 64h    Novell NetWare 286 */
  case 0x65: puts0("Novell "); break; /* 65h    Novell NetWare (3.11) */
  case 0x67: puts0("Novell "); break; /* 67h    Novell */
  case 0x68: puts0("Novell "); break; /* 68h    Novell */
  case 0x69: puts0("Novell "); break; /* 69h    Novell */
  case 0x70: puts0("DiskSec"); break; /* 70h    DiskSecure Multi-Boot */
  case 0x71: puts0("reserv "); break; /* 71h    officially listed as reserved */
  case 0x73: puts0("reserv "); break; /* 73h    officially listed as reserved */
  case 0x74: puts0("reserv "); break; /* 74h    officially listed as reserved */
  case 0x75: puts0("PC/IX  "); break; /* 75h    PC/IX */
  case 0x76: puts0("reserv "); break; /* 76h    officially listed as reserved */
  case 0x77: puts0("QNX    "); break; /* 77h    QNX4.x */
  case 0x78: puts0("QNX    "); break; /* 78h    QNX4.x 2nd part */
  case 0x79: puts0("QNX    "); break; /* 79h    QNX4.x 3rd part */
  #endif
  case 0x80: puts0("Minix  "); break; /* 80h    Minix v1.1 - 1.4a */
  case 0x81: puts0("Linux  "); break; /* 81h    Minix v1.4b+ */
                                       /* 81h    Linux */
                                       /* 81h    Mitac Advanced Disk Manager */
  case 0x82: puts0("Linux  "); break; /* 82h    Linux Swap partition */
                                       /* 82h    Prime */
  case 0x83: puts0("Linux  "); break; /* 83h    Linux native file system (ext2fs/xiafs) */
  #if 0
  case 0x84: puts0("OS/2   "); break; /* 84h    OS/2-renumbered type 04h partition (related to hiding DOS C: drive) */
  #endif
  case 0x85: puts0("LinuxEx"); break; /* 85h    Linux extended partition */
  case 0x86: puts0("WinNT  "); break; /* 86h    NTFS, FAT16 volume/stripe set (Windows NT) */
  case 0x87: puts0("HPFS/NT"); break; /* 87h    HPFS Fault-Tolerant mirrored partition */
                                       /* 87h    NTFS volume/stripe set */
  #if 0
  case 0x93: puts0("Amoeba "); break; /* 93h    Amoeba file system */
  case 0x94: puts0("Amoeba "); break; /* 94h    Amoeba bad block table */
  case 0xA0: puts0("Phoenix"); break; /* A0h    Phoenix NoteBIOS Power Management "Save-to-Disk" partition */
                                       /*        IBM Thinkpad hibernation partition */
  case 0xA1: puts0("reserv "); break; /* A1h    officially listed as reserved */
  case 0xA3: puts0("reserv "); break; /* A3h    officially listed as reserved */
  case 0xA4: puts0("reserv "); break; /* A4h    officially listed as reserved */
  case 0xA5: puts0("386BSD "); break; /* A5h    Net,Free,Open,386BSD and BSD/OS */
  case 0xA6: puts0("reserv "); break; /* A6h    officially listed as reserved */
  case 0xA7: puts0("NEXT   "); break; /* A7h    NEXTSTEP */
  case 0xB1: puts0("reserv "); break; /* B1h    officially listed as reserved */
  case 0xB3: puts0("reserv "); break; /* B3h    officially listed as reserved */
  case 0xB4: puts0("reserv "); break; /* B4h    officially listed as reserved */
  case 0xB6: puts0("reserv "); break; /* B6h    officially listed as reserved */
  case 0xB7: puts0("BSDI   "); break; /* B7h    BSDI file system (secondarily swap) */
  case 0xB8: puts0("BSDI   "); break; /* B8h    BSDI swap partition (secondarily file system) */
  case 0xC0: puts0("CTOS   "); break; /* C0h    CTOS */
  case 0xC1: puts0("DR DOS "); break; /* C1h    DR DOS 6.0 LOGIN.EXE-secured 12-bit FAT partition */
  case 0xC4: puts0("DR DOS "); break; /* C4h    DR DOS 6.0 LOGIN.EXE-secured 16-bit FAT partition < 32M */
  case 0xC6: puts0("DR DOS "); break; /* C6h    DR DOS 6.0 LOGIN.EXE-secured Huge partition >= 32M */
                                       /* C6h    corrupted FAT16 volume/stripe set (Windows NT) */
  case 0xC7: puts0("Syrinx "); break; /* C7h    Syrinx Boot */
                                       /* C7h    corrupted NTFS volume/stripe set */
  case 0xD8: puts0("CP/M-86"); break; /* D8h    CP/M-86 */
  case 0xDB: puts0("CP/M   "); break; /* DBh    CP/M, Concurrent CP/M, Concurrent DOS */
                                       /* DBh    CTOS (Convergent Technologies OS -Unisys) */
  case 0xE1: puts0("SpeedSt"); break; /* E1h    DOS access or SpeedStor 12-bit FAT extended partition */
  case 0xE3: puts0("DOS r/o"); break; /* E3h    DOS read-only */
                                       /* E3h    SpeedStor, Storage Dimensions */
  case 0xE4: puts0("SpeedSt"); break; /* E4h    SpeedStor 16-bit FAT extended partition < 1024 cyl */
  case 0xE5: puts0("reserv "); break; /* E5h    officially listed as reserved */
  case 0xE6: puts0("reserv "); break; /* E6h    officially listed as reserved */
  case 0xF1: puts0("Storage"); break; /* F1h    SpeedStor, Storage Dimensions */
  #endif
  case 0xF2: puts0("DOS sec"); break; /* F2h    DOS 3.3+ secondary partition */
  #if 0
  case 0xF3: puts0("reserv "); break; /* F3h    officially listed as reserved */
  case 0xF4: puts0("SpeedSt"); break; /* F4h    SpeedStor large partition, Storage Dimensions */
  case 0xF6: puts0("reserv "); break; /* F6h    officially listed as reserved */
  case 0xFE: puts0("LANstep"); break; /* FEh    LANstep */
                                       /* FEh    IBM PS/2 IML */
                                       /*        SpeedStor > 1024 cyl. */
  case 0xFF: puts0("XENIX  "); break; /* FFh    Xenix bad block table */
  #endif
  default  : puts0("unkn "); puthex_b(c);
  }
}
