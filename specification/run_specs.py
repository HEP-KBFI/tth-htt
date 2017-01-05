
import specs
import models

spec_runner = models.SpecRunner()
spec_runner.run_specs([
    specs.call_histogram_aggregation_on_cluster_node_spec,
    specs.call_histogram_aggregation_on_cluster_node_with_invalid_input_spec
    specs.execute_command_on_cluster_node_spec,
    specs.executable_hadd_in_cluster_spec,
    specs.check_that_histograms_are_valid_spec,
    specs.check_that_histograms_are_valid_with_missing_input_histogram_spec,
    specs.check_that_histograms_are_equal_spec,
    specs.check_that_histograms_are_equal_with_unequal_data
])

spec_runner.print_summary()
