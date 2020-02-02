from buildsystem.targetrules import TargetRules, TargetType
import glob, os

def config_h_build(target, source, env):

    config_h_defines = env.Dictionary()

    for a_target, a_source in zip(target, source):
        config_h = open(str(a_target), "w")
        config_h_in = open(str(a_source), "r")
        config_h.write(config_h_in.read() % config_h_defines)
        config_h_in.close()
        config_h.close()

def setup_target(self, target : TargetRules):
    if(target == None):
        return

    if(target.target_type == TargetType.PROGRAM):
        print("Setting up " + target.target_name + " program")
        source = []
        for base_dir in target.source_paths:    
            for file in glob.glob(os.path.join(base_dir,"**/*.cpp"), recursive=True):
                source.append(file)

        api_generated_file = os.path.join(target.intermediate_path, target.target_name + ".api.gen.h")
        api_template_file = os.path.join(self['ROOT_DIR'], "buildsystem", "templates", "api.gen.h.in")
    
        self.Append(
            SBS_MODULE_NAME_UPPER = str.upper(target.target_name)
        )

        self.Command(api_generated_file, api_template_file, config_h_build)
        
        
        self.Append(CPPPATH=target.intermediate_path)
        self.Append(CPPPATH=target.public_include_paths)
        self.Append(CPPPATH=target.private_include_paths)
        node = self.Program(
            target.target_name,
            source=source
        )
        self.Append(LIBS=target.public_dependencies)
        
        return node

    if(target.target_type == TargetType.MODULE):
        print("Setting up " + target.target_name + " module")
        source = []
        for base_dir in target.source_paths:    
            for file in glob.glob(os.path.join(base_dir,"**/*.cpp"), recursive=True):
                source.append(file)
        
        api_generated_file = os.path.join(target.intermediate_path, target.target_name + ".api.gen.h")
        api_template_file = os.path.join(self['ROOT_DIR'], "buildsystem", "templates", "api.gen.h.in")
    
        self.Append(
            SBS_MODULE_NAME_UPPER = str.upper(target.target_name)
        )

        self.Command(api_generated_file, api_template_file, config_h_build)
        self.Append(CPPPATH=target.intermediate_path)
        self.Append(CPPPATH=target.public_include_paths)
        self.Append(CPPPATH=target.private_include_paths)
        node = self.StaticLibrary(
            target.target_name,
            source=source
        )
        self.Append(LIBS=target.public_dependencies)
        return node

    if(target.target_type == TargetType.EXTERNAL):
        print("Setting up " + target.target_name + " external")
        source = []
        for base_dir in target.source_paths:    
            for file in glob.glob(os.path.join(base_dir,"**/*.cpp"), recursive=True):
                source.append(file)
        self.Append(CPPDEFINES=target.definitions)
        self.Append(CPPPATH=target.public_include_paths)
        self.Append(CPPPATH=target.private_include_paths)
        self.SharedLibrary(
            target.target_name,
            source=source
        )
        self.Append(LIBS=target.public_dependencies)
        return node
