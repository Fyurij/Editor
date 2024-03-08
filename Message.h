#pragma once
#include <optional>
#include <map>
#include <string>
#include "Commands.h"
#include "Editor.h"

class Message
{
private:
	std::map<int, std::string> text;
public:
	void Add(int num, std::string& message);
	void Delete(std::optional<int> numStart, std::optional<int> numFinish);
	void Change(std::optional<int> numStart, std::optional<int> numFinish, std::string& text);
	void Insert(std::map<int, std::string>& mapToWrite, int num);
	void Replace(std::optional<int> numStart, std::optional<int> numFinish, std::string& textToFind, std::string& textToWrite);
	const std::map<int, std::string>& Output();
	void Undo();
};