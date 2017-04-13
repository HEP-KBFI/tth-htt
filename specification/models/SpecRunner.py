from ColorPrinter import *

class SpecRunner:

    def __init__(self):
        self.failed = []
        self.successful = []

    def run_specs(self, specs):
        for spec in specs:
            self.run_spec(spec)

    def run_spec(self, spec):
        print_header("SPEC:" + self.get_spec_name(spec))
        result = spec()
        if result:
            print_ok("PASSED:" + self.get_spec_name(spec))
            self.successful.append(spec)
        else:
            print_fail("FAILED:" + self.get_spec_name(spec))
            self.failed.append(spec)

    def print_summary(self):
        print_ok("\nPassed tests were:")
        print_ok(self.array_to_string_list(self.successful))

        print_fail("\nFailing tests were:")
        print_fail(self.array_to_string_list(self.failed))

        print_ok("Successful: %s" % len(self.successful))
        print_fail("Failed: %s" % len(self.failed))

    def get_spec_name(self, spec):
        return spec.__name__.replace("_", " ").capitalize()

    def array_to_string_list(self, specs):
        strings = []

        for spec in specs:
            strings.append("  * %s\n" % self.get_spec_name(spec))

        return " ".join(strings)
