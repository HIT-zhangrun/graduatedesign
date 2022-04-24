clc;
clear;
close all;

p = param_init();
file = '../../data/zr_4_23_1443_data/2_617_high.bin';
raw_data = raw_data_process(file);
