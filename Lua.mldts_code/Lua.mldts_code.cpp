// Lua.mldts_code.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//



#include <iostream>
#include<Windows.h>


 

extern "C" {
#include "Lua/include/lua.h"
#include "Lua/include/lualib.h"
#include "Lua/include/lauxlib.h"
}

#pragma comment(lib , "lua5.1.lib")
#pragma comment(lib , "lua51.lib")
int main()
{
    lua_State* lua = luaL_newstate();
    luaL_openlibs(lua);

    luaL_dofile(lua, "LuaCode/main.lua");


    std::cout << "Hello World!\n";
}

 