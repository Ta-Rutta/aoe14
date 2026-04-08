# include <Siv3D.hpp> // Siv3D v0.6.14
# include "effect.h"
# include "PlayerUi.h"
# include "Skill.h"
# include "common.cpp"

//using App = SceneManager<String>;//using=省略
bool once = true;
enum class EntityState { playerSide, enemySide };//シーン管理{0,1}
class EntityManager;
class Player;
class Enemy;
class PlayerAct;

ColorF changeColor(double t, double limit) {
	
		if (t < limit*0.1) {
			return ColorF(1.0, 0.9, 0.0, 0.4);
		}
		else if (limit*0.1 <= t && t < limit - 0.5) {
			return ColorF(1.0, 0.9 - 0.3 * t, 0.0, 0.4);
		}
		else {
			return ColorF(1.0, 0, 0.0, 0.4);
		}
	
}

ColorF colorFrame(double t, double limit) {

	if (t < limit * 0.1) {
		return ColorF(1.0, 0.9, 0.0, 0.7);
	}
	else if (limit * 0.1 <= t && t < limit - 0.5) {
		return ColorF(1.0, 0.9 - 0.3 * t, 0.0, 0.7);
	}
	else {
		return ColorF(1.0, 0, 0.0, 0.7);
	}

}


void reBool(bool& a) {
	if (a == false)a = true;
}


void drawRect(int x, int y, double t, int wide, int length) {
	double pro = Min(t, 1.0);
	const double change = EaseOutQuart(pro);
	RectF{ Arg::center(x, y), change * wide, change * length }.draw(changeColor(t, 3)).drawFrame(10,0, changeColor(t, 3),colorFrame(t,3));
	if (1 < t && t <= 2) {
		double pro2 = Min(t-1, 1.0);
		const double change2 = EaseOutQuart(pro2);
		RectF{ Arg::center(x, y), change2 * wide, change2 * length }.draw(changeColor(t, 3));
	}
	if (2 < t && t < 3) {
		double pro3 = Min(t - 2, 1.0);
		const double change3 = EaseOutQuart(pro3);
		RectF{ Arg::center(x, y), change3 * wide, change3 * length }.draw(changeColor(t, 3));
	}
}

void drawCircle(int x, int y, double t, int r) {
	double pro = Min(t, 1.0);
	const double change = EaseOutQuart(pro);
	Circle{ Arg::center(x, y), change * r }.draw(changeColor(t, 3)).drawFrame(10, 0, changeColor(t, 3), colorFrame(t, 3));;
	if (1 < t && t <= 2) {
		double pro2 = Min(t - 1, 1.0);
		const double change2 = EaseOutQuart(pro2);
		Circle{ Arg::center(x, y), change2 * r }.draw(changeColor(t, 3)).drawFrame(10, 0, changeColor(t, 3), colorFrame(t, 3));;
	}
	if (2 < t && t < 3) {
		double pro3 = Min(t - 2, 1.0);
		const double change3 = EaseOutQuart(pro3);
		Circle{ Arg::center(x, y), change3 * r }.draw(changeColor(t, 3)).drawFrame(10, 0, changeColor(t, 3), colorFrame(t, 3));;
	}
}


void drawDonut(int x, int y, double t, int r, int wide) {
	double pro = Min(t, 1.0);
	const double change = EaseOutQuart(pro);
	Circle{ Arg::center(x, y), change * r }.drawFrame(wide, 0, changeColor(t, 3), colorFrame(t, 3));;
	
}

void drawBlethRight(int x, int y, double t, int r) {
	double pro = Min(t, 1.0);
	const double change = EaseOutQuart(pro);
	Circle{ Arg::center(x, y), change * r }.drawPie(75_deg,30_deg,changeColor(t, 3));
	if (1 < t && t <= 2) {
		double pro2 = Min(t - 1, 1.0);
		const double change2 = EaseOutQuart(pro2);
		Circle{ Arg::center(x, y), change2 * r }.drawPie(75_deg, 30_deg, changeColor(t, 3));
	}
	if (2 < t && t < 3) {
		double pro3 = Min(t - 2, 1.0);
		const double change3 = EaseOutQuart(pro3);
		Circle{ Arg::center(x, y), change3 * r }.drawPie(75_deg, 30_deg, changeColor(t, 3));
	}
}

