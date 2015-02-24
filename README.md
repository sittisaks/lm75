02/23/2015
This is a simple program to read temperature from lm75a through i2c bus.
Program was design to build on Openwrt Environment but can be easily ported
to other platform.

Example - Publish with Mosquitto

File: publish_temp.sh
<blockquote>
#!/bin/ash<p>
while :<p>
do<p>
        mosquitto_pub -h iot.eclipse.org -p 1883 -t project4fun/temp -m "`date` - `./lm75` C"<p>
        sleep 1<p>
done<p>
</blockquote>
Example - Subscribe with Mosquitto

mosquitto_sub -h iot.eclipse.org -p 1883 -t project4fun/temp


