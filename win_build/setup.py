#encoding:utf-8
from distutils.core import setup, Extension

zlib_dir = ""
zlib_zconf_dir = ""
project_base = ""
python_root = ""
dll_dir = ""

module1 = Extension('uwebsocketspy',
                    define_macros = [('MAJOR_VERSION', '1'),
                                     ('MINOR_VERSION', '0')],
                    include_dirs = [zlib_dir,
                                    zlib_zconf_dir,
                                    project_base+"\\uWebSockets\\src",
                                    project_base+"\\uWebSockets\\uSockets\\src",
                                    project_base+"\\libuv\\include"],
                    libraries = ['python38', "uSockets", "uv", "zlib", "python3", "Psapi", "Iphlpapi", "Userenv", "ws2_32"],
                    library_dirs = [python_root+'\\libs', dll_dir],
                    extra_compile_args = ['/std:c++latest', '/O2', "/MD"],
                    sources = [project_base+'\\src\\extension.cpp'])

setup (name = 'uwebsocketspy',
       version = '0.0.9',
       data_files=[(dll_dir, ["uSockets.dll", "uv.dll", "uv_a.dll", "zlib.dll"])],  # if this not works well, copy dlls to the pyd folder manually
       ext_modules = [module1])