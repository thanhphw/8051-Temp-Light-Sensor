#include "lcd.h"
#include <REGX52.H>

sbit LCD_RS = P0^0;                                  
sbit LCD_RW = P0^1;                                 
sbit LCD_EN = P0^2;                                  
sbit LCD_D4 = P0^4;
sbit LCD_D5 = P0^5;                                  
sbit LCD_D6 = P0^6;
sbit LCD_D7 = P0^7;

void delay_us(int time){
	while (time--);
}

void delay_ms(unsigned int t){
	unsigned int i,j;
	for(i=0;i<t;i++)
	for(j=0;j<123;j++);
}

void LCD_Enable(){
	LCD_EN =1;
	delay_us(3);                                              
	LCD_EN=0;
	delay_us(50);
}

void LCD_Send4Bit(unsigned char Data){     
	LCD_D4=Data & 0x01;                                  //Data chuyen thanh: 0110 1101 & 0000 0001 => D4 = 1
	LCD_D5=(Data>>1)&1;                                //Data chuyen thanh: 1011 0110 & 0000 0001 => D5 = 0
	LCD_D6=(Data>>2)&1;                                //Data chuyen thanh: 0101 1011 & 0000 0001 => D6 = 1
	LCD_D7=(Data>>3)&1;                                //Data chuyen thanh: 1010 1101 & 0000 0001 => D7 = 1
}

void LCD_SendCommand(unsigned char command){
	LCD_Send4Bit(command >>4);                    //Gui 4 bit cao truoc
	LCD_Enable(); //chot LCD
	LCD_Send4Bit(command);                            //Gui 4 bit thap sau
	LCD_Enable(); //chot LCD
}

void LCD_Clear(){
	LCD_SendCommand(0x01);                          //command =1 là xoa man hinh
	delay_us(10);
}

void LCD_Init(){ //khoi tao LCD
	LCD_Send4Bit(0x00);                                    //goi hàm, D4=0x00=D5=D6=D7
	delay_ms(20);
	LCD_RS=0;                                                   //Dua Command
	LCD_RW=0;                                                 //Cho phép ghi lên màn hình
	LCD_Send4Bit(0x03);
	LCD_Enable();                                              //Chot màn hình EN
	delay_ms(5);
	LCD_Enable();
	delay_us(100);
	LCD_Enable();
	LCD_Send4Bit(0x02);                                  //Che do gui 4 bit
	LCD_Enable();
	LCD_SendCommand( 0x28 );                     //28:khoi tao 16x2 trong 4 bit mode
	LCD_SendCommand( 0x0c);                      //0C:tat con tro và cho phep hien thi
	LCD_SendCommand( 0x06 );                     //06:dich con tro qua phai
	LCD_SendCommand(0x01);                      //01:xoa man hinh
}

void LCD_Gotoxy(unsigned char x, unsigned char y){
	unsigned char address;
	if(!y) address=(0x80+x);
	else address=(0xc0+x);                              //doan code nay là de chon hang, cot de hien thi data
	delay_us(1000);                                          //chon hang 1(80) hoac hang 2(C0)
	LCD_SendCommand(address);                  //vi du:(0,0) thi ghi data o hang 1,cot 1
	delay_us(50);                                             //(0,1) thi ghi data o hang 2 cot 1
}
 
/*Gui ky tu*/
void LCD_PutChar(unsigned char Data){
	LCD_RS=1;                                                  //cho phép ghi d? li?u
	LCD_SendCommand(Data);                        //gui data hoac command
	LCD_RS=0 ;
}
void LCD_Puts(char *s){                              //*s là gia tri cua dia chi mà s tro toi
	while (*s){
	LCD_PutChar(*s);                                        //vi du: du lieu là "Nhiet do,0", khi nào gui het thi s=0
	s++;                                                           //Tang dia chi len 1 don vi
	}
}