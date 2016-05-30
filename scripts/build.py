#!/usr/bin/env python
import sys
import os
import subprocess

def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("-t", help="run tests on n numbers", default=0, dest="test_size")
    parser.add_argument("-o", help="output dir (relative to source dir)", default="build", dest="out_dir")
    args = parser.parse_args()

    src_dir = os.path.dirname(os.path.dirname(__file__))

    subprocess.check_call("cmake . -B{}".format(args.out_dir).split(), cwd=src_dir)
    subprocess.check_call("cmake --build ./{}".format(args.out_dir).split(), cwd=src_dir)


    if args.test_size:
        n = pow(10, int(args.test_size))
        print "run virtual with {} numbers".format(n)
        subprocess.call("time ./virtual {}".format(n).split(), cwd=os.path.join(src_dir,args.out_dir))
        print "run variant with {} numbers".format(n)
        subprocess.call("time ./variant {}".format(n).split(), cwd=os.path.join(src_dir,args.out_dir))

if __name__ == "__main__":
    main()

