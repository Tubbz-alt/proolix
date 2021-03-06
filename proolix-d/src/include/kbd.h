/*      kbd.h

        BIOS keyboard status

        Copyright (c) Serge Pustovoitoff 1999

*/

#ifndef KBD_H
#define KBD_H

/* From [PC Help]
        BIOS keyboard flags (located in BIOS Data Area 40:17)

                񽼖񽔼񼭢񼆈�
                 � � � � � � � 滥哪� right shift key depressed
                 � � � � � � 滥哪哪 left shift key depressed
                 � � � � � 滥哪哪� CTRL key depressed
                 � � � � 滥哪哪哪 ALT key depressed
                 � � � 滥哪哪哪� scroll-lock is active
                 � � 滥哪哪哪哪 num-lock is active
                 � 滥哪哪哪哪� caps-lock is active
                 滥哪哪哪哪哪 insert is active
*/

#define R_SHIFT 1
#define RIGHT_SHIFT 1
#define L_SHIFT 2
#define LEFT_SHIFT 2
#define CTRL 4
#define CONTROL 4
#define ALT 8
#define SCROLL_LOCK 0x10
#define NUM_LOCK 0x20
#define CAPS_LOCK 0x40
#define INS 0x80
#define INSERT 0x80

#endif
