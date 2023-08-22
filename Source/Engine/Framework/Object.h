#pragma once
#include "Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DECLARATION(classname) \
	virtual const char* GetClassName() {return #classname;} \
	void Read(const json_t& value); \
	virtual std::unique_ptr<Object> Clone() {return std::make_unique<classname>(*this);} \
	class Register { \
	public: \
		Register() { \
			Factory::Instance().Register<classname>(#classname); \
		} \
	}; 

#define CLASS_DEFINITION(classname) \
	classname::Register register_class;

namespace ringo {
	class Object {
	public:
		Object() = default;
		Object(const std::string& name) : name{ name } {}
		virtual ~Object() { OnDestroy(); }

		CLASS_DECLARATION(Object)

		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}
		bool active = true;

	protected:
		std::string name = "";
	};
}
