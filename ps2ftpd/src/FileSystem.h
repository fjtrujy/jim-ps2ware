#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

/*
 * FileSystem.h - FTP server filesystem declarations
 *
 * Copyright (C) 2004 Jesper Svennevid
 *
 * Licensed under the AFL v2.0. See the file LICENSE included with this
 * distribution for licensing terms.
 *
 */

#ifdef LINUX
#include <dirent.h>
#else
#include <iomanX.h>
#endif

#define FS_IOMAN_DEVICES 16
#define FS_IOMANX_DEVICES 32

#ifndef LINUX
typedef enum
{
	FS_INVALID,
	FS_DEVLIST,
	FS_IODEVICE, // ioman or iomanX
} FSType;
#endif

typedef enum
{
	FM_READ,
	FM_CREATE,
	FM_APPEND,
} FileMode;

typedef struct FSContext
{
	char m_Path[256];

#ifndef LINUX
	FSType m_eType;
	iop_file_t m_kFile;
	char m_List[256];
#else
	int m_iFile;
	DIR* m_pDir;
#endif
} FSContext;

typedef enum
{
	FT_FILE,
	FT_DIRECTORY
} FileType;

typedef struct FSDirectory
{
	FileType	m_eType;	
	int				m_iSize;
	char			m_Name[256];
} FSDirectory;

//! Initialize context for use
void FileSystem_Create( FSContext* pContext );

//! Cleanup context
void FileSystem_Destroy( FSContext* pContext );

//! Open file for readin or writing
int FileSystem_OpenFile( FSContext* pContext, const char* pFile, FileMode eMode );

//! Open directory for listing
int FileSystem_OpenDir( FSContext* pContext, const char* pDir );

//! Read data from open file
int FileSystem_ReadFile( FSContext* pContext, char* pBuffer, int iSize );

//! Write data to open file
int FileSystem_WriteFile( FSContext* pContext, const char* pBuffer, int iSize );

//! Read directory
int FileSystem_ReadDir( FSContext* pContext, FSDirectory* pDirectory );

//! Get file information
int FileSystem_GetFileInfo( FSDirectory* pDirectory, const char* pPath );

//! Close file or directory
void FileSystem_Close( FSContext* pContext );

//! Determine device needed for accessing device & fill centext with info
const char* FileSystem_ClassifyPath( FSContext* pContext, const char* pPath );

//! Convert path from unified name to PS2 specific path (no verification of existance)
void FileSystem_BuildPath( char* pResult, const char* pOriginal, const char* pAdd );

//! Change directory
int FileSystem_ChangeDir( FSContext* pContext, const char* pPath );

//! Delete file
int FileSystem_DeleteFile( FSContext* pContext, const char* pFile );

//! Create new directory
int FileSystem_CreateDir( FSContext* pContext, const char* pDir );

//! Delete directory
int FileSystem_DeleteDir( FSContext* pContext, const char* pDir );

//! Scan devices & return ops structure if found
iop_device_t* FileSystem_ScanDevice( const char* pDevice, int iNumDevices, const char* pPath );

#endif

