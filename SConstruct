#!/usr/bin/env python

from os import path
from buildsystem import methods

env_base = Environment(
    ROOT_DIR = path.abspath(path.curdir)
)
env_base.__class__.setup_target = methods.setup_target

env = env_base.Clone()

Export('env')

SConscript(
    path.join("src", "SCsub"),
    # variant_dir=path.join("bin"),
    # duplicate=0
)