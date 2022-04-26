function [range, f] = chirp_z(data_origin, p) 
    N1 = 1024;
    data_origin = add_window(data_origin);
    n = (0 : N1/2-1);
    x_frequent = n * p.fs / N1;
    x_range = x_frequent * p.T * p.c / (2 * p.B);
    FFT = fft(data_origin, N1);
    FFT_ABS = abs(FFT(1 : N1 / 2));
    [x, ] = find(FFT_ABS == max(FFT_ABS), 1);
    range = x_range(x);
    %fprintf("FFT测距频率:%fHz\n", x_frequent(x));
%     fprintf("FFT测距:%fm\n", range);
%     figure();
%     plot(x_range, FFT_ABS);
%     title('FFT测距');
%     xlabel('距离/m]');ylabel('强度/dB]');
%     hold on;

    


% CZT
tic;
    D1 = N1;
    D2 = 100;
    XX = 1;%前后拓展的频点
    M = p.fs/D1;
    f1 = x_frequent(x)-M*XX;
    f2 = x_frequent(x)+M*XX;
    deta_f = f2 - f1;
    w = exp(-j*2*pi*(f2-f1)/(deta_f*D2));
    a = exp(j*2*pi*f1/deta_f);
    Y1 = czt(data_origin, D2, w, a);
    fn = (0:D2-1)/D2;
    F1 = (f2-f1)*fn + f1;
    [i ,n] = max(Y1);
    
    range_x = F1*p.c*p.T/2/p.B;%距离公式
    figure();
    plot(range_x,abs(Y1));
    title('CZT变换测距');
    xlabel('距离/m]');ylabel('强度/dB]');
    range = F1(n)*p.c*p.T/2/p.B;

    fprintf("CZT测算距离1.697940m\n", range);
toc;

end