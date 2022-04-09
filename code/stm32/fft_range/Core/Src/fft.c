#include "fft.h"

#define FFT_LENGTH 1024 //FFT点数
float   fft_input_buf[FFT_LENGTH*2]; //FFT 输入数组
float   fft_output_buf[FFT_LENGTH]; //FFT 输出数组

uint8_t fft_init()
{
    arm_cfft_radix4_instance_f32 fft;
    arm_cfft_radix4_init_f32(&fft, FFT_LENGTH, 0, 1);
    arm_cfft_radix4_f32(&fft,fft_input_buf);
    arm_cmplx_mag_f32(fft_input_buf,fft_output_buf,FFT_LENGTH);
}
