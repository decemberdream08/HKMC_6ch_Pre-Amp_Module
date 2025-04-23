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
  - Changed sending data of Input Source Control from High --> Low/Low --> High for DSP. //KMS241223_1
  - The I2S_OUT2 of DSP has not output. So, we changed register setting again. //KMS241223_2
  
## 2024-12-24
  - I2C I/F Init is moved after Power_Control() due to DSP Init problem and added delay 500ms. //KMS241224_1
  
## 2024-12-25
  - Finished Audio path Configuration including L/R position as our spec. //KMS241225_1
  - Made Mute function of ADAU1761. //KMS250106_2

## 2024-12-30
  - Master A2B transceiver doesn't work due to revision mismatching(actual revision is 0.1). Please refer to "adi_a2b_busconfig.c". //KMS241230_1

## 2025-01-06
  - Changed timing from 100ms to 500ms due to ADAU1452 Init failure. //KMS250106_1
  - Added Mute function of ADAU1761. //KMS250106_2

## 2025-01-09
  - To fix DSP NG issue(DSP doesn't wake-up when Power on. This issue is caused by DSP POR), I changed codes that MCU PA4 output can control DSP RESET in DSP init. //KMS250109_1
  - To avoid stack overflow when I2C function is executed DSP init, we use heap. Need to check starup_A31G22x.s also. //KMS250109_2
  
## 2025-01-10
  - To support TDM8 under A2B Slave mode like NE-N. //KMS250110_1
  
## 2025-01-13
  - Added Dump code for ADAU1452 registers. But some register size should be fixed later. //KMS250113_1
  
## 2025-01-20
  - Changed ADAU1452 init values due to A2B LR Swapping. But It'll be changed after HKMC defines A2B Audio source spec. Please refer to ADAU1452.c/ADAU_1452_Init_Reg.h.
  - Changed ADAU1452 init values due to Aux LR change issue. //KMS250120_1
  
## 2025-02-04
  - Changed ESTec Board doesn't check Device ID and Version of Slave Node's A2B transceiver when ESTec Board works as A2B Master. But Need to Test !!!(NTD). //KMS250204_1
  
## 2025-02-27
  - The PF3/Pin37(12V_CNTRL) is followed by LDO_CNTRL state. //KMS250227_1
  - The PA6/Pin2(A2B_DIRECT) can decide whether A2B Master feature is supportted(Low) or not(High). - High : A2B Master feature disable / Low : A2B Master feature enable. //KMS250227_2
  - The PE1/Pin31(MCLK_SW_CNTR) can choose XTAL-IN of DSP. - High : X-TAL(Aux Mode)  / Low : A2B Tranceiver's MCLK(A2B Mode) //KMS250227_3
  - The PE0/Pin32(I2C_SW_CNTL) can control I2C switch for I2C_0. Output - High : I2C_0 can use DSP & Ext.A2B  / Low : I2C_0 can use ADC & DAC. //KMS250227_4
  
## 2025-02-28
  - During Power-On, we don't need to initialize all peripherals especially in case of ACC-OFF. So, Changed SW. //KMS250228_1
  - The PA0/Pin44(ACC_INT_MICOM) and PA4/Pin48(INPUT_CNTRL) is input and no need internal pull-up. //KMS250228_2
  - Implemented Mute On/Off function. Especially, Mute Off is executed after 1 sec using timer. //KMS250228_3
  - Implemented I2C Slave on I2C_1 Port with Polling way. //KMS250228_4
  
## 2025-03-05
  - Under A2B Mode, DSP uses A2B Receiver's MCLK of as X-TAL In of DSP and Under Aux Mode, DSP uses X-TAL as X-TAL In of DSP. //KMS250305_1
  - Under A2B Mode, Power should be supplied at first time. //KMS250305_2

## 2025-03-06
  - Added delay due to GPIO read error under MCU On start. //KMS250306_1
  - Deleted codes which is related Slave interrupt stop because we need to get continueous message from I2C Master. //KMS250306_2
  - Just check wheter A2B Receiver get Amp data from A2B Master. //KMS250306_3
  
## 2025-03-07
  - Made PF2 to Low(Mute) during initailizing. //KMS250307_1
  
## 2025-03-14
  - To use A2B Bus as Master, we can define Master AD2428 I2C address with (0x68). Now it's 0x68. //KMS250314_1
  - Max buffer size is defined by ADAU1452.c/ADAU1761.c and the size is 1020. //KMS250314_2
  - To support HMC Master A2B Board which checks TI AMP and we already implemented TI AMP response using I2C Slave(I2C_1). Please refer to "HMC_A2B_MASTER_BOARD_SUPPORT" macro. //KMS250314_3
  
## 2025-03-15
  - Changed SW to send STEREO to A2B Slave. //KMS250318_1
  
## 2025-03-20
  - Changed Audio Path to Front R/Rear R under A2B. //KMS250320_1

## 2025-04-03
  - Changed I2C buffer size because we added High Pass Filter to DSP. //KMS250403_1
  - Changed register values because we added High Pass Filter to DSP. //KMS250403_2
  
## 2025-04-09
  - Changed I2C buffer size because we added volume level up under A2B mode. //KMS250409_1
  - Added Volume Up setting under A2B Mode. //KMS250409_2
  
## 2025-04-22
  - Changed condition to check product id only excepting version and Added some code to avoid version check of A2B Transceiver. //KMS250422_1
  - Added A2B Transceiver GPIO Control Code to use MUTE(GPIO6)/STANDBY(GPIO7) for A2B Slave(NE-N) When HKMC PreAmp module is used as A2B Master. //KMS250422_2
  - Changed A2B Out Audio Path from Front R/Rear R to Front R/Front R on Slot 0/1. Please refer to ADAU1452 registers. //KMS250422_3
  
## 2025-04-23
  - Volumed down A2B output for A2B Slave. //KMS250423_1