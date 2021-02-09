#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <string>
#include <fstream>

class Log
{
public:
	enum class MessageType : unsigned short {

		TYPE_NONE,
		TYPE_FATAL_ERROR,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_TRACE,
		TYPE_INFO
	};
	
	Log() = delete;
	Log(const Log&) = delete;
	Log(Log&&) = delete;
	Log& operator=(const Log&) = delete;
	Log& operator=(const Log&&) = delete;

	static void OnCreate(const std::string& name_ = "KandyEngineLog");
	static void SetSeverity(MessageType type_);
	static void Info(const std::string& message_, const std::string& fileName_,
		const int line_);
	static void Trace(const std::string& message_, const std::string& fileName_,
		const int line_);
	static void Warning(const std::string& message_, const std::string& fileName_,
		const int line_);
	static void Error(const std::string& message_, const std::string& fileName_,
		const int line_);
	static void FatalError(const std::string& message_, const std::string& fileName_,
		const int line_);
private:
	static void log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_);
	static MessageType currentSev;
	static std::string outputName;
};
#endif // !LOG_H
