import os

root_dir = os.path.dirname(__file__)

flags = "-x c++ -std=c++14 -isystem {0}/external/eggs-variant/include -I {0}".format(root_dir).split()

def FlagsForFile( filename, **kwargs ):
    return { 'flags': flags, 'do_cache': True }


