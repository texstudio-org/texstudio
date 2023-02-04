# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'TeXstudio'
copyright = '2022, TeXstudio Team'
author = 'TeXstudio Team'
release = '4.5.2'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'myst_parser', # In order to use Markdown as source files (see
                   # https://www.sphinx-doc.org/en/master/usage/markdown.html)
    'sphinx.ext.todo',
    'sphinx.ext.mathjax',
    'sphinx.ext.extlinks',
    'sphinx_inline_tabs',
    'sphinx_design',
    'sphinxext.opengraph',
]

templates_path = ['_templates']
exclude_patterns = []

# The suffix(es) of source filenames.
# You can specify multiple suffix as a list of string:
#
# source_suffix = ['.rst', '.md']
source_suffix = {
    '.rst': 'restructuredtext',
    '.md': 'markdown',
}
myst_heading_anchors = 4
myst_enable_extensions = [
     "colon_fence",
     "deflist",
     "strikethrough",
]

# The name of the Pygments (syntax highlighting) style to use.
# pygments_style = 'monokai'
pygments_style = "sphinx"
pygments_dark_style = "monokai"

highlight_language = 'latex'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

#html_theme = 'alabaster'
#html_theme = 'pyramid'
html_theme = 'furo'

# Theme options are theme-specific and customize the look and feel of a theme
# further.  For a list of options available for each theme, see the
# documentation.
#
html_theme_options = {
    "navigation_with_keys": True,
}

# html_static_path = ['_static']

# Custom sidebar templates, must be a dictionary that maps document names
# to template names.
#
# The default sidebars (for documents that don't match any pattern) are
# defined by theme itself.  Builtin themes are using these templates by
# default: ``['localtoc.html', 'relations.html', 'sourcelink.html',
# 'searchbox.html']``.
#
# html_sidebars = {}

html_logo = '../../texstudio128x128.png'
html_favicon = '../../../texstudio.ico'

