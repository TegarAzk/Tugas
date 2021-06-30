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
  int counter = 0;  
  float Filter_data[3]; //X[n] dan Y[n-1]
  float output;
  int i;
  Filter_data[0] = 0;
  Filter_data[1] = 0;
  Filter_data[2] = 0;
  Serial.println("start");
  Serial.println("time,filter_in,filter_out");
  for (i = 0; i < 100; i++) {
    float data = 0;
    data = output_adc[i] / 1024.0;

    Serial.print(counter);
    Serial.print(",");
    Serial.print(data);
    Serial.print(",");
    Filter_data[2] = Filter_data[1];
    Filter_data[1] = data;
    output = filter_LPF(Filter_data);
    //output = filter_HPF(Filter_data);
    Filter_data[0] = output;
    Serial.print(output);
    Serial.println("");
    counter++;
  }

  while (1) {
    // halt di sini
  }
}