void drawBlethLeght(int x, int y, double t, int r) {
	double pro = Min(t, 1.0);
	const double change = EaseOutQuart(pro);
	Circle{ Arg::center(x, y), change * r }.drawPie(255_deg, 30_deg, changeColor(t, 3));
	if (1 < t && t <= 2) {
		double pro2 = Min(t - 1, 1.0);
		const double change2 = EaseOutQuart(pro2);
		Circle{ Arg::center(x, y), change2 * r }.drawPie(255_deg, 30_deg, changeColor(t, 3));
	}
	if (2 < t && t < 3) {
		double pro3 = Min(t - 2, 1.0);
		const double change3 = EaseOutQuart(pro3);
		Circle{ Arg::center(x, y), change3 * r }.drawPie(255_deg, 30_deg, changeColor(t, 3));
	}
}

RectF returnRect(int x, int y, int wide, int height) {
	return RectF{ Arg::center(x, y), wide, height };
}

Circle returnCircle(int x, int y, int r) {
	return Circle{ Arg::center(x, y) ,r};
}

double returnRadi(Vec2 attacker, Vec2 damager) {
	Vec2 direction = damager - attacker;
	return Math::Atan2(direction.y, direction.x);
}

class Entity {
public:
	int hp;
	int r;
	double t;
	EntityManager* manager;
	EntityState state;
	Circle area;
	Vec2 pos;
	Entity* target;
	bool targeted = false;
	int exp;
	int Lv;
	

	virtual void update() = 0;		
	virtual void draw()const = 0;
	virtual Circle getHitbox()const = 0;
	virtual void setTarget(Entity* target) = 0;

	Entity(EntityManager* manager,EntityState state,Vec2 pos,int exp,int lv)
		:manager{manager},state{state},pos{pos},exp{exp},Lv{lv}
	{

	}


	EntityState getState()const
	{
	return state;
	}

	void Targeted(bool t) {
		targeted = t;
	}

	void damage(int damage) {
		hp -= damage;
	}

	virtual void getExp(int exp){};

};


class EntityManager {
public:
	Effect effect;
	Array<std::shared_ptr<Entity>>entitys;
	Array<std::shared_ptr<Player>>player;
	Array<std::shared_ptr<Enemy>>enemy;
	HashTable<EntityState, Array<Entity*>>entityTable;
	const Font font{ 40, Typeface::CJK_Regular_JP };

	void add(Entity* entity)//配列につっこむ
	{
		auto sharedEntity = std::shared_ptr<Entity>(entity);

		entitys.push_back(sharedEntity);
		if (entity->getState() == EntityState::playerSide)
		{
			// Entity型 -> Player型へキャストして追加
			player.push_back(std::static_pointer_cast<Player>(sharedEntity));
		}
		else
		{
			// Entity型 -> Enemy型へキャストして追加
			enemy.push_back(std::static_pointer_cast<Enemy>(sharedEntity));
		}
		entityTable[entity->state].push_back(entity);
	}

	Array<Entity*> get(EntityState state)
	{
		if (entityTable.contains(state))
		{
			return entityTable[state];
		}

		return Array<Entity*>{};
	}

	void removeEntitytable(Entity* entity)
	{
		EntityState state;
		state = entity->getState();
		entityTable[state].remove(entity);
	}

