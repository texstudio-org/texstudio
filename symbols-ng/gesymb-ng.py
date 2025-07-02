#!/usr/bin/env python3

import os
import subprocess
import xml.etree.ElementTree as ET
from PIL import Image, ImageDraw, ImageFont
import sys

class Package:
    def __init__(self, name="", arguments=""):
        self.name = name
        self.arguments = arguments

class Command:
    def __init__(self):
        self.unicodeCommand = ""
        self.comment = ""
        self.latexCommand = ""
        self.unicodePackages = []
        self.packages = []
        self.mathMode = False
        self.forcePNG = False
        self.iconMode = False
        self.name = ""
        self.ImageCommand = ""

class Preamble:
    def __init__(self):
        self.classArguments = ""
        self.className = ""
        self.additional = ""

class Version:
    def __init__(self):
        self.major = ""
        self.minor = ""

def read_image_comments(file_name):
    try:
        image = Image.open(file_name)
        print(f"Image {file_name} has Command _{image.info.get('Command', '')}_")
        print(f"Image {file_name} has Comment _{image.info.get('Comment', '')}_")
        print(f"Image {file_name} has Package _{image.info.get('Packages', '')}_")
        print(f"Image {file_name} has CommandUnicode _{image.info.get('CommandUnicode', '')}_")
        print(f"Image {file_name} has UnicodePackages _{image.info.get('UnicodePackages', '')}_")
    except Exception as e:
        print(f"===readComment=== ERROR {file_name} could not be loaded: {e}")

def convert_utf8_to_latin1_string(string):
    string_as_latin1 = ""
    for char in string:
        string_as_latin1 += f"U+{ord(char):04X},"
    return string_as_latin1[:-1]

def pkg_list_to_string(packages):
    packages_arg = ",".join([pkg.arguments for pkg in packages if pkg.arguments])
    packages_name = ",".join([pkg.name for pkg in packages if pkg.name])
    result = ""
    if packages_arg:
        result += f"[{packages_arg}]"
    if packages_name:
        result += f"{{{packages_name}}}"
    return result

def write_svg_comments(cmd, file_name):
    unicode_command_as_latin1 = convert_utf8_to_latin1_string(cmd.unicodeCommand) if cmd.unicodeCommand else ""
    comment_as_latin1 = convert_utf8_to_latin1_string(cmd.comment) if cmd.comment else ""

    print("fileName is", file_name)
    print("Command is", cmd.latexCommand)
    print("unicodeCommandAsLatin1 is", unicode_command_as_latin1)
    print("commentAsLatin1 is", comment_as_latin1)
    print("comment is", cmd.comment)

    try:
        with open(file_name, 'r') as file:
            file_content = file.readlines()

        with open(file_name, 'w') as file:
            for line in file_content:
                if line.strip().startswith("<defs>"):
                    command = cmd.latexCommand.replace("<", "&lt;")
                    file.write(f"<title>{command}</title>\n")
                    additional = ""
                    if comment_as_latin1:
                        additional += f" Comment='{comment_as_latin1}'"
                    if unicode_command_as_latin1:
                        additional += f" CommandUnicode='{unicode_command_as_latin1}'"
                        additional += f" UnicodePackages='{pkg_list_to_string(cmd.unicodePackages)}'"
                    file.write(f"<desc Packages='{pkg_list_to_string(cmd.packages)}'{additional}/>\n")
                file.write(line)
            file.write("\n")
    except Exception as e:
        print(f"Error writing SVG comments: {e}")

def read_svg(file_name):
    try:
        tree = ET.parse(file_name)
        root = tree.getroot()
        if root.tag != "svg":
            print("wrong format")
            return -3

        title = ET.Element("title")
        title.text = "title"
        root.append(title)

        tree.write(file_name)
        return 0
    except Exception as e:
        print(f"Error reading SVG: {e}")
        return -2

