function [param] = param_init(num)

    param_1 = struct( ...
        'chirp',    50, ...                     %计算的连续chirp数
        'frame',    1, ...                      %帧数
        'sample',   1024, ...                   %采样点数
        'rx',       4, ...                      %接收通道
        'fs',       18e6, ...                   %采样频率
        'N',        4096*4, ...                 %FFT点数
        'f_slope',  39.927, ...                 %上升斜率MHz/us
        'B',        3.9927e9, ...               %带宽
        'T',        0, ...                      %上升时间
        'f_begin',  77e9, ...                   %起始频率
        'c',        2.99792458e8, ...           %光速
        'M',        4096*4 ...                  %相位差FFT点数
        );
    param_1.T = param_1.B / (param_1.f_slope * 1e12);%上升时间

    param_2 = struct( ...
        'chirp',    50, ...                     %计算的连续chirp数
        'frame',    1, ...                      %帧数
        'sample',   600, ...                   %采样点数
        'rx',       4, ...                      %接收通道
        'fs',       10e6, ...                   %采样频率
        'N',        4096*8, ...                 %FFT点数
        'f_slope',  39.927, ...                 %上升斜率MHz/us
        'B',        3.9927e9, ...               %带宽
        'T',        0, ...                      %上升时间
        'f_begin',  77e9, ...                   %起始频率
        'c',        2.99792458e8, ...           %光速
        'M',        4096*8 ...                  %相位差FFT点数
        );
    param_2.T = param_2.B / (param_2.f_slope * 1e12);%上升时间

    param_3 = struct( ...
        'chirp',    128, ...                     %计算的连续chirp数
        'frame',    8, ...                      %帧数
        'sample',   600, ...                   %采样点数
        'rx',       4, ...                      %接收通道
        'fs',       15e6, ...                   %采样频率
        'N',        4096*64, ...                 %FFT点数
        'f_slope',  39.927, ...                 %上升斜率MHz/us
        'B',        3.9927e9, ...               %带宽
        'T',        0, ...                      %上升时间
        'f_begin',  77e9, ...                   %起始频率
        'c',        2.99792458e8, ...           %光速
        'M',        4096 ...                  %相位差FFT点数
        );
    param_3.T = param_3.B / (param_3.f_slope * 1e12);%上升时间
 
    switch(num)
    case 1
        param = param_1;
    case 2
        param = param_2;
    case 3
        param = param_3;
    end
end