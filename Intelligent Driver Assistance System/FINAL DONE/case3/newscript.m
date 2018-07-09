prevlat=0;
prevlongt=0;
prevfrontlat=0;
prevfrontlongt=0;
cspeed=50;
x=0;



%% open the serial port
s = serial('COM4');
        
set(s,'BaudRate',9600, 'Parity','none', 'Terminator', '!', 'InputBufferSize', 4500);
fopen(s);

count=1;
collectioninterval=2;
a=0;
%% infinite loop 
while count==1
    
    
    A = fgetl(s);
    if length(A)<2
        continue;
        pause(1);
    end
    A=strrep(A,'!','');
    res = regexp(A,',','split');
    lat=str2num(char(res(1)));
    longt=str2num(char(res(2)));
    distofront=str2num(char(res(3)));
  %% time=str2num(char(res(4)));
   
    frontlat=lat+distofront;
    frontlong=longt;     

    fprintf('recieved Lat=%f , Longt=%f , Distance to other=%f , time=%f \n',lat,longt,distofront);
    
    a=rand;
    x=a*5;
    prevlat=lat;
    lat=prevlat+cspeed*2+x*4;
    
    if(lat==prevlat)
        fprintf('vehicle is  halted \n');
        
    else
        fprintf('vehicle is moving \n');
        fprintf('acc=%f, prevlat=%f, lat=%f \n', x, prevlat, lat);
    end
 prevfrontlat=frontlat;
 frontlat =lat+distofront;
 fdistance = (frontlat - prevfrontlat);
 fspeed=fdistance/2;
 fprintf('prevfrontlat=%f, frontlat=%f,fspeed=%f \n', prevfrontlat,frontlat,fspeed);
 wanteddistance=sqrt(distofront^2+5^2);
 % speed of our vehicle
 pspeed = cspeed + x;
 fprintf('Present Speed = %f \n', pspeed);
 if(pspeed<50)
     wanteddistance/45=thtime;
     wanteddistanc/pspeed=time;
     if(thtime>time)
     fprintf('safe speed');
     else
         fprintf('unsafe speed');
     elseif(pspeed>50)
         wanteddistance/50=thntime;
          wanteddistanc/pspeed=time;
           if(thtime>time)
     fprintf('safe speed');
     else
         fprintf('unsafe speed');   
 
 % vb is the slowest vehicle
        vb=pspeed;        
        if vb>fspeed
           vb=fspeed; 
        end 
  % s is distance between vehicle
    sid=distofront;
  % reaction time is 5 sec for the driver
    t=5;
   Y=vb*t + 2*sid + vb* sqrt(4*sid/x);
   OSD=(Y*0.01);
   fprintf(1,'Accelearation to apply a=%d , OSD =%f \n',a,OSD);
    
    pause(collectioninterval);
 
end
    
    