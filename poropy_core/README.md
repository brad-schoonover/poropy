## README

This project aims to rewrite the core numerical routines of poropy, which were originally a hodge-podge of tools thrown together as a class project.  Although the main user-oriented part of the code will remain in Python, several classes will be written in C++ and exposed to Python using Swig.  I've had success doing this with other projects, and this approach will allow us to keep the full-fledged, PyQt-based GUI while also offering a somewhat limited, standalone executable for use in optimization studies.

