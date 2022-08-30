# python pyMake.py insatall

from distutils.core import setup, Extension
spam_mod = Extension("spam", sources = ['spammodule.c'])
setup(name = "spam",
    version = "1,0",
    description = "A sample Extention Module",
    ext_modules = [spam_mod],
)
