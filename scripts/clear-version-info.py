Import ("env")

def clear_commit_id(source, target, env):
    print("----Post-Build script----")
    print("Rewoking commit ID details.")
    # version_file = open('include/git-version.h','w')
    # version_file.write('#ifndef GIT_VERSION_H\n#define GIT_VERSION_H\n    #define GIT_COMMIT_ID "0000000"\n#endif')
    # version_file.close()
    print("----Post-Build script END ----")

env.AddPostAction("buildprog", clear_commit_id)
