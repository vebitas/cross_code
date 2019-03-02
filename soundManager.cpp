#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	:_system(NULL),
	_channel(NULL),
	_sound(NULL)
{
}


soundManager::~soundManager()
{

}

HRESULT soundManager::init()
{
	//FMOD ���� ������ ����ϰڴٰ� ����
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));

	// ���� �׷� ����
	_system->createSoundGroup("bgmSound", &_bgmSoundGroup);
	_system->createSoundGroup("effectSound", &_effectSoundGroup);

	// ä�� �׷� ����
	_system->createChannelGroup("bgm", &_bgmGroup);
	_system->createChannelGroup("effect", &_effectGroup);

	return S_OK;
}

void soundManager::release()
{
	//���� ����
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != NULL)
			{
				if (_sound != NULL) _sound[i]->release();
			}
		}
	}

	//�޸� �����
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	SAFE_RELEASE(_effectGroup);
	SAFE_RELEASE(_bgmGroup);

	SAFE_RELEASE(_bgmSoundGroup);
	SAFE_RELEASE(_effectSoundGroup);

	_effectGroup = nullptr;
	_bgmGroup = nullptr;
	_bgmSoundGroup = nullptr;
	_effectSoundGroup = nullptr;

	//�ý��� �ݱ� 
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void soundManager::update()
{
	//���� System ��������� ������Ʈ
	_system->update();

	//������ �ٲ�ų� 
	//����� ���� ���带 ä�ο��� �����µ��� �پ���
	//�۾��� �ڵ����� ���ش�
}


void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	// ����� TOTALSOUNDBUFFER�� ������ �߰� �� �� �ִ�.
	if (TOTALSOUNDBUFFER <= _mTotalSounds.size())
		return;

	// �������?
	FMOD_MODE mode = NULL;
	if (loop)
		mode = FMOD_LOOP_NORMAL;
	else
		mode = FMOD_DEFAULT;

	// ����ִ� ����ĭ�� ���ο� ���带 �Ҵ�
	int useSoundIdx = static_cast<int>(_mTotalSounds.size());
	if (bgm)
	{
		_system->createStream(soundName.c_str(), mode, NULL, &_sound[useSoundIdx]);
		_sound[useSoundIdx]->setSoundGroup(_bgmSoundGroup);
	}
	else
	{
		_system->createSound(soundName.c_str(), mode, NULL, &_sound[useSoundIdx]);
		_sound[useSoundIdx]->setSoundGroup(_effectSoundGroup);
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[useSoundIdx]));
}

void soundManager::play(string keyName, float volume)// 0.0 ~ 1.0f -> 0 ~ 255
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, ++count)
	{
		Sound* sound = *iter->second;
		SoundGroup* soundGroup = nullptr;

		if (keyName == iter->first)
		{
			// ��� ���� �׷쿡 �����ִ��� Ȯ��
			sound->getSoundGroup(&soundGroup);

			if (soundGroup == _bgmSoundGroup)	// bgm soundgroup
			{
				_bgmSoundGroup->stop(); // �÷������� bgm ����
				_channel[count]->setChannelGroup(_bgmGroup);
			}
			else								// effect soundgroup
				_channel[count]->setChannelGroup(_effectGroup);

			_system->playSound(FMOD_CHANNEL_FREE, sound, false, &_channel[count]);
			_channel[count]->setVolume(volume);
			
			break;
		}
	}
}

void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}


bool soundManager::isPlaySound(string keyName)
{
	bool isPlay = false;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause = false;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}

void soundManager::setEffectVolume(float volume)
{
	if (volume < 0.f)
		volume = 0.f;
	else if (1.0f < volume)
		volume = 1.0f;

	_effectGroup->setVolume(volume);

	cout << "effect volume : " << volume << endl;
}

void soundManager::setBgmVolume(float volume)
{
	if (volume < 0.f)
		volume = 0.f;
	else if (1.0f < volume)
		volume = 1.0f;

	_bgmGroup->setVolume(volume);

	cout << "bgm volume : " << volume << endl;
}

void soundManager::setAllSoundVolume(float volume)
{
	_bgmGroup->setVolume(volume);
	_effectGroup->setVolume(volume);
}

void soundManager::setEffectPause()
{
	_effectGroup->setPaused(true);
}

void soundManager::setBgmPause()
{
	_bgmGroup->setPaused(true);
}

void soundManager::setAllSoundPause()
{
	_bgmGroup->setPaused(true);
	_effectGroup->setPaused(true);
}

void soundManager::setEffectResume()
{
	_effectGroup->setPaused(false);
}

void soundManager::setBgmResume()
{
	_bgmGroup->setPaused(false);
}

void soundManager::setAllSoundResume()
{
	_bgmGroup->setPaused(false);
	_effectGroup->setPaused(false);
}
