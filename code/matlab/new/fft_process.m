function [range, f] = fft_process(data_origin, p)  
    data_origin = add_window(data_origin);
    n = (0 : p.N/2-1);
    x_frequent = n * p.fs / p.N;
    x_range = x_frequent * p.T * p.c / (2 * p.B);
    FFT = fft(data_origin, p.N);
    FFT_ABS = abs(FFT(1 : p.N / 2));
    [x, ] = find(FFT_ABS == max(FFT_ABS), 1);
    range = x_range(x);
    %fprintf("FFT测距频率:%fHz\n", x_frequent(x));
    fprintf("FFT测距:%fm\n", range);
    figure();
    plot(x_range, FFT_ABS);
    title('FFT测距');
    xlabel('距离/m]');ylabel('强度/dB]');
    hold on;
    %plot(x_range, 4.5*ca_cfar(FFT_ABS, 1800, 10));
    %plot(x_range, 6*os_cfar(FFT_ABS, 1800, 10));

    f = x_frequent(x);
end