#include "Log.h"

Log::MessageType Log::currentSev = MessageType::TYPE_NONE;
std::string Log::outputName = "";

void Log::OnCreate(const std::string& name_)
{
	outputName = name_ + ".txt";
	std::ofstream out;
	out.open(outputName.c_str(), std::ios::out);
	out.close();
	currentSev = MessageType::TYPE_INFO;

}

void Log::SetSeverity(MessageType type_)
{
	currentSev = type_;
}

void Log::Info(const std::string& message_, const std::string& fileName_, const int line_)
{
	log(MessageType::TYPE_INFO, "[INFO]: " + message_, fileName_, line_);
}

void Log::Trace(const std::string& message_, const std::string& fileName_, const int line_)
{
	log(MessageType::TYPE_TRACE, "[TRACE]: " + message_, fileName_, line_);

}

void Log::Warning(const std::string& message_, const std::string& fileName_, const int line_)
{
	log(MessageType::TYPE_WARNING, "[WARNING]: " + message_, fileName_, line_);

}

void Log::Error(const std::string& message_, const std::string& fileName_, const int line_)
{
	log(MessageType::TYPE_ERROR, "[ERROR]: " + message_, fileName_, line_);

}

void Log::FatalError(const std::string& message_, const std::string& fileName_, const int line_)
{
	log(MessageType::TYPE_FATAL_ERROR, "[FATAL ERROR]: " + message_, fileName_, line_);
}

void Log::log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_)
{
	if (type_ <= currentSev && currentSev > MessageType::TYPE_NONE) {
		std::ofstream out;
		out.open(outputName.c_str(), std::ios::app | std::ios::out);
		out << message_ << " in: " << fileName_ << " on line: " << line_ << std::endl;
		out.flush();
		out.close();
	
	}
}
