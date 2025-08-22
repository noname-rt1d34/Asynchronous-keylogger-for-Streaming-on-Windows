#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED



#include "raylib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "CSV_Asset_Loader.h"
#include "Test_ASYNC_Keypress.h"

extern uint32_t screen[2];
extern uint8_t RGBA[4];
extern char directory[255];
extern uint8_t programs_tocheck;
extern char programs[32][255];
extern uint32_t assets_loaded[3];



#endif // MAIN_H_INCLUDED
