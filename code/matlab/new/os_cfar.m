function [retval] = os_cfar(data, N, protect_N)
    ret = data;
    num = numel(data);
    for i = 1 : num
        CA_ = sort([left_val(data, i, N, protect_N), left_val(fliplr(data), num - i + 1, N, protect_N)]);
        CA = CA_(900);
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
        retval = data(1 : i - protect_N - 1);
        return;
    end
    retval = data(i - protect_N - N/2 - 1 : i - protect_N - 1);
end
