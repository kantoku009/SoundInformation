
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

#include "CWaveFormatOperatorUtility.h"

#include "ReadSample/CFactoryReadSample.h"
#include "ReadSample/IReadSample.h"

#include "WriteSample/CFactoryWriteSample.h"
#include "WriteSample/IWriteSample.h"

#include "../CWaveFormatOperator.h"

// デバッグ用フラグ.
bool g_bIsDEBUG=false;

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

/**************************
 * WAVEファイルから読みこみ.
 **************************/
bool CWaveFormatOperator::readWaveFile(const string i_strFileName)
{
	ifstream   fp(i_strFileName.c_str(),ios::binary);
	TChunk     chunk;
    
	if(!fp)
	{
		cerr << "Can't Open " << i_strFileName << ".\n";
		return false;
	}
    
	try
	{
		//'RIFF'
		this->readRIFFChunk(fp);

		//'WAVE'
		this->readWAVEChunk(fp);

		while( fp.read((char*)&chunk,sizeof(chunk)) )
		{
			if(strncmp(chunk.id,"fmt ",4) == 0)
			{
				// 'fmt ' read.
				this->readFmtChunk(fp, chunk);
			}
			else if(strncmp(chunk.id,"data",4) == 0)
			{
				// 'data' read.
				this->readSample(fp, chunk);
			}
			else
			{
				long lSize = CWaveFormatOperatorUtility::convert4ByteDataToLong(chunk.size);
				fp.seekg(lSize,ios::cur);
				if(g_bIsDEBUG) this->printChunk((char*)"Read Chunk", chunk);
			}
		}
	}
	catch(WaveFormatError err)
	{
		cerr << err.what() << endl;
		return false;
	}
   
	return true;
}

/**************************************
 * WAVEファイルからRIFF chunkを読みこみ.
 **************************************/
bool CWaveFormatOperator::readRIFFChunk(ifstream& i_cFileStream)
{
	TChunk chunk;
	memset((char*)&chunk, 0x00, sizeof(chunk));

	i_cFileStream.read((char*)&chunk,sizeof(chunk));
	if(strncmp(chunk.id,"RIFF",4) != 0)
	{
		throw WaveFormatError((char*)"CWaveFormatOperator error: not RIFF file");
	}

	if(g_bIsDEBUG) printChunk((char*)"Read Chunk", chunk);
	return true;
}

/**************************************
 * WAVEファイルからWAVE chunkを読みこみ.
 **************************************/
bool CWaveFormatOperator::readWAVEChunk(ifstream& i_cFileStream)
{
	TChunk chunk;
	memset((char*)&chunk, 0x00, sizeof(chunk));

	i_cFileStream.read((char*)&chunk.id,sizeof(chunk.id));
	if(strncmp(chunk.id,"WAVE",4) != 0)
	{
		throw WaveFormatError((char*)"CWaveFormatOperator error: not WAVE file");
	}

	if(g_bIsDEBUG) printChunk((char*)"Read Chunk", chunk);
	return true;
}

/**************************************
 * WAVEファイルからfmt chunkを読みこみ.
 **************************************/
bool CWaveFormatOperator::readFmtChunk(ifstream& i_cFileStream, TChunk& i_stChunk)
{
	long a_lChunkSize = CWaveFormatOperatorUtility::convert4ByteDataToLong(i_stChunk.size);

	TFmtChunk fmt;
	memset((char*)&fmt, 0x00, sizeof(fmt));
	i_cFileStream.read((char*)&fmt, a_lChunkSize);

	long nSamplesPerSec = CWaveFormatOperatorUtility::convert4ByteDataToLong(fmt.nSamplesPerSec);
	short wBitsPerSample = CWaveFormatOperatorUtility::convert2ByteDataToShort(fmt.wBitsPerSample);
	short nChannels = CWaveFormatOperatorUtility::convert2ByteDataToShort(fmt.nChannels);

	this->setSampleRate(nSamplesPerSec);
	this->setBitsPerSample(wBitsPerSample);
	this->setNumChannels(nChannels);

	if(g_bIsDEBUG) printChunk((char*)"Read Chunk", i_stChunk);
	if(g_bIsDEBUG) printFmtChunk((char*)"Read fmt", fmt);
	return true;
}

/******************************************
 * WAVEファイルからSampleデータを読みこみ.
 ******************************************/