	void update()
	{
		effect.update();
		for (auto& entity : entitys)
		{
			entity->update();
			if (entity->getHitbox().leftClicked())
			{
				for (auto& entity2 : entitys)
				{
					entity2->Targeted(false);
				}
				entity->Targeted(true);
				entitys[0]->setTarget(entity.get());
			}
		}

		entitys.remove_if([&](const std::shared_ptr<Entity>& entity)
		{
			if (entity->hp == 0)
			{
				entitys[0]->getExp(entity->exp);
				removeEntitytable(entity.get());
				return true;
			}
			return false;
		}
		);

	}

	void draw()const
	{
		for (auto& entity : entitys)
		{
			entity->draw();
		}
		

	}
};

class Player : public Entity
{
private:
	int expLimit[100] = {5,10,15,100};//経験値上限はここで設定
public:	
	bool move = true;

	Player(EntityManager* manager, EntityState state, Vec2 pos,int exp,int lv)
		:Entity{ manager,state,pos,exp,lv }
	{
		hp = 10000;
		r = 5;
		t = 0;

	}


	void update()
	{
		const double deltaTime = Scene::DeltaTime();
		t += deltaTime;
		area = { pos,r };

		if (move == true)
		{
			if (KeyD.pressed())
			{
				pos.x += Scene::DeltaTime() * 150;
			}
			if (KeyA.pressed())
			{
				pos.x -= Scene::DeltaTime() * 150;
			}
			if (KeyW.pressed())
			{
				pos.y -= Scene::DeltaTime() * 150;
			}
			if (KeyS.pressed())
			{
				pos.y += Scene::DeltaTime() * 150;
			}
			
		}

		while (Lv < 99 && exp >= expLimit[Lv-1])
		{
			exp -= expLimit[Lv-1]; 
			Lv++;           

			Print << U"Level Up! Lv: " << Lv;
		}
		
	}

	void drawTargeted()const
	{
		Circle{ pos,r + 15 }.drawFrame(5, 0, ColorF(1, 0, 0));
	}

	void getExp (int exp)
	{
		this->exp += exp;
	}

	void draw()const
	{
		area.draw();
	}

	Circle getHitbox()const
	{
		return Circle{ pos,r + 10 };
	}

	void damage()
	{
		hp -= 1;
	}

	int returnHP()
	{
		return hp;
	}

	Vec2 returnPos()
	{
		return pos;
	}

	void stop()
	{
		move = false;
	}

	void setTarget(Entity* Target)
	{
		target = Target;
	}

	void untarget()
	{
		target = nullptr;
	}

};

class SkillRegister
{
public:

	static Array<Skill> GetDefaultSkills() {
		return {
			{ U"斬撃", SkillType::Attack, U"Physic",U"GCD", 10, 30, 1, 0, {300, 300, 20}},
			{ U"メテオ", SkillType::Attack, U"Physic",U"GCD", 10, 30, 1, 0, {330, 300, 20} },
			{ U"ケアル", SkillType::Heal, U"Magic",U"", 10, 30, 1, 0, {360, 300, 20} }
		};
	}

};

class PlayerAct
{
public:

	void skillAttack(Player& player, EntityManager& manager, Skill skill)
	{
		manager.effect.add<DamageEffectP>(player.target->pos, 1, manager.font, skill.name);
		player.target->hp -= 1;
		if (player.target->hp == 0)player.untarget();
		skill.timer = skill.cooltime;
	}

	void skillHeal(Player& player, EntityManager& manager, Skill skill)
	{
		manager.effect.add<HealEffect>(player.pos, 1, manager.font, skill.name);
		player.hp += 1;
		skill.timer = skill.cooltime;
	}

	void skillBuff(Player& player, EntityManager& manager, Skill skill)
	{
		manager.effect.add<HealEffect>(player.pos, 1, manager.font, skill.name);
		player.hp += 1;
		skill.timer = skill.cooltime;
	}

};

class SkillManager
{
public:
	PlayerAct act;
	SkillRegister resister;
	Array<Skill> skill;
	bool itido = true;
	bool nido = true;

	void init() {
		skill = resister.GetDefaultSkills();
	}