def generate_svg(latex_file, index, symbol_group_name):
    texfile = "temp.tex"
    texfile_without_suffix = "temp"
    if symbol_group_name == "fontawesome5":
        svgfile = f"img{index:04d}fontawesome5.svg"
    elif index > 0:
        svgfile = f"img{index:03d}{symbol_group_name}.svg"
    else:
        svgfile = f"{symbol_group_name}.svg"

    with open(texfile, 'w', encoding='utf-8') as file:
        file.write(latex_file)

    texcommand = f"latex -interaction=batchmode {texfile}"
    dvipngcommand = f"dvisvgm -n -j --bbox=papersize --scale=32bp/h --zoom=-1 -O -o {svgfile} {texfile_without_suffix}.dvi"

    print(texcommand)
    print(dvipngcommand)

    latexret = subprocess.call(texcommand, shell=True)
    dvipngret = subprocess.call(dvipngcommand, shell=True)

    if latexret:
        print("Error compiling the latex file")
        return ""
    if dvipngret:
        print("Error producing the pngs")
        return ""

    return svgfile

def write_image_comments(cmd, file_name):
    try:
        image = Image.open(file_name)
        unicode_command_as_latin1 = convert_utf8_to_latin1_string(cmd.unicodeCommand) if cmd.unicodeCommand else ""
        comment_as_latin1 = convert_utf8_to_latin1_string(cmd.comment) if cmd.comment else ""

        print("fileName is", file_name)
        print("Command is", cmd.latexCommand)
        print("unicodeCommandAsLatin1 is", unicode_command_as_latin1)
        print("commentAsLatin1 is", comment_as_latin1)
        print("comment is", cmd.comment)

        image.info["Command"] = cmd.latexCommand
        if unicode_command_as_latin1:
            image.info["CommandUnicode"] = unicode_command_as_latin1
            image.info["UnicodePackages"] = pkg_list_to_string(cmd.unicodePackages)
        if comment_as_latin1:
            image.info["Comment"] = comment_as_latin1
        image.info["Packages"] = pkg_list_to_string(cmd.packages)

        image.save(file_name, "PNG")
    except Exception as e:
        print(f"===writeComment=== ERROR {file_name} could not be loaded: {e}")

def generate_png(latex_file, index, symbol_group_name, batik_convert):
    texfile = "temp.tex"
    texfile_without_suffix = "temp"
    if symbol_group_name == "fontawesome5":
        pngfile = f"img{index:04d}fontawesome5.png"
    elif index > 0:
        pngfile = f"img{index:03d}{symbol_group_name}.png"
    else:
        pngfile = f"{symbol_group_name}.png"

    with open(texfile, 'w', encoding='utf-8') as file:
        file.write(latex_file)

    texcommand = f"latex -interaction=batchmode {texfile}"
    dvipngcommand = f"dvisvgm -n -j --bbox=papersize --scale=32bp/h --zoom=-1 -O -o {texfile_without_suffix}.svg {texfile_without_suffix}.dvi"
    convert_command = f"{batik_convert} {texfile_without_suffix}.svg {pngfile}"
    remove_command = f"rm {texfile_without_suffix}.svg"

    print(texcommand)
    print(dvipngcommand)
    print(convert_command)

    latexret = subprocess.call(texcommand, shell=True)
    dvipngret = subprocess.call(dvipngcommand, shell=True)
    convertret = subprocess.call(convert_command, shell=True)
    rmret = subprocess.call(remove_command, shell=True)

    if latexret:
        print("Error compiling the latex file")
        return ""
    if dvipngret:
        print("Error producing the svg")
        return ""
    if convertret:
        print("Error converting svg to png")
        return ""
    if rmret:
        print("Error removing svg")
        return ""

    return pngfile

