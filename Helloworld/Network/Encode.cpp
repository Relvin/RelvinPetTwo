#include "Encode.h"
namespace MiniConnProxy
{
	short nVersion = 0x100;
	char cPackFlag = 1;		//后续数据包是否有开放平台包头.0-无，1-有
	int iCpID = 191;		//cp编号 2167
	int iGameID = 191;		//cp游戏ID 2180
	short nSvrID;		//cp服务器ID
	unsigned char cOpenIDLen;				//用户ID长度
	char szOpenID[MAX_OP_ID_LENGTH];//用户ID
	unsigned char cOptionLen;							//扩展数据长度，0表示无扩展数据
	char szOptionData[MAX_OP_ID_LENGTH];		//扩展数据
	short nAppPackLen;							//应用协议包体长度
	char szAppPackData[MAX_APP_PACK_LENGTH];	//应用协议包体
	int EncodeChar( char **pstrEncode, unsigned char ucSrc )
	{
		if( pstrEncode == NULL || *pstrEncode == NULL )
		{
			return 0;
		}

		**pstrEncode = (char)ucSrc;
		(*pstrEncode)++;

		return (int)sizeof(unsigned char);
	}

	int DecodeChar( char **pstrDecode, unsigned char *pucDest )
	{
		if( pstrDecode == NULL || *pstrDecode == NULL || pucDest == NULL)
		{
			return 0;
		}

		*pucDest = **pstrDecode;
		(*pstrDecode)++;

		return (int)sizeof(unsigned char);
	}

	int EncodeShort16( char **pstrEncode, unsigned short usSrc )
	{
		if( pstrEncode == NULL || *pstrEncode == NULL )
		{
			return 0;
		}

		**pstrEncode = (char)((usSrc & 0xFF00 )>> 8);
		(*pstrEncode)++;
		**pstrEncode = (char)(usSrc & 0xFF);	
		(*pstrEncode)++;

		return 2;
	}

	int DecodeShort16( char **pstrDecode, unsigned short *pusDest )
	{
		if( pstrDecode == NULL || *pstrDecode == NULL || pusDest == NULL)
		{
			return 0;
		}

		*pusDest = (unsigned char)**pstrDecode;
		*pusDest <<= 8;
		(*pstrDecode)++;
		*pusDest += (unsigned char)**pstrDecode;
		(*pstrDecode)++;


		return 2;
	}

	int EncodeLong( char **pstrEncode, unsigned long ulSrc )
	{
		unsigned long ulTemp;

		if( pstrEncode == NULL || *pstrEncode == NULL )
		{
			return 0;
		}

		ulTemp = htonl( ulSrc );

		memcpy((void *)(*pstrEncode), (const void *)&ulTemp, sizeof(unsigned long));
		*pstrEncode += sizeof(unsigned long);

		return (int)sizeof(unsigned long);
	}


	int DecodeLong( char **pstrDecode, unsigned long *pulDest )
	{
		unsigned long ulTemp;

		if( pstrDecode == NULL || *pstrDecode == NULL || pulDest == NULL)
		{
			return 0;
		}

		memcpy((void *)&ulTemp, (const void *)(*pstrDecode), sizeof(unsigned long) );
		*pstrDecode += sizeof(unsigned long);

		*pulDest = ntohl(ulTemp);

		return (int)sizeof(unsigned long);
	}

	int EncodeInt32( char **pstrEncode, unsigned int uiSrc )
	{
		if( pstrEncode == NULL || *pstrEncode == NULL )
		{
			return 0;
		}

		**pstrEncode = (char)((uiSrc & 0xFF000000 )>> 24);
		(*pstrEncode)++;
		**pstrEncode = (char)((uiSrc & 0xFF0000 )>> 16);
		(*pstrEncode)++;
		**pstrEncode = (char)((uiSrc & 0xFF00 )>> 8);
		(*pstrEncode)++;
		**pstrEncode = (char)(uiSrc & 0xFF);	
		(*pstrEncode)++;

		return 4;
	}

