clc;
clear;
close all;

p = param_init(1);
file = '../../data/zr_4_24_1443_data/1/2_749.bin';
raw_data = raw_data_process(file, p);
fft_process(raw_data, p);
file = '../../data/zr_4_24_1443_data/1/2_768.bin';
raw_data = raw_data_process(file, p);
fft_process(raw_data, p);

% p = param_init(2);
% file = '../../data/zr_4_24_1443_data/2/2_767.bin';
% raw_data = raw_data_process(file, p);
% fft_process(raw_data, p);
% phase_diff(raw_data, p);
% 
% file = '../../data/zr_4_24_1443_data/2/2_806.bin';
% raw_data = raw_data_process(file, p);
% fft_process(raw_data, p);
% phase_diff(raw_data, p);
% 
% file = '../../data/zr_4_24_1443_data/2/2_836.bin';
% raw_data = raw_data_process(file, p);
% fft_process(raw_data, p);
% phase_diff(raw_data, p);

p = param_init(3);
% file = '../../data/zr_4_18_1443_data/2_695.bin';
% raw_data = raw_data_process(file, p);
% fft_process(raw_data, p);
% phase_diff(raw_data, p);
% 
% file = '../../data/zr_4_18_1443_data/2_697.bin';
% raw_data = raw_data_process(file, p);
% fft_process(raw_data, p);
% phase_diff(raw_data, p);
% 
% file = '../../data/zr_4_18_1443_data/2_961.bin';
% raw_data = raw_data_process(file, p);
% fft_process(raw_data, p);
% phase_diff(raw_data, p);
% 
% file = '../../data/zr_4_18_1443_data/2_965.bin';
% raw_data = raw_data_process(file, p);
% fft_process(raw_data, p);
% phase_diff(raw_data, p);

file = '../../data/zr_4_24_1443_data/3/1_628.bin';
raw_data = raw_data_process(file, p);
fft_process(raw_data, p);
chirp_z(raw_data, p);
%phase_diff(raw_data, p);

% file = '../../data/zr_4_24_1443_data/3/1_636.bin';
% raw_data = raw_data_process(file, p);
% fft_process(raw_data, p);
% phase_diff(raw_data, p);
% 
% file = '../../data/zr_4_24_1443_data/3/1_639.bin';
% raw_data = raw_data_process(file, p);
% fft_process(raw_data, p);
% phase_diff(raw_data, p);
% 
% file = '../../data/zr_4_24_1443_data/3/1_641.bin';
% raw_data = raw_data_process(file, p);
% fft_process(raw_data, p);
% phase_diff(raw_data, p);
