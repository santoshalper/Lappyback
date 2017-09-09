pkg load signal
bit= 24;   %bit      
sps = 44100; %samples per sec
duration = 20; %secs
samp = sps*duration; %samples for clip

basefreq = 1000;

time = linspace(0,duration,samp);
n = 2^nextpow2(samp);
resplength = [1:n/2]*sps/n;

sine = sin(time*2*pi*basefreq);
sineresp = fft(sine,n)/n;
sineresp = sineresp(1:n/2);

sqar = square(time*2*pi*basefreq);
sqarresp = fft(sqar,n)/n;
sqarresp = sqarresp(1:n/2);

saw = sawtooth(time*2*pi*basefreq);
sawresp = fft(saw,n)/n;
sawresp = sawresp(1:n/2);

o=5;
x = time<5/basefreq;
f = resplength<(basefreq*2^o); 

figure(1);
subplot(2,2,1);
plot(time(x),sine(x));
title(sprintf('sine wave at freq = %d hz',basefreq));
subplot(2,2,3);
plot(resplength(f),abs(sineresp(f)));
title('frequency response');
subplot(2,2,4);
plot(resplength(f),unwrap(angle(sineresp(f)),pi/2));
title('phase response');

figure(2);
subplot(2,2,1);
plot(time(x),sqar(x));
title(sprintf('square wave at freq = %d hz',basefreq));
subplot(2,2,3);
plot(resplength(f),abs(sqarresp(f)));
title('frequency response');
subplot(2,2,4);
plot(resplength(f),unwrap(angle(sqarresp(f)),pi/2));
title('phase response');

figure(3);
subplot(2,2,1);
plot(time(x),saw(x));
title(sprintf('sawtooth wave at freq = %d hz',basefreq));
subplot(2,2,3);
plot(resplength(f),abs(sawresp(f)));
title('frequency response');
subplot(2,2,4);
plot(resplength(f),unwrap(angle(sawresp(f)),pi/2));
title('phase response');


wavwrite(sine,sps,bit,'sine.wav');
wavwrite(sqar,sps,bit,'sqar.wav');
wavwrite(saw,sps,bit,'saw.wav');

pause()


