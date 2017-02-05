/**
 * @file	BChunkOperator.cpp
 * @brief	WAVEファイルのChunkクラス.
 */

#include <cstring>
using namespace std;

#ifndef __BCHUNKOPERATOR_H__
#include "./BChunkOperator.h"
#endif

/**
 * コンストラクタ.
 */
BChunkOperator::BChunkOperator()
{
	strncpy(m_szID, "", 4);
	m_lSize = 0;

	m_bIsDEBUG = false;
}

/**
 * chunkをファイルから読み込み.
 */
bool  BChunkOperator::read(ifstream& i_cFileStream, CWaveFormatOperator& i_pcWaveFormatOperator, T_CHUNK& i_stChunk)
{
	long lSize = CWaveFormatOperatorUtility::convert4ByteDataToLong(i_stChunk.m_szSize);
	i_cFileStream.seekg(lSize,ios::cur);
	if(m_bIsDEBUG) this->printChunk((char*)"Read Chunk", i_stChunk);
	return true;
}

/**
 * chunkをファイルへ書き込み.
 */
bool BChunkOperator::write(ofstream& i_cFileStream, CWaveFormatOperator& i_pcWaveFormatOperator)
{
	return true;
}

/**
 * T_CHUNKを表示.
 */
void BChunkOperator::printChunk(char* i_pbyMessage, T_CHUNK& i_stChunk)
{
	printf("%s\n", i_pbyMessage);
	printf("  %c%c%c%c\n", i_stChunk.m_szID[0], i_stChunk.m_szID[1], i_stChunk.m_szID[2], i_stChunk.m_szID[3]);
	long lSize = CWaveFormatOperatorUtility::convert4ByteDataToLong(i_stChunk.m_szSize);
	printf("  0x%08lX\n", lSize);
}
