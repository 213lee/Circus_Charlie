#pragma once
#include "Mecro.h"

class BitMap
{
private:
	HDC MemDC;
	HBITMAP m_BitMap;
	SIZE m_Size;
public:
	void Init(HDC hdc,char* FileName, int width = 0, int height = 0);
	void Draw(HDC hdc, int x, int y);
	void Draw(HDC hdc, int x, int y, int width, int height);
	inline SIZE GetSize()
	{
		return m_Size;
	}
	BitMap();
	~BitMap();
};

