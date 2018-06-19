#pragma once

#include <vcclr.h>

#include "mip/stream.h"

namespace NetMip
{
	private class StreamWrapper : public mip::Stream
	{
	public:
		StreamWrapper(gcroot<System::IO::Stream^> stream)
			: m_cli(stream)
		{ }

		virtual int64_t Read(uint8_t* buffer, int64_t bufferLength) override;
		virtual int64_t Write(const uint8_t* buffer, int64_t bufferLength) override;
		virtual bool Flush() override;
		virtual void Seek(uint64_t position) override;
		virtual bool CanRead() const override;
		virtual bool CanWrite() const override;
		virtual uint64_t Position() override;
		virtual uint64_t Size() override;
		virtual void Size(uint64_t value) override;
		virtual std::shared_ptr<mip::Stream> Clone() override;

	private:
		gcroot<System::IO::Stream^> m_cli;
	};
}