def generate_latex_file(preamble, cmd):
    output = f"\\documentclass[{preamble.classArguments}]{{{preamble.className}}}\n"
    output += preamble.additional + '\n'

    for pkg in cmd.packages:
        if pkg.arguments:
            output += f"\\usepackage[{pkg.arguments}]{{{pkg.name}}}\n"
        else:
            output += f"\\usepackage{{{pkg.name}}}\n"

    if not cmd.iconMode:
        output += "\\usepackage{calc}\n"
        output += "\\newcommand{\\sqbox}[1]{\\rule[\\widthof{#1} * \\real{-0.3}]{0bp}{\\widthof{#1}}#1}\n"

    output += "\\begin{document}\n"
    cmd_string = cmd.ImageCommand if cmd.ImageCommand else cmd.latexCommand

    if cmd.mathMode:
        cmd_string = f"\\ensuremath{{{cmd_string}}}"

    if not cmd.iconMode:
        cmd_string = f"\\sqbox{{{cmd_string}}}\\strut"

    output += cmd_string + '\n'
    output += "\\end{document}\n"

    return output

def get_all_packages(e):
    packages = []
    for child in e:
        if child.tag == "package":
            pkg = Package()
            pkg.name = child.findtext("name","")
            pkg.arguments = child.findtext("arguments","")
            packages.append(pkg)
            print("pkg.name is", pkg.name)
            print("pkg.arguments is", pkg.arguments)
    return packages

def get_command_definition(e, unicode_packages):
    cmd = Command()
    cmd.unicodePackages = unicode_packages
    cmd.packages = get_all_packages(e)
    cmd.mathMode = e.findtext("mathMode","") == "true"
    cmd.forcePNG = e.findtext("forcePNG","") == "true"
    cmd.iconMode = e.findtext("iconMode","") == "true"
    cmd.name = e.findtext("name","")
    cmd.comment = e.findtext("comment","")
    cmd.latexCommand = e.findtext("latexCommand","")
    cmd.unicodeCommand = e.findtext("unicodeCommand","")
    cmd.ImageCommand = e.findtext("imageCommand","")

    print(f"cmd: latexCommand={cmd.latexCommand}, unicodeCommand={cmd.unicodeCommand}, imageCommand={cmd.ImageCommand}, comment={cmd.comment}, mathmode={cmd.mathMode}")

    if cmd.packages:
        print("packages are")
        for pkg in cmd.packages:
            print(f"name={pkg.name}, arguments={pkg.arguments}")
    else:
        print("no packages to include")

    return cmd

def usage():
    print("usage: gesymb-ng mySymbols.xml path/to/batikConvert")
    sys.exit(1)

def main():
    if len(sys.argv) < 3:
        usage()

    file_name = sys.argv[1]
    batik = sys.argv[2]

    try:
        tree = ET.parse(file_name)
        root = tree.getroot()

        if root.tag != "symbols":
            print("wrong format")
            return -3

        preamble = Preamble()
        version = Version()
        commands = []
        symbol_group_name = ""
        unicode_pkg_list = []

        for child in root:
            if child.tag == "formatVersion":
                version.major = child.get("major")
                version.minor = child.get("minor")
            elif child.tag == "symbolGroupName":
                symbol_group_name = child.text
            elif child.tag == "preamble":
                preamble.className = child.findtext("class","")
                preamble.classArguments = child.findtext("arguments","")
                preamble.additional = child.findtext("additional","")

                print("class is", preamble.className)
                print("arguments is", preamble.classArguments)
                print("additional is", preamble.additional)
            elif child.tag == "unicodeCommandPackages":
                unicode_pkg_list = get_all_packages(child)
            elif child.tag == "commandDefinition":
                commands.append(get_command_definition(child, unicode_pkg_list))
            else:
                print(f"unexpected node: {child.tag}")

        for i, cmd in enumerate(commands):
            content = generate_latex_file(preamble, cmd)
            print(content)
            if cmd.forcePNG:
                if not cmd.name:
                    pngfile = generate_png(content, i + 1, symbol_group_name, batik)
                else:
                    pngfile = generate_png(content, -1, cmd.name, batik)
                write_image_comments(cmd, pngfile)
            else:
                if not cmd.name:
                    svgfile = generate_svg(content, i + 1, symbol_group_name)
                else:
                    svgfile = generate_svg(content, -1, cmd.name)
                write_svg_comments(cmd, svgfile)

    except Exception as e:
        print(f"Error: {e}")
        return -1

if __name__ == "__main__":
    main()
