; say string

        locals

_TEXT   segment byte public 'CODE'
        assume  cs:_TEXT

sayr_proc       proc    ; ��楤�� �뢮�� ��ப� �� ����� �㭪権 BIOS
                        ; �室: DS:SI - ASCIIZ ��ப�.                        ; All registers saved
                        ; � ����᪨� ०���� �� ࠡ�⠥�
                        ; ALL REGS SAVED!
        push    ax
        push    si
        PUSHF

        cld
sayr_l1:
        lodsb
        or      al,al
        jz      sayr_ret
        mov     ah,0eh
        int     10h
        jmp     short sayr_l1
sayr_ret:
        POPF
        pop     si
        pop     ax
        ret
sayr_proc       endp
        public  sayr_proc

_TEXT   ends
        end
