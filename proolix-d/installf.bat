@echo off
cls
echo ��������������������������������������������������������������������Ŀ
echo � ���⠫���� �� Proolix �� ��᪥�� a:                               �
echo �                                                                    �
echo � ��⠫��, � ���஬ �ᯠ����� 䠩� slime?.arj                      �
echo � ������ ���� ⥪�騬.                                               �
echo �                                                                    �
echo � ����, ���-ᥪ�� ��᪥�� � ���                                   �
echo � ���ଠ��, ᮤ�ঠ���� �� ��᪥�, ����� ���� �����祭� !!!      �
echo � ������ CTRL BREAK, �᫨ �� ��।㬠�� ��뢠���� � Proolix'��.   �
echo � � ��⨢��� ��砥 ������ ANY KEY                                 �
echo ����������������������������������������������������������������������
pause>nul
cls
src\boot\bp -d0 -i -y src\boot\boots.bin
if errorlevel 1 goto Error
echo Boot manager to diskette a:
copy src\bm\bootf.bin a:\boot
echo Kernel to diskette a:
copy src\kernel\kernel.bin a:\kernel
echo on
REM
REM Files description to diskette a:
copy files.bbs a:\
REM
REM Utilities to diskette a:
mkdir a:\bin
copy src\command\kernel.ovl a:\
REM a:
REM cd \bin
REM c:
copy src\command\*. a:\bin
REM Fonts to diskette a:
copy src\command\*.fnt a:\bin
del a:\bin\makefile
REM Man to diskette
mkdir a:\usr
mkdir a:\usr\man
copy man\*.* a:\usr\man
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