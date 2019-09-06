#pragma once

static class TagType
{
public:
	enum : int
	{
		None = -1,
		Background,
		Obstacle,
		Player,
		Controller,
		UI,
		Camera
	};
};

static class UnitStateType
{
public:
	enum : int
	{
		None = -1,
		Idle = 1,
		Move = 2,
		Attack = 3,
		Death = 4,
		Talk = 5
	};

};

static class SoldierType
{
public:
	enum : int
	{
		None = -1,
		Ship = 1
	};

};

static class WobbleType
{
public:
	enum : int
	{
		None = -1,
		Width = 1,
		Height = 2
	};
};

static class TypingType
{
public:
	enum : int
	{
		None = -1,
		Typing = 1
	};
};

static class Window
{
public:
	enum : int
	{
		Width = 1280,
		Height = 720,
	};

	static const bool Windowed = true;
	inline static Vector3 Center = Vector3(Width / 2, Height / 2, 0);
};