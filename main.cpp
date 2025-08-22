#include "main.h"
#include "Test_ASYNC_Keypress.h"

//This is my bacgkround colour on twitch
#define TWITCHBG      CLITERAL(Color){ 30, 30, 30, 255 }

//expects 2 sets of vid pid to listen to
int main(int argc, char *argv[]) {
    uint32_t keypress[2];
    const int screenWidth = 521;
    const int screenHeight = 191;
    bool application_focused = false;
    bool debounce_application_focus = false;
    bool application_focus_override = false;
    Sound sound;
    int val;
    int run_every_2_seconds = 60;
    if (argc < 2){
        printf("Requires atleast a twitch channel as input to listen for new messages, extra input is for whitelist applications\r\n");
        return 0;
    }
    //hidecursor(); //Original method was printf
    InitAudioDevice();
    sound = LoadSound("notification.mp3");
    InitWindow(screenWidth, screenHeight, "KeyTracker");
    SetTargetFPS(30);
    load_images();

  if (!init(argv[1])) {
        UnloadSound(sound);
        CloseAudioDevice();
        CloseWindow();
        ender();
        printf("Initialization failed\n"); //note that console window for printf is "blocked" by -mwindows compile flag, can be visible if launched by command prompt
        return 0;
    }
    while (!WindowShouldClose()) {
    //enable or disable whitelist for input
    if (IsKeyDown(KEY_SPACE)){
        if (debounce_application_focus == false){
            debounce_application_focus = true;
            if (application_focus_override == false){
                application_focus_override = true;
            } else {
                application_focus_override = false;
            }
        }
    } else {
        debounce_application_focus = false;
    }
    application_focused = get_keypress_data_only(keypress, argc, argv, application_focus_override);
    BeginDrawing();
    ClearBackground(TWITCHBG);
    DrawTexture(tKeyboard_blank, 0, 0, WHITE);
    if (application_focused == true){
            //there's probably MUCH faster ways to do this but eh
        if (keypress[0]!=0){
            if ((keypress[0] & AKS_MOUSE1)!=0){
                DrawTexture(tMouse1, 0, 0, WHITE);
            }
            if ((keypress[0] & AKS_MOUSE2)!=0){
                DrawTexture(tMouse2, 0, 0, WHITE);
            }
            if ((keypress[0] & AKS_MOUSE3)!=0){
                DrawTexture(tMouse3, 0, 0, WHITE);
            }
            if ((keypress[0] & AKS_MOUSE4)!=0){
                DrawTexture(tMouse4, 0, 0, WHITE);
            }
            if ((keypress[0] & AKS_MOUSE5)!=0){
                DrawTexture(tMouse5, 0, 0, WHITE);
            }
            if ((keypress[0] & AKS_SPACE)!=0){
                DrawTexture(tspacebut, 0, 0, WHITE);
            }
            if ((keypress[0] & AKS_TAB)!=0){
                DrawTexture(ttabbut, 0, 0, WHITE);
            }
            //if ((keypress[0] & AKS_ENTER)!=0){
           // }
            if ((keypress[0] & AKS_SHIFT)!=0){
                DrawTexture(tshiftbut, 0, 0, WHITE);
            }
            if ((keypress[0] & AKS_CTRL)!=0){
                DrawTexture(tctrlbut, 0, 0, WHITE);
            }
            if ((keypress[0] & AKS_ALT)!=0){
                DrawTexture(taltbut, 0, 0, WHITE);
            }
    /* unused keys
            //if ((keypress[0] & AKS_ESC)!=0){
            //}
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
*/
            if ((keypress[0] & AKS_A)!=0){
                DrawTexture(tabut, 0, 0, WHITE);
            }
            if ((keypress[0] & AKS_B)!=0){
                DrawTexture(tbbut, 0, 0, WHITE);
            }
            if ((keypress[0] & AKS_C)!=0){
                DrawTexture(tcbut, 0, 0, WHITE);
            }
            if ((keypress[0] & AKS_D)!=0){
                DrawTexture(tdbut, 0, 0, WHITE);
            }
        }
        if (keypress[1]!=0){
            if ((keypress[1] & AKS_E)!=0){
                DrawTexture(tebut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_F)!=0){
                DrawTexture(tfbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_G)!=0){
                DrawTexture(tgbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_H)!=0){
                DrawTexture(thbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_I)!=0){
                DrawTexture(tibut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_J)!=0){
                DrawTexture(tjbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_K)!=0){
                DrawTexture(tkbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_L)!=0){
                DrawTexture(tlbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_M)!=0){
                DrawTexture(tmbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_N)!=0){
                DrawTexture(tnbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_O)!=0){
                DrawTexture(tobut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_P)!=0){
                DrawTexture(tpbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_Q)!=0){
                DrawTexture(tqbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_R)!=0){
                DrawTexture(trbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_S)!=0){
                DrawTexture(tsbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_T)!=0){
                DrawTexture(ttbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_U)!=0){
                DrawTexture(tubut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_V)!=0){
                DrawTexture(tvbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_W)!=0){
                DrawTexture(twbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_X)!=0){
                DrawTexture(txbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_Y)!=0){
                DrawTexture(tybut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_Z)!=0){
                DrawTexture(tzbut, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_0)!=0){
                DrawTexture(t0but, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_1)!=0){
                DrawTexture(t1but, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_2)!=0){
                DrawTexture(t2but, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_3)!=0){
                DrawTexture(t3but, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_4)!=0){
                DrawTexture(t4but, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_5)!=0){
                DrawTexture(t5but, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_6)!=0){
                DrawTexture(t6but, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_7)!=0){
                DrawTexture(t7but, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_8)!=0){
                DrawTexture(t8but, 0, 0, WHITE);
            }
            if ((keypress[1] & AKS_9)!=0){
                DrawTexture(t9but, 0, 0, WHITE);
            }
        }
         DrawTexture(tKeys, 0, 0, WHITE);
    } else {
        DrawTexture(tKeys, 0, 0, WHITE);
        DrawTexture(tNoFocus, 0, 0, WHITE);
    }
    EndDrawing();
    --run_every_2_seconds;
    if (run_every_2_seconds == 0){
        run_every_2_seconds = 60;
        val = runner();
        if (val == 1) {
            PlaySound(sound);
        } else if (val == 0) {
            break;
        }
    }
    }
    unload_textures();
    UnloadSound(sound);
    CloseAudioDevice();
    CloseWindow();
    ender();
    return 0;
}
