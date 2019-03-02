#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::init()
{
	return S_OK;
}

void txtData::release()
{
}

void txtData::txtSave(const char * saveFileName, vector<string> vStr)
{
	HANDLE file;
	DWORD write;

	char str[128];

	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}

char* txtData::vectorArrayCombine(vector<string> vArray)
{
	//���� �迭�� �����迭�� �ؼ� �׻� ũ�⿡ �°� ���������� �ٲ��
	//������ �� �غ����� �����ϴ� �� ġ��
	char str[128];
	ZeroMemory(str, sizeof(str));

	//���� ������ ��ŭ �ݺ��Ѵ�.
	//������ǥX, ������ǥY, ����ü��, �ִ�ü��
	//  300,     300,      80,      100
	for (int i = 0; i < vArray.size(); ++i)
	{
		//vector<string> -> ���ڿ� char c_str()
		strncat_s(str, 128, vArray[i].c_str(), 126);
		//300,300,80,100

		if (i + 1 < vArray.size()) strcat_s(str, ",");
	}

	return str;
}

vector<string> txtData::txtLoad(const char * loadFileName)
{
	HANDLE file;
	DWORD read;

	char str[1024] = {};

	file = CreateFile(loadFileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 1024, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::textLoadPerLine( const char* loadFileName, const char* ignoreStr)
{
	HANDLE file;
	DWORD read;

	char str[2048] = {};
	char datas[2048] = {};

	file = CreateFile( loadFileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	
	ReadFile(file, str, 2048, &read, NULL);
	
	vector<string> txtData;

	char* temp;
	const char* separator = "\n\r"; //������
	char* token;

	token = strtok_s( str, separator, &temp );

	const int ignoreCharSize = strlen( ignoreStr );
	if ( ignoreCharSize < strlen( token ) )
	{
		for ( int ii = 0; ii < ignoreCharSize; ++ii )
		{
			if ( ignoreStr[ii] != token[ii] )
			{
				txtData.push_back( token );
				break;
			}
		}
	}

	while ( NULL != ( token = strtok_s( NULL, separator, &temp ) ) )
	{
		if ( ignoreCharSize < strlen( token ) )
		{
			for ( int ii = 0; ii < ignoreCharSize; ++ii )
				if ( ignoreStr[ii] != token[ii] )
				{
					txtData.push_back( token );
					break;
				}
		}
		else
			txtData.push_back( token );
	}

	return txtData;
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	const char* separator = " ,\n\r"; //������
	char* token;

	token = strtok_s(charArray, separator, &temp);
	vArray.push_back(token);

	while (NULL != (token = strtok_s(NULL, separator, &temp)))
	{
		vArray.push_back(token);
	}

	//300,300,80,100
	//300

	return vArray;
}


