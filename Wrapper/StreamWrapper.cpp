#include "StreamWrapper.h"

using namespace System::Runtime::InteropServices;

namespace NetMip
{

	int64_t StreamWrapper::Read(uint8_t* buffer, int64_t bufferLength)
	{
		array<unsigned char>^ cliBuffer = gcnew array<unsigned char>((int)bufferLength);

		auto bytesRead = m_cli->Read(cliBuffer, 0, (int)bufferLength);

		Marshal::Copy(cliBuffer, 0, System::IntPtr((void *)buffer), (int)bufferLength);

		return bytesRead;
	}

	int64_t StreamWrapper::Write(const uint8_t* buffer, int64_t bufferLength)
	{
		array<unsigned char>^ cliBuffer = gcnew array<unsigned char>((int)bufferLength);

		Marshal::Copy(System::IntPtr((void *)buffer), cliBuffer, 0, (int)bufferLength);

		m_cli->Write(cliBuffer, 0, (int)bufferLength);
		return bufferLength;
	}

	bool StreamWrapper::Flush()
	{
		m_cli->Flush();
		return true;
	}

	void StreamWrapper::Seek(uint64_t position)
	{
		// TODO: Is SeekOrigin::Begin the correct parameter to use here, or should it be SeekOrigin::Current
		m_cli->Seek(position, System::IO::SeekOrigin::Begin);
	}

	bool StreamWrapper::CanRead() const
	{
		return m_cli->CanRead::get();
	}

	bool StreamWrapper::CanWrite() const
	{
		return m_cli->CanWrite::get();
	}

	uint64_t StreamWrapper::Position()
	{
		return m_cli->Position::get();
	}

	uint64_t StreamWrapper::Size()
	{
		return m_cli->Length::get();
	}

	void StreamWrapper::Size(uint64_t value)
	{
		m_cli->SetLength(value);
	}

	std::shared_ptr<mip::Stream> StreamWrapper::Clone()
	{
		// TODO:
		throw 1;
	}
}
