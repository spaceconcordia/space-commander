#ifndef DECODE_COMMAND_H
#define DECODE_COMMAND_H

#include <string>
#include "icommand.h"
#include <cstdlib>

using namespace std;

class DecodeCommand : public ICommand {
public:
    DecodeCommand(char* destPath, char* srcPath, int isExecutable, int totalSize) {
        this->destPath     = destPath;
        this->srcPath      = srcPath;
        this->isExecutable = isExecutable;
        this->totalSize    = totalSize;
    }
    
    ~DecodeCommand(){ 
//Does file_data need to be set to null as well?
        if (srcPath != NULL) {
            delete srcPath;
            srcPath = NULL;
        }
        
    }

    void* Execute();
    char* GetDestPath() { return destPath; }
    char* GetSrcPath()  { return srcPath; }
    int IsExecutable()  { return isExecutable; }
    int GetTotalSize()  { return totalSize; }
private:
    char* destPath;
    char* srcPath;
    int isExecutable;
    int totalSize;
};
#endif
