
#include "cocos2d.h"
#include "ctime"
#include "stdlib.h"
#include "string.h"
#include "sstream"
#include "cmath"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	void endGame(Ref* _ref);
	void restartGame(Ref* _ref);

private:


	CREATE_FUNC(GameOverScene);
};