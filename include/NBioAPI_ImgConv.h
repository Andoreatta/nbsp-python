#ifndef _NITGEN_NBioAPI_IMGCONV_H
#define _NITGEN_NBioAPI_IMGCONV_H

#include "NBioAPI_Basic.h"
#include "NBioAPI_Type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _NBioAPI_LOAD_LIBRARY

	NBioAPI_RETURN NBioAPI NBioAPI_ImgConvRawToBmpBuf(	
												NBioAPI_UINT8* lpImageBuffer, 
												NBioAPI_UINT32 nWidth, 
												NBioAPI_UINT32 nHeight,
												NBioAPI_UINT8* lpBMPBuffer,
												int * BMPBufLen);

	NBioAPI_RETURN NBioAPI NBioAPI_ImgConvRawToBmpBufEx(
												NBioAPI_UINT8* lpImageBuffer, 
												NBioAPI_UINT32 nWidth, 
												NBioAPI_UINT32 nHeight,
												NBioAPI_UINT32 nDPI,
												NBioAPI_UINT8* lpBMPBuffer,
												int * BMPBufLen);

	NBioAPI_RETURN NBioAPI NBioAPI_ImgConvBmpToRawBuf(
												NBioAPI_UINT8* lpImageBuffer, 
												NBioAPI_UINT32 * nWidth, 
												NBioAPI_UINT32 * nHeight, 
												NBioAPI_UINT8* lpRawBuffer);

	NBioAPI_RETURN NBioAPI NBioAPI_ImgConvBmpToRawBufEx(
												NBioAPI_UINT8* lpImageBuffer, 
												NBioAPI_UINT32 nBmpBufLen,
												NBioAPI_UINT32 * nWidth, 
												NBioAPI_UINT32 * nHeight, 
												NBioAPI_UINT8* lpRawBuffer);

	NBioAPI_RETURN NBioAPI NBioAPI_ImgConvRawToJpgBuf(
												NBioAPI_UINT8* lpRawBuffer,	
												NBioAPI_UINT32 nWidth,	
												NBioAPI_UINT32 nHeight,
												int nQuality,	
												NBioAPI_UINT8* lpJpgBuffer, 
												int * nJpgBufLen);

	NBioAPI_RETURN NBioAPI NBioAPI_ImgConvRawToJpgBufEx(
												NBioAPI_UINT8* lpRawBuffer,	
												NBioAPI_UINT32 nWidth,	
												NBioAPI_UINT32 nHeight,
												int nQuality,
												NBioAPI_UINT32 nDPI,
												NBioAPI_UINT8* lpJpgBuffer, 
												int * nJpgBufLen);

	NBioAPI_RETURN NBioAPI NBioAPI_ImgConvJpgToRawBuf(
												NBioAPI_UINT8* lpJpgBuffer,
												NBioAPI_UINT32 nJpgBufLen,
												NBioAPI_UINT32 * nWidth,
												NBioAPI_UINT32 * nHeight,
												NBioAPI_UINT8* lpRawBuffer);

	NBioAPI_RETURN NBioAPI NBioAPI_ImgConvRawToWSQBuf(
												NBioAPI_UINT8* lpRawBuffer,
												int nWidth,
												int nHeight,
												NBioAPI_UINT8* lpWSQBuffer,
												int * nReturn_size,
												float p);

	NBioAPI_RETURN NBioAPI NBioAPI_ImgConvWSQToRawBuf(
												NBioAPI_UINT8* lpWSQBuffer,
												NBioAPI_UINT8* lpRawBuffer,
												int * nReturn_size,
												int * nWidth,
												int * nHeight);

	NBioAPI_RETURN NBioAPI NBioAPI_ImgConvRawToJ2kBuf(
												NBioAPI_UINT8* lpRawBuffer,	
												NBioAPI_UINT32 nWidth,	
												NBioAPI_UINT32 nHeight,
												float fRate ,	
												NBioAPI_UINT8* lpJpgBuffer, 
												NBioAPI_UINT32 * nJpgBufLen);

	NBioAPI_RETURN NBioAPI NBioAPI_ImgConvJ2kToRawBuf(
												NBioAPI_UINT8* lpJ2kBuffer,
												NBioAPI_UINT32 nJ2kBufLen,
												NBioAPI_UINT32 * nWidth,
												NBioAPI_UINT32 * nHeight,
												NBioAPI_UINT8* lpRawBuffer);


