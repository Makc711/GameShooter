# GameShooter

It is a shooter game developed in C++. It is realized on STM32F746-DISCOVERY debug board with 4.3" LCD and capacitive touchscreen.

In hardware implemented:
- multi-touchscreen (processing of several touches at a time);
- SDRAM for storing and displaying images on LCD;
- LTDC 24 bits (RGB888);
- I2C for touchscreen operation;
- SDMMC+FatFs for recording saves;
- FreeRTOS.

The software part implements:
- game engine;
- algorithm for finding the path from the enemy to the player;
- algorithm for finding the shortest bullet flight path (taking into account the bounce from obstacles) from the enemy to the player;
- algorithm of defense and evasion of the enemy from the player's bullets flying at him;
- level generator;
- the game level contains bonuses that can be used to improve characteristics (speed, reload time, additional life, invulnerability).
- game menu with the ability to save and load the game, change settings, etc.

![image](https://github.com/Makc711/GameShooter/assets/40514121/cecc871f-a30c-4efd-a970-068539483613)
