
from specs.call_histogram_aggregation_on_cluster_node import call_histogram_aggregation_on_cluster_node
from specs.execute_command_on_cluster_node_spec import execute_command_on_cluster_node_spec
from models import *


spec_runner = SpecRunner()
spec_runner.run_specs([
    call_histogram_aggregation_on_cluster_node,
    execute_command_on_cluster_node_spec
])

spec_runner.print_summary()
