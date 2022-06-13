clc;
clear;
close all;

% 鍙傛暟
% 鍝堝搱
% 额
chirp = 16;                                       % chirp娣団�冲娇閺佷即锟�?
ADC_N = 600;                                      % ADC闁插洦鐗卞▎鈩冩殶
numRX = 1;                                        % RX娣団�冲娇锟�?姘朵壕閺侊拷
fs = 2.667e6;                                     % 闁插洦鐗遍悳锟�?
N = 4096;                                         % FFT閸欐ɑ宕查悙瑙勬殶
N1 = 2048;
T = 235e-6;                                       % chirp閸涖劍锟�?
B = 3.13e9;                                       % chirp锟�?锕�锟�?
f_begin = 78e9;                                   % 闂嗙柉锟�?鐠у嘲顫愭０鎴犲芳
f0 = f_begin+B/2;                                 % 闂嗙柉锟�?娑擃參锟�?
c = 2.99792458e8;                                 % 閸忥拷?锟解偓锟�?
A=load('RAW_4.0m.mat');                           % 鐎电厧鍙嗛梿锟�?锟�?閺佺増锟�?
ADCBuf=A.ADCBuf;

ADCBufSum = sum(ADCBuf,2);                          % 鏉╂柨娲栧В蹇庯拷?锟界悰灞锯偓璇叉嫲閻ㄥ嫬锟�?閸氭垿锟�?
ADCBufMean = mean(ADCBufSum);                       % 濮ｅ繋绔寸悰宀�娈戦崸鍥р偓锟�?
for i = 1:ADC_N
    ADCBufSum(i) = ADCBufSum(i)-ADCBufMean;         % 濠娿倖灏濇径锟�?锟�?
end

S=ADCBufSum;
S1=ADCBufSum(1:ADC_N/2);
S2=ADCBufSum(ADC_N/2+1:ADC_N);
FFT_S  = fft(S,N,1);
FFT_S1 = fft(S1,N,1);
FFT_S2 = fft(S2,N,1);
FFT_S_ABS=abs(FFT_S);
FFT_S1_ABS=abs(FFT_S1);
FFT_S2_ABS=abs(FFT_S2);
FFT_S_ANG = angle(FFT_S);
FFT_S1_ANG = angle(FFT_S1);
FFT_S2_ANG = angle(FFT_S2);
[k, ] = find(FFT_S_ABS==max(FFT_S_ABS),1);
[k1, ] = find(FFT_S1_ABS==max(FFT_S1_ABS),1);
[k2, ] = find(FFT_S2_ABS==max(FFT_S2_ABS),1);
phai_k=FFT_S_ANG(k);
phai_k1=FFT_S1_ANG(k1);
phai_k2=FFT_S2_ANG(k2);
n1=round(k1*ADC_N/(2*N));
f=n1*2/T+(phai_k2-phai_k1)/(pi*T);
R1=f*T*c/(2*B);   %閸楁洑缍卪
% R1锟斤拷锟斤拷

phai=phai_k+(ADC_N-1)*k*pi/N-(ADC_N-1)*f*T*pi/ADC_N;
R2=phai*(c/f_begin)/(4*pi);
n2=round(2*R1/(c/f_begin));
R=n2*(c/f_begin/2)+R2;


