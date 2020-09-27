import subprocess

commit_details = subprocess.check_output("git describe --always --dirty --tags", shell=True, universal_newlines=True).strip()

print(commit_details)

version_file = open('include/git-version.h','w')
version_file.write('#ifndef GIT_VERSION_H\n\
#define GIT_VERSION_H\n\
    #define GIT_COMMIT_ID "' + commit_details + '"\n\
#endif')
version_file.close()
