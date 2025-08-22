#ifndef TEST_ASYNC_KEYPRESS_H_INCLUDED
#define TEST_ASYNC_KEYPRESS_H_INCLUDED

#define AKS_MOUSE1  0x1
#define AKS_MOUSE2  0x2
#define AKS_MOUSE3  0x4
#define AKS_MOUSE4  0x8
#define AKS_MOUSE5  0x10
#define AKS_SPACE   0x20
#define AKS_TAB     0x40
#define AKS_ENTER   0x80
#define AKS_SHIFT   0x100
#define AKS_CTRL    0x200
#define AKS_ALT     0x400
#define AKS_ESC     0x800
#define AKS_F1      0x1000
#define AKS_F2      0x2000
#define AKS_F3      0x4000
#define AKS_F4      0x8000
#define AKS_F5      0x10000
#define AKS_F6      0x20000
#define AKS_F7      0x40000
#define AKS_F8      0x80000
#define AKS_F9      0x100000
#define AKS_F10     0x200000
#define AKS_F11     0x400000
#define AKS_F12     0x800000
#define AKS_LEFT    0x1000000
#define AKS_UP      0x2000000
#define AKS_RIGHT   0x4000000
#define AKS_DOWN    0x8000000
#define AKS_A       0x10000000
#define AKS_B       0x20000000
#define AKS_C       0x40000000
#define AKS_D       0x80000000

#define AKS_E       0x1
#define AKS_F       0x2
#define AKS_G       0x4
#define AKS_H       0x8
#define AKS_I       0x10
#define AKS_J       0x20
#define AKS_K       0x40
#define AKS_L       0x80
#define AKS_M       0x100
#define AKS_N       0x200
#define AKS_O       0x400
#define AKS_P       0x800
#define AKS_Q       0x1000
#define AKS_R       0x2000
#define AKS_S       0x4000
#define AKS_T       0x8000
#define AKS_U       0x10000
#define AKS_V       0x20000
#define AKS_W       0x40000
#define AKS_X       0x80000
#define AKS_Y       0x100000
#define AKS_Z       0x200000
#define AKS_0       0x400000
#define AKS_1       0x800000
#define AKS_2       0x1000000
#define AKS_3       0x2000000
#define AKS_4       0x4000000
#define AKS_5       0x8000000
#define AKS_6       0x10000000
#define AKS_7       0x20000000
#define AKS_8       0x40000000
#define AKS_9       0x80000000

void get_keypress(uint32_t *out, char *buffer, char *buffer2, char *buffer3, int argc, char *argv[]);

bool get_keypress_data_only(uint32_t *out, int argc, char *argv[], bool whitelist_override);

void hidecursor();

bool init(char * twitch_name);
int runner();
void ender();

#endif // TEST_ASYNC_KEYPRESS_H_INCLUDED
