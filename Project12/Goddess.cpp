#include"Goddess.h"


uint32_t fnv1a(const std::string& str) {
    uint32_t hash = 2166136261u; // FNVƫ�ƻ�׼ֵ
    const uint32_t prime = 16777619u; // FNV����

    for (char c : str) {
        hash ^= static_cast<uint32_t>(c); // ���ǰ�ַ�
        hash *= prime; // ��������
    }

    return hash;
}//�õ��ַ�����FNV1a��ϣֵ

bool isContentExist(const std::string& filename, const std::string& content) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�" << std::endl;
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