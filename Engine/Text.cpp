#include "pch.h"
#include "Text.h"

Text::Text(LPCWSTR text, D3DXCOLOR color, D3DXVECTOR2 tPos)
{
    _text = text;
    _color = color;
    _tPos = tPos;

    _font = nullptr;

    D3DXCreateFont(d3ddev, 17, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &_font);
}

Text::~Text()
{
        
}

void Text::Draw() const
{
    RECT rect;
    SetRect(&rect, _tPos.x, _tPos.y, 1000, 1000);

    if(_font == nullptr) return;
    _font->DrawTextW(NULL, _text.c_str(), -1, &rect, DT_NOCLIP | DT_LEFT, _color);
    //m_font->Release();
}