	int DecodeInt32( char **pstrDecode, unsigned int *puiDest )
	{
		if( pstrDecode == NULL || *pstrDecode == NULL || puiDest == NULL)
		{
			return 0;
		}

		*puiDest = (unsigned char)**pstrDecode;
		*puiDest <<= 8;
		(*pstrDecode)++;

		*puiDest += (unsigned char)**pstrDecode;
		*puiDest <<= 8;
		(*pstrDecode)++;

		*puiDest += (unsigned char)**pstrDecode;
		*puiDest <<= 8;
		(*pstrDecode)++;

		*puiDest += (unsigned char)**pstrDecode;
		(*pstrDecode)++;

		return 4;
	}

	int EncodeString( char **pstrEncode, char *strSrc, short sMaxStrLength )
	{
		unsigned short usTempLength;

		if( pstrEncode == NULL || *pstrEncode == NULL || strSrc == NULL || sMaxStrLength <= 0 )
		{
			return 0;
		}

		usTempLength = (unsigned short)strlen(strSrc);
		if( usTempLength > sMaxStrLength )
		{
			usTempLength = sMaxStrLength;
		}

		**pstrEncode = (char)((usTempLength & 0xFF00 )>> 8);
		(*pstrEncode)++;
		**pstrEncode = (char)(usTempLength & 0xFF);	
		(*pstrEncode)++;

		strncpy((*pstrEncode), strSrc, usTempLength);

		*pstrEncode += usTempLength;

		return (usTempLength + 2);
	}


	int DecodeString( char **pstrDecode, char *strDest, short sMaxStrLength )
	{
		unsigned short usTempLength;
		unsigned short usRealLength;

		if( pstrDecode == NULL || *pstrDecode == NULL || strDest == NULL || sMaxStrLength <= 0 )
		{
			return 0;
		}

		usTempLength = (unsigned char)**pstrDecode;
		usTempLength <<= 8;
		(*pstrDecode)++;
		usTempLength += (unsigned char)**pstrDecode;
		(*pstrDecode)++;
		if( usTempLength > sMaxStrLength )
		{
			usRealLength = sMaxStrLength;
		}
		else
		{
			usRealLength = usTempLength;
		}
		strncpy(strDest, (*pstrDecode), usRealLength);
		*pstrDecode += usTempLength;

		strDest[usRealLength] = '\0';
		return (usTempLength + 2);
	}

	int EncodeMem( char **pstrEncode, char *pcSrc, short sMemSize )
	{
		if( pstrEncode == NULL || *pstrEncode == NULL || pcSrc == NULL || sMemSize <= 0 )
		{
			return 0;
		}

		memcpy((void *)(*pstrEncode), (const void *)pcSrc, sMemSize);
		*pstrEncode += sMemSize;

		return sMemSize;
	}

	int DecodeMem( char **pstrDecode, char *pcDest, short sMemSize )
	{
		if( pstrDecode == NULL || *pstrDecode == NULL || pcDest == NULL || sMemSize <= 0 )
		{
			return 0;
		}

		memcpy((void *)pcDest, (const void *)(*pstrDecode), sMemSize);
		*pstrDecode += sMemSize;

		return sMemSize;
	}


	int EncodeMemInt( char **pstrEncode, char *pcSrc, int sMemSize )
	{


		if( pstrEncode == NULL || *pstrEncode == NULL || pcSrc == NULL || sMemSize <= 0 )
		{
			return 0;
		}

		memcpy((void *)(*pstrEncode), (const void *)pcSrc, sMemSize);
		*pstrEncode += sMemSize;

		return sMemSize;
	}

	int DecodeMemInt( char **pstrDecode, char *pcDest, int sMemSize )
	{


		if( pstrDecode == NULL || *pstrDecode == NULL || pcDest == NULL || sMemSize <= 0 )
		{
			return 0;
		}

		memcpy((void *)pcDest, (const void *)(*pstrDecode), sMemSize);
		*pstrDecode += sMemSize;
		
		return sMemSize;
	}


