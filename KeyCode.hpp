#pragma once

#include <Windows.h>

enum class KeyCode
{
	Q = 'Q',
	W = 'W',
	E = 'E',
	R = 'R',
	T = 'T',
	Y = 'Y',
	U = 'U',
	I = 'I',
	O = 'O',
	P = 'P',
	A = 'A',
	S = 'S',
	D = 'D',
	F = 'F',
	G = 'G',
	H = 'H',
	J = 'J',
	K = 'K',
	L = 'L',
	Z = 'Z',
	X = 'X',
	C = 'C',
	V = 'V',
	B = 'B',
	N = 'N',
	M = 'M',

	Minus = '-',
	Plus = '+',
	Slash = '/',
	Comma = ',',
	Period = '.',
	Colon = ':',
	Semicolon = ';',
	Less = '<',
	Equals = '=',
	Greater = '>',
	Question = '?',
	At = '@',

	Enter = VK_RETURN,
	Space = VK_SPACE,
	Backspace = VK_BACK,
	LeftShift = VK_LSHIFT,
	RightShift = VK_RSHIFT,
	Control = VK_CONTROL,
	Escape = VK_ESCAPE,
	Insert = VK_INSERT,
	Home = VK_HOME,
	End = VK_END,

	F1 = VK_F1,
	F2 = VK_F2,
	F3 = VK_F3,
	F4 = VK_F4,
	F5 = VK_F5,
	F6 = VK_F6,
	F7 = VK_F7,
	F8 = VK_F8,
	F9 = VK_F9,
	F10 = VK_F10,
	F11 = VK_F11,
	F12 = VK_F12,
	F13 = VK_F13,
	F14 = VK_F14,
	F15 = VK_F15,

	LeftArrow = VK_LEFT,
	UpArrow = VK_UP,
	RightArrow = VK_RIGHT,
	DownArrow = VK_DOWN,

	Mouse0 = VK_LBUTTON,
	Mouse1 = VK_RBUTTON,
	Mouse2 = VK_MBUTTON,
	Mouse3 = VK_XBUTTON1,
	Mouse4 = VK_XBUTTON2,

	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON
};