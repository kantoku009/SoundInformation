#include <iostream>		//debug用.
#include <cstring>		//memcpy.
using namespace std;

#include "CMpegFrame.h"
#include "../CMp3File.h"

bool CMp3File::read(const string i_strFileName)
{
	ifstream a_cFileStream(i_strFileName.c_str(), ios::in|ios::binary);
	CMpegFrame a_cMpegFrame;

	if(!a_cFileStream)
	{	// ファイルが開けなかった.
		cout << "Can't open file." << endl;
		return false;
	}

	// MPEG Frameの検索が成功する間, ループする.
	while( true == this->seekMpegFrame(a_cFileStream, a_cMpegFrame) )
	{
		// BWaveFormにサンプル値を設定.

		// debug用にMPEG Frame Headerを出力.
		if(m_bIsDebug) a_cMpegFrame.printHeaderInfo();

		// MPEG Frame Headerクラスを初期化.
		a_cMpegFrame.init();
	}

	return true;
}

/**
 * 4バイト分ファイルから読み込む.
 */
void CMp3File::read4byte(ifstream& i_cFileStream, unsigned long& i_ulHeader)
{
	char a_byBuffer = 0;			// ファイルからデータを読み込むためのバッファ.

	for(short a_shCnt=3; a_shCnt>=0; a_shCnt--)
	{
		i_cFileStream.read( &a_byBuffer, sizeof(a_byBuffer) );
		i_ulHeader += (unsigned char)a_byBuffer<<(a_shCnt*8);
	}
}

/**
 * MPEG Frameを探す.
 */
bool CMp3File::seekMpegFrame(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame)
{
	bool a_bIsSuccess = true;
	unsigned long a_ulHeader = 0;	// Mpeg Frameヘッダ.
	char a_byBuffer = 0;			// ファイルからデータを読み込むためのバッファ.

	// 最初にフレームヘッダ(4byte)分ファイルから読み込み.
	this->read4byte(i_cFileStream, a_ulHeader);

	//////////////////////////////////////////////////////////////////
	// フレームヘッダーの検索. 
	// 4096[byte]中に同期ヘッダが見つからなければ, MP3ファイルではない.
	//////////////////////////////////////////////////////////////////
	for(short a_shCounter=0; a_shCounter<4096; a_shCounter++)
	{
		a_bIsSuccess = i_cMpegFrame.isHeader(a_ulHeader);
		if(false == a_bIsSuccess)
		{
			// Frameヘッダではなかった為, 1[byte]分ずらす.
			i_cFileStream.read( &a_byBuffer, sizeof(a_byBuffer) );
			a_ulHeader = (a_ulHeader<<8) + (unsigned char)a_byBuffer;
			continue;
		}

		// MPEG Frame Headerを設定.
		a_bIsSuccess = i_cMpegFrame.setHeader(a_ulHeader);
		if(false == a_bIsSuccess)
		{
			// 不正なFrameヘッダだった為, 3[byte]分戻し, 4[byte]読み直す.
			i_cFileStream.seekg(-3, ios_base::cur);
			a_ulHeader = 0x00;
			this->read4byte(i_cFileStream, a_ulHeader);
			continue;
		}

		//////////////////////////////////////////////////////////////////
		// ここまで来たら, MPEG Frameヘッダ 検索成功.
		//////////////////////////////////////////////////////////////////
		// デバッグ用にFilePosを出力.
		if(m_bIsDebug) this->printFilePos((char*)"FilePosStart\t", i_cFileStream);

		// MPEG Frame 本体を読み込む.
		a_bIsSuccess = this->seekMpegFrameAfter(i_cFileStream, i_cMpegFrame);
		if(true != a_bIsSuccess)
		{
			return false;
		}
		// デバッグ用にFilePosを出力.
		if(m_bIsDebug) this->printFilePos((char*)"FilePosEnd\t", i_cFileStream);
		// MPEG Frame 読み込み成功.
		return true;
	}
	// ここにたどり着いたら, MP3ファイルではないと判断する.
	return false;
}

/**
 * MPEG Frame 本体を読み込む.
 */
bool CMp3File::seekMpegFrameAfter(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame)
{
	bool a_bIsSuccess = true;

	// CRCワードの読み込み.
	a_bIsSuccess = this->readCRC(i_cFileStream, i_cMpegFrame);
	if(true != a_bIsSuccess)
	{
		return false;
	}

	// サイド情報の読み込み.
	char a_pbySide[64];
	a_bIsSuccess = this->readSideInfo(i_cFileStream, i_cMpegFrame, a_pbySide);
	if(true != a_bIsSuccess)
	{
		return false;
	}

	// CRCチェック.
	bool a_bIsMatchCRC = true;
	a_bIsMatchCRC = this->checkCRC(i_cMpegFrame, a_pbySide);
	if(!a_bIsMatchCRC)
	{
		if(m_bIsDebug) cerr << "CMp3FileError:CRC did not match." << endl;
		return false;
	}

	// サポートフォーマットのチェック.

	// メインデータの読み込み.
	a_bIsSuccess = this->readMainData(i_cFileStream, i_cMpegFrame);
	if(true != a_bIsSuccess)
	{
		return false;
	}

	return true;
}

/**
 * CRCワードを読み込み.
 */