	int EncodeInt64( char **pstrEncode, u_int64_t uiSrc )
	{
		u_int32_t uiTemp;
		u_int32_t uiPartSrc = 0;

		if( pstrEncode == NULL || *pstrEncode == NULL )
		{
			return 0;
		}

		//先编高位的四个字节
		uiPartSrc = (u_int32_t)((uiSrc>>32) & 0xFFFFFFFF);
		uiTemp = htonl( uiPartSrc );	
		memcpy((void *)(*pstrEncode), (const void *)&uiTemp, sizeof(u_int32_t));
		*pstrEncode += sizeof(u_int32_t);

		//再编低位的四个字节
		uiPartSrc = (u_int32_t)(uiSrc & 0xFFFFFFFF);
		uiTemp = htonl( uiPartSrc );
		memcpy((void *)(*pstrEncode), (const void *)&uiTemp, sizeof(u_int32_t));
		*pstrEncode += sizeof(u_int32_t);	


		return (int)sizeof(u_int32_t)*2;
	}

	int DecodeInt64( char **pstrDecode, u_int64_t *puiDest )
	{
		u_int32_t uiTemp;
		u_int64_t ui64Temp = 0;

		if( pstrDecode == NULL || *pstrDecode == NULL || puiDest == NULL)
		{
			return 0;
		}

		memcpy((void *)&uiTemp, (const void *)(*pstrDecode), sizeof(u_int32_t) );
		*pstrDecode += sizeof(u_int32_t);
		ui64Temp = ntohl(uiTemp);
		ui64Temp <<= 32;

		memcpy((void *)&uiTemp, (const void *)(*pstrDecode), sizeof(u_int32_t) );
		*pstrDecode += sizeof(u_int32_t);
		ui64Temp += ntohl(uiTemp);

		*puiDest = ui64Temp;

		return (int)sizeof(u_int32_t) * 2;
	}

	
	int gEncode(char *pcOutBuffer, short& shOutLength)
	{
		char *pcTemp;
		short shTempLength;
	
		if(!pcOutBuffer)
		{
			return -1;
		}
	
		pcTemp = pcOutBuffer;
		shOutLength = sizeof(short);
		pcTemp += shOutLength;
	
		shTempLength = EncodeShort(&pcTemp, (unsigned short)nVersion);
		shOutLength += shTempLength;
	
		shTempLength = EncodeChar(&pcTemp, (unsigned char)cPackFlag);
		shOutLength += shTempLength;
	
		shTempLength = EncodeInt(&pcTemp, (unsigned short)iCpID);
		shOutLength += shTempLength;
	
		shTempLength = EncodeInt(&pcTemp, (unsigned short)iGameID);
		shOutLength += shTempLength;
		
		shTempLength = EncodeShort(&pcTemp, (unsigned short)nSvrID);
		shOutLength += shTempLength;
	
		shTempLength = EncodeChar(&pcTemp, (unsigned char)cOpenIDLen);
		shOutLength += shTempLength;
		
		shTempLength = EncodeMem( &pcTemp, (char *)szOpenID, cOpenIDLen );
		shOutLength += shTempLength;
	
	
		shTempLength = EncodeChar(&pcTemp, (unsigned char)cOptionLen);
		shOutLength += shTempLength;
		
		shTempLength = EncodeMem( &pcTemp, (char *)szOptionData, cOptionLen );
		shOutLength += shTempLength;
	
	
		shTempLength = EncodeShort(&pcTemp, (unsigned short)nAppPackLen);
		shOutLength += shTempLength;
		
		shTempLength = EncodeMem( &pcTemp, (char *)szAppPackData, nAppPackLen );
		shOutLength += shTempLength;
	
		pcTemp = pcOutBuffer;
		shTempLength = EncodeShort(&pcTemp, (unsigned short)shOutLength);
	
		return 0;
	}
}

