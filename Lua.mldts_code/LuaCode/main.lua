 
-- while (true ) do
--     print(GetForegroundWindow())
--     Sleep()
-- end
 
local hwnd = create_window(
    "1",
    "window_1",
    500,500
    )

print(hwnd)


MoveWindow(hwnd , 10,10,0,100)
Sleep(100)
MoveWindow(hwnd , 10,10,10,100)
Sleep(100)
MoveWindow(hwnd , 10,10,20,100)

-- for i=0 in 100 do 

--     MoveWindow(hwnd , 10,10,i,100)
--     Sleep(100)

-- end 

