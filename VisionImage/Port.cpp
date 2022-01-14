#include "pch.h"
#include "stdafx.h"
#include "Port.h"

using namespace std;
using namespace GenApi;
using namespace GenICam;
using namespace GenICam::Client;

CPort::CPort(PORT_HANDLE hPort)
	: m_hPort(hPort)
{

}

CPort::~CPort(void)
{

}

void  CPort::Read(void *pBuffer, int64_t Address, int64_t Length)
{
	size_t iSize = (size_t)Length;
	GC_ERROR status = GC_ERR_SUCCESS;
	status = GCReadPort(m_hPort, Address, pBuffer, &iSize);
	if ((status < 0) || (iSize != Length))
	{
		char pBuffer[256];
		sprintf_s(pBuffer, "Read register 0x%I64X is failed.", Address);
		throw ACCESS_EXCEPTION(pBuffer);
	}
}

void  CPort::Write(const void *pBuffer, int64_t Address, int64_t Length)
{
	size_t iSize = (size_t)Length;
	GC_ERROR status = GC_ERR_SUCCESS;
	status = GCWritePort(m_hPort, Address, pBuffer, &iSize);
	if ((status < 0) || (iSize != Length))
	{
		char pBuffer[256];
		sprintf_s(pBuffer, "Write register 0x%I64X is failed.", Address);
		throw ACCESS_EXCEPTION(pBuffer);
	}
}

EAccessMode CPort::GetAccessMode() const
{
	return RW;
}