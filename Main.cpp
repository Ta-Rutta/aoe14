# include <Siv3D.hpp> // Siv3D v0.6.14

using App = SceneManager<String>;//using=省略
bool once = true;

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

class Player {
private:	
	int hp = 3;
	int r = 5;
	double t = 0;
public:	
	Vec2 pos{ 640,360 };
	bool move = false;

	void update() {
		const double deltaTime = Scene::DeltaTime();
		t += deltaTime;

		if (move == true) {
			if (KeyRight.pressed()) {
				pos.x += Scene::DeltaTime() * 150;
			}
			if (KeyLeft.pressed()) {
				pos.x -= Scene::DeltaTime() * 150;
			}
			if (KeyUp.pressed()) {
				pos.y -= Scene::DeltaTime() * 150;
			}
			if (KeyDown.pressed()) {
				pos.y += Scene::DeltaTime() * 150;
			}
		}
	}

	void draw() {
		Circle{ pos,r }.draw();
	}

	Circle returnEria() {
		return Circle{ pos,r };
	}

	void damage() {
		hp -= 1;
	}
};


//class Attack
//{
//public:
//
//	Player* player;
//
// Array<double> time = Array<double>(100);
// Array<bool> timeStart = Array<bool>(100);
// Array<bool> attackCheck = Array<bool>(100);
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
//		:player{p}
//	{
//		attack3_3.pieAsPolygon(75_deg, 30_deg);
//		tr3_3 = attack3_3.pieAsPolygon(75_deg, 30_deg);
//
//		attack3_4.pieAsPolygon(255_deg, 30_deg);
//		tr3_4 = attack3_4.pieAsPolygon(255_deg, 30_deg);
//	}
//
//
//	void Action(int t) {
//
//		if (3 <= t && attack1_check) {
//			attack1_check = false;
//			if (Circle{ pos,20 }.intersects(attack1)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (4 <= t && attack2_check) {
//			attack2_check = false;
//			if (Circle{ pos,20 }.intersects(attack1_2)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (7 <= t && attack3_check) {
//			attack3_check = false;
//			if (Circle{ pos,20 }.intersects(attack2_1)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (7.25 <= t && attack4_check) {
//			attack4_check = false;
//			if (Circle{ pos,20 }.intersects(attack2_2)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (7.5 <= t && attack5_check) {
//			attack5_check = false;
//			if (Circle{ pos,20 }.intersects(attack2_3)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (7.75 <= t && attack6_check) {
//			attack6_check = false;
//			if (Circle{ pos,20 }.intersects(attack2_4)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (9 <= t && attack7_check) {
//			attack7_check = false;
//			if (Circle{ pos,20 }.intersects(attack2_5)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (12 <= t && attack8_check) {
//			attack8_check = false;
//			if (Circle{ pos,20 }.intersects(attack3_1)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (12 <= t && attack9_check) {
//			attack9_check = false;
//			if (Circle{ pos,20 }.intersects(attack3_2)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (12 <= t && attack10_check) {
//			attack10_check = false;
//			if (Circle{ pos,20 }.intersects(tr3_3)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (12 <= t && attack11_check) {
//			attack11_check = false;
//			if (Circle{ pos,20 }.intersects(tr3_4)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (13 <= t && attack12_check) {
//			attack12_check = false;
//			if (Circle{ pos,20 }.intersects(attack4_1)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (13 <= t && attack13_check) {
//			attack13_check = false;
//			if (Circle{ pos,20 }.intersects(attack4_2)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (15.5 <= t && attack14_check) {
//			attack14_check = false;
//			if (Circle{ pos,20 }.intersects(attack5_1)) {
//				player_hp -= 1;
//			}
//		}
//
//		if (14 <= t && attack15_check) {
//			attack15_check = false;
//			if (Circle{ pos,20 }.intersects(attack5_2)) {
//				player.player_hp -= 1;
//			}
//		}
//		
//
//	}
//
//	void update()
//
//
//};


class title : public App::Scene
{
public:

	title(const InitData& init)
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
	}

	void draw()const override {
		Ellipse{ 640, 360, 500, 300 }.draw(Color{ 139,69,19 });		
		font( U"Enterキーでスタート！" ).draw(50,400,260 , ColorF{ 0,0,0 });
	}
};

class Battle : public App::Scene
{
public:
	Array<double> time = Array<double>(100);
	Array<bool> timeStart = Array<bool>(100);
	Array<bool> attackCheck = Array<bool>(100);


	Battle(const InitData& init)
		: IScene{ init }
	{		
		attack3_3.pieAsPolygon(75_deg, 30_deg);
		tr3_3 = attack3_3.pieAsPolygon(75_deg, 30_deg);
		attack3_4.pieAsPolygon(255_deg, 30_deg);
		tr3_4 = attack3_4.pieAsPolygon(255_deg, 30_deg);
		for (auto t : timeStart) {
			t << true;
		}
		for (auto c : attackCheck) {
			c << false;
		}
	}

	int player_hp = 5;

