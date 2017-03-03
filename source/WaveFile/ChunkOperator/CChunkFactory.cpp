/**
 * @file	CChunkFactory.cpp
 * @brief	WAVEファイルのChunkクラス.
 */

#include <cstring>
using namespace std;

#ifndef __CCHUNKFACTORY_H__
#include "CChunkFactory.h"
#endif

/**
 * コンストラクタ.
 */
CChunkFactory::CChunkFactory()
{
	//m_mapChunk[m_cRIFFChunkOperator.getChunkID()] = m_cRIFFChunkOperator;
	//m_mapChunk[m_cWAVEChunkOperator.getChunkID()] = m_cWAVEChunkOperator;
	//m_mapChunk[m_cFmtChunkOperator.getChunkID()] = m_cFmtChunkOperator;
	//m_mapChunk[m_cDataChunkOperator.getChunkID()] = m_cDataChunkOperator;
	//m_mapChunk[m_cOtherChunkOperator.getChunkID()] = m_cOtherChunkOperator;
}

/**
 * WAVE chunkをファイルから読み込み.
 */
BChunkOperator*  CChunkFactory::create(const char* i_szID)
{
	//return &m_mapChunk[i_szID];
	BChunkOperator* rgbChunkOperator[] =
	{
		&m_cRIFFChunkOperator,
		&m_cFmtChunkOperator,
		&m_cDataChunkOperator,
		&m_cOtherChunkOperator,
	};
	short a_shLoopMax = sizeof(rgbChunkOperator) / sizeof(rgbChunkOperator[0]);
	for(short a_shIndex=0; a_shIndex<a_shLoopMax; a_shIndex++)
	{
		if(0 == memcmp(rgbChunkOperator[a_shIndex]->getChunkID(), i_szID, 4) )
		{
			return rgbChunkOperator[a_shIndex];
		}
	}
	return &m_cOtherChunkOperator;
}

/**
 * チャンクを探す.
 */
BChunkOperator* CChunkFactory::search(ifstream& i_cFileStream)
{
	char a_szID[4] = "";
	size_t a_uReaded = 0;

	a_uReaded = i_cFileStream.readsome(a_szID, sizeof(a_szID));
	if(sizeof(a_szID) != a_uReaded)
	{
		return NULL;
	}

	// chunkID分だけ戻す.
	for(unsigned short a_ushLoop=0; a_ushLoop<sizeof(a_szID); a_ushLoop++)
	{
		i_cFileStream.unget();
	}

	return this->create(a_szID);
}

