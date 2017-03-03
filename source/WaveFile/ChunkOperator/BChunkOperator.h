/**
 * @file	BChunkOperator.h
 * @brief	WAVEファイルのChunkクラス.
 */

#ifndef __BCHUNKOPERATOR_H__
#define __BCHUNKOPERATOR_H__

#include <fstream>
using namespace std;

#ifndef __CWAVEFILE_H__
#include "../../CWaveFile.h"
#endif

#ifndef __CWAVEFILEUTILITY_H__
#include "../Utility/CWaveFileUtility.h"
#endif

/**
 * @brief	WAVEファイルのChunk.
 */
class BChunkOperator
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	BChunkOperator();
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~BChunkOperator(){ }

	/**
	 * @brief	WAVEファイルのChunkを読み込む.
	 * @param	ifstream& i_cFileStream.
	 * @param	CWaveFile& pcWaveFile
	 * @return	成功 / 失敗.
	 */
	virtual bool read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile);

	/**
	 * @brief	WAVEファイルのChunkを書き込む.
	 * @param	ifstream& i_cFileStream.
	 * @param	CWaveFile& pcWaveFile
	 * @return	成功 / 失敗.
	 */
	virtual bool write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile);

	/**
	 * @brief	Chunk IDを取得.
	 * @param	なし.
	 * @return	成功 / 失敗.
	 */
	virtual char* getChunkID()
	{
		return m_szID;
	}
	
	/**
	 * @brief	Chunk sizeを取得.
	 * @param	なし.
	 * @return	成功 / 失敗.
	 */
	virtual long getChunkSize()
	{
		return m_lSize;
	}
protected:
	/**
	 * @brief	Chunk情報を表示.
	 * @param	char* i_pbyMessage	表示したいメッセージ.
	 * @return	なし.
	 * @note	デバッグ用.
	 */
	void printChunk(char* i_pbyMessage);

	/**
	 * @brief	Chunk ID.
	 */
	char m_szID[4];
	
	/**
	 * @brief	Chunk size.
	 */
	long m_lSize;
	
	/**
	 * @brief	各Chunk独自の情報.
	 * @note	各Chunkでサイズが異なる為, ポインタのメモリ確保のみ.
	 */
	char* m_szChunkInfo;

	/**
	 * @brief	Chunk情報を出力するか否か.
	 */
	bool m_bIsPrintChunkInfo;
	
	/**
	 * @brief	デバッグフラグ.
	 */
	bool m_bIsDEBUG;
};

#endif	//__BCHUNKOPERATOR_H__

