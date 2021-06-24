#include <mega328p.h>
#include <delay.h>
// Alphanumeric LCD functions
#include <alcd.h>
#define D4 eS_PORTB4
#define D5 eS_PORTB5
#define D6 eS_PORTB6
#define D7 eS_PORTB7
#define RS eS_PORTB0
#define EN eS_PORTB2
// Declare your global variables here
int counter = 50;
int aState;
int aState2;
int aLastState;  
/* simple demonstration of how to use a rotary encoder with an ATTiny2313
 R1 (rotary encoder switch 1) is PB2
 R2 (rotary encoder switch 2) is PB1
 B (button) is PB0 
*/
void main(void)
{
// Declare your local variables here
//Set mode PIN B menjadi OUTPUT
DDRB=0b11111111; 
//Set mode PIN B menjadi INPUT
DDRD=0b00000000;  
// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS: PORTB Bit 0
// RD: PORTB Bit 1
// EN: PORTB Bit 2
// D4: PORTB Bit 4
// D5: PORTB Bit 5
// D6: PORTB Bit 6
// D7: PORTB Bit 7
// Characters/line: 16
lcd_init(16);
aLastState = 0; //asumsi nilai output A berawal dari 0
while (1)
    {
      // Place your code here  
      //mengeset tampilan LCD
      lcd_gotoxy(0,0);
      lcd_puts("Position: ");         
      if (counter <= 9) {
        lcd_puts(" ");    
      }
      lcd_printf("%d", counter); 
	  //membaca nilai output A dan B yang baru
      if (PIND&(1<<PIND2)) {
        aState = 1;
      }
      else {
        aState = 0;
      }
      if (PIND&(1<<PIND1)) {
        aState2 = 1;
      }
      else {
        aState2 = 0;
      }
      //mengeset nilai counter kembali ke default jika button ditekan
      if (~PIND&(1<<PIND0)) {
        counter = 50;
      } 
      else {
		  //melihat apakah ada perubahan pada output A
		  if (aState != aLastState) {
			//melihat apakah ouput B sama dengan nilai output A selanjutnya
			if (aState2 != aState){
			  counter ++; //jika berbeda maka pulse A mendahului B sehingga counter bertambah
			} 
			else {
			  counter --; //jika berbeda maka pulse A mendahului B sehingga counter bertambah
			}			
		  } 
	  }
      //mengeset nilai maksimum counter 100
      if (counter >= 100) {
        counter = 0;
      }
      //mengeset nilai minimum counter 0
      if (counter < 0) {
        counter = 99;
      }
      //memperbaharui nilai awal ouput A
      aLastState = aState;
    }
}

