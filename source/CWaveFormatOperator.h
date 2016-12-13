/**
 * @file	CWaveFormatOperator.h
 * @brief	WAVEファイルを扱うクラス.
 */

#ifndef __CWAVE_FORMAT_OPERATOR_H__
#define __CWAVE_FORMAT_OPERATOR_H__

#include <fstream>
using namespace std;

#include "BSoundInformation.h"

/**
 * @brief	WaveファイルのChunk構造体.
 */
typedef struct TChunk
{
	char id[4];
	char size[4];
}TChunk;

/**
 * @brief	WaveファイルのFMT Chunk構造体.
 */
typedef struct TFmtChunk
{
	char wFormatTag[2];
	char nChannels[2];
	char nSamplesPerSec[4];
	char nAvgBytesPerSec[4];
	char nBlockAlign[2];
	char wBitsPerSample[2];
}TFmtChunk;


/**
 * @brief	WAVEファイルを扱うクラス.
 */
class CWaveFormatOperator : public BSoundInformation
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CWaveFormatOperator(
						long  sampleRate=44100,
						short bitsPerSample=8,
						short numChannels=1,
						long  numSamples=44100)
			:BSoundInformation(
							sampleRate, 
							bitsPerSample, 
							numChannels, 
							numSamples)
	{
	}
							
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CWaveFormatOperator(){ }

	/**
	 * @brief	WAVEファイルから読みこみ.
	 * @param	const string i_strFilename
	 * @return	成功/失敗.
	 */
	bool readWaveFile(const string i_strFileName);

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	const string i_strFileName	ファイル名.
	 * @return	成功/失敗.
	 */
	bool writeWaveFile(const string i_strFileName);

private:
	/**
	 * @brief	WAVEファイルからRIFF chunkを読みこみ.
	 * @param	ifstream i_cFileStream	読み込みファイルストリーム.
	 * @return	成功/失敗.
	 */
	bool readRIFFChunk(ifstream& i_cFileStream);

	/**
	 * @brief	WAVEファイルからWAVE chunkを読みこみ.
	 * @param	ifstream i_cFileStream	読み込みファイルストリーム.
	 * @return	成功/失敗.
	 */
	bool readWAVEChunk(ifstream& i_cFileStream);

	/**
	 * @brief	WAVEファイルからfmt chunkを読みこみ.
	 * @param	ifstream i_cFileStream	読み込みファイルストリーム.
	 * @return	成功/失敗.
	 */
	bool readFmtChunk(ifstream& i_cFileStream, TChunk& i_stChunk);

	/**
	 * @brief	WAVEファイルからSampleデータを読みこみ.
	 * @param	ifstream i_cFileStream	読み込みファイルストリーム.
	 * @return	成功/失敗.
	 */
	bool readSample(ifstream& i_cFileStream, TChunk& i_stChunk);

	/**
	 * @brief	RIFF chunkをWAVEファイルへ書き込み.
	 * @param	ofstream& i_cFileStream	書き込みファイルストリーム.
	 * @return	成功/失敗.
	 */
	bool writeRIFFChunk(ofstream& i_cFileStream);

	/**
	 * @brief	WAVE chunkをWAVEファイルへ書き込み.
	 * @param	ofstream& i_cFileStream	書き込みファイルストリーム.
	 * @return	成功/失敗.
	 */
	bool writeWAVEChunk(ofstream& i_cFileStream);

	/**
	 * @brief	fmt chunkをWAVEファイルへ書き込み.
	 * @param	ofstream& i_cFileStream	書き込みファイルストリーム.
	 * @return	成功/失敗.
	 */
	bool writeFmtChunk(ofstream& i_cFileStream);

	/**
	 * @brief	SampleデータをWAVEファイルへ書き込み.
	 * @param	ofstream& i_cFileStream	書き込みファイルストリーム.
	 * @return	成功/失敗.
	 */
	bool writeSample(ofstream& i_cFileStream);

	/**
	 * @brief	TChunkを表示.
	 * @param	char* i_pbyMessage	表示したいメッセージ.
	 * @param	TChunk i_stChunk	表示したいTChunk.
	 * @return	なし.
	 * @note	デバッグ用.
	 */
	void printChunk(char* i_pbyMessage, TChunk& i_stChunk);

	/**
	 * @brief	TFmtChunkを表示.
	 * @param	char* i_pbyMessage		表示したいメッセージ.
	 * @param	TFmtChunk& i_stFmtChunk	表示したいTFmtChunk
	 * @return	なし.
	 * @note	デバッグ用.
	 */
	void printFmtChunk(char* i_pbyMessage, TFmtChunk& i_stFmtChunk);
};

#endif	//__CWAVE_FORMAT_OPERATOR_H__

