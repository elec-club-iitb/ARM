@echo off
set DBG=3
start OpenOCD\bin\openocd.exe -d%DBG% -f interface/jtagkey2.cfg -f lpc2148_12MHz.cfg -c init -c "jtag_khz 500" -c targets
rem  -c "reset init"
start telnet localhost 4444
rem pause