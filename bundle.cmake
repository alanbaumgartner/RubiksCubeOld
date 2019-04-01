INCLUDE(BundleUtilities)

if (UNIX)
    fixup_bundle(bin/RubiksCube "" "")
endif (UNIX)

if (MSVC)
    fixup_bundle(bin/RubiksCube.exe "" "")
endif (MSVC)