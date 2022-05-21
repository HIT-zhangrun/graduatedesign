#include "fft.h"


static uint16_t ADC_N   = 460;
//static double   chirp   = 16;
static double   fs      = 2e6;
static double   N       = FFT_LENGTH;
static double   T       = 235e-6;
static double   B       = 3.13e9;
static double   f_begin = 77e9;
static double   c       = 2.99792458e8;
static double   pi      = acos(-1);

uint8_t fft_start(float32_t *fft_buf, float32_t *fft_abs_buf)
{
	//arm_cfft_f32(&arm_cfft_sR_f32_len2048, fft_buf, 0, 1);
	arm_cfft_radix4_instance_f32 scfft;
    arm_cfft_radix4_init_f32(&scfft, FFT_LENGTH, 0, 1);
    arm_cfft_radix4_f32(&scfft, fft_buf);
    arm_cmplx_mag_f32(fft_buf, fft_abs_buf, FFT_LENGTH);

    return 0;
}

uint32_t find_fft_max(float32_t *fft_abs_buf)
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

float caculate_range(float32_t *fft_abs_buf)
{
    uint32_t max_x = find_fft_max(fft_abs_buf);
    float range = (max_x * gap);

    return range;
}

float just_fft(recv_pack_signal_s recv_pack_signal)
{
    uint16_t *buf = recv_pack_signal.data;
    float32_t fft_buf[FFT_LENGTH * 2] = {0};
    float32_t fft_abs_buf[FFT_LENGTH];
    //uint16_t temp_buf;
    float range;
    float32_t aver = 0;
    for(uint32_t i = 0; i < 460; i++)
    {
        aver += (float32_t)buf[i];
    }
    aver /= 460;

    //clear_buf();
    for (int32_t i = 0; i < ADC_N; i++)
    {
        fft_buf[2 * i] = (float32_t)buf[i];
        fft_buf[2 * i] -= aver;
        fft_buf[2 * i + 1] = 0;
    }
    fft_start(fft_buf, fft_abs_buf);
    range = caculate_range(fft_abs_buf);

    return range;
}


float phase_diff(recv_pack_signal_s recv_pack_signal)
{
	uint32_t max_x;
    uint32_t max_x_1;
    uint32_t max_x_2;
    double phase;
    double phase_1;
    double phase_2;
    double phase_diff;
    uint32_t n_1;
    uint32_t n_2;
    double frequent_B;
    double phase_B;
    double R1;
    double R2;
    double wave_length_max;


    uint16_t *buf = recv_pack_signal.data;


    float range;
    float32_t aver = 0;
    for(uint32_t i = 0; i < 460; i++)
    {
        aver += (float32_t)buf[i];
    }
    aver /= 460;

    int16_t temp_buf;
    float32_t fft_buf[FFT_LENGTH * 2] = {0};
    float32_t fft_buf1[FFT_LENGTH * 2] = {0};
    float32_t fft_buf2[FFT_LENGTH * 2] = {0};
    float32_t fft_abs_buf[FFT_LENGTH] = {0};

    for (int32_t i = 0; i < ADC_N; i++)
    {
        fft_buf[2 * i] = (float32_t)buf[i];
        fft_buf[2 * i] -= aver;
        fft_buf[2 * i + 1] = 0;
    }
    fft_start(fft_buf, fft_abs_buf);
    max_x = find_fft_max(fft_abs_buf);

    for (int32_t i = 0; i < ADC_N / 2; i++)
    {
        fft_buf1[2 * i] = (float32_t)buf[i];
        fft_buf1[2 * i] -= aver;
        fft_buf1[2 * i + 1] = 0;
    }
    fft_start(fft_buf1, fft_abs_buf);
    max_x_1 = find_fft_max(fft_abs_buf);
    //phase_1 = atan2(fft_buf[max_x_1 * 2 + 1], fft_buf[max_x_1 * 2]);
    
    for (int32_t i = 0; i < ADC_N / 2; i++)
    {
        fft_buf2[2 * i] = (float32_t)buf[i + ADC_N / 2];
        fft_buf2[2 * i] -= aver;
        fft_buf2[2 * i + 1] = 0;
    }
    fft_start(fft_buf2, fft_abs_buf);
    max_x_2 = find_fft_max(fft_abs_buf);
    if(max_x_1 != max_x_2)
    {
    	max_x_1 = round((max_x_1 + max_x_2 + max_x) / 3);
    	max_x_2 = max_x_1;
    }
    phase   = atan2(fft_buf[max_x_1 * 2 + 1], fft_buf[max_x_1 * 2]);
    phase_1 = atan2(fft_buf1[max_x_1 * 2 + 1], fft_buf1[max_x_1 * 2]);
    phase_2 = atan2(fft_buf2[max_x_2 * 2 + 1], fft_buf2[max_x_2 * 2]);
    

    phase_diff = phase_2 - phase_1;

    n_1 = round(max_x_1 * fs * T / (2 * FFT_LENGTH));
    frequent_B = n_1 * 2 / T - phase_diff / (pi * T);
    phase_B = phase;
    R1 = frequent_B * T * c / (2 * B);
    wave_length_max = c / f_begin;
    R2 = phase_B * wave_length_max / (4 * pi);
    n_2 = round(2 * R1 / wave_length_max);
    double delta_r1 = R1 - n_2 * wave_length_max / 2;
    double phase_f_B = delta_r1/(wave_length_max/2);

    if(phase_B - phase_f_B > pi/2)
        n_2 = n_2 - 1;
    if(phase_f_B - phase_B > pi/2)
        n_2 = n_2 + 1;

    range = n_2 * (wave_length_max / 2) + R2;



    return range;
}

