#define BUFLEN 100
#define CMDLEN 17

#include "headers.h"

// global variables NOT USED! NOT WORK! BIKOZ .RSS SEGMENT NOT ADRESSED IN BIN FILE!

#if 0
void palette(void)
{int i;
for (i=0;i<256;i++) {if (i%16==0) puts0("\r\n");set_color(i); puts0("W");}
set_color(7); puts0("end of palette");
}
#endif

#ifdef PEMU // code for Proolix emulator under Linux
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include "liblinux.c"
#include "libemu.c"

int disk_a;

char arguments [100];

#endif

void print_time(void)
{
short int ii, hours;

ii=get_rtc();

if (mytimezone)
	{
	hours=((ii&0xF000)>>12)*10 + ((ii&0x0F00)>>8);
	//puts0("debug hours=");putdec(hours);puts0("\r\n");
	hours+=mytimezone;
	if (hours>=24) hours-=24;
	ii=(ii&0xFF) | ((hours/10)<<12) | ((hours%10)<<8);
	}

	puts0("time ");
	puthex(ii);

	ii=get_day();
	puts0(" day ");
	puthex(ii);

	ii=get_year();
	puts0(" year ");
	puthex(ii);
	puts0("\r\n");

}

void version (void)
{
#ifdef PEMU
	printf("Proolix emulator. q for quit\n");
#endif
puts0("\r\nProolix-l shell. Compiled ");
puts0(__DATE__);
puts0(" ");
puts0(__TIME__);
puts0("\r\n");
//pause();
puts0("? - for help\r\n");
puts0("End of code "); puthex(end_of()); puts0(" = "); putdec(end_of()); puts0("\r\n");
}

