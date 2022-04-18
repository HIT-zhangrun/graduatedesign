%处理1443bin数据
clc;
clear;
close all;

param = struct( ...
    'ADC_N', 256, ...
    'fs', 10e6, ...
    'N', 4096, ...
    'T', 5.5e-5, ...
    'B', 1.4991e9, ...
    'f_begin', 77e9, ...
    'c', 2.99792458e8 ...
    );

ADC = readDCA1000('../../data/zr_4_15_1443_data/2.bin');
ADC = ADC(1,1:256);
ADC_sum = frame_chirp_lane_process(ADC);
normal_fft(ADC', param);

data = ADC_sum;
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
    delta_phase = phase_2 - phase_1 + pi;
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


function [ret] = frame_chirp_lane_process(ADC_all)
numLanes = 4;
frame = 1;
chirp = 128;
sample = 256;

ADC_sum = sum(ADC_all, 1);
    ADC_mean = mean(ADC_sum);
    for i = 1 : sample
        ADC_sum(i) = ADC_sum(i) - ADC_mean;
    end
ret = transpose(ADC_sum);
end

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
retVal = adcData;
end

function ret = normal_fft(data, param)
    n = (0 : param.N/2 - 1);
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