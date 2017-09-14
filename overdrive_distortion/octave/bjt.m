pkg load signal
beta = 100; %input("beta gain of transistor:");
Vcc = 9; %input("positive rail voltage:");
rb1 = 100; %input("bias divider r1:");%voltage divider 1
rb2 = 100; %input("bias divider r2:");%voltage divider 2
re = 10000;%input("emitter resistance:");
rc = 10000;%load resistance

rtot = rb1+rb2;
rb = (rb1*rb2)/rtot
Vbb = Vcc*rb2/rtot
bpo = beta+1;
alp = beta/bpo;
vbe = 0.7;%emitter forward voltage
vbc = 0.5;%collector forward voltage

Ain = input("input voltage swing in milivolts:")/1000;
F = 440; % input("input frequency:");
sps = 44100; %samples per sec
duration = 3; %secs
samp = sps*duration; %samples for clip

time = linspace(0,duration,samp);
x = time<3/F;

Vin = Ain * sin(time*2*pi*F);
Vbp = Vbb*ones(1,samp);
Vbi = Vbp .+ Vin;


figure(1);
plot(time(x),Vin(x),'r', time(x),Vbp(x),'b', time(x),Vbi(x),'k', time(x),Vce(x),'g');
pause();
