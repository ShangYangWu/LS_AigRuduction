#include <string>
#include <vector>

struct CmdProducer{
    std::vector<std::string> cmd;

    void generateScript(const std::string& filename);
};