bool CWaveFormatOperator::readSample(ifstream& i_cFileStream, TChunk& i_stChunk)
{
	long lDataSize = CWaveFormatOperatorUtility::convert4ByteDataToLong(i_stChunk.size);
	this->setSamplesPerChannel(lDataSize/this->getBlockAlign());

	// 量子化ビットを取得.
	short a_BitsPerSample = this->getBitsPerSample();
	
	// サンプル値の読み込む方法を生成. (1サンプル 8bit, 16bit...のどれで読み込むかを決定).
	CFactoryReadSample a_CFactoryReadSample;
	IReadSample* i_pReadSample;
	i_pReadSample = a_CFactoryReadSample.create(a_BitsPerSample);
	
	// read sample.
	//bool a_bIsReadSuccess;
	for(long index=0;index<this->getSamplesPerChannel();index++)
	{
		for(short channel=0;channel<this->getNumChannels();channel++)
		{
			double a_dSample = i_pReadSample->read(i_cFileStream);
			this->setSample(a_dSample, index, channel);
		}
	}
	
	//if(!a_bIsReadSuccess)
	//{
	//	throw WaveFormatError((char*)"CWaveFormatOperator error: read file");
	//	return false;
	//}

	if(g_bIsDEBUG) printChunk((char*)"Read Chunk", i_stChunk);
	return true;
}

/****************************************
 * WAVEファイルに書き込み.
 ****************************************/
bool CWaveFormatOperator::writeWaveFile(const string i_strFileName)
{
	ofstream      fp(i_strFileName.c_str(),ios::binary);
	if(!fp)
	{
		cerr << "CWaveFormatOperator error: do not open" << i_strFileName << endl;
		return false;
	}

	try
	{
		//'RIFF' write
		this->writeRIFFChunk(fp);
	   
		//'WAVE' write
		this->writeWAVEChunk(fp);
	    
		//'fmt ' write
		this->writeFmtChunk(fp);
		
		//'data' write
		this->writeSample(fp);
	}
	catch(WaveFormatError err)
	{
		cerr << err.what() << endl;
		return false;
	}
 
	return true;
}

/***************************************************
 * RIFF chunkをWAVEファイルへ書き込み.
 ***************************************************/
bool CWaveFormatOperator::writeRIFFChunk(ofstream& i_cFileStream)
{
	TChunk chunk;
	memset((char*)&chunk, 0x00, sizeof(chunk));

	long dataSize = this->getSamplesPerChannel() * this->getBlockAlign();

	strncpy(chunk.id,"RIFF",4);
	long lRIFFSize = 0;
	lRIFFSize = 4						//'WAVE'
				+ sizeof(TChunk)		//'fmt '
				+ sizeof(TFmtChunk)		//FMT Chunk
				+ sizeof(TChunk)		//'data'
				+ dataSize;				//全サンプルのサイズ.
	CWaveFormatOperatorUtility::convertLongTo4ByteData(lRIFFSize, chunk.size);

	// chunkをファイルへ書き込み.
	i_cFileStream.write((char*)&chunk,sizeof(chunk));

	if(g_bIsDEBUG) printChunk((char*)"Write Chunk", chunk);
	return true;
}

/************************************
 * WAVE chunkをWAVEファイルへ書き込み.
 ************************************/
bool CWaveFormatOperator::writeWAVEChunk(ofstream& i_cFileStream)
{
	TChunk chunk;
	memset((char*)&chunk, 0x00, sizeof(chunk));

	strncpy(chunk.id, "WAVE", 4);
	i_cFileStream.write(chunk.id, 4);

	if(g_bIsDEBUG) printChunk((char*)"Write Chunk", chunk);
	return true;
}

/***********************************************
* fmt chunkをWAVEファイルへ書き込み.
************************************************/
bool CWaveFormatOperator::writeFmtChunk(ofstream& i_cFileStream)
{
	TChunk chunk;
	memset((char*)&chunk, 0x00, sizeof(chunk));
	TFmtChunk fmt;
	memset((char*)&fmt, 0x00, sizeof(fmt));

	strncpy(chunk.id,"fmt ",4);
	long lFmtSize = sizeof(fmt);
	CWaveFormatOperatorUtility::convertLongTo4ByteData(lFmtSize, chunk.size);
	// chunkをファイルへ書き込み.
	i_cFileStream.write((char*)&chunk,sizeof(chunk));

	short wFormatTag = 1;
	CWaveFormatOperatorUtility::convertShortTo2ByteData(wFormatTag, fmt.wFormatTag);

	short nChannels = this->getNumChannels();
	CWaveFormatOperatorUtility::convertShortTo2ByteData(nChannels, fmt.nChannels);

	long nSamplesPerSec = this->getSampleRate();
	CWaveFormatOperatorUtility::convertLongTo4ByteData(nSamplesPerSec, fmt.nSamplesPerSec);

	long nAvgBytesPerSec = this->getBlockAlign() * this->getSampleRate();
	CWaveFormatOperatorUtility::convertLongTo4ByteData(nAvgBytesPerSec, fmt.nAvgBytesPerSec);

	short nBlockAlign = this->getBlockAlign();
	CWaveFormatOperatorUtility::convertShortTo2ByteData(nBlockAlign, fmt.nBlockAlign);

	short wBitsPerSample = this->getBitsPerSample();
	CWaveFormatOperatorUtility::convertShortTo2ByteData(wBitsPerSample, fmt.wBitsPerSample);

	// fmt chunkをファイルへ書き込み.
	i_cFileStream.write((char*)&fmt,sizeof(fmt));

	if(g_bIsDEBUG) printChunk((char*)"Write Chunk", chunk);
	if(g_bIsDEBUG) printFmtChunk((char*)"Write FMT Chunk", fmt);
	return true;
}

