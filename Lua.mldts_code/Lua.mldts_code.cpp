// Lua.mldts_code.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//



#include <iostream>
#include<Windows.h>
#include <string>
#include <vector>
#include "Module/crWinOptions.cpp"


using namespace std;


#pragma region lua include 

#pragma comment(lib , "lua5.1.lib")
#pragma comment(lib , "lua51.lib")
extern "C" {
#include "Lua/include/lua.h"
#include "Lua/include/lualib.h"
#include "Lua/include/lauxlib.h"

}

#pragma endregion



lua_State* lua;

HWND hwnd = 0;
int* hwnd_mem = 0;

 
int V_count = 0;

extern "C" int GetFWindow(lua_State * L)
{
    lua_pushinteger(L, (int)GetForegroundWindow());
    return 1;   
}
extern "C" int _Sleep(lua_State * L)
{
    
    Sleep(1000);
    return 1;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_PAINT:
        HDC         hdc;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);

        // draw some text centered in the client area
        RECT rect;
        GetClientRect(hwnd, &rect);
        DrawText(hdc, TEXT("Hello, Windows!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        EndPaint(hwnd, &ps);
        return S_OK;

    case WM_DESTROY:
        // exit the application
        PostQuitMessage(0);
        return S_OK;
    }

    // let Windows process any unhandled messages
    return DefWindowProc(hwnd, message, wParam, lParam);
}

 
extern "C" int create_window(lua_State * L)
{
 
    size_t* size{};
    const char* name = lua_tolstring(L, 1 , size);
    size_t* size2{};
    const char* classNamae = lua_tolstring(L, 2, size2);

    int w = lua_tointeger(L, 3);
    int h = lua_tointeger(L, 4);

    cout << name << endl;

    
    WNDCLASS windowClass = { 0 };
    windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hInstance = NULL;
    windowClass.lpfnWndProc = WndProc;
    windowClass.lpszClassName = classNamae;
    windowClass.style =  CS_HREDRAW | CS_VREDRAW;
    if (!RegisterClass(&windowClass)) {
        MessageBox(NULL, "Could not register class", "Error", MB_OK);
         
    }
        
    HWND windowHandle = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        classNamae,
        name,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, w, h,
        NULL, NULL, NULL, NULL);

    cout << windowHandle << endl;
    ShowWindow(windowHandle, SW_RESTORE);
    

    lua_pushinteger(L,  (int)windowHandle);
     
    
    return 1;
}
char buff[256];
int error;
 
DWORD WINAPI error_lua_stack(void* b) {
    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        error = luaL_loadstring(lua, buff) || lua_pcall(lua, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s\n", lua_tostring(lua, -1));
            lua_pop(lua, 1);

        }
    }
    return 0;
}

 
int main()
{

    lua = luaL_newstate();

    lua_register(lua, "GetForegroundWindow", GetFWindow);
    lua_register(lua, "Sleep", _Sleep);

    lua_register(lua, "Sleep", _Sleep);
 
    lua_register(lua, "create_window", create_window);
    luaL_openlibs(lua);
    luaL_dofile(lua, "LuaCode/main.lua");  
     

    CreateThread(NULL, 0, error_lua_stack, NULL, NULL, NULL);

   
    MSG messages;
    while (GetMessage(&messages, NULL, 0, 0) > 0)
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    lua_close(lua);
    cout << "Close" << endl;

}

 