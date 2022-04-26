clc;
clear;
close all;
%% 参数设置      
ADC_N   = 600;                 %采样点数
fs      = 15e6;                %采样频率
N       = 4096;                %FFT点数
B       = 3.9927e9;            %带宽
f_begin = 77e9;                %起始频率
c       = 2.99792458e8;        %光速
f_slope = 39.927;              %上升斜率MHz/us
T       = B / (f_slope * 1e12);%上升时间
RX      = 4;                   %接收天线数
chirp   = 16;                  %计算的连续chirp数
num = 0;
%% 文件路径名称
fname='../../data/zr_4_18_1443_data/2_961.bin';
%% 选择文件读取数据包
fid = fopen(fname,'rb');%打开文件
data_origin = readDCA1000(fname);
%% 计算连续chirp数下单通道数据
data = data_origin(1:ADC_N);
data_process = hanning(ADC_N)' .* data;
%% 距离FFT
temp_fft=fft(data_process, N);%对每个chirp做N点FFT
%% 一维FFT后,距离与接收功率图
F=(0:N/2-1)*fs/N;%频率公式
X=(0:N/2-1)*fs*c*T/2/B/N;%距离公式
Y=abs(temp_fft(1:N/2));%接收功率公式
test = angle(temp_fft(1:N/2));
num = num + 1;
figure(num);
plot(X,Y);
[x, ] = find(Y == max(Y), 1);
    range = X(x);
fprintf("FFT测频%f\n", F(x));
fprintf("FFT测距:%fm\n", range);

%% CZT
Y1 = Y;
F1 = F;
deta_f = fs;
D1 = N;
D2 = 15;
XX = 3;%前后拓展的频点

while 1
    [i ,n] = max(Y1);
    fmax1 = F1(n);
    M = deta_f/D1;
    f1 = fmax1-M*XX;
    f2 = fmax1+M*XX;
    deta_f = f2 - f1;
    if(f1 == f2 && f1 == fmax1)
        break;
    end
    w = exp(-j*2*pi*(f2-f1)/(deta_f*D2));
    a = exp(j*2*pi*f1/deta_f);
    Y1 = czt(data_process, D2, w, a);
    fn = (0:D2-1)/D2;
    F1 = (f2-f1)*fn + f1;
    D1 = D2;
    num = num + 1;
    range_x = F1*c*T/2/B;%距离公式
%     if(num<10)
%     figure(num);
%     plot(range_x,abs(Y1));
%     end
    
    %hold on;
end
range =  fmax1*c*T/2/B;
fprintf("细化倍数%f\n", num);
fprintf("距离%f\n", range);

%% 相位差

N = 4096;
data_1 = data(1 : ADC_N/2);
data_2 = data(ADC_N/2 +1 : ADC_N);
FFT_Buff_1 = fft(data_1, N);
FFT_Buff_2 = fft(data_2, N);
FFT_Buff_1_ABS = abs(FFT_Buff_1);
FFT_Buff_2_ABS = abs(FFT_Buff_2);
FFT_Buff_1_ANG = angle(FFT_Buff_1);
FFT_Buff_2_ANG = angle(FFT_Buff_2);
[x_1, ] = find(FFT_Buff_1_ABS == max(FFT_Buff_1_ABS), 1);
[x_2, ] = find(FFT_Buff_2_ABS == max(FFT_Buff_2_ABS), 1);
phase_1 = FFT_Buff_1_ANG(x_1);
phase_2 = FFT_Buff_2_ANG(x_2);
delta_phase = phase_2 - phase_1;
n_1 = round(x_1 * ADC_N / (2 * N));
frequent_B = n_1 * 2 * fs / ADC_N + ...
fs * delta_phase / (pi * ADC_N);
%fprintf("相位法测频:%fHz\n", frequent_B);
phase_B = phase_1 + (ADC_N - 1) * x_1 * pi / N - ...
(ADC_N - 1) * frequent_B * T * pi / ADC_N;
R1 = frequent_B * T * c / (2 * B);
wave_length_min = c / (f_begin + B);
R2 = phase_B * wave_length_min / (4 * pi);
n_2 = round(2 * R1 / wave_length_min);
range = n_2 * (wave_length_min / 2) + R2;
fprintf("相位差测距:%fm\n", range);
fprintf("相位差测距:%fm\n", delta_phase*T*c*fs/2/pi/B/ADC_N);




%% 处理DAC原始bin文件，输出4路复数采样点
function [retVal] = readDCA1000(fileName)
%% global variables
% change based on sensor config
numADCBits = 16; % number of ADC bits per sample
numLanes = 4; % do not change. number of lanes is always 4 even if only 1 lane is used. unused lanes
isReal = 0; % set to 1 if real only data, 0 if complex dataare populated with 0 %% read file and convert to signed number
% read .bin file
fid = fopen(fileName,'r');
% DCA1000 should read in two's complement data
adcData = fread(fid, 'int16');
% if 12 or 14 bits ADC per sample compensate for sign extension
if numADCBits ~= 16
l_max = 2^(numADCBits-1)-1;
adcData(adcData > l_max) = adcData(adcData > l_max) - 2^numADCBits;
end
fclose(fid);
%% organize data by LVDS lane
% for real only data
if isReal
% reshape data based on one samples per LVDS lane
adcData = reshape(adcData, numLanes, []);
%for complex data
else
% reshape and combine real and imaginary parts of complex number
adcData = reshape(adcData, numLanes*2, []);
adcData = adcData([1,2,3,4],:) + sqrt(-1)*adcData([5,6,7,8],:);
end
%% return receiver data
%retVal = adcData;
%% 单通道数据
retVal = adcData(2, :);
end