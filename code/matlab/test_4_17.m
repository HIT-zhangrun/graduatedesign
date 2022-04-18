clc;
clear;
close all;
%% 参数设置      
ADC_N   = 256;           %采样点数
fs      = 10e6;          %采样频率
N       = 4096;          %FFT点数
T       = 5.5e-5;        %chirp周期
B       = 1.4991e9;      %带宽
f_begin = 77e9;          %起始频率
c       = 2.99792458e8;  %光速
RX      = 4;             %接收天线数
chirp   = 16;            %计算的连续chirp数
%% 文件路径名称
fname='../../data/zr_4_15_1443_data/1.bin';
%% 选择文件读取数据包
fid = fopen(fname,'rb');%打开文件
data_origin = readDCA1000(fname);

%% 测试
% A = load('../../data/RAW_3.6m.mat');
% data1 = A.ADCBuf;
% 
%     data_sum1 = sum(data1, 2);
%     data_mean1 = mean(data_sum1);
%     for i = 1 : 600
%         data_sum1(i) = data_sum1(i) - data_mean1;
%     end
%     data1 = hanning(600) .* data_sum1;
% temp_fft1=fft(data1, N);%对每个chirp做N点FFT
% 
% X=(0:N/2-1)*fs*c*T/2/B/N;%距离公式
% Y=abs(temp_fft1(1:N/2,1));%接收功率公式
% plot(X,Y);

%% 计算连续chirp数下单通道数据

data = reshape(data_origin, [], ADC_N);
data = data(1,:);
data = sum(data, 1);
data_mean = mean(data);
for i = 1 : ADC_N
    data(i) = data(i) - data_mean;
end
data_process = hanning(ADC_N)' .* data;


%% 距离FFT
temp_fft=fft(data_process, N);%对每个chirp做N点FFT

%% 一维FFT后,距离与接收功率图    
X=(0:N/2-1)*fs*c*T/2/B/N;%距离公式
Y=abs(temp_fft(1:N/2));%接收功率公式
plot(X,Y);

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
retVal = adcData(1, :);
end