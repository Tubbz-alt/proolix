# 1 "end.S"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "end.S"
# ��� �����, ������� �������

.code16

.text

.global Buff
.global FATaddr

Buff:	.byte	# buffer for 1 cluster

FATaddr	=	Buff+512*1	# buffer for FAT
				# � ������ ������ ������ FAT - 9 ��������
