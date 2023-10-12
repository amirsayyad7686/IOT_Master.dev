# IOT_Master.dev

![pngwing com(2)zxc](https://github.com/amirsayyad7686/IOT_Master.dev/assets/78236642/1d2806a5-7e5e-4d71-9972-32f0bdffa96e)

This platform offers a wide range of features for junior developers to create their own plans and designs in IoT. It's a full-time responsibility with no limits, and it's designed to be open-source with real-time capabilities.

Anyone can join my IoT Masters colony, create their plans with a user-friendly GUI, and control their controllers (such as ESP modules and NodeMCU) with code that I've prepared for them. Setting up and compiling is a breeze, requiring just one click.

This website is highly secure and lightning-fast. You'll appreciate it after just one experience! I'm eager to hear your feedback.

Domain: iot-master.dev & iot-master.ir

How to get started?

Step 1 (Registration): Register for free on iot-master.dev. Afterward, you'll have access to your IoT dashboard.

Step 2 (Set up a node): Define a node, such as your module (NodeMCU or ESP32), and enter your WiFi configuration, including SSID and password. Choose a name for your node.

Step 3 (Set up components): Configure the components on your node, such as toggle buttons, push buttons, sensors, and sliders.

Step 4 (Generate Code): Visit the component table page and click on the "Generate Code" button to obtain code for your selected node with all the components you set up earlier. It will be sent to your email. Your code includes three files: static.h, static.cpp, and IOT_Master.ino. These three files should remain together in a folder and be compiled together. The only necessary modification to the code is selecting your desired GPIO in:
gpioMappings[component id don't change it] = [your GPIO];

Also, use:
pinMode([your GPIO], OUTPUT);

And:
sendSensorData([component id don't change it], [replace 'random' with your input sensor; it should be an int or float]);

Now everything is ready; compile your code and enjoy it!

I hope this helps. If you have any further questions or need additional assistance, please feel free to ask.





