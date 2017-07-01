#include <cstring>
#include <string>
#include <iostream>
using namespace std;

#include "CMpegFrame.h"

/**
 * コンストラクタ.
 */
CMpegFrame::CMpegFrame()
{
	// 初期化.
	this->init();

	m_bIsDebug = false;
}

/**
 * デストラクタ.
 */
CMpegFrame::~CMpegFrame()
{
}

/**
 * 初期化.
 */
void CMpegFrame::init()
{
	m_ulHeader = 0;
	m_eVersionIndex = E_MPEG_VERSION_MIN;
	m_eLayerIndex = E_LAYER_MIN;
	m_eProtectionBit = E_PROTECTION_BIT_MIN;
	m_eBitrateIndex = E_BITRATE_MIN;
	m_eSampleRateIndex = E_SAMPLERATE_MIN;
	m_ePaddingBit = E_PADDING_BIT_MIN;
	m_ePrivateBit = E_PRIVATE_BIT_MIN;
	m_eChannelMode = E_CHANNEL_MODE_MIN;
	m_eModeExtention = E_MODE_EXTENTION_MIN;
	m_eCopyright = E_COPYRIGHT_MIN;
	m_eOriginal = E_ORIGINAL_MIN;
	m_eEmphasis = E_EMPHASIS_MIN;

	m_usCRCCheck = 0;
	m_usMainDataBegin = 0;

	memset( m_pusScfSi, 0x00, sizeof(m_pusScfSi) );
	memset( m_pGranuleInfo, 0x00, sizeof(m_pGranuleInfo) );

	memset( m_pbyMainData, 0x00, sizeof(m_pbyMainData) );
	m_lMainDataSize = 0;
}

/**
 * MPEG Frame Headerを設定.
 */
