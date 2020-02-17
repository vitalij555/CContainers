###################################################################################
#                                                                                 #
# NAME: meson.build                                                               #
#                                                                                 #
# AUTHOR: Vitalij Gotovskij                                                       #
#                                                                                 #
#                                                                                 #
# License: MIT                                                                    #
#                                                                                 #
###################################################################################



project('CContainersTests', 'c',
    license         : 'MIT',
    meson_version   : '>=0.50.0',
    default_options: ['warning_level=3', 'werror=true', 'c_std=c11']
)
lang = 'c'
cc = meson.get_compiler(lang)


##
#
# Meson: Add compiler flags
#
##
if cc.get_id() == 'clang'
    add_project_arguments(cc.get_supported_arguments(
            [
                '-Wcast-qual',	'-Wshadow', '-Wcast-align', '-Wweak-vtables',
                '-Wold-style-cast', '-Wpointer-arith', '-Wconversion',
                '-Wexit-time-destructors', '-Wglobal-constructors',
                '-Wmissing-noreturn', '-Wmissing-prototypes', '-Wno-missing-braces'
            ]
        ), language: lang)
endif

if cc.get_argument_syntax() == 'gcc'
    add_project_arguments(cc.get_supported_arguments(
            [
                '-Wformat', '-Waddress', '-Winit-self', '-Wno-multichar',
                '-Wpointer-arith'       , '-Wwrite-strings'              ,
                '-Wno-parentheses'      , '-Wno-type-limits'             ,
                '-Wformat-security'     , '-Wunreachable-code'           ,
                '-Waggregate-return'    , '-Wformat-nonliteral'          ,
                '-Wmissing-prototypes'  ,
# '-Wold-style-definition'       ,
                '-Wmissing-declarations', '-Wmissing-include-dirs'       ,
                '-Wno-unused-parameter' 
            ]
        ), language: lang)
endif

if cc.get_id() == 'msvc'
    add_project_arguments(cc.get_supported_arguments(
            [
                '/w44265', '/w44061', '/w44062',
                '/wd4018', '/wd4146', '/wd4244',
                '/wd4305', '/D _CRT_SECURE_NO_WARNINGS'
            ]
        ), language: lang)
endif


ccontainers_include_dirs = include_directories( '.', 
                                                './subprojects/unity/extras/memory/src', 
                                                './subprojects/unity/extras/fixture/src', 
                                                './subprojects/unity/src')

#unity_lib = static_library(meson.project_name(), 
#    sources: ['unity.c'],
#    include_directories: unity_dir)
#subdir('unity')
#unity = dependency('unity')

src = ['TestRunner.c', 'main.c', 'List.c', 'ListTests.c', 'containerMemory.c']

unity = subproject('unity')
unity_dep = unity.get_variable('unity_dep')

executable('CContainersTests', src, dependencies : unity_dep, include_directories : ccontainers_include_dirs)

