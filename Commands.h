#pragma once
#include <map>
#include <optional>
#include <string>
#include "Editor.h"
#include "Message.h"

class ICommand
{
public:
	virtual void execute(Message& message) = 0;
	virtual ~ICommand() = default;
};

class DeleteCommand : public ICommand
{
private:
	std::optional<int> numStart;
	std::optional<int> numFinish;
public:
	DeleteCommand(const std::string& text, int finish);
	void execute(Message& message);
};

class ChangeCommand : public ICommand
{
private:
	std::optional<int> numStart;
	std::optional<int> numFinish;
	std::string textToWrite;
public:
	ChangeCommand(const std::string& text, int finish);
	void execute(Message& message);
};

class InsertCommand : public ICommand
{
private:
	int num;
	std::map<int, std::string> mapToWrite;
public:
	InsertCommand(const std::string& text);
	void execute(Message& message);
};

class ReplaceCommand : public ICommand
{
private:
	std::optional<int> numStart;
	std::optional<int> numFinish;
	std::string textToFind;
	std::string textToWrite;
public:
	ReplaceCommand(const std::string& text);
	void execute(Message& message);
};