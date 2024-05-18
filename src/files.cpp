#include <dreamcatcher.hpp>
#include <internals.hpp>

WORD __cdecl DF_OpenFile(
	const char* pPfxFilePath,
	HANDLE* pFileHandle)
{
	WORD result = 0;
	HANDLE fileHandle = INVALID_HANDLE_VALUE;
	char resolvedFilePath[MAX_PATH];

	memset(resolvedFilePath, '\0', sizeof(resolvedFilePath) / sizeof(char));

	DF_ProcessMessages();

	DF_ResolveFilePath(pPfxFilePath, resolvedFilePath);
	
	fileHandle = CreateFileA(
		resolvedFilePath,
		(GENERIC_READ | GENERIC_WRITE),
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		(FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH),
		NULL);

	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		fileHandle = CreateFileA(
			resolvedFilePath,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			(FILE_FLAG_WRITE_THROUGH | FILE_ATTRIBUTE_READONLY),
			NULL);

		if (fileHandle == INVALID_HANDLE_VALUE)
		{
			result = 0x006B;
		}
	}

#if 1
	printf("Opening \"%.*s\" -> %s\n", pPfxFilePath[0], &pPfxFilePath[1], resolvedFilePath);
#endif

	*pFileHandle = fileHandle;

	return result;
}

BEGIN_CALL_PATCHES(DF_OpenFile)
	PATCH_CALL_IN_DUST(0x00401BC1)
	PATCH_CALL_IN_DUST(0x0042B375)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x0042CF20, DF_OpenFile);

WORD __cdecl DF_CloseFile(
	HANDLE* pFileHandle)
{
	BOOL result;

	DF_ProcessMessages();

	result = CloseHandle(*pFileHandle);

	return result ? 0 : 0x006B;
}

BEGIN_CALL_PATCHES(DF_CloseFile)
	PATCH_CALL_IN_DUST(0x00401B86)
	PATCH_CALL_IN_DUST(0x00401D14)
	PATCH_CALL_IN_DUST(0x0042B468)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x0042CFB0, DF_CloseFile);

WORD __cdecl DF_ReadIntoBuffer(
	HANDLE* pFile,
	char* pBuffer,
	size_t bufferLength)
{
	int result = 0;

	DF_ProcessMessages();
	
	if (SetFilePointer(*pFile, 0, 0, 1) != INVALID_SET_FILE_POINTER)
	{
		do
		{
			DF_ProcessMessages();

			if (bufferLength)
			{
				DWORD numOfBytesToRead = 10000;
				DWORD numOfBytesThatWereRead = 0;

				if (bufferLength < numOfBytesToRead)
				{
					numOfBytesToRead = bufferLength;
				}

				BOOL readResult = ReadFile(
					*pFile, pBuffer,
					numOfBytesToRead, &numOfBytesThatWereRead,
					NULL);

				if (readResult)
				{
					pBuffer += numOfBytesThatWereRead;
					bufferLength -= numOfBytesThatWereRead;

					if (numOfBytesThatWereRead == numOfBytesToRead)
					{
						continue;
					}
				}

#if DEBUG
				__debugbreak();
#endif
			}
			else
			{
				result = 0;
				break;
			}
		} while (true);
	}
	else
	{
		result = 0x006B;
	}

	return result;
}

BEGIN_CALL_PATCHES(DF_ReadIntoBuffer)
	PATCH_CALL_IN_DUST(0x00401C12)
	PATCH_CALL_IN_DUST(0x00401E97)
	PATCH_CALL_IN_DUST(0x004021C0)
	PATCH_CALL_IN_DUST(0x00402540)
	PATCH_CALL_IN_DUST(0x0040264A)
	PATCH_CALL_IN_DUST(0x00402DAC)
	PATCH_CALL_IN_DUST(0x0042B3FB)
	PATCH_CALL_IN_DUST(0x0042B42C)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x0042CB90, DF_ReadIntoBuffer);

WORD __cdecl DF_GetFileSize(
	HANDLE* pFileHandle,
	DWORD* pFileSize)
{
	WORD result = 0;

	DWORD fileSize = GetFileSize(*pFileHandle, NULL);

	if (!fileSize)
	{
		result = 0x006B;
	}

	*pFileSize = fileSize;

	return result;
}

BEGIN_CALL_PATCHES(DF_GetFileSize)
	PATCH_CALL_IN_DUST(0x00401C42)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x0042CFE0, DF_GetFileSize);

WORD __cdecl DF_GetFileExists(
	char* pPfxString, 
	DWORD* unknown1,
	DWORD* unknown2)
{
	WORD result = 0;

	char filePath[MAX_PATH];

	DF_ProcessMessages();

	memset(filePath, '\0', sizeof(filePath));

	DF_ResolveFilePath(pPfxString, filePath);
	
	if (GetFileAttributes(filePath) == INVALID_FILE_ATTRIBUTES)
	{
		result = 0x006B;
	}
	else
	{
		if (unknown1)
			*unknown1 = 0;

		if (unknown2)
			*unknown2 = 0;
	}

	return result;
}

BEGIN_CALL_PATCHES(DF_GetFileExists)
	PATCH_CALL_IN_DUST(0x0042D027)
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x0042CE70, DF_GetFileExists)

// Override this function to prevent the game
// from asking for a CD-ROM
DWORD __cdecl DF_Prompt_CDROM()
{
	printf("Skipping CD-ROM check\n");
	return 0;
}

BEGIN_CALL_PATCHES(DF_Prompt_CDROM)
	PATCH_CALL_IN_DUST(0x0042BDFA) // CD-ROM Check
END_CALL_PATCHES

DECLARE_DF_FUNCTION_IN_DUST(
	0x0042b320, DF_Prompt_CDROM);