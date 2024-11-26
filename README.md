# Revision History

## 2024-11-22
  - To make base MCU SW, Added I2C and UART(for Debuggin) features. Please refer to "I2C_0_ENABLE" macro.

## 2024-11-25
  - Implemented I2C features.
  - Clock source is Changed USED_HSEPLL to USED_HSI due to no X-TAL. //KMS241125_1
  - Changed buffer size of I2C Tx/Rx. //KMS241125_2
  - Added code to break out of the infinite loop. But Need to check this code later !!!//KMS241125_3
  - To fixe Buffer_Init() error, Changed 16bit length for I2C data. //KMS241125_4
