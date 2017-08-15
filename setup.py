#!/usr/bin/env python
from setuptools import setup, Extension

setup(
    name="absmode",
    modules=['runit.py'],
    ext_modules=[Extension("fpread", ["fpread.c"])],
)
