@echo off
cls
echo ��������������������������������������������������������������������Ŀ
echo � ���⠫���� �� Proolix �� a: � c: (boot manager �� a:, �� �� c: )�
echo �                                                                    �
echo � Installator (install.bat) version H-0.0.2.1 30-Sep-98              �
echo �                                                                    �
echo � ��⠫��, � ���஬ �ᯠ����� 䠩� slime?.arj                      �
echo � ������ ���� ⥪�騬.                                               �
echo � � ���ன�⢥ a: ������ ���� ���� ��᪥�!                        �
echo �                                                                    �
echo � ����, ���-ᥪ��� ��᪠ � ��᪥��, � ⠪�� ���                   �
echo � ���ଠ��, ᮤ�ঠ���� �� ��᪥ � ��᪥�, ����� ���� �����祭� !�
echo � ������ CTRL BREAK, �᫨ �� ��।㬠��.                            �
echo � � ��⨢��� ��砥 ������ ANY KEY                                 �
echo ����������������������������������������������������������������������
pause>nul
cls
src\boot\bp -d0 -i -y src\boot\boots.bin
if errorlevel 1 goto Error
echo Boot manager to diskette a:
copy src\bm\booth a:\boot > nul
echo Kernel to disk c:
copy src\kernel\kernel c:\kernel > nul
echo on
REM
REM Doc to disk c:
copy *.doc c:\
REM
REM Files description to disk c:
copy files.bbs c:\
REM
REM Utilities to disk c:
mkdir c:\bin
copy src\command\kernel.ovl c:\ > nul
REM a:
REM cd \bin
REM c:
copy src\command\*. c:\bin
REM Fonts to disk c:
copy src\command\*.fnt c:\bin
REM
REM Man
mkdir c:\usr
mkdir c:\usr\man
copy man\*.* c:\usr\man
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
