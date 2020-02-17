###################################################################################
#                                                                                 #
# NAME: meson.build                                                               #
#                                                                                 #
# AUTHOR: Mike Karlesky, Mark VanderVoord, Greg Williams.                         #
# WRITTEN BY: Michael Brockus.                                                    #
#                                                                                 #
# License: MIT                                                                    #
#                                                                                 #
###################################################################################

unity_dir = include_directories('.', '../extras/fixture/src/', '../extras/memory/src/')

unity_lib = static_library(meson.project_name(), 
    sources: ['unity.c', '../extras/fixture/src/unity_fixture.c'],
    include_directories: unity_dir)
