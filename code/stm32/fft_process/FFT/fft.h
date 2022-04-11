#ifndef FFT_H_
#define FFT_H_
#include "main.h"
#include "usbd_cdc_if.h"
#include "arm_math.h"

#define FFT_LENGTH 4096

#define gap    ((fs / N) * T * c / (2 * B))



void fft_start();
uint32_t find_fft_max();
double caculate_range();
double just_fft();
double phase_diff();
void clear_buf();


#endif
