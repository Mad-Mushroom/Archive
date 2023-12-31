#pragma once
#include <stdint.h>


template <typename T> class Array
{
    private:
    T* arr;
    bool freed;
    uint64_t size;

    public:
    //bool freed;
    uint64_t getSize();
    Array<T>(uint64_t size);
    T& operator[](uint64_t index);
    void free();
    Array<T> clone();
    void copy(Array<T> target);
    void reInit(uint64_t size);
};

template <typename T> class List
{
    private:
    uint64_t count;
    uint64_t cap;
    Array<T> arr;
    bool freed;
    void init(uint64_t capacity);
    void expandArr();

    public:
    List<T>(uint64_t capacity);
    List<T>();
    void free();
    List<T> clone(); 
    uint64_t getCount();
    uint64_t getCapacity();
    int64_t getIndexOf(T item);
    void add(T item);
    void insertAt(T item, uint64_t index);
    void removeAt(uint64_t index);
    void removeLast();
    void removeFirst();
    T elementAt(uint64_t index);
    T& operator[](uint64_t index);
    void clear();
    bool operator==(List<T> other);
};

template class Array<int>;
template class List<int>;

template class Array<void*>;
template class List<void*>;

#include "../tasks/task.h"

template class Array<Task*>;
template class List<Task*>;

#include "../WindowStuff/Window/window.h"

template class Array<Window*>;
template class List<Window*>;

#include "../userinput/mousePacket.h"

template class Array<MousePacket>;
template class List<MousePacket>;

#include "../WindowStuff/SubInstances/newTerminalInstance/consoleChar.h"

template class Array<ConsoleChar>;
template class List<ConsoleChar>;
template class Array<List<ConsoleChar>*>;
template class List<List<ConsoleChar>*>;

#include "../kernelStuff/Disk_Stuff/Partition_Interfaces/generic/partitionStructs.h"

template class Array<PartitionInterface::PartitionInfo*>;
template class  List<PartitionInterface::PartitionInfo*>;

#include "../kernelStuff/Disk_Stuff/Filesystem_Interfaces/generic/fileSystemStructs.h"

template class Array<FilesystemInterface::BaseInfo*>;
template class  List<FilesystemInterface::BaseInfo*>;

template class Array<FilesystemInterface::FileInfo*>;
template class  List<FilesystemInterface::FileInfo*>;

template class Array<FilesystemInterface::FolderInfo*>;
template class  List<FilesystemInterface::FolderInfo*>;

// #include "../kernelStuff/Disk_Stuff/Partition_Interfaces/generic/genericPartitionInterface.h"

// template class Array<PartitionInterface::GenericPartitionInterface*>;
// template class  List<PartitionInterface::GenericPartitionInterface*>;

#include "../kernelStuff/Disk_Stuff/Disk_Interfaces/generic/genericDiskInterface.h"

template class Array<DiskInterface::GenericDiskInterface*>;
template class List<DiskInterface::GenericDiskInterface*>;


#include "../WindowStuff/SubInstances/guiInstance/guiStuff/components/base/baseComponent.h"

template class Array<GuiComponentStuff::BaseComponent*>;
template class List<GuiComponentStuff::BaseComponent*>;