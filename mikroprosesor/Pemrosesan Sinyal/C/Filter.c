/* 
 * File:   main.c
 * Author: waskita
 *
 * Created on April 18, 2020, 4:39 PM
 * 
 * Renamed FIle : Filter.c
 * edit by : muhammad tegar azkiya
 */

#include <stdio.h>
#include <stdlib.h>

#include "string.h"
#include "math.h"

float filter_LPF(float input[3]) {
  float B = 0.0432214; //0.389661[3kHz]; 0.207879[5kHz]; 0.0432214[10kHz];
  return ((1-B)*input[0] + B*input[1]);
}
float filter_HPF(float input[3]) {
  float B = 0.0432214; //0.389661[3kHz]; 0.207879[5kHz]; 0.0432214[10kHz];
  return B*(input[0] + input[1] - input[2]);
}

#define BUFFER_LENGTH 100

int main(int argc, char** argv) {
    float waktu = 0;
    float sampling_rate = 10000; // frekuensi sampling
    float waktu_step;

    char output_filename[] = "../Data/simulasi-filter.csv";
    char dac_filename[] = "../Data/dac-output.txt"; // simulasi output DAC
    float Filter_data[3];

    waktu_step = 1 / sampling_rate; // penambahan waktu tiap time step, sesuai frekuensi sampling
    // inisialisasi delay line
    Filter_data[0] = 0;
    Filter_data[1] = 0;
    Filter_data[2] = 0;

    char data[BUFFER_LENGTH];
    char filename[] = "../Data/anti-aliasing-out.csv";
    FILE *fp;
    FILE *output_fp;
    FILE *dac_fp;
    output_fp = fopen(output_filename, "w"); // file output
    dac_fp = fopen(dac_filename, "w"); // file output

    fprintf(output_fp, "n,vin,lpf_out,filter_out,dac_out\n");
    fp = fopen(filename, "r");
    if (fp != NULL && output_fp != NULL) { // kedua file harus dapat dibuka

        printf("read file %s ok\n", filename);
        fgets(data, BUFFER_LENGTH, fp); // buang baris pertama, karena isinya nama kolom
        while (fgets(data, BUFFER_LENGTH, fp) != NULL) {

            float output; // output filter sesaat
            int kolom = 0; // menandai angka itu di kolom berapa
            printf("%s\n", data);
            int angka_waktu; // waktu integer
            float angka_input, angka_output_lpf; // sinyal floating point

            int init_size = strlen(data);
            char delim[] = ",";

            char *ptr = strtok(data, delim);

            while (ptr != NULL) {
                int angka = 0;
                printf("%s\n", ptr);
                angka = atoi(ptr);
                printf("angka %d\n", angka);
                ptr = strtok(NULL, delim);
                if (kolom == 0) {
                    angka_waktu = angka;
                }
                if (kolom == 1) {
                    angka_input = angka / 32768.0;
                }
                if (kolom == 2) {
                    angka_output_lpf = angka / 32768.0;
                }
                kolom++;
            }
            float angka_output_adc = 0;
            float level_adc = 1024; // jumlah level ADC . 10 bit-> 1024, 8 bit->  256 
            // kuantisasi output ADC menjadi 12 bit (1024 level)
            // asumsi angka_output_lpf sudah dipetakan 0 sampai 1 volt (sesuai limit di LTSpice)
            // simulasi output ADC, dalam praktek bedanya kecil sekali (1/1024)
            angka_output_adc = (floor(angka_output_lpf * level_adc)) / level_adc;
            printf("waktu:%d vin:%f lpf_out:%f adc_out:%f\n"
                    , angka_waktu
                    , angka_input, angka_output_lpf, angka_output_adc);

            
            Filter_data[2] = Filter_data[1];
			Filter_data[1] = angka_output_lpf;
			//output = filter_LPF(Filter_data);
			output = filter_HPF(Filter_data);
			Filter_data[0] = output;
            printf("output %f\n", output);
            fprintf(output_fp, "%d,%f,%f,%f,%f\n"
                    , angka_waktu
                    , angka_input
                    , angka_output_lpf
                    , angka_output_adc
                    , output);
            // output DAC seharusnya dikuantisasi menjadi 12 level sesuai resolusi DAC, namun pada simulasi ini perbedaan kecil saja.
            // output DAC berupa anak tangga di bawah ini:
            int i;
            for (i = 0; i < 10; i++) {
                fprintf(dac_fp, "%f,%f\n", waktu + waktu_step / 10 * i, output);
            }
            waktu += waktu_step;
        }
        fclose(fp);
        fclose(output_fp);
        fclose(dac_fp);

    } else {
        printf("error read file %s\n", filename);
    }
    return (EXIT_SUCCESS);
}

// ref: https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split
