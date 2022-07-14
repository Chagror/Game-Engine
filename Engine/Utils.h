#pragma once
#include "framework.h"
#include <string>


LPCWSTR static FloatToLPCWSTR(float a) {
    std::string stringtoconvert = std::to_string(a);

    std::wstring temp = std::wstring(stringtoconvert.begin(), stringtoconvert.end());
    LPCWSTR lpcwstr = temp.c_str();
    return lpcwstr;
}

static void DebugLog(std::string s)
{
    s += "\n";
    std::wstring temp(s.begin(), s.end());
    LPCWSTR lpcwstr = temp.c_str();
    OutputDebugStringW(lpcwstr);
}

static D3DXVECTOR3 palette(float t, D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c, D3DXVECTOR3 d)
{
    float rR = a.x + b.x * cos(6.28318f * (c.x * t + d.x));
    float rG = a.y + b.y * cos(6.28318f * (c.y * t + d.y));
    float rB = a.z + b.z * cos(6.28318f * (c.z * t + d.z));

    D3DXVECTOR3 result = D3DXVECTOR3(rR, rG, rB);
    return result;
}