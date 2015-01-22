#include "GameMainScene.h"
#include "GameOverScene.h"
#include "ctime"
#include "stdlib.h"
#include "string.h"
#include "sstream"
#include "cmath"
#include "fstream"

USING_NS_CC;


Scene* GameMainScene::createScene()
{
    auto scene = Scene::create();
	auto layer = GameMainScene::create();
    scene->addChild(layer);
    return scene;
}


bool GameMainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();

	CCSprite *backGround = CCSprite::create("background.png");
	backGround->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(backGround);

	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
		{
			mainBox[i][j] = CCSprite::create("b.png");
			mainBox[i][j]->setPosition(ccp(93+173*j,946-173*i));
			this->addChild(mainBox[i][j]);
		}

	CCLOG("1");
	totBox = 0;

	GameMainScene::CreatStartScene();
    
    return true;
}

void GameMainScene::CreatStartScene()
{
	GameMainScene::DefaultClass();
	GameMainScene::CreatBoxSprite();
	GameMainScene::CreatBoxSprite();

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [&](Touch* touch, Event* event){
			Point touchPoint = touch->getLocation(); 
			touch->getLocationInView();
			beginX=touchPoint.x;
			beginY=touchPoint.y;
	
			return true;

};

	listener1->onTouchEnded = [=](Touch* touch, Event* event){
			Point touchPoint = touch->getLocation(); 
			touch->getLocationInView();
			endX=touchPoint.x;
			endY=touchPoint.y;

			if (abs(endX-beginX)>abs(endY-beginY))
				{
					if (endX>beginX)
					{
						CCLOG("right");
						GameMainScene::touchRightorLeft(true);
						CCLOG("creat");
						GameMainScene::CreatBoxSprite();
									for (int i = 0;i<4;i++)
		CCLOG("%d %d %d %d",number[i][0],number[i][1],number[i][2],number[i][3]);

					}
					else
					{
						GameMainScene::touchRightorLeft(false);
						GameMainScene::CreatBoxSprite();
									for (int i = 0;i<4;i++)
		CCLOG("%d %d %d %d",number[i][0],number[i][1],number[i][2],number[i][3]);
					}
				}
			else 
				{
					if (endY>beginY)
					{
						GameMainScene::touchUporDown(true);
						GameMainScene::CreatBoxSprite();
									for (int i = 0;i<4;i++)
		CCLOG("%d %d %d %d",number[i][0],number[i][1],number[i][2],number[i][3]);
					}
					else
					{
						GameMainScene::touchUporDown(false);
						GameMainScene::CreatBoxSprite();
									for (int i = 0;i<4;i++)
		CCLOG("%d %d %d %d",number[i][0],number[i][1],number[i][2],number[i][3]);
					}
				}
    
			};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1,this);
	CCLOG("2");
}

void GameMainScene::DefaultClass()
{
	for (int i = 0;i<4;i++)
		for (int j = 0;j<4;j++)
		{
			boxNumber[i][j].stringValue = "0";
			boxNumber[i][j].intValue = 0;
			number[i][j] = 0;
		}
		test = 2;
		
}


void GameMainScene::touchRightorLeft(bool flag)
{
	int j,vec,tot = 0;
	bool merge;
	if (flag) vec=1;else vec=-1;
	for (int i = 0;i<4;i++)
	{
		if (flag) j=3;else j=0;
		for (j;(j>=0)&&(j<=3);j=j-vec)
		{
			if ((j+vec<=3)&&(j+vec>=0)&&(number[i][j] != 0))
			{
				for (int n = j+vec;(n>=0)&&(n<=3);n = n + vec)
				{
					if (number[i][j] == number[i][n]) 
					{
						merge = true;
						if (abs(n-j)>1)
						{
							for (int m=j+vec;m!=n;m=m+vec) if (number[i][m] != 0) merge = false;
						}
						if (flag&&merge) GameMainScene::actionBox(true,"right",i,j,abs(n-j)); 
						if ((!flag)&&(merge)) GameMainScene::actionBox(true,"left",i,j,abs(n-j));
						break;
					}

					if (((n+vec<0)||(n+vec>3)||((number[i][j] != number[i][n+vec])&&(number[i][n+vec] != 0)))&&(number[i][n] == 0))
					{
						if (flag) GameMainScene::actionBox(false,"right",i,j,abs(n-j)); else GameMainScene::actionBox(false,"left",i,j,abs(n-j));
						break;
					}

				}
			}
		}
	}
}

