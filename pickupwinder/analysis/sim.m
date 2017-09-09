pkg load signal
l = input("inductance in henry:");
r = input("resistance in kiloohms:")*1e3;
c = input("capacitance in pico:")*1e-12;
b = [ (1/(l*c)) ];
a = [ 1 r/l (1/(l*c)) ];
w = logspace(1,5,256);
wo = sqrt((1/(l*c)));
fo = wo/(2*pi)
Q = l/(r*wo)
pk = r*c/2*wo;
wp = wo*sqrt(1-pk^2);
fp = wp/(2*pi)
r
l
c
data = freqs(b,a,w);
mag = abs(data);
phase = angle(data);
subplot(2,1,1), loglog(w,mag), grid on
xlabel 'frequency', ylabel Magnitude
pause;

