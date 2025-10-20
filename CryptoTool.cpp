#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <limits>

using namespace std;
class FileHandler
{
public:
    static string readFile(const string Path){
        ifstream ifs(Path);
        if (!ifs) return {};
        ostringstream ss;
        return ss.str();
    }
    static string writeFile(const string text, int flag) {
        const char *name[] = {"encrypted.txt", "decrypted.txt"};
        const string file = name[(flag == 0) ? 0 : 1];
        ofstream ofs(file, ios::out | ios::binary);
        if (!ofs) {
            return "文件保存失败";
        }
        ofs << text;
        return file;
    }

};
class Crypto
{
public:
    
    static string Caesar(const string text, int key, int mode) 
    {
        string result;
        for (char ch : text) {
            char c = static_cast<char>(ch);
            if (isalpha(ch)) {
                char base = islower(ch) ? 'a' : 'A';
                int k = ((key % 26) + 26) % 26;
                c = static_cast<char>((c - base + mode * k + 26) % 26 + base);
            }
            result += c;
        }
        return result;
    }
};
class Menu
{
    int key;
public:
    int flag;
    string text;
    int getkey(){
        cout<<"请输入密钥：";
        cin>>key;
        return key;
    }
    void Showmu();
    int run();
};
int main()
{
    Menu menu;
    return menu.run();
}

void Menu::Showmu() {
    switch (flag) {
    case 1: {
        cout << "请输入要加密的文本：" << endl;
        getline(cin, text);
        key = getkey();
        cout << "加密结果：" << Crypto::Caesar(text, key, 1) << endl;
        break;
    }
    case 2: {
        cout << "请输入要解密的文本：" << endl;
        getline(cin, text);
        key = getkey();
        cout << "解密结果：" << Crypto::Caesar(text, key, -1) << endl;
        break;
    }
    case 3: {
        cout << "请输入要加密的文件路径：" << endl;
        getline(cin, text);
        key = getkey();
        string ftext = FileHandler::readFile(text);
        if (ftext.empty()) {
            cout << "file empty"<< endl;
            break;
        }
        string enc = Crypto::Caesar(ftext, key, 1);
        cout << "加密结果已保存到：" << FileHandler::writeFile(enc, 0) << endl;
        break;
    }
    case 4: {
        cout << "请输入要解密的文件路径：" << endl;
        getline(cin, text);
        key = getkey();
        string ftext = FileHandler::readFile(text);
        if (ftext.empty()) {
            cout << "file empty"<< endl;
            break;
        }
        string dec = Crypto::Caesar(ftext, key, -1);
        cout << "解密结果已保存到：" << FileHandler::writeFile(dec, 1) << endl;
        break;
    }
    case 0:
        break;
    default: {
        cout << "无效选择，请重新输入。" << endl;
        break;
    }
    }
}

int Menu::run() {
    int choice;
    while(1){
    cout<<"欢迎使用简单Caesar Cipher加解密工具\n请选择模式：\n1=加密文本 2=解密文本 3=加密文件 4=解密文件 0=退出"<<endl;
    cin>>choice;
    if(choice==0)
        break;
    flag=choice;
    cin.ignore();
    Showmu();
   }
    return 0;
}