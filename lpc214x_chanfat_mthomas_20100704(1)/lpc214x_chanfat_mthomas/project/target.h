#ifndef TARGET_H_
#define TARGET_H_

#if defined(OLIMEX_LPC_P2148) || defined(KEIL_MCB2140)

/* System configuration: Fosc, Fcclk, Fcco, Fpclk must be defined */
/* Crystal frequency, 10MHz~25MHz should be the same as actual status. */
#define Fosc	12000000

/* System frequency, should be (1~32)multiples of Fosc and should be equal or
less than 60MHz. */
#define Fcclk	(Fosc * 5)

/* CCO frequency, should be 2/4/8/16 multiples of Fcclk, ranged from 156MHz to
320MHz. */
#define Fcco	(Fcclk * 4)

/* VPB clock frequency, must be 1/2/4 multiples of (Fcclk / 4). */
#define Fpclk	(Fcclk / 4) * 4


#if defined(OLIMEX_LPC_P2148)

#define LED1_BIT            (1UL << 10)     // LED 1 - active low output
#define LED2_BIT            (1UL << 11)     // LED 2 - active low output

#define LED1ON()  ( FIO0CLR |= LED1_BIT )
#define LED1OFF() ( FIO0SET |= LED1_BIT )
#define LED2ON()  ( FIO0CLR |= LED2_BIT )
#define LED2OFF() ( FIO0SET |= LED2_BIT )

static inline void LED_init(void)
{
	FIO0DIR |= ( LED1_BIT | LED2_BIT );
}

#elif defined(KEIL_MCB2140)

#define LED1_BIT            (1UL << 16)
#define LED2_BIT            (1UL << 17)

#define LED1OFF()  ( FIO1CLR |= LED1_BIT )
#define LED1ON()   ( FIO1SET |= LED1_BIT )
#define LED2OFF()  ( FIO1CLR |= LED2_BIT )
#define LED2ON()   ( FIO1SET |= LED2_BIT )

static inline void LED_init(void)
{
	FIO1DIR |= ( LED1_BIT | LED2_BIT );
}

#endif

#else

#error "unsupported Board"

#endif

#endif /* TARGET_H_ */
