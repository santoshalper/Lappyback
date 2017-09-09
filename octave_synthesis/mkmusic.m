% This M file has been tested in Matlab and Octave
% It works the same
%
% Octave may require you to copy wavout.m to the working folder
% I have had to do it on a machine running an old version of vista


fs=11200;
t=0:1/fs:20.0;
t=t(:);
%generate two notes and play a tune and a chord... sort of
% The tune is given by 60, 67, 60
% i.e. play the note 60, then note 67 and then note 60

% The chord we will play is notes 60, 65 and 67 simultaneously.

% We will use the Fourier coefficients for a clarinet sound.
jay = sqrt(-1);
C = -jay * [100, 60, 10, 10, 42, 15, 5]
C0=0;


%Generate the note #60 using fourier series
f60=440*2^((60-69)/12)

note60 = C0;
for k=1:7 % We have only 7 Coeeficients
    w = 2*pi*f60*k; %omega for k-th harmonic
    note60 = note60 + 2*real( C(k)*exp(jay*w*t) );
end
% scale it down so the maximum absolute value is less than 1, say 0.85
maxval = max(abs(note60));
note60 = note60 /maxval * 0.85;

% repeat for note #67
f67=440*2^((67-69)/12)

note67 = C0;
for k=1:7
    w = 2*pi*f67*k; %omega for k-th harmonic
    note67 = note67 + 2*real( C(k)*exp(jay*w*t) );
end
maxval = max(abs(note67));
note67 = note67 /maxval * 0.85;


silence=0*(0:1/fs:0.1); %0.1 second of silence between notes

%make one long signal by putting one on top of other. 
%The index (:) makes it a column vector
% The music consists of the notes: 60,67,60

music=[
	note60(:)
	silence(:)
	note67(:)
	silence(:)
	note60(:)
];

disp('=================================================');
disp('  Writing the wave files ... ');
disp('  If you get an error: Permission denied'); 
disp('  make sure have closed the Windows Media Player. (oh well...)');
disp('=================================================');
if exist('wavout.m', 'file')
        % if wavout exists, use it!
        wavout(music,fs,16,'sample.wav');
else
	    wavwrite(music,fs,16,'sample.wav');
end

f65=440*2^((65-69)/12)

note65 = C0;
for k=1:7
    w = 2*pi*f65*k; %omega for k-th harmonic
    note65 = note65 + 2*real( C(k)*exp(jay*w*t) );
end
maxval = max(abs(note65));
note65 = note65 /maxval * 0.85;



combined = note60+note65+note67;
maxval = max(abs(combined));
combined = combined /maxval * 0.85;

if exist('wavout.m', 'file')
        % if wavout exists, use it!
        wavout(combined,fs,16,'combined.wav');
else
	    wavwrite(combined,fs,16,'combined.wav');
end
