#pragma once

namespace CLI
{
	generic <typename  TFirst, typename TSecond>
	public ref class Pair sealed
	{
	private:
		TFirst m_first;
		TSecond m_second;

	public:
		Pair(TFirst first, TSecond second)
			: m_first(first),
			m_second(second)
		{
		}

		property TFirst First
		{
			TFirst get() { return m_first; }
			void set(TFirst value) { m_first = value; }
		}

		property TSecond Second
		{
			TSecond get() { return m_second; }
			void set(TSecond value) { m_second = value; }
		}
	};
}