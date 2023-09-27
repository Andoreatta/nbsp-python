#ifndef _NITGEN_NEXPORTRAWTOISO_H
#define _NITGEN_NEXPORTRAWTOISO_H

#include "NBioAPI_Basic.h"
#include "NBioAPI_Type.h"
#include "NBioAPI_ExportType.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NEXPORT_COMPRESS_MOD_NONE   0
#define NEXPORT_COMPRESS_MOD_WSQ    1

	typedef struct _tagNImportRaw  {
		NBioAPI_UINT8     nFingerID;
		NBioAPI_UINT16    nImgWidth;
		NBioAPI_UINT16    nImgHeight;
		NBioAPI_UINT32    nDataLen;
		NBioAPI_UINT8*    pRawData;
	} NIMPORTRAW, * NIMPORTRAW_PTR;

	typedef struct _tagNImportRawSet  {
		NBioAPI_UINT8     nDataCount;
		NIMPORTRAW_PTR    pImportRawData;
	} NIMPORTRAWSET, * NIMPORTRAWSET_PTR;

#ifndef _NEXPORTRAWTOISO_LOAD_LIBRARY

   NBioAPI_RETURN NBioAPI NBioAPI_ExportRawToISOV1(NBioAPI_EXPORT_AUDIT_DATA_PTR pAuditData, 
                                                   NBioAPI_UINT8**               pISOBuf, 
                                                   NBioAPI_UINT32*               pISOBufLen,
                                                   NBioAPI_BOOL                  bIsRollDevice,
                                                   NBioAPI_UINT8                 nCompressMod);

   NBioAPI_RETURN NBioAPI NBioAPI_ExportRawToISOV2(NBioAPI_UINT8     nFingerID, 
                                                   NBioAPI_UINT16    nImgWidth, 
                                                   NBioAPI_UINT16    nImgHeight, 
                                                   NBioAPI_UINT8*    pRawBuf, 
                                                   NBioAPI_UINT8**   pISOBuf, 
                                                   NBioAPI_UINT32*   pISOBufLen,
                                                   NBioAPI_BOOL      bIsRollDevice,
                                                   NBioAPI_UINT8     nCompressMod);

   NBioAPI_RETURN NBioAPI NBioAPI_ExportRawToANSIV1(NBioAPI_EXPORT_AUDIT_DATA_PTR pAuditData, 
                                                   NBioAPI_UINT8**               pISOBuf, 
                                                   NBioAPI_UINT32*               pISOBufLen,
                                                   NBioAPI_BOOL                  bIsRollDevice,
                                                   NBioAPI_UINT8                 nCompressMod);

   NBioAPI_RETURN NBioAPI NBioAPI_ExportRawToANSIV2(NBioAPI_UINT8     nFingerID, 
                                                   NBioAPI_UINT16    nImgWidth, 
                                                   NBioAPI_UINT16    nImgHeight, 
                                                   NBioAPI_UINT8*    pRawBuf, 
                                                   NBioAPI_UINT8**   pISOBuf, 
                                                   NBioAPI_UINT32*   pISOBufLen,
                                                   NBioAPI_BOOL      bIsRollDevice,
                                                   NBioAPI_UINT8     nCompressMod);


   NBioAPI_RETURN NBioAPI NBioAPI_ImportISOToRaw(NBioAPI_UINT8*      pISOBuf, 
                                                 NBioAPI_UINT32      nISOBufLen, 
                                                 NIMPORTRAWSET_PTR   pImportRawSet);

   NBioAPI_RETURN NBioAPI NBioAPI_ImportANSIToRaw(NBioAPI_UINT8*      pISOBuf, 
                                                  NBioAPI_UINT32      nISOBufLen, 
                                                  NIMPORTRAWSET_PTR   pImportRawSet);

   void NBioAPI NBioAPI_FreeExportISOData(NBioAPI_UINT8* pISOBuf);

   void NBioAPI NBioAPI_FreeImportRawSet(NIMPORTRAWSET_PTR pImportRawSet);

#else
	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ExportRawToISOV1)(NBioAPI_EXPORT_AUDIT_DATA_PTR pAuditData, 
		NBioAPI_UINT8**               pISOBuf, 
		NBioAPI_UINT32*               pISOBufLen,
		NBioAPI_BOOL                  bIsRollDevice,
		NBioAPI_UINT8                 nCompressMod);

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ExportRawToISOV2)(NBioAPI_UINT8     nFingerID, 
		NBioAPI_UINT16    nImgWidth, 
		NBioAPI_UINT16    nImgHeight, 
		NBioAPI_UINT8*    pRawBuf, 
		NBioAPI_UINT8**   pISOBuf, 
		NBioAPI_UINT32*   pISOBufLen,
		NBioAPI_BOOL      bIsRollDevice,
		NBioAPI_UINT8     nCompressMod);

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ExportRawToANSIV1)(NBioAPI_EXPORT_AUDIT_DATA_PTR pAuditData, 
		NBioAPI_UINT8**               pISOBuf, 
		NBioAPI_UINT32*               pISOBufLen,
		NBioAPI_BOOL                  bIsRollDevice,
		NBioAPI_UINT8                 nCompressMod);

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ExportRawToANSIV2)(NBioAPI_UINT8     nFingerID, 
		NBioAPI_UINT16    nImgWidth, 
		NBioAPI_UINT16    nImgHeight, 
		NBioAPI_UINT8*    pRawBuf, 
		NBioAPI_UINT8**   pISOBuf, 
		NBioAPI_UINT32*   pISOBufLen,
		NBioAPI_BOOL      bIsRollDevice,
		NBioAPI_UINT8     nCompressMod);

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImportISOToRaw)(NBioAPI_UINT8*      pISOBuf, 
		NBioAPI_UINT32      nISOBufLen, 
		NIMPORTRAWSET_PTR   pImportRawSet);

	typedef NBioAPI_RETURN (NBioAPI* FP_NBioAPI_ImportANSIToRaw)(NBioAPI_UINT8*      pISOBuf, 
		NBioAPI_UINT32      nISOBufLen, 
		NIMPORTRAWSET_PTR   pImportRawSet);

	typedef void (NBioAPI* FP_NBioAPI_FreeExportISOData)(NBioAPI_UINT8* pISOBuf);
	typedef void (NBioAPI* FP_NBioAPI_FreeImportRawSet)(NIMPORTRAWSET_PTR pImportRawSet);
   
#endif//_NEXPORTRAWTOISO_LOAD_LIBRARY

#ifdef __cplusplus
}
#endif

#endif//_NITGEN_NEXPORTRAWTOISO_H
