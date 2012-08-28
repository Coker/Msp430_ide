/*
************************************************************
*                                                          *
* Uylulama 1.2  20.09.2009	www.fatihinanc.com         *
*                                                          *
* P1.7 deki butona basýnca program kesmeye gidip,          *
* P1.0 daki LEDi yakmakta, kesme fonksiyonunda ise         *
* P1.0 ve P1.7 sürekli terslenmektedir. Kesme sonunda ise  *
* kesme bayraðý sýfýrlanýp yeniden kesme oluþmasýna izin   *
* verilmektedir. Ayrýca bu örnekte bitsel olarak nasýl     *
* iþlem yapýlacaðý da gösterilmiþtir.                      *
*							   *
************************************************************
*/
 
#include "GPIO.h"
 
#define LED0 P1OUT_bit.P1OUT_0
#define LED6 P1OUT_bit.P1OUT_6

//P1.3 Pin Tanýmlamalarý
#define P1REN3 P1REN_bit.P1REN_3
#define P1OUT3 P1OUT_bit.P1OUT_3
#define P1IE3 P1IE_bit.P1IE_3
#define P1IES3 P1IES_bit.P1IES_3
#define P1IFG3 P1IFG_bit.P1IFG_3

void main( void )
{
	WDTCTL = WDTPW + WDTHOLD; //Watchdog timer durduruluyor...
	
	// P1DIR = BIT0 | BIT6;   //P1.6 ve P1.0 ÇIKIÞ, diðerleri giriþ...
	
	set_dir(1, 0, 1);
	set_dir(1, 6, 1);
	set_pullup_resistors(1, 3);
	interrupt_command(1, 3, 0);
	
	BCSCTL1= CALBC1_1MHZ; //DCOCLK 1MHZ Seçiliyor...
	DCOCTL = CALDCO_1MHZ;
	
	_BIS_SR(GIE); // General interrupt activated
	
	while(1); 
}

#pragma vector=PORT1_VECTOR
//P1 Interrupt Vektörü Tanýmlanýyor... 
__interrupt void P1_Int_handler(void)
{
   if(P1IFG & BIT3)
   {
	   LED0=~LED0;
	   LED6=~LED6;
	   P1IFG3=0; // P1.6 kesme bayraðý temizleniyor
   }
}