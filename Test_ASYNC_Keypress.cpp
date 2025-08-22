#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <psapi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Test_ASYNC_Keypress.h"

#pragma comment(lib, "ws2_32.lib")

static WSADATA wsaData;
static struct addrinfo hints, *result = NULL;
static SOCKET sock;
static char recvBuffer[4096] = "";
static char buffer[1024];

bool init(char * twitch_name){
    u_long mode = 1;
    char join[256] = {0};
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSA startup failed: %d\n", WSAGetLastError());
        return false;
    }

    // Resolve hostname
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo("irc.chat.twitch.tv", "6667", &hints, &result) != 0) {
        printf("getaddrinfo failed.\n");
        WSACleanup();
        return false;
    }

    // Create socket
    sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sock == INVALID_SOCKET) {
        printf("socket failed: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    // Connect to server
    if (connect(sock, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        printf("connect failed: %d\n", WSAGetLastError());
        closesocket(sock);
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    // Set socket to non-blocking
    if (ioctlsocket(sock, FIONBIO, &mode) != NO_ERROR) {
        printf("ioctlsocket failed.\n");
        closesocket(sock);
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    // Send authentication for anonymous access, Grok provided the pass and nick values
    const char* pass = "PASS blah\r\n";
    const char* nick = "NICK justinfan12345\r\n";
    //const char* join = "JOIN #mychannel\r\n";  //Replace with your twitch channel's name, made it dynamic for ease of use
    snprintf(join, sizeof(join), "JOIN #%s\r\n", twitch_name);

    send(sock, pass, strlen(pass), 0);
    send(sock, nick, strlen(nick), 0);
    send(sock, join, strlen(join), 0);
    freeaddrinfo(result);
    return true;
}

//Twitch chat IRC for read only, thanks Grok! Didn't know this was a thing
int runner() {
    // Receive data non-blocking
    int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        strncat(recvBuffer, buffer, sizeof(recvBuffer) - strlen(recvBuffer) - 1);

        // Process complete lines
        char* pos;
        while ((pos = strstr(recvBuffer, "\r\n")) != NULL) {
            *pos = '\0';
            char* line = recvBuffer;

            // Handle PING
            if (strncmp(line, "PING", 4) == 0) {
                char pong[256];
                snprintf(pong, sizeof(pong), "PONG%s\r\n", line + 4);
                send(sock, pong, strlen(pong), 0);
            }

            // Detect new chat message
            if (strstr(line, "PRIVMSG") != NULL) {
                printf("Chat message: %s\n", line);
                memmove(recvBuffer, pos + 2, strlen(pos + 2) + 1);
                return 1;  // Signal new message
            }

            // Move remaining data
            memmove(recvBuffer, pos + 2, strlen(pos + 2) + 1);
        }
    } else if (bytes == SOCKET_ERROR) {
        int err = WSAGetLastError();
        if (err != WSAEWOULDBLOCK) {
            printf("recv failed: %d\n", err);
            return 0;
        }
    }
    return 2;
}

void ender() {
    closesocket(sock);
    WSACleanup();
}

/* unused old method
void hidecursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100; // Set cursor size (1 to 100)
    info.bVisible = FALSE; // Set cursor visibility to FALSE (hidden)
    SetConsoleCursorInfo(consoleHandle, &info);
}
*/

// Function to get the executable name of the foreground window
BOOL GetForegroundProcessName(char* processName, DWORD size) {
    HWND hwnd = GetForegroundWindow();
    if (hwnd == NULL) return FALSE;

    DWORD processId;
    GetWindowThreadProcessId(hwnd, &processId);

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId);
    if (hProcess == NULL) return FALSE;

    BOOL result = GetProcessImageFileNameA(hProcess, processName, size);
    CloseHandle(hProcess);
    if (result) {
        char* lastBackslash = strrchr(processName, '\\');
        if (lastBackslash) {
            memmove(processName, lastBackslash + 1, strlen(lastBackslash));
        }
    }
    return result;
}

// Function to check if the target process is in focus
BOOL IsTargetProcessFocused( int argc, char *argv[]) {
    char processName[MAX_PATH];
    int temp = 1;
    if (GetForegroundProcessName(processName, MAX_PATH)) {
        while (temp < argc){
            if (strstr(processName, argv[temp]) != NULL) {
                return TRUE;
            }
            ++temp;
        }
    }
    return FALSE;
}

bool get_keypress_data_only(uint32_t *out, int argc, char *argv[], bool whitelist_override){
if (IsTargetProcessFocused(argc,argv) == true || whitelist_override == true) {
    out[0] = 0;
    if (GetAsyncKeyState(1) & 0x8000){//left click
        out[0] |= AKS_MOUSE1; //out[0] |= 1;
    }
    if (GetAsyncKeyState(2) & 0x8000){//right click
        out[0] |= AKS_MOUSE2;
    }
    if (GetAsyncKeyState(4) & 0x8000){//middle mouse click
        out[0] |= AKS_MOUSE3;
    }
    if (GetAsyncKeyState(5) & 0x8000){//side mouse click
        out[0] |= AKS_MOUSE4;
    }
    if (GetAsyncKeyState(6) & 0x8000){//side mouse2 click
        out[0] |= AKS_MOUSE5;
    }
    if (GetAsyncKeyState(32) & 0x8000){//32=space,8=backspace
        out[0] |= AKS_SPACE;
    }
    if (GetAsyncKeyState(9) & 0x8000){//tab
       // printf("TAB ");
        out[0] |= AKS_TAB;
    }
    if (GetAsyncKeyState(13) & 0x8000){//enter
        //printf("ENTER ");
        out[0] |= AKS_ENTER;
    }
    if (GetAsyncKeyState(16) & 0x8000){//shift
        //printf("SHIFT ");
        out[0] |= AKS_SHIFT;
    }
    if (GetAsyncKeyState(17) & 0x8000){//ctrl
        //printf("CTRL ");
        out[0] |= AKS_CTRL;
    }
    if (GetAsyncKeyState(18) & 0x8000){//alt
      //  printf("ALT ");
        out[0] |= AKS_ALT;
    }
    if (GetAsyncKeyState(27) & 0x8000){//escape
       // printf("ESC ");
        out[0] |= AKS_ESC;
    }
    if (GetAsyncKeyState(112) & 0x8000){//f1
        //printf("F1 ");
        out[0] |= AKS_F1;
    }
    if (GetAsyncKeyState(113) & 0x8000){//f2
        //printf("F2 ");
        out[0] |= AKS_F2;
    }
    if (GetAsyncKeyState(114) & 0x8000){//f3
        //printf("F3 ");
        out[0] |= AKS_F3;
    }
    if (GetAsyncKeyState(115) & 0x8000){//f4
        //printf("F4 ");
        out[0] |= AKS_F4;
    }
    if (GetAsyncKeyState(116) & 0x8000){//f5
        //printf("F5 ");
        out[0] |= AKS_F5;
    }
    if (GetAsyncKeyState(117) & 0x8000){//f6
        //printf("F6 ");
        out[0] |= AKS_F6;
    }
    if (GetAsyncKeyState(118) & 0x8000){//f7
        //printf("F7 ");
        out[0] |= AKS_F7;
    }
    if (GetAsyncKeyState(119) & 0x8000){//f8
        //printf("F8 ");
        out[0] |= AKS_F8;
    }
    if (GetAsyncKeyState(120) & 0x8000){//f9
        //printf("F9 ");
        out[0] |= AKS_F9;
    }
    if (GetAsyncKeyState(121) & 0x8000){//f10
        //printf("F10 ");
        out[0] |= AKS_F10;
    }
    if (GetAsyncKeyState(122) & 0x8000){//f11
        //printf("F11 ");
        out[0] |= AKS_F11;
    }
    if (GetAsyncKeyState(123) & 0x8000){//f12
        //printf("F12 ");
        out[0] |= AKS_F12;
    }
    if (GetAsyncKeyState(37) & 0x8000){//left arrow
        out[0] |= AKS_LEFT;
    }
    if (GetAsyncKeyState(38) & 0x8000){//up arrow
        out[0] |= AKS_UP;
    }
    if (GetAsyncKeyState(39) & 0x8000){//right arrow
        out[0] |= AKS_RIGHT;
    }
    if (GetAsyncKeyState(40) & 0x8000){//down arrow
        out[0] |= AKS_DOWN;
    }
    if (GetAsyncKeyState(65) & 0x8000){//a
        //printf("A ");
        out[0] |= AKS_A;
    }
    if (GetAsyncKeyState(66) & 0x8000){//b
        //printf("B ");
        out[0] |= AKS_B;
    }
    if (GetAsyncKeyState(67) & 0x8000){//c
        //printf("C ");
        out[0] |= AKS_C;
    }
    if (GetAsyncKeyState(68) & 0x8000){//d
        //printf("D ");
        out[0] |= AKS_D;
    }

    out[1] = 0;
    if (GetAsyncKeyState(69) & 0x8000){//e
        //printf("E ");
        out[1] |= AKS_E;
    }
    if (GetAsyncKeyState(70) & 0x8000){//f
        //printf("F ");
        out[1] |= AKS_F;
    }
    if (GetAsyncKeyState(71) & 0x8000){//g
        //printf("G ");
        out[1] |= AKS_G;
    }
    if (GetAsyncKeyState(72) & 0x8000){//h
        //printf("H ");
        out[1] |= AKS_H;
    }
    if (GetAsyncKeyState(73) & 0x8000){//i
        //printf("I ");
        out[1] |= AKS_I;
    }
    if (GetAsyncKeyState(74) & 0x8000){//j
        //printf("J ");
        out[1] |= AKS_J;
    }
    if (GetAsyncKeyState(75) & 0x8000){//k
        //printf("K ");
        out[1] |= AKS_K;
    }
    if (GetAsyncKeyState(76) & 0x8000){//l
        //printf("L ");
        out[1] |= AKS_L;
    }
    if (GetAsyncKeyState(77) & 0x8000){//m
        //printf("M ");
        out[1] |= AKS_M;
    }
    if (GetAsyncKeyState(78) & 0x8000){//n
        //printf("N ");
        out[1] |= AKS_N;
    }
    if (GetAsyncKeyState(79) & 0x8000){//o
        //printf("O ");
        out[1] |= AKS_O;
    }
    if (GetAsyncKeyState(80) & 0x8000){//p
        //printf("P ");
        out[1] |= AKS_P;
    }
    if (GetAsyncKeyState(81) & 0x8000){//q
        //printf("Q ");
        out[1] |= AKS_Q;
    }
    if (GetAsyncKeyState(82) & 0x8000){//r
        //printf("R ");
        out[1] |= AKS_R;
    }
    if (GetAsyncKeyState(83) & 0x8000){//s
        //printf("S ");
        out[1] |= AKS_S;
    }
    if (GetAsyncKeyState(84) & 0x8000){//t
        //printf("T ");
        out[1] |= AKS_T;
    }
    if (GetAsyncKeyState(85) & 0x8000){//u
        //printf("U ");
        out[1] |= AKS_U;
    }
    if (GetAsyncKeyState(86) & 0x8000){//v
        //printf("V ");
        out[1] |= AKS_V;
    }
    if (GetAsyncKeyState(87) & 0x8000){//w
        //printf("W ");
        out[1] |= AKS_W;
    }
    if (GetAsyncKeyState(88) & 0x8000){//x
        //printf("X ");
        out[1] |= AKS_X;
    }
    if (GetAsyncKeyState(89) & 0x8000){//y
        //printf("Y ");
        out[1] |= AKS_Y;
    }
    if (GetAsyncKeyState(90) & 0x8000){//z
        //printf("Z ");
        out[1] |= AKS_Z;
    }
    if (GetAsyncKeyState(48) & 0x8000){//0
        //printf("0 ");
        out[1] |= AKS_0;
    }
    if (GetAsyncKeyState(49) & 0x8000){//1
        //printf("1 ");
        out[1] |= AKS_1;
    }
    if (GetAsyncKeyState(50) & 0x8000){//2
        //printf("2 ");
        out[1] |= AKS_2;
    }
    if (GetAsyncKeyState(51) & 0x8000){//3
        //printf("3 ");
        out[1] |= AKS_3;
    }
    if (GetAsyncKeyState(52) & 0x8000){//4
        //printf("4 ");
        out[1] |= AKS_4;
    }
    if (GetAsyncKeyState(53) & 0x8000){//5
        //printf("5 ");
        out[1] |= AKS_5;
    }
    if (GetAsyncKeyState(54) & 0x8000){//6
        //printf("6 ");
        out[1] |= AKS_6;
    }
    if (GetAsyncKeyState(55) & 0x8000){//7
        //printf("7 ");
        out[1] |= AKS_7;
    }
    if (GetAsyncKeyState(56) & 0x8000){//8
        //printf("8 ");
        out[1] |= AKS_8;
    }
    if (GetAsyncKeyState(57) & 0x8000){//9
        //printf("9 ");
        out[1] |= AKS_9;
    }
    return true;
}
    return false;
}

