// lab5_jts.c
// adapted from starter code on E155 website
// Joshua Sealand jsealand@hmc.edu
// 13 October 2015
// main plays the song Frosty the Snowman

// Notes for Fur Elise, E155 Lab 5
// Pitch in Hz, duration in ms
const int notes[][2] = {
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	250},
{0,	125},
{494,	125},
{523,	125},
{587,	125},
{659,	375},
{392,	125},
{699,	125},
{659,	125},
{587,	375},
{349,	125},
{659,	125},
{587,	125},
{523,	375},
{330,	125},
{587,	125},
{523,	125},
{494,	250},
{0,	125},
{330,	125},
{659,	125},
{0,	250},
{659,	125},
{1319,	125},
{0,	250},
{623,	125},
{659,	125},
{0,	250},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	500},
{0,	0}};


const int frostyTheSnowman[][2] = {
	{1047,	500},
	{880,	375},
	{932,	125},
	{1047,	250},
	{1397,	500},
	{1319,	125},
	{1397, 	125},
	{1568, 	250},
	{1397,	250},
	{1319,	250},
	{1175,	250},
	{1047, 	750},
	{1319,	125},
	{1397, 	125},
	{1568,	250},
	{1397,	250},
	{1319,	250},
	{1175,	120},
	{0,	10},
	{1175,	120},
	{1047,	250},
	{1397,	250},
	{880,	250},
	{1047,	125},
	{1175,	125},
	{1047,	250},
	{932,	250},
	{880,	250},
	{932,	250},
	{1047,	750},  //end of first phrase
	{0,		250},
	{1047,	500},
	{880,	375},
	{932,	125},
	{1047,	250},
	{1397,	500},
	{1319,	125},
	{1397, 	125},
	{1568, 	250},
	{1397,	250},
	{1319,	250},
	{1175,	250},
	{1047, 	750},
	{1319,	125},
	{1397, 	125},
	{1568,	250},
	{1397,	250},
	{1319,	250},
	{1175,	120},
	{0,	10},
	{1175,	120},
	{1047,	250},
	{1397,	250},
	{880,	250},
	{1047,	125},
	{1175,	125},
	{1047,	250},
	{932,	250},
	{880,	250},
	{784,	250},
	{698,	750},  // end of second phrase
	{0,		250},
	{1175,	245},
	{0, 	10},
	{1175, 245},
	{1397,	245},
	{0, 	10},
	{1397, 245},
	{1319,	250},
	{1175,	250},
	{1047,	250},
	{880,	250},
	{932,	250},
	{1175,	250},
	{1047,	250},
	{932,	250},
	{880,	750},
	{0,		10},
	{880,	240},
	{784,	245},
	{0,		10},
	{784,	245},
	{1047,	245},
	{0,		10},
	{1047,	245},
	{1319,	245},
	{0,		10},
	{1319,	245},
	{1568,	250},
	{0,		10},
	{1568,	120},
	{1319,	120},
	{1568,	250},
	{1397,	250},
	{1319,	250},
	{1175,	250},
	{1047,	1000},
	{0,		250},  //end of middle chorus
	{1047,	500},
	{880,	375},
	{932,	125},
	{1047,	250},
	{1397,	500},
	{1319,	125},
	{1397, 	125},
	{1568, 	250},
	{1397,	250},
	{1319,	250},
	{1175,	250},
	{1047, 	750},
	{1319,	125},
	{1397, 	125},
	{1568,	250},
	{1397,	250},
	{1319,	250},
	{1175,	120},
	{0,	10},
	{1175,	120},
	{1047,	250},
	{1397,	250},
	{880,	250},
	{1047,	125},
	{1175,	125},
	{1047,	250},
	{932,	250},
	{880,	250},
	{784,	250},
	{698,	750},  // end of second phrase repeat
	{0, 	500},
	{1047,	120},
	{0,		5},
	{1047,	120},
	{0,		5},
	{1047,	245},
	{0,		5},
	{1047,	245},
	{0,		5},
	{1047,	245},
	{1175,	125},
	{1047,	120},
	{0,		5},
	{1047,	245},
	{0,		5},
	{1047,	245},
	{0,		5},
	{1047,	245},
	{1175,	250},
	{1047, 	250},
	{880,	250},
	{1047,	250},
	{784,	1000}, //first fast phrase end
	{1047,	120},
	{0,		5},
	{1047,	120},
	{0,		5},
	{1047,	245},
	{0,		5},
	{1047,	245},
	{0,		5},
	{1047,	245},
	{1175,	125},
	{1047,	120},
	{0,		5},
	{1047,	245},
	{0,		5},
	{1047,	245},
	{0,		5},
	{1047,	245},
	{0,		5},
	{1047,	120},
	{0,		5},
	{1047,	120},
	{0,		5},
	{1047,	250},
	{1175,	250},
	{1319,	250},
	{1397,	1000},
	{0,		0}};


#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////

// GPIO FSEL Types
#define INPUT  0
#define OUTPUT 1
#define ALT0   4
#define ALT1   5
#define ALT2   6
#define ALT3   7
#define ALT4   3
#define ALT5   2

