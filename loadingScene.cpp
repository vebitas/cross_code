#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
	:_currentCount(0)
{
}


loadingScene::~loadingScene()

{
}

HRESULT loadingScene::init()
{
	imgAdd();
	soundAdd();
	setWindowsSize(0, 0, GAMESIZEX, GAMESIZEY);
	CreateThread
	(
		NULL,				//스레드의 보안속성(자식윈도우가 있을때) 핸들로 자식인지 부모인지 여부파악
		NULL,				//스레드의 스택크기(NULL로 두면 메인쓰레드와 스택크기는 동일)
		ThreadFunction,		//스레드 함수 명
		this,				//스레드의 매개변수 (this로 하면 본 클래스)
		NULL,				//스레드의 특성(NULL로 두면 바로 실행함)
		0					//스레드의 생성 후 스레드의 ID를 넘겨준다 보통은 NULL로 둠.
	);



	return S_OK;
}

void loadingScene::release()
{
}

void loadingScene::update()
{
	_width = (float)_currentCount / (float)LOADINGMAX;
	
	if (_currentCount == LOADINGMAX)
	{
		SCENEMANAGER->changeScene("menuScene");
	}
}

void loadingScene::render()
{
	IMAGEMANAGER->findImage("loadingBackground")->render(0, 0, 1);

	IMAGEMANAGER->findImage("loadingImg")->render(0, 150, 1024, 462, 0.5);

	IMAGEMANAGER->findImage("backBar")->render(180, WINSIZEY / 2, 700, 20, 1);

	IMAGEMANAGER->findImage("frontBar")->render(180, WINSIZEY / 2, 700 * _width, 15);

	D2DMANAGER->createBrush(RGB(255, 0, 255), 1);
	//WCHAR str[128];
	//swprintf_s(str, L"길이 : %d", _currentCount);
	//D2DMANAGER->drawText(str, 100, 100);

}

