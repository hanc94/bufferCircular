clc;
clear all;
close all;
[x,fs]=audioread('message.wav');
%y=myConvCircularBuffer_eco(x,10);
%soundsc(y,fs);
%% Prueba eco con r muestras de retardo
r=10000;
for i=1:length(x)-r
    y(i)=x(i+r);
end
for i=1:length(y)
    y_1(i)=x(i)+y(i);
end
for j=1:length(x)-length(y)
    y_1(i+j)=x(i+j);
end
y_1=y_1';
soundsc(y_1,fs);