function [retval] = ca_cfar(data, N, protect_N)
    ret = data;
    num = numel(data);
    for i = 1 : num
        left = left_val(data, i, N, protect_N);
        right = left_val(fliplr(data), num - i + 1, N, protect_N);
        CA = (left + right) / 2;
        ret(i) =  CA;
    end
    retval = ret;
end

function [retval] = left_val(data, i, N, protect_N)
    if (i <= protect_N +1)
        retval = 0;
        return;
    end
    if (i <= N / 2 + protect_N + 1)
        retval = mean(data(1 : i - protect_N - 1));
        return;
    end
    retval = mean(data(i - protect_N - N/2 - 1 : i - protect_N - 1));
end
