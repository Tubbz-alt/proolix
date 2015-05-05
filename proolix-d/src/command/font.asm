;������������������������������������������������������ͻ
;�							�
;�	(c) G.Shepelev		All right reserved	�
;�							�
;������������������������������������������������������͹
;�							�
;�			FONT.COM			�
;�							�
;�	V 0.0			Proolix-�����		�
;�							�
;������������������������������������������������������ͼ

;	�����稪 ���᪮�� ���� ��� Proolix		(c) 1997 G.Shepelev
; ����⠥� ⮫쪮 �� EGA � VGA!

; ��᪮��� �ணࠬ�� ᤥ���� ��� ���䨪�樨, � � �������ਨ �� ���᪮�...

  IDEAL			; �������� TASM � ०��� IDEAL !	;-)


MACRO	JR  val	; ���⪨� ���室, �⮡� TASM �� ������� �� ��⨬���樨
	jmp  short  val
   ENDM

; ��।������ ��� Proolix

INT_NO	equ	84h

exit_vect EQU	0Ch	; ����� ��楤��� �����襭��

puts	EQU	7	; �뤠�� ᨬ���� ASCIIZ � stdout � ��ॢ��� ��ப�
open	EQU	24h	; ������ 䠩�
read	EQU	26h	; ������ �� 䠩�� � ����
close	EQU	28h	; ������� 䠩�

O_RDONLY  EQU	1	; ०�� ����㯠 - ⮫쪮 �⥭��


SEGMENT	seg_$	PARA	PUBLIC 'code'

  ASSUME  CS:seg_$, DS:seg_$, ES:seg_$

	ORG	100h
 

  PROC	font	FAR	; �� ��楤�� "������" � �ନ���
				; �� Proolix
start:				; ����� ⠪ ��⠥��� � �����...
	JR	real_start
	db	0DEh,0ADh	;  signature (magick)
 ENDP


  PROC	real_start	NEAR	; �� � �� ���� ��� ᤥ���� � "�������" �����!

	mov	AX,offset txt_c	; ���� ��砫쭮�� ᮮ�饭��
	push	DS		; seg 	(bug of C-compiler)
	push	AX		; offset txt
	call	_puts		; �뢮� ��砫쭮�� ᮮ�饭��
	add	SP,4

; ��।����� ࠧ��� ���୮� ������
	push	DS
	xor	AX,AX
	mov	DS,AX
	mov	AX,[485h]	; POINTS    ( 0040:0085 � ॠ���� ����� )
	pop	DS

	or	AH,AH		; �� � ��� � ���訬 ���⮬ POINTS ?
	jz	nxt_test	; �த����� �஢���...

err_mode:		; �� �� �� ᨬ���쭠� ����� ⠪��? ;)
	mov	AX,offset txt_err_mode	; ���� ᮮ�饭�� �� �訡�� �����०���
	JR	d_exit

nxt_test:
	cmp	AL,8	; ����� � ��� 8 ���祪 � �����?
	jnz	nxt0
		; ०�� � 8 ��ப��� � �����
	mov	DX,offset mode8
	mov	CX,2048
	JR	op_file

nxt0:	cmp	AL,14	; � ����� � 14? ;)
	jnz	nxt1
		; ०�� � 14 ��ப��� � �����
	mov	DX,offset mode14
	mov	CX,3584
	JR	op_file


nxt1:	cmp	AL,16	; �� ⮣�� � �筮 16!
	jnz	err_mode
		; ०�� � 16 ��ப��� � �����
	mov	DX,offset mode16
	mov	CX,4096


op_file:		; DX - ���� ����� ᮮ⢥�����饣� 䠩��
			; CX - ����� 䠩��
	mov	[f_size],AL	; �᫮ ��ப � ᨬ���쭮� �����

	; ����⨥ 䠩�� ������������
	mov	AL,O_RDONLY	; ⮫쪮 �⥭��
	push	AX		; ��ਡ�� ����㯠
	push	DS		; seg	(bug of C-compiler)
	push	DX		; offset path_name
	call	_open
	add	SP,6

	mov	[n_file],AX	; ����� ����⮣� 䠩�� ������������
	inc	AX		; 0 - �訡�� ������ 䠩��
	jnz	open_ok		; ���뫨 - �த�����

