/*
 * EFSL to FatFS interface demo
 * Copyright (c) 2010 Martin Thomas, 3BSD license
 */

#include <stdint.h>
#include <string.h>
#include "efs.h"
#include "ls.h"
#include "mkfs.h"
#include "interfaces/efsl_dbg_printf_arm.h"

#include "comm.h"     /* uart0_put */
#include "monitor.h"  /* xprintf et al */

EmbeddedFileSystem efs;
EmbeddedFile filer, filew;
DirList list;
unsigned short e;
unsigned char buf[513];
static char LogFileName1[] = "LOGDAT31.TXT";

static inline int dbg_putc(int b)
{
	uart0_put(b);
	return 1;
}

void efsl_api_test1(void)
{
	int8_t res;
	uint32_t free_bytes;

#if !EFSL_GLUE_DEBUG_PRINTF
#warning "efsl_debug_*_arm disabled"
#endif

	efsl_debug_devopen_arm(dbg_putc);
	efsl_debug_printf_arm("Hello from efsl_debug_printf_arm\n");
	DBG(TXT("(testing DBG(TXT(...))\n"));

	xprintf("\nCARD initialization...");
	if ((res = efs_init( &efs, 0 )) != 0) {
		xprintf("failed with %d\n",res);
	}
	else {
		xprintf("ok\n");

		/* myFs.volumeID is not supported by the efsl-glue-functions.
		   Use this to get the number of free bytes: */
		free_bytes = fat_diskfree(&efs.myFs);
		xprintf("%lu bytes ", free_bytes);
		if (free_bytes == UINT32_MAX) {
			xprintf("or more ");
		}
		xprintf("free\n\n");

		xprintf("Directory of 'root':\n");
		if (ls_openDir(&list, &(efs.myFs) , "/") == 0) {;
			while (ls_getNext(&list) == 0) {
				list.currentEntry.FileName[LIST_MAXLENFILENAME-1] = '\0';
				xprintf("%s ( %lu bytes, %c )\n" ,
					list.currentEntry.FileName,
					list.currentEntry.FileSize,
					(list.currentEntry.Attribute & ATTR_DIRECTORY) ? 'D' : 'F');
			}
		} else {
			xprintf("ls_openDir error\n");
		}

		if (file_fopen(&filer, &efs.myFs , LogFileName1 , 'r') == 0) {
			xprintf("File %s open. Content:\n", LogFileName1);
			while ((e = file_read( &filer, 512, buf)) != 0) {
				buf[e]='\0';
				xputs_raw((char*)buf);
			}
			xprintf( "\n" );
			file_fclose( &filer );
		} else {
			xprintf("Failed to open file for read.\n");
		}

		if (file_fopen(&filew, &efs.myFs , LogFileName1 , 'a') == 0) {
			xprintf("File %s open for append. Appending...", LogFileName1);
			strcpy((char*)buf, "Yet another line appended\r\n");
			if (file_write(&filew, strlen((char*)buf), buf) == strlen((char*)buf)) {
				xprintf("ok\n\n");
			}
			else {
				xprintf("fail\n\n");
			}
			file_fclose(&filew);
		} else {
			xprintf("Failed to open file for write.\n");
		}

		if (file_fopen(&filer, &efs.myFs , LogFileName1 , 'r') == 0) {
			xprintf("File %s open. Content:\n", LogFileName1);
			while ((e = file_read( &filer, 512, buf)) != 0) {
				buf[e]='\0';
				xputs_raw((char*)buf);
			}
			xprintf("\n");
			file_fclose( &filer );
		}

		fs_umount( &efs.myFs ) ;
	}
}

