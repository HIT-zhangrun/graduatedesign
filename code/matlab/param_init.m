function [param] = param_init()
    param_1 = struct( ...
        'chirp',    16, ...                     %计算的连续chirp数
        'ADC_N',    600, ...                    %采样点数
        'RX',       4, ...                      %接收通道
        'fs',       15e6, ...                   %采样频率
        'N',        4096*2, ...                 %FFT点数
        'f_slope',  39.927, ...                 %上升斜率MHz/us
        'B',        3.9927e9, ...               %带宽
        'T',        0, ...                      %上升时间
        'f_begin',  77e9, ...                   %起始频率
        'c',        2.99792458e8, ...           %光速
        'M',        4096*2 ...                  %相位差FFT点数
        );
    param_1.T = param_1.B / (param_1.f_slope * 1e12);%上升时间
 
    param = param_1;
end