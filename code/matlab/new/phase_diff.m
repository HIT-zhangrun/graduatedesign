function [range, f] = phase_diff(data_origin, p)
    data = data_origin;
    data_process  = add_window(data(1 : p.sample));
    data_process1 = add_window(data(1 : p.sample / 2));
    data_process2 = add_window(data(p.sample / 2 + 1 : p.sample));

    FFT_Buff   = fft(data_process, p.M);
    FFT_Buff_1 = fft(data_process1, p.M);
    FFT_Buff_2 = fft(data_process2, p.M);
    FFT_Buff_ABS   = abs(FFT_Buff);
    FFT_Buff_1_ABS = abs(FFT_Buff_1);
    FFT_Buff_2_ABS = abs(FFT_Buff_2);
    FFT_Buff_ANG   = angle(FFT_Buff);
    FFT_Buff_1_ANG = angle(FFT_Buff_1);
    FFT_Buff_2_ANG = angle(FFT_Buff_2);
    [x,   ] = find(FFT_Buff_ABS   == max(FFT_Buff_ABS), 1);
    [x_1, ] = find(FFT_Buff_1_ABS == max(FFT_Buff_1_ABS), 1);
    [x_2, ] = find(FFT_Buff_2_ABS == max(FFT_Buff_2_ABS), 1);

    if(x_1 ~= x_2)
        %fprintf("x_1 %f != x_2 %f!\n", x_1, x_2);
        x_1 = round((x + x_1 + x_2) / 3);
        x_2 = x_1;
    end
    phase   = FFT_Buff_ANG(x);
    phase_1 = FFT_Buff_1_ANG(x_1);
    phase_2 = FFT_Buff_2_ANG(x_2);
    delta_phase = phase_2 - phase_1;
    n_1 = round(x_1 * p.fs * p.T / (2 * p.M));
    frequent_B = n_1 * 2 / p.T - delta_phase / (pi * p.T);
    %fprintf("相位差测频%f\n", frequent_B);
    phase_B = phase; %+(p.sample - 1) * (x_1-1) * pi / p.M - (p.sample - 1) * frequent_B * p.T * pi / p.sample;
    R1 = frequent_B * p.T * p.c / (2 * p.B);
    wave_length_max = p.c / p.f_begin;
    R2 = phase_B * wave_length_max / (4 * pi);
    n_2 = round(2 * R1 / wave_length_max);
    
    
    delta_r1 = R1 - n_2 * wave_length_max / 2;
    phase_f_B = delta_r1/(wave_length_max/2);
    ret = phase_B - phase_f_B;
    if(phase_B - phase_f_B > pi/2)
        n_2 = n_2 - 1;
    end
    if(phase_f_B - phase_B > pi/2)
        n_2 = n_2 + 1;
    end
    
    range = n_2 * (wave_length_max / 2) + R2;
    fprintf("相位差测距:%fm\n", R1);
    range = R1;
    f = frequent_B;
end