#define   SETBIT(reg, bit)          reg |= (1<<bit)            
#define   CLEARBIT(reg, bit)        reg &= (~(1<<bit))
#define   INVBIT(reg, bit)          reg ^= (1<<bit)
#define   BITISSET(reg, bit)      ((reg & (1<<bit)) != 0)
#define   BITISCLEAR(reg, bit)    ((reg & (1<<bit)) == 0)
// выход Ў»ма под двигатель 1 канал (3 вывод ардуино)
#define OUT1_L 		 3
#define OUT1_L_PORT	 PORTD
#define OUT1_L_DDR	 DDRD
#define OUT1_L_PIN 	 3

// выход Ў»ма под двигатель 1 канал (11 вывод ардуино)
#define OUT1_R		 11
#define OUT1_R_PORT	 PORTB
#define OUT1_R_DDR	 DDRB
#define OUT1_R_PIN 	 3



// выход Ў»ма под двигатель 2 канал (9 вывод ардуино)
#define OUT2_L 		 9
#define OUT2_L_PORT	 PORTB
#define OUT2_L_DDR	 DDRB
#define OUT2_L_PIN 	 1

// выход Ў»ма под двигатель 2 канал (10 вывод ардуино)
#define OUT2_R		 10
#define OUT2_R_PORT	 PORTB
#define OUT2_R_DDR	 DDRB
#define OUT2_R_PIN 	 2

// выход Ў»ма под вольтметр 1 канал (4 вывод ардуино)
#define OUT1_VM_PORT PORTD
#define OUT1_VM_DDR DDRD
#define OUT1_VM_PIN 4		

// выход Ў»ма под вольтметр 2 канал (2 вывод ардуино)
#define OUT2_VM_PORT PORTD
#define OUT2_VM_DDR DDRD
#define OUT2_VM_PIN 2		

// On the Arduino board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.

// ATMEL ATMEGA8 & 168 / ARDUINO
//
//                  +-\/-+
//            PC6  1|    |28  PC5 (AI 5) (19)
//      (D 0) PD0  2|    |27  PC4 (AI 4) (18)
//      (D 1) PD1  3|    |26  PC3 (AI 3) (17)
//      (D 2) PD2  4|    |25  PC2 (AI 2) (16)
// PWM+ (D 3) PD3  5|    |24  PC1 (AI 1) (15)
//      (D 4) PD4  6|    |23  PC0 (AI 0) (14)
//            VCC  7|    |22  GND
//            GND  8|    |21  AREF
//            PB6  9|    |20  AVCC
//            PB7 10|    |19  PB5 (D 13)
// PWM+ (D 5) PD5 11|    |18  PB4 (D 12)
// PWM+ (D 6) PD6 12|    |17  PB3 (D 11) PWM
//      (D 7) PD7 13|    |16  PB2 (D 10) PWM
//      (D 8) PB0 14|    |15  PB1 (D 9) PWM
//                  +----+
//
// (PWM+ indicates the additional PWM pins on the ATmega168.)

#define POT1_1 	A6
#define POT2_2 	A7

#define BUT1_L	17
#define BUT1_R	16
#define BUT1_ML	15
#define CHAN_1	14

#define BUT2_L	8
#define BUT2_R	7
#define BUT2_ML	6
#define CHAN_2	5

#define LED2_R	13
#define LED2_L	12
#define LED1_L	19
#define LED1_R	18

#define BUT_DELAY 	50
#define ACTIV 		LOW

#define TRUE		0xFF
#define FALSE		0x00

#define DELAY 			1000

#define LED_DEB			13  	// arduino number
#define LED_DEB_PIN		5
#define LED_DEB_DDR		DDRB
#define LED_DEB_PORT 	PORTB

#define SET_LED_DEB 	(SETBIT(LED_DEB_PORT,LED_DEB_PIN))
#define RESET_LED_DEB 	(CLEARBIT(LED_DEB_PORT,LED_DEB_PIN))

#define OFF_1_RIGHT      (CLEARBIT(OUT1_R_PORT,OUT1_R_PIN))
#define OFF_2_RIGHT      (CLEARBIT(OUT2_R_PORT,OUT2_R_PIN))
#define ON_1_RIGHT      (SETBIT(OUT1_R_PORT,OUT1_R_PIN))
#define ON_2_RIGHT      (SETBIT(OUT2_R_PORT,OUT2_R_PIN))

#define OFF_1_LEFT      (CLEARBIT(OUT1_L_PORT,OUT1_L_PIN))
#define OFF_2_LEFT      (CLEARBIT(OUT2_L_PORT,OUT2_L_PIN))
#define ON_1_LEFT       (SETBIT(OUT1_L_PORT,OUT1_L_PIN))
#define ON_2_LEFT       (SETBIT(OUT2_L_PORT,OUT2_L_PIN))