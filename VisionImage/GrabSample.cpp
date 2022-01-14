#include "stdafx.h"
#include "pch.h"
#include <conio.h>
#include <algorithm>
#include "Port.h"
#include "GenApi/GenApi.h"
#include "TLI/GenTL.h"

using namespace std;
using namespace GenApi;
using namespace GenICam;
using namespace GenICam::Client;

#define BUFF_COUNT		4

CPort*			g_pPort = NULL;
CNodeMapRef*	g_pDeviceMap = NULL;

void HandleError(const char *pText)
{
	char szBuffer[4096] = { 0, };
	size_t iSize = 4096;
	printf_s("%s", pText);
	GC_ERROR status = GCGetLastError(NULL, szBuffer, &iSize);
	if (status == GC_ERR_SUCCESS)
		printf_s("\t%s\n", szBuffer);
	else
		printf_s("\tNo additional information\n");
}

gcstring RetrieveXML(PORT_HANDLE hPort)
{
	GC_ERROR status;
	char sURL[2048];
	size_t iUrlLength = 0;
	size_t iLength;
	uint64_t iAddr;
	size_t iOffset;
	size_t   iXMLSize;
	gcstring gcstrXml;

	string strFilename;
	char *pEnd;
	iLength = 2048;

	iUrlLength = 2048;
	status = GCGetPortURL(hPort, sURL, &iUrlLength);
	if (status < 0)
	{
		HandleError("Erron in GCGetPortURL : ");
		return gcstrXml;
	}
	if (strlen(sURL) > 2047)
		return gcstrXml;

	// Read XML Address
	string strXMLAddress = sURL;
	string strLocation = strXMLAddress.substr(0, 6);
	std::transform(strLocation.begin(), strLocation.end(), strLocation.begin(), (int(*)(int)) toupper);
	string strXMLFilename;

	if (strLocation == "LOCAL:")
	{
		iOffset = 6;
		iLength = (uint32_t)strXMLAddress.find(";", iOffset);
		strFilename = strXMLAddress.substr(iOffset, iLength - iOffset);

		iOffset = iLength + 1;
		iLength = strXMLAddress.find(";", iOffset);
		iAddr = _strtoui64(strXMLAddress.substr(iOffset, iLength - iOffset).c_str(), &pEnd, 16);

		iOffset = iLength + 1;
		iLength = strXMLAddress.size();
		iXMLSize = (size_t)_strtoui64(strXMLAddress.substr(iOffset, iLength - iOffset).c_str(), &pEnd, 16);

		iXMLSize = (iXMLSize + 3)&~3;  // make sure we read from a dword boundary
		void *pXML = malloc(iXMLSize + 1);
		memset(pXML, 0, iXMLSize + 1);

		GCReadPort(hPort, iAddr, pXML, &iXMLSize);

		((BYTE *)pXML)[iXMLSize] = '\0';
		gcstrXml = (char *)pXML;

		free(pXML);
	}

	if (gcstrXml == "")
		throw ACCESS_EXCEPTION("Unable to retrieve XML");

	return gcstrXml;
}

CNodeMapRef* GetNodeMap(PORT_HANDLE hPort)
{
	if (g_pDeviceMap)
		return g_pDeviceMap;

	GC_ERROR status;
	CNodeMapRef *pDeviceMap = new CNodeMapRef;

	gcstring strXML = RetrieveXML(hPort);
	pDeviceMap->_LoadXMLFromString(strXML);

	if (g_pPort)		delete g_pPort;
	g_pPort = new CPort(hPort);
	GenApi::IPort *pGenApiPort = dynamic_cast<GenApi::IPort *>(g_pPort);

	char szPortName[256];
	size_t iSize = 256;
	INFO_DATATYPE iType;
	status = GCGetPortInfo(hPort, PORT_INFO_PORTNAME, &iType, szPortName, &iSize);
	if (status < 0)
	{
		delete pDeviceMap;
		HandleError("Erron in GCGetPortInfo : ");
		return NULL;
	}

	gcstring gcstrPortName = szPortName;
	bool bResult = pDeviceMap->_Connect(pGenApiPort, gcstrPortName);

	g_pDeviceMap = pDeviceMap;
	return pDeviceMap;
}

