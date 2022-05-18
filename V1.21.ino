/*
 Изменения от 16.3.18 :
 
 Добавлена ф-ция для масштабирования рабочего напряжения при помощи тумблеров для каждого канала отдельно. Sup_Scale_Read
*/

#include "board.h"

volatile unsigned char Scale_Sup1 = 2; // Делителем устанавливаем диапазон выходного напряжения 
volatile unsigned char Scale_Sup2 = 2; // ADC = 1024 поразрадный сдвиг влево на Scale_Sup

volatile unsigned char Pot1=0;		// Хранение значения потенциометров для ШИМа
volatile unsigned char Pot2=0;

volatile unsigned char Cntr = 0;	// Счетная переменная для ШИМа

/*** Режим работы выходного ШИМа для каждого канала ***/
/*** L - Влево 
	 R - Вправо
	 M - Влево макс
	 S - Вправо 
 ***/
volatile  char Pwm1_EN=0;			
volatile  char Pwm2_EN=0;

/*****************************************************/
volatile unsigned char Chan1_EN=FALSE;		// Флаг включенности канала
volatile unsigned char Chan2_EN=FALSE;

#define DEB

void check_1(void);
void check_2(void);
boolean Sup_Scale_Read(byte PIN);

SIGNAL(TIMER2_COMPA_vect)
{
/*
	Реализован программно-аппаратный ШИМ с частотой порядка 300Гц. Мало, но выше не могу
	Используется переменная Cntr для ШИМа
	Регулировка Вольтметра 1, 2, ШИМ канала 1 влево и вправо, то же для 2 канала.
*/


	Cntr++;

	// Если вольтметр 1 включен
	
if (Chan1_EN>0)
	{
		// если счет достиг значения ПОТ1 и есть разрешение тогда делаем выход VM1 = 0
		if(Cntr<Pot1) {SETBIT(OUT1_VM_PORT,OUT1_VM_PIN);}
		else		  {CLEARBIT(OUT1_VM_PORT,OUT1_VM_PIN);}
	}
else {CLEARBIT(OUT1_VM_PORT,OUT1_VM_PIN);}
// Если вольтметр 2 включен
if (Chan2_EN>0)
	{
		// если счет достиг значения ПОТ2 и есть разрешение тогда делаем выход VM2 = 0
		if(Cntr<Pot2)	{SETBIT(OUT2_VM_PORT,OUT2_VM_PIN);}
		else			{CLEARBIT(OUT2_VM_PORT,OUT2_VM_PIN);}
	}
else {CLEARBIT(OUT2_VM_PORT,OUT2_VM_PIN);}

/****
// РАБОТА ШИМ ДЛЯ 1 КАНАЛА ДВИГАТЕЛЯ
*****/

switch (Pwm1_EN)
	{	
		case 'L':	// если направление влево
			{
				OFF_1_RIGHT;	// отключаем 1 правый канал	
				
				//непосредственно ШИМ регулирование левый канал 1
				if(Cntr<Pot1) {ON_1_LEFT;}
				else		  {OFF_1_LEFT;}
			};break;
		case 'R':	// если направление вправо
			{
				OFF_1_LEFT;	// отключаем 1 левый канал	
				
				//непосредственно ШИМ регулирование правый канал 1
				if(Cntr<Pot1) {ON_1_RIGHT;}
				else		  {OFF_1_RIGHT;}
			}; break;
		case 'M':	// если направление влево MAX
			{
				OFF_1_RIGHT;	// отключаем 1 правый канал	
				ON_1_LEFT;		// включаем 1 левый канал на постоянку
			};break;
		case 'S':	// если направление вправо MAX
			{
				OFF_1_LEFT;	// отключаем 1 левый канал	
				ON_1_RIGHT;		// включаем 1 правый канал на постоянку
			};break;
			
		default: 
			{
				OFF_1_LEFT;
				OFF_1_RIGHT;
			}
	}

/****
// РАБОТА ШИМ ДЛЯ 2 КАНАЛА ДВИГАТЕЛЯ
*****/

switch (Pwm2_EN)
	{	
		case 'L':	// если направление влево
			{
				OFF_2_RIGHT;	// отключаем 2 правый канал	
				
				//непосредственно ШИМ регулирование левый канал 2
				if(Cntr<Pot2) {ON_2_LEFT;}
				else		  {OFF_2_LEFT;}
			};break;
		case 'R':	// если направление вправо
			{
				OFF_2_LEFT;	// отключаем 2 левый канал	
				
				//непосредственно ШИМ регулирование правый канал 2
				if(Cntr<Pot2) {ON_2_RIGHT;}
				else		  {OFF_2_RIGHT;}
			}; break;
		case 'M':	// если направление влево MAX
			{
				OFF_2_RIGHT;	// отключаем 2 правый канал	
				ON_2_LEFT;		// включаем 2 левый канал на постоянку
			};break;
		case 'S':	// если направление вправо MAX
			{
				OFF_2_LEFT;	// отключаем 2 левый канал	
				ON_2_RIGHT;		// включаем 2 правый канал на постоянку
			};break;
			
		default: 
			{
				OFF_2_LEFT;
				OFF_2_RIGHT;
			}
	}

	
}

