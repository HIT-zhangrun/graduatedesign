clc;
clear;
close all;

% 鍙傛暟
chirp = 16;                                       % chirp数量
ADC_N = 600;                                      % ADC閲囨牱娆℃暟
numRX = 1;                                        % RX淇″彿閫氶亾鏁�
fs = 2.667e6;                                     % 閲囨牱鐜�
N = 4096*64;                                         % FFT鍙樻崲鐐规暟
N1 = 2048;
T = 235e-6;                                       % chirp鍛ㄦ湡
B = 3.13e9;                                       % chirp甯﹀��
f_begin = 78e9;                                   % 闆疯揪璧峰�嬮�戠巼
f0 = f_begin+B/2;                                 % 闆疯揪涓�棰�
c = 2.99792458e8;                                 % 鍏夐€�
A=load('RAW_2.9m.mat');                           % 瀵煎叆闆疯揪鏁版嵁
w=hann(ADC_N);
%w=hamming(ADC_N);
%w=chebwin(ADC_N);
%w=blackman(ADC_N);
ADCBuf=A.ADCBuf;
%ADCBuf=A.ADCBuf;

% FFT娴嬮�戞硶
ADCBufSum = sum(ADCBuf,2);                          % 杩斿洖姣忎竴琛屾€诲拰鐨勫垪鍚戦噺
ADCBufMean = mean(ADCBufSum);                       % 姣忎竴琛岀殑鍧囧€�

for i = 1:ADC_N
    ADCBufSum(i) = ADCBufSum(i)-ADCBufMean;         % 婊ゆ尝澶勭悊
end
ADCBufSum = w.*ADCBufSum;

fn1 = (1:N/2);
fx1_f = fn1*fs/N;                                       % 棰戠巼閲�
fx1_r = fx1_f*T*c*100/(2*B);                            % 鍗曚綅 cm
FFT_Buf = fft(ADCBufSum,N,1);                     % 鍋氬皬鐐规暟FFT锛屽緱鍒板ぇ鑷撮�戣氨
FFT_Buf_ABS = abs(FFT_Buf(1:N/2));                  % 鍙栨ā
[row1,col1] = find(FFT_Buf_ABS==max(FFT_Buf_ABS),1);
R1 = fx1_r(row1);
figure(1);
plot(fx1_r,FFT_Buf_ABS);
title('FFT缁撴灉');
xlabel('璺濈�诲崟鍏僛cm]');ylabel('骞呭害[dB]');