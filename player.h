#pragma once
#include "gameNode.h"
#include "playerUI.h"
#include "playerBullet.h"

#define PLAYERFPS 13
#define PLAYERSPEED 5

enum PLAYERSTATE
{
	PLAYER_IDLE = 0,
	PLAYER_MOVE,
	PLAYER_MOVE_BREAK,
	PLAYER_THROW_AIM,
	PLAYER_THROW_HOLD,
	PLAYER_THROW_HOLD_MOVE,
	PLAYER_THROW_1,
	PLAYER_THROW_2,
	PLAYER_ATTACK_COMBO_1,
	PLAYER_ATTACK_COMBO_2,
	PLAYER_ATTACK_COMBO_FINISH,
	PLAYER_DEFENSE,
	PLAYER_AVOID,
	PLAYER_ATTACKED,
	PLAYER_TELEPORT, 
	PLAYER_CHARGE,
	PLAYER_SKILL_FIRE,
};
enum PLAYERDIRECTION
{
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT,
};

struct tagPlayer
{
	D2D1_RECT_F rc;
	D2D1_RECT_F attackRc;
	image* effImage;
	image* image;
	animation* motion;
	animation* effAni;
	PLAYERSTATE state;
	PLAYERDIRECTION direction;
	playerBullet* bullet;
	string name;
	float x, y;
	float speed;
	float avoidPower;
	float jumpPower;
	float gravity;
	float angle;
	int idX, idY;
	int HP;
	int maxHP;
	int MP;
	int maxMP;
	int damage;
	int money;
	float alphaValue;
	int level;
	int exp;
	int maxExp;
};

class player : public gameNode
{
private:
	tagPlayer _player;
	D2D1_ELLIPSE _attackRangeRc;
	ELLIPSE _cursorChangeEll;
	image* _effect;
	playerUI* _playerUI;
	HCURSOR _cursor;
	HCURSOR _cursor2;

	POINT _effPos;
	int _effectFrameX, _effectFrameY;
	int _effectMaxFrameX, _effectMaxFrameY;
	int _effectAngle;
	int _effectCount;
	int _effSelect;
	bool _effCopy;
	bool _effectPlay;

	int _playerAlphaCount;
	float _effSpeed;

	bool _isAttack;
	bool _isThrowAttack;
	bool _isMove;
	bool _isLea;
	bool _isRight;
	bool _isAvoid;
	bool _isAttacked;
	bool _isCharge;
	bool _isSkill;
	bool _effSkillStart;

	int _effOldTime;

	bool _nobKey[4];

	int _effCount;


	//대각선 무브브레이크 상태를 설정하기위한 필요한 변수들
	int _oldTime[4];
	int _breakCheck[4];
	//원거리공격 패턴을 바꾸기위한 변수
	int _attackTimeKeyUp;
	int _attackTimeKeyDown;
	//원거리공격 패턴을 바꾸기위한 변수
	int _throwCount;	
	//시간차로 연속콤보를 가능하게하기위한 시간변수
	int _attackComboTime;
	int _attackComboCount;
	//회피
	int _avoidTime;
	int _avoidFPS;
	int _avoidEffTime;
	int _moveEffTime;
	
	int _attackedOldTime;

	POINTF _skillStartPos;
	bool _skillMove;
	bool _skillEff;


public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render(bool uiRender);

	void keyAniInit();
	void effectInit();

	void effectUpdate(int maxFrameX, int maxFrameY, int fps);

	void aimKeyInput();
	void playerKeyInput();
	void playerState();
	void setType();

	void attackAngle(bool stayOn);

	void playerAniName(string playerName, string aniName);

	static void cbMoveBreak(void* obj);
	static void cbThrowAim(void* obj);
	static void cbAttack(void* obj);
	static void cbAvoid(void* obj);
	static void cbSkillFire(void* obj);

public:
	//================ 접근자 설정자 ====================
	D2D1_RECT_F getPlayerRc() { return _player.rc; }
	D2D1_RECT_F getPlayerAttackRc() { return _player.attackRc; }
	playerBullet* getPlayerBullet() { return _player.bullet; }
	PLAYERSTATE getPlayerState() { return _player.state; }
	PLAYERDIRECTION getPlayerDirection() { return _player.direction; }
	string getPlayerName() { return _player.name; }
	float getPlayerPosX() { return _player.x; }
	float getPlayerPosY() { return _player.y; }
	float getPlayerSpeed() { return _player.speed; }
	float getPlayerJumpPower() { return _player.jumpPower; }
	float getPlayerAngle() { return _player.angle; }
	int getPlayerIdX() { return _player.idX; }
	int getPlayerIdY() { return _player.idY; }
	int getPlayerHP() { return _player.HP; }
	int getPlayerMaxHP() { return _player.maxHP;}
	bool getIsThorowAttack() { return _isThrowAttack; }
	bool getIsAttack() { return _isAttack; }
	bool getIsAttacked() { return _isAttacked; }
	bool getIsSkill() { return _isSkill; }

	void setEffectPlay(bool effectPlay) { _effectPlay = effectPlay; }

	void setPlayerState(PLAYERSTATE playerState) { _player.state = playerState; }
	void setPlayerDirection(PLAYERDIRECTION playerDirection) { _player.direction = playerDirection; }
	void setPlayerRc(D2D1_RECT_F rc) { _player.rc = rc; }
	void setPlayerAttackRc(D2D1_RECT_F rc) { _player.attackRc = rc; }
	void setPlayerName(string name) { _player.name = name; }
	void setPlayerPosX(float x) { _player.x = x; }
	void setPlayerPosY(float y) { _player.y = y; }
	void setPlayerSpeed(float speed) { _player.speed = speed; }
	void setPlayerJumpPower(float jumpPower) { _player.jumpPower = jumpPower; }
	void setPlayerAngle(float angle) { _player.angle = angle; }
	void setPlayerIdX(int idX) { _player.idX = idX; }
	void setPlayerIdY(int idY) { _player.idY = idY; }
	void setPlayerHP(int hp) { _player.HP = hp; }
	void setEffSpeed(float speed) { _effSpeed = speed; }

	void setIsThrowAttack(bool isThrowAttack) { _isThrowAttack = isThrowAttack; }
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }
	void setIsAvoid(bool isAvoid) { _isAvoid = isAvoid; }
	void setIsSkill(bool isSkill) { _isSkill = isSkill; }
	void setIsSkillMove(bool isSkillMove) { _skillMove = isSkillMove; }
	void setSkillEff(bool skillEff) { _skillEff = skillEff; }
};

