# Proolix-l boot sector for HDD

# russian text in UTF-8

# by Serge Pustovoitoff, 1993-2016

#include	"macros.S"

# Смещение, связанное с тем, что во время компиляции
# адресом начала является 0, а во время
# выполнения 0x7c00

off     =     0x7c00

Drive   =     0x80       # HDD 0

stage2_seg          =     0x3050       # Сегментный адрес, куда будет
                                       # загружен stage2

        .code16
	.text

.global _start
_start:

Begin:          jmp     start
message:	.ascii	"MBR"
		.byte 13,10,0
TrkSecs:         .word      17
HeadCnt:         .word      4

start:
#        pushw   %CS
#        popw    %DS
#        print    message+off

	call	print_registers

# get drive parameters
	movb	$8,%ah
	movb	$Drive,%dl
	int	$0x13

#	call	print_registers

# Значения регистров после загрузки из boot-сектора дискеты
# CS:IP = 0:7C00 SS=30 SP=F6 ES=0

# /* 0:0 - 0:200 - таблица прерываний */
# Стек: c 30:F6 (0:3F6) растет к 0 (0:200-0:400 - стек)
# ROM BIOS area 0:400-0:500

#       cli
        # Модификация diskette param table (взято из бута MSDOS 6.0)
	# нужен ли в нижеследующей команде префикс ES: ?
#	lds  %es:(0x78),%si # DS:si - vector diskette param table

/*
                movb    $0xf,9(%si)  # head settle := f 
                movw    TrkSecs+off,%cx # TrkSecs
                movb    %cl,6(%si) # Data Transfer Length
#               sti
                movb    $Drive,%dl
                xorw    %ax,%ax
                int     $0x13   # Disk  %dl=drive %ah=func 00
                                # reset disk, %al=return status
                jc      l_err
		proolfool
*/
        pushw   %CS
        popw    %ES

        pushw   %CS
        popw    %DS

	movw	$stage2_seg,%ax
	movw	%ax,%ES
	xorw	%bx,%bx

	movw	$1, %ax
	movw	$127, %cx		# number of blocks: читаем с запасом

loop1:  # Загрузка stage2 посекторно
        # имени ядра
        pushw   %cx

        pushw   %ax
        movb    $Drive,%dl
        pushw   %ax
        call    SecRead
        jc      l_err
        popw    %ax

#               pushw   %ax
#               CHR1    'R'
#               popw    %ax

        popw    %ax
        incw    %ax

	addw	$512,%bx
        popw    %cx
        loop    loop1

        # EXEC!

#       sayr    OEM+off

        movw    $stage2_seg,%ax
        movw    %ax,%DS
	movw	%ax,%ES		# set ES register
        cli
        movw    %ax,%SS
        movw    $0xfffe,%SP
        sti
	movw	$0xDDDD,%ax	# DDDD - magick, boot from HDD

        .byte      0xea    # JMP stage2_seg:0000
        .word      0x0000,stage2_seg

l_err:
        putch   $'e'
        putch	$'r'
        call    ohw
        xorb    %ah,%ah
        int     $0x16
        int     $0x19
#Vis:    jmp     short Vis

SecRead:        # Read absolute sectors
                # Input: %ax - abs sec number
                #        %dl - drive (for int 0x13 Fn=2)
                #        ES:%bx - buffer

                # Use global variables:
                # word ptr HeadCnt+off
                # word ptr TrkSecs+off

                # Output: cf=1 if error
                # NO ALL REGS SAVED !!!

#       pushw    %ax
        pushw    %bx
        pushw    %cx
        pushw    %dx
        pushw    %si
        pushw    %di
 
        movw    %bx,%si   # save %bx & %dx
        movw    %dx,%di

        PUSHW    %ax

        movw    HeadCnt+off,%ax
        movw    TrkSecs+off,%cx
        mul     %cx      # %dx:%ax := HeadCnt * TrkSecs
        movw    %ax,%bx  # %bx = HeadCnt * TrkSecs

        POPW     %ax
        xorw     %dx,%dx   # %dx:%ax - Abs Sec No
        div     %bx # %ax=Track=AbsSec/(HeadCnt*TrkSecs); %dx - mod (Sec on Cyl)

        movw    %ax,%bx   # %bx - track no

        movw    %dx,%ax
        xorw    %dx,%dx   # %dx:%ax - module (Sec on Cyl)
        div     %cx # Head=[%dx:%ax]/TrkSecs;%ax - Head; mod (%dx) - Sec on Head-1
        incw    %dx # %dx - Sec on Head

#        movw    $1,%cx
#l_loop:
#        pushw    %cx

        movb     %dl,%cl    # sector
        movb     %bl,%ch    # track ; Warning: track < 255 !!!
        movw     %si,%bx    # Restore %bx - offset for buff
        movw     %di,%dx    # Restore %dl - drive no
        movb     %al,%dh    # head
        movw     $0x201,%ax # Fn=02, Read 1 sector
        int      $0x13
#        jnc     l_break

#        popw     %cx
#        loop    l_loop
#        jmp     l_ret
#l_break:
#        popw     %cx
l_ret:
        popw     %di
        popw     %si
        popw     %dx
        popw     %cx
        popw     %bx
#       popw     %ax

        ret
# SecRead endp

ohw: #     proc

#       Вывод слова в HEX-виде. Вход: слово в %ax.
#       Все регистры сохраняются.
#       Вызывает подпрограмму ohb

        pushw    %ax      # Сохр. ради %al.
        movb     %ah,%al
        call    ohb
        popw     %ax              # Восст. %al.
        call    ohb
        ret
# ohw     endp
ohb: #     proc

# Procedure output hex byte Ver 0.1.1 6 Dec 93 via BIOS
# Input: %al - byte
# All regs. reserved ;)

# Not worked in graph mode. bl - bg color !!!

        pushw    %ax
        pushw    %cx
        pushw    %dx

        movb     %al,%dl
        movb     $4,%cl
        shrb     %cl,%al
        call    ohb1

        movb    %dl,%al
        andb    $0xf,%al
        call    ohb1

        popw     %dx
        popw     %cx
        popw     %ax

        ret

# ohb     endp

ohb1: #    proc    # Regs not saved !!!
        pushw    %ax

        cmpb     $9,%al
        ja      l_1    # %al > 9
        # %al <= 9
        addb     $0x30,%al	# addb '0',%al
        jmp     l_out

l_1:   addb     $0x37,%al #  addb    'A'-10,%al 
l_out: movb     $0xe,%ah
        int     $0x10

        popw     %ax

        ret
# ohb1    endp

#include "sayr.S"
#include "saycsip.S"

/*
	. = 446
	# partition
	.byte 0x80 # partition bootable (active)
	.byte 0
	.byte 1
	.byte 1
	.byte 1 # FAT12 ;)
	.byte 3
	.byte 17
	.byte 166
	.word 68
	.word 0
	.word 11288
	.word 0
proolfool
*/

	. = 510
	.word 0xAA55

/*
	. = 512
	jmp	l_2
	.byte 0xDE
	.byte 0xAD
l_2:	putch $'0'
	putch $'k'
l_stop: jmp l_stop

*/
