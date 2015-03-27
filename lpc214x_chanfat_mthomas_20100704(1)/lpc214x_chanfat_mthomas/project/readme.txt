******************************************************************************
  Demo for ChaN's FAT-module on LPC213x/214x
  Version Timestamp 20100529
  by Martin Thomas, Kaiserslautern, Germany <mthomas(at)rhrk.uni-kl.de>
******************************************************************************

/* Copyright (c) 2009, 2010
   - ChaN (FAT-Code, monitor)
   - Martin Thomas (LPC diskio-functions, modifications for LPC213x/214x)
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
******************************************************************************

Changes:
20100529
- main.c: for 8GB cards the number for free bytes is > 0xffffffff,
  using 64-bit integers and range-checks to work around 32-bit limits
  in the demo-code
- Makefile: based on newer template
- fat_sd/: update to ChaN's FatFs version R0.07e (11/2009)
- diskio.h, sd_spi_lpc2000.c: configuration-option for call-interval of
  disc_timerproc
- Makefile: Amontec JTAGkey -> JTAGkey2
- added lunch- and debug-configurations for Eclipse/gdb-HW-debugging
  (experimental, tested with OpenOCD 0.5.0-dev-snapshot (2010-04-08-15:03))
- project-specific lpc2148_12MHz.cfg for OpenOCD (12MHz ext. XTAL, PLL)
- tested with CS G++ lite for ARM EABI Version 2010q1-188 and Eclipse Galileo
- interrupt.c: new file with functions formerly located in main.c
- various minor modifications and clean-ups
- reminder: right-click project -> Index -> Rebuild 

available on request:
- efsl_glue.c/.h: glue functions to map EFSL API to FatFs API
- efsl_api_test.c/.h: test for glue-functions

******************************************************************************

This is a small demo-application to show how ChaN's FAT-Module (FatFs)
can be used to interface MM-, SD- and SDHC-Cards with a NXP LPC213x/214x
microcontroller (ARM Ltd. ARM7TDMI-S). It should work with all LPC2k 
with SSP-interface after minor modifications.

Code from others used in this project:
- Chan's FatFs
- LPC SSP code inspired by the EFSL interface-code from Mike Anton (FIFO)
  and me. Nothing has been directly copied from EFSL sources.
- a few lines from NXP's code-bundle for LPC213x/214x available
  from nxp.com

Tested with:
- Controller: NXP LPC2148, cards connected to SSP
- Board: Olimex LPC-P2148 (probably Revision A)
- Cards: extrememory 1GB performance SD-Card, SanDisk 256MB SD-Card,
         SanDisk Ultra II 4GB SDHC-Card, Traveler Highspeed 4GB SDHC,
         Fujifilm microSDHC 8GB, Kingston MircoSD 2GB

Tools:
- Compiler/Toolchain: GNU cross-toolchain for ARM (binutils, gcc)
  with newlib as libc as in the package Codesourcery G++ lite for 
  ARM EABI
- IDEs/Editors: 
  - Programmers Notepad
  - Eclipse IDE for C/C++ Developers, Additional plug-ins: 
    - CDT Hardware Debugging, Target Management Terminal, 
    - RXTX Enduser Runtime.
  - Keil uVision Eval. configured to use a GNU toolchain (Realview tools
    not supported)
- OpenOCD for "batch programming" (make program) and debugging with
  gdb and Eclipse.
- Amontec JTAGkey2 (FTDI2232H-based JTAG-interface)

******************************************************************************

Test-Session with FUJIFILM microSDHC 8GB "class2":


FatFs module test monitor for LPC213x/214x V1.0.5
using ChaN's FatFs Version 0.07E
>di 0
rc=0
>ds
Drive size: 15544320 sectors
Sector size: 512
Erase block size: 8192 sectors
MMC/SDC type: 12
CSD:
00000000  40 0E 00 32 5B 59 00 00 3B 4B 7F 80 0A 40 40 41 @..2[Y..;K...@@A
CID:
00000000  1B 53 4D 30 30 30 30 30 10 74 1F 28 E0 00 9C 39 .SM00000.t.(...9
OCR:
00000000  C0 FF 80 00 ....
SD Status:
00000000  00 00 00 00 03 00 00 00 01 01 90 00 00 01 00 00 ................
00000010  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
00000020  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
00000030  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
>fi 0
rc=0 FR_OK
>fs
FAT type = 3
Bytes/Cluster = 32768
Number of FATs = 2
Root DIR entries = 0
Sectors/FAT = 1896
Number of clusters = 242624
FAT start (lba) = 12592
DIR start (lba,cluster) = 2
Data start (lba) = 16384

1 files, 100000000 bytes.
0 folders.
7763968 KB total disk space.
7666272 KB available.
>fl
----A 2010/05/15 12:01 100000000  1  
   1 File(s),  100000000 bytes total
   0 Dir(s),     7666272 KB free
>t
2010/5/15 12:16:38
>t 2010 5 16 1 41 0
2010/5/16 01:41:00
>fo 10 2
rc=0 FR_OK
>fw 1000000 1
1000000 bytes written with 1180 kB/sec.
>fw 1000000 2
1000000 bytes written with 865 kB/sec.
>fw 1000000 3
1000000 bytes written with 514 kB/sec.
>fw 1000000 4
1000000 bytes written with 788 kB/sec.
>fw 1000000 5
1000000 bytes written with 522 kB/sec.
>fw 1000000 6
1000000 bytes written with 823 kB/sec.
>fw 1000000 7
1000000 bytes written with 516 kB/sec.
>fc
rc=0 FR_OK
>fo 10 3
rc=0 FR_OK
>fw 10000000 2
10000000 bytes written with 1082 kB/sec.
>fc
rc=0 FR_OK
>fl
----A 2010/05/15 12:01 100000000  1  
----A 2010/05/16 01:41   7000000  2  
----A 2010/05/16 01:42  10000000  3  
   3 File(s),  117000000 bytes total
   0 Dir(s),     7649632 KB free
>fo 1 2
rc=0 FR_OK
>fr 1000000
1000000 bytes read with 1390 kB/sec.
>fr 1000000
1000000 bytes read with 1315 kB/sec.
>fr 1000000
1000000 bytes read with 1256 kB/sec.
>fc
rc=0 FR_OK
>fo 10 A long Filename with Umlauts ÜÖÄüöä
rc=0 FR_OK
>fw 1 1
1 bytes written with 0 kB/sec.
>fc
rc=0 FR_OK
>fl
----A 2010/05/15 12:01 100000000  1  
----A 2010/05/16 01:41   7000000  2  
----A 2010/05/16 01:42  10000000  3  
----A 2010/05/16 01:43         1  ALONGF~1  A long Filename with Umlauts ÜÖÄüöä
   4 File(s),  117000001 bytes total
   0 Dir(s),     7649600 KB free
>t
2010/5/16 01:44:01
>t
2010/5/16 01:44:02
>


******************************************************************************

EFSL interface-layer test with 8GB SDHC-card:

Hello from efsl_debug_printf_arm

CARD initialization...ok
4294967295 bytes or more free

Directory of 'root':
1           ( 100000000 bytes )
2           ( 7000000 bytes )
3           ( 10000000 bytes )
ALONGF~1    ( 1 bytes )
LOGDAT23TXT ( 81 bytes )
File LOGDAT23.TXT open. Content:
Yet another line appended
Yet another line appended
Yet another line appended

File LOGDAT23.TXT open for append. Appending...ok

File LOGDAT23.TXT open. Content:
Yet another line appended
Yet another line appended
Yet another line appended
Yet another line appended


******************************************************************************

Output from cs-make clean all program:

C:\WinARM\examples\lpc213x_chanfat_ws\project>make clean all program
-------- begin (mode: ROM_RUN) --------
Cleaning project:
cs-rm -f ROM_RUN/lpcspi.map
cs-rm -f ROM_RUN/lpcspi.elf
cs-rm -f ROM_RUN/lpcspi.hex
cs-rm -f ROM_RUN/lpcspi.bin
cs-rm -f ROM_RUN/lpcspi.sym
cs-rm -f ROM_RUN/lpcspi.lss
cs-rm -f ROM_RUN/asmfunc.o ROM_RUN/main.o ROM_RUN/comm.o ROM_RUN/rtc.o ROM_RUN/m
onitor.o ROM_RUN/ff.o ROM_RUN/fattime.o ROM_RUN/ccsbcs.o ROM_RUN/sd_spi_lpc2000.
o
cs-rm -f ROM_RUN/asmfunc.lst ROM_RUN/main.lst ROM_RUN/comm.lst ROM_RUN/rtc.lst R
OM_RUN/monitor.lst ROM_RUN/ff.lst ROM_RUN/fattime.lst ROM_RUN/ccsbcs.lst ROM_RUN
/sd_spi_lpc2000.lst
cs-rm -f ROM_RUN/dep/asmfunc.o.d ROM_RUN/dep/main.o.d ROM_RUN/dep/comm.o.d ROM_R
UN/dep/rtc.o.d ROM_RUN/dep/monitor.o.d ROM_RUN/dep/ff.o.d ROM_RUN/dep/fattime.o.
d ROM_RUN/dep/ccsbcs.o.d ROM_RUN/dep/sd_spi_lpc2000.o.d
cs-rm -f main.s comm.s rtc.s monitor.s fat_sd/ff.s fat_sd/fattime.s fat_sd/optio
n/ccsbcs.s fat_sd/sd_spi_lpc2000.s
cs-rm -f
cs-rm -f
cs-rm -f
-------- end --------
arm-none-eabi-gcc (Sourcery G++ Lite 2009q3-68) 4.4.1
Copyright (C) 2009 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

**** Assembling (ARM-only): asmfunc.S -> ROM_RUN/asmfunc.o
arm-none-eabi-gcc -c -mcpu=arm7tdmi-s -mthumb-interwork -I. -x assembler-with-cp
p -D__ASSEMBLY__ -DVECT_TAB_ROM -DROM_RUN -DLPC2148 -Wa,-adhlns=ROM_RUN/asmfunc.
lst -Wa,-gdwarf-2 -Ifat_sd asmfunc.S -o ROM_RUN/asmfunc.o
**** Compiling C : main.c -> ROM_RUN/main.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi-s -mthumb-interwork
-DVECT_TAB_ROM -DROM_RUN -DLPC2148 -Ifat_sd -I. -ffunction-sections -fdata-secti
ons -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -Wsh
adow -Wcast-qual -Wcast-align -pedantic -Wa,-adhlns=ROM_RUN/main.lst -MD -MP -MF
 ROM_RUN/dep/main.o.d -Wnested-externs  -std=gnu99 main.c -o ROM_RUN/main.o
**** Compiling C : comm.c -> ROM_RUN/comm.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi-s -mthumb-interwork
-DVECT_TAB_ROM -DROM_RUN -DLPC2148 -Ifat_sd -I. -ffunction-sections -fdata-secti
ons -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -Wsh
adow -Wcast-qual -Wcast-align -pedantic -Wa,-adhlns=ROM_RUN/comm.lst -MD -MP -MF
 ROM_RUN/dep/comm.o.d -Wnested-externs  -std=gnu99 comm.c -o ROM_RUN/comm.o
**** Compiling C : rtc.c -> ROM_RUN/rtc.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi-s -mthumb-interwork
-DVECT_TAB_ROM -DROM_RUN -DLPC2148 -Ifat_sd -I. -ffunction-sections -fdata-secti
ons -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -Wsh
adow -Wcast-qual -Wcast-align -pedantic -Wa,-adhlns=ROM_RUN/rtc.lst -MD -MP -MF
ROM_RUN/dep/rtc.o.d -Wnested-externs  -std=gnu99 rtc.c -o ROM_RUN/rtc.o
**** Compiling C : monitor.c -> ROM_RUN/monitor.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi-s -mthumb-interwork
-DVECT_TAB_ROM -DROM_RUN -DLPC2148 -Ifat_sd -I. -ffunction-sections -fdata-secti
ons -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -Wsh
adow -Wcast-qual -Wcast-align -pedantic -Wa,-adhlns=ROM_RUN/monitor.lst -MD -MP
-MF ROM_RUN/dep/monitor.o.d -Wnested-externs  -std=gnu99 monitor.c -o ROM_RUN/mo
nitor.o
**** Compiling C : fat_sd/ff.c -> ROM_RUN/ff.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi-s -mthumb-interwork
-DVECT_TAB_ROM -DROM_RUN -DLPC2148 -Ifat_sd -I. -ffunction-sections -fdata-secti
ons -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -Wsh
adow -Wcast-qual -Wcast-align -pedantic -Wa,-adhlns=ROM_RUN/ff.lst -MD -MP -MF R
OM_RUN/dep/ff.o.d -Wnested-externs  -std=gnu99 fat_sd/ff.c -o ROM_RUN/ff.o
**** Compiling C : fat_sd/fattime.c -> ROM_RUN/fattime.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi-s -mthumb-interwork
-DVECT_TAB_ROM -DROM_RUN -DLPC2148 -Ifat_sd -I. -ffunction-sections -fdata-secti
ons -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -Wsh
adow -Wcast-qual -Wcast-align -pedantic -Wa,-adhlns=ROM_RUN/fattime.lst -MD -MP
-MF ROM_RUN/dep/fattime.o.d -Wnested-externs  -std=gnu99 fat_sd/fattime.c -o ROM
_RUN/fattime.o
**** Compiling C : fat_sd/option/ccsbcs.c -> ROM_RUN/ccsbcs.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi-s -mthumb-interwork
-DVECT_TAB_ROM -DROM_RUN -DLPC2148 -Ifat_sd -I. -ffunction-sections -fdata-secti
ons -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -Wsh
adow -Wcast-qual -Wcast-align -pedantic -Wa,-adhlns=ROM_RUN/ccsbcs.lst -MD -MP -
MF ROM_RUN/dep/ccsbcs.o.d -Wnested-externs  -std=gnu99 fat_sd/option/ccsbcs.c -o
 ROM_RUN/ccsbcs.o
**** Compiling C : fat_sd/sd_spi_lpc2000.c -> ROM_RUN/sd_spi_lpc2000.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi-s -mthumb-interwork
-DVECT_TAB_ROM -DROM_RUN -DLPC2148 -Ifat_sd -I. -ffunction-sections -fdata-secti
ons -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -Wsh
adow -Wcast-qual -Wcast-align -pedantic -Wa,-adhlns=ROM_RUN/sd_spi_lpc2000.lst -
MD -MP -MF ROM_RUN/dep/sd_spi_lpc2000.o.d -Wnested-externs  -std=gnu99 fat_sd/sd
_spi_lpc2000.c -o ROM_RUN/sd_spi_lpc2000.o

**** Linking : ROM_RUN/lpcspi.elf
arm-none-eabi-gcc -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi-s -mthumb-interwork   -DV
ECT_TAB_ROM -DROM_RUN -DLPC2148 -Ifat_sd -I. -ffunction-sections -fdata-sections
 -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -Wshado
w -Wcast-qual -Wcast-align -pedantic -Wa,-adhlns=ROM_RUN/asmfunc.lst -MD -MP -MF
 ROM_RUN/dep/lpcspi.elf.d ROM_RUN/asmfunc.o ROM_RUN/main.o ROM_RUN/comm.o ROM_RU
N/rtc.o ROM_RUN/monitor.o ROM_RUN/ff.o ROM_RUN/fattime.o ROM_RUN/ccsbcs.o ROM_RU
N/sd_spi_lpc2000.o --output ROM_RUN/lpcspi.elf -nostartfiles -Wl,-Map=ROM_RUN/lp
cspi.map,--cref,--gc-sections  -lc  -lm  -lc -lgcc  -TLPC2148-ROM.ld
Creating load file: ROM_RUN/lpcspi.hex
arm-none-eabi-objcopy -O ihex ROM_RUN/lpcspi.elf ROM_RUN/lpcspi.hex
Creating load file: ROM_RUN/lpcspi.bin
arm-none-eabi-objcopy -O binary ROM_RUN/lpcspi.elf ROM_RUN/lpcspi.bin
Creating Extended Listing/Disassembly: ROM_RUN/lpcspi.lss
arm-none-eabi-objdump -h -S -C -r ROM_RUN/lpcspi.elf > ROM_RUN/lpcspi.lss
Creating Symbol Table: ROM_RUN/lpcspi.sym
arm-none-eabi-nm -n ROM_RUN/lpcspi.elf > ROM_RUN/lpcspi.sym
Size after build:
arm-none-eabi-size -A  ROM_RUN/lpcspi.elf
ROM_RUN/lpcspi.elf  :
section            size         addr
.text             20692            0
.data                 4   1073741824
.bss              19580   1073741828
.stack             1536   1073761408
.ARM.attributes      46            0
.comment            336            0
.debug_aranges      896            0
.debug_pubnames     893            0
.debug_info       14421            0
.debug_abbrev      3226            0
.debug_line        4731            0
.debug_frame       2952            0
.debug_str         2507            0
.debug_loc        19139            0
.debug_ranges      1024            0
Total             91983


Programming with OPENOCD
./OpenOCD/bin/openocd -d0 -f interface/jtagkey2.cfg -f target/lpc2148.cfg -c "ad
apter_khz 500" -c init -c "arm7_9 dcc_downloads enable" -c "arm7_9 fast_memory_a
ccess enable" -c targets -c "soft_reset_halt" -c "reset init" -c "wait_halt 100"
 -c "flash write_image erase ROM_RUN/lpcspi.elf" -c "verify_image ROM_RUN/lpcspi
.elf" -c "reset run" -c shutdown
Open On-Chip Debugger 0.5.0-dev-snapshot (2010-04-08-15:03)
Licensed under GNU GPL v2
For bug reports, read
        http://openocd.berlios.de/doc/doxygen/bugs.html
debug_level: 0
RCLK - adaptive
adapter_nsrst_delay: 200
jtag_ntrst_delay: 200
trst_and_srst srst_pulls_trst srst_gates_jtag trst_push_pull srst_open_drain
500 kHz
dcc downloads are enabled
fast memory access is enabled
    TargetName         Type       Endian TapName            State
--  ------------------ ---------- ------ ------------------ ------------
 0* lpc2148.cpu        arm7tdmi   little lpc2148.cpu        running
requesting target halt and executing a soft reset
target state: halted
target halted in ARM state due to debug-request, current mode: Supervisor
cpsr: 0x000000d3 pc: 0x00000000
target state: halted
target halted in Thumb state due to debug-request, current mode: User
cpsr: 0x60000070 pc: 0x0000120a
core state: ARM
auto erase enabled
wrote 24576 bytes from file ROM_RUN/lpcspi.elf in 1.156250s (20.757 kb/s)
verified 20696 bytes in 0.218750s (92.393 kb/s)
shutdown command invoked

C:\WinARM\examples\lpc213x_chanfat_ws\project>