	void addSkill()
	{
		/*if (itido)
		{
			Skill slash = { U"斬撃",SkillType::Attack,U"Physic",10,30,1,0,{300,300,20} };
			skill.push_back(slash);
			itido = false;
		}

		if (nido)
		{
			Skill meteo = { U"メテオ",SkillType::Attack,U"Physic",10,30,1,0,{330,300,20} };
			skill.push_back(meteo);
			Skill kearu = { U"ケアル",SkillType::Heal,U"Magic",10,30,1,0,{360,300,20} };
			skill.push_back(kearu);
			nido = false;
		}*/

	}

	void update(Player& player, EntityManager& manager)
	{
		for (Skill s : skill)
		{
			if (s.image.leftClicked())
			{
				if (player.target != nullptr)
				{
					if (s.type == SkillType::Attack)
					{
						act.skillAttack(player, manager, s);
					}					

					if (s.type == SkillType::Buff)
					{
						act.skillBuff(player, manager, s);
					}

				}

				if (s.type == SkillType::Heal)
				{
					act.skillHeal(player, manager, s);
				}
			}
		}
	}

	void draw()const
	{
		for (const auto& s : skill)
		{
			s.image.draw();
		}
	}
};






class Enemy :public Entity
{
public:
	bool move = true;

	double distance = 0;
	Vec2 velocity{ 0, 0 };
	Circle detection{ pos,r + 20 };
	Circle cougi;
	Polygon ougi;
	double fanwide = 30_deg;
	double autoAttack = 0;

	Enemy(EntityManager* manager, EntityState state, Vec2 pos, int exp, int lv)
		:Entity{ manager,state,pos,exp,lv }
	{
		hp = 1;
		r = 10;
		t = 0;
	}

	void update()
	{
		cougi = { pos,300 };

		if (target != nullptr)
		{
			double targetRadi = returnRadi(pos, target->pos);
			double halfFan = 30_deg / 2.0;
			ougi = cougi.pieAsPolygon(targetRadi, 30_deg);
		}

		area = { pos,r };
		detection = { pos,r + 20 };

		if (move)
		{
			if (target != nullptr)
			{
				const double deltaTime = Scene::DeltaTime();
				autoAttack += deltaTime;

				pos = Math::SmoothDamp(pos, toTarget(pos, target->pos, 35), velocity, 0.2);//敵の追従スピード0.2が最適
				if (autoAttack >= 0.5) {
					target->damage(3);
					manager->effect.add<DamageEffectE>(target->pos, 3, manager->font, U"a");
					autoAttack = 0;
				}
			}
			else
			{
				autoAttack = 0;
			}
		}
	}

	void drawTargeted()const
	{
		Circle{ pos,r + 15 }.drawFrame(5, 0, ColorF(1, 0, 0));
	}

	void draw()const
	{

		if (targeted == true)drawTargeted();
		Circle{ pos,r }.draw();
		if (target != nullptr)
		{
			ougi.draw(ColorF{ 1,0,0,0.5 });
		}
	}

	void serchTarget()
	{
		for (auto& player : manager->get(EntityState::playerSide))
		{
			if (player->area.intersects(Circle{ pos,r + 100 }))
			{
				setTarget(player);
			}
		}
	}

	Vec2 toTarget(const Vec2& startPos, const Vec2& targetPos, double length)
	{
		return targetPos + (startPos - targetPos).setLength(length);
	}

	Circle getHitbox()const
	{
		return Circle{ pos,r + 50 };
	}

	void setTarget(Entity* Target)
	{
		target = Target;
	}

};



