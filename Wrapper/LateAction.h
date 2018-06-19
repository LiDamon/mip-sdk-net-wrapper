#pragma once

using namespace System::Threading;

namespace NetMip
{
	public ref class LateAction
	{
	private:
		ManualResetEvent ^ m_EventHandle;
		System::Exception^ m_Exception = nullptr;

	public:
		LateAction();

	public:
		void Complete();

		void SetError(System::Exception^ ex);

		void Await();

		void Await(int millisecondsTimeout);
	};
}