TL_HANDLE SelectTL(void)
{
	// Load TL
	GC_ERROR status;
	TL_HANDLE hTl = NULL;
	status = TLOpen(&hTl);
	if (status < 0)
	{
		HandleError("Error in TLOpen :");
	}

	return hTl;
}

IF_HANDLE SelectInterface(TL_HANDLE hTl)
{
	// Loading first Interface
	GC_ERROR status;
	uint32_t iNumInterfaces = 0;
	IF_HANDLE hInterface = NULL;
	char szBuffer[1024];
	size_t iSize = 1024;

	printf_s("\n", szBuffer);
	status = TLUpdateInterfaceList(hTl, NULL, 500);
	if (status < 0)
	{
		HandleError("Erron in TLUpdateInterfaceList : ");
		return NULL;
	}

	status = TLGetNumInterfaces(hTl, &iNumInterfaces);
	if (status < 0)
	{
		HandleError("Erron in TLGetNumInterfaces : ");
		return NULL;
	}

	if (iNumInterfaces < 1)
	{
		printf_s("This TL returns no interfaces\n");
		return NULL;
	}

	// retrieve name of interface with index 0
	// 0 index : USB 1,  index : GigE
	iSize = 1024;
	status = TLGetInterfaceID(hTl, 1, szBuffer, &iSize);
	if (status < 0)
	{
		HandleError("Erron in TLGetInterfaceID : ");
		return NULL;
	}

	// Open the interface
	status = TLOpenInterface(hTl, szBuffer, &hInterface);
	if (status < 0)
	{
		HandleError("Erron in TLOpenInterface : ");
		return NULL;
	}
	return hInterface;
}

DEV_HANDLE SelectDevice(IF_HANDLE hInterface)
{
	GC_ERROR status;
	DEV_HANDLE hDev = NULL;
	bool HasChanged;
	char szName[1024];
	size_t iSize = 1024;
	uint32_t iNumDevs = 0;

	// Loading first Device
	status = IFUpdateDeviceList(hInterface, &HasChanged, 500);
	if (status < 0)
	{
		HandleError("Erron in IFUpdateDeviceList : ");
		return NULL;
	}

	status = IFGetNumDevices(hInterface, &iNumDevs);
	if (status < 0)
	{
		HandleError("Erron in IFGetNumDevices : ");
		return NULL;
	}

	if (iNumDevs < 1)
	{
		printf_s("No Device\n");
		return NULL;
	}

	iSize = 1024;
	status = IFGetDeviceID(hInterface, 0, szName, &iSize);
	if (status < 0)
	{
		HandleError("Erron in IFGetDeviceID : ");
		return NULL;
	}

	status = IFOpenDevice(hInterface, szName, DEVICE_ACCESS_NONE, &hDev);
	if (status < 0)
	{
		HandleError("Erron in IFOpenDevice : ");
		return NULL;
	}

	return hDev;
}

DS_HANDLE SelectDataStream(DEV_HANDLE hDevice)
{
	GC_ERROR status;
	DS_HANDLE hDatastream = NULL;
	char szBuffer[1024];
	size_t iSize = 1024;
	uint32_t iNumStreams;

	// Loading first DataStream
	status = DevGetNumDataStreams(hDevice, &iNumStreams);
	if (status < 0)
	{
		HandleError("Erron in DevGetNumDataStreams : ");
		return NULL;
	}

	if (iNumStreams < 1)
	{
		printf_s("No DataStream\n");
		return NULL;
	}

	iSize = 1024;
	status = DevGetDataStreamID(hDevice, 0, szBuffer, &iSize);
	if (status < 0)
	{
		HandleError("Erron in DevGetDataStreamID : ");
		return NULL;
	}

	iSize = 1024;
	status = DevOpenDataStream(hDevice, szBuffer, &hDatastream);
	if (status < 0)
	{
		HandleError("Erron in DevOpenDataStream : ");
		return NULL;
	}

	return hDatastream;
}

