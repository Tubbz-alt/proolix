    .code16
    .text

    .global sayr_proc

sayr_proc: # proc       Ver 0.0.2 19-Oct-2004
                        # ��������� ������ ������ ��� ������ ������� BIOS
                        # ����: %DS:%si - ASCIIZ ������.
                        # REGS SAVED !!!
# � ����������� ������� �� ��������
	pushw	%ax
	
#       cld
sayr_l1:
        lodsb
        orb     %al,%al
        jz      sayrret
        movb    $0x0e,%ah
        int     $0x10
        jmp     sayr_l1
sayrret:
	popw	%ax
        ret
