clc; close all;

Rex_x = [1, 0, 1, 0, 0]
Rex_y = [1, 1, 0, 1 , 1]

m = length(Rex_y);
N = 31;

out = zeros(1, N);

for i = 1:N
    out(i) = Rex_x(5) ~= Rex_y(5);

    temp1 = Rex_x(3) ~= Rex_x(5);
    temp2 = Rex_y(3) ~= Rex_y(5);

    for j = m:-1:2
        Rex_x(j) = Rex_x(j-1);
        Rex_y(j) = Rex_y(j-1);
    end
    Rex_x(1) = temp1;
    Rex_y(1) = temp2;
end

out

disp('Автокорреляция out')
disp(autocorr(out, N-1));

Rex_x_2 = [1, 0, 1, 0 , 1]
Rex_y_2 = [1, 0, 1, 1 , 0]

out_2 = zeros(1, N);

for i = 1:N
    out_2(i) = Rex_x_2(5) ~= Rex_y_2(5);

    temp1 = Rex_x_2(3) ~= Rex_x_2(5);
    temp2 = Rex_y_2(3) ~= Rex_y_2(5);

    for j = m:-1:2
        Rex_x_2(j) = Rex_x_2(j-1);
        Rex_y_2(j) = Rex_y_2(j-1);
    end
    Rex_x_2(1) = temp1;
    Rex_y_2(1) = temp2;
end

out_2

disp('Корреляция out и out2')
disp(xcorr(out, out_2))

figure;
autocorr(out, N-1);
title('Автокорреляция');
xlabel('Лаги');
ylabel('Автокорреляция');
