#ifndef __MMC_LIB_H_
#define __MMC_LIB_H_


extern unsigned char Mmc_Init(volatile unsigned long *port, unsigned char cspin);
extern unsigned char Mmc_Read_Sector(unsigned long sector, unsigned char *dbuff);
extern unsigned char Mmc_Write_Sector(unsigned long sector, unsigned char *dbuff);

extern unsigned char Mmc_Read_Cid(unsigned char *data_cid);
extern unsigned char Mmc_Read_Csd(unsigned char *data_csd);


#endif
