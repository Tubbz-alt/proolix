@echo off
cls
echo 旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커
echo � 댂飡젷ワ與� 럱 Proolix 췅 �젳ㄵ� d: FAT-12                         �
echo �                                                                    �
echo � Installator (install.bat) version D-0.0.3.1  24-Feb-98             �
echo �                                                                    �
echo � 뒥�젷��, � ぎ獸昔� �졹캙ぎ쥯� �젵� slime?.arj                      �
echo � ㄾウ�� 〓筍 收ゃ蟯�.                                               �
echo �                                                                    �
echo � 볡殊收, ▲�-醒も�� ㄸ稅� � Master Boot Record, � �젶┘ ㏇�         �
echo � Þ兒席졿⑨, 貰ㄵ逝좈좑碎 췅 ㄸ稅�, Мｃ� 〓筍 쭬��暹��� !          �
echo � 뜝━ⓥ� CTRL BREAK, αエ 귣 ��誓ㅳ쵟エ.                            �
echo � � �昔殊˛�� 笹晨젰 췅━ⓥ� ANY KEY                                 �
echo 읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸
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
