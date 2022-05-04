#include "fft.h"

static float32_t fft_buf[FFT_LENGTH * 2];
static float32_t fft_abs_buf[FFT_LENGTH];
static double test_value1;
static double test_value2;
static double test_value3;
static double test_value4;
static double test_value5;

static uint16_t ADC_N   = 600;
//static double   chirp   = 16;
static double   fs      = 2.667e6;
static double   N       = FFT_LENGTH;
static double   T       = 235e-6;
static double   B       = 3.13e9;
static double   f_begin = 78e9;
static double   c       = 2.99792458e8;
static double   pi      = acos(-1);

void fft_start()
{
    arm_cfft_radix4_instance_f32 scfft;
    arm_cfft_radix4_init_f32(&scfft, FFT_LENGTH, 0, 1);
    arm_cfft_radix4_f32(&scfft, fft_buf);
    arm_cmplx_mag_f32(fft_buf, fft_abs_buf, FFT_LENGTH);
}

uint32_t find_fft_max()
{
    float32_t max = 0;
    uint32_t max_x = -1;
    for (int32_t i = 0; i < FFT_LENGTH / 2; i++)
    {
        if (max < fft_abs_buf[i])
        {
            max = fft_abs_buf[i];
            max_x = i;
        }
    }
    return max_x;
}

double caculate_range()
{
    uint32_t max_x = find_fft_max();
    double range = (max_x * gap);

    return range;
}

double just_fft()
{
    int16_t temp_buf;
    double range;
    clear_buf();
    for (int32_t i = 0; i < FFT_LENGTH; i++)
    {
        if (i < ADC_N)
        {
            temp_buf = UserRxBufferFS[2 * i] | (UserRxBufferFS[2 * i + 1] << 8);
            fft_buf[2 * i] = (float32_t)(temp_buf);
            fft_buf[2 * i + 1] = 0;
        }
        else
        {
            fft_buf[2 * i] = 0;
            fft_buf[2 * i + 1] = 0;
        }
    }
    fft_start();
    range = caculate_range();

    return range;
}

double phase_diff()
{
    uint32_t max_x_1;
    uint32_t max_x_2;
    double phase_1;
    double phase_2;
    double phase_diff;
    uint32_t n_1;
    uint32_t n_2;
    double frequent_B;
    double phase_B;
    double R1;
    double R2;
    double wave_length_min;
    double range;
    TIM2->CNT = 0;

    int16_t temp_buf;
    clear_buf();
    for (int32_t i = 0; i < FFT_LENGTH; i++)
    {
        if (i < ADC_N / 2)
        {
            temp_buf = UserRxBufferFS[2 * i] | (UserRxBufferFS[2 * i + 1] << 8);
            fft_buf[2 * i] = (float32_t)(temp_buf);
            fft_buf[2 * i + 1] = 0;
        }
        else
        {
            fft_buf[2 * i] = 0;
            fft_buf[2 * i + 1] = 0;
        }
    }

    fft_start();
    max_x_1 = find_fft_max();
    phase_1 = atan2(fft_buf[max_x_1 * 2 + 1], fft_buf[max_x_1 * 2]);
    
    clear_buf();
    for (int32_t i = 0; i < FFT_LENGTH; i++)
    {
        if (i < ADC_N / 2)
        {
            temp_buf = UserRxBufferFS[2 * i + ADC_N] | (UserRxBufferFS[2 * i + 1 + ADC_N] << 8);
            fft_buf[2 * i] = (float32_t)(temp_buf);
            fft_buf[2 * i + 1] = 0;
        }
        else
        {
            fft_buf[2 * i] = 0;
            fft_buf[2 * i + 1] = 0;
        }
    }

    fft_start();
    max_x_2 = find_fft_max();
    phase_2 = atan2(fft_buf[max_x_2 * 2 + 1], fft_buf[max_x_2 * 2]);
    

    phase_diff = phase_2 - phase_1;
    n_1 = (uint32_t)round((max_x_1 * ADC_N) / (2 * N));
    frequent_B = (n_1 * 2 * fs) / ADC_N + (fs * phase_diff) / (pi * ADC_N);
    phase_B = phase_1 + ((ADC_N - 1) * (max_x_1 + 1) * pi) / N - ((ADC_N - 1) * frequent_B * T * pi) / ADC_N;
    R1 = (frequent_B * T * c) / (2 * B);
    wave_length_min = c / (f_begin + B);
    R2 = (phase_B * wave_length_min) / (4 * pi);
    n_2 = (uint32_t)round((2 * R1) / wave_length_min);
    range = n_2 * (wave_length_min / 2) + R2;

    test_value1 = phase_1;
    test_value2 = phase_2;
    test_value4 = max_x_1;
    test_value5 = TIM2->CNT;
    test_value3 = range;

    return range;
}

void clear_buf()
{
    for (int32_t i = 0; i < FFT_LENGTH; i++)
    {
        fft_buf[2 * i]     = 0;
        fft_buf[2 * i + 1] = 0;
    }
}

