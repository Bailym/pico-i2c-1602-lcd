#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

typedef struct
{
    char *screenName;
    void (*screenInit)();
    void (*screenExit)();
    void (*screenSelect)();
    void (*screenScrollUp)();
    void (*screenScrollDown)();
} tScreen;

void ScreenManager_InitScreen(tScreen *screen);
void ScreenManager_ExitScreen(tScreen *screen);
void ScreenManager_SelectPress(tScreen *screen);
void ScreenManager_ScrollUp(tScreen *screen);
void ScreenManager_ScrollDown(tScreen *screen);
#endif // SCREEN_BEHAVIOUR_H