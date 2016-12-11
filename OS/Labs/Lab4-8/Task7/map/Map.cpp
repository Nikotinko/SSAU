#include <iostream>
#include <fstream>
#include <cstring>
#include <w32api/ntdef.h>
#include <w32api/fileapi.h>
#include <w32api/handleapi.h>
#include <w32api/synchapi.h>
#include <w32api/rpc.h>
#include "Map.h"



void writeNode(HANDLE hFile, Node *node) {
    if (node != nullptr) {
        WriteFile(hFile, node->getKey(), sizeof(int), NULL, NULL);
        WriteFile(hFile, node->getValue(), sizeof(int), NULL, NULL);
        writeNode(hFile, node->getLeftNode());
        writeNode(hFile, node->getRightNode());
    }
}

static DWORD WINAPI putAsyncStart(CONST LPVOID lpParam)
{
    Map* instance = (Map*) lpParam;
    return instance->putAsync();
}

DWORD WINAPI Map::putAsync(){
    WaitForSingleObject(hMutex, INFINITE);
    int key = *(buffer->getKey());
    int value = *(buffer->getValue());
    putSync(key, value);
    Map::output("savedMap.txt",this);
    ReleaseMutex(hMutex);
    ExitThread(0);
}

//public
int *Map::get(int key) {
    if (rootNode != nullptr) {
        Node *node = rootNode->findNode(key);
        if (node != nullptr) {
            return node->getValue();
        }
    }
    return nullptr;
}

void Map::put(int key, int val) {
    if (currentThread != NULL && currentThread != nullptr) {
        WaitForSingleObject(currentThread,INFINITE);
    }
    WaitForSingleObject(hMutex, INFINITE);
    buffer = new Node(key, val);
    ReleaseMutex(hMutex);

    currentThread = CreateThread(NULL, 0, &putAsyncStart, this, 0, NULL);
    if(NULL == currentThread) {
        std::cout << "Error while try to create new thread" << std::endl;
    }
}

void Map::putSync(int key, int val) {
    Node *insertedNode = new Node(key,val);

    if (rootNode != NULL && rootNode!= nullptr) {
        rootNode->insertNode(insertedNode);
    } else {
        rootNode = insertedNode;
    }
    (*size)++;
}

void Map::remove(int key) {
    if (rootNode != nullptr) {
        if (rootNode->removeNode(key)) {
            (*size)--;
        }
    }
}

Map::Map() {
    hMutex = CreateMutex(NULL, FALSE, NULL);
    size = new int(0);
    rootNode = nullptr;
    if(NULL == hMutex) {
        std::cout << "Error while try to create mutex" << std::endl;
    }
}

Map::~Map() {
    std::cout << "Map destructor, size=" << *size << std::endl;
    delete size;
    rootNode->~Node();
    CloseHandle(hMutex);
}

int Map::getSize() {
    return *size;
}


void Map::output(char *filename, Map *source) {
    HANDLE hFile = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    int size = source->getSize();
    WriteFile(hFile, &size, sizeof(int), NULL, NULL);
    writeNode(hFile, source->rootNode);
    CloseHandle(hFile);
}

Map *Map::input(char *filename) {
    Map *map = new Map();
    HANDLE hFile = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, NULL, NULL);
    int len, k, v;
    ReadFile(hFile, &len, sizeof(int), NULL, NULL);
    for (int i = 0; i < len; i++) {
        ReadFile(hFile, &k, sizeof(int), NULL, NULL);
        ReadFile(hFile, &v, sizeof(int), NULL, NULL);
        map->putSync(k, v);
    }
    CloseHandle(hFile);
    return map;
}