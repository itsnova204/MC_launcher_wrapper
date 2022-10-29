#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

#include "json.hpp"

using namespace std;
using json = nlohmann::json;
string appdata;
string root_path;
string remote = "git@github.com:itsnova204/PLauncher.git";

bool exists (string name) {
    ifstream f(name.c_str());
    return f.good();
}

void setUsername() {
    string name;
    json file_content;
    string write_buffer;

    cout << "enter username: ";
    cin >> name;


    string myText;
    ifstream MyReadFile(root_path + "\\bin\\accounts.json");
    file_content = json::parse(MyReadFile);
    MyReadFile.close();

    file_content["accounts"][0]["ygg"]["extra"]["userName"] = name;
    file_content["accounts"][0]["ygg"]["token"] = name;

    write_buffer = file_content.dump();

    ofstream MyWriteFile(root_path + "\\bin\\accounts.json");
    MyWriteFile << write_buffer;

    MyWriteFile.close();
}

    void install(){

    string command = "ssh-keyscan github.com >> githubKey";
    char cmd[100];
    strcpy(cmd,command.c_str());
    system(cmd);

    command = "cd " + appdata + " && git clone " + remote;

    strcpy(cmd,command.c_str());
    system(cmd);
}

void launch(){
    char cmd[100];
    string command;

    command = "start " + root_path + "\\launch";
    strcpy(cmd,command.c_str());
    system(cmd);
}

void update(){
        string command;
    char cmd[100];

        command = "git pull origin master";
        strcpy(cmd,command.c_str());
        system(cmd);
        //todo make updates not break usernames!
}

int main() {

    appdata = getenv("APPDATA");
    root_path = appdata + "\\PLauncher";


    cout << "launching program..." << endl;



    if (exists(root_path + "\\bin\\UltimMC.exe")) {
        cout << "Instalacao encontrada.\n"
                "Iniciar Minecraft? [1]\n";
        string ans;
        cin >> ans;

        if (ans == "1"){
            update();
            launch();
            return 0;
        }

    }
    else{
        cout << "Instalacao nao encontrada. Instalar agora? [Y para sim, N para nao]: ";
        string ans;
        cin >> ans;

        if (ans == "y" || ans == "Y"){
            install();
            setUsername();
        }else{
            cout << "Abortando" << endl;
        }

    }

    return 0;

}




