#include "QWQ.h"

using namespace std;


class node
{
public:
    static const node* Not_found;
    string str;
    size_t weight;
    vector<node*> child;
    string word;
    int HaveBeenPushed = 0;
    node(char Strings = '\0', size_t  weights = 0) {
        str = Strings;
        weight = weights;
        child.clear();
    }
    node* add_child(char String, size_t  weights = 0) {
        node* ans = new node(String, weights);
        child.push_back(ans);
        return ans;
    }
    node* find_child(char String) {
        for (vector<node*>::iterator now = child.begin(); now != child.end(); now++) {
            if ((*now)->str[0] == String)
                return *now;
        }
        return NULL;
    }
};
const node* node::Not_found = NULL;


/*class authors
{
private:
public:
    string name;
    size_t  weight;
    authors(const string& names) {
        name = names;
        weight = 0;
    }
    size_t  operator++() {
        return ++weight;
    }
    bool operator < (const authors& tar) {
        return this->weight < tar.weight;
    }
    bool operator > (const authors& tar) {
        return this->weight > tar.weight;
    }
    bool operator >= (const authors& tar) {
        return this->weight >= tar.weight;
    }
    bool operator <= (const authors& tar) {
        return this->weight <= tar.weight;
    }
    authors& operator =(const authors& tar) {
        name = tar.name;
        weight = tar.weight;
        return *this;
    }
};*/
vector<node*>AuthorLocation;

vector<string> RecordSpeeling;
vector<size_t>AuthorValue;
vector<node*>bin[10000000];

