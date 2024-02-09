//InputTypeBase.h

#pragma once
#include "InputTypeBase.h"
#include "SurvivantCore/TupleHasher.h"

#include <functional>
#include <tuple>

namespace App
{
	template<typename ...Args>
	class InputType : public InputTypeBase
	{
	public:
		typedef void (*InputFuncPtr)(Args&...);

	public:
		class InputCallback
		{
		public:
			typedef std::function<void(Args&...)> InputDelegate;

		public:
			InputCallback() = default;
			~InputCallback() = default;

			void Invoke(InputType<Args...> p_type);
		private:
			InputDelegate m_delegate;
		};

	public:
		InputType(const Args&... p_inputInfo);
		~InputType() = default;

	public:
		void temp() override { return; }

	public:
		bool operator==(const InputType<Args...>& other) const;

	public:
		std::tuple<Args...> m_inputInfo;
	};

	
	template<typename ...Args>
	struct std::hash<App::InputType<Args...>>
	{
		std::size_t operator()(const App::InputType<Args...>& p_this) const
		{
			p_this;
			hash_tuple hasher;
			return hasher(p_this.m_inputInfo);
		}
	};


	template<typename ...Args>
	InputType<Args...>::InputType(const Args & ...p_inputInfo) : m_inputInfo(p_inputInfo...)
	{
	}

	template<typename ...Args>
	bool InputType<Args...>::operator==(const InputType<Args...>& other) const
	{
		return this->m_inputInfo == other.m_inputInfo;
	}

	template<typename ...Args>
	void InputType<Args...>::InputCallback::Invoke(InputType<Args...> p_type)
	{
		std::apply(m_delegate, p_type.m_inputInfo);
	}
}


