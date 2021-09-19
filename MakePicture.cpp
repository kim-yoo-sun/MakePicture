#include <bangtal>
using namespace bangtal;
int click_loc[2][4] = { 0, };
int checkIn(int x, int y) {
	int temp = 0;
	if ((200 < x && x < 200 + 180) && (760 < y && y < 760 + 180))
	{
		temp = 1;
	}
	else if ((200 + 180 < x && x < 200 + 360) && (760 < y && y < 760 + 180))
	{
		temp = 2;
	}
	else if ((200 + 360 < x && x < 200 + 540) && (760 < y && y < 760 + 180))
	{
		temp = 3;
	}
	else if ((200 < x && x < 200 + 180) && (580 < y && y < 580 + 180))
	{
		temp = 4;
	}
	else if ((200 + 180 < x && x < 200 + 360) && (580 < y && y < 580 + 180))
	{
		temp = 5;
	}
	else if ((200 + 360 < x && x < 200 + 540) && (580 < y && y < 580 + 180))
	{
		temp = 6;
	}
	else if ((200 < x && x < 200 + 180) && (400 < y && y < 400 + 180))
	{
		temp = 7;
	}
	else if ((200 + 180 < x && x < 200 + 360) && (400 < y && y < 400 + 180))
	{
		temp = 8;
	}
	else if ((200 + 360 < x && x < 200 + 540) && (400 < y && y < 400 + 180))
	{
		temp = 9;
	}
	return temp;
}

