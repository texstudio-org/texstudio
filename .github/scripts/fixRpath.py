#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from subprocess import Popen, PIPE
from string import Template
import os
import sys
import logging
import argparse
import re
from collections import namedtuple

def run_and_get_output(popen_args):
    """Run process and get all output"""
    process_output = namedtuple('ProcessOutput', ['stdout', 'stderr', 'retcode'])
    try:
        proc = Popen(popen_args, stdin=PIPE, stdout=PIPE, stderr=PIPE)
        stdout, stderr = proc.communicate(b'')
        proc_out = process_output(stdout, stderr, proc.returncode)

        return proc_out
    except Exception as exc:
        return process_output('', exc.message, -1)

def get_dependencies(filename):
    """
    input: filename must be an absolute path
    Should call `otool` and returns the list of dependencies, unsorted,
    unmodified, just the raw list so then we could eventually re-use in other
    more specialized functions
    """
    popen_args = ['otool', '-L', filename]
    proc_out = run_and_get_output(popen_args)
    deps = []
    if proc_out.retcode == 0:
        # some string splitting
        deps = [s.strip().split(' ')[0] for s in proc_out.stdout.splitlines()[1:] if s]
        # prevent infinite recursion when a binary depends on itself (seen with QtWidgets)...
        deps = [s for s in deps if os.path.basename(filename) not in s]
    return deps

def fixRPATH(path,libPath):
    dirs=os.listdir(path)
    for fn in dirs:
        #print("working on %s" % fn)
        if os.path.isdir(path+'/'+fn) and 'framework' in fn:
            fixRPATH(path+'/'+fn,libPath)
        if os.path.isfile(path+'/'+fn):
            print("checking file %s" % fn)
            deps=get_dependencies(path+'/'+fn)
            for lnk in deps:
                if lnk.startswith('@rpath'):
                    newLnk=lnk.replace('@rpath',libPath)
                    print("fix %s" % lnk)
                    print("with %s" % newLnk)
                    popen_args = ['install_name_tool', '-change', lnk, newLnk, path+'/'+fn]
                    proc_out = run_and_get_output(popen_args)


if __name__ == "__main__":
    descr = """finish the job started by macdeployqt!
 - find dependencies/rpaths with otool
 - copy missed dependencies with cp and mkdir
 - fix missed rpaths        with install_name_tool

 exit codes:
 - 0 : success
 - 1 : error
 """

    parser = argparse.ArgumentParser(description=descr,
                                     formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('qtpath',
                        help='path of Qt libraries used to build the Qt application')
    args = parser.parse_args()

    qtpath = os.path.normpath(args.qtpath)
    fixRPATH(qtpath,qtpath)
