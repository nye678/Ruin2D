#include "RuinAssert.h"
#include <cstdio>
#include <cstring>
#include <Windows.h>

using namespace Ruin2D::Assertion;

const char* AssertMessageFormat = "An assertion has failed at %s:%d\n\n%s";

AssertDialogResult Ruin2D::Assertion::ShowAssertionDialog(const char* message, const char* file, int line)
{
	char* formattedMessage = nullptr;
	size_t messageSize = FormatAssertMessage(message, file, line, formattedMessage);

	int dialogResult = MessageBoxA(nullptr, formattedMessage, "Assertion!", MB_ABORTRETRYIGNORE | MB_ICONERROR);
	AssertDialogResult assertDialogResult = None;

	switch (dialogResult)
	{
	case IDABORT:
		assertDialogResult = Abort;
		break;
	case IDRETRY:
		assertDialogResult = Debug;
		break;
	case IDIGNORE:
		assertDialogResult = Ignore;
		break;
	}

	if (formattedMessage)
	{
		delete[] formattedMessage;
	}

	return assertDialogResult;
}

size_t Ruin2D::Assertion::FormatAssertMessage(const char* message, const char* file, int line, char* buffer)
{
	size_t messageLength = strlen(message);
	size_t fileLength = strlen(file);
	size_t formatLength = strlen(AssertMessageFormat);
	size_t lineNumberLength = 15;

	size_t bufferSize = messageLength + fileLength + formatLength + lineNumberLength + 1;
	buffer = new char[bufferSize];
	memset(buffer, 0x00, bufferSize);
	sprintf_s(buffer, bufferSize, AssertMessageFormat, file, line, message);

	return bufferSize;
}