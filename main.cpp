#include <iostream>
#include <vector>
#include "Editor.h"
#include "Commands.h"
#include "Message.h"

int main()
{
	Message message = ReadFromFileMessage("text.txt");
	WorkWithRecipe("Recipe.txt", message);
	std::map<int, std::string> output = message.Output();
	for (std::map<int, std::string>::iterator i = output.begin(); i != output.end(); ++i)
	{
		std::cout << i->first << " " << i->second << std::endl;
	}
	return 0;
}