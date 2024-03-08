#pragma once
#include <optional>
#include <map>
#include <string>
#include "Commands.h"
#include "Message.h"

class Message;

int FindNumber(const std::string& text, int& pos);
void WorkWithRecipe(const std::string& name, Message& message);
Message ReadFromFileMessage(const std::string& name);
std::map<int, std::string> FromTextToMap(std::string& message, int numStart);