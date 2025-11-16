clc; close all;

%% 3 - 5 задания
t = linspace(0, 3, 3000);

f1 = 20; % Мой порядковый номер в журнале
f2 = 24; % Мой порядковый номер в журнале + 4
f3 = 41; % Мой порядковый номер в журнале * 2 + 1

s1_t = cos(2*pi*f1*t);
s2_t = cos(2*pi*f2*t);
s3_t = cos(2*pi*f3*t);

a_t = 2*s1_t + 4*s2_t + s3_t;
b_t = s1_t + 1/3*s2_t;

cor_sa = corr(s1_t, a_t);
cor_sb = corr(s1_t, b_t);

norm_cor_sa = normcorr(s1_t, a_t);
norm_cor_sb = normcorr(s1_t, b_t);

fprintf("Корелляция S(t) и a(t): %.4f\n", cor_sa);
fprintf("Корелляция S(t) и b(t): %.4f\n", cor_sb);
fprintf("Нормализованная корелляция S(t) и a(t): %.4f\n", norm_cor_sa);
fprintf("Нормализованная корелляция S(t) и b(t): %.4f\n", norm_cor_sb);

%% 6

a = [0.3, 0.2, -0.1, 4.2, -2, 1.5, 0];
b = [0.3, 4, -2.2, 1.6, 0.1, 0.1, 0.2];

figure;
subplot(2, 1, 1);
plot(0:length(a)-1, a);
grid;
title("a[]");
xlabel("Индекс");
ylabel("Значение");
subplot(2, 1, 2);
plot(0:length(b)-1, b);
grid;
title("b[]");
xlabel("Индекс");
ylabel("Значение");

n = length(b);

corr_val = zeros(n);

b_s = b;

corr_val(1) = normcorr(a, b_s);

for j = 2:n
    for i = 1:n
        swap = b_s(i);
        b_s(i) = b_s(n);
        b_s(n) = swap;
    end

    corr_val(j) = normcorr(a, b_s);
end

figure;
plot(0:length(a)-1, corr_val);
grid;
title("Корреляция а и б со сдвигом");
xlabel("Сдвиг");
ylabel("Значение");

b_shifted = [b(end-2+1:end), b(1:end-2)];

figure;
subplot(2, 1, 1);
plot(0:length(a)-1, a);
grid;
title("a[]");
xlabel("Индекс");
ylabel("Значение");
subplot(2, 1, 2);
plot(0:length(b)-1, b_shifted);
grid;
title("b[] со сдвигом на 2");
xlabel("Индекс");
ylabel("Значение");

%% Доп задание

array = b;



function result = corr(a, b)
    result = 0;
    n = length(a);
    for i = 1:n
        result = result + a(i) * b(i);
    end
end

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