#ifndef PIPELINE_H__
#define PIPELINE_H__

#include <string>
#include <vector>
#include <map>
#include "PipeFile.h"

class CommandItem
{
public:
	std::string name_;
	std::string cmdLine_;
};

class Procedure
{
public:
	std::string Name() const { return name_; }
	std::string Pos() const { return pos_; }
	std::vector<CommandItem> GetCommandLines() const { return commandLines_; }

	void SetName(const std::string& name) { name_ = name; }
	bool AppendCommand(const std::string& line);
	bool AppendCommand(const std::string& cmd, const std::vector<std::string>& arguments);
private:
	std::string name_;
	std::vector<CommandItem> commandLines_;
	std::string pos_; // format as "filename(line-no)"
};

class Pipeline
{
public:
	static bool CheckIfPipeFile(const std::string& command);

	bool Load(const std::string& filename);
	bool Save(const std::string& filename) const;

	bool AppendCommand(const std::string& cmd, const std::vector<std::string>& arguments);
	std::string JoinCommandLine(const std::string& cmd, const std::vector<std::string>& arguments);

	std::vector<CommandItem> GetCommandLines() const { return defaultProc_.GetCommandLines(); }
	std::vector<std::string> GetProcNameList() const;
	const Procedure& GetDefaultProc() const { return defaultProc_; }

	const Procedure* GetProc(const std::string& name) const;
private:
	bool LoadConf(const std::string& filename, std::map<std::string, std::string>& confMap);
	bool LoadProc(PipeFile& file, const std::string& name, std::string leftBracket, Procedure& proc);
private:
	std::map<std::string, Procedure> procList_;
	Procedure defaultProc_;
};

#endif
