from enum import Enum
from pathlib import Path
import os


class TargetType(Enum):
    PROGRAM     = 0
    MODULE      = 1
    EXTERNAL    = 2

class TargetRules:
    target_name : str
    target_type : TargetType
    public_include_paths: []
    private_include_paths: []
    source_paths: []
    
    def __init__(self):
        self.target_type = TargetType.MODULE
        self.intermediate_path = "Intermediate"
        self.public_include_paths = ["Source/Public"]
        self.private_include_paths = ["Source/Private"]
        self.source_paths = ["Source/Private", "Source/Public"]
        self.target_name = Path(os.path.abspath(".")).stem


def config_h_build(target, source, env):

    config_h_defines = env.Dictionary()

    for a_target, a_source in zip(target, source):
        config_h = open(str(a_target), "w")
        config_h_in = open(str(a_source), "r")
        config_h.write(config_h_in.read() % config_h_defines)
        config_h_in.close()
        config_h.close()

def setup_target(env, target : TargetRules):
    env_target = env.Clone()
    

    if(target.target_type == TargetType.PROGRAM):
        import glob, os
        source = []
        for base_dir in target.source_paths:    
            for file in glob.glob(os.path.join(base_dir,"**/*.cpp"), recursive=True):
                source.append(file)
        print(source)
        env_target.Program(target.target_name, source)
    if(target.target_type == TargetType.MODULE):
        import glob, os
        source = []
        for base_dir in target.source_paths:    
            for file in glob.glob(os.path.join(base_dir,"**/*.cpp"), recursive=True):
                print(file)
                source.append(file)
        
        api_generated_file = os.path.join(target.intermediate_path, target.target_name + ".api.gen.h")
        api_template_file = os.path.join(env_target['ROOT_DIR'], "buildsystem", "templates", "api.gen.h.in")
    
        env_target.Append(
            SBS_MODULE_NAME_UPPER = str.upper(target.target_name)
        )

        env_target.Command(api_generated_file, api_template_file, config_h_build)
        env_target.Append(CPPPATH=target.intermediate_path)
        env_target.Append(CPPPATH=target.public_include_paths)
        env_target.Append(CPPPATH=target.private_include_paths)
        env_target.StaticLibrary(
            target.target_name,
            source=source
        )