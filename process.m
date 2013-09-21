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
    i=1;
    while i < 100
        R(i) = fscanf(s1,'%f');
        phi(i) = fscanf(s1,'%f');
        theta(i) = fscanf(s1,'%f');

        i=i+1;
    end
    theta = theta.*(pi/180);
    phi  = phi.*(pi/180);
    % cart = sph2cart(phi, theta, R);
    phi
    R
    polar(phi, R);
    fclose(s1);
catch exception
    fclose(s1);
    throw (exception);
end