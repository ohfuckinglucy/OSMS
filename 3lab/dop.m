clc; close all;

%% Доп задание
a = randi(100,16,1) - 1;
b = randi(100,16,1) - 1;
c = randi(100,16,1) - 1;

res_ab = normcorr(a, b);
res_ac = normcorr(a, c);
res_bc = normcorr(b, c);

fprintf("Нормализованная корреляция АБ: %.4f\n", res_ab);
fprintf("Нормализованная корреляция АС: %.4f\n", res_ac);
fprintf("Нормализованная корреляция БС: %.4f\n", res_bc);

figure();
subplot(3, 1, 1);
plot(1:16, a);
title("a[]");
subplot(3, 1, 2);
plot(1:16, b);
title("b[]");
subplot(3, 1, 3);
plot(1:16, c);
title("c[]");

res_a_shift = zeros(1, 16);
res_b_shift = zeros(1, 16);
res_c_shift = zeros(1, 16);

for i = 1:16
    shifted_a = circshift(a, i-1);
    shifted_b = circshift(b, i-1);
    shifted_c = circshift(c, i-1);
    res_a_shift(i) = normcorr(a, shifted_a);
    res_b_shift(i) = normcorr(b, shifted_b);
    res_c_shift(i) = normcorr(c, shifted_c);
end

figure();
subplot(3, 1, 1);
plot(1:16, res_a_shift);
title("Автокорреляция a[]");
subplot(3, 1, 2);
plot(1:16, res_b_shift);
title("Автокорреляция b[]");
subplot(3, 1, 3);
plot(1:16, res_c_shift);
title("Автокорреляция c[]");

function result = normcorr(a, b)
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    n = length(a);
    for i = 1:n
        sum1 = sum1 + a(i) * b(i);
        sum2 = sum2 + a(i) * a(i);
        sum3 = sum3 + b(i) * b(i);
    end
    result = sum1 / sqrt(sum2 * sum3);
end