bool CMp3File::readCRC(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame)
{
	// プロテクションビットが立っていなかったら, 何もしない.
	if(E_PROTECTION_BIT_TRUE != i_cMpegFrame.getProtectionBit())
	{
		i_cMpegFrame.setCRCCheck(0);
		return true;
	}

	// CRCワードを読み込み.
	char a_byBuffer2[2] = {0, 0};
	unsigned short a_usCRCCheck = 0;
	i_cFileStream.read(a_byBuffer2, sizeof(a_byBuffer2));

	// CRCワードをフレーム情報に設定.
	a_usCRCCheck = ((unsigned char)a_byBuffer2[0]<<8) + (unsigned char)a_byBuffer2[1];
	i_cMpegFrame.setCRCCheck(a_usCRCCheck);

	return true;
}

/**
 * サイド情報の読み込み.
 */
bool CMp3File::readSideInfo(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame, char* i_pbySide)
{
	unsigned short a_usSideSize = i_cMpegFrame.getSideSize();

	// サイド情報を読み込み.
	i_cFileStream.read(i_pbySide, a_usSideSize);

	// サイド情報を設定.
	bool a_bIsSuccess = i_cMpegFrame.setSideInfo(i_pbySide);
	if(true != a_bIsSuccess)
	{
		return false;
	}

	return true;
}

/**
 * メインデータの読み込み.
 */
bool CMp3File::readMainData(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame)
{
	char a_pFrameData[2048];

	// Mainデータサイズを取得.
	long a_lSize = i_cMpegFrame.getMainDataSize();
	if(0 > a_lSize)
	{
		if(m_bIsDebug) cerr << "CMp3FileError:do not read Maindata:" << a_lSize << endl;
		return false;
	}

	// Mainデータを読み込み.
	i_cFileStream.read(a_pFrameData, a_lSize);

	// MainデータをFrameに設定.
	i_cMpegFrame.setMainData(a_pFrameData, a_lSize);

	return true;
}

/**
 * CRCをチェック.
 */
bool CMp3File::checkCRC(CMpegFrame& i_cMpegFrame, char* i_pbySide)
{
	// プロテクションビットが立っていなかったら, 何もしない.
	if(E_PROTECTION_BIT_TRUE != i_cMpegFrame.getProtectionBit())
	{
		return true;
	}

	unsigned char a_pbyCheckBuf[34];	// Side情報の最大サイズ+2

	// Frame Headerの下位2[byte]をバッファに詰める.
	unsigned short a_ushHeaderLow = static_cast<unsigned short>((i_cMpegFrame.getHeader() & 0x0000FFFF));
	memcpy(a_pbyCheckBuf, &a_ushHeaderLow, sizeof(unsigned short));
	// リトルエンディアンだったら, 上位バイトと下位バイトを入れ替える.
	unsigned char a_byTemp = a_pbyCheckBuf[0];
	a_pbyCheckBuf[0] = a_pbyCheckBuf[1];
	a_pbyCheckBuf[1] = a_byTemp;

	// Side情報をバッファに詰める.
	unsigned short a_usSideSize = i_cMpegFrame.getSideSize();
	memcpy(a_pbyCheckBuf+2, i_pbySide, a_usSideSize);

	// CRCを計算.
	unsigned short a_usCRCValue = this->calcCRC(a_pbyCheckBuf, a_usSideSize+2);
	if( a_usCRCValue != i_cMpegFrame.getCRCCheck() )
	{
		// CRCエラー.
		if(m_bIsDebug)
		{
			printf("CRC error: %02x \t %02x\n", a_usCRCValue, i_cMpegFrame.getCRCCheck());
			for(int cnt=0; cnt<a_usSideSize+2; cnt++)
			{
				printf("%02x ", a_pbyCheckBuf[cnt]);
			}
			printf("\n");
		}
		return false;
	}

	return true;
}

/**
 * CRCを計算.
 */
unsigned short CMp3File::calcCRC( unsigned char* i_pbyCheckBuf, short i_shBytes )
{
	const unsigned long CRC16_POLYNOMIAL = 0x18005;
	unsigned long a_lCRCValue = 0xffff;

	for( short a_shLoop=0; a_shLoop<i_shBytes; a_shLoop++ )
	{
		unsigned short a_usByte = static_cast<unsigned short>(i_pbyCheckBuf[a_shLoop]);
		for( short a_shCnt=0; a_shCnt<8; a_shCnt++ )
		{
			a_lCRCValue <<= 1;
			a_usByte <<= 1;
			short a_shCRCCarry = (a_lCRCValue & 0x10000)!=0;
			short a_shDataCarry = (a_usByte & 0x100)!=0;
			if( (!a_shCRCCarry && a_shDataCarry) || (a_shCRCCarry && !a_shDataCarry))
			{
				a_lCRCValue ^= CRC16_POLYNOMIAL;
			}
			a_lCRCValue &= 0xffff;
		}
	}
	return static_cast<unsigned short>(a_lCRCValue);
}

/**
 * ファイルポジションを表示. Debug用.
 */
void CMp3File::printFilePos(char* i_pMessage, ifstream& i_cFileStream)
{
	ifstream::pos_type a_nPos = i_cFileStream.tellg();
	cout << i_pMessage << a_nPos << endl;
}

