#pragma once

#define PI 3.141592f
#define PI2 2 * PI


typedef struct tagELLIPSE
{
	POINTF p;
	float r;
} ELLIPSE, *LPELLIPSE;

namespace TEAM_15DUCK_UTILL
{
	const wstring MakeImageName(const WCHAR* imageName, const WCHAR* folderName = nullptr);

	const wstring AppendInt(const WCHAR* imageName, int value);

	POINT PointMake(int x, int y);

	POINTF PointFMake(float x, float y);

	void LineMake(HDC hdc, int startX, int startY, int endX, int endY, bool isAbsolut = true);

	void LineMake(HDC hdc, POINTF start, POINTF end, bool isAbsolut = true);


	//================= ��Ʈ ���� �Լ� ========================
	//    ��Ʈ�� �����(����Ʈ, ž, ����ũ��, ����ũ��)
	RECT RectMake(int x, int y, int width, int height);
	//    ��Ʈ�� �����(����X��ǥ, ����Y��ǥ, ����ũ��, ����ũ��)
	RECT RectMakeCenter(int x, int y, int width, int height);


	//====================== �� �� �� �� ���� ===============================
	//        �� �����Լ� (hdc, left, top, ����ũ��, ����ũ��)
	ELLIPSE EllipseMake(float x, float y, float r);

	//���� ������ ��׸���
	float RadToDeg(float angle);

	//��׸� ������ ��������
	float DegToRad(float angle);

	//�Ÿ����ϱ�
	float getDistance(float x1, float y1, float x2, float y2);
	float getDistance(POINTF& p1, POINTF& p2);

	//���浹�ߴ���
	bool EllipseCollision(ELLIPSE& e1, ELLIPSE& e2);

	//�������ϱ�
	float getCenter(float a, float b);

	//��Ʈ ���� ��ȯ�Լ�
	POINT getRectCenter(RECT& rc);

	//��Ʈ x���� ��ȯ �Լ�
	float getRectXCenter(RECT& rc);

	//��Ʈ y���� ��ȯ �Լ�
	float getRectYCenter(RECT& rc);

	//��Ʈ width ��ȯ �Լ�
	float getRectWidth(RECT& rc);

	//��Ʈ height ��ȯ �Լ�
	float getRectHeight(RECT& rc);

	//�� �� �浹
	bool PtInEllipse(ELLIPSE& e, POINTF p);

	//�� �� �浹
	bool PtInEllipse(ELLIPSE& e, float x, float y);

	//��׸� �ڻ���
	float dCosf(float angle);

	//��׸� ����
	float dSinf(float angle);

	//���ΰ� �ھƼ� �����޾ƿ��� ��ũź��Ʈ ��ȯ�� ����
	float getAngle(POINTF p, POINTF target);

	float getAngle(float x, float y, float x2, float y2);

	//�� �ΰ� �ھƼ� �����޾ƿ��� ��ũ�ڻ��� ��ȯ�� ����
	float getAngle2(POINTF p, POINTF target);

	float getAngle2(float x, float y, float x2, float y2);

	//���ΰ� �ھƼ� �����޾ƿ��� ��ũź��Ʈ ��ȯ�� ��׸�
	float dGetAngle(POINTF target, POINTF p);

	float dGetAngle(float x2, float y2, float x, float y);

	//�� �ΰ� �ھƼ� �����޾ƿ��� ��ũ�ڻ��� ��ȯ�� ��׸�
	float dGetAngle2(POINTF target, POINTF p);

	float dGetAngle2(float x2, float y2, float x, float y);

	//�� �簢�� �浹
	bool RectEllipseCollition(RECT& rc, ELLIPSE& e);

	//=========================== string wstring ��ȯ ===============================

	wstring string2wstring(string str);
}