void setup() {

SETBIT(OUT1_VM_DDR,OUT1_VM_PIN);
SETBIT(OUT2_VM_DDR,OUT2_VM_PIN);
SETBIT(LED_DEB_DDR,LED_DEB_PIN);
	
pinMode(OUT1_L,OUTPUT);
pinMode(OUT1_R,OUTPUT);
pinMode(OUT2_L,OUTPUT);
pinMode(OUT2_R,OUTPUT);

pinMode(LED_DEB,OUTPUT);

pinMode(LED1_L,OUTPUT);
pinMode(LED1_R,OUTPUT);
pinMode(LED2_L,OUTPUT);
pinMode(LED2_R,OUTPUT);

digitalWrite(LED1_L,HIGH);
digitalWrite(LED1_R,HIGH);
digitalWrite(LED2_L,HIGH);
digitalWrite(LED2_R,HIGH);

delay(400);

digitalWrite(LED1_L,LOW);
digitalWrite(LED1_R,LOW);
digitalWrite(LED2_L,LOW);
digitalWrite(LED2_R,LOW);

//TCCR1B = TCCR1B & 0b11111000 |0x02; // 9,10 - 4KhZ PWM
//TCCR2B = TCCR2B & 0b11111000 |0x02; // 3,11 - 4KhZ	PWM

// Timer 2 
TCCR2B=0;
TCCR2A =0;
TCCR2B |= (1<<CS20);  	// devider 1
TCCR2A |= (1<<WGM21);  	// CTC
OCR2A = 16;
TIMSK2 |= (1<<OCIE2A);	// COMP int enable

Serial.begin(115200);
analogReference(DEFAULT);

Serial.print("DC motor controll device ");
Serial.println("V1.21");

}


void loop() {

check_1();
check_2(); 


// В зависимости от положения тумблера у нас масштабируется все рабочее напряжение.
if(Sup_Scale_Read(LED1_L))	 {Scale_Sup1=3;}
else						{Scale_Sup1=2;}



if(Sup_Scale_Read(LED1_R))	 {Scale_Sup2=3;}
else						{Scale_Sup2=2;}

/* #ifdef DEB
 Serial.print ("S2=");
 Serial.println (Scale_Sup2);
#endif */
}

