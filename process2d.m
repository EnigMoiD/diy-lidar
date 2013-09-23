% Communications MatLab <--> Arduino
% Matlab file 1 for use with Arduino file 1
clc;
clear all;
close all;
numSec=1;
t=[];
v=[];

s1 = serial('/dev/tty.usbmodem1421');    % define serial port
s1.BaudRate=9600;
set(s1, 'terminator', 'LF');
fopen(s1);

try
	thetaoffset = 103;
	phioffset = 45;
	i = 1;
	while i < 45
		rho = fscanf(s1,'%f')
		datatheta = fscanf(s1,'%f');
		phi = (180 - datatheta) - thetaoffset

		phi  = phi.*(pi/180);

		x = rho*cos(phi);
		y = rho*sin(phi);

		X(i) = x;
		Y(i) = y;

		PHI(i) = phi;
		RHO(i) = rho;

		i=i+1;
	end

	polar(PHI, RHO);
	grid on

	fclose(s1);
catch exception
	fclose(s1);
	throw (exception);
end