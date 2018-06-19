#pragma once

using namespace System::Threading;

namespace CLI
{
	generic <class T>
	public ref class LateValue
	{
	private:
		ManualResetEvent^ m_EventHandle;
		System::Exception^ m_Exception = nullptr;
		T m_Value;

	public:
		LateValue();

	public:
		void SetValue(T value);

		void SetError(System::Exception^ ex);

		T AwaitValue();

		T AwaitValue(int millisecondsTimeout);
	};
}