/* ��������� ��堭���� ��⥬��� �맮��� */

int ParLen, Alpha, Beta;
int user_ax, user_ss, user_sp;

void interrupt SysCall2()
{
/*
� �⮩ �㭪樨 imho ����� �ᯮ�짮���� ������� ��६����. (???)
*/

/* CS ᥩ�� 㪠�뢠�� �� ��, � DS/SS/SP �� �᪨� �����, �맢��訩
����� �맮� */
/* ���࠭���� ���ﭨ� (ॣ���஢) �����, �맢��襣� system call */
/*
;       push    ax
;       push    bx
;       push    cx
;       push    dx
;       push    es
;       push    ds
;       push    si
;       push    di
;       push    bp
;       mov     bp,DGROUP
;       mov     ds,bp
                                ; � ����� � DS 㪠�뢠�� �� ��
*/
Mode=0; /* Mode kernel */
asm     mov     bp,sp

asm     mov     user_ax,ax

asm     mov     ax,SS
asm     mov     user_ss,ax

asm     mov     ax,BP; /* � BP ����� �㦭�� ��� ��࠭���� �᪮� SP */
asm     mov     user_sp,ax

#if 0
/* ��⠭�������� 拉�� SS/SP */
asm     cli
asm     mov     ax,50H
asm     mov     SS,ax
asm     mov     ax,0FFFEh
asm     mov     SP,ax
asm     mov     BP,SP
asm     sti
#endif

/* ����஢���� ��ࠬ��஢ �� �⥪� � �⥪ */
ParLen=SysTable[user_ax].ParNo*2;
asm     sub     SP,ParLen;
asm     mov     Alpha,SS;
asm     mov     Beta,SP;
memcpy(MK_FP(Alpha,Beta), MK_FP(user_ss,user_sp+26), ParLen);
/* �맮� �㭪樨, ॠ�����饩 ����� ��⥬�� �맮� */
(SysTable[user_ax].Entry)();
asm     add     SP,ParLen;
asm     mov     Alpha,ax;
asm     mov     Beta,dx;
Mode=1; /* Mode user */

/* �������뢠�� � �⥪, ��� ��࠭��� ॣ�����, ���祭��, �����饭���
��⥬�� �맮��� � ॣ����� AX � DX */
*(int far*)MK_FP(user_ss,user_sp+16)=Alpha;
*(int far*)MK_FP(user_ss,user_sp+10)=Beta;

/*  ����⠭������� �᪨� ss sp */
asm     cli
Global=user_ss;
asm     mov     ax,Global
asm     mov     SS,ax
Global=user_sp;
asm     mov     ax,Global;
asm     mov     SP,ax
asm     sti
}
