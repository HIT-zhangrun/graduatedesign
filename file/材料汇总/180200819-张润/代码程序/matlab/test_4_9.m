%生成bin文件用
clc;
clear;
close all;    
A = load('../../data/RAW_3.6m.mat');
data = A.ADCBuf;
data_sum = sum(data, 2);
% data_mean = mean(data_sum);
% for i = 1 : 600
%     data_sum(i) = data_sum(i) - data_mean;
% end
fid = fopen('../../data/data.bin', 'w');
fwrite(fid, data_sum, 'int16');
fclose(fid);