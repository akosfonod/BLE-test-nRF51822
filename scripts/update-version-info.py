import subprocess

commit_details = subprocess.check_output("git describe --always --dirty --tags", shell=True, universal_newlines=True)

version_file = open('include/git-version.h','w')
version_file.write("#ifndef GIT_VERSION_H\n\
#define GIT_VERSION_H\n\
    #define GIT_VERSION " + commit_details + \
"#endif")
version_file.close()
