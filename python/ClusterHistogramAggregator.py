import os

class ClusterHistogramAggregator:

    def __init__(
        self,
        input_histograms = None,
        final_output_histogram = None,
        maximum_histograms_in_batch = 20,
        waitForJobs = True,
        sbatch_manager = None,
        auxDirName = None,
        script_file_name = None,
        log_file_name = None
    ):
        self.input_histograms = input_histograms
        self.final_output_histogram = final_output_histogram
        self.sbatch_manager = sbatch_manager
        self.maximum_histograms_in_batch = maximum_histograms_in_batch
        self.waitForJobs = waitForJobs
        self.auxDirName = auxDirName
        self.cfg_dir = os.path.dirname(script_file_name)
        self.log_dir = os.path.dirname(log_file_name)

    def create_output_histogram(
        self
    ):
        self.aggregate(
            input_histograms=self.input_histograms,
            final_output_histogram=self.final_output_histogram,
            maximum_histograms_in_batch=self.maximum_histograms_in_batch
        )

    def aggregate(
        self,
        input_histograms = None,
        final_output_histogram = None,
        maximum_histograms_in_batch = 20,
        level = 0
    ):

        # Log some info

        print("ClusterHistogramAggregator#aggregate(%s, %s, %s, %s)" % (
            input_histograms,
            final_output_histogram,
            maximum_histograms_in_batch,
            level
        ))

        # Create jobs for output files

        output_histograms = []
        current_job_id = 0

        while current_job_id * maximum_histograms_in_batch < len(input_histograms):
            start_pos = current_job_id * maximum_histograms_in_batch
            end_pos = start_pos + maximum_histograms_in_batch
            output_histogram = final_output_histogram.replace(
                ".root",
                "_%s-%s.root" % (level, current_job_id)
            )
            output_histograms.append(output_histogram)

            self.hadd_on_cluster_node(
                input_histograms = input_histograms[start_pos:end_pos],
                output_histogram = output_histogram
            )

            current_job_id = current_job_id + 1

        self.sbatch_manager.waitForJobs()

        # Aggregate output files

        if len(output_histograms) > maximum_histograms_in_batch:

            # Recursive call to method self

            self.aggregate(
                input_histograms = output_histograms,
                final_output_histogram = final_output_histogram,
                maximum_histograms_in_batch = maximum_histograms_in_batch,
                level = level + 1
            )

        else:

            # This is the last aggregation

            self.hadd_on_cluster_node(
                input_histograms=output_histograms,
                output_histogram=final_output_histogram
            )

            if self.waitForJobs:
                self.sbatch_manager.waitForJobs()

        # Delete output files produced by "intermediate" levels

        # for output_histogram in output_histograms:
        #    os.remove(output_histogram)

        return True

    def hadd_on_cluster_node(
        self,
        input_histograms = None,
        output_histogram = None,
    ):

        output_dir = self.auxDirName if self.auxDirName else os.path.dirname(output_histogram)

        print("ClusterHistogramAggregator#hadd_on_cluster_node(input_histograms=%s, output_histogram=%s, output_dir=%s)" % (
            input_histograms, output_histogram, output_dir))

        if not (input_histograms and output_histogram and output_dir):
            raise ValueError(
                'SBatchManager#hadd_on_cluster_node: All parameters not defined.')

        output_and_input_histograms = []
        output_and_input_histograms.append(os.path.basename(output_histogram))
        output_and_input_histograms.extend(input_histograms)
        ##print "output_and_input_histograms = ", output_and_input_histograms
        
        task_name = 'create_%s' % os.path.basename(output_histogram)
        scriptFile = os.path.join(self.cfg_dir, '%s.sh' % task_name)
        logFile = os.path.join(self.log_dir, '%s.log' % task_name)

        self.sbatch_manager.submitJob(
            inputFiles = input_histograms,
            executable = "hadd",
            command_line_parameter = " ".join(output_and_input_histograms),
            outputFilePath = os.path.dirname(output_histogram),
            outputFiles = [ os.path.basename(output_histogram) ],
            scriptFile = scriptFile,
            logFile = logFile,
            skipIfOutputFileExists = False,
            job_template_file = 'sbatch-node.template.hadd.sh'
        )
