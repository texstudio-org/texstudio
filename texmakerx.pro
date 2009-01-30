TEMPLATE	= subdirs 
CONFIG = $$unique(CONFIG)
CONFIG -= debug debug_and_release release
CONFIG	+= ordered  debug_and_release
SUBDIRS += qcodeedit/lib/lib.pro \
           texmakerapp.pro
