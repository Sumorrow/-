//update log-2024-04-20
//CODER:Tomorrow Samuel(Somorrow)202230442395，计科一班_数据结构大作业


#pragma once
#include "Goddess.h";

void writeToINI(const std::string& filename, const std::string& content, std::string X);
bool check_Elem(std::string tempstr);
void parseAndWriteToINI(std::string host, const std::string& filename, pugi::xml_node articleElement);
void article_read();
void author_read();