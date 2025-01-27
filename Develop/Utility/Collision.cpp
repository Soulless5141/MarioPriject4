#include "Collision.h"
#include <math.h>

/// <summary>
/// 適用オブジェクトか確認する処理
/// </summary>
/// <param name="hit_object">相手のオブジェクトタイプ</param>
/// <returns>適用するオブジェクトなら、true</returns>
bool Collision::IsCheckHitTarget(eObjectType hit_object) const
{
	// 適用するオブジェクトタイプなら、true
	for (eObjectType type : hit_object_type)
	{
		if (type == hit_object)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 当たり判定確認処理
/// </summary>
/// <param name="c1">情報1</param>
/// <param name="c2">情報2</param>
/// <returns>当たっているなら、true</returns>
bool IsCheckCollision(const Collision& c1, const Collision& c2)
{
	// 矩形Aの左辺と矩形Bの右辺の関係チェック
	bool is_left_less_right = false;
	if (c1.point[0].x <= c2.point[1].x)
	{
		is_left_less_right = true;
	}

	// 矩形Aの右辺と矩形Bの左辺の関係チェック
	bool is_right_greater_left = false;
	if (c1.point[1].x >= c2.point[0].x)
	{
		is_right_greater_left = true;
	}

	// 矩形Aの上辺と矩形Bの下辺の関係チェック
	bool is_top_less_bottom = false;
	if (c1.point[0].y <= c2.point[1].y)
	{
		is_top_less_bottom = true;
	}

	// 矩形Aの下辺と矩形Bの上辺の関係チェック
	bool is_bottom_greater_top = false;
	if (c1.point[1].y >= c2.point[0].y)
	{
		is_bottom_greater_top = true;
	}

	// 各辺の関係をチェックする(全てtrueなら当たり)
	if (is_left_less_right == true &&
		is_right_greater_left == true &&
		is_top_less_bottom == true &&
		is_bottom_greater_top)
	{
		return true;
	}

	// 全ての条件が成立していない場合、当たっていない
	return false;
}
