/**
 * @file	CMp3File.h
 * @brief	MP3ファイルを操作するクラス.
 */
#ifndef __CMP3FILE_H__
#define __CMP3FILE_H__

#include <fstream>
using namespace std;

#ifndef __BWAVEFORM_H__
#include "BWaveForm.h"
#endif

// クラス前方宣言.
class CMpegFrame;

/**
 * @brief	MP3ファイルを扱うクラス.
 */
class CMp3File : public BWaveForm
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CMp3File()
	{ 
		m_bIsDebug = true;
	}

	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CMp3File(){ }

	/**
	 * @brief	MP3ファイルから読み込み.
	 * @param	const string i_strFileName
	 * @return	成功/失敗.
	 */
	bool read(const string i_strFileName);

	/**
	 * @brief	MP3ファイルに書き込み.
	 * @param	const string i_strFileName
	 * @return	成功/失敗.
	 * @note	未実装.
	 */
	bool write(const string i_strFileName){ return true; }

private:
	/**
	 * @brief	MPEG Frameを探す.
	 * @param	[in ] ifstream& i_cFileStream
	 * @param	[out]CMpegFrame& i_cMpegFrame
	 * @return	成功/失敗.
	 */
	bool seekMpegFrame( ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame );

	/**
	 * @brief
	 */
	bool seekMpegFrameAfter(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame);

	/**
	 * @brief	CRCを読み込み.
	 */
	bool readCRC(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame);

	/**
	 * @brief	サイド情報を読み込み.
	 * @param	[in]ifstream& i_cFileStream
	 * @param	[in]CMpegFrame& i_cMpegFrame
	 * @param	[out]char* i_pbySide
	 */
	bool readSideInfo(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame, char* i_pbySide);

	/**
	 * @brief	メインデータを読み込み.
	 */
	bool readMainData(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame);

	/**
	 * @brief	4バイト分ファイルから読む.
	 * @param	[out]ifstream& i_cFileStream
	 * @param	[out]unsigned long& i_ulHeader
	 * @return	なし.
	 */
	void read4byte(ifstream& i_cFileStream, unsigned long& i_ulHeader);

	/**
	 * @brief	CRCをチェック.
	 * @param	[in]CMpegFrame& i_cMpegFrame
	 * @param	[in]unsigned char* i_pbySide
	 * @return	true:CRC一致 / false:CRC不一致.
	 */
	bool checkCRC(CMpegFrame& i_cMpegFrame, char* i_pbySide);
	/**
	 * @brief	CRCを計算.
	 * @param	unsigned char* i_pbyCheckBuf
	 * @param	short i_shBytes
	 * @return	CRC値.
	 */
	unsigned short calcCRC(unsigned char* i_pbyCheckBuf, short i_shBytes);


    //BOOL DecodeSideInfo( CBitStream* pbs, CMpegFrame* pmf );

	/**
	 * @brief	ファイルポジションを表示. Debug用.
	 * @param	char* i_pMessage
	 * @param	ifstream& i_cFileStream
	 * @return	なし
	 */
	void printFilePos(char* i_pMessage, ifstream& i_cFileStream);

	/**
	 * @brief	デバッグ用のフラグ.
	 */
	bool m_bIsDebug;
};

#endif  //__MP3FILE_H__

