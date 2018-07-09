
%% open the serial port
s = serial('COM52');
        
set(s,'BaudRate',9600, 'Parity','none', 'Terminator', '!', 'InputBufferSize', 4500);
fopen(s);

count=1;

imleft = imread('left1.jpg');
imright = imread('right1.jpg');
imbreak = imread('sp1.jpg');
imparking = imread('np1.jpg');
imnstanding = imread('ns1.jpg');
im30limit = imread('ovs1.jpg');
im80limit = imread('ovs2.jpg');


%% capture all serial data in infinite loop
while count==1
    
    A = fgetl(s);
    A
    if length(A)<2
        pause(1);
        continue;
    end
    A=strrep(A,'!','');
    res = regexp(A,',','split');
    tsign=str2num(char(res(1)));
    tspeed=str2num(char(res(2)));
    
    if tsign==0
        %[x,Fs,nbits]= wavread('left.wav');
        %wavplay(x,Fs);
        figure
        imshow(imleft);
        
    end
    
    if tsign==1
         %[x,Fs,nbits]= wavread('right.wav');
         %wavplay(x,Fs);
         imshow(imright);
    end
    
    if tsign==2
               
        %[x,Fs,nbits]= wavread('speedbrake.wav');
         %wavplay(x,Fs);
         imshow(imbreak);
    end
    
    if tsign==3
               
        %[x,Fs,nbits]= wavread('parking.wav');
         %wavplay(x,Fs);
         imshow(imparking);
    end
    
    if tsign==4
               
        %[x,Fs,nbits]= wavread('nstanding.wav');
         %wavplay(x,Fs);
         imshow(imnstanding);
    end
    
    if tsign==5
               
        %[x,Fs,nbits]= wavread('30limit.wav');
         %wavplay(x,Fs);
         imshow(im30limit);
         speed=30; 
         fprintf('the speed travelling=%f \n',speed);
         accr=rand*5;
	if(accr>10)
		accr=accr-20;
        fprintf(1,'The Current accelaration = %f \n', accr);
    else
        fprintf(1,'The Current accelaration = %f \n', accr);
    end
    sspeed=speed+accr;
	fprintf(1,'the speed during acceleration %f \n', sspeed);
	if (tspeed>sspeed)
		fprintf(1,'SAFE Speed %d \n', tspeed);
	else
		fprintf(1,'Reduce Speed %d \n', tspeed);

		if(accr>0)
			fprintf(1,'!!! Vehicle cannot accelerate in this situation, overspeed set, pls decelerate \n');
		else
			fprintf(1,'!!! Vehicle is decelerating \n');
		end
		[x, Fs, nbits]= wavread('overspeed.wav');
		end
        
    end
    
    if tsign==6
               
        %[x,Fs,nbits]= wavread('80limit.wav');
         %wavplay(x,Fs);
         imshow(im80limit);
         speed=25;
         fprintf('the speed travelling=%f \n',speed);
       accr=rand*5;
	if(accr>10)
		accr=accr-20;
        fprintf(1,'The Current accelaration = %f \n', accr);
    else
	fprintf(1,'The Current accelaration = %f \n', accr);
    end
    sspeed=speed+accr;
    fprintf(1,'the speed during acceleration %f \n', sspeed);
	
	if (tspeed>sspeed)
		fprintf(1,'SAFE Speed %d \n', tspeed);
	else
		fprintf(1,'Reduce Speed %d \n', tspeed);

		if(accr>0)
			fprintf(1,'!!! Vehicle cannot accelerate in this situation, overspeed set, pls decelerate \n');
		else
			fprintf(1,'!!! Vehicle is decelerating \n');
		end
		[x, Fs, nbits]= wavread('overspeed.wav');
		end
    end
    
    if tsign==7
       fprintf(1,'Vehicle Stopped\n');
       break;
        
    end
    
  
		pause(10);
end
fclose(s);