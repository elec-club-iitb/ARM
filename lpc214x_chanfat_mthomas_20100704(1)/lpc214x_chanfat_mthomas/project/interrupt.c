/*
 * Functions to handle the VIC190.
 * These functions are called from the SWI handler,
 * do not call them directly.
 */

#include <stdint.h>
#include <stdlib.h> /* NULL */
#include "LPC214x.h"
#include "interrupt.h"

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define VECT_ADDR_INDEX	0x100
#define VECT_CNTL_INDEX 0x200
#define IRQ_SLOT_EN		0x20	/* bit 5 in Vector control register */
#define VIC_SIZE		16

void ClearVector_c(void) {
	uint32_t i = 0;
	uint32_t *vect_addr, *vect_cntl;

	/* initialize VIC*/
	VICIntEnClr = 0xffffffff;
	VICVectAddr = 0;
	VICIntSelect = 0;

	/* set all the vector and vector control register to 0 */
	for (i = 0; i < VIC_SIZE; i++) {
		vect_addr = (uint32_t *) (VIC_BASE_ADDR + VECT_ADDR_INDEX + i * 4);
		vect_cntl = (uint32_t *) (VIC_BASE_ADDR + VECT_CNTL_INDEX + i * 4);
		*vect_addr = 0;
		*vect_cntl = 0;
	}

	VICProtection = 1;

	return;
}

uint32_t RegisterVector_c(uint32_t IntNumber, void *HandlerAddr, uint32_t priority,
		uint32_t class)
{
	uint32_t i;
	uint32_t *vect_addr;
	uint32_t *vect_cntl;

	VICIntEnClr = 1 << IntNumber; /* Disable Interrupt */

	if (priority == PRI_HIGHEST) {
		for (i = 0; i < VIC_SIZE; i++) {
			/* find first un-assigned VIC address for the handler */
			vect_addr = (uint32_t *) (VIC_BASE_ADDR + VECT_ADDR_INDEX + i * 4);
			vect_cntl = (uint32_t *) (VIC_BASE_ADDR + VECT_CNTL_INDEX + i * 4);
			if (*vect_addr == (uint32_t) NULL) {
				*vect_addr = (uint32_t) HandlerAddr; /* set interrupt vector */
				*vect_cntl = (uint32_t) (IRQ_SLOT_EN | IntNumber);
				if ( class == CLASS_FIQ ) {
					VICIntSelect |= (1UL << IntNumber);
				} else {
					VICIntSelect &= ~(1UL << IntNumber);
				}
				break;
			}
		}
		if (i == VIC_SIZE) {
			return (FALSE); /* fatal error, can't find empty vector slot */
		}
	} else {
		for (i = VIC_SIZE; i > 0; i--) {
			/* find first un-assigned VIC address for the handler */
			vect_addr = (uint32_t *) (VIC_BASE_ADDR + VECT_ADDR_INDEX + (i-1) * 4);
			vect_cntl = (uint32_t *) (VIC_BASE_ADDR + VECT_CNTL_INDEX + (i-1) * 4);
			if (*vect_addr == (uint32_t) NULL) {
				*vect_addr = (uint32_t) HandlerAddr; /* set interrupt vector */
				*vect_cntl = (uint32_t) (IRQ_SLOT_EN | IntNumber);
				if ( class == CLASS_FIQ ) {
					VICIntSelect |= (1UL << IntNumber);
				} else {
					VICIntSelect &= ~(1UL << IntNumber);
				}
				break;
			}
		}
		if (i == 0) {
			return (FALSE); /* fatal error, can't find empty vector slot */
		}
	}
	VICIntEnable = 1 << IntNumber; /* Enable Interrupt */
	return (TRUE);
}
