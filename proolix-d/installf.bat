@echo off
cls
echo 旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커
echo � 댂飡젷ワ與� 럱 Proolix 췅 ㄸ稅β� a:                               �
echo �                                                                    �
echo � 뒥�젷��, � ぎ獸昔� �졹캙ぎ쥯� �젵� slime?.arj                      �
echo � ㄾウ�� 〓筍 收ゃ蟯�.                                               �
echo �                                                                    �
echo � 볡殊收, ▲�-醒も�� ㄸ稅β� � ㏇�                                   �
echo � Þ兒席졿⑨, 貰ㄵ逝좈좑碎 췅 ㄸ稅β�, Мｃ� 〓筍 쭬��暹��� !!!      �
echo � 뜝━ⓥ� CTRL BREAK, αエ 귣 ��誓ㅳ쵟エ 聲筌猶졻藺� � Proolix'��.   �
echo � � �昔殊˛�� 笹晨젰 췅━ⓥ� ANY KEY                                 �
echo 읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸
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