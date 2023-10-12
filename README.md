# IOT_Master.dev

![pngwing com(2)zxc](https://github.com/amirsayyad7686/IOT_Master.dev/assets/78236642/1d2806a5-7e5e-4d71-9972-32f0bdffa96e)

dynamic iot platform that i named it : IOT_Master 
this platfrom has too many features for every junior developers for making their own plans and designs in iot and fulltime responsible with no limits , this platform designed open-source and has realtime actions.
Every one can join with my iot masters colony and making their own palns with a responsible GUI and control their controllers (Esp modules , NodeMCU) with a code that i prepare for them just with one click and easy to setup and compile.
This web site has really secure and fast just with one experience you will like it :) 
im glad to having your feedback

domain : iot-master.dev & iot-master.ir

How to start ?
Step 1 (Registration) : Please register for free in iot-master.dev after that you have iot dashboard and it accessible just for you 
Step 2 (Setup a node) : Define a node that is your module like NodeMCU or esp32 ... and fill your WIFI config like ssid and password and choose a name for it 
Step 3 (Setup components) : Setup your components on your node (Toggle button , Push button , Sensor , Slider)
Step 4 (Generate Code) : Go to component table page and click on generate code button get code for your selected node with all components that you setuped before , it will send to your email , your codes containing 3 files with name static.h static.cpp and IOT_Master.ino these three file should stay together in a file and compile together just a modification is necessary for codes is select your desire gpio in 
gpioMappings[component id dont change it] = [your gpio];
and 
pinMode([your gpio],OUTPUT);
and
sendSensorData([component id dont change it],[replace random with your input sensor it should be int or float]);
now every things are ready compile your code and enjoy it



