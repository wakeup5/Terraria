#pragma once

#define TRANS_COLOR RGB(255, 0, 255)

#define RESOURCE_PATH		"resource/"
#define IMAGE_PATH			RESOURCE_PATH"image/"
#define SOUND_PATH			RESOURCE_PATH"sound/"

#define RESOURCE(fileName)	RESOURCE_PATH""fileName
#define IMAGE(fileName)		IMAGE_PATH""fileName".bmp"
#define SOUND(fileName)		SOUND_PATH""fileName

#define METER_TO_PIXEL		16
#define GRAVITY_ACCEL		(METER_TO_PIXEL * 60)

#define PLAYER_WIDTH		(METER_TO_PIXEL * 1.5)
#define PLAYER_HEIGHT		(METER_TO_PIXEL * 2)

#define MAX_SPEED			(METER_TO_PIXEL * 40)
#define MAX_ACCEL			(METER_TO_PIXEL * 100)
#define PLAYER_MOVE_SPEED	(METER_TO_PIXEL * 15)
#define PLAYER_MOVE_ACCEL	(METER_TO_PIXEL * 25)

#define JUMP_SPEED			-(METER_TO_PIXEL * 28)

#define MAP_SIZE_X 1000
#define MAP_SIZE_Y 100

#define INVENTORY_LENGTH 30

namespace Terraria
{
	typedef enum EQUIPMENT_TYPE
	{
		EQUIP_HELMET,
		EQUIP_TOP,
		EQUIP_PANT,
		EQUIP_ACCESSORY,
		EQUIP_NONE
	} EquipType;

	typedef enum ITEM_TYPE
	{
		ITEM_EQUIP,
		ITEM_WEAPON_SWORD,
		ITEM_WEAPON_BOW,
		ITEM_WEAPON_GUN,
		ITEM_WEAPON_MAGIC,
		ITEM_TOOL_PICKAXE,
		ITEM_TOOL_AXE,
		ITEM_AMMO_ARROW,
		ITEM_AMMO_BULLET,
		ITEM_POTION,
		ITEM_BLOCK_GRASS,
		ITEM_BLOCK_STONE,
		ITEM_BLOCK_TREE,
		ITEM_BLOCK_SILVER,
		ITEM_BLOCK_GOLD,
		ITEM_BLOCK_PLATFORM,
		ITEM_NONE
	} ItemType;

	typedef struct tagItemAbility
	{
		float HP;
		float MP;
		float attack;
		float defense;
		float atkSpeed;
		int shootNum;
	} ItemAbillity;

	typedef enum TILE_TYPE
	{
		TILE_GRASS,
		TILE_STONE,
		TILE_TREE,
		TILE_SILVER,
		TILE_GOLD,
		TILE_PLATFORM,
		TILE_NONE
	} TileType;

	typedef enum TILE_EXIST_DIRECT
	{
		TILE_EXIST_LEFT = 1,
		TILE_EXIST_TOP = 2,
		TILE_EXIST_RIGHT = 4,
		TILE_EXIST_BOTTOM = 8
	} TileExistDirect;

	/*
	typedef struct tagTile
	{
		int idx;
		int idy;
		TileType type;
	} Tile;
	*/
}