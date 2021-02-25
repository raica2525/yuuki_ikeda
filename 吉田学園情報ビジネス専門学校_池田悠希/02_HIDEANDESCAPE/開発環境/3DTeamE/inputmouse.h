//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	inputkeyboard.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_
#include "input.h"
#include "main.h"
class CInputMouse : public CInput
{
public:
    CInputMouse();
    ~CInputMouse();

    typedef enum
    {
        MOUSE_LEFT = 0,
        MOUSE_RIGHT,
        MOUSE_CENTER,
        MOUSE_MAX
    } MOUSE;

    HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    void Uninit(void);
    void Update(void);

    bool GetKeyPress(int nkey);
    bool GetKeyTrigger(int nkey);

private:
    DIMOUSESTATE2 m_State;
};

#endif
