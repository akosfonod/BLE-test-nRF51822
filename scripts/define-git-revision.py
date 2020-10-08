#!/usr/bin/env python3
# define-git-revision.py

import subprocess

REVISION = subprocess.check_output(["git", "describe", "--always", "--dirty"]).strip()

print("-D GIT_COMMIT_ID='\"{}\"'".format(REVISION.decode("UTF-8")))