#If not specified target, all cmd will be used for executing dining file first 
#all->conventional target name, not a special keyword
Maksud_BOSS=gcc

all: dining   #dining->dependency 


#When executing dining file, these mentioned files will (not) be executed one by one
#dependencies -> 3 files   
#dining is now target
dining: main.c functions.c dining.h
	$(Maksud_BOSS) main.c functions.c -o dining


#cmd: make clean -> the dining.exe file will be vanished
clean:
	rm -f dining dining.exe