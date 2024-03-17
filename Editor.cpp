#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <map>
#include <optional>
#include <vector>
#include <memory>
#include "Editor.h"
#include "Commands.h"
#include "Message.h"

int FindNumber(const std::string& text, int& pos)
{
	int finish = text.find(' ', pos);
	pos = finish + 1;
	finish = text.find(' ', pos);
	std::string temp = text.substr(pos, finish - pos);
	int numStart = std::stoi(temp);
	return numStart;
}

void WorkWithCommands(std::vector<std::unique_ptr<ICommand>>& commands, Message& message)
{
	for (int i = 0; i < commands.size(); ++i)
	{
		commands[i]->execute(message);
	}
}

void WorkWithRecipe(const std::string& name, Message& message)
{
	std::ifstream File(name);
	if (!File.is_open())
	{
		throw std::runtime_error("Can't open file");
	}
	std::string text;
	std::vector<std::unique_ptr<ICommand>> commands;
	while (std::getline(File, text))
	{
		int pos = 0;
		int finish = text.find(' ');
		std::string command = text.substr(pos, finish);
		if (command == "delete")
		{
			auto deleteCommand = std::make_unique<DeleteCommand>(text, finish); //std::unique_ptr<ICommand> deleteCommand(new DeleteCommand(text, finish));
			commands.push_back(std::move(deleteCommand));
		}
		else if (command == "change")
		{
			std::unique_ptr<ICommand> changeCommand(new ChangeCommand(text, finish));
			commands.push_back(std::move(changeCommand));
		}
		else if (command == "insert")
		{
			std::unique_ptr<ICommand> insertCommand(new InsertCommand(text));
			commands.push_back(std::move(insertCommand));
		}
		else if (command == "replace")
		{
			std::unique_ptr<ICommand> replaceCommand(new ReplaceCommand(text));
			commands.push_back(std::move(replaceCommand));
		}
		else if (command == "undo")
		{
			std::unique_ptr<ICommand> undoCommand(new UndoCommand(commands.back().get())); // ...commands[commands.size() - 1].get()
			commands.push_back(std::move(undoCommand));
		}
		else
		{
			throw std::invalid_argument("Unknown command");
		}
	}
	WorkWithCommands(commands, message);
}

Message ReadFromFileMessage(const std::string& name)
{
	std::ifstream File(name);
	if (!File.is_open())
	{
		throw std::runtime_error("Can't open file");
	}
	std::string message;
	int num = 0;
	Message text;
	while (std::getline(File,message))
	{
		text.Add(num, message);
		++num;
	}
	return text;
}