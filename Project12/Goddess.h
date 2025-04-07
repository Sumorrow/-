#pragma once
//update log-2024-04-20
//CODER:Tomorrow Samuel(Somorrow)202230442395，计科一班_数据结构大作业

#pragma once
#include"GOD.h"

extern const int KW;
extern const int HASH_KEY;
extern const char* FILEE;
extern const char* ARTICLEFILE;
extern const char* AUTHORFILE;
uint32_t fnv1a(const std::string& str);
bool isContentExist(const std::string& filename, const std::string& content);