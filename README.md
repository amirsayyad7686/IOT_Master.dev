# IOT_Master.dev https://iot-master.dev/  
Dynamic

![pngwing com(2)zxc](https://github.com/amirsayyad7686/IOT_Master.dev/assets/78236642/1d2806a5-7e5e-4d71-9972-32f0bdffa96e)

This platform offers a wide range of features for junior developers to create their own plans and designs in IoT. It's a full-time responsibility with no limits, and it's designed to be open-source with real-time capabilities.

Anyone can join my IoT Masters colony, create their plans with a user-friendly GUI, and control their controllers (such as ESP modules and NodeMCU) with code that I've prepared for them. Setting up and compiling is a breeze, requiring just one click.

This website is highly secure and lightning-fast. You'll appreciate it after just one experience! I'm eager to hear your feedback.
> [!NOTE]
> Domain: iot-master.dev & iot-master.ir

How to get started?

Step 1 (Registration): Register for free on iot-master.dev. Afterward, you'll have access to your IoT dashboard.

Step 2 (Set up a node): Define a node, such as your module (NodeMCU or ESP32), and enter your WiFi configuration, including SSID and password. Choose a name for your node.

link:
https://iot-master.dev/iot-panel/component-designer

Step 3 (Set up components): Configure the components on your node, such as toggle buttons, push buttons, sensors, and sliders.

Step 4 (Generate Code): Visit the component table page and click on the "Generate Code" button to obtain code for your selected node with all the components you set up earlier. It will be sent to your email. Your code includes three files: static.h, static.cpp, and IOT_Master.ino. These three files should remain together in a folder and be compiled together. The only necessary modification to the code is selecting your desired GPIO in:
`gpioMappings[<component id don't change it>] = {your gpio};`

Also, use:
`pinMode({your gpio}, OUTPUT);`

And:
`sendSensorData(<component id don't change it>, <replace 'random' with your input sensor; it should be an int>);`

link:
https://iot-master.dev/iot-panel/component-table

Now everything is ready; compile your code and enjoy it!

I hope this helps. If you have any further questions or need additional assistance, please feel free to ask.


## Keywords:

for OUTPUT ,PWM or Digital

`gpioMappings[<component id don't change it>] = {your gpio};`
for INPUT , Sensors or any type of int,float

`sendSensorData(<component id don't change it>, <replace 'random' with your input sensor; it should be an int>);`

> [!IMPORTANT]
> also dont change or delete this loop :
> `IOT_Master();//main iot master loop`

> [!WARNING]
> dont change sensor condition timer (if (now - sensor > 10000){}) it may make your panel slower or disconnect 

## Dashboard sample:

![asd](https://github.com/amirsayyad7686/IOT_Master.dev/assets/78236642/b32050aa-171b-4e6a-b44b-0676ed642f2c)


## Web Serial API:

new experiance with serial monitor with IOT_Master web serial API :

the variable from incoming data from web serial is `webSerialData` with as string type and also you can send your desire data to web serial monitor with this function `webSerial("String")` you should pass string argument as data to this function

![aa](https://github.com/amirsayyad7686/IOT_Master.dev/assets/78236642/9318ce87-90d7-4b33-93d2-f3972f8ae22e)

Also you can check web serial example 