//class Attack
//{
//public:
//
//	Player* player;
//	double t = 0;
//	bool keepTime = false;
//
//	Array<double> time = Array<double>(100, 0);
//	Array<bool> timeStart = Array<bool>(100, false);
//	Array<bool> attackCheck = Array<bool>(100, true);
//	
//	RectF attack1 = returnRect(890, 360, 500, 600);
//	RectF attack1_2 = returnRect(390, 360, 500, 600);
//
//	Circle attack2_1 = returnCircle(890, 210, 250);
//	Circle attack2_2 = returnCircle(390, 210, 250);
//	Circle attack2_3 = returnCircle(390, 510, 250);
//	Circle attack2_4 = returnCircle(890, 510, 250);
//	Circle attack2_5 = returnCircle(640, 360, 250);
//
//	RectF attack3_1 = returnRect(640, 110, 1000, 100);
//	RectF attack3_2 = returnRect(640, 610, 1000, 100);
//
//	Circle attack3_3 = returnCircle(140, 360, 1000);	
//
//	Circle attack3_4 = returnCircle(1140, 360, 1000);
//
//	Polygon tr3_3;
//	Polygon tr3_4;
//
//	RectF attack4_1 = returnRect(640, 210, 1000, 100);
//	RectF attack4_2 = returnRect(640, 510, 1000, 100);
//
//	RectF attack5_1 = returnRect(640, 310, 1000, 100);
//	RectF attack5_2 = returnRect(640, 410, 1000, 100);
//
//	Attack(Player* p)
//		: player{p}
//	{
//		attack3_3.pieAsPolygon(75_deg, 30_deg);
//		tr3_3 = attack3_3.pieAsPolygon(75_deg, 30_deg);
//
//		attack3_4.pieAsPolygon(255_deg, 30_deg);
//		tr3_4 = attack3_4.pieAsPolygon(255_deg, 30_deg);  
//    }
//
//	void closeTime(double t1, double t2, double t, int n) {
//		if (t1 < t && t < t2) {
//			reBool(timeStart[n]);
//		}
//	}
//
//	void checkRect(bool& b, RectF t) {
//		b = false;
//		if (Circle{ player->returnPos(),20}.intersects(t)) {
//			player->damage();
//		}
//	}
//
//	void checkCircle(bool& b, Circle c) {
//		b = false;
//		if (Circle{ player->returnPos(),20 }.intersects(c)) {
//			player->damage();
//		}
//	}
//
//	int returnHp() {
//		return player->returnHP();
//	}
//
//	void Action(int t) {
//
//		//攻撃判定追加(あとでめんどーになる)
//		if (3 <= t && attackCheck[0]) {
//			attackCheck[0] = false;
//			if (Circle{ player->returnPos(),20 }.intersects(attack1)) {
//				player->damage();
//			}
//			//checkRect(attackCheck[0], attack1);
//		}
//
//		if (4 <= t && attackCheck[1]) {
//			attackCheck[1] = false;
//			if (Circle{ player->returnPos(),20 }.intersects(attack1_2)) {
//				player->damage();
//			}
//		}
//
//		if (7 <= t && attackCheck[2]) {
//			attackCheck[2] = false;
//			if (Circle{ player->returnPos(),20 }.intersects(attack2_1)) {
//				player->damage();
//			}
//		}
//
//		if (7.25 <= t && attackCheck[3]) {
//			attackCheck[3] = false;
//			if (Circle{ player->returnPos(),20 }.intersects(attack2_2)) {
//				player->damage();
//			}
//		}
//
//		if (7.5 <= t && attackCheck[4]) {
//			attackCheck[4] = false;
//			if (Circle{ player->returnPos(),20 }.intersects(attack2_3)) {
//				player->damage();
//			}
//		}
//
//		if (7.75 <= t && attackCheck[5]) {
//			attackCheck[5] = false;
//			if (Circle{ player->returnPos(),20 }.intersects(attack2_4)) {
//				player->damage();
//			}
//		}
//
//		if (9 <= t && attackCheck[6]) {
//			attackCheck[6] = false;
//			if (Circle{ player->returnPos(),20 }.intersects(attack2_5)) {
//				player->damage();
//			}
//		}
//
//		if (12 <= t && attackCheck[7]) {
//
//			attackCheck[7] = false;
//
//			if (Circle{ player->returnPos(),20 }.intersects(attack3_1)) {
//				player->damage();
//			}
//
//			if (Circle{ player->returnPos(),20 }.intersects(attack3_2)) {
//				player->damage();
//			}
//
//			if (Circle{ player->returnPos(),20 }.intersects(tr3_3)) {
//				player->damage();
//			}
//
//			if (Circle{ player->returnPos(),20 }.intersects(tr3_4)) {
//				player->damage();
//			}
//		}
//
//
//		if (13 <= t && attackCheck[11]) {
//			attackCheck[11] = false;
//			if (Circle{ player->returnPos(),20 }.intersects(attack4_1)) {
//				player->damage();
//			}
//		}
//
//		if (13 <= t && attackCheck[12]) {
//			attackCheck[12] = false;
//			if (Circle{ player->returnPos(),20 }.intersects(attack4_2)) {
//				player->damage();
//			}
//		}
//
//		if (15.5 <= t && attackCheck[13]) {
//			attackCheck[13] = false;
//			if (Circle{ player->returnPos(),20 }.intersects(attack5_1)) {
//				player->damage();
//			}
//
//			if (Circle{ player->returnPos(),20 }.intersects(attack5_2)) {
//				player->damage();
//			}
//		}
//
//		if (15.5 <= t && attackCheck[14]) {
//			attackCheck[14] = false;
//			
//		}		
//	}
//
//	void chengeTime() {
//
//		closeTime(0, 3, t, 0);
//
//		closeTime(1, 4, t, 1);
//
//		closeTime(4, 7, t, 2);
//
//		closeTime(4.25, 7.25, t, 3);
//
//		closeTime(4.5, 7.5, t, 4);
//
//		closeTime(4.75, 7.75  , t, 5);
// 
//		closeTime(6, 9, t, 6);
//
//		closeTime(9, 12, t, 7);
//
//		closeTime(10, 13, t, 8);
//
//		closeTime(12.5, 15.5, t, 9);
//		
//	}
//
//	int returnT() {
//		return t;
//	}
//
//
//
//	void update() {
//		const double deltaTime = Scene::DeltaTime();
//		if (!keepTime) {			
//			t += deltaTime;
//		}
//
//		for (int k = 0; k < 10; k++) {
//			if (timeStart[k] == true) {
//				time[k] += deltaTime;
//			}
//		}
//
//		Action(t);
//		chengeTime();
//	}
//
//
//	void draw()const {
//
//		//攻撃描画追加(あとでめんどーになる)
//		if (0 < t && t < 3) {
//			drawDonut(player->pos.x, player->pos.y, time[0], 300, 200);
//		}
//
//		if (1 < t && t < 4) {
//			drawRect(390, 360, time[1], 500, 600);
//		}
//
//		if (4 < t && t < 7) {
//			drawCircle(890, 210, time[2], 250);
//		}
//
//		if (4.25 < t && t < 7.25) {
//			drawCircle(390, 210, time[3], 250);
//		}
//
//		if (4.5 < t && t < 7.5) {
//			drawCircle(390, 510, time[4], 250);
//		}
//
//		if (4.75 < t && t < 7.75) {
//			drawCircle(890, 510, time[5], 250);
//		}
//		if (6 < t && t < 9) {
//			drawCircle(640, 360, time[6], 250);
//		}
//		if (9 < t && t < 12) {
//			drawRect(640, 110, time[7], 1000, 100);
//			drawRect(640, 610, time[7], 1000, 100);
//			drawBlethRight(140, 360, time[7], 1000);
//			drawBlethLeght(1140, 360, time[7], 1000);
//		}
//		if (10 < t && t < 13) {
//			drawRect(640, 210, time[8], 1000, 100);
//			drawRect(640, 510, time[8], 1000, 100);
//		}
//		if (12.5 < t && t < 15.5) {
//			drawRect(640, 310, time[9], 1000, 100);
//			drawRect(640, 410, time[9], 1000, 100);
//		}
//
//	}
//
//
//};