/****************************************
* SampleデータをWAVEファイルへ書き込み.
*****************************************/
bool CWaveFormatOperator::writeSample(ofstream& i_cFileStream)
{
	TChunk chunk;
	memset((char*)&chunk, 0x00, sizeof(chunk));

	strncpy(chunk.id,"data",4);
	long lDataSize = this->getSamplesPerChannel() * this->getBlockAlign();
	CWaveFormatOperatorUtility::convertLongTo4ByteData(lDataSize, chunk.size);
	// chunkをファイルへ書き込み.
	i_cFileStream.write((char*)&chunk,sizeof(chunk));
    
	// 量子化ビットを取得.
	short a_BitsPerSample = this->getBitsPerSample();
	
	// サンプル値の読み込む方法を生成. (1サンプル 8bit, 16bit...のどれで読み込むかを決定).
	CFactoryWriteSample a_CFactoryWriteSample;
	IWriteSample* i_pWriteSample;
	i_pWriteSample = a_CFactoryWriteSample.create(a_BitsPerSample);
	
	// write sample.
	bool a_bIsWriteSuccess = true;
	for(long index=0;index<this->getSamplesPerChannel();index++)
	{
		for(short channel=0;channel<this->getNumChannels();channel++)
		{
			double a_Sample = this->getSample(index,channel);
			a_bIsWriteSuccess = i_pWriteSample->write(a_Sample, i_cFileStream);
			if(a_bIsWriteSuccess) break;
			
		}
	}

	if(!a_bIsWriteSuccess)
	{
		throw WaveFormatError((char*)"CWaveFormatOperator error: write file");
		return false;
	}

	if(g_bIsDEBUG) printChunk((char*)"Write Sample Chunk", chunk);
	return true;
}

/****************************************
 * TChunkを表示.
 * デバッグ用.
 ****************************************/
void CWaveFormatOperator::printChunk(char* i_pbyMessage, TChunk& i_stChunk)
{
	printf("%s\n", i_pbyMessage);
	printf("  %c%c%c%c\n", i_stChunk.id[0], i_stChunk.id[1], i_stChunk.id[2], i_stChunk.id[3]);
	long lSize = CWaveFormatOperatorUtility::convert4ByteDataToLong(i_stChunk.size);
	printf("  %lX\n", lSize);
}

/**********************************
 * TFmtChunkを表示.
 * デバッグ用.
 **********************************/
void CWaveFormatOperator::printFmtChunk(char* i_pbyMessage, TFmtChunk& i_stFmtChunk)
{
	short wFormatTag = CWaveFormatOperatorUtility::convert2ByteDataToShort(i_stFmtChunk.wFormatTag);
	short nChannels = CWaveFormatOperatorUtility::convert2ByteDataToShort(i_stFmtChunk.nChannels);
	long  nSamplesPerSec = CWaveFormatOperatorUtility::convert4ByteDataToLong(i_stFmtChunk.nSamplesPerSec);
	long  nAvgBytesPerSec = CWaveFormatOperatorUtility::convert4ByteDataToLong(i_stFmtChunk.nAvgBytesPerSec);
	short nBlockAlign = CWaveFormatOperatorUtility::convert2ByteDataToShort(i_stFmtChunk.nBlockAlign);
	short wBitsPerSample = CWaveFormatOperatorUtility::convert2ByteDataToShort(i_stFmtChunk.wBitsPerSample);

	printf("%s\n", i_pbyMessage);
	printf("  wFormatTag = %X\n", wFormatTag);
	printf("  nChannels = %X\n", nChannels);
	printf("  nSamplesPerSec = %lX\n", nSamplesPerSec);
	printf("  nAvgBytesPerSec = %lX\n", nAvgBytesPerSec);
	printf("  nBlockAlign = %X\n", nBlockAlign);
	printf("  wBitsPerSample = %X\n", wBitsPerSample);
}


