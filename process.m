% Communications MatLab <--> Arduino
% Matlab file 1 for use with Arduino file 1
clc;
clear all;
numSec=1;
t=[];
v=[];

s1 = serial('/dev/tty.usbmodem1411');    % define serial port
s1.BaudRate=9600;
set(s1, 'terminator', 'LF');
fopen(s1);

try
	i = 1;
	j = 1;
	while j < 10
		rho = fscanf(s1,'%f');
		phi = fscanf(s1,'%f');
		theta = fscanf(s1,'%f');

		if (theta == 0)
			j=j+1;
			i=1;
		end

		theta = theta.*(pi/180);
		phi  = phi.*(pi/180);

		x = rho*sin(phi)*cos(theta);
		y = rho*sin(phi)*sin(theta);
		z = rho*cos(phi);

		X(i, j) = x;
		Y(i, j) = y;
		Z(i, j) = z;

		i=i+1;
	end

	surf(X, Y, Z);
	grid on
	fclose(s1);
catch exception
	fclose(s1);
	throw (exception);
end