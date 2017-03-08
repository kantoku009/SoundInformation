/**
 * @file	CWaveFile.cpp
 * @brief	WAVEファイルを操作するクラス.
 */
 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

#ifndef __CWAVEFILE_H__
#include "../CWaveFile.h"
#endif

#ifndef __CCHUNKFACTORY_H__
#include "./ChunkOperator/CChunkFactory.h"
#endif

#ifndef __BCHUNKOPERATOR_H__
#include "./ChunkOperator/BChunkOperator.h"
#endif

class WaveFormatError
{
public:
	WaveFormatError(char *message)
	{
		size_t len;

		len = strlen(message);
		mMessage = new char [len+1];
		strcpy(mMessage,message);
	}
	const char* what() const { return mMessage; }
private:
	char* mMessage;
};

/**
 * WAVEファイルから読みこみ.
 */
bool CWaveFile::read(const string i_strFileName)
{
	ifstream   fp(i_strFileName.c_str(),ios::binary);

	if(!fp)
	{
		cerr << "Can't Open " << i_strFileName << ".\n";
		return false;
	}
	
	// Chunkファクトリを生成.
	CChunkFactory a_cChunkFactory;
	BChunkOperator* a_pbChunk = NULL;
	bool a_bIsSuccess = true;

	try
	{
		// 'RIFF' (ファイルの先頭はRIFF Chunk).
		a_pbChunk = a_cChunkFactory.create((char*)"RIFF");
		a_bIsSuccess = a_pbChunk->read(fp, *this);
		if(false == a_bIsSuccess)
		{
			throw WaveFormatError(a_pbChunk->getChunkID()); 
		}

		while( !fp.eof() )
		{
			a_pbChunk = a_cChunkFactory.search(fp);
			if(NULL == a_pbChunk)
			{
				break;
			}
			
			a_bIsSuccess = a_pbChunk->read(fp, *this);
			if(false == a_bIsSuccess)
			{
				throw WaveFormatError(a_pbChunk->getChunkID());
			}
		}
	}
	catch(WaveFormatError err)
	{
		char a_szErrorString[256];
		char a_szChunkID[5];
		memset(a_szChunkID, 0x00, 5);
		memcpy(a_szChunkID, err.what(), 4);
		sprintf(a_szErrorString, "CWaveFile read error: %s chunk.", a_szChunkID);
		cerr << a_szErrorString << endl;
		return false;
	}
   
	return true;
}

/**
 * WAVEファイルに書き込み.
 */
bool CWaveFile::write(const string i_strFileName)
{
	ofstream	fp(i_strFileName.c_str(),ios::binary);
	if(!fp)
	{
		cerr << "CWaveFile error: do not open" << i_strFileName << endl;
		return false;
	}

	const char* a_rgszID[] = 
	{
		"RIFF",
		"fmt ",
		"data"
	};

	// Chunkファクトリを生成.
	CChunkFactory a_cChunkFactory;
	BChunkOperator* a_pbChunk = NULL;
	bool a_bIsSuccess = true;
	try
	{
		short a_shLoopMax = sizeof(a_rgszID) / sizeof(a_rgszID[0]);
		for(short a_shIndex=0; a_shIndex < a_shLoopMax; a_shIndex++)
		{
			const char* a_pszID = a_rgszID[a_shIndex];
			a_pbChunk = a_cChunkFactory.create(a_pszID);
			a_bIsSuccess = a_pbChunk->write(fp, *this);
			if(false == a_bIsSuccess)
			{
				throw WaveFormatError((char*)a_pszID);
			}
		}
	}
	catch(WaveFormatError err)
	{
		char a_szErrorString[256];
		char a_szChunkID[5];
		memset(a_szChunkID, 0x00, 5);
		memcpy(a_szChunkID, err.what(), 4);
		sprintf(a_szErrorString, "CWaveFile read error: %s chunk.", a_szChunkID);
		cerr << a_szErrorString << endl;
		return false;
	}
 
	return true;
}

