class SpecRunner:

    def __init__(self):
        self.failed = []
        self.successful = []

    def run_specs(self, specs):
        for spec in specs:
            self.run_spec(spec)

    def run_spec(self, spec):
        result = spec()
        if result:
            self.successful.append(spec)
        else:
            self.failed.append(spec)

    def print_summary(self):
        print("Successful: %s, Failed: %s" % (len(self.successful), len(self.failed)))
