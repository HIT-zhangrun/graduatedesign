close all;
clc;
clear;

% 参数
chirp = 16;                                       % chirp信号数量
ADC_N = 600;                                      % ADC采样次数
numRX = 1;                                        % RX信号通道数
fs = 2.667e6;                                     % 采样率
N = 4096;                                         % FFT变换点数
N1 = 2048;
T = 235e-6;                                       % chirp周期
B = 3.13e9;                                       % chirp带宽
f_begin = 78e9;                                   % 雷达起始频率
f0 = f_begin+B/2;                                 % 雷达中频
c = 2.99792458e8;                                 % 光速
A=load('RAW_4.0m.mat');                           % 导入雷达数据
w=gausswin(ADC_N);
ADCBuf=w.*A.ADCBuf;




