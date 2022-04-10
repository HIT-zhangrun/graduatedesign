#ifndef FFT_H_
#define FFT_H_
#include "main.h"
#include "usbd_cdc_if.h"
#include "arm_math.h"

#define FFT_LENGTH 4096

#define gap    ((fs / N) * T * c / (2 * B))

static double chirp   = 16;
static double ADC_N   = 600;
static double numRX   = 1;
static double fs      = 2.667e6;
static double N       = FFT_LENGTH;
static double N1      = 2048;
static double T       = 235e-6;
static double B       = 3.13e9;
static double f_begin = 78e9;
static double c       = 2.99792458e8;

void fft_start();
uint32_t find_fft_max();
double caculate_range();


#endif
