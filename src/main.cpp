#include "arg_parser.hpp"
#include "cmd_producer.hpp"
#include <iomanip>

int main(int argc, char **argv) {
    auto arg = ParseArgument(argc, argv);
    CmdProducer out;
    out.generateScript(arg.file);
}

// 生成ex00.script~ex99.script
/*
int main() {
    for (int i = 0; i < 100; ++i) {
        std::ostringstream filename_stream;
        filename_stream << "ex" << std::setw(2) << std::setfill('0') << i << ".truth";
        std::string filename = filename_stream.str();
        
        std::string program_name = "pa2.out";
        char* argv[] = {const_cast<char*>(program_name.c_str()), const_cast<char*>(filename.c_str()), nullptr};
        auto arg = ParseArgument(2, argv);
        
        CmdProducer out;
        out.generateScript(arg.file);
    }

    return 0;
}
*/