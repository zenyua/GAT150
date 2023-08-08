#pragma once
#include <string>
#include <cassert>
#include <fstream>

#ifdef _DEBUG
#define INFO_LOG(message) {if(ringo::g_logger.Log(ringo::LogLevel::Info, __FILE__, __LINE__)) { ringo::g_logger << message << "\n"; } };
#define WARNING_LOG(message) {if(ringo::g_logger.Log(ringo::LogLevel::Warning, __FILE__, __LINE__)) { ringo::g_logger << message << "\n"; }};
#define ERROR_LOG(message) {if(ringo::g_logger.Log(ringo::LogLevel::Error, __FILE__, __LINE__)) { ringo::g_logger << message << "\n"; }};
//slashes allow the #define to span multiple lines
#define ASSERT_LOG(condition, message) {\
if(!condition && ringo::g_logger.Log(ringo::LogLevel::Assert, __FILE__, __LINE__)) { ringo::g_logger << message << "\n"; } assert(condition); \
};
#else
#define INFO_LOG(message {})
#define WARNING_LOG(message {})
#define ERROR_LOG(message {})
#define ASSERT_LOG(condition, message {})
#endif //_DEBUG

namespace ringo {
	enum LogLevel {
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger {
	public:
		Logger(LogLevel logLevel, std::ostream* ostream, const std::string& filename = "") :
			m_ostream{ ostream },
			m_logLevel {logLevel}
		{
			if(!filename.empty()) m_fstream.open(filename);
		}

		bool Log(LogLevel logLevel, const std::string& filename, int line);

		template<typename T>
		Logger& operator << (T value);

	private:
		LogLevel m_logLevel;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;
	};

	extern Logger g_logger;

	template<typename T>
	inline Logger& Logger::operator<<(T value)
	{
		if(m_ostream) *m_ostream << value;
		if (m_fstream.is_open()) {
			m_fstream << value;
			m_fstream.flush();
		}

		return *this;
	}
}