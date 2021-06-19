#include <queue>
#include <set>
#include <string>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "delrep.h"
#include <iostream>


std::queue<std::string> folders;
std::set<std::string> files;

void delrep(std::string initial_foldername)
{
    char buf[256];
    getcwd(buf, 256);
    std::string debugfile = std::string(buf) + '/' + "debugfile.txt";
    int fd = open(debugfile.c_str(), 
                  O_CREAT | O_RDWR, 0644);
    folders.push(initial_foldername);
    while(!folders.empty())
    {
        std::string foldername = folders.front();
        folders.pop();
        if(foldername != ".") chdir(foldername.c_str());
        DIR* folder;
        struct dirent* entry;
        folder = opendir(foldername.c_str());
        if(folder == NULL) 
            std::cout << "failed to open " << foldername << std::endl;
        while( (entry = readdir(folder)) != nullptr)
        {
            struct stat filestat;
            if((stat(entry->d_name, &filestat)) == -1) 
                std::cout << "stat failed!\n";
            char basepath[256];
            getcwd(basepath, 256);
            if(S_ISDIR(filestat.st_mode))
            {
                std::string entryname = std::string(entry->d_name);
                if(entryname != ".." && entryname != ".")
                {
                    folders.push(std::string(basepath) + '/' + entryname);
                }
            }
            else if(S_ISREG(filestat.st_mode))
            {
                std::string filename = std::string(entry->d_name);
                std::string filepath = std::string(basepath) + '/' + filename;
                size_t sizetest = files.size();
                files.insert(filename);
                if(sizetest == files.size())
                {
                    if(remove(filepath.c_str()) == -1) 
                        std::cout << "couldn't delete " << filename << std::endl;
                    write(fd, std::string("REMOVED " + filepath + "\n").c_str(), filepath.size() + 9);
                }
                else
                {
                    write(fd, (filepath + "\n").c_str(), filepath.size() + 1);
                }
            }
        }
        if(closedir(folder) == -1)
        {
            std::cout << "falied to close " << foldername << std::endl;
        }
    }
    close(fd);
}
