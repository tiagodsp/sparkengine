sbs_add_module(
    PROGRAM
    USE_PCH
    DEPENDS sparkengine
    DEFINITIONS
        #"IMGUI_API"
    SOURCE_PATHS
        "Source/Public/"
        "Source/Private/"
    PUBLIC_INCLUDE_PATHS
        "Source/Public/"
    PRIVATE_INCLUDE_PATHS
        "Source/Private/"
)
