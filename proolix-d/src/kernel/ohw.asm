; ohw

        locals

_TEXT   segment byte public 'CODE'
        assume  cs:_TEXT

        extrn   ohb:near

ohw     proc

;       �뢮� ᫮�� � HEX-����. �室: ᫮�� � ax.
;       �� ॣ����� ��࠭�����.
;       ��뢠�� ����ணࠬ�� ohb

        push    ax      ; ����. ࠤ� al.
        mov     al,ah
        call    ohb
        pop     ax      ; �����. al.
        call    ohb
        ret
ohw     endp

        public  ohw

_TEXT   ends
        end
