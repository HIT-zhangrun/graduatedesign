clc;
clear;
close all;
%% 参数设置
ADC_N   = 600;                 %采样点数
fs      = 15e6;                %采样频率
N       = 4096*4;                %FFT点数

M       = 4096;                %相位差第二FFT点数
B       = 3.9927e9;            %带宽
f_begin = 77e9;                %起始频率
c       = 2.99792458e8;        %光速
f_slope = 39.927;              %上升斜率MHz/us
T       = B / (f_slope * 1e12);%上升时间
RX      = 4;                   %接收天线数
chirp   = 16;                  %计算的连续chirp数
num = 0;
%% 文件路径名称
fname='../../data/zr_4_18_1443_data/2_697.bin';
%% 选择文件读取数据包
fid = fopen(fname,'rb');%打开文件
data_origin = readDCA1000(fname);


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
        fprintf("x_1 %f != x_2 %f!\n", x_1, x_2);
        x_1 = round((x + x_1 + x_2) / 3);
        x_2 = x_1;
    end
    phase   = FFT_Buff_ANG(x);
    phase_1 = FFT_Buff_1_ANG(x_1);
    phase_2 = FFT_Buff_2_ANG(x_2);
    delta_phase = phase_2 - phase_1;
    n_1 = round((x_1-1) * fs * T / (2 * M));
    frequent_B = n_1 * 2 / T + delta_phase / (pi * T);
    RRRR = c * n_1 / B + delta_phase * c / 2 / pi / B;
    %fprintf("相位差测频%f\n", frequent_B);
    phase_B = phase %+ (ADC_N - 1) * (x_1-1) * pi / M - (ADC_N - 1) * frequent_B * T * pi / ADC_N;
    R1 = frequent_B * T * c / (2 * B);
    wave_length_max = c / f_begin;
    R2 = phase_B * wave_length_max / (4 * pi);

    n_2 = round(2 * R1 / wave_length_max);
    
    
    delta_r1 = R1 - n_2 * wave_length_max / 2;
    phase_f_B = delta_r1/(wave_length_max/2);
    ret = phase_B - phase_f_B;
    
%     if(delta_r1 < 0)
%         if(mod(n_2, 2) == 0)
%             n_2 = n_2 - 2;
%         else
%             n_2 = n_2 - 1;
%         end
%     elseif(delta_r1 > 0)
%         if(mod(n_2, 2) == 0)
%             n_2 = n_2;
%         else
%             n_2 = n_2 - 1;
%         end
%     end
    
    range = n_2 * (wave_length_max / 2) + R2;
    fprintf("相位差测距:%fm\n", range);
    
    f = frequent_B;

    
    
    
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
