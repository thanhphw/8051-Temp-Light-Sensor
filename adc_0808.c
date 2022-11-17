#include "adc_0808.h"
#include <REGX52.H>
#define ADC0808_DATA P1
sbit ADC0808_A = P2^0;
sbit ADC0808_B = P2^1;                             //A,B,C la chân chon cong tin hieu ADC
sbit ADC0808_C = P2^2;
sbit ADC0808_ALE = P2^3;                         //chan chot dia chi
sbit ADC0808_START = P2^4;                     //chan bao bat dau chuyen doi
sbit ADC0808_EOC = P2^5;                        //EOC kiem tra xem da chuyen doi xong chua
sbit ADC0808_OE = P2^6;                          //mang du lieu da chuyen doi ra khoi ADC
sbit ADC0808_CLK = P2^7; 

void ADC0808_Init(){
	ADC0808_START = 0;	
	ADC0808_ALE = 0;
	ADC0808_OE = 0;
}


unsigned char ADC0808_Read(unsigned char channel){
	unsigned char kq;                                      // khai báo bien ket qua
	ADC0808_A = channel & 0x01;
	ADC0808_B = channel & 0x02;                 //8051 lua chon kenh du lieu
	ADC0808_C = channel & 0x04;
	ADC0808_ALE = 1;                                    //kích hoat chân ALE, xung L-to-H de chot dia chi
	ADC0808_START = 1;                                //kích hoat chân Start L-to-H de bat dau chuyen doi
	ADC0808_ALE = 0;
	ADC0808_START = 0;
	while(ADC0808_EOC);                              //giam sat qua trinh chuyen doi
	while(!ADC0808_EOC);                             //giam sat EOC het muc thap chua
	ADC0808_OE = 1;                                    //OE o muc H-to-L de 8051 doc data
	kq = ADC0808_DATA;                              //sau khi chuyen doi P3 dã có các giá tri, gán P3=kq
	ADC0808_OE = 0;
	return kq;
}