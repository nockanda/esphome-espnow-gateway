# esphome-espnow-gateway
How to communicate with multiple boards from esphome to espnow
![234234](https://user-images.githubusercontent.com/106683637/175523467-72848d07-ff06-4147-8b92-4cc75289d35b.PNG)

1. Upload nockanda_espnow.h to ESPHOME!
2. Register the board in ESPHOME, edit the contents of the espnow_gateway.yaml file to suit yourself, and upload it!
3. Prepare one more board and upload espnow_node1.ino!
4. At this time, you must change the mac address of the gateway in the file to your own!
5. Upload the software the same way for both boards!
6. Upload virtual temperature and humidity sensor measurements to Home Assistant!
7. Press a button in Home Assistant to turn the board's built-in LED on or off!
