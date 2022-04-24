function [retval] = add_window(data)
    size = numel(data);
    retval = hanning(size) .* data;
end