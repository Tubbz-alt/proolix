/* rand.c - pseudorandom numbers generation */
/* rand() srand() */
/*
� NICE.SOURCES (2:461/35.301)
 Msg  : 34 of 167
 From : Al xCruel                   2:4653/1.8              Fri 07 Apr 95 12:00
 To   : Jura Lobunets
 Subj : H���! ������� ��砩��� �ᥫ!
��������������������������������������������������������������������������������
.MSGID: 2:4653/1.8 f85748e0
.REPLY: 2:463/212.5 2f71f91a
.PID: timEd-g2+
.TID: FastEcho 1.41/g 1995
Jura Lobunets wrote in a message to All:

 JL>  �祭� ���� subj!

   � ����, ������ �����樨 �ᥢ����砩��� �ᥫ
� ���ࢠ�� ��⭮� 2 ⠪��:

   - ��६ ᤢ����� ॣ����,
   - �����뢠�� � ���� ���⮢�� ���祭��,

 | (����� 横��筮)
 |
 | - ����砥� �ᥢ����砩��� �᫮ �� ॣ���� (!),
 | - ��६ ��� 2 ॣ���� � �������㥬 ���,
 | - ��६ ��� 1 ॣ���� � XOR'�� ��� � ��������� 2 ��⮬,
 | - ��६ ��� 0 ॣ���� � XOR'�� ��� � �।��騬 १���⮬,
 | - ����稢訩�� � �⮣� ��� ����娢��� � ���訩 ࠧࠤ ॣ����,
 | - ᤢ����� ॣ����,
 |
 | (横� �� ������⢮ ����権)

   �����⢥��� ������⮪ - �ய�᪠���� �������樨 ⨯� 1010 �
0101 � �.�. � ᮮ⢥��⢨� � ࠧ�來�����.
   ��! ���⠫ �� �� � ����� 㬭�� �㪥, ⠬ �� ���⨭�� �뫠:

   ----- - - - - - - - - - -------------
   | N |                   | 2 | 1 | 0 |   Shift register
   ----- - - - - - - - - - -------------
     ^                       |   |   |
     |                       |   |   |
     |  -------              |   |   |
     ---| XOR O<--------------   |   |
        |     |<------------------   |
        |     |<----------------------
        -------

bk00l! Al XCRUEl.

---
 * Origin: la sagrada familia (2:4653/1.8)
.PATH: 4653/1 51/2 5100/8 5020/251 144 400 461/21 35
*/
static unsigned int RandomSave;

int rand (void)
{unsigned int reg, bit;
reg=RandomSave;
bit=((!(reg&4))^(reg&2))^(reg&1);
reg>>=1;
reg|=(bit<<15);
RandomSave=reg;
if (reg<0) reg=-reg;
return reg;
}

void srand (unsigned seed)
{
RandomSave=seed;
}
