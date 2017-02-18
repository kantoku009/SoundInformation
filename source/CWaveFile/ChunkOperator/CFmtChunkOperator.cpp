/**
 * @file	CFmtChunkOperator.cpp
 * @brief	WAVEファイルのfmt Chunkクラス.
 */

#include <cstring>
using namespace std;

#ifndef __CFMTCHUNKOPERATOR_H__
#include "CFmtChunkOperator.h"
#endif

/**
 * コンストラクタ.
 */
CFmtChunkOperator::CFmtChunkOperator()
{
	strncpy(m_szID, "fmt ", 4);
	m_lSize = 0;
}

/**
 * fmt chunkをファイルから読み込み.
 */
bool  CFmtChunkOperator::read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile, T_CHUNK& i_stChunk)
{
	long a_lChunkSize = CWaveFileUtility::convert4ByteDataToLong(i_stChunk.m_szSize);
	
	T_FMT_CHUNK a_stFmt;
	memset((char*)&a_stFmt, 0x00, sizeof(a_stFmt));
	i_cFileStream.read((char*)&a_stFmt, a_lChunkSize);

	long nSamplesPerSec = CWaveFileUtility::convert4ByteDataToLong(a_stFmt.m_nSamplesPerSec);
	short wBitsPerSample = CWaveFileUtility::convert2ByteDataToShort(a_stFmt.m_wBitsPerSample);
	short nChannels = CWaveFileUtility::convert2ByteDataToShort(a_stFmt.m_nChannels);

	i_pcWaveFile.setSampleRate(nSamplesPerSec);
	i_pcWaveFile.setBitsPerSample(wBitsPerSample);
	i_pcWaveFile.setNumChannels(nChannels);

	if(m_bIsDEBUG) printChunk((char*)"Read Chunk", i_stChunk);
	if(m_bIsDEBUG) printFmtChunk((char*)"Read fmt", a_stFmt);
	return true;
}

/**
 * fmt chunkをファイルへ書き込み.
 */
bool CFmtChunkOperator::write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	T_CHUNK a_stChunk;
	memset((char*)&a_stChunk, 0x00, sizeof(a_stChunk));
	T_FMT_CHUNK a_stFmt;
	memset((char*)&a_stFmt, 0x00, sizeof(a_stFmt));

	// "fmt "をコピー.
	strncpy(a_stChunk.m_szID, this->m_szID, sizeof(a_stChunk.m_szID));
	
	// "fmt "のサイズを計算.
	long lFmtSize = sizeof(a_stFmt);
	CWaveFileUtility::convertLongTo4ByteData(lFmtSize, a_stChunk.m_szSize);
	
	// chunkをファイルへ書き込み.
	i_cFileStream.write((char*)&a_stChunk, sizeof(a_stChunk));

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

	// fmt chunkをファイルへ書き込み.
	i_cFileStream.write((char*)&a_stFmt, sizeof(a_stFmt));

	if(m_bIsDEBUG) printChunk((char*)"Write Chunk", a_stChunk);
	if(m_bIsDEBUG) printFmtChunk((char*)"Write FMT Chunk", a_stFmt);
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

