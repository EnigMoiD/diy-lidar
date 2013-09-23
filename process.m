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
	thetaoffset = 90;
	phioffset = 45;
	i = 1;
	j = 1;
	while j < 110
		rho = fscanf(s1,'%f')
		phi = fscanf(s1,'%f') + phioffset
		datatheta = fscanf(s1,'%f');
		theta = (180 - datatheta) - thetaoffset

		theta = theta.*(pi/180);
		phi  = phi.*(pi/180);

		x = rho*sin(phi)*cos(theta);
		y = rho*sin(phi)*sin(theta);
		z = rho*cos(phi);

		X(i, j) = x;
		Y(i, j) = y;
		Z(i, j) = z;

		i=i+1;

		if (datatheta == 45)
			j=j+1;
			i=1;
			disp 'New loop!';
		end;
	end

	surf(X, Y, Z);

	xlabel('X');
	ylabel('Y');
	zlabel('Z');
	grid on

	Xs = X(:)';
	Ys = Y(:)';
	Zs = Z(:)';

	figure
	scatter3(Xs, Ys, Zs, 50, Zs, 'fill');
	xlabel('X');
	ylabel('Y');
	zlabel('Z');
	grid on

	fclose(s1);
catch exception
	fclose(s1);
	throw (exception);
end