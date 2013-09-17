% Communications MatLab <--> Arduino
% Matlab file 1 for use with Arduino file 1
clc;
clear all;
numSec=1;
t=[];
v=[];

s1 = serial('/dev/tty.usbmodem1421');    % define serial port
s1.BaudRate=9600;
set(s1, 'terminator', 'LF');
fopen(s1);

try
    while 1
        fscanf(s1,'%f')
    end
    fclose(s1);
catch exception
    fclose(s1);
    throw (exception);
end