[Open manual](https://texstudio-org.github.io/getting_started.html)

The manual is written as myST markdown to be processed with sphinx-doc.
The markdown-dialect is decribed [here](https://myst-parser.readthedocs.io/en/latest/intro.html) and [here](https://pradyunsg.me/furo/reference/).

The translation is done by calling `make html`

The result is in `./build/html/` , `getting_started.html` as entry point.

Set up of sphinx, see [web](sphinx-doc.org):
```
pip3 install --upgrade pip
pip3 install sphinx
pip3 install myst_parser
pip3 install sphinx_comments
pip3 install sphinx_design
pip3 install sphinxext.opengraph
pip3 install sphinx-inline-tabs
pip3 install furo
```

