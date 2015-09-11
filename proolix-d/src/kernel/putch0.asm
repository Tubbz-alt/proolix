_TEXT   segment byte public 'CODE'
        assume  cs:_TEXT

        extrn   _TextAttr:byte
        extrn   VideoPage:near

_putch0 proc    near
        push    bp
        mov     bp,sp
        push    ax
        push    bx
        push    cx

        mov     al,byte ptr [bp+4]
        cmp     al,10
        je      l_CRLF
        cmp     al,13
        je      l_CRLF
        ; set color

        ; 09H ����� ᨬ���/��ਡ�� � ⥪�饩 ����樨 �����
        ; �室:  BH = ����� ����� ��࠭���
        ;   AL = �����뢠��� ᨬ���
        ;   CX = ���稪 (᪮�쪮 ������஢ ᨬ���� �������)
        ;   BL = ����� ��ਡ�� (⥪��) ��� 梥� (��䨪�)
        ;        (����᪨� ०���: +80H ����砥� XOR � ᨬ����� �� �࠭�)
        call    VideoPage
        mov     ah,9
        mov     al,' '
        mov     cx,1
        mov     bl,_TextAttr
        int     10h

        ; byte ptr [bp+4] - argument 1
        mov     al,byte ptr [bp+4]
l_CRLF: mov     ah,0eh
        int     10h

        pop     cx
        pop     bx
        pop     ax
        xor     ah,ah
        pop     bp
        ret
_putch0 endp
public  _putch0

_TEXT   ends
        end
