clc;
clear;
close all;
%% 参数全局化
global ADC_N fs N M B f_begin c f_slope T RX chirp num;
%% 参数设置
ADC_N   = 600;                 %采样点数
fs      = 15e6;                %采样频率
N       = 4096*2;                %FFT点数
M       = 4096*2;                %相位差第二FFT点数
B       = 3.9927e9;            %带宽
f_begin = 77e9;                %起始频率
c       = 2.99792458e8;        %光速
f_slope = 39.927;              %上升斜率MHz/us
T       = B / (f_slope * 1e12);%上升时间
RX      = 4;                   %接收天线数
chirp   = 16;                  %计算的连续chirp数
num     = 0;
%% 文件路径名称
fname='../../data/zr_4_24_1443_data/3/1_636.bin';
%% 选择文件读取数据包
data_origin = readDCA1000(fname);

phase_range = zeros(1, 512);
f1 = zeros(1, 512);
fft_range = zeros(1, 512);
for n = 0 : 511
[phase_range(n + 1), f1(n+1)] = phase_diff(data_origin(n * ADC_N + 1 : ADC_N + ADC_N * n));
end
figure(1);
for n = 0 : 511
if(abs(phase_range(n+1) - mean(phase_range))>0.001)
    phase_range(n+1) = mean(phase_range);
end
end
plot(phase_range);
hold on;
figure(2);
plot(f1);
hold on;

for n = 0 : 511
[fft_range(n + 1), f2(n+1)] = fft_process(data_origin(n * ADC_N + 1 : ADC_N + ADC_N * n));
end
figure(1);
plot(fft_range);
legend('相位差','FFT');
figure(2);
plot(f2);
legend('相位差','FFT');
% [phase_range, f1] = phase_diff(data_origin(1 : ADC_N));
% [fft_range, f2] = fft_process(data_origin(1 : ADC_N));

fprintf("FFT测距标准差:%f\n", std(fft_range));
fprintf("相位差测距标准差:%f\n", std(phase_range));
fprintf("FFT测距均值:%f\n", mean(fft_range));
fprintf("相位差测距均值:%f\n", mean(phase_range));
fprintf("提升精确度:%fmm\n", 1000*(mean(fft_range)-mean(phase_range)));



%% 相位差算法
function [range, f] = phase_diff(data_origin)
    %% 参数全局化
    global ADC_N fs M B f_begin c f_slope T RX chirp num;
    
    %% 处理数据
    data = data_origin(1 : ADC_N);
    data_process  = hanning(ADC_N)' .* data(1 : ADC_N);
    data_process1 = hanning(ADC_N / 2)' .* data(1 : ADC_N / 2);
    data_process2 = hanning(ADC_N / 2)' .* data(ADC_N / 2 + 1 : ADC_N);

    %% 相位差结合相位法
    FFT_Buff   = fft(data_process, M);
    FFT_Buff_1 = fft(data_process1, M);
    FFT_Buff_2 = fft(data_process2, M);
    FFT_Buff_ABS   = abs(FFT_Buff);
    FFT_Buff_1_ABS = abs(FFT_Buff_1);
    FFT_Buff_2_ABS = abs(FFT_Buff_2);
    FFT_Buff_ANG   = angle(FFT_Buff);
    FFT_Buff_1_ANG = angle(FFT_Buff_1);
    FFT_Buff_2_ANG = angle(FFT_Buff_2);
    [x,   ] = find(FFT_Buff_ABS   == max(FFT_Buff_ABS), 1);
    [x_1, ] = find(FFT_Buff_1_ABS == max(FFT_Buff_1_ABS), 1);
    [x_2, ] = find(FFT_Buff_2_ABS == max(FFT_Buff_2_ABS), 1);

    if(x_1 ~= x_2)
        %fprintf("x_1 %f != x_2 %f!\n", x_1, x_2);
        x_1 = round((x + x_1 + x_2) / 3);
        x_2 = x_1;
    end
    phase   = FFT_Buff_ANG(x);
    phase_1 = FFT_Buff_1_ANG(x_1);
    phase_2 = FFT_Buff_2_ANG(x_2);
    delta_phase = phase_2 - phase_1;
    n_1 = round((x_1-1) * fs * T / (2 * M));
    frequent_B = n_1 * 2 / T + delta_phase / (pi * T);
    %fprintf("相位差测频%f\n", frequent_B);
    phase_B = phase; %+(ADC_N - 1) * (x_1-1) * pi / M - (ADC_N - 1) * frequent_B * T * pi / ADC_N;
    R1 = frequent_B * T * c / (2 * B);
    wave_length_max = c / f_begin;
    R2 = phase_B * wave_length_max / (4 * pi);
    n_2 = round(2 * R1 / wave_length_max);
    
    
    delta_r1 = R1 - n_2 * wave_length_max / 2;
    phase_f_B = delta_r1/(wave_length_max/2);
    ret = phase_B - phase_f_B;
    if(phase_B - phase_f_B > pi/2)
        n_2 = n_2 - 1;
    end
    if(phase_f_B - phase_B > pi/2)
        n_2 = n_2 + 1;
    end
    
    range = n_2 * (wave_length_max / 2) + R2;
    %fprintf("相位差测距:%fm\n", range);
    
    f = frequent_B;
