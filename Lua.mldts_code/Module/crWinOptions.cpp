#include <Windows.h>

class crWinOptions
{
public:
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    WNDPROC WNDPROC_CALL;
    HINSTANCE HINSTANCE_CALL;
    const char* CLASS = "myWindowClass";
    void new_create(WNDPROC _WNDPROC_CALL, HINSTANCE _HINSTANCE_CALL) {

        WNDPROC_CALL = _WNDPROC_CALL;
        HINSTANCE_CALL = _HINSTANCE_CALL;



        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = 0;
       // wc.lpfnWndProc = *WNDPROC_CALL;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = HINSTANCE_CALL;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName = NULL;
        wc.lpszClassName = CLASS;
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
        RegisterClassEx(&wc);
    }

};

