#ifndef FFT_H_
#define FFT_H_
#include "main.h"
#include "usbd_cdc_if.h"
#include "arm_math.h"
#include "radar_recv.h"
#define FFT_LENGTH (4096)

#define gap    ((fs / FFT_LENGTH) * T * c / (2 * B))
//(1959.0 / 1005.0)


uint8_t fft_start(float32_t *fft_buf, float32_t *fft_abs_buf);
uint32_t find_fft_max(float32_t *fft_abs_buf);
float caculate_range(float32_t *fft_abs_buf);
float just_fft(recv_pack_signal_s recv_pack_signal);
float phase_diff(recv_pack_signal_s recv_pack_signal);



#endif
