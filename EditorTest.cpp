#include <gtest/gtest.h>
#include "Editor.h"
#include "Message.h"

TEST(MessageTest, DeleteTest)
{
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	std::optional<int> start = 2;
	std::optional<int> finish = 4;
	message.Delete(start, finish);
	std::map<int, std::string> expectedMap{ {0, temp0}, {1, temp1}, {2, temp5}, {3, temp6} };
	EXPECT_EQ(message.Output(), expectedMap);
}

TEST(MessageTest, DeleteTestFrom)
{
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	std::optional<int> start = 2;
	std::optional<int> finish;
	message.Delete(start, finish);
	std::map<int, std::string> expectedMap{ {0, temp0}, {1, temp1} };
	EXPECT_EQ(message.Output(), expectedMap);
}

TEST(MessageTest, DeleteTestTo)
{
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	std::optional<int> start;
	std::optional<int> finish = 4;
	message.Delete(start, finish);
	std::map<int, std::string> expectedMap{ {0, temp5}, {1, temp6} };
	EXPECT_EQ(message.Output(), expectedMap);
}

TEST(MessageTest, DeleteTestFromOutOfRange)
{
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	std::optional<int> start = -3;
	std::optional<int> finish = 1;
	message.Delete(start, finish);
	std::map<int, std::string> expectedMap{ {0, temp2}, {1, temp3}, {2, temp4}, {3, temp5}, {4, temp6} };
	EXPECT_EQ(message.Output(), expectedMap);
}

TEST(MessageTest, DeleteTestToOutOfRange)
{
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	std::optional<int> start = 5;
	std::optional<int> finish = 10;
	message.Delete(start, finish);
	std::map<int, std::string> expectedMap{ {0, temp0}, {1, temp1}, {2, temp2}, {3, temp3}, {4, temp4} };
	EXPECT_EQ(message.Output(), expectedMap);
}



TEST(FromTextToMap, Default)
{
	std::string message = "Hello\\nWorld\\nHow are You?";
	std::map<int, std::string> expectedMap{ {2, "Hello"}, {3, "World"}, {4, "How are You?"} };
	std::map<int, std::string> Map = FromTextToMap(message, 2);
	EXPECT_EQ(expectedMap, Map);
}

TEST(FromTextToMap, OneStroke)
{
	std::string message = "Hello World How are You?";
	std::map<int, std::string> expectedMap{ {2, "Hello World How are You?"}};
	std::map<int, std::string> Map = FromTextToMap(message, 2);
	EXPECT_EQ(expectedMap, Map);
}



TEST(ChangeTest, ChangeAll)
{
	std::optional<int> start;
	std::optional<int> finish;
	std::string text = "Changed message";
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	message.Change(start, finish, text);
	std::map<int, std::string> expectedMap{ {0, text} };
	EXPECT_EQ(message.Output(), expectedMap);
}

TEST(ChangeTest, DeleteMoreThanAdd)
{
	std::optional<int> start = 2;
	std::optional<int> finish = 4;
	std::string text = "Changed message";
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	message.Change(start, finish, text);
	std::map<int, std::string> expectedMap{ {0, temp0}, {1, temp1},  {2, text}, {3, temp5}, {4, temp6} };
	EXPECT_EQ(message.Output(), expectedMap);
}

TEST(ChangeTest, DeleteLessThanAdd)
{
	std::optional<int> start = 2;
	std::optional<int> finish = 3;
	std::string text = "Changed message\\nChanged message\\nChanged message\\nChanged message";
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	message.Change(start, finish, text);
	std::map<int, std::string> expectedMap{ {0, temp0}, {1, temp1},  {2, "Changed message"}, {3, "Changed message"}, {4, "Changed message"}, {5, "Changed message"}, {6, temp4}, {7, temp5}, {8, temp6} };
	EXPECT_EQ(message.Output(), expectedMap);
}

