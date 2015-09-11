@GetChAtr       MACRO   page    ; ���� ��ਡ�⮢ ᨬ���� -> AH
;               �।���⥫쭮 ������ ���� �����⥭ ����� ⥪�饩 ��࠭���.
;               ��� ���� �������� � ��ࠬ��� page.
;               �� 㬮�砭�� ����� ��࠭��� - 0.

;               ��. ����� @GetAtr

                IFNB    <page>
                mov     bh,page
                ELSE
                sub     bh,bh
                ENDIF
                mov     ah,08h
                int     10h
                ENDM    @GetChAtr

@cls            MACRO
                ; �� ॣ����� ��࠭���
                push    ax
                push    bx
                push    cx
                push    dx
                push    BP      ; ���࠭���� BP, ����� ������� ����� ��
                                ; �맮��� int 10h

                @GetChAtr
                mov     bl,bh
                mov     bh,ah
                sub     cx,cx
                mov     dx,184Fh
                mov     ax,0600h
                int     10h
                mov     bh,bl
                sub     dx,dx
                mov     ah,02h
                int     10h

                pop     BP
                pop     dx
                pop     cx
                pop     bx
                pop     ax
                ENDM    @cls

                ; ������������������� ������������

; (C) Copyright Serge Pustovoitoff, 1995
;       FidoNet 2:461/35
;       E-mail prool@infocom.kharkov.ua
;       BBS in Kharkov - phone 007 24h 5 lines
;       ���⮢� ����: 310168, ���쪮�, �/� 2996.

; �� ��� ���ப������� ������ ��� ��࠭��� ॣ����� (ࠧ㬥����, �஬� ��,
; � ����� ����頥��� ��室��� १����), ���� � ������������ � �����
; ������������ �� ������� ����.

GetPage         MACRO   ; ����� ⥪. ��࠭��� -> BH
;               �������� �� ���������: AX, BH
                mov     ah,0fh
                int     10h
                ENDM    GetPage

say     macro   str
; � ����᪨� ०���� �� ࠡ�⠥�
        push    si
        lea     si,str  ; �뫮 mov si,offset str
        call    sayr_proc
        pop     si
        endm    say

sayr    macro   str
; � ����᪨� ०���� �� ࠡ�⠥�
        push    si
        lea     si,str  ; �뫮 mov si,offset str
        call    sayr_proc
        pop     si
        endm    sayr

chr     macro   sym     ; via BIOS
        ; Not worked in graph mode (bl - bg color!)
        push    ax

        mov     al,sym
        mov     ah,0eh
        int     10h

        pop     ax
        endm    chr

chr1    macro   sym     ; via BIOS
        ; Not worked in graph mode (bl - bg color!)
        push    ax

        mov     al,sym
        mov     ah,0eh
        int     10h

        pop     ax
        endm    chr1

inkey   macro
        ; ���� ������ ᨬ���� � ���������� � ��������� ��� �� � ॣ���� AL
        ; �᫨ AL=0 � � AH ���뫠���� ���७�� ��� ���� - � AH ���뫠����
        ; ᪥�-���.

        ; � �⫨稥 �� inkey � inkey1 ����� ����� �ॡ�� ������������ �맮��
        ; ��� ॠ�樨 �� ����������� ASCII �������.

        ; �� �६� �������� ॠ��� �� CTRL-BREAK ����, ॠ�樨 �� CTRL-C ���.
        ; �� �६� �������� popup �ணࠬ�� TECH HELP ��뢠����.

        ; ������ ॣ���� AX

        mov     ah,00h
        int     16h

        endm    inkey

inkey2  macro
        ; ���� ������ ᨬ���� � ���������� � ��������� ��� �� � ॣ���� AL
        ; �᫨ AL=0 � � AH ���뫠���� ���७�� ��� ���� - � AH ���뫠����
        ; ᪥�-���.

        ; � �⫨稥 �� inkey � inkey1 ����� ����� �ॡ�� ������������ �맮��
        ; ��� ॠ�樨 �� ����������� ASCII �������.

        ; �� �६� �������� ॠ��� �� CTRL-BREAK ����, ॠ�樨 �� CTRL-C ���.
        ; �� �६� �������� popup �ணࠬ�� TECH HELP ��뢠����.

        ; ������ ॣ���� AX

        mov     ah,00h
        int     16h

        endm    inkey2
