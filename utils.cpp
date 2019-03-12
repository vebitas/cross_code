#include "stdafx.h"
#include "utils.h"


namespace TEAM_15DUCK_UTILL
{
	const wstring MakeImageName(const WCHAR * imageName, const WCHAR * folderName)
	{
		wstring str = L"";

		if (nullptr != folderName)
		{
			str.append(folderName);
			str.append(L"/");
		}

		str.append(imageName);
		str.append(L".bmp");
		
		return str;
	}
	const wstring AppendInt(const WCHAR * imageName, int value)
	{
		wstring str = L"";

		str.append(imageName);
		str.append(to_wstring(value));

		return str;
	}

	POINT PointMake(int x, int y)
	{
		POINT pt = { x, y };

		return pt;
	}
	POINTF PointFMake(float x, float y)
	{
		POINTF pt = { x, y };

		return pt;
	}
	void LineMake(HDC hdc, int startX, int startY, int endX, int endY, bool isAbsolut)
	{
		float posX = startX - (int)CAMERA->getCameraX();
		float posY = startY - (int)CAMERA->getCameraY();
		float posX2 = endX - (int)CAMERA->getCameraX();
		float posY2 = endY - (int)CAMERA->getCameraY();

		MoveToEx(hdc, posX, posY, NULL);
		LineTo(hdc, posX2, posY2);
	}
	void LineMake(HDC hdc, POINTF start, POINTF end, bool isAbsolut)
	{
		float posX = start.x - (int)CAMERA->getCameraX();
		float posY = start.y - (int)CAMERA->getCameraY();
		float posX2 = end.x - (int)CAMERA->getCameraX();
		float posY2 = end.y - (int)CAMERA->getCameraY();

		MoveToEx(hdc, posX, posY, NULL);
		LineTo(hdc, posX2, posY2);
	}
	RECT RectMake(int x, int y, int width, int height)
	{
		RECT rc = { x, y, x + width, y + height };
		return rc;
	}
	RECT RectMakeCenter(int x, int y, int width, int height)
	{
		RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
		return rc;
	}



	ELLIPSE EllipseMake(float x, float y, float r)
	{
		ELLIPSE rt;
		rt.p.x = x;
		rt.p.y = y;
		rt.r = r;
		return rt;
	}

	float RadToDeg(float angle)
	{
		return angle * (180.0f / PI);
	}
	float DegToRad(float angle)
	{
		return angle * (PI / 180.0f);
	}
	//�Ÿ� ���ϴ� �Լ�
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return sqrtf(x * x + y * y);
	}

	float getDistance(POINTF & p1, POINTF & p2)
	{
		return sqrtf((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
	}

	bool EllipseCollision(ELLIPSE & e1, ELLIPSE & e2)
	{
		return (e1.r + e2.r >= getDistance(e1.p, e2.p));
	}

	float getCenter(float a, float b)
	{
		return a + (b - a) / 2;
	}

	POINT getRectCenter(RECT & rc)
	{
		POINT p;
		p.x = getCenter(rc.left, rc.right);
		p.y = getCenter(rc.top, rc.bottom);
		return p;
	}

	float getRectXCenter(RECT & rc)
	{
		return getCenter(rc.left, rc.right);
	}

	float getRectYCenter(RECT & rc)
	{
		return getCenter(rc.top, rc.bottom);
	}

	float getRectWidth(RECT & rc)
	{
		return rc.right - rc.left;
	}

	float getRectHeight(RECT & rc)
	{
		return rc.bottom - rc.top;
	}

	bool PtInEllipse(ELLIPSE & e, POINTF p)
	{
		return (e.r >= getDistance(e.p, p));
	}

	bool PtInEllipse(ELLIPSE & e, float x, float y)
	{
		return (e.r >= getDistance(e.p.x, e.p.y, x, y));
	}

	float dCosf(float angle)
	{
		return cosf(DegToRad(angle));
	}

	float dSinf(float angle)
	{
		return sinf(DegToRad(angle));
	}

	float getAngle(POINTF p, POINTF target)
	{
		return -atan2f(target.y - p.y, target.x - p.x);
	}

	float getAngle(float x, float y, float x2, float y2)
	{
		return -atan2f(y2 - y, x2 - x);
	}

	float getAngle2(POINTF p, POINTF target)
	{
		float angle;
		float deltaX = target.x - p.x;
		float deltaY = target.y - p.y;
		float distance = sqrtf(deltaX* deltaX + deltaY * deltaY);
		angle = acosf(deltaX / distance);
		if (deltaY < 0)
		{
			angle = 2 * PI - angle;
			if (angle > 2 * PI) angle -= 2 * PI;
		}
		return angle;
	}

	float getAngle2(float x, float y, float x2, float y2)
	{
		float angle;
		float deltaX = x2 - x;
		float deltaY = y2 - y;
		float distance = sqrtf(deltaX* deltaX + deltaY * deltaY);
		angle = acosf(deltaX / distance);
		if (y2 < y)
		{
			angle = 2 * PI - angle;
			if (angle > 2 * PI) angle -= 2 * PI;
		}
		return angle;
	}

	float dGetAngle(POINTF target, POINTF p)
	{
		return RadToDeg(-atan2f(target.y - p.y, target.x - p.x));
	}

	float dGetAngle(float x2, float y2, float x, float y)
	{
		return RadToDeg(-atan2f(y2 - y, x2 - x));
	}

	float dGetAngle2(POINTF target, POINTF p)
	{
		float angle;
		float deltaX = target.x - p.x;
		float deltaY = target.y - p.y;
		float distance = sqrtf(deltaX* deltaX + deltaY * deltaY);
		angle = acosf(deltaX / distance);
		if (deltaY < 0)
		{
			angle = 2 * PI - angle;
		}
		return RadToDeg(angle);
	}

	float dGetAngle2(float x2, float y2, float x, float y)
	{
		float angle;
		float deltaX = x2 - x;
		float deltaY = y2 - y;
		float distance = sqrtf(deltaX* deltaX + deltaY * deltaY);
		angle = acosf(deltaX / distance);
		if (deltaY < 0)
		{
			angle = 2 * PI - angle;
		}
		return RadToDeg(angle);
	}

	bool RectEllipseCollition(RECT & rc, ELLIPSE & e)
	{
		if ((rc.left <= e.p.x && e.p.x <= rc.right) || (rc.top <= e.p.y && e.p.y <= rc.bottom))
		{
			POINT p;
			p.x = e.p.x;
			p.y = e.p.y;
			RECT rc2 = { rc.left - e.r, rc.top - e.r, rc.right + e.r, rc.bottom + e.r };
			if (PtInRect(&rc2, p))return true;
		}
		else
		{
			POINTF p;
			p.x = rc.left;
			p.y = rc.top;
			if (PtInEllipse(e, p)) return true;
			p.x = rc.left;
			p.y = rc.bottom;
			if (PtInEllipse(e, p)) return true;
			p.x = rc.right;
			p.y = rc.top;
			if (PtInEllipse(e, p)) return true;
			p.x = rc.right;
			p.y = rc.bottom;
			if (PtInEllipse(e, p)) return true;
		}
		return false;
	}

	wstring string2wstring(string str)
	{

		int nLen = MultiByteToWideChar(CP_ACP, 0, &str[0], str.size(), NULL, NULL);
		wstring strUni(nLen, 0);
		MultiByteToWideChar(CP_ACP, 0, &str[0], str.size(), &strUni[0], nLen);

		return strUni;
	}

}