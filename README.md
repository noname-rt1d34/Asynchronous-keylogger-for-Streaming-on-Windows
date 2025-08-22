This is a tool for displaying keypresses on OBS and plays an mp3 sound when a new message is recevied on twitch, I use it personally and just slapped it together on a weekend.

If anyone wants to expand on it or if they want me to modify it, please feel free to reach out to me on twitch or please comment on this repository.

Compiled with raylib and mingww64 Compiler flags used:

-static-libstdc++ -static-libgcc -static -mwindows -O2  -lraylib -lopengl32 -lgdi32 -lwinmm -lsetupapi -lws2_32

Audio sound from https://pixabay.com/sound-effects/notification-pluck-on-269288/

Made the PNG's myself

Press Space on the utility to ignore whitelisted applications (helldivers 2 for some reason does not get detected in the whitelist?), launch via a shortcut with command line parameters or automate with task scheduler.

KeyTracker.exe [twitchname] TslGame.exe HaloInfinite.exe AoE2DE_s.exe

TslGame.exe is pubg

Tool will auto-close if there is no twitch handle passed in, because I was lazy and didn't do a case where it checks if it is missing

Grok was used for the twitch IRC read chat process, I am still alittle confused about why it works? It seems that read only via a generic username and fake password, works..? No OATH2 or bot authentication/registration required, Twitch's API documentation does not seem to cover this method much, or I missed it?.

This is my first github I've ever made too!

Hash's of KeyTracker.exe (I don't know if this will help cause the only way the exe can be replaced is if a hacker has access to this account.... And can just as easily modify this info anyway...?): 

SHA1: 549f4e60677a8ab46b8ddd12dcb4f3cce90ac18d

MD5: 060bdf41792cdd77abea0c7fa8780a9b

SHA512: 760d6c7cbc42e2460082713c915d1f414f542e10fa457e679425234f0f7d69d2e3a1b96c47c558f9711327d0e93b9410c5328cbb937cd67df119ea72b494a25f
