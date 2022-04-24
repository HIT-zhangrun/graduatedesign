%% 普通FFT
function [range, f] = fft_process(data_origin)
    n = (0 : N/2-1);
    x_frequent = n * fs / N;
    x_range = x_frequent * T * c / (2 * B);
    FFT = fft(data_origin, N);
    FFT_ABS = abs(FFT(1 : N / 2));
    [x, ] = find(FFT_ABS == max(FFT_ABS), 1);
    range = x_range(x-1);
    %fprintf("FFT测距频率:%fHz\n", x_frequent(x));
    %fprintf("FFT测距:%fm\n", range);
%     figure(3);
%     plot(x_range, FFT_ABS);
%     title('FFT测距');
%     xlabel('距离/m]');ylabel('强度/dB]');
    f = x_frequent(x-1);
end