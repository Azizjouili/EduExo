clear all;

localHost = '0.0.0.0';
 localPort = 1236;
 remotePort=1237;

 forceThreshold = 16;  
 minAngle = 80;  
 maxAngle = 180;  
 gain = 0.25;  
 positionDesired=180;
 forceDesired=10;

 %begin the UDP connection with the declared  hostIp and port:
 u = udpport("LocalHost", localHost, "LocalPort", localPort,"Timeout", 30);

 while true
    tic;

    %read the UDP data sent as a string of 27 characters and display it:
    data = read(u,27,"string");
    disp(['Received message: ', data]);

    %REGULAR EXPRESSION:
    pattern = 'Force,([-+]?\d+\.\d+);';
    match = regexp(data, pattern, 'tokens', 'once');
    if ~isempty(match)
    extracted_string = match{1};
    formatted_string = sprintf('%.2f', str2double(extracted_string));
    disp(['Extracted string:', formatted_string]);
    force = str2double(extracted_string);
    else
    disp('Pattern not found.');
    end
    
    %ADMITTANCE CONTROLLER:
    if abs(force) > forceThreshold
        positionDesired = positionDesired - gain*(force - forceDesired);
    end
    if positionDesired < minAngle
        positionDesired = minAngle;
    elseif positionDesired > maxAngle
        positionDesired = maxAngle;
    end
    
    %POSITION + TIME:
    positionString = num2str(positionDesired);
    display(positionString);
    display (force);
    %send the desired servo position with UDP to the arduino:
    write(u,positionString,"10.181.181.34",localPort);
    elapsedTime = toc;
    %display computation time in ms:
    display(elapsedTime*1000);

 end








