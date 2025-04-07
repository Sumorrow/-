#include "basic_search.h"


// ����ƫ������ȡ��������
void readArticle(const char* filename, size_t offset) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // ��λ�ļ�ָ�뵽ָ����ƫ����λ��
    file.seekg(offset);

    std::string line;
    while (std::getline(file, line)) {
        // ������� "</article>" ������ǩ����ֹͣ��ȡ
        if (line.find("</article>") != std::string::npos) {
            break;
        }
        // �����ǰ�����ݣ�Ҳ���Ը�����Ҫ������������
        std::cout << line << std::endl;
    }

    file.close();
}

// ʵ�ֹ���
void article_find() {
    std::string title;
    std::cout << "���������µ�ȫ����" << std::endl;
    std::getline(std::cin, title);

    // �������Ĺ�ϣֵ
    uint32_t hashValue = fnv1a(title);
    uint32_t hashKey = hashValue % HASH_KEY; // �����ϣֵ��Ӧ�Ĺ�ϣͰ���
    std::string str = std::to_string(hashKey);
    std::string fullname = ARTICLEFILE + str + ".ini";
    std::ifstream file(fullname);
    if (!file.is_open()) {
        std::cerr << "�ļ��򿪴���!" << std::endl;
        return;
    }

    std::string line;
    bool found = false;

    // ����ƫ����Ѱ�� XML �ļ��е���������
    while (std::getline(file, line)) {
        // ɾ�����׺���β�Ŀո�
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        // ������Ƿ���Ŀ����⿪ͷ
        if (line.find(title) == 0) {
            found = true;
            // ���ƥ��ı���
            //std::cout << "Match found: " << line << std::endl;

            // ��ƥ��������ȡƫ����
            std::istringstream iss(line.substr(title.length()));
            // �������Ѿ��õ����ֽ�ƫ����
            size_t byteOffset;
            iss >> byteOffset;

            readArticle(FILEE, byteOffset);
            break;
        }
    }

    if (!found) {
        std::cerr << "�Ҳ���ƥ������¡�" << std::endl;
    }

    file.close();
}


/*void article_find() {
    std::string title;
    std::cout << "���������µ�ȫ����" << std::endl;
    std::cin >> title;

    // �������Ĺ�ϣֵ
    uint32_t hashValue = fnv1a(title);
    uint32_t hashKey = hashValue % HASH_KEY; // �����ϣֵ��Ӧ�Ĺ�ϣͰ���
    std::string str = std::to_string(hashKey);
    std::string fullname = ARTICLEFILE + str + ".ini";
    std::ifstream file(fullname);
    if (!file.is_open()) {
        std::cerr << "�ļ��򿪴���!" << std::endl;
        return;
    }

    std::string line;
    bool found = false;

    // ���ݱ����������ļ��в���ƫ����
    while (std::getline(file, line)) {
        // ������Ƿ���Ŀ����⿪ͷ
        if (line.find(title) == 0) {
            found = true;
            // ���ƥ��ı���
            std::cout << "Match found: " << line << std::endl;

            // ��ƥ��������ȡƫ����
            size_t pos = line.find("\t"); // ��������ƫ����֮�����Ʊ���ָ�
            if (pos != std::string::npos) {
                std::string offsetStr = line.substr(pos + 1);
                std::istringstream iss(offsetStr);
                size_t byteOffset;
                if (iss >> byteOffset) {
                    // ��ȡ��������
                    readArticle(FILEE, byteOffset);
                }
                else {
                    std::cerr << "�޷�����ƫ������" << std::endl;
                }
            }
            else {
                std::cerr << "�Ҳ���ƫ������" << std::endl;
            }
            break;
        }
    }

    if (!found) {
        std::cerr << "�Ҳ���ƥ������¡�" << std::endl;
    }

    file.close();
}
*/


void author_findARTICLETITLE() {
        std::string stri;
        std::cout << "������������������������Ʒ��" << std::endl;
        while (std::getline(std::cin, stri)) {
            uint32_t hashValue = fnv1a(stri);
            uint32_t hashKey = hashValue % HASH_KEY; // �����ϣֵ��Ӧ�Ĺ�ϣͰ���
            std::string str = std::to_string(hashKey);
            std::string filename = AUTHORFILE + str + ".ini";

            std::ifstream file(filename); // �� ini �ļ�
            if (!file.is_open()) {
                std::cerr << "�޷����ļ�: " << filename << std::endl;
                return;
            }
            
            std::string line;
            while (std::getline(file, line)) { // ���ж�ȡ�ļ�����

                size_t dollarPos = line.find("$"); // ����$�ַ�
                if (dollarPos != std::string::npos) { 
                    // ����ҵ���$
                    // ���ҵ�һ��$�ַ�ǰ���ַ���
                    std::string beforeDollar = line.substr(0, dollarPos);
                    // ����ҵ���$�����һ�ȡ��$�ַ�֮ǰ���ַ���
                    if (beforeDollar == stri) { // ����ҵ����ַ������� stri
                        size_t pos = line.find("��"); // ���ң��ַ�
                        if (pos != std::string::npos) { // ����ҵ��ˣ��ַ�
                            std::string afterYuan = line.substr(pos + 1); 
                            // ��ȡ���ַ�������ַ���
                            // ��� afterYuan �еĻ��з��ͻس���
                            afterYuan.erase(std::remove_if(afterYuan.begin(), afterYuan.end(), [](unsigned char c) { return !std::isprint(c); }), afterYuan.end());
                            std::cout << afterYuan << std::endl;
                        }
                    }
                }
                 
            }
           file.close(); // �ر��ļ�
        }
        return;
    }

