#pragma once
#include <vector>

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

//void* ���� : � ���µ� �� ����ų���ִ�(�Ű������� �� �� �������ִ�)
//		���� : � �������� ��ø� �ؾ��Ѵ�.	

class animation
{
public:
	typedef vector<POINT>	vFrameList;	//�������ε��� 
	typedef vector<int>		vPlayList;	//�÷����ε���

private:
	int			_frameNum;		//�ִϸ��̼� ������ ����
	vFrameList	_frameList;		//������ ����Ʈ
	vPlayList	_playList;		//�÷��� ����Ʈ

	int _frameWidth;			//������ ����ũ��
	int _frameHeight;			//������ ����ũ��

	BOOL _loop;					//�ִϸ��̼� ��������

	float _frameUpdateSec;		//������ ���Žð�
	float _elapsedSec;			//����ð�

	DWORD _nowPlayIndex;		//���� �÷��� �ε���
	BOOL _play;					//�ִϸ��̼� �������

	DWORD _eventFrameIndex;		//�̺�Ʈ�� �߻��ϴ� ������ ��ȣ
	bool _isDoEvent;			// �̺�Ʈ �����ߴ°�

	void*						_obj;
	CALLBACK_FUNCTION			_callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

public:
	animation();
	~animation();

	//       �̹�����ü����ũ�� ��ü����ũ��  �������Ӱ���ũ�� �������Ӽ���ũ��
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release();

	//����Ʈ �ִϸ��̼�
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);


	//�迭�� ��� �ִϸ��̼� ���
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//���� �ִϸ��̼� ���
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);


	//�ִϸ��̼� ������ ����ӵ� ����
	void setFPS(int framePerSec);

	//������
	void frameUpdate(float elapsedTime);

	void start();		//���
	void stop();		//����
	void pause();		//�Ͻ�����
	void resume();		//�ٽ����

	inline BOOL isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }

	// �̺�Ʈ ������ ��ȣ set/get
	inline void setEventFrame(int frameIndex) { _eventFrameIndex = frameIndex; }
	inline int getEventFrame() { return _eventFrameIndex; }

	// �̺�Ʈ ���� �ߴ��� 
	void setEventDo(bool flag) { _isDoEvent = flag; }
	bool getEventDo() {return _isDoEvent;}

	// �̺�Ʈ �������ΰ�
	bool isEventFrame() { return _nowPlayIndex  == _eventFrameIndex; }
};

