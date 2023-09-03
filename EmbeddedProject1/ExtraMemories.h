#pragma once

//E.g. void SDRAM_TEXT func();
#define SDRAM_TEXT __attribute__((section(".sdram_text")))

//E.g. int SDRAM_DATA g_Initialized = 1;
#define SDRAM_DATA __attribute__((section(".sdram_data")))

//E.g. int SDRAM_BSS g_Uninitialized;
#define SDRAM_BSS __attribute__((section(".sdram_bss")))


