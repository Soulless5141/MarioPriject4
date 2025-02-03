#pragma once

#include "Vector2D.h"
#include <vector>

// オブジェクトタイプ
enum class eObjectType : unsigned char
{
	eNone,
	ePlayer,
	eEnemy,
	eBlock,
	eItem
};

// 当たり判定基底クラス
class Collision
{
public:
	bool						is_blocking;		// すり抜けフラグ
	eObjectType					object_type;		// 自身のオブジェクトタイプ
	std::vector<eObjectType>	hit_object_type;	// 適用するオブジェクトタイプ
	Vector2D					pivot;				// 中心点
	Vector2D					box_size;			// 判定の大きさ

public:
	Collision() :
		is_blocking(false),
		object_type(eObjectType::eNone),
		hit_object_type(),
		pivot(0.0f),
		box_size(0.0f)
	{

	}
	~Collision()
	{
		hit_object_type.clear();
	}

	// 当たり判定有効確認処理
	bool IsCheckHitTarget(eObjectType hit_object) const;
};

/// <summary>
/// 当たり判定確認処理
/// </summary>
/// <param name="c1">形状の情報1</param>
/// <param name="c2">形状の情報2</param>
/// <returns>当たっているなら、true</returns>
bool IsCheckCollision(const Collision& c1, const Collision& c2);


