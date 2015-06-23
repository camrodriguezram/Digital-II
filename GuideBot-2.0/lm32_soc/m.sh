#!/bin/bash
SI="y"
VARIABLE="compilar"
##Sintetizar boot0-serial

while [ "$VARIABLE" ]; do


echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
echo ~~~~~~~~~~~~~ Synthesize program and LM32~~~~~~~~~~~~~~~
echo ~~~~~~~~~~~~~~~~ Author: Carlos Gil ~~~~~~~~~~~~~~~~~~~~
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


echo ========================================================
echo !------------------------------------------------------!
echo !++++++++++++++ CREATING IMAGE imagen.ram +++++++++++++!
echo !------------------------------------------------------!
echo ========================================================

cd ~/Desktop/SemestreVII/DEII/LM32COMPILER/lm32_soc/firmware/boot0-serial
##cd ~/Desktop/SemestreVII/DEII/lmprofe/lm32_soc/firmware/hw-test
make clean
make

	echo  Compile again? y o n
	read COMPILE
	if [ "$COMPILE" == "$SI" ]; then
		clear
	else
		break
	fi
done

	
	
	echo ========================================================
	echo !------------------------------------------------------!
	echo !++++++++++++++++++ IMAGE CREATED +++++++++++++++++++++!
	echo !------------------------------------------------------!
	echo ========================================================
	
	
	## Sintetizar LM32
	echo ========================================================
	echo !------------------------------------------------------!
	echo !+++++++++ SYNTHESIZING LM32, CREATING .bit +++++++++++!
	echo !------------------------------------------------------!
	echo ========================================================
	
	cd ~/Desktop/SemestreVII/DEII/LM32COMPILER/lm32_soc/ 
	make clean
	make 
	make syn
	
	echo ========================================================
	echo !------------------------------------------------------!
	echo !+++++++++++++++++ LM32 SYNTHESIZED +++++++++++++++++++!
	echo !------------------------------------------------------!
	echo ========================================================
	
	#Programar la FPGA
	echo ========================================================
	echo !------------------------------------------------------!
	echo !+++++++++++++++++ PROGRAMMING FPGA +++++++++++++++++++!
	echo !------------------------------------------------------!
	echo ========================================================


	#djtgcfg enum; 
	#djtgcfg init -d Nexys4; 
	#djtgcfg prog  -d Nexys4 -i 0 -f ~/Desktop/SemestreVII/DEII/lmprofe/lm32_soc/system.bit
	
	cp ~/Desktop/SemestreVII/DEII/LM32COMPILER/lm32_soc/system.bit //media/user/KINGSTON

	echo ========================================================
	echo !------------------------------------------------------!
	echo !++++++++++++++++++ FPGA PROGRAMMED +++++++++++++++++++!
	echo !------------------------------------------------------!
	echo ========================================================
	
exit 0







