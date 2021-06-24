#include <LiquidCrystal.h> 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //mengeset LCD
#define outputA 7 
#define outputB 8
#define button 6
int counter = 50; //mengeset angka default untuk counter 50
int aLastState; //nilai awal ouput A
int aState; //nilai kedua output A untuk mengecek perubahan

void setup() { 
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  pinMode (button, INPUT);
   
  lcd.begin(16, 2);
  //membaca nilai awal output A
  aLastState = digitalRead(outputA);   
} 
void loop() { 
  //mengeset tampilan LCD
  lcd.setCursor(0,0);
  lcd.print("Position: ");
  //agar angka puluhan terhapus ketika berubah mgenjadi angka satuan diperlukan spasi, 
 //hal ini bisa juga dilakukan dengan clear
  if (counter <= 9) {  
    lcd.print(" "); 
  }
  lcd.print(counter);
  //membaca nilai output A selanjutnya
  aState = digitalRead(outputA); 
  //mengeset nilai counter kembali ke default jika button ditekan
  if (digitalRead(button) == LOW) {
    counter = 50;
  } 
  else { 
	  //melihat apakah ada perubahan pada ouput A
	  if (aState != aLastState){     
		//melihat apakah output B berbeda dengan nilai ouput A selanjutnya
	if (digitalRead(outputB) != aState) { 
		  counter ++; //jika berbeda maka pulse A mendahului B sehingga counter bertambah 

		} 
		else {
		  counter --; //jika sama maka pulse B mendahului A sehingga counter berkurang
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
