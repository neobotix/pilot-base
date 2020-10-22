/*
 * SerialPort.cpp
 *
 *  Created on: May 27, 2020
 *      Author: jaw
 */

#include <pilot/base/SerialPort.h>

#include <windows.h>


namespace pilot {
namespace base {

void SerialPort::open_port()
{
	close_port();

	std::string device = "\\\\.\\" + port;
	m_fd = CreateFile(device.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(m_fd == INVALID_HANDLE_VALUE){
		DWORD dwErrorCode = GetLastError();
		throw std::runtime_error("open('" + port + "') failed with: " + std::to_string(dwErrorCode));
	}


	// set parameters
	DCB dcb;
	if (!GetCommState(m_fd, &dcb)){
		DWORD dwErrorCode = GetLastError();
		throw std::runtime_error("GetCommState() of " + device + " failed with: " + std::to_string(dwErrorCode));
	}

	// Default values
	dcb.DCBlength = sizeof(dcb);
	dcb.BaudRate = (DWORD)baud_rate;
	dcb.fBinary = raw_mode ? TRUE : FALSE;
	dcb.fParity = FALSE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	dcb.fDsrSensitivity = FALSE;
	dcb.fTXContinueOnXoff = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	dcb.fErrorChar = FALSE;
	dcb.fNull = FALSE;	//!!!
	dcb.fRtsControl = RTS_CONTROL_ENABLE;
	dcb.fAbortOnError = FALSE;
	//dcb.wReserved = 0; // ??? ovb: visual c++ 2005 error
	dcb.XonLim = 0;
	dcb.XoffLim = 255;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.XonChar = 0;
	dcb.XoffChar = (char)255;
	dcb.ErrorChar = 0;
	dcb.EofChar = 0;
	dcb.EvtChar = 0;

	if(!SetCommState(m_fd, &dcb)){
		DWORD dwErrorCode = GetLastError();
		throw std::runtime_error("SetCommState() of " + device + " failed with: " + std::to_string(dwErrorCode));
	}

	log(INFO).out << "Opened port '" << port << "'";
}

void SerialPort::close_port()
{
	if(m_fd != INVALID_HANDLE_VALUE) {
		CloseHandle(m_fd);
		m_fd = INVALID_HANDLE_VALUE;
	}
}

ssize_t SerialPort::read_port(void* buf, size_t len, int timeout_ms) const
{
	// set read timeout
	COMMTIMEOUTS Timeouts = { 0, 0, (DWORD)timeout_ms, 0, 0 };
	SetCommTimeouts(m_fd, &Timeouts);

	DWORD BytesRead;
	if(!ReadFile(m_fd, buf, len, &BytesRead, NULL)){
		return -1;
	}

	return BytesRead;
}

ssize_t SerialPort::write_port(const void* buf, size_t len) const
{
	DWORD numBytesWritten;
	if(!WriteFile(m_fd, buf, len, &numBytesWritten, NULL)){
		return -1;
	}

	return numBytesWritten;
}


} // base
} // pilot