void loadingScene::imgAdd()
{
	//로딩씬 이미지
	IMAGEMANAGER->addImage("backBar", L"image/intro/backBar.png", 200, 7);
	IMAGEMANAGER->addImage("frontBar", L"image/intro/frontBar.png", 3, 3);
	IMAGEMANAGER->addImage("loadingBackground", L"image/intro/lodingBackground.png", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("loadingImg", L"image/intro/loding.png", 1000, 462);
	//폰트
	IMAGEMANAGER->addFrameImage("number", L"image/font/number.png", 200, 23, 10, 1);
	//메뉴씬 이미지
	IMAGEMANAGER->addImage("glow_1", L"image/intro/glow_1.png", WINSIZEX, 34);
	IMAGEMANAGER->addImage("glow_2", L"image/intro/glow_2.png", 128, 122);
	IMAGEMANAGER->addImage("glow_3", L"image/intro/glow_3.png", 128, 122);
	IMAGEMANAGER->addImage("rfgFish", L"image/intro/rfg-fish.png", 150, 150);
	IMAGEMANAGER->addImage("rfgText", L"image/intro/rfg-Text.png", 254, 46);
	IMAGEMANAGER->addImage("blackground", L"image/intro/lodingBackground.png", 1024, 768);
	IMAGEMANAGER->addImage("blackground2", L"image/intro/lodingBackground2.png", 1024, 768);
	IMAGEMANAGER->addImage("titleLogo", L"image/intro/title_logo.png", 325, 111);
	IMAGEMANAGER->addImage("clouds", L"image/intro/clouds.png", 1024, 499);
	IMAGEMANAGER->addImage("sky", L"image/intro/sky.png", 1024, 712);
	IMAGEMANAGER->addImage("ground", L"image/intro/ground.png", 1024, 292);
	IMAGEMANAGER->addImage("railings", L"image/intro/railings.png", 1024, 114);
	IMAGEMANAGER->addImage("planet", L"image/intro/planet.png", 300, 525);
	IMAGEMANAGER->addImage("keyboard", L"image/intro/keyboard.png", 102, 50);
	IMAGEMANAGER->addFrameImage("lea", L"image/intro/lea.png", 1800, 399, 6, 1);
	IMAGEMANAGER->addFrameImage("newGameB", L"image/intro/newGameButton.png", 288, 144, 1, 3);
	IMAGEMANAGER->addFrameImage("optionB", L"image/intro/optionButton.png", 288, 144, 1, 3);
	IMAGEMANAGER->addFrameImage("exidB", L"image/intro/exidButton.png", 288, 144, 1, 3);
	//플레이어
	IMAGEMANAGER->addFrameImage("leaMove", L"image/player/move.png", 1040, 1235, 16, 19);
	IMAGEMANAGER->addFrameImage("leaThrow", L"image/player/throw.png", 520, 1300, 8, 20);
	IMAGEMANAGER->addFrameImage("attackNormal", L"image/effect/sweep_normal.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackNormalR", L"image/effect/sweep_normal_R.png", 400, 150, 4, 2);
	//IMAGEMANAGER->addFrameImage("attackNormalF", L"image/effect/sweep_normal_Last.png", 240, 42, 4, 1);
	IMAGEMANAGER->addFrameImage("attackFire", L"image/effect/sweep_fire.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackFireR", L"image/effect/sweep_fire_R.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackIce", L"image/effect/sweep_water.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackIceR", L"image/effect/sweep_water_R.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackSpake", L"image/effect/sweep_spake.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackSpakeR", L"image/effect/sweep_spake_R.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackWave", L"image/effect/sweep_wave.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("attackWaveR", L"image/effect/sweep_wave_R.png", 400, 150, 4, 2);
	IMAGEMANAGER->addFrameImage("bullet", L"image/effect/ball.png", 520, 320, 13, 8);
	IMAGEMANAGER->addFrameImage("bulletN", L"image/effect/ball_N_E.png", 160, 16, 10, 1);
	IMAGEMANAGER->addFrameImage("guard", L"image/effect/guard.png", 512, 512, 8, 8);
	IMAGEMANAGER->addFrameImage("teleportEff", L"image/effect/spread.png", 660, 60, 11, 1);
	EFFECTMANAGER->addEffect("attackNormalF", "image/effect/sweep_normal_Last.png", 240, 42, 60, 42, 5, 0.05, 20);
	EFFECTMANAGER->addEffect("avoidEff", "image/effect/player_avoid.png", 300, 51, 50, 51, 7, 0.05, 20);
	EFFECTMANAGER->addEffect("circle", "image/effect/circle.png", 900, 300, 300, 300, 7, 0.05, 20);
	EFFECTMANAGER->addEffect("moveEff", "image/effect/player_move.png", 150, 23, 30, 23, 6, 0.04, 20);
	IMAGEMANAGER->addImage("sceneChange", L"image/effect/sceneChange.png", 1024, 768);
	EFFECTMANAGER->addEffect("hit", "image/effect/hit.png", 512, 128, 64, 64, 5, 0.05, 30);
	EFFECTMANAGER->addEffect("deadEff", "image/effect/deadEff.png", 252, 177, 63, 59, 5, 0.05, 30);
	EFFECTMANAGER->addEffect("summon", "image/effect/summons.png", 280, 216, 40, 216, 5, 0.04, 30);
	EFFECTMANAGER->addEffect("fire1", "image/effect/fire1.png", 180, 57, 60, 57, 5, 0.05, 1);
	IMAGEMANAGER->addFrameImage("fire2", L"image/effect/fire2.png", 256, 128, 8, 1);
	EFFECTMANAGER->addEffect("fire3", "image/effect/fire3.png", 558, 170, 93, 85, 5, 0.06, 50);
	EFFECTMANAGER->addEffect("fire4", "image/effect/fire4.png", 308, 49, 44, 49, 5, 0.05, 50);
	EFFECTMANAGER->addEffect("fire5", "image/effect/fire5.png", 240, 52, 30, 52, 5, 0.05, 300);
	IMAGEMANAGER->addFrameImage("playerAttribute", L"image/player/playerAttribute.png", 800, 160, 5, 1);
	IMAGEMANAGER->addImage("playerUI", L"image/player/playerUI.png", 205, 80);
	IMAGEMANAGER->addImage("playerHPBar", L"image/player/playerHPBar.png", 103, 7);
	//오브젝트
	IMAGEMANAGER->addFrameImage("teleport", L"image/object/teleport.png", 150, 77, 2, 1);
	IMAGEMANAGER->addFrameImage("barricade", L"image/object/barricade.png", 180, 113, 9, 1);
	IMAGEMANAGER->addFrameImage("switch", L"image/object/switch.png", 512, 64, 16, 1);
	//에너미
	IMAGEMANAGER->addFrameImage("hog", L"image/enemy/hedgehog.png", 800, 256, 10, 4);
	IMAGEMANAGER->addFrameImage("easyBot", L"image/enemy/easy-bot.png", 660, 240, 11, 4);
	IMAGEMANAGER->addFrameImage("turret", L"image/enemy/turret.png", 450, 450, 9, 9);
	//보스
	IMAGEMANAGER->addFrameImage("boss_head", L"image/enemy/boss/boss_head.png", 640, 156, 4, 1);
	IMAGEMANAGER->addFrameImage("boss_body1", L"image/enemy/boss/boss_body.png", 484, 194, 4, 1);
	IMAGEMANAGER->addFrameImage("boss_body2", L"image/enemy/boss/boss_body_2.png", 404, 169, 4, 1);
	IMAGEMANAGER->addFrameImage("boss_body3", L"image/enemy/boss/boss_body_3.png", 316, 128, 4, 1);
	IMAGEMANAGER->addImage("boss_body4", L"image/enemy/boss/boss_body_4.png", 68, 91);
	IMAGEMANAGER->addImage("boss_body5", L"image/enemy/boss/boss_body_5.png", 64, 64);
	IMAGEMANAGER->addFrameImage("boss_tail", L"image/enemy/boss/boss_tail.png", 330, 70, 4, 1);
	IMAGEMANAGER->addFrameImage("boss_diving2", L"image/enemy/boss/diving2.png", 8000, 800, 10, 1);
	IMAGEMANAGER->addFrameImage("bossBullet", L"image/enemy/boss/effect_3.png", 600, 360, 5, 3);
	IMAGEMANAGER->addImage("X", L"image/enemy/boss/x.png", 50, 50);
	IMAGEMANAGER->addImage("bossHPOutLine", L"image/enemy/boss/bossHPBar.png", 943, 35);
	IMAGEMANAGER->addImage("bossHPBar", L"image/enemy/boss/bossHP.png", 770, 24);
	EFFECTMANAGER->addEffect("effect1", "image/enemy/boss/effect_1.png", 505, 106, 63, 53, 3, 0.1, 50);
	EFFECTMANAGER->addEffect("effect2", "image/enemy/boss/effect_2.png", 210, 70, 35, 35, 3, 0.1, 50);
	EFFECTMANAGER->addEffect("effect3", "image/enemy/boss/effect_3.png", 600, 360, 120, 120, 3, 0.1, 50);
	EFFECTMANAGER->addEffect("effect4", "image/enemy/boss/effect_4.png", 1200, 600, 300, 300, 3, 0.07, 50);
	EFFECTMANAGER->addEffect("effect5", "image/enemy/boss/effect_5.png", 600, 360, 120, 120, 3, 0.1, 200);
	EFFECTMANAGER->addEffect("effect6", "image/enemy/boss/effect_6.png", 600, 150, 150, 150, 3, 0.1, 50);
	EFFECTMANAGER->addEffect("effect7", "image/enemy/boss/effect_7.png", 2100, 389, 300, 389, 7, 0.06, 600);
	EFFECTMANAGER->addEffect("effect8", "image/enemy/boss/effect_8.png", 1024, 260, 128, 260, 5, 0.05, 600);
	EFFECTMANAGER->addEffect("bossDeath", "image/enemy/boss/bossDeathEff.png", 404, 285, 101, 95, 5, 0.05, 300);
	//맵툴
	IMAGEMANAGER->addFrameImage("stage1_1", L"image/tileNode/stage1_1.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_2", L"image/tileNode/stage1_2.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_3", L"image/tileNode/stage1_3.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage2", L"image/tileNode/stage2.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("bossStage", L"image/tileNode/bossStage.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_1(mini)", L"image/tileNode/stage1_1(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_2(mini)", L"image/tileNode/stage1_2(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_3(mini)", L"image/tileNode/stage1_3(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage2(mini)", L"image/tileNode/stage2(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("bossStage(mini)", L"image/tileNode/bossStage(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addImage("mapToolBackground", L"image/tileNode/mapToolBackground.png", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("build_LR", L"image/tileNode/build_LR.png", 64, 830);
	IMAGEMANAGER->addImage("build_UD", L"image/tileNode/build_UD.png", 750, 64);
	IMAGEMANAGER->addFrameImage("button", L"image/tileNode/button.png", 150, 200, 3, 4);
	IMAGEMANAGER->addFrameImage("button2", L"image/tileNode/button_2.png", 375, 250, 3, 5);
	IMAGEMANAGER->addFrameImage("textXY", L"image/tileNode/textXY.png", 96, 48, 2, 1);
	IMAGEMANAGER->addImage("textMap", L"image/tileNode/textMap.png", 96, 48);
	IMAGEMANAGER->addImage("window", L"image/tileNode/window.png", 300, 300);
	IMAGEMANAGER->addFrameImage("okButton", L"image/tileNode/okButton.png", 144, 48, 3, 1);
	IMAGEMANAGER->addFrameImage("number", L"image/tileNode/number.png", 144, 48, 3, 1);
	IMAGEMANAGER->addFrameImage("stage1_1", L"image/tileNode/stage1_1.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_2", L"image/tileNode/stage1_2.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_3", L"image/tileNode/stage1_3.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage2", L"image/tileNode/stage2.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("bossStage", L"image/tileNode/bossStage.png", 1024, 608, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_1(mini)", L"image/tileNode/stage1_1(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_2(mini)", L"image/tileNode/stage1_2(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage1_3(mini)", L"image/tileNode/stage1_3(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("stage2(mini)", L"image/tileNode/stage2(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameImage("bossStage(mini)", L"image/tileNode/bossStage(mini).png", 128, 76, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addImage("mapToolBackground", L"image/tileNode/mapToolBackground.png", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("build_LR", L"image/tileNode/build_LR.png", 64, 830);
	IMAGEMANAGER->addImage("build_UD", L"image/tileNode/build_UD.png", 750, 64);
	IMAGEMANAGER->addFrameImage("button", L"image/tileNode/button.png", 150, 200, 3, 4);
	IMAGEMANAGER->addFrameImage("button2", L"image/tileNode/button_2.png", 375, 250, 3, 5);
	IMAGEMANAGER->addFrameImage("textXY", L"image/tileNode/textXY.png", 96, 48, 2, 1);
	IMAGEMANAGER->addImage("textMap", L"image/tileNode/textMap.png", 96, 48);
	IMAGEMANAGER->addImage("window", L"image/tileNode/window.png", 300, 300);
	IMAGEMANAGER->addFrameImage("okButton", L"image/tileNode/okButton.png", 144, 48, 3, 1);
	IMAGEMANAGER->addFrameImage("number", L"image/tileNode/number.png", 144, 48, 3, 1);
}

void loadingScene::soundAdd()
{
	//BGM
	SOUNDMANAGER->addSound("title", "sound/introOpening.mp3", true, true);
	SOUNDMANAGER->addSound("awakened", "sound/awakened.mp3", true, true);
	SOUNDMANAGER->addSound("battle", "sound/battle1.mp3", true, true);
	SOUNDMANAGER->addSound("bossBattle", "sound/bossBattle.mp3", true, true);
	SOUNDMANAGER->addSound("cargoHold", "sound/cargoHold.mp3", true, true);
	SOUNDMANAGER->addSound("fierceBattle", "sound/fierceBattle.mp3", true, true);
	//EFFECT
	SOUNDMANAGER->addSound("whale_1", "sound/effectSound/whale-call.mp3", false, false);
	SOUNDMANAGER->addSound("whale_2", "sound/effectSound/whale-call-2.mp3", false, false);
	SOUNDMANAGER->addSound("whale_3", "sound/effectSound/whale-call-3.mp3", false, false);
	SOUNDMANAGER->addSound("sweep1", "sound/effectSound/sweep1.mp3", false, false);
	SOUNDMANAGER->addSound("sweep2", "sound/effectSound/sweep2.mp3", false, false);
	SOUNDMANAGER->addSound("sweep3", "sound/effectSound/sweep3.mp3", false, false);
	SOUNDMANAGER->addSound("sweep4", "sound/effectSound/sweep3.mp3", false, false);
	SOUNDMANAGER->addSound("throwE_1", "sound/effectSound/ball-hit-hard1.mp3", false, false);
	SOUNDMANAGER->addSound("throwE_2", "sound/effectSound/ball-hit-massive.mp3", false, false);
	SOUNDMANAGER->addSound("enemyDeath", "sound/effectSound/exposion-enemy-short-2.mp3", false, false);
	SOUNDMANAGER->addSound("playerAttacked", "sound/effectSound/playerAttacked.mp3", false, false);
	SOUNDMANAGER->addSound("throw1", "sound/effectSound/throw1.mp3", false, false);
	SOUNDMANAGER->addSound("throw2", "sound/effectSound/throw2.mp3", false, false);

}

DWORD CALLBACK ThreadFunction(LPVOID lpParameter)
{
	loadingScene* loadHelper = (loadingScene*)lpParameter;

	while (loadHelper->_currentCount != LOADINGMAX)
	{
		Sleep(1);


		loadHelper->_currentCount++;
	}

	return 0;
}

void loadingScene::setWindowsSize(int x, int y, int width, int height)
{
	//SAFE_RELEASE2(D2DMANAGER->_renderTarget);
	D2DMANAGER->_renderTarget->Resize(SizeU(width, height));

	//---------------------------------------------------------------------------
	//   Hwnd Render Target 생성
	//---------------------------------------------------------------------------
	//D2DMANAGER->_d2dFactory->CreateHwndRenderTarget(RenderTargetProperties(),
	//	HwndRenderTargetProperties(_hWnd, SizeU(width, height)),
	//	&D2DMANAGER->_renderTarget);

	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//실질적으로 클라이언트 영역 크기 셋팅을 한다
	SetWindowPos(_hWnd, NULL, x, y,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);
}

