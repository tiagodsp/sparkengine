from enum import Enum
from pathlib import Path
import os
import glob

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
    definitions : []
    public_dependencies : []
    
    def __init__(self):
        self.target_type = TargetType.MODULE
        self.intermediate_path = "Intermediate"
        self.public_include_paths = ["Source/Public"]
        self.private_include_paths = ["Source/Private"]
        self.source_paths = ["Source/Private", "Source/Public"]
        self.target_name = Path(os.path.abspath(".")).stem
        self.definitions = []
        self.public_dependencies = []