#endif/*_NBioAPI_LOAD_LIBRARY */

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImgConvRawToBmpBuf)(
												NBioAPI_UINT8* lpImageBuffer, 
												NBioAPI_UINT32 nWidth, 
												NBioAPI_UINT32 nHeight,
												NBioAPI_UINT8* lpBMPBuffer,
												int * nBMPBufLen);

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImgConvRawToBmpBufEx)(
												NBioAPI_UINT8* lpImageBuffer, 
												NBioAPI_UINT32 nWidth, 
												NBioAPI_UINT32 nHeight,
												NBioAPI_UINT32 nDPI,
												NBioAPI_UINT8* lpBMPBuffer,
												int * BMPBufLen);

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImgConvBmpToRawBuf)(
												NBioAPI_UINT8* lpImageBuffer, 
												NBioAPI_UINT32 * nWidth, 
												NBioAPI_UINT32 * nHeight, 
												NBioAPI_UINT8* lpRawBuffer);

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImgConvBmpToRawBufEx)(
												NBioAPI_UINT8* lpImageBuffer, 
												NBioAPI_UINT32 nBmpBufLen,
												NBioAPI_UINT32 * nWidth, 
												NBioAPI_UINT32 * nHeight, 
												NBioAPI_UINT8* lpRawBuffer);

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImgConvRawToJpgBuf)(
												NBioAPI_UINT8* lpRawBuffer,
												NBioAPI_UINT32 nWidth,			
												NBioAPI_UINT32 nHeight,		
												int nQuality,					 
												NBioAPI_UINT8* lpJpgBuffer,  
												int * nJpgBufLen); 

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImgConvRawToJpgBufEx)(
												NBioAPI_UINT8* lpRawBuffer,	
												NBioAPI_UINT32 nWidth,	
												NBioAPI_UINT32 nHeight,
												int nQuality,
												NBioAPI_UINT32 nDPI,
												NBioAPI_UINT8* lpJpgBuffer, 
												int * nJpgBufLen);

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImgConvJpgToRawBuf)(
												NBioAPI_UINT8* lpJpgBuffer,
												NBioAPI_UINT32 nJpgBufLen,
												NBioAPI_UINT32 * nWidth,
												NBioAPI_UINT32 * nHeight,
												NBioAPI_UINT8* lpBmpBuffer);

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImgConvRawToWSQBuf)(
												NBioAPI_UINT8* lpRawBuffer,
												int nWwidth,
												int nHeight,
												NBioAPI_UINT8* lpWSQBuffer,
												int * nReturn_size,
												float p);

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImgConvWSQToRawBuf)(
												NBioAPI_UINT8* lpWSQBuffer,
												NBioAPI_UINT8* lpRawBuffer,
												int * nReturn_size,
												int * nWidth,
												int * nHeight);


	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImgConvRawToJ2kBuf)(
												NBioAPI_UINT8* lpRawBuffer,
												NBioAPI_UINT32 nWidth,			
												NBioAPI_UINT32 nHeight,		
												float fRate,					 
												NBioAPI_UINT8* lpJpgBuffer,  
												int * nJpgBufLen); 

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImgConvJ2kToRawBuf)(
												NBioAPI_UINT8* lpJ2kBuffer,
												NBioAPI_UINT32 nJ2kBufLen,
												NBioAPI_UINT32 * nWidth,
												NBioAPI_UINT32 * nHeight,
												NBioAPI_UINT8* lpBmpBuffer);


#ifdef __cplusplus
}
#endif

#endif //_NITGEN_NBioAPI_IMGCONV_H
