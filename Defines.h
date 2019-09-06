#pragma once

// Define functions

#if DEBUG
#define Log(context) std::cout<< context << std::endl;
#else
#define Log
#endif

#define PropertyG(G) __declspec(property(get = G))
#define PropertyS(S) __declspec(property(put = S))
#define PropertyGS(G, S) __declspec(property(get = G, put = S))

#define Half(in) ((float)in / 2.0f)

#define Super __super

// Define variables

#define g_pDevice		DXUTGetD3D9Device()
#define g_fNowTime		DXUTGetTime()
#define g_fDeltaTime	DXUTGetElapsedTime()

// 

using Tag = int;