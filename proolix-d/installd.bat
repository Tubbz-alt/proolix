@echo off
cls
echo ��������������������������������������������������������������������Ŀ
echo � ���⠫���� �� Proolix �� ࠧ��� d: FAT-12                         �
echo �                                                                    �
echo � Installator (install.bat) version D-0.0.3.1  24-Feb-98             �
echo �                                                                    �
echo � ��⠫��, � ���஬ �ᯠ����� 䠩� slime?.arj                      �
echo � ������ ���� ⥪�騬.                                               �
echo �                                                                    �
echo � ����, ���-ᥪ�� ��᪠ � Master Boot Record, � ⠪�� ���         �
echo � ���ଠ��, ᮤ�ঠ���� �� ��᪥, ����� ���� �����祭� !          �
echo � ������ CTRL BREAK, �᫨ �� ��।㬠��.                            �
echo � � ��⨢��� ��砥 ������ ANY KEY                                 �
echo ����������������������������������������������������������������������
pause>nul
cls
src\boot\bp -d@ boot.mbr
src\boot\bp -d3 -i -a0 boot.mbr
src\boot\bp -d4 -i src\boot\booth12.bin
copy src\bm\boot d:\boot > nul
echo Kernel to disk d:
copy src\kernel\kernel d:\kernel > nul
echo on
REM
REM Doc to disk d:
copy *.doc d:\
REM
REM Files description to disk d:
copy files.bbs d:\
REM
REM Utilities to disk d:
mkdir d:\bin
copy src\command\kernel.ovl d:\ > nul
REM a:
REM cd \bin
REM c:
copy src\command\*. d:\bin
REM Fonts to disk d:
copy src\command\*.fnt d:\bin
REM
REM Man
mkdir d:\usr
mkdir d:\usr\man
copy man\*.* d:\usr\man
REM
REM Installation done.
REM Reboot, please, from diskette a:
REM Press, please, Ctrl Alt Del
REM
goto End
:Error
echo !
echo ! Installation error
echo !
:End
