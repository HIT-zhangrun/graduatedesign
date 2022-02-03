clc;
clear;
close all;

A=load('..\data\RAW_4.0m.mat');                           % 导入雷达数据

ADCBuf=A.ADCBuf;
x=1:600;

plot(x,ADCBuf(:,1),'.');

