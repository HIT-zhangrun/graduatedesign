clear all;
close all;

chirp_number = 10;
adc_sample = [];
N = 512;
fid = fopen('../data/2022123214723.bin','rb'); %bin文件路径
raw = fread(fid,800*chirp_number,'int16');
fclose(fid);


for i = 1 : chirp_number
    adc_sample(i,:) = (raw(1 + 800 * (i - 1): 800 + 800 * (i - 1)) - 8192) .* 3300 ./ 16384;
end
ADCBufMean=mean(adc_sample);    %ADCBufMean = 平均后的采样数据
ADCBufMean=transpose(ADCBufMean);
ADCBufMean=hann(800).*ADCBufMean;
ft = fft(ADCBufMean,N);%FFT

    n = (1 : N/2);
    x_frequent = n * 2e6 / N;
    x_range = x_frequent * 6e-4 * 2.99792458e8 * 100 / (2 * 3.98e9);
    
    FFT_ABS = abs(ft(1 : N / 2));
    [x, y] = find(FFT_ABS == max(FFT_ABS), 1);
    range = x_range(x);
    
figure(1);
hold on;
for i = 1 : chirp_number   
    plot(adc_sample(i,:));
end
figure(2);
plot(ADCBufMean);
figure(3);
plot(abs(ft));
