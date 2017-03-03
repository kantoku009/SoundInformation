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
	memset(m_szID, 0x00, sizeof(m_szID));
	m_lSize = 0;
	m_szChunkInfo = NULL;
	
	m_bIsPrintChunkInfo = true;
	m_bIsDEBUG = true;
}

/**
 * chunkをファイルから読み込み.
 */
bool  BChunkOperator::read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	size_t a_uReaded = 0;
	char a_szID[4];
	char a_szSize[4];
	
	memset(a_szID, 0x00, sizeof(a_szID));
	memset(a_szSize, 0x00, sizeof(a_szSize));

	// Chunk IDをファイルから読み込み.
	a_uReaded= i_cFileStream.readsome(a_szID, sizeof(a_szID));
	if(sizeof(a_szID) != a_uReaded)
	{
		if(m_bIsDEBUG) printf("failed:BChunk do not read. %02x %02x %02x %02x\n", a_szID[0], a_szID[1], a_szID[2], a_szID[3]);
		return false;
	}
	memcpy(this->m_szID, a_szID, sizeof(this->m_szID));
	
	// Chunk sizeをファイルから読み込み.
	a_uReaded= i_cFileStream.readsome(a_szSize, sizeof(a_szSize));
	if(sizeof(a_szID) != a_uReaded)
	{
		if(m_bIsDEBUG) printf("failed:BChunk Size read.\n");
		return false;
	}
	// Chunk sizeを設定.
	this->m_lSize = CWaveFileUtility::convert4ByteDataToLong(a_szSize);

	return true;
}

/**
 * chunkをファイルへ書き込み.
 */
bool BChunkOperator::write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	// Chunk IDを書き込む
	i_cFileStream.write( this->m_szID, sizeof(this->m_szID) );

	// Chunk Sizeをファイルへ書き込む.
	char a_szSize[4];
	CWaveFileUtility::convertLongTo4ByteData(this->m_lSize, a_szSize);
	i_cFileStream.write(a_szSize, sizeof(a_szSize));

	return true;
}

/**
 * Chunkを表示.
 */
void BChunkOperator::printChunk(char* i_pbyMessage)
{
	printf("%s\n", i_pbyMessage);
	printf("  %c%c%c%c\n", this->m_szID[0], this->m_szID[1], this->m_szID[2], this->m_szID[3]);
	printf("  0x%08lX\n", m_lSize);
}

