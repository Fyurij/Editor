#include <string>
#include <map>
#include <optional>
#include <iterator>
#include "Message.h"

void Message::Add(int num, std::string& message)
{
	text[num] = message;
}

void Message::Delete(std::optional<int> numStart, std::optional<int> numFinish)
{
	int start = 0;
	int finish = text.size() - 1;
	if (numStart.has_value())
	{
		start = std::max(numStart.value(), start);
	}
	if (numFinish.has_value())
	{
		finish = std::min(numFinish.value(), finish);
	}
	int move = finish - start + 1;
	int left = text.size() - finish - 1;
	for (int i = start; i < start + left; ++i)
	{
		text[i] = text[i + move];
	}
	int temp = text.size();
	for (int i = temp - 1; i >= temp - move; --i)
	{
		text.erase(i);
	}
}

std::map<int, std::string> FromTextToMap(std::string& message, int numStart)
{
	std::map<int, std::string> mapToWrite;
	int pos = 0;
	int finish = message.find("\\n"); // \n
	int i = numStart;
	while (finish != std::string::npos)
	{
		if (finish >= 1 && message[finish - 1] != '\\')
		{
			mapToWrite[i] = message.substr(pos, finish - pos);
		}
		pos = finish + 2;	//pos = finish + 1;
		finish = message.find("\\n", pos); // \n
		++i;
	}
	mapToWrite[i] = message.substr(pos, finish - pos);
	return mapToWrite;
}

void Message::Insert(std::map<int, std::string>& mapToWrite, int num)
{
	int size = text.size();
	std::map<int, std::string> temp = text;
	for (int i = num + 1; i <= size - 1; ++i)
	{
		temp[i + mapToWrite.size()] = text[i];
	}
	size = mapToWrite.size();
	for (int i = 1; i <= size; ++i)
	{
		temp[i + num] = mapToWrite[i + num];
	}
	text = temp;
}

void Message::Change(std::optional<int> numStart, std::optional<int> numFinish, std::string& message)
{
	int start = 0;
	int finish = text.size();
	if (numStart.has_value())
	{
		start = std::max(numStart.value(), start);
	}
	if (numFinish.has_value())
	{
		finish = std::min(numFinish.value(), finish);
	}
	std::map<int, std::string> mapToWrite = FromTextToMap(message, start);
	int temp = mapToWrite.size();
	int min = std::min(temp, (finish - start + 1));
	for (int i = 0; i < min; ++i)
	{
		text[start + i] = mapToWrite[start + i];
	}
	if ((finish - start + 1) > mapToWrite.size())
	{
		Delete(start + mapToWrite.size(), finish);
	}
	if ((finish - start + 1) < mapToWrite.size())
	{
		std::map<int, std::string> tempMap;
		for (int i = min; i < mapToWrite.size(); ++i)
		{
			tempMap[start + i] = mapToWrite[start + i];
		}
		Insert(tempMap, start + min - 1);
	}
}

void Message::Replace(std::optional<int> numStart, std::optional<int> numFinish, std::string& textToFind, std::string& textToWrite)
{
	int start = 0;
	int finish = text.size();
	if (numStart.has_value())
	{
		start = numStart.value();
	}
	if (numFinish.has_value())
	{
		finish = numFinish.value();
	}
	std::map<int, std::string>::iterator startIter = text.begin();
	std::advance(startIter, start);
	std::map<int, std::string>::iterator endIter = text.begin();
	std::advance(endIter, finish);
	for (std::map<int, std::string>::iterator i = startIter; i != endIter; ++i)
	{
		int pos = i->second.find(textToFind);
		if (pos != std::string::npos)
		{
			int finish = pos + textToFind.size();
			i->second.erase(pos, textToFind.size());
			i->second.insert(pos, textToWrite);
		}
	}
}

const std::map<int, std::string>& Message::Output()
{
	return text;
}

void Message::Undo()
{

}