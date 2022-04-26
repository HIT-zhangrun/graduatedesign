Fs = 15;  % Sampling Frequency

Fstop1 = 0.1;             % First Stopband Frequency
Fpass1 = 0.133;           % First Passband Frequency
Fpass2 = 0.266;           % Second Passband Frequency
Fstop2 = 0.3;             % Second Stopband Frequency
Dstop1 = 0.001;           % First Stopband Attenuation
Dpass  = 0.057501127785;  % Passband Ripple
Dstop2 = 0.0001;          % Second Stopband Attenuation
dens   = 20;              % Density Factor

% Calculate the order from the parameters using FIRPMORD.
[N, Fo, Ao, W] = firpmord([Fstop1 Fpass1 Fpass2 Fstop2]/(Fs/2), [0 1 ...
                          0], [Dstop1 Dpass Dstop2]);

% Calculate the coefficients using the FIRPM function.
b  = firpm(N, Fo, Ao, W, {dens});
Hd = dfilt.dffir(b);
data_process = filter(b,1,data_process);
temp_fft=fft(data_process, N);%对每个chirp做N点FFT

%% 一维FFT后,距离与接收功率图    
X=(0:N/2-1)*fs*c*T/2/B/N;%距离公式
Y=abs(temp_fft(1:N/2));%接收功率公式
figure(1);
plot(X,Y);