02/23/2015
This is a simple program to read temperature from lm75a through i2c bus.
Program was design to build on Openwrt Environment but can be easily ported
to other platform.

Example - Publish with Mosquitto

File: publish_temp.sh

#!/bin/ash
while :
do
        mosquitto_pub -h iot.eclipse.org -p 1883 -t project4fun/temp -m "`date` - `./lm75` C"
        sleep 1
done

Example - Subscribe with Mosquitto

mosquitto_sub -h iot.eclipse.org -p 1883 -t project4fun/temp