int main()
{
	int location[9] = { 0, };
	int tmp = 0;
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	// 장면을 생성한다.
	ScenePtr scene = Scene::create("Initial Picture", "Images/0_0.png");
	
	auto object_scene = Object::create("Images/0_0.png", scene, 0, 0);
	auto ob1_1 = Object::create("Images/1_1.png", scene, 200, 760);auto ob1_2 = Object::create("Images/1_2.png", scene, 380, 760);auto ob1_3 = Object::create("Images/1_3.png", scene, 560, 760);
	auto ob2_1 = Object::create("Images/2_1.png", scene, 200, 580);auto ob2_2 = Object::create("Images/2_2.png", scene, 380, 580);auto ob2_3 = Object::create("Images/2_3.png", scene, 560, 580);
	auto ob3_1 = Object::create("Images/3_1.png", scene, 200, 400);auto ob3_2 = Object::create("Images/3_2.png", scene, 380, 400);auto ob3_3 = Object::create("Images/3_3.png", scene, 560, 400);
	
	// 123
	// 456
	// 789

	location[0] = 9; location[1] = 1; location[2] = 3;
	location[3] = 4; location[4] = 7; location[5] = 5;
	location[6] = 2; location[7] = 6; location[8] = 8;

	ob3_3->locate(scene, 200, 760);ob1_1->locate(scene, 380, 760);ob1_3->locate(scene, 560, 760);
	ob2_1->locate(scene, 200, 580);ob3_1->locate(scene, 380, 580);ob2_2->locate(scene, 560, 580);
	ob1_2->locate(scene, 200, 400);ob2_3->locate(scene, 380, 400);ob3_2->locate(scene, 560, 400);
	// 이 기본 세팅이고, 초기에는 913, 475, 268로 위치 시켜서 시작

	ob1_1->setScale(0.5);ob1_2->setScale(0.5);ob1_3->setScale(0.5);
	ob2_1->setScale(0.5);ob2_2->setScale(0.5);ob2_3->setScale(0.5);
	ob3_1->setScale(0.5);ob3_2->setScale(0.5);ob3_3->setScale(0.5);

	auto startB = Object::create("Images/start.png", scene, 800, 570);
	auto endB = Object::create("Images/end.png", scene, 800, 500);
	auto timer = Timer::create(30.f);

	startB->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		startB->hide();
		showMessage("해당 놀이는 그림을 맞추는 놀이입니다.\n바꾸고 싶은 사진을 2번 클릭하고 그 사진과 교체하고 싶은 사진을 2번 클릭하시면 됩니다.\n즐거운 놀이 되세요 :)\n");
		timer->start();
		
		startB->setImage("Images/restart.png");

		return true;
		});

	endB->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
		});

	showTimer(timer);
	timer->setOnTimerCallback([&](TimerPtr)->bool {
		showMessage("Picture doesn't look good :(");
		startB->show();
		timer->set(30.f);
		return true;
		});

	int cnt = 0, k = 0;
	object_scene->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if ((cnt % 2) == 1)
		{
			click_loc[0][0] = checkIn(x, y);
			click_loc[0][1] = k;
		}
		else
		{
			click_loc[1][0] = checkIn(x, y);
			click_loc[1][1] = k;
		}

		if ((cnt % 2) == 0)
		{
			// location 정보 스왑
			location[click_loc[0][0] - 1] = click_loc[1][1];
			location[click_loc[1][0] - 1] = click_loc[0][1];

			// 사진 위치 스왑
			if (click_loc[0][1] == 1)
			{
				if (click_loc[1][0] == 1)
				{
					ob1_1->locate(scene, 200, 760);
				}
				if (click_loc[1][0] == 2)
				{
					ob1_1->locate(scene, 380, 760);
				}
				if (click_loc[1][0] == 3)
				{
					ob1_1->locate(scene, 560, 760);
				}
				if (click_loc[1][0] == 4)
				{
					ob1_1->locate(scene, 200, 580);
				}
				if (click_loc[1][0] == 5)
				{
					ob1_1->locate(scene, 380, 580);
				}
				if (click_loc[1][0] == 6)
				{
					ob1_1->locate(scene, 560, 580);
				}
				if (click_loc[1][0] == 7)
				{
					ob1_1->locate(scene, 200, 400);
				}
				if (click_loc[1][0] == 8)
				{
					ob1_1->locate(scene, 380, 400);
				}
				if (click_loc[1][0] == 9)
				{
					ob1_1->locate(scene, 560, 400);
				}
			}
			if (click_loc[0][1] == 2)
			{
				if (click_loc[1][0] == 1)
				{
					ob1_2->locate(scene, 200, 760);
				}
				if (click_loc[1][0] == 2)
				{
					ob1_2->locate(scene, 380, 760);
				}
				if (click_loc[1][0] == 3)
				{
					ob1_2->locate(scene, 560, 760);
				}
				if (click_loc[1][0] == 4)
				{
					ob1_2->locate(scene, 200, 580);
				}
				if (click_loc[1][0] == 5)
				{
					ob1_2->locate(scene, 380, 580);
				}
				if (click_loc[1][0] == 6)
				{
					ob1_2->locate(scene, 560, 580);
				}
				if (click_loc[1][0] == 7)
				{
					ob1_2->locate(scene, 200, 400);
				}
				if (click_loc[1][0] == 8)
				{
					ob1_2->locate(scene, 380, 400);
				}
				if (click_loc[1][0] == 9)
				{
					ob1_2->locate(scene, 560, 400);
				}
			}
			if (click_loc[0][1] == 3)
			{
				if (click_loc[1][0] == 1)
				{
					ob1_3->locate(scene, 200, 760);
				}
				if (click_loc[1][0] == 2)
				{
					ob1_3->locate(scene, 380, 760);
				}
				if (click_loc[1][0] == 3)
				{
					ob1_3->locate(scene, 560, 760);
				}
				if (click_loc[1][0] == 4)
				{
					ob1_3->locate(scene, 200, 580);
				}
				if (click_loc[1][0] == 5)
				{
					ob1_3->locate(scene, 380, 580);
				}
				if (click_loc[1][0] == 6)
				{
					ob1_3->locate(scene, 560, 580);
				}
				if (click_loc[1][0] == 7)
				{
					ob1_3->locate(scene, 200, 400);
				}
				if (click_loc[1][0] == 8)
				{
					ob1_3->locate(scene, 380, 400);
				}
				if (click_loc[1][0] == 9)
				{
					ob1_3->locate(scene, 560, 400);
				}
			}
			if (click_loc[0][1] == 4)
			{
				if (click_loc[1][0] == 1)
				{
					ob2_1->locate(scene, 200, 760);
				}
				if (click_loc[1][0] == 2)
				{
					ob2_1->locate(scene, 380, 760);
				}
				if (click_loc[1][0] == 3)
				{
					ob2_1->locate(scene, 560, 760);
				}
				if (click_loc[1][0] == 4)
				{
					ob2_1->locate(scene, 200, 580);
				}
				if (click_loc[1][0] == 5)
				{
					ob2_1->locate(scene, 380, 580);
				}
				if (click_loc[1][0] == 6)
				{
					ob2_1->locate(scene, 560, 580);
				}
				if (click_loc[1][0] == 7)
				{
					ob2_1->locate(scene, 200, 400);
				}
				if (click_loc[1][0] == 8)
				{
					ob2_1->locate(scene, 380, 400);
				}
				if (click_loc[1][0] == 9)
				{
					ob2_1->locate(scene, 560, 400);
				}
			}
			if (click_loc[0][1] == 5)
			{
				if (click_loc[1][0] == 1)
				{
					ob2_2->locate(scene, 200, 760);
				}
				if (click_loc[1][0] == 2)
				{
					ob2_2->locate(scene, 380, 760);
				}
				if (click_loc[1][0] == 3)
				{
					ob2_2->locate(scene, 560, 760);
				}
				if (click_loc[1][0] == 4)
				{
					ob2_2->locate(scene, 200, 580);
				}
				if (click_loc[1][0] == 5)
				{
					ob2_2->locate(scene, 380, 580);
				}
				if (click_loc[1][0] == 6)
				{
					ob2_2->locate(scene, 560, 580);
				}
				if (click_loc[1][0] == 7)
				{
					ob2_2->locate(scene, 200, 400);
				}
				if (click_loc[1][0] == 8)
				{
					ob2_2->locate(scene, 380, 400);
				}
				if (click_loc[1][0] == 9)
				{
					ob2_2->locate(scene, 560, 400);
				}
			}
			if (click_loc[0][1] == 6)
			{
				if (click_loc[1][0] == 1)
				{
					ob2_3->locate(scene, 200, 760);
				}
				if (click_loc[1][0] == 2)
				{
					ob2_3->locate(scene, 380, 760);
				}
				if (click_loc[1][0] == 3)
				{
					ob2_3->locate(scene, 560, 760);
				}
				if (click_loc[1][0] == 4)
				{
					ob2_3->locate(scene, 200, 580);
				}
				if (click_loc[1][0] == 5)
				{
					ob2_3->locate(scene, 380, 580);
				}
				if (click_loc[1][0] == 6)
				{
					ob2_3->locate(scene, 560, 580);
				}
				if (click_loc[1][0] == 7)
				{
					ob2_3->locate(scene, 200, 400);
				}
				if (click_loc[1][0] == 8)
				{
					ob2_3->locate(scene, 380, 400);
				}
				if (click_loc[1][0] == 9)
				{
					ob2_3->locate(scene, 560, 400);
				}
			}
			if (click_loc[0][1] == 7)
			{
				if (click_loc[1][0] == 1)
				{
					ob3_1->locate(scene, 200, 760);
				}
				if (click_loc[1][0] == 2)
				{
					ob3_1->locate(scene, 380, 760);
				}
				if (click_loc[1][0] == 3)
				{
					ob3_1->locate(scene, 560, 760);
				}
				if (click_loc[1][0] == 4)
				{
					ob3_1->locate(scene, 200, 580);
				}
				if (click_loc[1][0] == 5)
				{
					ob3_1->locate(scene, 380, 580);
				}
				if (click_loc[1][0] == 6)
				{
					ob3_1->locate(scene, 560, 580);
				}
				if (click_loc[1][0] == 7)
				{
					ob3_1->locate(scene, 200, 400);
				}
				if (click_loc[1][0] == 8)
				{
					ob3_1->locate(scene, 380, 400);
				}
				if (click_loc[1][0] == 9)
				{
					ob3_1->locate(scene, 560, 400);
				}
			}
			if (click_loc[0][1] == 8)
			{
				if (click_loc[1][0] == 1)
				{
					ob3_2->locate(scene, 200, 760);
				}
				if (click_loc[1][0] == 2)
				{
					ob3_2->locate(scene, 380, 760);
				}
				if (click_loc[1][0] == 3)
				{
					ob3_2->locate(scene, 560, 760);
				}
				if (click_loc[1][0] == 4)
				{
					ob3_2->locate(scene, 200, 580);
				}
				if (click_loc[1][0] == 5)
				{
					ob3_2->locate(scene, 380, 580);
				}
				if (click_loc[1][0] == 6)
				{
					ob3_2->locate(scene, 560, 580);
				}
				if (click_loc[1][0] == 7)
				{
					ob3_2->locate(scene, 200, 400);
				}
				if (click_loc[1][0] == 8)
				{
					ob3_2->locate(scene, 380, 400);
				}
				if (click_loc[1][0] == 9)
				{
					ob3_2->locate(scene, 560, 400);
				}
			}
			if (click_loc[0][1] == 9)
			{
				if (click_loc[1][0] == 1)
				{
					ob3_3->locate(scene, 200, 760);
				}
				if (click_loc[1][0] == 2)
				{
					ob3_3->locate(scene, 380, 760);
				}
				if (click_loc[1][0] == 3)
				{
					ob3_3->locate(scene, 560, 760);
				}
				if (click_loc[1][0] == 4)
				{
					ob3_3->locate(scene, 200, 580);
				}
				if (click_loc[1][0] == 5)
				{
					ob3_3->locate(scene, 380, 580);
				}
				if (click_loc[1][0] == 6)
				{
					ob3_3->locate(scene, 560, 580);
				}
				if (click_loc[1][0] == 7)
				{
					ob3_3->locate(scene, 200, 400);
				}
				if (click_loc[1][0] == 8)
				{
					ob3_3->locate(scene, 380, 400);
				}
				if (click_loc[1][0] == 9)
				{
					ob3_3->locate(scene, 560, 400);
				}
			}
			if (click_loc[1][1] == 1)
			{
				if (click_loc[0][0] == 1)
				{
					ob1_1->locate(scene, 200, 760);
				}
				if (click_loc[0][0] == 2)
				{
					ob1_1->locate(scene, 380, 760);
				}
				if (click_loc[0][0] == 3)
				{
					ob1_1->locate(scene, 560, 760);
				}
				if (click_loc[0][0] == 4)
				{
					ob1_1->locate(scene, 200, 580);
				}
				if (click_loc[0][0] == 5)
				{
					ob1_1->locate(scene, 380, 580);
				}
				if (click_loc[0][0] == 6)
				{
					ob1_1->locate(scene, 560, 580);
				}
				if (click_loc[0][0] == 7)
				{
					ob1_1->locate(scene, 200, 400);
				}
				if (click_loc[0][0] == 8)
				{
					ob1_1->locate(scene, 380, 400);
				}
				if (click_loc[0][0] == 9)
				{
					ob1_1->locate(scene, 560, 400);
				}
			}
			if (click_loc[1][1] == 2)
			{
				if (click_loc[0][0] == 1)
				{
					ob1_2->locate(scene, 200, 760);
				}
				if (click_loc[0][0] == 2)
				{
					ob1_2->locate(scene, 380, 760);
				}
				if (click_loc[0][0] == 3)
				{
					ob1_2->locate(scene, 560, 760);
				}
				if (click_loc[0][0] == 4)
				{
					ob1_2->locate(scene, 200, 580);
				}
				if (click_loc[0][0] == 5)
				{
					ob1_2->locate(scene, 380, 580);
				}
				if (click_loc[0][0] == 6)
				{
					ob1_2->locate(scene, 560, 580);
				}
				if (click_loc[0][0] == 7)
				{
					ob1_2->locate(scene, 200, 400);
				}
				if (click_loc[0][0] == 8)
				{
					ob1_2->locate(scene, 380, 400);
				}
				if (click_loc[0][0] == 9)
				{
					ob1_2->locate(scene, 560, 400);
				}
			}
			if (click_loc[1][1] == 3)
			{
				if (click_loc[0][0] == 1)
				{
					ob1_3->locate(scene, 200, 760);
				}
				if (click_loc[0][0] == 2)
				{
					ob1_3->locate(scene, 380, 760);
				}
				if (click_loc[0][0] == 3)
				{
					ob1_3->locate(scene, 560, 760);
				}
				if (click_loc[0][0] == 4)
				{
					ob1_3->locate(scene, 200, 580);
				}
				if (click_loc[0][0] == 5)
				{
					ob1_3->locate(scene, 380, 580);
				}
				if (click_loc[0][0] == 6)
				{
					ob1_3->locate(scene, 560, 580);
				}
				if (click_loc[0][0] == 7)
				{
					ob1_3->locate(scene, 200, 400);
				}
				if (click_loc[0][0] == 8)
				{
					ob1_3->locate(scene, 380, 400);
				}
				if (click_loc[0][0] == 9)
				{
					ob1_3->locate(scene, 560, 400);
				}
			}
			if (click_loc[1][1] == 4)
			{
				if (click_loc[0][0] == 1)
				{
					ob2_1->locate(scene, 200, 760);
				}
				if (click_loc[0][0] == 2)
				{
					ob2_1->locate(scene, 380, 760);
				}
				if (click_loc[0][0] == 3)
				{
					ob2_1->locate(scene, 560, 760);
				}
				if (click_loc[0][0] == 4)
				{
					ob2_1->locate(scene, 200, 580);
				}
				if (click_loc[0][0] == 5)
				{
					ob2_1->locate(scene, 380, 580);
				}
				if (click_loc[0][0] == 6)
				{
					ob2_1->locate(scene, 560, 580);
				}
				if (click_loc[0][0] == 7)
				{
					ob2_1->locate(scene, 200, 400);
				}
				if (click_loc[0][0] == 8)
				{
					ob2_1->locate(scene, 380, 400);
				}
				if (click_loc[0][0] == 9)
				{
					ob2_1->locate(scene, 560, 400);
				}
			}
			if (click_loc[1][1] == 5)
			{
				if (click_loc[0][0] == 1)
				{
					ob2_2->locate(scene, 200, 760);
				}
				if (click_loc[0][0] == 2)
				{
					ob2_2->locate(scene, 380, 760);
				}
				if (click_loc[0][0] == 3)
				{
					ob2_2->locate(scene, 560, 760);
				}
				if (click_loc[0][0] == 4)
				{
					ob2_2->locate(scene, 200, 580);
				}
				if (click_loc[0][0] == 5)
				{
					ob2_2->locate(scene, 380, 580);
				}
				if (click_loc[0][0] == 6)
				{
					ob2_2->locate(scene, 560, 580);
				}
				if (click_loc[0][0] == 7)
				{
					ob2_2->locate(scene, 200, 400);
				}
				if (click_loc[0][0] == 8)
				{
					ob2_2->locate(scene, 380, 400);
				}
				if (click_loc[0][0] == 9)
				{
					ob2_2->locate(scene, 560, 400);
				}
			}
			if (click_loc[1][1] == 6)
			{
				if (click_loc[0][0] == 1)
				{
					ob2_3->locate(scene, 200, 760);
				}
				if (click_loc[0][0] == 2)
				{
					ob2_3->locate(scene, 380, 760);
				}
				if (click_loc[0][0] == 3)
				{
					ob2_3->locate(scene, 560, 760);
				}
				if (click_loc[0][0] == 4)
				{
					ob2_3->locate(scene, 200, 580);
				}
				if (click_loc[0][0] == 5)
				{
					ob2_3->locate(scene, 380, 580);
				}
				if (click_loc[0][0] == 6)
				{
					ob2_3->locate(scene, 560, 580);
				}
				if (click_loc[0][0] == 7)
				{
					ob2_3->locate(scene, 200, 400);
				}
				if (click_loc[0][0] == 8)
				{
					ob2_3->locate(scene, 380, 400);
				}
				if (click_loc[0][0] == 9)
				{
					ob2_3->locate(scene, 560, 400);
				}
			}
			if (click_loc[1][1] == 7)
			{
				if (click_loc[0][0] == 1)
				{
					ob3_1->locate(scene, 200, 760);
				}
				if (click_loc[0][0] == 2)
				{
					ob3_1->locate(scene, 380, 760);
				}
				if (click_loc[0][0] == 3)
				{
					ob3_1->locate(scene, 560, 760);
				}
				if (click_loc[0][0] == 4)
				{
					ob3_1->locate(scene, 200, 580);
				}
				if (click_loc[0][0] == 5)
				{
					ob3_1->locate(scene, 380, 580);
				}
				if (click_loc[0][0] == 6)
				{
					ob3_1->locate(scene, 560, 580);
				}
				if (click_loc[0][0] == 7)
				{
					ob3_1->locate(scene, 200, 400);
				}
				if (click_loc[0][0] == 8)
				{
					ob3_1->locate(scene, 380, 400);
				}
				if (click_loc[0][0] == 9)
				{
					ob3_1->locate(scene, 560, 400);
				}
			}
			if (click_loc[1][1] == 8)
			{
				if (click_loc[0][0] == 1)
				{
					ob3_2->locate(scene, 200, 760);
				}
				if (click_loc[0][0] == 2)
				{
					ob3_2->locate(scene, 380, 760);
				}
				if (click_loc[0][0] == 3)
				{
					ob3_2->locate(scene, 560, 760);
				}
				if (click_loc[0][0] == 4)
				{
					ob3_2->locate(scene, 200, 580);
				}
				if (click_loc[0][0] == 5)
				{
					ob3_2->locate(scene, 380, 580);
				}
				if (click_loc[0][0] == 6)
				{
					ob3_2->locate(scene, 560, 580);
				}
				if (click_loc[0][0] == 7)
				{
					ob3_2->locate(scene, 200, 400);
				}
				if (click_loc[0][0] == 8)
				{
					ob3_2->locate(scene, 380, 400);
				}
				if (click_loc[0][0] == 9)
				{
					ob3_2->locate(scene, 560, 400);
				}
			}
			if (click_loc[1][1] == 9)
			{
				if (click_loc[0][0] == 1)
				{
					ob3_3->locate(scene, 200, 760);
				}
				if (click_loc[0][0] == 2)
				{
					ob3_3->locate(scene, 380, 760);
				}
				if (click_loc[0][0] == 3)
				{
					ob3_3->locate(scene, 560, 760);
				}
				if (click_loc[0][0] == 4)
				{
					ob3_3->locate(scene, 200, 580);
				}
				if (click_loc[0][0] == 5)
				{
					ob3_3->locate(scene, 380, 580);
				}
				if (click_loc[0][0] == 6)
				{
					ob3_3->locate(scene, 560, 580);
				}
				if (click_loc[0][0] == 7)
				{
					ob3_3->locate(scene, 200, 400);
				}
				if (click_loc[0][0] == 8)
				{
					ob3_3->locate(scene, 380, 400);
				}
				if (click_loc[0][0] == 9)
				{
					ob3_3->locate(scene, 560, 400);
				}
			}

			// 결과 확인
			if (location[0] == 1 && location[1] == 2 && location[2] == 3 && location[3] == 4 && location[4] == 5 && location[5] == 6 && location[6] == 7 && location[7] == 8 && location[8] == 9)
			{
				showMessage("You made the right picture!! :)"); printf("종료까지 클릭을 총 %d만큼 하셨습니다.", cnt);
				startB->show();
			}
		}
		if (cnt % 2 == 0)
		{
			ob1_1->show(); ob1_2->show(); ob1_3->show();
			ob2_1->show(); ob2_2->show(); ob2_3->show();
			ob3_1->show(); ob3_2->show(); ob3_3->show();
		}
		return true;
		});

	ob1_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		cnt++;
		ob1_1->hide();
		k = 1;
		return true;
		});
	ob1_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		cnt++;
		ob1_2->hide();
		k = 2;
		return true;
		});
	ob1_3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		cnt++;
		ob1_3->hide();
		k = 3;
		return true;
		});
	ob2_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		cnt++;
		ob2_1->hide();
		k = 4;
		return true;
		});
	ob2_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		cnt++;
		ob2_2->hide();
		k = 5;
		return true;
		});
	ob2_3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		cnt++;
		ob2_3->hide();
		k = 6;
		return true;
		});
	ob3_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		cnt++;
		ob3_1->hide();
		k = 7;
		return true;
		});
	ob3_2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		cnt++;
		ob3_2->hide();
		k = 8;
		return true;
		});
	ob3_3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		cnt++;
		ob3_3->hide();
		k = 9;
		return true;
		});
	startGame(scene);
	return 0;
}