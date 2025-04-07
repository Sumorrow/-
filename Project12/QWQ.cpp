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
    }//压入作者的位置
    node* insert1(const string& word) {
        node* now = root;
        for (size_t i = 0; i < word.size(); i++) {
            node* next = now->find_child(word[i]);
            if (next == NULL) {
                next = now->add_child(word[i]);
            }
            now = next;RecordSpeeling.push_back(now->str);
        }//此处放完单词的最后一个字母
        now->weight = now->weight + 1;//作者出现次数加一
        now->word = "";
        for (int i = 0; i < RecordSpeeling.size(); i++) {
            now->word = now->word + RecordSpeeling[i];
        }//拼好作者名字
        RecordSpeeling.clear();
        return now;
    }//
    //读完所有文章后，执行下面的copy函数，得到每个作者的次数
};
//三棵树以及根节点
dictionary_tree WordsOfYears; node* RootOfWordOfYear = WordsOfYears.root;
dictionary_tree Author; node* RootOfAuthor = Author.root;
dictionary_tree Words; node* RootOfWord = Words.root;

    void copyAuthorTimes() {
        for (size_t i = 0; i < AuthorLocation.size(); i++) {
            AuthorValue.push_back(AuthorLocation[i]->weight);
            cout << "正在拷贝第" << i+1 << "条数据,共" << AuthorLocation.size() << "条,数据为" << AuthorLocation[i]->word << ",出现次数为"<< AuthorLocation[i]->weight << endl;
        }
        return;
    }
    void putbin() {
        
        for (long long int i = 0;i < AuthorLocation.size();i++)
        {
            int x = 0;
            cout << "正在压入第" << i+1 << "条数据，共" << AuthorLocation.size() << "条，数据为" <<AuthorLocation[i]->word<< ",出现次数为"<< AuthorLocation[i]->weight <<endl;
            bin[AuthorLocation[i]->weight].push_back(AuthorLocation[i]);
        }
    };//放入桶;
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


                    string content = bin[i][j]->word + " 总共写了" + to_string(i) + "篇文章";
                    file1 << content << std::endl;
                    cout << content << endl;
                    if (flag >= 100)break;
                }


            }if (flag >= 100)break;
        }file1.close();
    };//桶排序
    //下面是g跑的快速排序，应该能用。。
    //调用时arr的位置放Authorvalue，low放0，high放Authorvalue.size()-1

    // 快速排序的内部函数，用于在划分过程中交换元素
    size_t partition(std::vector<size_t>& arr, size_t low, size_t high) {
        size_t pivot = arr[high]; // 选择最右侧元素作为基准
        size_t i = (low - 1); // i指针用于记录小于基准的元素的最右位置

        for (size_t j = low; j <= high - 1; j++) {
            // 如果当前元素小于或等于基准
            if (arr[j] <= pivot) {
                i++; // 将i指针向右移动
                swap(arr[i], arr[j]);
                swap(AuthorLocation[i], AuthorLocation[j]);//交换作者的次数Authorvalue
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    // 递归的快速排序函数
  /* void quickSort(vector<size_t>& arr, size_t low, size_t high) {
        if (low < high) {
            // 分区并得到分区点
            size_t pi = partition(arr, low, high);

            // 使用递归分区排序左侧和右侧
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    
    // 快速排序的封装函数，简化外部调用
   // void quickSort(std::vector<size_t>& arr) {
        quickSort(arr, 0, arr.size() - 1);
    }
    //附带打印功能的封装好的快速排序函数
  //  void fquickSort(std::vector<size_t>& arr) {
        quickSort(arr);
        for (int i = 0;i< 10; i++) {
            std::cout << arr[i] << "篇 " << AuthorLocation[i]->word << endl;;
        }
     

    }
    */
    void writeToINI(const std::string& filename, const std::string& content, std::string X) {
        std::ofstream file(filename, std::ios::app); // 以追加方式打开文件
        if (!file.is_open()) {
            std::cerr << "无法打开文件或正在创建文件 " << filename << std::endl;
            return;
        }

        if (X == "[A]")  file << "$" << content;
        else if (X == "[B]")file << "￥" << content << std::endl;
        else if (X == "[]") {
             Author.insert(content);file << content; }

        file.close(); // 关闭文件流
    }

    void parseAndWriteToINI(std::string host, const std::string& filename, pugi::xml_node articleElement) {
        std::string sectionA = "[A]";
        std::string sectionB = "[B]";
        std::string sectionAContent;
        std::string sectionBContent;

        writeToINI(filename, host, "[]");

        for (pugi::xml_node authorElement : articleElement.children("author")) {
            const char* authorName = authorElement.child_value(); // 获取 <author> 节点的文本内容
            sectionAContent = authorName;


            if (sectionAContent != host) writeToINI(filename, sectionAContent, sectionA);


        }

        for (pugi::xml_node titleElement : articleElement.children("title")) {
            const char* titleName = titleElement.child_value(); // 获取 <title> 节点的文本内容
            sectionBContent = titleName;

            // 检查内容是否已经存在
            if (isContentExist(filename, sectionBContent)) {
                std::cout << "内容已存在!" << std::endl;
                continue; // 如果内容已存在，则跳过写入部分
            }
            writeToINI(filename, sectionBContent, sectionB);
        }
    }

    bool check_Elem(std::string tempstr)//尾节点判定
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
            std::cerr << "找不到该文件！ " << std::endl;
            return;
        }

        std::string tempstr;
        pugi::xml_node dblpNode = doc.child("dblp"); // 获取 <dblp> 节点

        // 检查是否找到了 <dblp> 节点
        if (dblpNode.empty()) {
            std::cerr << "找不到 <dblp> 节点！" << std::endl;
            return;
        }


        for (pugi::xml_node articleElement : dblpNode.children()) {
            const char* tag = articleElement.name();
            if (tag != nullptr) tempstr = tag;
            else {
                std::cerr << "警告：找不到文章标题！" << std::endl;
                continue;
            }

            if (!check_Elem(tempstr)) {
                std::cerr << "出现错误数据！" << std::endl;
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
                            std::cerr << "文件打开错误!" << std::endl;
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
        // 创建一个 XML 文档对象
        pugi::xml_document doc;

        // 加载 XML 文件
        if (!doc.load_file(FILEE)) {
            std::cerr << "找不到该文件！ " << std::endl;
            return;
        }
        
        std::string tempstr;

        // 获取 <dblp> 节点
        pugi::xml_node dblpNode = doc.child("dblp");
        if (dblpNode.empty()) {
            std::cerr << "找不到 <dblp> 节点！" << std::endl;
            return;
        }
        int flagarticle = 0;
        for (pugi::xml_node articleElement : dblpNode.children()) {
            cout << "正在读取"<< flagarticle+1 <<"文章" << endl;
            flagarticle++;
            const char* tag = articleElement.name();
            if (tag != nullptr) tempstr = tag;
            else {
                std::cerr << "警告：找不到文章标题！" << std::endl;
                continue;
            }

            if (!check_Elem(tempstr)) {
                std::cerr << "出现错误数据！" << std::endl;
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
                            std::cerr << "文件打开错误!" << std::endl;
                            return;
                        }

                        // 记录元素在XML文件中的偏移量
                        std::streampos offset = articleElement.offset_debug();
                        std::ostringstream oss;
                        oss << offset;
                        std::string Li = oss.str();
                        std::string Lin = input + "\t" + Li+ "\t" + year;
                        // 检查内容是否已经存在
                        if (isContentExist(fullname, Lin)) {
                            std::cout << "内容已存在!" << std::endl;
                            continue; // 如果内容已存在，则跳过写入部分
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
            std::cerr << "找不到该文件！ " << std::endl;
            return;
        }
        int flag = 0;

        std::string tempstr;
        pugi::xml_node dblpNode = doc.child("dblp"); // 获取 <dblp> 节点

        // 检查是否找到了 <dblp> 节点
        if (dblpNode.empty()) {
            std::cerr << "找不到 <dblp> 节点！" << std::endl;
            return;
        }

        for (pugi::xml_node articleElement : dblpNode.children()) {
            cout << "正在读取文章" << flag+1 << endl;
            const char* tag = articleElement.name();
            std::string tempstr;

            if (tag != nullptr) tempstr = tag;
            else {
                std::cerr << "警告：找不到文章标题！" << std::endl;
                continue;
            }

            if (!check_Elem(tempstr)) {
                std::cerr << "出现错误数据！" << std::endl;
            }
            else {
               // cout << "正在读取作者" << endl;
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
