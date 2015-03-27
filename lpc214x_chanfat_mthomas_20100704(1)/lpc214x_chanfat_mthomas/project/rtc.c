/* LPC RTC Handling */

#include "LPC214x.h"
#include "rtc.h"

BOOL rtc_gettime (RTC *rtc)
{
	DWORD d, t;


	do {
		t = CTIME0;
		d = CTIME1;
	} while (t != CTIME0 || d != CTIME1);

	rtc->sec   = t & 63;
	rtc->min   = (t >> 8) & 63;
	rtc->hour  = (t >> 16) & 31;
	rtc->wday  = (t >> 24) & 7;
	rtc->mday  = d & 31;
	rtc->month = (d >> 8) & 15;
	rtc->year  = (d >> 16) & 4095;

	return TRUE;
}




BOOL rtc_settime (const RTC *rtc)
{
	/* Stop RTC */
	CCR = 0x12;

	/* Update RTC registers */
	SEC   = rtc->sec;
	MIN   = rtc->min;
	HOUR  = rtc->hour;
	DOW   = rtc->wday;
	DOM   = rtc->mday;
	MONTH = rtc->month;
	YEAR  = rtc->year;

	/* Start RTC with external XTAL */
	CCR = 0x11;

	return TRUE;
}


