#include <stdio.h>		//Input and output
#include <unistd.h>		// getopt
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DEVICE_PATH "/sys/class/power_supply/BAT0/"

int readValueFromFile(char *path);
float getEnergyLevel(char *devicePath);

int main(int argc, char *argv[]) {
	
	printf("%f", getEnergyLevel(DEVICE_PATH));
	
	return 0;
}

float getEnergyLevel(char *devicePath) {

	char filePath[80];
	
	strcpy(filePath, devicePath);
	strcat(filePath, "energy_full");
	
	int energyFull = readValueFromFile(filePath);
	
	filePath[0] = 0;
	
	strcpy(filePath, devicePath);
	strcat(filePath, "energy_now");
	
	int energyNow = readValueFromFile(filePath);
	
	return ((float) energyNow / (float) energyFull);
	
}

int readValueFromFile(char *path) {

	FILE *fp;
	int value; 
	
	fp = fopen(path, "r");
	
	if(fp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n", path);
		exit(0);
	}
	
	fscanf(fp, "%d", &value);	
	
	return value;
}
