# Sistema de riego automático

Características técnicas del proyecto: 
 - IDE utilizado: IAR
 - Desarrollado en Baremetal.
 - Microcontrolador utilizado: stm32f103c8t6.
 - Librería utilizada:STM32F10x_StdPeriph_Lib_V3.5.0.

Funciones implementadas hasta el momento:
- Base de tiempo con Systick de 1ms.
- Módulo de gestión de timers implementado sobre la base de tiempo del Systick.
- Módulo de gestión del led loco.
- Módulo de gestión de lectura de 3 canales del ADC1 con DMA canal 1.