/************************************** main() *****************************************/
#ifndef PEMU
void main(void)
#else
int main (int argc, char **argv)
#endif
{
char command [CMDLEN];
char buf [BUFLEN];
int i,j;
char c,cc;
char bootsector[512];
//unsigned short int drive, reg_bx, reg_cx, reg_dx;
//unsigned short int cyl, sectors, heads, total_sec;
char *pp;
#ifdef PEMU
FILE *cfg;
#endif

if (firstboot)
 {// begin firstboot
 firstboot=0;

#ifndef PEMU
//putch('/');
putch_color('@', 4);
#endif

#ifdef PEMU

printf("Proolix emulator--------------------------------------------------\n");
mytimezone=0;
buf[0]=0;
cfg=0;

switch (argc)
	{
	case 1: /* pemu */
		cfg=fopen("pemu.cfg","r");

		if (cfg==NULL) printf("\npemu.cfg not found\n");
		else printf("\npemu.cfg found\n");
		break;
	case 2: /* pemu imagename */
		break;
	case 3: /* pemu imagename command */
		break;
	default: /* argc>2 :: pemu imagename command parameters... */
		;
	}

if (cfg)
	{
	buf[0]=0;
	fgets(buf,BUFLEN,cfg);
	pp=strchr(buf,0x0A);
	if (pp) *pp=0;
	disk_a=open(buf,O_RDWR);
	printf("disk A = '%s'\n", buf);
	}
else
	{
	if (argc==1) {printf("Usage: pemu [imagename] [command] [parameters]\n"); return 1;}
	disk_a=open(argv[1],O_RDWR);
	printf("disk A = '%s'\n", argv[1]);
	}

if (disk_a==-1) {printf("Diskette image file not opened\n"); return 2;}

puts("");

//puts0("\nProolix emulator. q for quit\n");
#endif

version();

print_time();

print_boot();

// test disk drives

for (i=0;i<4;i++)
	{ // i = 0, 1, 2, 3
	if (i==2) drive=0x80; else if (i==3) drive=0x81; else drive=i;
	// drive = 0, 1, 0x80, 0x81
	reg_bx=GetDriveParam_bx(drive);
	//puts0("debug GetDriveParam bx  cx  dx "); puthex(reg_bx);
	if (reg_bx==0xFFFF) {
		gCyl[i]=0;
		gSec[i]=0;
		gHeads[i]=0;
		gTotal[i]=0;
		continue;}

	reg_cx=GetDriveParam_cx(drive);
	reg_dx=GetDriveParam_dx(drive);
	//puts0(" "); puthex(reg_cx); puts0(" "); puthex(reg_dx); puts0("\r\n"); // debug

	cyl = (((reg_cx & 0xFF00U)>>8)&0xFFU) | ((reg_cx & 0xC0U)<<2);

	sectors = reg_cx &0x3FU;

	heads = ((reg_dx & 0xFF00U) >> 8)&0xFFU;
	heads++;

	total_sec=(sectors*heads*(cyl+1));

	gCyl[i]=cyl;
	gSec[i]=sectors;
	gHeads[i]=heads;
	gTotal[i]=total_sec;
	}

puts0("Cyl Sec Heads Total\r\n");
for (i=0;i<4;i++)
{
putdec(gCyl[i]);
puts0(" ");
putdec(gSec[i]);
puts0(" ");
putdec(gHeads[i]);
puts0(" ");
putdec(gTotal[i]);
puts0("\r\n");
}

 }//end firstboot

#ifdef PEMU
if (argc>2)
	if (argv[2])
		{
		//printf("argv[2]='%s'\n", argv[2]);
		if (!strcmp(argv[2],"exit")) return 0;
		else if (!strcmp(argv[2],"fromhost"))
			{
			if (argc<4) {printf("no filename\n"); return 4;}
			if (argv[3])
				{
				printf("parameter='%s'\n", argv[3]);
				from_host2(argv[3]);
				}
			else
				printf("empty parameter\n");
			return 0;
			}
		else
			{
			printf("Invalid batch command '%s'\n", argv[2]);
			return 3;
			}
		}
#endif

while (1)
	{
	puts0("\r\nEnter command -> ");
		for(i=0;i<CMDLEN;i++) command[i]=0;
	getsn(buf,BUFLEN);
	pp=strchr(buf,' ');
	if (pp==0)
		{// аргументов нет
		strncpy(command,buf,CMDLEN);
		arguments[0]=0;
		}
	else
		{// аргументы есть
		strncpy(arguments,pp+1,BUFLEN);
		*pp=0;
		strncpy(command,buf,CMDLEN);
		}
#if 0 // debug
	puts0("command ='");
	puts0(command);
	puts0("' arguments='");
	puts0(arguments);
	puts0("'\r\n");
#endif
	puts0("\r\n");

	if (command[0]==0) puts0("");
	else if (!strcmp(command,"ver")) version();
	else if (!strcmp(command,"help")) help();
	else if (!strcmp(command,"?")) help();
	else if (!strcmp(command,"reboot")) reboot();
	else if (!strcmp(command,"cold")) cold();
	else if (!strcmp(command,"hdd0")) hdd0();
	else if (!strcmp(command,"hdd1")) hdd1();
	else if (!strcmp(command,"fdd"))  fdd();
	else if (!strcmp(command,"test")) test();
	else if (!strcmp(command,"ascii")) ascii();
	else if (!strcmp(command,"sysinfo")) sysinfo();
	else if (!strcmp(command,"memd0")) memd0();
	else if (!strcmp(command,"memd")) memd();
	else if (!strcmp(command,"memmap")) memmap();
	else if (!strcmp(command,"basic")) basic();
	else if (!strcmp(command,"diskd0")) diskd0();
	else if (!strcmp(command,"diskd")) diskd();
	else if (!strcmp(command,"off")) off();
	else if (!strcmp(command,"vec")) vectors();
	else if (!strcmp(command,"sk")) skript();
	else if (!strcmp(command,"scr")) screensaver();
	else if (!strcmp(command,"time")) print_time();
	else if (!strcmp(command,"install")) install();
	else if (!strcmp(command,"format")) format();
	else if (!strcmp(command,"super")) view_superblock();
	else if (!strcmp(command,"ls")) ls();
	else if (!strcmp(command,"create")) create_file3();
	else if (!strcmp(command,"append")) append();
	else if (!strcmp(command,"tofile")) tofile();
	else if (!strcmp(command,"tofile2")) tofile2();
	else if (!strcmp(command,"rm")) remove_file();
	else if (!strcmp(command,"cat")) cat();
	else if (!strcmp(command,"hcat")) hexcat();
	else if (!strcmp(command,"dd")) dd();
	else if (!strcmp(command,"settimezone")) settimezone();
	else if (!strcmp(command,"videomod")) videomod_();
	else if (!strcmp(command,"run")) load_and_run();
	else if (!strcmp(command,"rundos")) load_and_run_msdos();
#ifdef PEMU
	else if (!strcmp(command,"fr")) from_host();
	else if (!strcmp(command,"sh")) system("sh");
	else if (!strcmp(command,"quit")) return 0;
	else if (!strcmp(command,"q")) return 0;
#endif
	else
		{short int fexec;
		unsigned short int load_segment, offset;
		fexec=open_(command,O_READ);
		if (fexec!=-1) {//puts0("file exists!\r\n");
			load_segment=0x4050; offset=0;
			while(readc(0,&c)==0)
				{
				poke(c,load_segment,offset++);
				}
			//puts0("\r\nEXEC!\r\n");
			close_(fexec);
			run();}
		else {puts0("Unknown command '");
		puts0(command);
		puts0("'\r\n"); }
		}
	}
}

#include "clib.c"
