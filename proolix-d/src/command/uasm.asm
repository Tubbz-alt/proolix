;       Proolix external asm-utility

;        include ..\kernel\macros.asm
        include syscall.h

;        .286

        .model tiny
        .code
;        org     0
;Revert  label   dword
;        org     100h

_main   proc    near    ; �� ��砫� ������� �ணࠬ��
        public  _main

;extrn   _saycsip:near
;        call    _saycsip

        ;       ��窠 �. (��. ����)

;        pusha
;        popa

        mov     ax,'A'  ; ��⠫������ � �⥪ ���� (� �����⢥���) ��ࠬ���
        push    ax      ; ��⥬���� �맮��

        mov     ax,0deadh ; �������� �⥪ �� 1 ᫮�� ��� ᮢ���⨬���
        push    ax        ; � �맮���� �� �ணࠬ� �� �

        mov     ax,putch        ; �� ��⥬�� �맮� putch
        int     INT_NO

        add     sp,4    ; �����頥� �⥪ � ��室��� ���ﭨ�, ����� �� ��
                        ; � �窥 �
        ret             ; ������ � ��㫨��
_main   endp

        end