#include "basic_search.h"


// 根据偏移量读取文章内容
void readArticle(const char* filename, size_t offset) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // 定位文件指针到指定的偏移量位置
    file.seekg(offset);

    std::string line;
    while (std::getline(file, line)) {
        // 如果遇到 "</article>" 结束标签，则停止读取
        if (line.find("</article>") != std::string::npos) {
            break;
        }
        // 输出当前行内容，也可以根据需要进行其他处理
        std::cout << line << std::endl;
    }

    file.close();
}

// 实现功能
void article_find() {
    std::string title;
    std::cout << "请输入文章的全名：" << std::endl;
    std::getline(std::cin, title);

    // 计算标题的哈希值
    uint32_t hashValue = fnv1a(title);
    uint32_t hashKey = hashValue % HASH_KEY; // 计算哈希值对应的哈希桶编号
    std::string str = std::to_string(hashKey);
    std::string fullname = ARTICLEFILE + str + ".ini";
    std::ifstream file(fullname);
    if (!file.is_open()) {
        std::cerr << "文件打开错误!" << std::endl;
        return;
    }

    std::string line;
    bool found = false;

    // 根据偏移量寻找 XML 文件中的文章内容
    while (std::getline(file, line)) {
        // 删除行首和行尾的空格
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        // 检查行是否以目标标题开头
        if (line.find(title) == 0) {
            found = true;
            // 输出匹配的标题
            //std::cout << "Match found: " << line << std::endl;

            // 从匹配行中提取偏移量
            std::istringstream iss(line.substr(title.length()));
            // 假设你已经得到了字节偏移量
            size_t byteOffset;
            iss >> byteOffset;

            readArticle(FILEE, byteOffset);
            break;
        }
    }

    if (!found) {
        std::cerr << "找不到匹配的文章。" << std::endl;
    }

    file.close();
}


/*void article_find() {
    std::string title;
    std::cout << "请输入文章的全名：" << std::endl;
    std::cin >> title;

    // 计算标题的哈希值
    uint32_t hashValue = fnv1a(title);
    uint32_t hashKey = hashValue % HASH_KEY; // 计算哈希值对应的哈希桶编号
    std::string str = std::to_string(hashKey);
    std::string fullname = ARTICLEFILE + str + ".ini";
    std::ifstream file(fullname);
    if (!file.is_open()) {
        std::cerr << "文件打开错误!" << std::endl;
        return;
    }

    std::string line;
    bool found = false;

    // 根据标题在索引文件中查找偏移量
    while (std::getline(file, line)) {
        // 检查行是否以目标标题开头
        if (line.find(title) == 0) {
            found = true;
            // 输出匹配的标题
            std::cout << "Match found: " << line << std::endl;

            // 从匹配行中提取偏移量
            size_t pos = line.find("\t"); // 假设标题和偏移量之间用制表符分隔
            if (pos != std::string::npos) {
                std::string offsetStr = line.substr(pos + 1);
                std::istringstream iss(offsetStr);
                size_t byteOffset;
                if (iss >> byteOffset) {
                    // 读取文章内容
                    readArticle(FILEE, byteOffset);
                }
                else {
                    std::cerr << "无法解析偏移量。" << std::endl;
                }
            }
            else {
                std::cerr << "找不到偏移量。" << std::endl;
            }
            break;
        }
    }

    if (!found) {
        std::cerr << "找不到匹配的文章。" << std::endl;
    }

    file.close();
}
*/


void author_findARTICLETITLE() {
        std::string stri;
        std::cout << "请输入作者名来查找他的作品：" << std::endl;
        while (std::getline(std::cin, stri)) {
            uint32_t hashValue = fnv1a(stri);
            uint32_t hashKey = hashValue % HASH_KEY; // 计算哈希值对应的哈希桶编号
            std::string str = std::to_string(hashKey);
            std::string filename = AUTHORFILE + str + ".ini";

            std::ifstream file(filename); // 打开 ini 文件
            if (!file.is_open()) {
                std::cerr << "无法打开文件: " << filename << std::endl;
                return;
            }
            
            std::string line;
            while (std::getline(file, line)) { // 逐行读取文件内容

                size_t dollarPos = line.find("$"); // 查找$字符
                if (dollarPos != std::string::npos) { 
                    // 如果找到了$
                    // 查找第一个$字符前的字符串
                    std::string beforeDollar = line.substr(0, dollarPos);
                    // 如果找到了$，并且获取了$字符之前的字符串
                    if (beforeDollar == stri) { // 如果找到的字符串等于 stri
                        size_t pos = line.find("￥"); // 查找￥字符
                        if (pos != std::string::npos) { // 如果找到了￥字符
                            std::string afterYuan = line.substr(pos + 1); 
                            // 获取￥字符后面的字符串
                            // 清除 afterYuan 中的换行符和回车符
                            afterYuan.erase(std::remove_if(afterYuan.begin(), afterYuan.end(), [](unsigned char c) { return !std::isprint(c); }), afterYuan.end());
                            std::cout << afterYuan << std::endl;
                        }
                    }
                }
                 
            }
           file.close(); // 关闭文件
        }
        return;
    }