uint32_t GetImageSize(string strPixelFormat, uint32_t Width, uint32_t Height)
{
	uint32_t ImageSize = 0;
	if (strPixelFormat == "Mono8")
	{
		ImageSize = Width * Height;
	}
	else if (strPixelFormat == "Mono10")
	{
		ImageSize = Width * 2 * Height;
	}
	else if (strPixelFormat == "Mono12")
	{
		ImageSize = Width * 2 * Height;
	}
	else if (strPixelFormat == "Mono10_PACKED")
	{
		ImageSize = ((Width >> 1) * 3)*Height;
	}
	else if (strPixelFormat == "Mono12_PACKED")
	{
		ImageSize = ((Width >> 1) * 3)*Height;
	}
	else if (strPixelFormat == "BayerRG8")
	{
		ImageSize = Width * Height;
	}
	else if (strPixelFormat == "BayerRG10")
	{
		ImageSize = Width * 2 * Height;
	}
	else if (strPixelFormat == "BayerRG12")
	{
		ImageSize = Width * 2 * Height;
	}
	else if (strPixelFormat == "BayerRG10_PACKED")
	{
		ImageSize = ((Width >> 1) * 3)*Height;
	}
	else if (strPixelFormat == "BayerRG12_PACKED")
	{
		ImageSize = ((Width >> 1) * 3)*Height;
	}
	else if (strPixelFormat == "YUV422_PACKED")
	{
		ImageSize = Width * 2 * Height;
	}
	else if (strPixelFormat == "YUV422_YUYV_Packed")
	{
		ImageSize = Width * 2 * Height;
	}
	else if (strPixelFormat == "BGR8_PACKED")
	{
		ImageSize = Width * 3 * Height;
	}
	else if (strPixelFormat == "RGB8_PACKED")
	{
		ImageSize = Width * 3 * Height;
	}
	return ImageSize;
}


