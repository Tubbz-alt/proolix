_TEXT   segment byte public 'CODE'
        assume  cs:_TEXT

_ReadPhysSec    proc
; int ReadPhysSec (unsigned char drive, unsigned char sec, unsigned char head,
; unsigned char trk /* or cyl */, char *Buffer);

;       /*
;       2 bytes are combined to a word similar to INT 13:
;
;       �7�6�5�4�3�2�1�0� 1st byte  (sector)
;        � � ������������� Sector offset within cylinder
;        ���������������� High order bits of cylinder #
;
;       �7�6�5�4�3�2�1�0� 2nd byte  (cylinder)
;        ������������������ Low order bits of cylinder #
;        */

; ALL REGS SAVED
        push    bp
        mov     bp,sp
        push    bx
        push    cx
        push    dx
        push    ES

        push    DS
        pop     ES

        mov     dl,byte ptr [bp+ 4] ; drive
        mov     cl,byte ptr [bp+ 6] ; sec
        mov     dh,byte ptr [bp+ 8] ; head
        mov     ch,byte ptr [bp+10] ; trk
        mov     bx,word ptr [bp+12] ; Buffer
        mov     ax,0201h; Fn=02, Read 1 sector
        int     13h
        jc      @@err
        xor     ax,ax
        jmp     @@ret

@@err:
;       mov     ax,-1
@@ret:

        pop     ES
        pop     dx
        pop     cx
        pop     bx
;       mov     sp,bp
        pop     bp

        ret
_ReadPhysSec    endp
public  _ReadPhysSec

_TEXT   ends
        end
