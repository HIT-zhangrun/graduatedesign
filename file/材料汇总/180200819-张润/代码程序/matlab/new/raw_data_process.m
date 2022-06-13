%% 处理DAC原始bin文件，输出4路复数采样点
function [retval] = raw_data_process(fileName, param)
%% global variables
% change based on sensor config
numADCBits = 16; % number of ADC bits per sample
numLanes = 4; % do not change. number of lanes is always 4 even if only 1 lane is used. unused lanes
isReal = 0; % set to 1 if real only data, 0 if complex dataare populated with 0 %% read file and convert to signed number
% read .bin file
fid = fopen(fileName,'r');
% DCA1000 should read in two's complement data
adcData = fread(fid, 'int16');
% if 12 or 14 bits ADC per sample compensate for sign extension
if numADCBits ~= 16
l_max = 2^(numADCBits-1)-1;
adcData(adcData > l_max) = adcData(adcData > l_max) - 2^numADCBits;
end
fclose(fid);
%% organize data by LVDS lane
% for real only data
if isReal
% reshape data based on one samples per LVDS lane
adcData = reshape(adcData, numLanes, []);
%for complex data
else
% reshape and combine real and imaginary parts of complex number
adcData = reshape(adcData, numLanes*2, []);
adcData = adcData([1,2,3,4],:) + sqrt(-1)*adcData([5,6,7,8],:);
end
%% return receiver data
%retVal = adcData;
%% 单通道数据
% data = adcData(2, :);
% 
% data1 = reshape(data, [], param.sample);
% % data_sum = sum(data1);
% % data_mean = mean(data_sum);
% % for i = 1 : param.sample
% %     data_sum(i) = (data_sum(i) - data_mean) / data_mean;
% % end
% retval = data1;
retval = adcData(2, 1:param.sample);
retval = adcData(2, 5*param.sample + 1 :param.sample*6);
end