end
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
%% 普通FFT
function [range, f] = fft_process(data_origin)
    %% 参数全局化
    global ADC_N fs N M B f_begin c f_slope T RX chirp num;
    
    %% 处理数据
    n = (0 : N/2-1);
    x_frequent = n * fs / N;
    x_range = x_frequent * T * c / (2 * B);
    FFT = fft(data_origin, N);
    FFT_ABS = abs(FFT(1 : N / 2));
    [x, ] = find(FFT_ABS == max(FFT_ABS), 1);
    range = x_range(x)+0.026;
    %fprintf("FFT测距频率:%fHz\n", x_frequent(x));
    %fprintf("FFT测距:%fm\n", range);
%     figure(3);
%     plot(x_range, FFT_ABS);
%     title('FFT测距');
%     xlabel('距离/m]');ylabel('强度/dB]');
    f = x_frequent(x);
end
%% 原始未封装函数
% %% 计算连续chirp数下单通道数据
% data = data_origin(1:ADC_N);
% data_process1 = hanning(ADC_N/2)' .* data(1 : ADC_N/2);
% data_process2 = hanning(ADC_N/2)' .* data(ADC_N/2 +1 : ADC_N);
% %% 相位差结合相位法
% FFT_Buff_1 = fft(data_process1, N);
% FFT_Buff_2 = fft(data_process2, N);
% FFT_Buff_1_ABS = abs(FFT_Buff_1);
% FFT_Buff_2_ABS = abs(FFT_Buff_2);
% FFT_Buff_1_ANG = angle(FFT_Buff_1);
% FFT_Buff_2_ANG = angle(FFT_Buff_2);
% [x_1, ] = find(FFT_Buff_1_ABS == max(FFT_Buff_1_ABS), 1);
% [x_2, ] = find(FFT_Buff_2_ABS == max(FFT_Buff_2_ABS), 1);
% if(x_1 ~= x_2)
%     fprintf("x_1%f != x_2%f!!!\n",x_1,x_2);
%     x_1 =x_2;
% end
% 
% phase_1 = FFT_Buff_1_ANG(x_1);
% phase_2 = FFT_Buff_2_ANG(x_2);
% delta_phase = phase_2 - phase_1;
% n_1 = round(x_1 * ADC_N / (2 * N));
% frequent_B = n_1 * 2 * fs / ADC_N + ...
% fs * delta_phase / (pi * ADC_N);
% %fprintf("相位法测频:%fHz\n", frequent_B);
% phase_B = phase_1 + (ADC_N - 1) * x_1 * pi / M - ...
% (ADC_N - 1) * frequent_B * T * pi / ADC_N;
% R1 = frequent_B * T * c / (2 * B);
% wave_length_min = c / (f_begin + B);
% R2 = phase_B * wave_length_min / (4 * pi);
% n_2 = round(2 * R1 / wave_length_min);
% delta_r1 = R1 - n_2 * wave_length_min / 2;
% phase_f_B = delta_r1/(wave_length_min/2);
% ret = phase_B - phase_f_B;
% 
% if(ret>pi/2)
%     n_2 = n_2 - 1;
% end
% if(ret<-pi/2)
%     n_2 = n_2+1;
% end
% 
% range = n_2 * (wave_length_min / 2) + R2;
% fprintf("相位差测距:%fm\n", range);