d_err:			; ��-� �� � ���浪� � ��᪮��� ����樥� :-(
	mov	AX,offset txt_derr	; ���� ᮮ�饭�� � ��᪮��� �訡��

d_exit:	push	DS		; seg	(bug of C-compiler)
	push	AX		; offset txt
	call	_puts
	add	SP,4
	jmp	[dword ptr exit_vect]	; ���ᥣ����� ��室 �� �ணࠬ��


open_ok:	; CX - ����� 䠩��
	mov	BX,200h		; ����� ᥪ��
	mov	BP,offset buff	; ���� ᮧ�������� ⠡����
	mov	SI,BP		; �� �� ���� ��砫� ����
rd_file:
	xor	AX,AX
	push	AX		; ���襥 ᫮�� ����� (bug of C-compiler)
	push	BX		; ����� �⠥��� ���樨...
	push	DS		; seg (bug of C-compiler)
	push	SI		; offset	���� ����
	push	[n_file]	; ����� 䠩��
	call	_read	; ��ᥪ�୮� �⥭�� 䠩�� (bug of Proolix)
	add	SP,10

	or	DX,DX		; ���訩 ���� ����� ������ ���� = 0
	jz	nxt2	; �ࠢ��쭮...

cl_d_err:		; �訡�� �⥭��		:-(
	call	n_close		; ������� 䠩� � �뤠�� ᮮ�饭�� �� �訡��
	JR	d_err

nxt2:	cmp	AX,BX	; � ���� ᥪ�� ��⠭?
	jnz	cl_d_err	; ������� �� ����襭��� �᫮ ����

	add	SI,BX	; ���४�� ����樨 � ����
	sub	CX,BX	; ���⮪ 䠩��
	jnz	rd_file		; �த������� �⥭�� (bug of Proolix)

		; ����㧪� ��ࠧ�� ᨬ����� � �����������
	mov	AX,1100h	; �㭪�� 0 - ����㧪� ���짮��⥫�᪮�� ����
			; ES:BP - ���� ⠡����
	mov	BH,[f_size]	; �᫮ ��ப � �����
	mov	CX,256		; �᫮ ᨬ����� � ⠡���
	xor	DX,DX		; ����� ��ࢮ�� ��।��塞��� ᨬ����
	mov	BL,DL		; ����� ����� ������������
	int	10h		; EGA � VGA �ࠧ� ������ ��� ���� ��⨢��

			; �����襭�� ࠡ���...
	call	n_close		; ������� 䠩�...
ok:	mov	AX,offset txt_ok	; ⥪�� ᮮ�饭�� �� �ᯥ譮� ����㧪�
d_e:	JR	d_exit


n_close:
	push	[n_file]	; ����� 䠩��
	call	_close
	inc	sp
	inc	sp
	ret


_close:	mov	AX,close
	JR	f_proolix

_puts:	mov	AX,puts

f_proolix:		; ���� �窠 ��� ��⥬��� �맮��� �맮��� 
	int	INT_NO
	ret	; ����, �� ���������� ����� 㤠���� ��ࠬ���� � �⥪�
		; (�������⭮ ᪮�쪮 �� �뫮)

_open:	mov	AX,open
	JR	f_proolix

_read:	mov	AX,read
	JR	f_proolix


txt_c	DB	"Font loader for EGA & VGA  Ver 0.0  (c) 1997 G.Shepelev",0
txt_err_mode	DB	"Incorrect videomode!",0
txt_derr	DB	"Disk error!",0
txt_ok	DB	"Font installed",0

mode8	DB	"08.fnt",0	; ����� 䠩��� � ��ࠧ��� ���⮢
mode14	DB	"14.fnt",0
mode16	DB	"16.fnt",0

n_file	DW	?	; ����� 䠩��
f_size	DB	?	; �᫮ ��ப � ����� ᨬ����
buff	DB	16*256 DUP (?) ; ���ᨬ���� ࠧ��� 䠩�� ������������

 ENDP
	  ENDS

	END	start
