#include <REGX52.H>
#include <math.h>
#include "lcd.h"
#include "adc_0808.h"


void TempShow(unsigned char temp){
	delay_us(1000);
	LCD_PutChar(temp/100+0x30);
	LCD_PutChar(temp%100/10+0x30);                    
	LCD_PutChar(temp%100%10+0x30);
}

void VoltShow(unsigned char temp){
	unsigned char te = temp;
	int a = (int)te * 19.61f ;
	int b = a/1000;
	int c = a%1000/100;
	int d = a%1000%100/10;
	int e = a%1000%100%10;
	unsigned char b1 = b;
	unsigned char c1 = c;
	unsigned char d1 = d;
	unsigned char e1 = e;
	LCD_Gotoxy(0,1);
	delay_us(1000);
	LCD_PutChar(b1+0x30);
	LCD_PutChar(c1+0x30);
	LCD_PutChar(d1+0x30);
	LCD_PutChar(e1+0x30);
}

void NhietShow(unsigned char temp){
	unsigned int y = ((100-0)*temp - 139*100 + 0*191) / (191-139); 
	if (temp > 165) y++; // hieu chinh sai so vi do phan giai thap hon muc nhiet
	delay_us(100);
	LCD_Gotoxy(0,0);
	LCD_Puts("TEMP: ");
	LCD_PutChar(y/100+0x30);
	LCD_PutChar(y%100/10+0x30);                    
	LCD_PutChar(y%100%10+0x30);
}

void QuangShow(unsigned char temp){
	float vol = temp * 5.0 / 255.0;
	float R2 = (vol*10000)/(5.0-vol);
	float E2 = pow((18000/R2),1.0/0.9)*10;
   	unsigned int y = E2;
	delay_us(100);
	LCD_Gotoxy(0,1);
	LCD_Puts("LIGHT: ");
	LCD_PutChar(y/100+0x30);
	LCD_PutChar(y%100/10+0x30);                    
	LCD_PutChar(y%100%10+0x30);
}
// chanel 1: temperature
// chanel 2: light sensor
void main(){	
	unsigned char temp;
	LCD_Init();
	ADC0808_Init();
	temp = ADC0808_Read(1);	
	delay_ms(250);
	LCD_Clear();
	NhietShow(temp);
	ADC0808_Init();
	temp = ADC0808_Read(2);
	QuangShow(temp);
	delay_ms(2000);
	
	while (1){		
		temp = ADC0808_Read(1);	
		delay_ms(50);
		LCD_Clear();
		NhietShow(temp);

		ADC0808_Init();
		temp = ADC0808_Read(2);
		QuangShow(temp);
		delay_ms(3000);	
	}
}