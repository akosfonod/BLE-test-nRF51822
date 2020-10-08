Import ("env")

def clear_commit_id(source, target, env):
    print("----Post-Build script----")
    print("----Post-Build script END ----")

env.AddPostAction("buildprog", clear_commit_id)
