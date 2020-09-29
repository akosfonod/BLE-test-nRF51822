Import ("env")
import subprocess

commit_details = subprocess.check_output("git describe --always --dirty --tags", shell=True, universal_newlines=True).strip()
print("----Pre-Build script----")
print("ENV:         " + str(env))
print("COMMIT ID:   " + commit_details)
print("Current build targets:", map(str, BUILD_TARGETS))
print("Updating commit-ID: " + commit_details)
version_file = open('include/git-version.h','w')
version_file.write('#ifndef GIT_VERSION_H\n#define GIT_VERSION_H\n    #define GIT_COMMIT_ID "' + commit_details + '"\n#endif')
version_file.close()
print("----Pre-Build script END----")
