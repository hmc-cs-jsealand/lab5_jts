// lab5_starter.c // Notes for Fur Elise, E155 Lab 5

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

#define SYSTIMER	((volatile unsigned int *) (0x3F003000))

// Physical addresses
#define BCM2836_PERI_BASE        0x3F000000
#define GPIO_BASE               (BCM2836_PERI_BASE + 0x200000)
#define BLOCK_SIZE (4*1024)

// Pointers that will be memory mapped when pioInit() is called
volatile unsigned int *gpio; //pointer to base of gpio


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

int digitalRead(int pin) {
	int out;
	if (pin < 32)
		out = (GPLEV[0] >> pin) && 1;
	else
		out = (GPLEV[1] >> (pin - 32)) && 1;
	return out;
}
void delayMicros(int micros) {
	SYSTIMER[4] = SYSTIMER[1] + micros;
	SYSTIMER[0] = 0b0010;
	while (!(SYSTIMER[0] & 0b0010));
}

void playNote(int freq, int duration) {
	int period = 1000000 / freq;
	int val = 0;
	SYSTIMER[5] = SYSTIMER[1] + duration;
	SYSTIMER[0] = 0b0100;
	while (!(SYSTIMER[0] & 0b0100)) {
		digitalWrite(23, val);
		delayMicros(duration);
		val = (val ==  0) ? 1 : 0;
	}
}


void playSong() {
	int counter = 0;
	int note[2];
	note[0] = notes[counter][0];
	note[1] = notes[counter][1];
	while (note[0] != 0 & note[1] != 0) {
		note[0] = notes[counter][0];
		note[1] = notes[counter][1];
		playNote(note[0], note[1]);
		counter++;
	}
}

void testSong() {
	while (1) {
		digitalWrite(23, 1);
		delayMicros(1000000);
		digitalWrite(23, 0);
		delayMicros(1000000);
	}
}

void main() {
	pioInit();
	pinMode(23, OUTPUT);
	testSong();
}
