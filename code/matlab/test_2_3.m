clc;
clear;
close all;

param = struct( ...
    'chirp', 16, ...
    'ADC_N', 600, ...
    'numRX', 1, ...
    'fs', 2.667e6, ...
    'N', 4096, ...
    'N1', 2048, ...
    'T', 235e-6, ...
    'B', 3.13e9, ...
    'f_begin', 78e9, ...
    'c', 2.99792458e8 ...
    );

[ret, data] = data_init(3.6, param);
if(ret)
    fprintf("data init error\n");
else
    fprintf("data init ok\n");
end

normal_fft(data, param);
phase_diff(data, param);

function [ret, data] = data_init(range, param)
    switch(range)
    case 2.9
    A = load('../../data/RAW_2.9m.mat');
    case 3.6
    A = load('../../data/RAW_3.6m.mat');
    case 4.0
    A = load('../../data/RAW_4.0m.mat');
    case 5.99
    A = load('../../data/RAW2_5.990m.mat');
    case 7.25
    A = load('../../data/RAW2_7.250m.mat');
    case 2.983
    A = load('../../data/RAW2_M_2.983m.mat');
    case 5.05
    A = load('../../data/RAW2_M_5.050m.mat');
    case 1.132
    A = load('../../data/RAW2_M2_1.132m.mat');
    case 2.25
    A = load('../../data/RAW2_M2_2.250m.mat');
    default
    fprintf("无此名称的数据\n");
    ret = 1;
    return;
    end

    data = A.ADCBuf;

    fid = fopen('../../data/data.bin', 'w');
    fwrite(fid, data, 'int8');
    fclose(fid);

    data_sum = sum(data, 2);
    data_mean = mean(data_sum);
    for i = 1 : param.ADC_N
        data_sum(i) = data_sum(i) - data_mean;
    end
    data = hann(param.ADC_N) .* data_sum;
    ret = 0;
end

function ret = normal_fft(data, param)
    n = (1 : param.N/2);
    x_frequent = n * param.fs / param.N;
    x_range = x_frequent * param.T * param.c / (2 * param.B);
    FFT = fft(data, param.N, 1);
    FFT_ABS = abs(FFT(1 : param.N / 2));
    [x, ] = find(FFT_ABS == max(FFT_ABS), 1);
    range = x_range(x);
    %fprintf("FFT测距频率:%fHz\n", x_frequent(x));
    fprintf("FFT测距:%fm\n", range);
    figure(1);
    plot(x_range, FFT_ABS);
    title('FFT测距');
    xlabel('距离/m]');ylabel('强度/dB]');
    ret = 0;
end

function ret = phase_diff(data, param)
    data_1 = data(1 : param.ADC_N/2);
    data_2 = data(param.ADC_N/2 +1 : param.ADC_N);
    FFT_Buff_1 = fft(data_1, param.N, 1);
    FFT_Buff_2 = fft(data_2, param.N, 1);
    FFT_Buff_1_ABS = abs(FFT_Buff_1);
    FFT_Buff_2_ABS = abs(FFT_Buff_2);
    FFT_Buff_1_ANG = angle(FFT_Buff_1);
    FFT_Buff_2_ANG = angle(FFT_Buff_2);
    [x_1, ] = find(FFT_Buff_1_ABS == max(FFT_Buff_1_ABS), 1);
    [x_2, ] = find(FFT_Buff_2_ABS == max(FFT_Buff_2_ABS), 1);
    phase_1 = FFT_Buff_1_ANG(x_1);
    phase_2 = FFT_Buff_2_ANG(x_2);
    delta_phase = phase_2 - phase_1;
    n_1 = round(x_1 * param.ADC_N / (2 * param.N));
    frequent_B = n_1 * 2 * param.fs / param.ADC_N + ...
    param.fs * delta_phase / (pi * param.ADC_N);
    %fprintf("相位法测距:%fHz\n", frequent_B);
    phase_B = phase_1 + (param.ADC_N - 1) * x_1 * pi / param.N - ...
    (param.ADC_N - 1) * frequent_B * param.T * pi / param.ADC_N;
    R1 = frequent_B * param.T * param.c / (2 * param.B);
    wave_length_min = param.c / (param.f_begin + param.B);
    R2 = phase_B * wave_length_min / (4 * pi);
    n_2 = round(2 * R1 / wave_length_min);
    range = n_2 * (wave_length_min / 2) + R2;
    fprintf("相位差测距:%fm\n", range);

    ret= 0;
end