class dictionary_tree
{
    
    
public:
    node* root;
    unordered_map<string, size_t> author_weight;
    dictionary_tree() {
        root = new node();
    }
    ~dictionary_tree() {
        delete root;
    }
    void insert(const string& word) {
        node* guodu = insert1(word);
        if (guodu->HaveBeenPushed == 0)
        {AuthorLocation.push_back(guodu);
            guodu->HaveBeenPushed = 1;
        }
    }//ѹ�����ߵ�λ��
    node* insert1(const string& word) {
        node* now = root;
        for (size_t i = 0; i < word.size(); i++) {
            node* next = now->find_child(word[i]);
            if (next == NULL) {
                next = now->add_child(word[i]);
            }
            now = next;RecordSpeeling.push_back(now->str);
        }//�˴����굥�ʵ����һ����ĸ
        now->weight = now->weight + 1;//���߳��ִ�����һ
        now->word = "";
        for (int i = 0; i < RecordSpeeling.size(); i++) {
            now->word = now->word + RecordSpeeling[i];
        }//ƴ����������
        RecordSpeeling.clear();
        return now;
    }//
    //�����������º�ִ�������copy�������õ�ÿ�����ߵĴ���
};
//�������Լ����ڵ�
dictionary_tree WordsOfYears; node* RootOfWordOfYear = WordsOfYears.root;
dictionary_tree Author; node* RootOfAuthor = Author.root;
dictionary_tree Words; node* RootOfWord = Words.root;

    void copyAuthorTimes() {
        for (size_t i = 0; i < AuthorLocation.size(); i++) {
            AuthorValue.push_back(AuthorLocation[i]->weight);
            cout << "���ڿ�����" << i+1 << "������,��" << AuthorLocation.size() << "��,����Ϊ" << AuthorLocation[i]->word << ",���ִ���Ϊ"<< AuthorLocation[i]->weight << endl;
        }
        return;
    }
    void putbin() {
        
        for (long long int i = 0;i < AuthorLocation.size();i++)
        {
            int x = 0;
            cout << "����ѹ���" << i+1 << "�����ݣ���" << AuthorLocation.size() << "��������Ϊ" <<AuthorLocation[i]->word<< ",���ִ���Ϊ"<< AuthorLocation[i]->weight <<endl;
            bin[AuthorLocation[i]->weight].push_back(AuthorLocation[i]);
        }
    };//����Ͱ;
    void binsort() {
        int flag = 0;
        copyAuthorTimes();

        putbin(); 
        string filename = "C:/Users/sby/Desktop/Project1/finalauthor.ini";
        std::ofstream file1(filename, std::ios::app);
        for (size_t i = 10000 - 1;i > 0 && flag < 100;i--) {

            if (bin[i].size() > 0) {

                for (size_t j = 0;j < bin[i].size() - 1;j++) {
                    flag++;


                    string content = bin[i][j]->word + " �ܹ�д��" + to_string(i) + "ƪ����";
                    file1 << content << std::endl;
                    cout << content << endl;
                    if (flag >= 100)break;
                }


            }if (flag >= 100)break;
        }file1.close();
    };//Ͱ����
    //������g�ܵĿ�������Ӧ�����á���
    //����ʱarr��λ�÷�Authorvalue��low��0��high��Authorvalue.size()-1

    // ����������ڲ������������ڻ��ֹ����н���Ԫ��
    size_t partition(std::vector<size_t>& arr, size_t low, size_t high) {
        size_t pivot = arr[high]; // ѡ�����Ҳ�Ԫ����Ϊ��׼
        size_t i = (low - 1); // iָ�����ڼ�¼С�ڻ�׼��Ԫ�ص�����λ��

        for (size_t j = low; j <= high - 1; j++) {
            // �����ǰԪ��С�ڻ���ڻ�׼
            if (arr[j] <= pivot) {
                i++; // ��iָ�������ƶ�
                swap(arr[i], arr[j]);
                swap(AuthorLocation[i], AuthorLocation[j]);//�������ߵĴ���Authorvalue
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    // �ݹ�Ŀ���������
  /* void quickSort(vector<size_t>& arr, size_t low, size_t high) {
        if (low < high) {
            // �������õ�������
            size_t pi = partition(arr, low, high);

            // ʹ�õݹ�������������Ҳ�
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    
    // ��������ķ�װ���������ⲿ����
   // void quickSort(std::vector<size_t>& arr) {
        quickSort(arr, 0, arr.size() - 1);
    }
    //������ӡ���ܵķ�װ�õĿ���������
  //  void fquickSort(std::vector<size_t>& arr) {
        quickSort(arr);
        for (int i = 0;i< 10; i++) {
            std::cout << arr[i] << "ƪ " << AuthorLocation[i]->word << endl;;
        }
     

    }
    */
    void writeToINI(const std::string& filename, const std::string& content, std::string X) {
        std::ofstream file(filename, std::ios::app); // ��׷�ӷ�ʽ���ļ�
        if (!file.is_open()) {
            std::cerr << "�޷����ļ������ڴ����ļ� " << filename << std::endl;
            return;
        }

        if (X == "[A]")  file << "$" << content;
        else if (X == "[B]")file << "��" << content << std::endl;
        else if (X == "[]") {
             Author.insert(content);file << content; }

        file.close(); // �ر��ļ���
    }

    void parseAndWriteToINI(std::string host, const std::string& filename, pugi::xml_node articleElement) {
        std::string sectionA = "[A]";
        std::string sectionB = "[B]";
        std::string sectionAContent;
        std::string sectionBContent;

        writeToINI(filename, host, "[]");

        for (pugi::xml_node authorElement : articleElement.children("author")) {
            const char* authorName = authorElement.child_value(); // ��ȡ <author> �ڵ���ı�����
            sectionAContent = authorName;


            if (sectionAContent != host) writeToINI(filename, sectionAContent, sectionA);


        }

        for (pugi::xml_node titleElement : articleElement.children("title")) {
            const char* titleName = titleElement.child_value(); // ��ȡ <title> �ڵ���ı�����
            sectionBContent = titleName;

            // ��������Ƿ��Ѿ�����
            if (isContentExist(filename, sectionBContent)) {
                std::cout << "�����Ѵ���!" << std::endl;
                continue; // ��������Ѵ��ڣ�������д�벿��
            }
            writeToINI(filename, sectionBContent, sectionB);
        }
    }

    bool check_Elem(std::string tempstr)//β�ڵ��ж�
    {
        if (
            (tempstr.find("article") != std::string::npos) ||
            (tempstr.find("inproceedings") != std::string::npos) ||
            (tempstr.find("proceedings") != std::string::npos) ||
            (tempstr.find("book") != std::string::npos) ||
            (tempstr.find("incollection") != std::string::npos) ||
            (tempstr.find("phdthesis") != std::string::npos) ||
            (tempstr.find("mastersthesis") != std::string::npos) ||
            (tempstr.find("www") != std::string::npos) ||
            (tempstr.find("person") != std::string::npos) ||
            (tempstr.find("data") != std::string::npos)
            )
            return true;
        else return false;
    };

    /*
    void article_read() {


        pugi::xml_document doc;
        if (!doc.load_file(FILEE)) {
            std::cerr << "�Ҳ������ļ��� " << std::endl;
            return;
        }

        std::string tempstr;
        pugi::xml_node dblpNode = doc.child("dblp"); // ��ȡ <dblp> �ڵ�

        // ����Ƿ��ҵ��� <dblp> �ڵ�
        if (dblpNode.empty()) {
            std::cerr << "�Ҳ��� <dblp> �ڵ㣡" << std::endl;
            return;
        }


        for (pugi::xml_node articleElement : dblpNode.children()) {
            const char* tag = articleElement.name();
            if (tag != nullptr) tempstr = tag;
            else {
                std::cerr << "���棺�Ҳ������±��⣡" << std::endl;
                continue;
            }

            if (!check_Elem(tempstr)) {
                std::cerr << "���ִ������ݣ�" << std::endl;
                continue;
            }
            else {
                for (pugi::xml_node titleElement : articleElement.children()) {
                    std::string temp = titleElement.name();
                    if (temp == "title" || temp == "booktitle") {
                        const char* text = titleElement.child_value();
                        std::string input = text;
                        uint32_t hashValue = fnv1a(input);
                        uint32_t hashKey = hashValue % HASH_KEY;
                        std::string str = std::to_string(hashKey);
                        std::string fullname = ARTICLEFILE + str + ".ini";

                        std::ofstream file(fullname, std::ios::out | std::ios::app);
                        if (!file.is_open()) {
                            std::cerr << "�ļ��򿪴���!" << std::endl;
                            return;
                        }

                        std::streampos offset = file.tellp();
                        file << input << "\t" << offset << std::endl;
                        file.close();
                    }
                }
            }
        }
    }*/
    


   void article_read() {
        // ����һ�� XML �ĵ�����
        pugi::xml_document doc;

        // ���� XML �ļ�
        if (!doc.load_file(FILEE)) {
            std::cerr << "�Ҳ������ļ��� " << std::endl;
            return;
        }
        
        std::string tempstr;

        // ��ȡ <dblp> �ڵ�
        pugi::xml_node dblpNode = doc.child("dblp");
        if (dblpNode.empty()) {
            std::cerr << "�Ҳ��� <dblp> �ڵ㣡" << std::endl;
            return;
        }
        int flagarticle = 0;
        for (pugi::xml_node articleElement : dblpNode.children()) {
            cout << "���ڶ�ȡ"<< flagarticle+1 <<"����" << endl;
            flagarticle++;
            const char* tag = articleElement.name();
            if (tag != nullptr) tempstr = tag;
            else {
                std::cerr << "���棺�Ҳ������±��⣡" << std::endl;
                continue;
            }

            if (!check_Elem(tempstr)) {
                std::cerr << "���ִ������ݣ�" << std::endl;
                continue;
            }
            else {
                for (pugi::xml_node titleElement : articleElement.children()) {
                    std::string temp = titleElement.name();
                    if (temp == "title" || temp == "booktitle") {
                        const char* text = titleElement.child_value();
                        std::string input = text;
                        uint32_t hashValue = fnv1a(input);
                        uint32_t hashKey = hashValue % HASH_KEY;
                        std::string str = std::to_string(hashKey);
                        std::string fullname = ARTICLEFILE + str + ".ini";

                        pugi::xml_node* yearpoint = new pugi::xml_node;
                        (*yearpoint) = articleElement.child("year");
                        std::string year = (*yearpoint).child_value();



                        std::ofstream file(fullname, std::ios::out | std::ios::app);
                        if (!file.is_open()) {
                            std::cerr << "�ļ��򿪴���!" << std::endl;
                            return;
                        }

                        // ��¼Ԫ����XML�ļ��е�ƫ����
                        std::streampos offset = articleElement.offset_debug();
                        std::ostringstream oss;
                        oss << offset;
                        std::string Li = oss.str();
                        std::string Lin = input + "\t" + Li+ "\t" + year;
                        // ��������Ƿ��Ѿ�����
                        if (isContentExist(fullname, Lin)) {
                            std::cout << "�����Ѵ���!" << std::endl;
                            continue; // ��������Ѵ��ڣ�������д�벿��
                        }


                        file << input << "\t" << offset<< "\t" << year << std::endl;
                        delete yearpoint;
                        file.close();
                    }
                }
            }
        }
    }

    
    void author_read() {
        pugi::xml_document doc;
        if (!doc.load_file(FILEE)) {
            std::cerr << "�Ҳ������ļ��� " << std::endl;
            return;
        }
        int flag = 0;

        std::string tempstr;
        pugi::xml_node dblpNode = doc.child("dblp"); // ��ȡ <dblp> �ڵ�

        // ����Ƿ��ҵ��� <dblp> �ڵ�
        if (dblpNode.empty()) {
            std::cerr << "�Ҳ��� <dblp> �ڵ㣡" << std::endl;
            return;
        }

        for (pugi::xml_node articleElement : dblpNode.children()) {
            cout << "���ڶ�ȡ����" << flag+1 << endl;
            const char* tag = articleElement.name();
            std::string tempstr;

            if (tag != nullptr) tempstr = tag;
            else {
                std::cerr << "���棺�Ҳ������±��⣡" << std::endl;
                continue;
            }

            if (!check_Elem(tempstr)) {
                std::cerr << "���ִ������ݣ�" << std::endl;
            }
            else {
               // cout << "���ڶ�ȡ����" << endl;
                std::stringstream ss;
                articleElement.print(ss);

                std::string line = ss.str();

                for (pugi::xml_node authorElement : articleElement.children()) {
                    std::string temp = authorElement.name();
                    if (temp == "author" || temp == "editor") {
                        const char* authorName = authorElement.child_value();
                        std::string stri = authorName ? authorName : "";
                        uint32_t hashValue = fnv1a(stri);
                        uint32_t hashKey = hashValue % HASH_KEY;
                        std::string str = std::to_string(hashKey);
                        std::string fullname = AUTHORFILE + str + ".ini";



                        if (!str.empty()) {
                            parseAndWriteToINI(stri, fullname, articleElement);
                        }
                    }
                }
            }flag++;
           // cout<<flag<<endl;
                    if (flag >= 400000)break;
        }
    }



    int main()
    {
       // article_read();
     author_read();
      // fquickSort(AuthorValue);
   
        binsort();
      
        return 0;

    }