class Title : public App::Scene
{
public:

    Title(const InitData& init)
		: IScene{ init }
	{

	}
	const Font font{ 46 };
	void update()override {
		const double hue = (Scene::Time() * 30);		
			Scene::SetBackground(HSV{ hue });
			if (KeyEnter.down()) {
				changeScene(U"Battle", 0.5s);
			}
			if (KeySpace.down()) {
				changeScene(U"Debug", 0.5s);
			}
	}

	void draw()const override {
		Ellipse{ 640, 360, 500, 300 }.draw(Color{ 139,69,19 });		
		font( U"Enterキーでスタート！" ).draw(50,400,260 , ColorF{ 0,0,0 });
	}
};

//class Battle : public App::Scene
//{
//public:
//	EntityManager* manager;
//
//	Battle(const InitData& init)
//		: IScene{ init }
//	{		
//		attack3_3.pieAsPolygon(75_deg, 30_deg);
//		tr3_3 = attack3_3.pieAsPolygon(75_deg, 30_deg);
//		attack3_4.pieAsPolygon(255_deg, 30_deg);
//		tr3_4 = attack3_4.pieAsPolygon(255_deg, 30_deg);		
//	}
//
//	Player* player = new Player(manager, EntityState::playerSide, Vec2{ 640,360 }, 0, 0);
//	Attack attack{ player };
//	
//
//	Ellipse field{ 640, 360, 500, 300 };
//	Vec2 UIpos{ 640, 360 };
//	Vec2 check;
//	Vec2 bar;
//
//	const Font font{ 46 };
//	double t = 0;
//	int hp=0;
//	
//	
//	static constexpr int r = 5;
//
//	Camera2D camera{ UIpos, 1.0, CameraControl::None_ };
//	bool move = true;
//	bool end = false;
//	bool win = false;
//	
//
//	RectF attack1=returnRect(890, 360, 500, 600);
//	RectF attack1_2 = returnRect(390, 360, 500, 600);
//
//	Circle attack2_1 = returnCircle(890, 210, 250);
//	Circle attack2_2 = returnCircle(390, 210, 250);
//	Circle attack2_3 = returnCircle(390, 510, 250);
//	Circle attack2_4 = returnCircle(890, 510, 250);
//	Circle attack2_5 = returnCircle(640, 360, 250);
//
//	RectF attack3_1 = returnRect(640, 110, 1000, 100);
//	RectF attack3_2 = returnRect(640, 610, 1000, 100);
//
//	Circle attack3_3 = returnCircle(140, 360, 1000);
//	Circle attack3_4 = returnCircle(1140, 360, 1000);	
//    Polygon tr3_3;	
//	Polygon tr3_4;
//
//	RectF attack4_1 = returnRect(640, 210, 1000, 100);
//	RectF attack4_2 = returnRect(640, 510, 1000, 100);
//
//	RectF attack5_1 = returnRect(640, 310, 1000, 100);
//	RectF attack5_2 = returnRect(640, 410, 1000, 100);
//	
//
//
//	void update()override {
//		UIpos.x = player->pos.x;
//		UIpos.y = player->pos.y;
//
//		hp = player->returnHP();
//
//		const double hue = (Scene::Time() * 30);
//		if (end == false) {
//			Scene::SetBackground(HSV{ hue });
//		}
//
//		
//		camera.update();
//		camera.setTargetCenter(UIpos);
//		
//
//		bar.x = player->pos.x-32;
//		bar.y = player->pos.y - 75;
//
//		
//		player->update();
//		attack.update();
//		
//		
//
//		if (t >= 16) {
//			win = true;
//		}
//
//		if (!(Circle{ player->pos,20 }.intersects(field))) {									
//			hp = 0;
//		}
//
//		if (hp <= 0)
//		{
//			move = false;
//			end = true;
//			t = 0;
//			
//		}
//
//		if (end == true)
//		{
//			player->stop();
//			if (KeyEnter.down()) {
//				changeScene(U"Battle", 0.5s);
//			}
//		}
//
//		if (win == true) {
//			move = false;
//			t = 0;
//			player->stop();
//			if (KeyEnter.down()) {
//				changeScene(U"Battle", 0.5s);
//			}
//		}
//
//	}
//
//	void draw() const override {
//		
//			const auto te = camera.createTransformer();
//
//			field.draw(Color{ 139,69,19 });
//
//			player->draw();
//			attack.draw();
//			
//
//			//hpバー
//			RectF{ player->pos.x - 30,player->pos.y - 45,60,20 }.draw(ColorF(1,1,1)).drawFrame(3);
//			RectF{ player->pos.x - 30,player->pos.y - 45,hp * 20,20 }.draw(ColorF(0, 1, 0));
//		
//		
//		if (end)
//		{			
//			Rect(-500, -500, 3000, 3000).draw(ColorF{ 0,0,0,0.7 });
//			font(U"YOU DIED").draw(80, player->pos.x-200, player->pos.y-60, ColorF(1, 1, 1));
//			font(U"Enterキーでリスタート").draw(50, player->pos.x - 250, player->pos.y+40, ColorF(1, 1, 1));
//			
//		}
//
//		if (win)
//		{
//			Rect(-500, -500, 3000, 3000).draw(ColorF{ 0,0,0.3,0.7 });
//			font(U"YOU WIN!").draw(80, player->pos.x - 200, player->pos.y - 60, ColorF(1, 1, 1));
//			font(U"Enterキーでリスタート").draw(50, player->pos.x - 250, player->pos.y + 40, ColorF(1, 1, 1));
//		}
//		
//	}
//};