void GameMainScene::touchUporDown(bool flag)
{
	int i,vec,tot = 0;
	bool merge;
	if (flag) vec=-1;else vec=1;
	for (int j = 0;j<4;j++)
	{
		if (flag) i=0;else i=3;
		for (i;(i>=0)&&(i<=3);i=i-vec)
		{
			if ((i+vec<=3)&&(i+vec>=0)&&(number[i][j] != 0))
			{
				for (int n = i+vec;(n>=0)&&(n<=3);n = n + vec)
				{
					if (number[i][j] == number[n][j]) 
					{
						merge = true;
						if (abs(n-i)>1)
						{
							for (int m=i+vec;m!=n;m=m+vec) if (number[m][j] != 0) merge = false;
						}
						if ((flag)&&(merge)) GameMainScene::actionBox(true,"up",i,j,abs(n-i)); 
						if ((!flag)&&(merge)) GameMainScene::actionBox(true,"down",i,j,abs(n-i));
						break;
					}

					if (((n+vec<0)||(n+vec>3)||((number[i][j] != number[n+vec][j])&&(number[n+vec][j] != 0)))&&(number[n][j] == 0))
					{
						if (flag) GameMainScene::actionBox(false,"up",i,j,abs(n-i)); else GameMainScene::actionBox(false,"down",i,j,abs(n-i));
						break;
					}
				}
			}
		}
	}
}

void GameMainScene::actionBox(bool isMerge,std::string vet,int x,int y,int dis)
{
	bool nextStep = false;
	if (vet == "right")
	{
		if (!isMerge)
		{
			mainBox[x][y]->setTexture("b.png");  CCLOG("D1");
			int t = number[x][y];
			number[x][y+dis] = t;
			number[x][y] = 0;
			mainBox[x][y+dis]->setTexture(getString(number[x][y+dis]));CCLOG("#1");
					
		}
		else
		{

			mainBox[x][y]->setTexture("b.png"); CCLOG("D2"); 
			number[x][y] = 0;
			number[x][y+dis] = number[x][y+dis] * 2;
			mainBox[x][y+dis]->setTexture(getString(number[x][y+dis]));CCLOG("2#");
			totBox--;
			
		}
		CCLOG("get2");
	}

	if (vet == "left")
	{
		if (!isMerge)
		{
			mainBox[x][y]->setTexture("b.png"); CCLOG("D3"); 
			int t = number[x][y];
			number[x][y-dis] = t;
			number[x][y] = 0;
			mainBox[x][y-dis]->setTexture(getString(number[x][y-dis]));CCLOG("3#");

			
		}
		else
		{
			mainBox[x][y]->setTexture("b.png"); CCLOG("D4"); 
			number[x][y] = 0;
			number[x][y-dis] = number[x][y-dis] * 2;
			mainBox[x][y-dis]->setTexture(getString(number[x][y-dis]));CCLOG("4#");
			totBox--;

		}
	}

	if (vet == "up")
	{
		if (!isMerge)
		{
			mainBox[x][y]->setTexture("b.png"); CCLOG("D5"); 
			int t = number[x][y];
			number[x-dis][y] = t;
			number[x][y] = 0;
			mainBox[x-dis][y]->setTexture(getString(number[x-dis][y]));CCLOG("5#");


		}
		else
		{
			mainBox[x][y]->setTexture("b.png"); CCLOG("D6");
			number[x][y] = 0;
			number[x-dis][y] = number[x-dis][y] * 2;
			mainBox[x-dis][y]->setTexture(getString(number[x-dis][y]));CCLOG("6#");
			totBox--;

		}
	}

	if (vet == "down")
	{
		if (!isMerge)
		{
			mainBox[x][y]->setTexture("b.png");  CCLOG("D7");
			int t = number[x][y];
			number[x+dis][y] = t;
			number[x][y] = 0;
			mainBox[x+dis][y]->setTexture(getString(number[x+dis][y]));CCLOG("7#");

		}
		else
		{
			mainBox[x][y]->setTexture("b.png"); CCLOG("D8"); 
			number[x][y] = 0;
			number[x+dis][y] = number[x+dis][y] * 2;
			mainBox[x+dis][y]->setTexture(getString(number[x+dis][y]));CCLOG("8#");
			totBox--;
		}
	}

}

void GameMainScene::CreatBoxSprite()
{
	if (totBox == 16) 
		{
			GameMainScene::toGameOverScene();
			return;
		}
	std::srand(unsigned(time(0)));
	int tot,randN = (rand()+1)%(16 - totBox) + 1;
	tot = 0;
	for (int i = 0;i<4;i++)
		for (int j = 0;j<4;j++)
		{
			if (number[i][j]==0) tot++;
			if (tot == randN) 
			{
				number[i][j] = 2;
				mainBox[i][j]->setTexture(getString(number[i][j]));CCLOG("#9");
				totBox++;
				return;
			}
		}
}

std::string GameMainScene::getString(int intvalue)
{
	char t[100];
	sprintf(t, "%d", intvalue);
	std::string s;
	s = t;
	s = s + ".png";
	return s;
}

void GameMainScene::toGameOverScene()
{
	int max=0;
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			if (number[i][j]>max) max = number[i][j];
	std::ofstream bestpoint;
	bestpoint.open("point.data");
	bestpoint<<max;
	bestpoint.close();
	CCScene* sceneChange = GameOverScene::createScene();
	auto reScene = CCTransitionCrossFade::create(1,GameOverScene::createScene());
	CCDirector::sharedDirector()->replaceScene(reScene);

}