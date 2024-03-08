#include <string>
#include "Editor.h"

DeleteCommand::DeleteCommand(const std::string& text, int finish)
{
	if (finish != std::string::npos)
	{
		int pos = text.find("from");
		if (pos != std::string::npos)
		{
			numStart = FindNumber(text, pos);
		}
		pos = text.find('to', pos);
		if (pos != std::string::npos)
		{
			numFinish = FindNumber(text, pos);
		}
	}
}

void DeleteCommand::execute(Message& message)
{
	message.Delete(numStart, numFinish);
}

ChangeCommand::ChangeCommand(const std::string& text, int finish)
{
	if (finish != std::string::npos)
	{
		int pos = text.find("from");
		if (pos != std::string::npos)
		{
			numStart = FindNumber(text, pos);
		}
		pos = text.find('to', pos);
		if (pos != std::string::npos)
		{
			numFinish = FindNumber(text, pos);
		}
		pos = text.find('"') + 1;
		finish = text.find('"', pos);
		textToWrite = text.substr(pos, finish - pos);
	}
}

void ChangeCommand::execute(Message& message)
{
	message.Change(numStart, numFinish, textToWrite);
}

InsertCommand::InsertCommand(const std::string& text)
{
	int pos = text.find("after");
	pos = text.find(' ', pos) + 1;
	int finish = text.find(' ', pos);
	std::string temp = text.substr(pos, finish - pos);
	num = std::stoi(temp);
	pos = text.find('"') + 1;
	finish = text.find('"', pos);
	std::string textToWrite = text.substr(pos, finish - pos);
	std::map<int, std::string> mapToWrite = FromTextToMap(textToWrite, num + 1);
}

void InsertCommand::execute(Message& message)
{
	message.Insert(mapToWrite, num);
}

ReplaceCommand::ReplaceCommand(const std::string& text)
{
	int pos = text.find("from");
	if (pos != std::string::npos)
	{
		numStart = FindNumber(text, pos);
	}
	pos = text.find("to");
	if (pos != std::string::npos)
	{
		numFinish = FindNumber(text, pos);
	}
	pos = text.find('"');
	int finish = text.find('"', pos + 1);
	textToFind = text.substr(pos + 1, finish - pos - 1);
	pos = finish + 1;
	pos = text.find('"', pos);
	finish = text.find('"', pos + 1);
	textToWrite = text.substr(pos + 1, finish - pos - 1);
}

void ReplaceCommand::execute(Message& message)
{
	message.Replace(numStart, numFinish, textToFind, textToWrite);
}