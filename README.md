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
  - Made test codes for veryfing the functions with MCU EVK. //KMS241126_1
  - Implemented GPIO function by product spec. //KMS241127_2
  - Enabled _TIMER2n to use TIMER20/21. //KMS241127_3
  - Added TIMER20 code. This is timeer for ACC OFF delay. //KMS241127_4
  - Added TIMER21 code. This is just continueous tick. //KMS241127_5