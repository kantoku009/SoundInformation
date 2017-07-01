#include <cstring>
#include <string>
#include <iostream>
using namespace std;

#include "CMpegFrame.h"

/**
 * �R���X�g���N�^.
 */
CMpegFrame::CMpegFrame()
{
	// ������.
	this->init();

	m_bIsDebug = false;
}

/**
 * �f�X�g���N�^.
 */
CMpegFrame::~CMpegFrame()
{
}

/**
 * ������.
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
 * MPEG Frame Header��ݒ�.
 */
bool CMpegFrame::setHeader(unsigned long i_ulHeader)
{
	// Version��ݒ�.
	if( false == this->setVersionIndex(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [Version]:" << this->m_eVersionIndex << endl;
		return false;
	}

	// Layer��ݒ�.
	if( false == this->setLayerIndex(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [Layer]:" << this->m_eLayerIndex << endl;
		return false;
	}

	// �v���e�N�V�����r�b�g��ݒ�.
	if( false == this->setProtectionBit(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:"<< hex << i_ulHeader << " [ProtectionBit]:" << this->m_eProtectionBit << endl;
		return false;
	}

	// �r�b�g���[�g�C���f�b�N�X��ݒ�.
	if( false == this->setBitrateIndex(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [Bitrate]:" << this->m_eBitrateIndex << endl;
		return false;
	}

	// �T���v�����O���g���C���f�b�N�X��ݒ�.
	if( false == this->setSampleRateIndex(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [SampleRate]:" << this->m_eSampleRateIndex << endl;
		return false;
	}

	// �p�f�B���O�r�b�g��ݒ�.
	if( false == this->setPaddingBit(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [PaddingBit]:" << this->m_ePaddingBit << endl;
		return false;
	}

	// ���g�p�r�b�g��ݒ�.
	if( false == this->setPrivateBit(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [PrivateBit]:" << this->m_ePrivateBit << endl;
		return false;
	}

	// �`�����l�����[�h��ݒ�.
	if( false == this->setChannelMode(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [ChannelMode]:" << this->m_eChannelMode << endl;
		return false;
	}

	// �g�����[�h��ݒ�.
	if( false == this->setMoedExtention(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [ModeExtention]:" << this->m_eModeExtention << endl;
		return false;
	}

	// ���쌠����ݒ�.
	if( false == this->setCopyright(i_ulHeader) )
	{
		if(m_bIsDebug) cerr << "!!!!! failed [FrameHeader]:" << hex << i_ulHeader << " [Copyright]:" << this->m_eCopyright << endl;
		return false;
	}

	// �I���W�i�����ۂ���ݒ�.
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
 * �t���[���T�C�Y���擾.
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
 * ���C���f�[�^�T�C�Y���擾.
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
 * �T���v�����O���g�����擾.
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
 * �r�b�g���[�g���擾.
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
 * MPEG Frame Header���ۂ����m�F.
 */
bool CMpegFrame::isHeader(unsigned long i_ulHeader) const
{
	const unsigned long DEF_MASK_SYNC_WORD = 0xFFE00000;
	if( (i_ulHeader&DEF_MASK_SYNC_WORD) == DEF_MASK_SYNC_WORD )
	{	// MPEG Frame Header�̓����w�b�_�Ɉ�v����.
		return true;
	}

	// MPEG Frame Header�̓����w�b�_�Ɉ�v���Ȃ�����.
	return false;
}

/**
 * MPEG Frame Header�̐ݒ�i�������j.
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
	
	// �͈̓`�F�b�N.
	if( (i_ulTemp<=i_ulMin) || (i_ulMax<=i_ulTemp) )
	{
		if(m_bIsDebug) cerr << "check range failed." << "Min=" << i_ulMin << " Max=" << i_ulMax << " Value=" << i_ulTemp << endl;
		return false;
	}

	*i_pulValue = i_ulTemp;
	return true;
}

/**
 * MPEG�o�[�W������ݒ�.
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
	{	// ����`��Version.
		a_bIsSuccess = false;
	}

	return a_bIsSuccess;
}

/**
 * Layer��ݒ�.
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
	{	// ����`��Layer.
		a_bIsSuccess = false;
	}

	return a_bIsSuccess;
}

/**
 * �v���e�N�V�����r�b�g��ݒ�.
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
 * �r�b�g���[�g�C���f�b�N�X��ݒ�.
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
	{	// �s���l�̃r�b�g���[�g.
		a_bIsSuccess = false;
	}

	return a_bIsSuccess;
}

/**
 * �T���v�����O���g���C���f�b�N�X��ݒ�.
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
	{	//����`�̃T���v�����O���g��.
		a_bIsSuccess = false;
	}

	return a_bIsSuccess;
}

/**
 * �p�f�B���O�r�b�g��ݒ�.
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
 * @brief	�\��ς݃r�b�g��ݒ�.
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
 * @brief	�`�����l�����[�h��ݒ�.
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
 * �g�����[�h��ݒ�.
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
 * ���쌠����ݒ�.
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
 * @brief	�I���W�i�����ۂ���ݒ�.
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
 * @brief	�G���t�@�V�X��ݒ�.
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
	{	// ����`�̃G���t�@�V�X.
		a_bIsSuccess = false;
	}

	return a_bIsSuccess;
}

/**
 * MPEG Frame Header�����o��.
 * debug�p�ɏ����o��.
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

	// ���g�p�r�b�g.
	string a_strPrivateBit[E_PRIVATE_BIT_MAX] = 
	{
		"false",
		"true",
	};
	cout << "  PrivateBit:" << a_strPrivateBit[m_ePrivateBit] << endl;

	// �`�����l�����[�h.
	string a_strChannelMode[E_CHANNEL_MODE_MAX] = 
	{
		"Stereo",
		"JointStereo",
		"DualStereo",
		"Monoral",
	};
	cout << "  Channel Mode: " << a_strChannelMode[m_eChannelMode] << endl;

	// �g�����[�h.
	string a_strModeExtention[E_MODE_EXTENTION_MAX] = 
	{
		"[I Stereo:false] [M/S Stereo:false]",
		"[I Stereo:true ] [M/S Stereo:false]",
		"[I Stereo:false] [M/S Stereo:true ]",
		"[I Stereo:true ] [M/S Stereo:true ]",
	};
	cout << "  Extention Mode: " << a_strModeExtention[m_eModeExtention] << endl;

	// ���쌠���.
	string a_strCopyright[E_COPYRIGHT_MAX] = 
	{
		"false",
		"true",
	};
	cout << "  Copyright: " << a_strCopyright[m_eCopyright] << endl;

	// �I���W�i��.
	string a_strOriginal[E_ORIGINAL_MAX] = 
	{
		"copy",
		"original",
	};
	cout << "  copy/original-> " << a_strOriginal[m_eOriginal] << endl;

	// �G���t�@�V�X.
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
 * �T�C�h����ݒ�.
 */
bool CMpegFrame::setSideInfo(char* i_bySide)
{
	// TBA. ������.
	return true;
}

/**
 * ���C���f�[�^��ݒ�.
 */
bool CMpegFrame::setMainData(char* i_pMainData, long i_lSize)
{
	memcpy(m_pbyMainData, i_pMainData, i_lSize);
	return true;
}