void check_1 (void)
/*
	Pot1 = 0-255
	Pwm1_EN = 0,L,R,S,M
	Chan1_EN = 0, 0xFF
	
	Проверка нажатия кнопок, положения тумблеров.
	Соответствующее изменение флага режима работы через переменную Pwm1_EN
	Включение или выключение полностью канала в зависимости от переменной Chan1_EN
	
	Считывание положение потенциометра через переменную Pot1
	с автоматическим скейлингом от пепеменной Scale_Sup1
	
	Управление светодиодами индикации LED1_L, LED1_R
*/
{
	
	if (digitalRead(CHAN_1)==ACTIV)
	{
		Chan1_EN = TRUE; 		
		
		Pot1=((analogRead(POT1_1))>>Scale_Sup1);	// Считываем значение с ПОТ.	
		
		/* Проверка кнопок*/
		if	(digitalRead(BUT1_L)==ACTIV)	
		{
			Pwm1_EN = 'L';
			#ifdef DEB
				Serial.println ("BUT1_L");
			#endif
			
			digitalWrite(LED1_L,HIGH);	// индикация режима.
			digitalWrite(LED1_R,LOW);	
		
		}	// Проверка кнопок
		else if	(digitalRead(BUT1_R)==ACTIV)	
		{
		
			Pwm1_EN = 'R';			
			#ifdef DEB
				Serial.println ("BUT1_R");
			#endif
			
			digitalWrite(LED1_L,LOW);// индикация режима.
			digitalWrite(LED1_R,HIGH);
		} 
		else if	(digitalRead(BUT1_ML)==ACTIV)	// Если зажали МАХ, то гоним на макс скорости в одну либо вдругую сторону 
		{
			//если было направление влево, то выставляем МАХ лево
			if 		(Pwm1_EN == 'L') {Pwm1_EN = 'M';}	
			//если было направление вправо, то выставляем МАХ право
			else if (Pwm1_EN == 'R') {Pwm1_EN = 'S';}
			
			#ifdef DEB
			Serial.println ("MAX1");
			#endif
		}
		// до того момента когда кнопка МАХ зажата, иначе остановка полная.
		else if (Pwm1_EN=='M'){Pwm1_EN = 'L';}
		else if (Pwm1_EN=='S'){Pwm1_EN = 'R';}		
	}
	else {
			Chan1_EN = FALSE; 
			digitalWrite(LED1_L,LOW);
			digitalWrite(LED1_R,LOW);
			Pwm1_EN = 0;
		 }
}
void check_2 (void)
{
	/*
	Pot2 = 0-255
	Pwm2_EN = 0,L,R,S,M
	Chan2_EN = 0, 0xFF
	
	Проверка нажатия кнопок, положения тумблеров.
	Соответствующее изменение флага режима работы через переменную Pwm2_EN
	Включение или выключение полностью канала в зависимости от переменной Chan2_EN
	
	Считывание положение потенциометра через переменную Pot2
	с автоматическим скейлингом от пепеменной Scale_Sup2
	
	Управление светодиодами индикации LED2_L, LED2_R
*/
	
	if (digitalRead(CHAN_2)==ACTIV)
	{
		Chan2_EN = TRUE; 	
				
		Pot2=((analogRead(POT2_2))>>Scale_Sup2);	// Считываем значение с ПОТ.		
		/* Проверка кнопок*/
		if	(digitalRead(BUT2_L)==ACTIV)	
		{
			Pwm2_EN = 'L';
			#ifdef DEB
			Serial.println ("BUT2_L");
			#endif
			
			digitalWrite(LED2_L,HIGH);	// индикация режима.
			digitalWrite(LED2_R,LOW);	
		
		}	// Проверка кнопок
		else if	(digitalRead(BUT2_R)==ACTIV)	
		{
			Pwm2_EN = 'R';			
			#ifdef DEB
			Serial.println ("BUT2_R");
			#endif
			
			digitalWrite(LED2_L,LOW);// индикация режима.
			digitalWrite(LED2_R,HIGH);
		} 
		else if	(digitalRead(BUT2_ML)==ACTIV)	// Если зажали МАХ, то гоним на макс скорости в одну либо вдругую сторону
		{
			//если было направление влево, то выставляем МАХ лево
			if 		(Pwm2_EN == 'L') {Pwm2_EN = 'M';}	
			//если было направление вправо, то выставляем МАХ право
			else if (Pwm2_EN == 'R') {Pwm2_EN = 'S';}
			
			#ifdef DEB
			Serial.println ("MAX2");
			#endif
		}
		// до того момента когда кнопка МАХ зажата, иначе возврат в скоростной режим.
		else if (Pwm2_EN=='M'){Pwm2_EN = 'L';}
		else if (Pwm2_EN=='S'){Pwm2_EN = 'R';}
	}
	else {
			Chan2_EN = FALSE; 
			digitalWrite(LED2_L,LOW);
			digitalWrite(LED2_R,LOW);
			Pwm2_EN = 0;
		 }
}

boolean Sup_Scale_Read(byte PIN)
// аргумент PIN		 - номер пина АЦП в любом виде. Похер что там висит и в каком изначально состоянии находится пин
// результат boolean - есть там напряжение (падение на светодиоде) или нет.
{
	
	byte state =0x00;			// для хранения состояния порта
	boolean Data = false;		// в итоге есть напряжение или нет
	unsigned int val = 0;		// храним значение АЦП
	
	state = digitalRead(PIN);	// считать предыдущее состояние выхода порта, запомнить
	digitalWrite(PIN,0);		// на всякий случай опускаем в 0 сигнал
	pinMode(PIN,INPUT);			// переконфиг на вход
	
	//asm("cli");
	delayMicroseconds(10);		// пауза для переходных процессов
	
	for (byte i = 0; i<=5;i++)
	{
		val = val+ analogRead(PIN); // делаем 5 выборок и накапливаем
	}
	val = (val>>2)/5;				// усредняем и обрезаем значение до 255 вместо 1024

	if (val > 90)	// Если там присутствует подтяжка, то значит тумблер включен
	{
		Data = true;			// Меняем состояние на трууу!
		
	}
	
	/* #ifdef DEB
			 Serial.print (PIN);Serial.print ("-");
			 Serial.println (val);
			 
	#endif */
	//asm("sei");
	
	pinMode(PIN,OUTPUT);	// снова на выход конфиг
	digitalWrite(PIN,state);// возвращаем туда что было.
	
	return Data;			// возврат результата.
	
}
