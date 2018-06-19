#pragma once

#include <vcclr.h>

#include "mip/stream.h"

namespace CLI
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

	/*
	ref class StreamWrapper  : public System::IO::Stream
	{
	protected:
		std::shared_ptr<mip::Stream>* m_Instance;

	internal:
		StreamWrapper(std::shared_ptr<mip::Stream>* instance)
			: m_Instance(instance)
		{
		}

	public:
		virtual ~StreamWrapper()
		{
			this->!StreamWrapper();
		}

		!StreamWrapper()
		{
			if (m_Instance != nullptr)
			{
				delete m_Instance;
				m_Instance = nullptr;
			}
		}

	public:
		property virtual bool CanRead { bool get() override; };

		property virtual bool CanSeek { bool get() override; };

		property virtual bool CanWrite { bool get() override; };

		property virtual long long Length { long long get() override; };

		property virtual long long Position
		{
			long long get() override;
			void set(long long value) override;
		};

		virtual void Flush() override;

		virtual int Read(array<System::Byte>^ buffer, int offset, int count) override;

		virtual long long Seek(long long offset, System::IO::SeekOrigin origin) override;

		virtual void SetLength(long long value) override;

		virtual void Write(array<System::Byte>^ buffer, int offset, int count) override;

	};
	*/
}
