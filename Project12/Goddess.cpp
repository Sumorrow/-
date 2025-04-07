#include"Goddess.h"


uint32_t fnv1a(const std::string& str) {
    uint32_t hash = 2166136261u; // FNV偏移基准值
    const uint32_t prime = 16777619u; // FNV素数

    for (char c : str) {
        hash ^= static_cast<uint32_t>(c); // 异或当前字符
        hash *= prime; // 乘以素数
    }

    return hash;
}//得到字符串的FNV1a哈希值

bool isContentExist(const std::string& filename, const std::string& content) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == content) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}