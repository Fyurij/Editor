#pragma once
#include <optional>
#include <map>
#include <string>

class Message
{
private:
	std::map<int, std::string> text;
public:
	void Add(int num, std::string& message);
	void Delete(std::optional<int> numStart, std::optional<int> numFinish);
	std::map<int, std::string> Change(std::optional<int> numStart, std::optional<int> numFinish, std::string& text);
	std::map<int, std::string> Insert(std::map<int, std::string>& mapToWrite, int num);
	std::map<int, std::string> Replace(std::optional<int> numStart, std::optional<int> numFinish, std::string& textToFind, std::string& textToWrite);
	const std::map<int, std::string>& Output();
	void Undo();
};
std::map<int, std::string> FromTextToMap(std::string& message, int numStart);