	Ellipse field{ 640, 360, 500, 300 };
	Vec2 pos{ 640, 360 };
	Vec2 check;
	Vec2 bar;

	const Font font{ 46 };
	double t = 0;
	
	
	
	static constexpr int r = 5;

	Camera2D camera{ pos, 1.0, CameraControl::None_ };
	bool move = true;
	bool end = false;
	bool win = false;
	

	RectF attack1=returnRect(890, 360, 500, 600);
	RectF attack1_2 = returnRect(390, 360, 500, 600);

	Circle attack2_1 = returnCircle(890, 210, 250);
	Circle attack2_2 = returnCircle(390, 210, 250);
	Circle attack2_3 = returnCircle(390, 510, 250);
	Circle attack2_4 = returnCircle(890, 510, 250);
	Circle attack2_5 = returnCircle(640, 360, 250);

	RectF attack3_1 = returnRect(640, 110, 1000, 100);
	RectF attack3_2 = returnRect(640, 610, 1000, 100);

	Circle attack3_3 = returnCircle(140, 360, 1000);
	Circle attack3_4 = returnCircle(1140, 360, 1000);	
    Polygon tr3_3;	
	Polygon tr3_4;

	RectF attack4_1 = returnRect(640, 210, 1000, 100);
	RectF attack4_2 = returnRect(640, 510, 1000, 100);

	RectF attack5_1 = returnRect(640, 310, 1000, 100);
	RectF attack5_2 = returnRect(640, 410, 1000, 100);
	


	bool attack1_check = true;
	bool attack2_check = true;
	bool attack3_check = true;
	bool attack4_check = true;
	bool attack5_check = true;
	bool attack6_check = true;
	bool attack7_check = true;
	bool attack8_check = true;
	bool attack9_check = true;
	bool attack10_check = true;
	bool attack11_check = true;
	bool attack12_check = true;
	bool attack13_check = true;
	bool attack14_check = true;
	bool attack15_check = true;
	

	void update()override {
		
		const double hue = (Scene::Time() * 30);
		if (end == false) {
			Scene::SetBackground(HSV{ hue });
		}

		
		camera.update();
		camera.setTargetCenter(pos);
		const double deltaTime = Scene::DeltaTime();		
		t += deltaTime;

		bar.x = pos.x-32;
		bar.y = pos.y - 75;

		for (int k = 0; k < 10;k++) {
			if (timeStart[k]==true) {
				time[k] += deltaTime;
			}
		}

		if (move == true) {
			if (KeyRight.pressed()) {
				pos.x += Scene::DeltaTime() * 150;
			}
			if (KeyLeft.pressed()) {
				pos.x -= Scene::DeltaTime() * 150;
			}
			if (KeyUp.pressed()) {
				pos.y -= Scene::DeltaTime() * 150;
			}
			if (KeyDown.pressed()) {
				pos.y += Scene::DeltaTime() * 150;
			}
		}

		//攻撃判定追加
		if (3 <= t && attack1_check) {
			attack1_check = false;
			if (Circle{ pos,20 }.intersects(attack1)) {
				player_hp -= 1;
			}
		}

		if (4 <= t && attack2_check) {
			attack2_check = false;
			if (Circle{ pos,20 }.intersects(attack1_2)) {
				player_hp -= 1;
			}
		}

		if (7 <= t && attack3_check) {
			attack3_check = false;
			if (Circle{ pos,20 }.intersects(attack2_1)) {
				player_hp -= 1;
			}
		}

		if (7.25 <= t && attack4_check) {
			attack4_check = false;
			if (Circle{ pos,20 }.intersects(attack2_2)) {
				player_hp -= 1;
			}
		}

		if (7.5 <= t && attack5_check) {
			attack5_check = false;
			if (Circle{ pos,20 }.intersects(attack2_3)) {
				player_hp -= 1;
			}
		}

		if (7.75 <= t && attack6_check) {
			attack6_check = false;
			if (Circle{ pos,20 }.intersects(attack2_4)) {
				player_hp -= 1;
			}
		}

		if (9 <= t && attack7_check) {
			attack7_check = false;
			if (Circle{ pos,20 }.intersects(attack2_5)) {
				player_hp -= 1;
			}
		}

		if (12 <= t && attack8_check) {
			attack8_check = false;
			if (Circle{ pos,20 }.intersects(attack3_1)) {
				player_hp -= 1;
			}
		}

		if (12 <= t && attack9_check) {
			attack9_check = false;
			if (Circle{ pos,20 }.intersects(attack3_2)) {
				player_hp -= 1;
			}
		}

		if (12 <= t && attack10_check) {
			attack10_check = false;
			if (Circle{ pos,20 }.intersects(tr3_3)) {
				player_hp -= 1;
			}
		}

		if (12 <= t && attack11_check) {
			attack11_check = false;
			if (Circle{ pos,20 }.intersects(tr3_4)) {
				player_hp -= 1;
			}
		}

		if (13 <= t && attack12_check) {
			attack12_check = false;
			if (Circle{ pos,20 }.intersects(attack4_1)) {
				player_hp -= 1;
			}
		}

		if (13 <= t && attack13_check) {
			attack13_check = false;
			if (Circle{ pos,20 }.intersects(attack4_2)) {
				player_hp -= 1;
			}
		}

		if (15.5 <= t && attack14_check) {
			attack14_check = false;
			if (Circle{ pos,20 }.intersects(attack5_1)) {
				player_hp -= 1;
			}
		}

		if (14 <= t && attack15_check) {
			attack15_check = false;
			if (Circle{ pos,20 }.intersects(attack5_2)) {
				player_hp -= 1;
			}
		}
			

		if (Circle{ pos,20 }.intersects(field)) {

		}

		//時間追加
		if (0 < t && t < 3) {
			reBool(timeStart[0]);
		}
		if (1 < t && t < 4) {
			reBool(timeStart[1]);
		}
		if (4 < t && t < 7) {
			reBool(timeStart[2]);
		}
		if (4.25 < t && t < 7.25) {
			reBool(timeStart[3]);
		}

		if (4.5 < t && t < 7.5) {
			reBool(timeStart[4]);
		}

		if (4.75 < t && t < 7.75) {
			reBool(timeStart[5]);
		}

		if (6 < t && t < 9) {
			reBool(timeStart[6]);
		}

		if (9 < t && t < 12) {
			reBool(timeStart[7]); 
		}
		if (10 < t && t < 13) {
			reBool(timeStart[8]); 
		}
		if (12.5 < t && t < 15.5) {
			reBool(timeStart[9]);
		}

		
		

		if (t >= 16) {
			win = true;
		}

		if (!(Circle{ pos,20 }.intersects(field))) {									
			player_hp = 0;
		}

		if (player_hp <= 0) {
			move = false;
			end = true;
			t = 0;
			
		}

		if (end == true) {
			if (KeyEnter.down()) {
				changeScene(U"Battle", 0.5s);
			}
		}

		if (win == true) {
			move = false;
			t = 0;
			if (KeyEnter.down()) {
				changeScene(U"Battle", 0.5s);
			}
		}

	}