class Debug : public App::Scene
{
public:

	EntityManager manager;
	SkillManager skillManager;
	Camera2D camera{ Vec2{ 640, 360 }, 1.0 };

	Debug(const InitData& init)
		: IScene{ init }
	{
		Scene::SetBackground(Palette::Black);
		manager.add(new Player{ &manager, EntityState::playerSide, Vec2{640,360},0 ,1});
		manager.add(new Enemy{ &manager, EntityState::enemySide, Vec2{100,100},5 ,1 });
		manager.add(new Enemy{ &manager, EntityState::enemySide, Vec2{200,100},10 ,2 });
		manager.add(new Enemy{ &manager, EntityState::enemySide, Vec2{300,100} ,15,3 });
		
		skillManager.init();
	}
	
	
	void update()override
	{
		manager.update();

		
		if (not manager.player.isEmpty()) {
			auto& player = *manager.player[0];
			skillManager.update(*manager.player[0], manager);
			Vec2 targetPos = player.pos;

			if (player.target != nullptr)
			{
				// ターゲットとの中間地点を計算
				targetPos = (player.pos + player.target->pos) / 2.0;
			}
			camera.setTargetCenter(targetPos);

			camera.setTargetCenter(targetPos);

			// B. ズーム（マウスホイール）
			double scale = camera.getTargetScale();
			// ホイールの回転量に応じてスケールを変更（0.2倍〜4.0倍の範囲に制限）
			scale = Clamp(scale + (Mouse::Wheel() * -0.1), 0.2, 4.0);
			camera.setTargetScale(scale);
		}

		camera.update();

		for (auto& enemy : manager.enemy)
		{
			enemy->serchTarget();
			
		}
	}

	void draw()const override {
		const auto transformer = camera.createTransformer();
		Scene::SetBackground(Palette::Skyblue);
		manager.draw();
		skillManager.draw();
	}
};

void Main()
{

	
	Window::Resize(1920, 720);
	Window::SetStyle(WindowStyle::Sizable);

	App manager;

	//manager.add<Title>(U"Title");
	/*manager.add<Battle>(U"Battle");*/
	manager.add<Debug>(U"Debug");

	while (System::Update())
	{
		if (not manager.update())
		{

			break;
		}
	}
}
