#pragma once
#include <map>
#include <optional>
#include <string>
#include "Message.h"

class ICommand
{
public:
	virtual void execute(Message& message) = 0;
	virtual ~ICommand() = default;
	virtual void undo(Message& message) = 0;
};

class DeleteCommand : public ICommand
{
private:
	std::optional<int> numStart;
	std::optional<int> numFinish;
	Message previousMessage;
public:
	DeleteCommand(const std::string& text, int finish);
	void execute(Message& message);
	void undo(Message& message);
};

class ChangeCommand : public ICommand
{
private:
	std::optional<int> numStart;
	std::optional<int> numFinish;
	std::string textToWrite;
	std::map<int, std::string> previousText;
public:
	ChangeCommand(const std::string& text, int finish);
	void execute(Message& message);
	void undo(Message& message);
};

class InsertCommand : public ICommand
{
private:
	int num;
	std::map<int, std::string> mapToWrite;
	std::map<int, std::string> previousText;
public:
	InsertCommand(const std::string& text);
	void execute(Message& message);
	void undo(Message& message);
};

class ReplaceCommand : public ICommand
{
private:
	std::optional<int> numStart;
	std::optional<int> numFinish;
	std::string textToFind;
	std::string textToWrite;
	std::map<int, std::string> previousText;
public:
	ReplaceCommand(const std::string& text);
	void execute(Message& message);
	void undo(Message& message);
};

class UndoCommand : public ICommand
{
private:
	ICommand* previousCommand;
public:
	UndoCommand(ICommand* previousCommand_)
		:previousCommand(previousCommand_)
	{}
	void execute(Message& message);
	void undo(Message& message);
};