	void draw() const override {
		
			const auto te = camera.createTransformer();

			field.draw(Color{ 139,69,19 });
			Circle player{ pos,r };

			//攻撃描画追加
			if (0 < t && t < 3) {
				//drawRect(890, 360, time[0],500,600);
				drawDonut(pos.x, pos.y, time[0], 300, 200);
			}

			if (1 < t && t < 4) {
				drawRect(390, 360, time[1], 500, 600);							
			}

			if (4 < t && t < 7) {
				drawCircle(890, 210, time[2], 250);
			}

			if (4.25 < t && t < 7.25) {
				drawCircle(390, 210, time[3], 250);
			}

			if (4.5 < t && t < 7.5) {
				drawCircle(390,510, time[4], 250);
			}

			if (4.75 < t && t < 7.75) {
				drawCircle(890, 510, time[5], 250);
			}
			if (6 < t && t < 9) {
				drawCircle(640, 360, time[6], 250);
			}
			if (9 < t && t < 12) {
				drawRect(640, 110, time[7], 1000, 100);
				drawRect(640, 610, time[7], 1000, 100);
				drawBlethRight(140, 360, time[7], 1000);
				drawBlethLeght(1140, 360, time[7], 1000);
			}
			if (10 < t && t < 13) {
				drawRect(640, 210, time[8], 1000, 100);
				drawRect(640, 510, time[8], 1000, 100);
			}
			if (12.5 < t && t < 15.5) {
				drawRect(640, 310, time[9], 1000, 100);
				drawRect(640, 410, time[9], 1000, 100);
			}
			
			//hpバー
			RectF{ pos.x - 30,pos.y - 45,60,20 }.draw(ColorF(1,1,1)).drawFrame(3);
			RectF{ pos.x - 30,pos.y - 45,player_hp * 20,20 }.draw(ColorF(0, 1, 0));
			player.draw(Color{ 1,0,0 });
		
		
		if (end) {			
			Rect(-500, -500, 3000, 3000).draw(ColorF{ 0,0,0,0.7 });
			font(U"YOU DIED").draw(80,pos.x-200,pos.y-60, ColorF(1, 1, 1));
			font(U"Enterキーでリスタート").draw(50, pos.x - 250, pos.y+40, ColorF(1, 1, 1));
			
		}

		if (win) {
			Rect(-500, -500, 3000, 3000).draw(ColorF{ 0,0,0.3,0.7 });
			font(U"YOU WIN!").draw(80, pos.x - 200, pos.y - 60, ColorF(1, 1, 1));
			font(U"Enterキーでリスタート").draw(50, pos.x - 250, pos.y + 40, ColorF(1, 1, 1));
		}
	}
};


void Main()
{
	Window::Resize(1280, 720);

	App manager;

	manager.add<title>(U"title");
	manager.add<Battle>(U"Battle");

	while (System::Update())
	{
		if (not manager.update())
		{

			break;
		}
	}
}