/*
void author_findCOOPERATOR() {
    std::string stri;
    std::cout << "请输入作者名查找往届合作对象：" << std::endl;
    while (std::getline(std::cin, stri)) {
        uint32_t hashValue = fnv1a(stri);
        uint32_t hashKey = hashValue % HASH_KEY; // 计算哈希值对应的哈希桶编号
        std::string str = std::to_string(hashKey);
        std::string filename = AUTHORFILE + str + ".ini";

        std::ifstream file(filename); // 打开 ini 文件
        if (!file.is_open()) {
            std::cerr << "无法打开文件: " << filename << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line)) { // 逐行读取文件内容
            size_t pos = 0;
            while ((pos = line.find("$", pos)) != std::string::npos) { // 查找$字符
                size_t dollarPos = line.find("$"); // 查找$字符
                if (dollarPos != std::string::npos) { // 如果找到了$
                    // 查找第一个$字符前的字符串
                    std::string beforeDollar = line.substr(0, dollarPos);
                    // 如果找到了$，并且获取了$字符之前的字符串}
                    if (beforeDollar == stri) { 
                        // 如果找到的字符串等于 stri}
                        // 如果找到了$，输出$字符后面的内容，直到遇到下一个$
                        size_t nextPos = line.find("$", pos + 1); // 查找下一个$
                        if (nextPos == std::string::npos) { // 如果没有找到下一个$
                            size_t nexttPos = line.find("￥", pos + 1);
                            std::string afterDollar = line.substr(pos + 1, nexttPos - pos - 1); // 获取$后面的内容
                            std::cout << afterDollar << std::endl; // 输出$后面的内容
                            break; // 退出循环
                        }
                        else {
                            std::string afterDollar = line.substr(pos + 1, nextPos - pos - 1); // 获取$后面的内容
                            std::cout << afterDollar << std::endl; // 输出$后面的内容
                            pos = nextPos; // 更新位置为下一个$
                        }

                    }
                }
            }
             
        }
        file.close(); // 关闭文件
    }
return;
}

*/

void author_findCOOPERATOR() {
    std::string stri;
    std::cout << "请输入作者名查找往届合作对象：" << std::endl;

    std::vector<std::string> afterDollarArray; // 用于存储 afterDollar 字符串的数组

    while (std::getline(std::cin, stri)) {
        uint32_t hashValue = fnv1a(stri);
        uint32_t hashKey = hashValue % HASH_KEY; // 计算哈希值对应的哈希桶编号
        std::string str = std::to_string(hashKey);
        std::string filename = AUTHORFILE + str + ".ini";

        std::ifstream file(filename); // 打开 ini 文件
        if (!file.is_open()) {
            std::cerr << "无法打开文件: " << filename << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line)) { // 逐行读取文件内容
            size_t pos = 0;
            while ((pos = line.find("$", pos)) != std::string::npos) { // 查找$字符
                size_t dollarPos = line.find("$"); // 查找$字符
                if (dollarPos != std::string::npos) { // 如果找到了$
                    // 查找第一个$字符前的字符串
                    std::string beforeDollar = line.substr(0, dollarPos);
                    // 如果找到了$，并且获取了$字符之前的字符串}
                    if (beforeDollar == stri) {
                        // 如果找到的字符串等于 stri}
                        // 如果找到了$，输出$字符后面的内容，直到遇到下一个$
                        size_t nextPos = line.find("$", pos + 1); // 查找下一个$
                        if (nextPos == std::string::npos) { // 如果没有找到下一个$
                            size_t nexttPos = line.find("￥", pos + 1);
                            std::string afterDollar = line.substr(pos + 1, nexttPos - pos - 1); // 获取$后面的内容

                            // 在插入之前检查是否已经存在于数组中
                            bool found = false;
                            for (const std::string& str : afterDollarArray) {
                                if (str == afterDollar) {
                                    found = true;
                                    break;
                                }
                            }
                            if (!found) {
                                afterDollarArray.push_back(afterDollar);
                                std::cout << afterDollar << std::endl; // 输出$后面的内容
                            }
                            break; // 退出循环
                        }
                        else {
                            std::string afterDollar = line.substr(pos + 1, nextPos - pos - 1); // 获取$后面的内容

                            // 在插入之前检查是否已经存在于数组中
                            bool found = false;
                            for (const std::string& str : afterDollarArray) {
                                if (str == afterDollar) {
                                    found = true;
                                    break;
                                }
                            }
                            if (!found) {
                                afterDollarArray.push_back(afterDollar);
                                std::cout << afterDollar << std::endl; // 输出$后面的内容
                            }

                            pos = nextPos; // 更新位置为下一个$
                        }

                    }
                }
            }

        }
        file.close(); // 关闭文件
    }

    return;
}







//int main() {
//
//    article_find();
//    //author_findARTICLETITLE();
//    //author_findCOOPERATOR();
//    return 0;
//}