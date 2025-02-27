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
		Enemy,
		Controller,
		Radar,
		UI,
		Button,
		Effect,
		Operator,
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
		Ship = 1,
		Short = 2,
		Long = 3,
		Builder = 4,
		DefenceTower = 5,
		Tank = 6,
		AirCraft = 7,
		Dron = 8,
		LargeAirCraft = 9,
		LargeSoldier = 10
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

static class MapType
{
public:
	enum : int
	{
		None = -1,
		Haeundae = 1,
		Seomyeon = 2,
		Busan_station = 3
	};
};

static class PlayerControllerType
{
public:
	enum : int
	{
		Default = 0,
		Tutorial = 1,
		Stage1 = 2,
		Stage2 = 3,
		Stage3 = 4
	};
};

static class FadeTarget
{
public:
	enum : int
	{
		None = -1,
		Renderer_Alpha
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

	static const bool Windowed = false;
	inline static Vector3 Center = Vector3(Width / 2, Height / 2, 0);
};