
import specs
import models

spec_runner = models.SpecRunner()
spec_runner.run_specs([
    specs.call_histogram_aggregation_on_cluster_node_spec,
    specs.execute_command_on_cluster_node_spec,
    specs.executable_hadd_in_cluster_spec
])

spec_runner.print_summary()
