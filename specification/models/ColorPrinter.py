OK = '\033[92m'
FAIL = '\033[91m'
BLUE = '\033[94m'
BOLD = '\033[1m'
CLEAR = '\033[0m'

def print_ok(string):
    print(OK + string + CLEAR)

def print_fail(string):
    print(FAIL + string + CLEAR)

def print_header(string):
    print(BOLD + BLUE + string + CLEAR)
