#ifndef INCLUDED_PARAMETER_H
#define INCLUDED_PARAMETER_H

#include <string>

namespace enlighten {

	class ParameterBase 
	{
		std::string asString;
	public:
		ParameterBase(const std::string &_asString) 
			: asString(_asString) {}
		virtual ~ParameterBase() {}
		std::string AsString() { return asString; }
	};

	template <class ParameterType>
	class Parameter : public ParameterBase
	{
	public:
		virtual ~Parameter() {}
		Parameter(ParameterType _value, const std::string &asString)
			: ParameterBase(asString), value(_value)  {}

		ParameterType GetValue() const 
		{
			return value;
		}
	private:
		ParameterType value;
	};

} // namespace enlighten

#endif