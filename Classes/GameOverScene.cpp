#include "GameMainScene.h"
#include "GameOverScene.h"
#include "ctime"
#include "stdlib.h"
#include "string.h"
#include "sstream"
#include "cmath"
#include "fstream"

USING_NS_CC;


Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
	auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}


bool GameOverScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	CCSprite *backGround = CCSprite::create("gg.png");
	backGround->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(backGround);

	std::ifstream bestpoint;
	bestpoint.open("point.data");
	int p;
	bestpoint>>p;
	bestpoint.close();
	char t[100];
	sprintf(t, "%d", p);
	std::string s;
	s = t;
	
	CCLabelTTF  *Npoint = CCLabelTTF::create(s,"/font/BRLNSDB.TTF",100);
	Npoint->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(Npoint);

	CCMenuItemImage* endGameButtum = CCMenuItemImage::create("exit.png","exit.png","exit.png",this,menu_selector(GameOverScene::endGame));
	endGameButtum->setPosition(ccp(visibleSize.width/2+100,visibleSize.height/2-100));

	CCMenuItemImage* restartGameButtum = CCMenuItemImage::create("again.png","restart.png","again.png",this,menu_selector(GameOverScene::restartGame));
	restartGameButtum->setPosition(ccp(visibleSize.width/2-100,visibleSize.height/2-100));

	CCMenu *Menu = CCMenu::create(endGameButtum,restartGameButtum,NULL);
	Menu->setPosition(ccp(0,0));
	this->addChild(Menu);
    
    return true;
}

void GameOverScene::endGame(Ref* _ref)
{
	Director::getInstance()->end();
}

void GameOverScene::restartGame(Ref* _ref)
{
	auto reScene = CCTransitionFade::create(1,GameMainScene::createScene());
	CCDirector::sharedDirector()->replaceScene(reScene);
}