/*
void author_findCOOPERATOR() {
    std::string stri;
    std::cout << "���������������������������" << std::endl;
    while (std::getline(std::cin, stri)) {
        uint32_t hashValue = fnv1a(stri);
        uint32_t hashKey = hashValue % HASH_KEY; // �����ϣֵ��Ӧ�Ĺ�ϣͰ���
        std::string str = std::to_string(hashKey);
        std::string filename = AUTHORFILE + str + ".ini";

        std::ifstream file(filename); // �� ini �ļ�
        if (!file.is_open()) {
            std::cerr << "�޷����ļ�: " << filename << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line)) { // ���ж�ȡ�ļ�����
            size_t pos = 0;
            while ((pos = line.find("$", pos)) != std::string::npos) { // ����$�ַ�
                size_t dollarPos = line.find("$"); // ����$�ַ�
                if (dollarPos != std::string::npos) { // ����ҵ���$
                    // ���ҵ�һ��$�ַ�ǰ���ַ���
                    std::string beforeDollar = line.substr(0, dollarPos);
                    // ����ҵ���$�����һ�ȡ��$�ַ�֮ǰ���ַ���}
                    if (beforeDollar == stri) { 
                        // ����ҵ����ַ������� stri}
                        // ����ҵ���$�����$�ַ���������ݣ�ֱ��������һ��$
                        size_t nextPos = line.find("$", pos + 1); // ������һ��$
                        if (nextPos == std::string::npos) { // ���û���ҵ���һ��$
                            size_t nexttPos = line.find("��", pos + 1);
                            std::string afterDollar = line.substr(pos + 1, nexttPos - pos - 1); // ��ȡ$���������
                            std::cout << afterDollar << std::endl; // ���$���������
                            break; // �˳�ѭ��
                        }
                        else {
                            std::string afterDollar = line.substr(pos + 1, nextPos - pos - 1); // ��ȡ$���������
                            std::cout << afterDollar << std::endl; // ���$���������
                            pos = nextPos; // ����λ��Ϊ��һ��$
                        }

                    }
                }
            }
             
        }
        file.close(); // �ر��ļ�
    }
return;
}

*/

void author_findCOOPERATOR() {
    std::string stri;
    std::cout << "���������������������������" << std::endl;

    std::vector<std::string> afterDollarArray; // ���ڴ洢 afterDollar �ַ���������

    while (std::getline(std::cin, stri)) {
        uint32_t hashValue = fnv1a(stri);
        uint32_t hashKey = hashValue % HASH_KEY; // �����ϣֵ��Ӧ�Ĺ�ϣͰ���
        std::string str = std::to_string(hashKey);
        std::string filename = AUTHORFILE + str + ".ini";

        std::ifstream file(filename); // �� ini �ļ�
        if (!file.is_open()) {
            std::cerr << "�޷����ļ�: " << filename << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line)) { // ���ж�ȡ�ļ�����
            size_t pos = 0;
            while ((pos = line.find("$", pos)) != std::string::npos) { // ����$�ַ�
                size_t dollarPos = line.find("$"); // ����$�ַ�
                if (dollarPos != std::string::npos) { // ����ҵ���$
                    // ���ҵ�һ��$�ַ�ǰ���ַ���
                    std::string beforeDollar = line.substr(0, dollarPos);
                    // ����ҵ���$�����һ�ȡ��$�ַ�֮ǰ���ַ���}
                    if (beforeDollar == stri) {
                        // ����ҵ����ַ������� stri}
                        // ����ҵ���$�����$�ַ���������ݣ�ֱ��������һ��$
                        size_t nextPos = line.find("$", pos + 1); // ������һ��$
                        if (nextPos == std::string::npos) { // ���û���ҵ���һ��$
                            size_t nexttPos = line.find("��", pos + 1);
                            std::string afterDollar = line.substr(pos + 1, nexttPos - pos - 1); // ��ȡ$���������

                            // �ڲ���֮ǰ����Ƿ��Ѿ�������������
                            bool found = false;
                            for (const std::string& str : afterDollarArray) {
                                if (str == afterDollar) {
                                    found = true;
                                    break;
                                }
                            }
                            if (!found) {
                                afterDollarArray.push_back(afterDollar);
                                std::cout << afterDollar << std::endl; // ���$���������
                            }
                            break; // �˳�ѭ��
                        }
                        else {
                            std::string afterDollar = line.substr(pos + 1, nextPos - pos - 1); // ��ȡ$���������

                            // �ڲ���֮ǰ����Ƿ��Ѿ�������������
                            bool found = false;
                            for (const std::string& str : afterDollarArray) {
                                if (str == afterDollar) {
                                    found = true;
                                    break;
                                }
                            }
                            if (!found) {
                                afterDollarArray.push_back(afterDollar);
                                std::cout << afterDollar << std::endl; // ���$���������
                            }

                            pos = nextPos; // ����λ��Ϊ��һ��$
                        }

                    }
                }
            }

        }
        file.close(); // �ر��ļ�
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