void GrabImage(DEV_HANDLE hDev)
{
	GC_ERROR		status;
	void*			pImageBuffer[BUFF_COUNT];
	DS_HANDLE		hDatastream = NULL;
	PORT_HANDLE		hRemoteDevicePort = NULL;
	size_t			iSize;
	uint32_t		uAcqStartStop = 0;
	uint64_t		AcqFrameCount;
	BUFFER_HANDLE	pB = NULL;
	void*			NewImageEventData[2];
	EVENT_HANDLE	pEventNewBuffer = NULL;
	void*			pBase = NULL;
	CNodeMapRef*	pDeviceMap = NULL;
	int32_t			i, j;
	memset(pImageBuffer, 0, sizeof(pImageBuffer));

	try
	{
		// open data stream
		hDatastream = SelectDataStream(hDev);
		if (hDatastream == NULL)
			return;

		//retrieve access to device 
		status = DevGetPort(hDev, &hRemoteDevicePort);
		if (status < 0)
			throw("Erron in DevGetPort : ");

		//retrieve access to register
		pDeviceMap = GetNodeMap(hRemoteDevicePort);
		if (pDeviceMap == NULL)
			return;

		// Get PixelFormat
		CEnumerationPtr ptrPixelFormat = pDeviceMap->_GetNode("PixelFormat");
		string strPixelFormat = ptrPixelFormat->ToString().c_str();

		// Get image information
		CIntegerPtr ptrWidth = pDeviceMap->_GetNode("Width");
		uint32_t Width = (uint32_t)ptrWidth->GetValue();

		CIntegerPtr ptrHeight = pDeviceMap->_GetNode("Height");
		uint32_t Height = (uint32_t)ptrWidth->GetValue();

		uint32_t ImageSize = GetImageSize(strPixelFormat, Width, Height);

		// alloc and announce buffer
		for (i = 0; i < BUFF_COUNT; i++)
		{
			pImageBuffer[i] = malloc(ImageSize);
			status = DSAnnounceBuffer(hDatastream, pImageBuffer[i], ImageSize, NULL, &pB);
			if (status < 0)
				throw("Erron in DSAnnounceBuffer : ");
			status = DSQueueBuffer(hDatastream, pB);
			if (status < 0)
				throw("Erron in DSQueueBuffer : ");
		}

		// Register New Buffer Event
		status = GCRegisterEvent(hDatastream, EVENT_NEW_BUFFER, &pEventNewBuffer);
		if (status < 0)
			throw("Erron in GCRegisterEvent : ");

		// Start Acquisition
		AcqFrameCount = 0xffffffffffffffff;
		status = DSStartAcquisition(hDatastream, ACQ_START_FLAGS_DEFAULT, AcqFrameCount);

		// Send Acquisition start
		CCommandPtr ptrAcquisitionStart = pDeviceMap->_GetNode("AcquisitionStart");
		ptrAcquisitionStart->Execute();

		// Acquisition Loop
		bool bRun = true;
		while (bRun)
		{
			// Get event data
			iSize = sizeof(NewImageEventData);
			status = EventGetData(pEventNewBuffer, &NewImageEventData, &iSize, 500);
			if (status == GC_ERR_TIMEOUT)
			{
				printf_s("Timeout\n");
				if (_kbhit())
				{
					toupper(_getch());
					bRun = false;
				}
			}
			else if (status < 0)
			{
				throw("Erron in EventGetData : ");
			}
			else
			{
				// Get image
				iSize = sizeof(pBase);
				status = DSGetBufferInfo(hDatastream, NewImageEventData[0], BUFFER_INFO_BASE, NULL, &pBase, &iSize);
				if (status < 0)
					throw("Erron in DSGetBufferInfo : ");

				printf_s("NewImage : %d\n", (WORD)((BYTE*)pBase)[0]);

				// Queue buffer
				status = DSQueueBuffer(hDatastream, NewImageEventData[0]);
				if (status < 0)
					throw("Erron in DSQueueBuffer : ");

				if (_kbhit())
				{
					toupper(_getch());
					bRun = false;
				}
			}
		}

		// Stop Acquisition
		status = DSStopAcquisition(hDatastream, ACQ_STOP_FLAGS_DEFAULT);
		if (status < 0)
			throw("Erron in DSStopAcquisition : ");

		// Send Acquisition stop
		CCommandPtr ptrAcquisitionStop = pDeviceMap->_GetNode("AcquisitionStop");
		ptrAcquisitionStop->Execute();

		// Unregister Even
		status = GCUnregisterEvent(hDatastream, EVENT_NEW_BUFFER);
		if (status < 0)
			throw("Erron in GCUnregisterEvent : ");

		// Cleanup
		status = DSFlushQueue(hDatastream, ACQ_QUEUE_INPUT_TO_OUTPUT);
		if (status < 0)
			throw("Erron in DSFlushQueue : ");

		status = DSFlushQueue(hDatastream, ACQ_QUEUE_OUTPUT_DISCARD);
		if (status < 0)
			throw("Erron in DSFlushQueue : ");

		// Close DataStream
		status = DSClose(hDatastream);
		hDatastream = NULL;
		if (status < 0)
			throw("Erron in DSClose : ");

		// free buffer
		for (j = 0; j < BUFF_COUNT; j++)
		{
			if (pImageBuffer[j])
				free(pImageBuffer[j]);
			pImageBuffer[j] = NULL;
		}
	}
	catch (GenericException e)
	{
		// Close DataStream
		if (hDatastream)
			DSClose(hDatastream);

		// free buffer
		for (j = 0; j < BUFF_COUNT; j++)
		{
			if (pImageBuffer[j])
				free(pImageBuffer[j]);
			pImageBuffer[j] = NULL;
		}

		printf_s("Error : %s\r\n", e.GetDescription());
		return;
	}
	catch (char* pErr)
	{
		// Close DataStream
		if (hDatastream)
			DSClose(hDatastream);

		// free buffer
		for (j = 0; j < BUFF_COUNT; j++)
		{
			if (pImageBuffer[j])
				free(pImageBuffer[j]);
			pImageBuffer[j] = NULL;
		}

		HandleError(pErr);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	TL_HANDLE hTl = NULL;
	IF_HANDLE hInterface = NULL;
	DEV_HANDLE hDevice = NULL;

	GCInitLib();

	// Open TL
	hTl = SelectTL();
	if (hTl != NULL)
	{
		// Open Interface
		hInterface = SelectInterface(hTl);
		if (hInterface != NULL)
		{
			// Open Device
			hDevice = SelectDevice(hInterface);
			if (hDevice != NULL)
			{
				// Grab Image
				GrabImage(hDevice);
			}
			DevClose(hDevice);
		}
		IFClose(hInterface);
	}

	TLClose(hTl);

	GCCloseLib();

	if (g_pPort)
		delete g_pPort;

	if (g_pDeviceMap)
		delete g_pDeviceMap;

	return 0;
}
