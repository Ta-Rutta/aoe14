#pragma once

enum class SkillType
{
	Attack,
	Heal,
	Buff
};

struct Skill
{
	String name; //スキル名
	SkillType type; //攻撃・補助の区別
	String skillID; //スキルID
	String coolTimeID; //クールタイム分け
	int value; //攻撃力
	double range; //範囲
	double cooltime; //クールタイム
	double timer=0; //経過時間
	Rect image; //
};



