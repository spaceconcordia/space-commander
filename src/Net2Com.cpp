#include <Net2Com.h>
#include <NamedPipe.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#ifdef PC
const char* Net2Com::pipe_str[] = {"pipe1", "pipe2", "pipe3", "pipe4"};
#else
const char* Net2Com::pipe_str[] = {"pipes/pipe1", "pipes/pipe2", "pipes/pipe3", "pipes/pipe4"}; // Q6 paths
#endif
//----------------------------------------------
//  Constructor
//----------------------------------------------
Net2Com::Net2Com(PIPE_NUM dataw, PIPE_NUM datar, PIPE_NUM infow, PIPE_NUM infor){
    Initialize();
    CreatePipes();

    dataPipe_w = pipe[dataw];
    dataPipe_r = pipe[datar];
    infoPipe_w = pipe[infow];
    infoPipe_r = pipe[infor];
}
//----------------------------------------------
//  Destructor
//----------------------------------------------
Net2Com::~Net2Com(){
    for (int i=0; i<NUMBER_OF_PIPES; i++){
        delete pipe[i];
    }
}
//----------------------------------------------
//  Initialize
//----------------------------------------------
bool Net2Com::Initialize(){
    for (int i=0; i<NUMBER_OF_PIPES; i++){
        pipe[i] = new NamedPipe(pipe_str[i]);
    }

    return true;
}
//----------------------------------------------
//  CreatePipes
//----------------------------------------------
bool Net2Com::CreatePipes(){
    for (int i=0; i<NUMBER_OF_PIPES; i++){
        if (pipe[i]->Exist() == false){
            pipe[i]->CreatePipe();
        }
    }

    return true;
}

//----------------------------------------------
//  OpenReadPipesPersistently
//----------------------------------------------
void Net2Com::OpenReadPipesPersistently(){
}
//----------------------------------------------
//  OpenWritePipesPersistently
//----------------------------------------------
void Net2Com::OpenWritePipesPersistently(){
}
//----------------------------------------------
// WriteToDataPipe
//----------------------------------------------
int Net2Com::WriteToDataPipe(const char* str){
    int result = dataPipe_w->WriteToPipe(str, strlen(str) + NULL_CHAR_LENGTH);
    return result;
}
int Net2Com::WriteToDataPipe(const void* data, int size){
    int result = dataPipe_w->WriteToPipe(data, size);
    return result;
}
int Net2Com::WriteToDataPipe(unsigned char number){
    unsigned char byte = number;
    return dataPipe_w->WriteToPipe(&byte, sizeof(unsigned char));
}
//----------------------------------------------
// ReadFromDataPipe
//----------------------------------------------
int Net2Com::ReadFromDataPipe(char* buffer, int buf_size){
    return dataPipe_r->ReadFromPipe(buffer, buf_size);
}
//----------------------------------------------
// WriteToInfoPipe
//----------------------------------------------
int Net2Com::WriteToInfoPipe(const char* str){
    int result = infoPipe_w->WriteToPipe(str, strlen(str) + NULL_CHAR_LENGTH);
    return result;
}
int Net2Com::WriteToInfoPipe(const void* data, int size){
    int result = infoPipe_w->WriteToPipe(data, size);
    return result;
}
int Net2Com::WriteToInfoPipe(unsigned char number){
    unsigned char byte = number;
    return infoPipe_w->WriteToPipe(&byte, sizeof(unsigned char));
}
//----------------------------------------------
//  ReadFromInfoPipe
//----------------------------------------------
int Net2Com::ReadFromInfoPipe(char* buffer, int buf_size){
    return infoPipe_r->ReadFromPipe(buffer, buf_size);
}
