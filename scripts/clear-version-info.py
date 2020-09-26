version_file = open('include/git-version.h','w')
version_file.write("#ifndef GIT_VERSION_H\n\
#define GIT_VERSION_H\n\
    #define GIT_VERSION 0000000\n\
#endif")
version_file.close()
