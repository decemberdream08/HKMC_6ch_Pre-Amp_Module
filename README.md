# Revision History

## 2024-11-22
  - To make base MCU SW, Added I2C and UART(for Debuggin) features. Please refer to "I2C_0_ENABLE" macro.

## 2024-11-25
  - Implemented I2C features.
  - Clock source is Changed USED_HSEPLL to USED_HSI due to no X-TAL. //KMS241125_1
  - Changed buffer size of I2C Tx/Rx. //KMS241125_2
  - Added code to break out of the infinite loop. But Need to check this code later !!!//KMS241125_3
  - To fixe Buffer_Init() error, Changed 16bit length for I2C data. //KMS241125_4
  
## 2024-11-26
  - Added ADAU1452(DSP) code. //KMS241126_1
  - I2C read function(HAL_I2C_MasterReceiveData()) has some problem which can't not read data. so I fixed it. //KMS241126_2
  - Added GPIO code. //KMS241126_3

## 2024-11-27
  - Made test codes for veryfing the functions with MCU EVK. //KMS241127_1
  - Implemented GPIO function by product spec. //KMS241127_2
  - Enabled _TIMER2n to use TIMER20/21. //KMS241127_3
  - Added TIMER20 code. This is timer for ACC OFF delay. //KMS241127_4
  - Added TIMER21 code. This is just continueous tick. //KMS241127_5

## 2024-11-28
  - Implemented DEEP-SLEEP mode. //KMS241128_1
  
## 2024-11-29
  - Implemented MCU reset after wake-up from Deep-sleep.//KMS241129_1
  - Implemented lowest power consumption under MCU deep-sleep mode. //KMS241129_2
  - To avoid mismatching between ACC ON pin and Deep-Sleep Mode, Need to check whether ACC Off or ACC On again before MCU goes deep-sleep mode. //KMS241129_3
  - To merge A2B Stack, we use "ESTEC_A2B_STACK_PORTING" define. //KMS241129_4

## 2024-12-02
  - To reduce RAM size, we need to modify original ADAU1452_init_Reg.h and ADAU1452.c like below. //KMS241202_1
  - To reduce RAM size, we need to modify original ADAU1761_init_Reg.h and ADAU1761.c like below. //KMS241202_2
  - To reduce RAM size, we need to use A2B BCF COMPRESSED. //KMS241202_3

## 2024-12-03
  - A2B_BCF_FROM_FILE_IO define is not used with ADI_SIGMASTUDIO_BCF at once. //KMS241203_1
  
## 2024-12-06
  - A2B I2C speed is fixed 400K in A2B and MCU both sides. //KMS241206_1
  
## 2024-12-10
  - To commnunicate with A2B Bus through I2C. //KMS241210_1
  - SCL_TIMEOUT define makes A2B i2c communication error when master try to init peripheral of slave node. //KMS241210_2
  - I2C_MANUAL_BUS_CONTROL define is not used. //KMS241210_3

## 2024-12-11
  - To make A2B Stack code as module code. So we can remove A2B Stack without disabling "A2B_STACK_CODE_FROM_ADI". //KMS241211_1
  - To share I2C function for I2C_0 & I2C_1, it's changed I2C related functions as the following. //KMS241211_2

## 2024-12-13
  - To share ADAU1761 init with each same devices which have jsut different Device Address. //KMS241213_1
  - To implement Input Source Selection, I added some functions and used GPIO. Sometime, we need to define "INTPUT_SOURCE_SELECTION_UPON_POWER_ON". //KMS241213_2
  - Just check one time upon power on if "INTPUT_SOURCE_SELECTION_UPON_POWER_ON" is defined but it checks current status with intterrupt and upon Power On if "INTPUT_SOURCE_SELECTION_UPON_POWER_ON" is not defined. //KMS241213_3

## 2024-12-19
  - Need to move Power_Control() because power should be supplied before DSP/Audio Codec init. //KMS241219_1
  
## 2024-12-20
  - Added SYSTEM TICK Timer instead of TIMER21. //KMS241220_1
  - Changed INPUT_CNTRL_OUT pin from Open-Drain to Push-pull and GPIO_Configure() due to wrong information. //KMS241220_2
  
## 2024-12-23
  - Chnaged sending data of Input Source Control from High --> Low/Low --> High for DSP. //KMS241223_1
  - The I2S_OUT2 of DSP has not output. So, we changed register setting again. //KMS241223_2