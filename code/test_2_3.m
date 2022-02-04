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

[ret, data] = data_init(4.0, param);
if(ret)
    fprintf("data init error\n");
else
    fprintf("data init ok\n");
end

normal_fft(data, param);



function [ret, data] = data_init(range, param)
    switch(range)
    case 2.9
    A = load('../data/RAW_2.9m.mat');
    
    case 3.6
    A = load('../data/RAW_3.6m.mat');

    case 4.0
    A = load('../data/RAW_4.0m.mat');

    case 5.99
    A = load('../data/RAW2_5.990m.mat');

    case 7.25
    A = load('../data/RAW2_7.250m.mat');

    case 2.983
    A = load('../data/RAW2_M_2.983m.mat');

    case 5.05
    A = load('../data/RAW2_M_5.050m.mat');

    case 1.132
    A = load('../data/RAW2_M2_1.132m.mat');

    case 2.25
    A = load('../data/RAW2_M2_2.250m.mat');

    default
    fprintf("无此名称的数据\n");
    ret = 1;
    return;
    end

    data = A.ADCBuf;
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
    x_range = x_frequent * param.T * param.c * 100 / (2 * param.B);
    FFT = fft(data, param.N, 1);
    FFT_ABS = abs(FFT(1 : param.N / 2));
    [x, y] = find(FFT_ABS == max(FFT_ABS), 1);
    range = x_range(x);
    fprintf("FFT测距：%fcm\n",range);
    figure(1);
    plot(x_range, FFT_ABS);
    title('FFT测距');
    xlabel('距离/cm]');ylabel('强度/dB]');
end