clc;
clear;
close all;
% 鍙傛暟
chirp = 16;                                       % chirp淇″彿鏁伴噺
ADC_N = 600;                                      % ADC閲囨牱娆℃暟
numRX = 1;                                        % RX淇″彿閫氶亾鏁�
fs = 2.667e6;                                     % 閲囨牱鐜�
N = 4096;                                          % FFT鍙樻崲鐐规暟
N1 = 2048;
T = 235e-6;                                       % chirp鍛ㄦ湡
B = 3.13e9;                                       % chirp甯﹀��
f_begin = 78e9;                                   % 闆疯揪璧峰�嬮�戠巼
f0 = f_begin+B/2;                                 % 闆疯揪涓�棰�
c = 2.99792458e8;                                 % 鍏夐€�
A=load('../data/RAW_4.0m.mat');                           % 瀵煎叆闆疯揪鏁版嵁
%A=load('RAW2_7.250m.mat'); 
%A=load('RAW2_M2_1.132m.mat');
ADCBuf=A.ADCBuf;

% FFT娴嬮�戞硶
ADCBufSum = sum(ADCBuf,2);                          % 杩斿洖姣忎竴琛屾€诲拰鐨勫垪鍚戦噺
ADCBufMean = mean(ADCBufSum);                       % 姣忎竴琛岀殑鍧囧€�
for i = 1:ADC_N
    ADCBufSum(i) = ADCBufSum(i)-ADCBufMean;         % 婊ゆ尝澶勭悊
end

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



% 鐩镐綅宸�娉曟祴棰�
% FFT_Buf_phy = angle(FFT_Buf);
% phy = FFT_Buf_phy(row1);
delta_R = c/(2*B);
Buff1 = zeros(ADC_N/2,1);
Buff2 = zeros(ADC_N/2,1);
Buff1(1:ADC_N/2) = ADCBufSum(1:ADC_N/2);
Buff2(1+ADC_N/2:ADC_N) = ADCBufSum(1:ADC_N/2);
FFT_Buff1 = fft(Buff1,N1,1); 
FFT_Buff2 = fft(Buff2,N1,1); 
FFT_Buff1_ABS = abs(FFT_Buff1);
FFT_Buff2_ABS = abs(FFT_Buff2);
FFT_Buff1_ANG = angle(FFT_Buff1);
FFT_Buff2_ANG = angle(FFT_Buff2);
[row2_1,col2_1] = find(FFT_Buff1_ABS==max(FFT_Buff1_ABS),1);
[row2_2,col2_2] = find(FFT_Buff1_ABS==max(FFT_Buff1_ABS),1);
delta_phy = FFT_Buff2_ANG(row2_2)-FFT_Buff1_ANG(row2_1);
R22 = delta_phy*delta_R*100/pi;%鍗曚綅cm
R2 = R1+R22;


% chirp_Z鍙樻崲
czt_data =  ADCBufSum;                          % 鍔犵獥鍚庢暟鎹�
f_start =(row1-3)*fs/N;                        % 缁嗗寲棰戞�佃捣濮嬮�戠巼
f_end =(row1+3)*fs/N;                          % 缁嗗寲棰戞�垫埅姝㈤�戠巼
multiple =64;                                   % CZT娉曠粏鍖栧€嶆暟
DELf=fs/N/multiple;
M2=(f_end-f_start)/DELf;
A=exp(1i*2*pi*f_start/fs);
W=exp(-1i*2*pi*DELf/fs);
R_czt=czt(czt_data,M2,W,A);
R_czt_result = R_czt;
fn2=(1:M2)'/M2;
fx2=(f_end-f_start)*fn2+f_start;
fx2=fx2*T*c*100/(2*B);                          %鍗曚綅mm
czt_re = abs(R_czt_result);
[row2,col2]=find(czt_re==max(czt_re),1);
R3 = fx2(row2);
figure(2)
plot(fx2,czt_re);
title(['chirp-Z鍙樻崲娉曠粨鏋滐紝缁嗗寲鍊嶆暟锛�' ,num2str(multiple)]);
xlabel('璺濈�诲崟鍏僛cm]');ylabel('骞呭害[dB]');

fprintf('FFT娴嬪緱璺濈��:%fcm\n',R1);
fprintf('CZT鍙樻崲娴嬪緱璺濈��:%fcm\n',R3);
fprintf('FFT缁撳悎鐩镐綅宸�娉曟祴寰楄窛绂�:%fcm\n',R2);
fprintf('CZT鍙樻崲鍜岀浉浣嶅樊娉曠粨鍚堟祴寰楄窛绂�:%fcm\n',R3+R22);

fprintf('绮惧害鎻愰珮:%fcm\n',abs(fx2(row2)-fx1_r(row1)));