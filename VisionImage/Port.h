#ifndef GC_PORT_H_
#define GC_PORT_H_

#include "TLI/GenTL.h"
#include "GenApi/GenApi.h"


class CPort
	: public GenApi::IPort
{
public:
	CPort(GenICam::Client::PORT_HANDLE hPort);
	virtual       ~CPort(void);

	virtual void  Read(void *pBuffer, int64_t Address, int64_t Length);

	virtual void  Write(const void *pBuffer, int64_t Address, int64_t Length);

	virtual		GenApi::EAccessMode GetAccessMode(void) const;

private:

	GenICam::Client::PORT_HANDLE   m_hPort;
};

#endif //GC_PORT_H_