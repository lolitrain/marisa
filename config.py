import ConfigParser

parser = ConfigParser.RawConfigParser()
parser.read(["default.cfg"])

def getint(section, option):
    return parser.getint(section, option)

def getbool(section, option):
    return parser.getboolean(section, option)


def read(filename):
    try:
        parser.readfp(open(filename))
    except:
        pass

def save(filename):
    fp = open(filename, "w")
    fp.write("# Automatically generated file\n")
    fp.write("# Do not modify\n")
    parser.write(fp)
