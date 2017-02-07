/**
 * @file	CFmtChunkOperator.h
 * @brief	WAVEファイルのChunkクラス.
 */

#ifndef __CFMTCHUNKOPERATOR_H__
#define __CFMTCHUNKOPERATOR_H__

#include <fstream>
using namespace std;

#ifndef __BCHUNKOPERATOR_H__
#include "./BChunkOperator.h"
#endif

/**
 * @brief	WaveファイルのFMT Chunk構造体.
 */
typedef struct T_FMT_CHUNK
{
	char m_wFormatTag[2];
	char m_nChannels[2];
	char m_nSamplesPerSec[4];
	char m_nAvgBytesPerSec[4];
	char m_nBlockAlign[2];
	char m_wBitsPerSample[2];
}T_FMT_CHUNK;

/**
 * @brief	WAVEファイルのChunk.
 */
class CFmtChunkOperator : public BChunkOperator
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CFmtChunkOperator();
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CFmtChunkOperator(){ }

	/**
	 * @brief	WAVEファイルのChunkを読み込む.
	 * @param	T_CHUNK& i_stChunk
	 * @param	CWaveFile& pcWaveFile
	 * @param	ifstream& i_cFileStream.
	 * @return	成功 / 失敗.
	 */
	bool read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile, T_CHUNK& i_stChunk);
	
	/**
	 * @brief	WAVEファイルのChunkを書き込む.
	 * @param	T_CHUNK& i_stChunk
	 * @param	CWaveFile& pcWaveFile
	 * @param	ifstream& i_cFileStream.
	 * @return	成功 / 失敗.
	 */
	bool write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile);

protected:
	/**
	 * @brief	TFmtChunkを表示.
	 * @param	char* i_pbyMessage		表示したいメッセージ.
	 * @param	TFmtChunk& i_stFmtChunk	表示したいTFmtChunk
	 * @return	なし.
	 * @note	デバッグ用.
	 */
	void printFmtChunk(char* i_pbyMessage, T_FMT_CHUNK& i_stFmtChunk);
};

#endif	//__CFMTCHUNKOPERATOR_H__