#define GPFSEL   ((volatile unsigned int *) (gpio + 0))
#define GPSET    ((volatile unsigned int *) (gpio + 7))
#define GPCLR    ((volatile unsigned int *) (gpio + 10))
#define GPLEV    ((volatile unsigned int *) (gpio + 13))
#define INPUT  0
#define OUTPUT 1

// base address of timer registers
#define SYSTIMER	0x3F003000

// Physical addresses
#define BCM2836_PERI_BASE        0x3F000000
#define GPIO_BASE               (BCM2836_PERI_BASE + 0x200000)
#define BLOCK_SIZE (4*1024)

// Pointer that will be memory mapped when pioInit() is called
volatile unsigned int *gpio; //pointer to base of gpio

// Timer pointer that will be memory mapped when piTimerInit() is called
volatile unsigned int *timer; //pointer to base of timer stuff


void pioInit() {
	int  mem_fd;
	void *reg_map;

	// /dev/mem is a psuedo-driver for accessing memory in the Linux filesystem
	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
	      printf("can't open /dev/mem \n");
	      exit(-1);
	}

	reg_map = mmap(
	  NULL,             //Address at which to start local mapping (null means don't-care)
      BLOCK_SIZE,       //Size of mapped memory block
      PROT_READ|PROT_WRITE,// Enable both reading and writing to the mapped memory
      MAP_SHARED,       // This program does not have exclusive access to this memory
      mem_fd,           // Map to /dev/mem
      GPIO_BASE);       // Offset to GPIO peripheral

	if (reg_map == MAP_FAILED) {
      printf("gpio mmap error %d\n", (int)reg_map);
      close(mem_fd);
      exit(-1);
    }

	gpio = (volatile unsigned *)reg_map;
}

void piTimerInit() {
	int  mem_fd;
	void *reg_map;

	// /dev/mem is a psuedo-driver for accessing memory in the Linux filesystem
	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
	      printf("can't open /dev/mem \n");
	      exit(-1);
	}

	reg_map = mmap(
	  NULL,             //Address at which to start local mapping (null means don't-care)
      BLOCK_SIZE,       //Size of mapped memory block
      PROT_READ|PROT_WRITE,// Enable both reading and writing to the mapped memory
      MAP_SHARED,       // This program does not have exclusive access to this memory
      mem_fd,           // Map to /dev/mem
      SYSTIMER);       // Offset to timer address

	if (reg_map == MAP_FAILED) {
      printf("gpio mmap error %d\n", (int)reg_map);
      close(mem_fd);
      exit(-1);
    }

	timer = (volatile unsigned *)reg_map;
}

// pinMode sets a pin to be an INPUT, OUTPUT, or other state
void pinMode(int pin, int state) {
	unsigned int offset = pin/10;
	unsigned int shift = (pin % 10) * 3;
	GPFSEL[offset] &= ~(7 << shift);
	GPFSEL[offset] |= (state << shift);
}

// digitalWrite writes a 0 or 1 to the passed in pin
void digitalWrite(int pin, int val) {
	unsigned int set = (pin < 32) ? 7 : 8;
	unsigned int clr = (pin < 32) ? 10 : 11;
	if (val == 1)
		gpio[set] = 1 << (pin % 32);
	else
		gpio[clr] = 1 << (pin % 32);
}

// digitalRead reads in a digital value from the passed in pin
int digitalRead(int pin) {
	int out;
	if (pin < 32)
		out = (GPLEV[0] >> pin) && 1;
	else
		out = (GPLEV[1] >> (pin - 32)) && 1;
	return out;
}

// delayMicros delays for micros microseconds
void delayMicros(int micros) {
	timer[4] = timer[1] + micros;
	timer[0] = 0b0010;
	while (!(timer[0] & 0b0010));
}

// playNote plays a note at the desired frequency for the desired duration
void playNote(int freq, int durationInMillis) {
	if (freq == 0) {
		delayMicros(durationInMillis * 1000);
	}
	else {
		int halfperiod = 1000000 / freq / 2;
		int counter = 0;
		int end = durationInMillis * 1000 / halfperiod;
		int val = 0;
		while (counter < end) {
			digitalWrite(23, val);
			delayMicros(halfperiod);
			val = (val ==  0) ? 1 : 0;
			counter++;
		}
	}
}

// playSong steps through an array of notes/durations and plays them all
void playSong() {
	int counter = 0;
	int note[2];
	note[0] = frostyTheSnowman[counter][0];
	note[1] = frostyTheSnowman[counter][1];
	while ( (note[0] > 0) | (note[1] > 0) ) {
		playNote(note[0], note[1]);
		counter++;
		note[0] = frostyTheSnowman[counter][0];
		note[1] = frostyTheSnowman[counter][1];
	}
	printf("Song is over\n");
}

// testSong 
void testSong() {
	while (1) {
		playNote(500, 1000);
		playNote(300, 1000);
	}
}

// set up the gpio and timer pointers
// initialize pin 23 as an output
// play the song
void main() {
	piTimerInit();
	pioInit();
	pinMode(23, OUTPUT);
	playSong();
}

