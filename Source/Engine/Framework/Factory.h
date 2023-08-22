#pragma once
#include "Singleton.h"
#include "Core/Logger.h"
#include <memory>
#include <map>
#include <string>

#define CREATE_CLASS(classname) ringo::Factory::Instance().Create<ringo::classname>(#classname);
#define CREATE_CLASS_BASE(classbase, classname) ringo::Factory::Instance().Create<ringo::classbase>(classname);
#define INSTANTIATE(classbase, classname) ringo::Factory::Instance().Create<ringo::classbase>(classname);

namespace ringo {
	class CreatorBase {
	public:
		virtual ~CreatorBase() = default;

		virtual std::unique_ptr<class Object> Create() = 0;
	};

	template <typename T>
	class Creator : public CreatorBase {
	public:
		std::unique_ptr<class Object> Create() override {
			return std::make_unique<T>();
		}
	};

	template <typename T>
	class PrototypeCreator : public CreatorBase {
	public:
		PrototypeCreator(std::unique_ptr<T> prototype) : m_prototype{ std::move(prototype) } {}
		std::unique_ptr<class Object> Create() override {
			return m_prototype->Clone();
		}
	private:
		std::unique_ptr<T> m_prototype;
	};

	class Factory : public Singleton<Factory> {
	public:
		template<typename T>
		void Register(const std::string& key);

		template<typename T>
		void RegisterPrototype(const std::string& key, std::unique_ptr<T> prototype);

		template<typename T>
		std::unique_ptr<T> Create(const std::string& key);

		friend class Singleton;

	protected:
		Factory() = default;

	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;
	};

	template<typename T>
	inline void Factory::Register(const std::string& key)
	{
		INFO_LOG("Class registered: " << key);

		m_registry[key] = std::make_unique<Creator<T>>();
	}

	template<typename T>
	inline void Factory::RegisterPrototype(const std::string& key, std::unique_ptr<T> prototype)
	{
		INFO_LOG("Prototype Class registered " << key);

		m_registry[key] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
	}

	template<typename T>
	inline std::unique_ptr<T> Factory::Create(const std::string& key)
	{
		auto iter = m_registry.find(key);
		if (iter != m_registry.end()) {
			return std::unique_ptr<T>(dynamic_cast<T*>(iter->second->Create().release()));
		}

		return std::unique_ptr<T>();
	}
}