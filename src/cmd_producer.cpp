#include "cmd_producer.hpp"
#include <cstdlib>
#include <ctime>
#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <array>
#include <memory>
#include <stdio.h>
#include <cctype>

std::string getFileNameWithoutExtension(const std::string& filename) {
    size_t lastSlashPos = filename.find_last_of("/\\");
    size_t lastDotPos = filename.find_last_of('.');

    if (lastDotPos == std::string::npos || (lastSlashPos != std::string::npos && lastDotPos < lastSlashPos)) {
        return filename;
    }
    return filename.substr(lastSlashPos + 1, lastDotPos - lastSlashPos - 1);
}


std::vector<std::string> produceCmd(const std::string filename) {
    std::vector<std::string> candidates = {"balance", "rewrite","refactor", "resub"};
    std::vector<std::string> cmd;
    srand(static_cast<unsigned int>(time(0)));
    int temp = 0;

    std::string firstline = "read_truth -xf " + filename + ";";
    cmd.emplace_back(firstline);
    cmd.emplace_back("strash;");
    for (int i = 0; i < 19; ++i) {
        std::string candidate;
        int randnum = rand()%4;
        while(randnum == temp){
            randnum = rand()%4;
        }
        temp = randnum;
        candidate = candidates[randnum];
        candidate += ";";
        cmd.emplace_back(candidate);
    }
    cmd.emplace_back("print_stats");

    return cmd;
}

std::string exec(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (!feof(pipe)) {
        if (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            std::string line = buffer.data();
            size_t pos = line.find("and = ");
            if (pos != std::string::npos) {
                size_t start = pos + 6;
                while (start < line.size() && isspace(line[start])) {
                    ++start;
                }
                size_t end = start;
                while (end < line.size() && isdigit(line[end])) {
                    ++end;
                }
                result = line.substr(start, end - start);
                break;
            }
        }
    }
    pclose(pipe);
    return result;
}


int execute(std::vector<std::string> temp_cmd) {
    std::string command = "../abc -c \"";
    for(auto &item : temp_cmd){
        command += item;
    }
    command += "\"";
    // std::cout << command << std::endl;
    std::string command_output = exec(command);
    // std::cout <<"\n" << command_output << std::endl;

    int result_int = std::stoi(command_output);

    return result_int;
}


void CmdProducer::generateScript(const std::string& filename) {
    
    const std::string scriptName = getFileNameWithoutExtension(filename);
    const std::string scriptFilename = scriptName + ".script";

    std::vector<std::string> temp_cmd;
    temp_cmd = produceCmd(filename);
    int min = INT_MAX;
    for(size_t i=0; i<100; ++i){
        int temp_min = execute(temp_cmd);
        if(temp_min < min){
            cmd.clear();
            cmd = temp_cmd;
        }
    }

    std::ofstream scriptFile(scriptFilename);
    if (scriptFile.is_open()) {
        scriptFile << "read_truth -xf " << scriptName << ".truth; " ;
        for(size_t i=1; i<21; ++i){
            scriptFile << cmd[i] ;
        }
        scriptFile << "write " << scriptName << ".aig" << "; " ;
        scriptFile << "print_stats" ;
        scriptFile.close();
        std::cout << "Script file generated: " << scriptFilename << std::endl;
    } else {
        std::cerr << "Error: Unable to open script file." << std::endl;
    }
}