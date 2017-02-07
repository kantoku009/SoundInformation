/**
 * @file	CWAVEChunkOperator.cpp
 * @brief	WAVEファイルのChunkクラス.
 */

#include <cstring>
using namespace std;

#ifndef __CWAVECHUNKOPERATOR_H__
#include "CWAVEChunkOperator.h"
#endif

/**
 * コンストラクタ.
 */
CWAVEChunkOperator::CWAVEChunkOperator()
{
	strncpy(m_szID, "WAVE", 4);
	m_lSize = 0;
}

/**
 * WAVE chunkをファイルから読み込み.
 */
bool  CWAVEChunkOperator::read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile, T_CHUNK& i_stChunk)
{
	memset((char*)&i_stChunk, 0x00, sizeof(i_stChunk));
	
	// ファイルから読み込み.
	i_cFileStream.read((char*)&i_stChunk.m_szID, sizeof(i_stChunk.m_szID));
	
	// 自分自身のChunk IDと比較.
	if( 0 != strncmp(i_stChunk.m_szID, this->m_szID, sizeof(i_stChunk.m_szID) ) )
	{
		return false;
	}

	if(m_bIsDEBUG) printChunk((char*)"Read Chunk", i_stChunk);
	return true;
}

/**
 * WAVE chunkをファイルへ書き込み.
 */
bool CWAVEChunkOperator::write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	T_CHUNK a_stChunk;
	memset((char*)&a_stChunk, 0x00, sizeof(a_stChunk));

	// Chunk IDを書き込む.
	strncpy(a_stChunk.m_szID, this->m_szID, sizeof(a_stChunk.m_szID));
	i_cFileStream.write(a_stChunk.m_szID, sizeof(a_stChunk.m_szID) );
	
	if(m_bIsDEBUG) printChunk((char*)"Write Chunk", a_stChunk);
	return true;
}

