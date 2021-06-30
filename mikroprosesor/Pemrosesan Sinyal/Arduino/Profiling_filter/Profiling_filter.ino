#include "D:\3_Tugas\S6_Sismik\Tugas_5_6\Data/data.h"

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

float filter_LPF(float input[3]) {
  float B = 0.0432214; //0.389661[3kHz]; 0.207879[5kHz]; 0.0432214[10kHz];
  return ((1-B)*input[0] + B*input[1]);
}
float filter_HPF(float input[3]) {
  float B = 0.0432214; //0.389661[3kHz]; 0.207879[5kHz]; 0.0432214[10kHz];
  return B*(input[0] + input[1] - input[2]);

void loop() {
  float Filter_data[3]; // jumlah delay line sesuai orde filter
  float data = 0;
  float output;
  // pengukuran waktu
  unsigned long waktu_awal = millis();
  unsigned long y = 0;
  data = 1.0;
  Filter_data[0] = 0;
  Filter_data[1] = 0;
  Filter_data[2] = 0;
  Serial.println("start");
  for (y = 0; y < 1000000L; y++) {
    data = data + 1.0; // data mesti diubah terus, supaya tidak dioptimize oleh compiler
    data = (data+ output)/2; // supaya output tidak dioptimize
    Filter_data[2] = Filter_data[1];
    Filter_data[1] = data;
    output = filter_LPF(Filter_data);
    //output = filter_HPF(Filter_data);
    Filter_data[0] = output;
  }
  unsigned long waktu_akhir = millis();
  Serial.println(output); // output mesti dipakai, supaya tidak dioptimize oleh compiler
  Serial.print("waktu awal:");
  Serial.println(waktu_awal);
  Serial.print("waktu akhir:");
  Serial.println(waktu_akhir);
  Serial.print("beda waktu:");
  Serial.println(waktu_akhir - waktu_akhir);


  while (1) {
    // halt di sini
  }
}
