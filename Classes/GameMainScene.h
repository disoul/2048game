#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ctime"
#include "stdlib.h"
#include "string.h"
#include "sstream"
#include "cmath"
#include "fstream"

class GameMainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	void DefaultClass();
	void CreatBoxSprite();
	void GoGame();
	void touchRightorLeft(bool flag);
	void touchUporDown(bool flag);
	void actionBox(bool isMerge,std::string vet,int x,int y,int dis);
	void CreatStartScene();
	void toGameOverScene();

	std::string getString(int intvalue);


private:
    int beginX,beginY,endX,endY,totBox;
	struct NString
	{
		std::string stringValue;;
		int intValue;
	} boxNumber[4][4];
	int number[4][4];
	cocos2d::CCString* stringBox[4][4];
	cocos2d::CCLabelTTF* numberBox[4][4];
	cocos2d::CCSprite* mainBox[4][4];
	int test;

	CREATE_FUNC(GameMainScene);
};

#endif // __HELLOWORLD_SCENE_H__

