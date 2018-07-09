Fs=44100;
fprintf(1,'Say something, it will be recorded\n');
y=wavrecord(4*Fs,Fs);
fprintf(1,'Recording stopped');
wavplay(y,Fs);
wavwrite(y,Fs,'testmysample.wav');


% 
% [signal,fs] = wavread('test.wav');
% signal = signal(:,1);
% figure('Name','Recorded Voice');
% plot(psd(spectrum.periodogram,signal,'Fs',fs,'NFFT',length(signal)));
% 
% figure('Name','Recorded voice time plot');
% t=linspace(0,length(signal)/fs,length(signal));
% plot(t,signal);
% 
% 
% fprintf(1,'Adding noise to it');
% y=awgn(y,30);
% wavplay(y,Fs);
% 
% wavwrite(y,Fs,'testwithnoise.wav');
% 
% 
% [signal,fs] = wavread('testwithnoise.wav');
% signal = signal(:,1);
% figure('Name','Noise with Voice');
% plot(psd(spectrum.periodogram,signal,'Fs',fs,'NFFT',length(signal)));
% 
% figure('Name','voice with noise time plot');
% t=linspace(0,length(signal)/fs,length(signal));
% plot(t,signal);
% 
