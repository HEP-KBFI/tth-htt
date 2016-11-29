
import specs
import models

spec_runner = models.SpecRunner()
spec_runner.run_specs([
    specs.call_histogram_aggregation_on_cluster_node,
    specs.execute_command_on_cluster_node_spec
])

spec_runner.print_summary()