TEST(ChangeTest, DeleteSimilarWithAdded)
{
	std::optional<int> start = 2;
	std::optional<int> finish = 3;
	std::string text = "Changed message\\nChanged message";
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	message.Change(start, finish, text);
	std::map<int, std::string> expectedMap{ {0, temp0}, {1, temp1},  {2, "Changed message"}, {3, "Changed message"}, {4, temp4}, {5, temp5}, {6, temp6} };
	EXPECT_EQ(message.Output(), expectedMap);
}



TEST(ReplaceTest, FindWhatToReplace)
{
	std::optional<int> start;
	std::optional<int> finish;
	std::string text = "REPLACED MESSAGE";
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	std::string messageToFind = "what";
	message.Replace(start, finish, messageToFind, text);
	std::map<int, std::string> expectedMap{ {0, temp0}, {1, temp1},  {2, temp2}, {3, temp3}, {4, "REPLACED MESSAGE to do"}, {5, temp5}, {6, temp6}};
	EXPECT_EQ(message.Output(), expectedMap);
}

TEST(ReplaceTest, NotFindWhatToReplace)
{
	std::optional<int> start;
	std::optional<int> finish;
	std::string text = "REPLACED MESSAGE";
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	std::string messageToFind = "goodbye";
	message.Replace(start, finish, messageToFind, text);
	std::map<int, std::string> expectedMap{ {0, temp0}, {1, temp1},  {2, temp2}, {3, temp3}, {4, temp4}, {5, temp5}, {6, temp6} };
	EXPECT_EQ(message.Output(), expectedMap);
}

TEST(ReplaceTest, OutOfBordersToFind)
{
	std::optional<int> start = 2;
	std::optional<int> finish = 3;
	std::string text = "REPLACED MESSAGE";
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	std::string messageToFind = "what";
	message.Replace(start, finish, messageToFind, text);
	std::map<int, std::string> expectedMap{ {0, temp0}, {1, temp1},  {2, temp2}, {3, temp3}, {4, temp4}, {5, temp5}, {6, temp6} };
	EXPECT_EQ(message.Output(), expectedMap);
}



TEST(InsertTest, InBegining)
{
	int start = -1;
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	std::string text = "INSERTED MESSAGE";
	std::map<int, std::string> inserted{ {0, text}, {1, text}, {2, text} };
	message.Insert(inserted, start);
	std::map<int, std::string> expectedMap{ {0, text}, {1, text},  {2, text}, {3, temp0}, {4, temp1}, {5, temp2}, {6, temp3}, {7, temp4}, {8, temp5}, {9, temp6} };
	EXPECT_EQ(message.Output(), expectedMap);
}

TEST(InsertTest, Default)
{
	int start = 0;
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	std::string text = "INSERTED MESSAGE";
	std::map<int, std::string> inserted{ {1, text}, {2, text}, {3, text} };
	message.Insert(inserted, start);
	std::map<int, std::string> expectedMap{ {0, temp0}, {1, text},  {2, text}, {3, text}, {4, temp1}, {5, temp2}, {6, temp3}, {7, temp4}, {8, temp5}, {9, temp6} };
	EXPECT_EQ(message.Output(), expectedMap);
}

TEST(InsertTest, InEnd)
{
	int start = 6;
	Message message;
	std::string temp0 = "Hello World";
	message.Add(0, temp0);
	std::string temp1 = "How are you?";
	message.Add(1, temp1);
	std::string temp2 = "I am fine";
	message.Add(2, temp2);
	std::string temp3 = "Just go away...";
	message.Add(3, temp3);
	std::string temp4 = "what to do";
	message.Add(4, temp4);
	std::string temp5 = "I need to go";
	message.Add(5, temp5);
	std::string temp6 = "Far away";
	message.Add(6, temp6);
	std::string text = "INSERTED MESSAGE";
	std::map<int, std::string> inserted{ {7, text}, {8, text}, {9, text} };
	message.Insert(inserted, start);
	std::map<int, std::string> expectedMap{ {0, temp0}, {1, temp1},  {2, temp2}, {3, temp3}, {4, temp4}, {5, temp5}, {6, temp6}, {7, text}, {8, text}, {9, text} };
	EXPECT_EQ(message.Output(), expectedMap);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}