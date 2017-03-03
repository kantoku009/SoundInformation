/**
 * @file	CFmtChunkOperator.cpp
 * @brief	WAVEファイルのfmt Chunkクラス.
 */

#include <cstring>
using namespace std;

#ifndef __CFMTCHUNKOPERATOR_H__
#include "CFmtChunkOperator.h"
#endif

#define DEF_CHUNK_ID_FMT "fmt "

/**
 * コンストラクタ.
 */
CFmtChunkOperator::CFmtChunkOperator()
{
	strncpy(m_szID, "fmt ", 4);
	m_lSize = sizeof(T_FMT_CHUNK);
	m_szChunkInfo = (char*)&m_stFmt;
}

/**
 * fmt chunkをファイルから読み込み.
 */
bool  CFmtChunkOperator::read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	bool a_bIsSuccess = true;
	
	a_bIsSuccess = BChunkOperator::read(i_cFileStream, i_pcWaveFile);
	if(!a_bIsSuccess)
	{
		if(m_bIsDEBUG) printf("failed:fmt  chunk do not read.\n");
		return false;
	}

	// 自分自身のChunk IDと比較.
	if( 0 != strncmp(this->m_szID, DEF_CHUNK_ID_FMT, sizeof(this->m_szID)) )
	{
		if(m_bIsDEBUG) printf("failed:RIFF read. not chunk.\n");
		this->m_lSize = 0;
		return false;
	}

	// fmt をファイルから読み込み.
	T_FMT_CHUNK a_stFmt;
	memset((char*)&a_stFmt, 0x00, sizeof(a_stFmt));
	size_t a_uReaded = 0;
	a_uReaded = i_cFileStream.readsome((char*)&a_stFmt, sizeof(a_stFmt));
	if(sizeof(a_stFmt) != a_uReaded)
	{
		if(m_bIsDEBUG) printf("failed:fmt do not read.\n");
		return false;
	}

	// fmt Exサイズ分だけ読み飛ばす.
	long a_lSize = this->m_lSize - sizeof(a_stFmt);
	if(0 != a_lSize)
	{
		i_cFileStream.seekg(a_lSize,ios::cur);
	}
	
	long nSamplesPerSec = CWaveFileUtility::convert4ByteDataToLong(a_stFmt.m_nSamplesPerSec);
	short wBitsPerSample = CWaveFileUtility::convert2ByteDataToShort(a_stFmt.m_wBitsPerSample);
	short nChannels = CWaveFileUtility::convert2ByteDataToShort(a_stFmt.m_nChannels);

	i_pcWaveFile.setSampleRate(nSamplesPerSec);
	i_pcWaveFile.setBitsPerSample(wBitsPerSample);
	i_pcWaveFile.setNumChannels(nChannels);

	if(m_bIsPrintChunkInfo) printChunk((char*)"Read Chunk");
	if(m_bIsPrintChunkInfo) printFmtChunk((char*)"Read fmt", a_stFmt);
	return true;
}

/**
 * fmt chunkをファイルへ書き込み.
 */
bool CFmtChunkOperator::write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	T_FMT_CHUNK a_stFmt;
	memset((char*)&a_stFmt, 0x00, sizeof(a_stFmt));

	// "fmt " Chunk IDをコピー.
	memcpy(this->m_szID, DEF_CHUNK_ID_FMT, sizeof(this->m_szID));

	// "fmt "のサイズを計算.
	this->m_lSize = sizeof(a_stFmt);
	
	short wFormatTag = 1;
	CWaveFileUtility::convertShortTo2ByteData(wFormatTag, a_stFmt.m_wFormatTag);

	short nChannels = i_pcWaveFile.getNumChannels();
	CWaveFileUtility::convertShortTo2ByteData(nChannels, a_stFmt.m_nChannels);

	long nSamplesPerSec = i_pcWaveFile.getSampleRate();
	CWaveFileUtility::convertLongTo4ByteData(nSamplesPerSec, a_stFmt.m_nSamplesPerSec);

	long nAvgBytesPerSec = i_pcWaveFile.getBlockAlign() * i_pcWaveFile.getSampleRate();
	CWaveFileUtility::convertLongTo4ByteData(nAvgBytesPerSec, a_stFmt.m_nAvgBytesPerSec);

	short nBlockAlign = i_pcWaveFile.getBlockAlign();
	CWaveFileUtility::convertShortTo2ByteData(nBlockAlign, a_stFmt.m_nBlockAlign);

	short wBitsPerSample = i_pcWaveFile.getBitsPerSample();
	CWaveFileUtility::convertShortTo2ByteData(wBitsPerSample, a_stFmt.m_wBitsPerSample);

	// Chunk ID および Chunk Sizeをファイルへ書き込み.
	BChunkOperator::write(i_cFileStream, i_pcWaveFile);

	// fmt chunkをファイルへ書き込み.
	i_cFileStream.write((char*)&a_stFmt, sizeof(a_stFmt));

	if(m_bIsPrintChunkInfo) printChunk((char*)"Write Chunk");
	if(m_bIsPrintChunkInfo) printFmtChunk((char*)"Write FMT Chunk", a_stFmt);
	return true;
}

/**
 * T_FMT_CHUNKを表示.
 * デバッグ用.
 */
void CFmtChunkOperator::printFmtChunk(char* i_pbyMessage, T_FMT_CHUNK& i_stFmtChunk)
{
	short wFormatTag = CWaveFileUtility::convert2ByteDataToShort(i_stFmtChunk.m_wFormatTag);
	short nChannels = CWaveFileUtility::convert2ByteDataToShort(i_stFmtChunk.m_nChannels);
	long  nSamplesPerSec = CWaveFileUtility::convert4ByteDataToLong(i_stFmtChunk.m_nSamplesPerSec);
	long  nAvgBytesPerSec = CWaveFileUtility::convert4ByteDataToLong(i_stFmtChunk.m_nAvgBytesPerSec);
	short nBlockAlign = CWaveFileUtility::convert2ByteDataToShort(i_stFmtChunk.m_nBlockAlign);
	short wBitsPerSample = CWaveFileUtility::convert2ByteDataToShort(i_stFmtChunk.m_wBitsPerSample);

	printf("%s\n", i_pbyMessage);
	printf("  wFormatTag = %X\n", wFormatTag);
	printf("  nChannels = %X\n", nChannels);
	printf("  nSamplesPerSec = %lX\n", nSamplesPerSec);
	printf("  nAvgBytesPerSec = %lX\n", nAvgBytesPerSec);
	printf("  nBlockAlign = %X\n", nBlockAlign);
	printf("  wBitsPerSample = %X\n", wBitsPerSample);
}

