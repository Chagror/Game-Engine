#pragma once
#include <string>

class Text
{
	std::wstring _text;
	D3DXCOLOR _color;
	D3DXVECTOR2 _tPos;
	LPD3DXFONT _font;

public:
	Text(LPCWSTR, D3DXCOLOR, D3DXVECTOR2);
	~Text();

	void SetText(LPCWSTR text) { _text = text; }

	void Draw() const;
};
