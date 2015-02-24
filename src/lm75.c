/*
 * lm75 - Simple program just read out temperature
 *
 * Copyright (C) 2015 Sittisak Sakamornlertsakul <sittisaks@hotmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License v2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
  char rxBuffer[4];  // receive buffer
  char txBuffer[4];  // transmit buffer
  int lm75Address = 0x4f; 
  int opResult = 0;   // keep operation result
  int sign = 1;     // Temperature sign

  // Create a file descriptor for the I2C bus
  int i2cHandle = open("/dev/i2c-0", O_RDWR);
  if(i2cHandle < 0) {
	printf("Error open /dev/i2c-0!!!");
	exit(1);
  }

  // Tell the I2C bus the address of the device 
  // we are going to talk to.
  opResult = ioctl(i2cHandle, I2C_SLAVE, lm75Address);

  // Clear our buffers
  memset(rxBuffer, 0, sizeof(rxBuffer));
  memset(txBuffer, 0, sizeof(txBuffer));

  txBuffer[0] = 0x00; // This is the register 0 (temp) of lm75a we want to read from.
  opResult = write(i2cHandle, txBuffer, 1);
  // Read back the temperture, the data is in word
  if (opResult != 1) printf("No ACK bit!\n");
  opResult = read(i2cHandle, rxBuffer, 2);
  // rxBuffer[0] = MSB, rxBuffer[1] = LSB
  // Bit 7 of rxBuffer[0], if = 1, temp is negative
  // Bit 0-4 of rxBuffer[1] is ignore, therefore we need to shift value by divided by 32
  // Each bit is 0.125 C
  // printf("temp: %x\n", (int)(((rxBuffer[0] & 0xff) * 256) + (rxBuffer[1] & 0xff))); 
  sign = ((rxBuffer[0] & 0x80)!= 0) ? -1 : 1;

  printf("%.3f", sign * (((rxBuffer[0] & 0x7f) * 256) + (rxBuffer[1] & 0xff))/32*0.125); 
  close(i2cHandle);
}