bool CMpegFrame::setHeader(unsigned long i_ulHeader)
{
	// Versionを設定.
	if( false == this->setVersionIndex(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [Version]:" << this->m_eVersionIndex << endl;
		return false;
	}

	// Layerを設定.
	if( false == this->setLayerIndex(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [Layer]:" << this->m_eLayerIndex << endl;
		return false;
	}

	// プロテクションビットを設定.
	if( false == this->setProtectionBit(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:"<< hex << i_ulHeader << " [ProtectionBit]:" << this->m_eProtectionBit << endl;
		return false;
	}

	// ビットレートインデックスを設定.
	if( false == this->setBitrateIndex(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [Bitrate]:" << this->m_eBitrateIndex << endl;
		return false;
	}

	// サンプリング周波数インデックスを設定.
	if( false == this->setSampleRateIndex(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [SampleRate]:" << this->m_eSampleRateIndex << endl;
		return false;
	}

	// パディングビットを設定.
	if( false == this->setPaddingBit(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [PaddingBit]:" << this->m_ePaddingBit << endl;
		return false;
	}

	// 未使用ビットを設定.
	if( false == this->setPrivateBit(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [PrivateBit]:" << this->m_ePrivateBit << endl;
		return false;
	}

	// チャンネルモードを設定.
	if( false == this->setChannelMode(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [ChannelMode]:" << this->m_eChannelMode << endl;
		return false;
	}

	// 拡張モードを設定.
	if( false == this->setMoedExtention(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [ModeExtention]:" << this->m_eModeExtention << endl;
		return false;
	}

	// 著作権情報を設定.
	if( false == this->setCopyright(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [Copyright]:" << this->m_eCopyright << endl;
		return false;
	}

	// オリジナルか否かを設定.
	if( false == this->setOriginal(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [Original]:" << this->m_eOriginal << endl;
		return false;
	}

	if( false == this->setEmphasis(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [Emphasis]:" << this->m_eEmphasis << endl;
		return false;
	}

	this->m_ulHeader = i_ulHeader;
	if(m_bIsDebug) cerr << "MPEG [FrameHeader]:" << hex << i_ulHeader << endl;
	return true;
}

/**
 * フレームサイズを取得.
 */
long CMpegFrame::getFrameSize() const
{
	long a_lSlots;
	short a_shPadding;
    
	switch(this->m_eLayerIndex){
	//Layer3 and Layer2
	case E_LAYER_3:
	case E_LAYER_2:
		a_lSlots = (long)(144.0 * (double)getBitrate() / (double)getSampleRate() );
		if( E_PADDING_BIT_FALSE != m_ePaddingBit ) a_lSlots++;
		break;

	//Layer1
	case E_LAYER_1:
		a_shPadding = (E_PADDING_BIT_TRUE==m_ePaddingBit)? 1:0;
		a_lSlots = (long)(12.0 * (double)getBitrate() / (double)getSampleRate() + a_shPadding) * 4;
		break;
	
	default:
		a_lSlots = 0;
	}
    
	return a_lSlots;
}

/**
 * メインデータサイズを取得.
 */
long CMpegFrame::getMainDataSize() const
{
	long a_lSlots = this->getFrameSize();
    
	//Header Bytes
	a_lSlots -= 4;
    
	//CRC Bytes
	if( E_PROTECTION_BIT_TRUE == this->m_eProtectionBit )
	{
		a_lSlots -= 2; 
	}
    
	//SideInfo Bytes
	if( 1 == this->getChannels() )
	{
		a_lSlots -= 17;
	}
	else
	{
		a_lSlots -=32;
	}
    
	return a_lSlots;
}

/**
 * サンプリング周波数を取得.
 */
long CMpegFrame::getSampleRate() const
{
	const long a_rglSampleRate[E_MPEG_VERSION_MAX][E_SAMPLERATE_MAX] =
	{ 
		{ 11025, 12000,  8000 },	//MPEG2.5.
		{     0,     0,     0 },	//Reserved.
		{ 22050, 24000, 16000 },	//MPEG2.
		{ 44100, 48000, 32000 },	//MPEG1.
	};

	return a_rglSampleRate[m_eVersionIndex][m_eSampleRateIndex];
}

/**
 * ビットレートを取得.
 */
long CMpegFrame::getBitrate() const
{
	const short a_rgshBitrate[E_MPEG_VERSION_MAX][E_LAYER_MAX][E_BITRATE_MAX] = 
	{
		{	//MPEG2.5.
			{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },	//Layer Reserved.
			{   0,   8,  16,  24,  32,  40,  48,  56,  64,  80,  96, 112, 128, 144, 160 },	//Layer3.
			{   0,   8,  16,  24,  32,  40,  48,  56,  64,  80,  96, 112, 128, 144, 160 },	//Layer2.
			{   0,  32,  48,  56,  64,  80,  96, 112, 128, 144, 160, 176, 192, 224, 256 },	//Layer1
		},
		{	//RESERVED.
			{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },	//Layer Reserved.
			{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },	//Layer3.
			{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },	//Layer2.
			{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },	//Layer1.
		},
		{	//MPEG2.
			{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },	//Layer Reserved.
			{   0,   8,  16,  24,  32,  40,  48,  56,  64,  80,  96, 112, 128, 144, 160 },	//Layer3.
			{   0,   8,  16,  24,  32,  40,  48,  56,  64,  80,  96, 112, 128, 144, 160 },	//Layer2.
			{   0,  32,  48,  56,  64,  80,  96, 112, 128, 144, 160, 176, 192, 224, 256 },	//Layer1
		},
 		{	//MPEG1.
			{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },	//Layer Reserved.
			{   0,  32,  40,  48,  56,  64,  80,  96, 112, 128, 160, 192, 224, 256, 320 },	//Layer3.
			{   0,  32,  48,  56,  64,  80,  96, 112, 128, 160, 192, 224, 256, 320, 384 },	//Layer2.
			{   0,  32,  64,  96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448 },	//Layer1.
		},
	};
	
	return a_rgshBitrate[m_eVersionIndex][m_eLayerIndex][m_eBitrateIndex]*1000;
}

/**
 * MPEG Frame Headerか否かを確認.
 */
bool CMpegFrame::isHeader(unsigned long i_ulHeader) const
{
	const unsigned long DEF_MASK_SYNC_WORD = 0xFFE00000;
	if( (i_ulHeader&DEF_MASK_SYNC_WORD) == DEF_MASK_SYNC_WORD )
	{	// MPEG Frame Headerの同期ヘッダに一致した.
		return true;
	}

	// MPEG Frame Headerの同期ヘッダに一致しなかった.
	return false;
}

/**
 * MPEG Frame Headerの設定（実処理）.
 */
bool CMpegFrame::setHeaderValueImp(
		const unsigned long i_ulHeader,
		const unsigned long i_ulMask,
		const unsigned long i_ulShift,
		const long i_ulMin,
		const long i_ulMax,
		long* i_pulValue
		)
{
	long i_ulTemp = (i_ulHeader & i_ulMask) >> i_ulShift;
	
	// 範囲チェック.
	if( (i_ulTemp<=i_ulMin) || (i_ulMax<=i_ulTemp) )
	{
		if(m_bIsDebug) cerr << "check range failed." << "Min=" << i_ulMin << " Max=" << i_ulMax << " Value=" << i_ulTemp << endl;
		return false;
	}

	*i_pulValue = i_ulTemp;
	return true;
}

/**
 * MPEGバージョンを設定.
 */
bool CMpegFrame::setVersionIndex(unsigned long i_ulHeader)
{
	const unsigned long DEF_MASK_VERSION_INDEX =  0x00180000;
	const unsigned long DEF_SHIFT_VERSION_INDEX = 19;
	bool a_bIsSuccess = true;

	a_bIsSuccess = this->setHeaderValueImp(
									i_ulHeader,
									DEF_MASK_VERSION_INDEX,
									DEF_SHIFT_VERSION_INDEX,
									E_MPEG_VERSION_MIN,
									E_MPEG_VERSION_MAX,
									(long*)&(this->m_eVersionIndex)
									);

	if(E_MPEG_RESERVED == this->m_eVersionIndex)
	{	// 未定義のVersion.
		a_bIsSuccess = false;
	}

	return a_bIsSuccess;
}

/**
 * Layerを設定.
 */
bool CMpegFrame::setLayerIndex(unsigned long i_ulHeader)
{
	const unsigned long DEF_MASK_LAYER_INDEX = 0x00060000;
	const unsigned long DEF_SHIFT_LAYER_INDEX = 17;
	bool a_bIsSuccess = true;

	a_bIsSuccess = this->setHeaderValueImp(
									i_ulHeader,
									DEF_MASK_LAYER_INDEX,
									DEF_SHIFT_LAYER_INDEX,
									E_LAYER_MIN,
									E_LAYER_MAX,
									(long*)&(this->m_eLayerIndex)
									);

	if(E_LAYER_RESERVED == this->m_eLayerIndex)
	{	// 未定義のLayer.
		a_bIsSuccess = false;
	}

	return a_bIsSuccess;
}

/**
 * プロテクションビットを設定.
 */
bool CMpegFrame::setProtectionBit(unsigned long i_ulHeader)
{
	const unsigned long DEF_MASK_PROTECTIONBIT = 0x00010000;
	const unsigned long DEF_SHIFT_PROTECTIONBIT = 16;
	bool a_bIsSuccess = true;

	a_bIsSuccess = this->setHeaderValueImp(
									i_ulHeader,
									DEF_MASK_PROTECTIONBIT,
									DEF_SHIFT_PROTECTIONBIT,
									E_PROTECTION_BIT_MIN,
									E_PROTECTION_BIT_MAX,
									(long*)&(this->m_eProtectionBit)
									);

	return a_bIsSuccess;
}

/**
 * ビットレートインデックスを設定.
 */
bool CMpegFrame::setBitrateIndex(unsigned long i_ulHeader)
{
	const unsigned long DEF_MASK_BITRATE_INDEX = 0x0000F000;
	const unsigned long DEF_SHIFT_BITRATE_INDEX = 12;
	bool a_bIsSuccess = true;

	a_bIsSuccess = this->setHeaderValueImp(
									i_ulHeader,
									DEF_MASK_BITRATE_INDEX,
									DEF_SHIFT_BITRATE_INDEX,
									E_BITRATE_MIN,
									E_BITRATE_MAX,
									(long*)&(this->m_eBitrateIndex)
									);

	if(E_BITRATE_INVALID == this->m_eBitrateIndex)
	{	// 不正値のビットレート.
		a_bIsSuccess = false;
	}

	return a_bIsSuccess;
}

/**
 * サンプリング周波数インデックスを設定.
 */
bool CMpegFrame::setSampleRateIndex(unsigned long i_ulHeader)
{
	const unsigned long DEF_MASK_SAMPLERATE_INDEX = 0x00000C00;
	const unsigned long DEF_SHIFT_SAMPLERATE_INDEX = 10;
	bool a_bIsSuccess = true;

	a_bIsSuccess = this->setHeaderValueImp(
									i_ulHeader,
									DEF_MASK_SAMPLERATE_INDEX,
									DEF_SHIFT_SAMPLERATE_INDEX,
									E_SAMPLERATE_MIN,
									E_SAMPLERATE_MAX,
									(long*)&(this->m_eSampleRateIndex)
									);

	if(E_SAMPLERATE_RESERVED == this->m_eSampleRateIndex)
	{	//未定義のサンプリング周波数.
		a_bIsSuccess = false;
	}

	return a_bIsSuccess;
}

/**
 * パディングビットを設定.
 */
bool CMpegFrame::setPaddingBit(unsigned long i_ulHeader)
{
	const unsigned long DEF_MASK_PADDINGBIT = 0x00000200;
	const unsigned long DEF_SHIFT_PADDINGBIT = 9;
	bool a_bIsSuccess = true;

	a_bIsSuccess = this->setHeaderValueImp(
									i_ulHeader,
									DEF_MASK_PADDINGBIT,
									DEF_SHIFT_PADDINGBIT,
									E_PADDING_BIT_MIN,
									E_PADDING_BIT_MAX,
									(long*)&(this->m_ePaddingBit)
									);

	return a_bIsSuccess;
}

/**
 * @brief	予約済みビットを設定.
 */
bool CMpegFrame::setPrivateBit(unsigned long i_ulHeader)
{
	const unsigned long DEF_MASK_PRIVATEBIT = 0x00000100;
	const unsigned long DEF_SHIFT_PRIVATEBIT = 8;
	bool a_bIsSuccess = true;

	a_bIsSuccess = this->setHeaderValueImp(
									i_ulHeader,
									DEF_MASK_PRIVATEBIT,
									DEF_SHIFT_PRIVATEBIT,
									E_PRIVATE_BIT_MIN,
									E_PRIVATE_BIT_MAX,
									(long*)&(this->m_ePrivateBit)
									);

	return a_bIsSuccess;
}


/**
 * @brief	チャンネルモードを設定.
 */
bool CMpegFrame::setChannelMode(unsigned long i_ulHeader)
{
	const unsigned long DEF_MASK_MODE_INDEX = 0x000000C0;
	const unsigned long DEF_SHIFT_MODE_INDEX = 6;
	bool a_bIsSuccess = true;

	a_bIsSuccess = this->setHeaderValueImp(
									i_ulHeader,
									DEF_MASK_MODE_INDEX,
									DEF_SHIFT_MODE_INDEX,
									E_CHANNEL_MODE_MIN,
									E_CHANNEL_MODE_MAX,
									(long*)&(this->m_eChannelMode)
									);

	return a_bIsSuccess;
}

/**
 * 拡張モードを設定.
 */
bool CMpegFrame::setMoedExtention(unsigned long i_ulHeader)
{
	const unsigned long DEF_MASK_MODE_EXTENTION_INDEX = 0x00000030;
	const unsigned long DEF_SHIFT_MODE_EXTENTION_INDEX = 4;
	bool a_bIsSuccess = true;

	a_bIsSuccess = this->setHeaderValueImp(
									i_ulHeader,
									DEF_MASK_MODE_EXTENTION_INDEX,
									DEF_SHIFT_MODE_EXTENTION_INDEX,
									E_MODE_EXTENTION_MIN,
									E_MODE_EXTENTION_MAX,
									(long*)&(this->m_eModeExtention)
									);

	return a_bIsSuccess;
}

/**
 * 著作権情報を設定.
 */
bool CMpegFrame::setCopyright(unsigned long i_ulHeader)
{
	const unsigned long DEF_MASK_COPYRIGHT = 0x00000008;
	const unsigned long DEF_SHIFT_COPYRIGHT = 3;
	bool a_bIsSuccess = true;

	a_bIsSuccess = this->setHeaderValueImp(
									i_ulHeader,
									DEF_MASK_COPYRIGHT,
									DEF_SHIFT_COPYRIGHT,
									E_COPYRIGHT_MIN,
									E_COPYRIGHT_MAX,
									(long*)&(this->m_eCopyright)
									);

	return a_bIsSuccess;
}

/**
 * @brief	オリジナルか否かを設定.
 */
bool CMpegFrame::setOriginal(unsigned long i_ulHeader)
{
	const unsigned long DEF_MASK_ORIGINAL = 0x00000004;
	const unsigned long DEF_SHIFT_ORIGINAL = 2;
	bool a_bIsSuccess = true;

	a_bIsSuccess = this->setHeaderValueImp(
									i_ulHeader,
									DEF_MASK_ORIGINAL,
									DEF_SHIFT_ORIGINAL,
									E_ORIGINAL_MIN,
									E_ORIGINAL_MAX,
									(long*)&(this->m_eOriginal)
									);

	return a_bIsSuccess;
}

/**
 * @brief	エンファシスを設定.
 */
bool CMpegFrame::setEmphasis(unsigned long i_ulHeader)
{
	const unsigned long DEF_MASK_EMPHASIS = 0x00000003;
	const unsigned long DEF_SHIFT_EMPHASIS = 0;
	bool a_bIsSuccess = true;

	a_bIsSuccess = this->setHeaderValueImp(
									i_ulHeader,
									DEF_MASK_EMPHASIS,
									DEF_SHIFT_EMPHASIS,
									E_EMPHASIS_MIN,
									E_EMPHASIS_MAX,
									(long*)&(this->m_eEmphasis)
									);

	if(E_EMPHASIS_RESERVED == this->m_eEmphasis)
	{	// 未定義のエンファシス.
		a_bIsSuccess = false;
	}

	return a_bIsSuccess;
}

/**
 * MPEG Frame Header情報を出力.
 * debug用に情報を出力.
 */
void CMpegFrame::printHeaderInfo()
{
	cout << "MPEG Frame Header: \t" << hex << this->m_ulHeader << endl;

	// MPEG Version
	string a_strVersin[E_MPEG_VERSION_MAX] = 
	{
		"2.5",
		"undef",
		"2",
		"1",
	};
	cout << "  MPEG Version " << a_strVersin[m_eVersionIndex] << endl;

	// Layer
	string a_strLayer[E_LAYER_MAX] =
	{
		"reserved",
		"III",
		"II",
		"I",
	};
	cout << "  Layer " << a_strLayer[m_eLayerIndex] << endl;

	// Protection Bit.
	string a_strProtectionBit[E_PROTECTION_BIT_MAX] = 
	{
		"true",
		"false",
	};
	cout << "  Protection(CRC): " << a_strProtectionBit[m_eProtectionBit] << endl;

	// Bitrate.
	cout << "  Bitrate (" << dec << m_eBitrateIndex << "):" << getBitrate() << "[bps]" << endl;
	
	// SampleRate.
	cout << "  SampleRate (" << dec << m_eSampleRateIndex << "):" << getSampleRate() << "[Hz]" << endl;

	// PaddingBit.
	string a_strPaddingBit[E_PADDING_BIT_MAX] = 
	{
		"false",
		"true",
	};
	cout << "  PaddingBit:" << a_strPaddingBit[m_ePaddingBit] << endl;

	// 未使用ビット.
	string a_strPrivateBit[E_PRIVATE_BIT_MAX] = 
	{
		"false",
		"true",
	};
	cout << "  PrivateBit:" << a_strPrivateBit[m_ePrivateBit] << endl;

	// チャンネルモード.
	string a_strChannelMode[E_CHANNEL_MODE_MAX] = 
	{
		"Stereo",
		"JointStereo",
		"DualStereo",
		"Monoral",
	};
	cout << "  Channel Mode: " << a_strChannelMode[m_eChannelMode] << endl;

	// 拡張モード.
	string a_strModeExtention[E_MODE_EXTENTION_MAX] = 
	{
		"[I Stereo:false] [M/S Stereo:false]",
		"[I Stereo:true ] [M/S Stereo:false]",
		"[I Stereo:false] [M/S Stereo:true ]",
		"[I Stereo:true ] [M/S Stereo:true ]",
	};
	cout << "  Extention Mode: " << a_strModeExtention[m_eModeExtention] << endl;

	// 著作権情報.
	string a_strCopyright[E_COPYRIGHT_MAX] = 
	{
		"false",
		"true",
	};
	cout << "  Copyright: " << a_strCopyright[m_eCopyright] << endl;

	// オリジナル.
	string a_strOriginal[E_ORIGINAL_MAX] = 
	{
		"copy",
		"original",
	};
	cout << "  copy/original-> " << a_strOriginal[m_eOriginal] << endl;

	// エンファシス.
	string a_strEmphasis[E_EMPHASIS_MAX] = 
	{
		"ON",
		"50/15ms",
		"reserved",
		"CCIT J.17",
	};
	cout << "  Emphasis: " << a_strEmphasis[m_eEmphasis] << endl;
}

/**
 * サイド情報を設定.
 */
bool CMpegFrame::setSideInfo(char* i_bySide)
{
	// TBA. 未実装.
	return true;
}

/**
 * メインデータを設定.
 */
bool CMpegFrame::setMainData(char* i_pMainData, long i_lSize)
{
	memcpy(m_pbyMainData, i_pMainData, i_lSize);
	return true;
}

