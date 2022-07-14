#pragma once
class Button
{
private:
	RECT _rect;
public:
	Button(RECT);
	~Button();

	bool RectCollision(RECT rectA, RECT rectB);
	bool CheckForButtonPress(HWND hwnd);

	void Draw();
};

