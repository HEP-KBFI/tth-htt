import os

class ClusterHistogramAggregator:

    def __init__(
        self,
        input_files = None,
        final_output_file = None,
        max_input_files_per_job = 10,
        waitForJobs = True,
        sbatch_manager = None,
        auxDirName = None,
        script_file_name = None,
        log_file_name = None
     ):
        self.input_files = input_files
        self.final_output_file = final_output_file
        self.sbatch_manager = sbatch_manager
        self.max_input_files_per_job = max_input_files_per_job
        self.waitForJobs = waitForJobs
        self.auxDirName = auxDirName
        self.cfg_dir = os.path.dirname(script_file_name)
        self.log_dir = os.path.dirname(log_file_name)

    def create_output_file(
        self
    ):
        self.aggregate(
            input_files = self.input_files,
            final_output_file = self.final_output_file,
            max_input_files_per_job = self.max_input_files_per_job
        )

    def aggregate(
        self,
        input_files = None,
        final_output_file = None,
        max_input_files_per_job = 10,
        level = 0
    ):

        # Log some info

        print("ClusterHistogramAggregator#aggregate(%s, %s, %s, %s)" % (
            input_files,
            final_output_file,
            max_input_files_per_job,
            level
        ))

        # Create jobs for output files

        output_files = []
        current_job_id = 0

        while current_job_id * max_input_files_per_job < len(input_files):
            start_pos = current_job_id * max_input_files_per_job
            end_pos = start_pos + max_input_files_per_job
            output_file = None
            if len(input_files) <= max_input_files_per_job:
                # This is the last aggregation,
                # the output file produced by this hadd job will be the final one
                output_file = final_output_file
            else:
                # This is not the last aggregation,
                # this hadd job will produce a temporary output file
                output_file = final_output_file.replace(
                    ".root",
                    "_%s-%s.root" % (level, current_job_id)
                )
            output_files.append(output_file)

            task_name = 'ClusterHistogramAggregator_%s' % os.path.basename(output_file)
            task_name = task_name.replace(".root", "")
            script_file = os.path.join(self.cfg_dir, '%s.sh' % task_name)
            log_file = os.path.join(self.log_dir, '%s.log' % task_name)

            self.hadd_on_cluster_node(
                input_files = input_files[start_pos:end_pos],
                output_file = output_file,
                script_file = script_file,
                log_file = log_file
            )

            current_job_id = current_job_id + 1

        self.sbatch_manager.waitForJobs()

        # Aggregate output files

        if len(output_files) > 1:

            # Recursive call to method self

            self.aggregate(
                input_files = output_files,
                final_output_file = final_output_file,
                max_input_files_per_job = max_input_files_per_job,
                level = level + 1
            )

        # Delete output files produced by "intermediate" levels

        # for output_file in output_files:
        #    os.remove(output_file)

        return True

    def hadd_on_cluster_node(
        self,
        input_files = None,
        output_file = None,
        script_file = None,
        log_file = None
    ):

        output_dir = self.auxDirName if self.auxDirName else os.path.dirname(output_file)

        print("ClusterHistogramAggregator#hadd_on_cluster_node(input_files=%s, output_file=%s, output_dir=%s)" % (
            input_files, output_file, output_dir))

        if not (input_files and output_file and output_dir):
            raise ValueError(
                'SBatchManager#hadd_on_cluster_node: All parameters not defined.')

        output_and_input_files = []
        output_and_input_files.append(os.path.basename(output_file))
        output_and_input_files.extend(input_files)
        ##print "output_and_input_files = ", output_and_input_files

        self.sbatch_manager.submitJob(
            inputFiles = input_files,
            executable = "hadd -cachesize 1GiB", # CV: use 1 Gb of cache memory to reduce random disk access
            command_line_parameter = " ".join(output_and_input_files),
            outputFilePath = os.path.dirname(output_file),
            outputFiles = [ os.path.basename(output_file) ],
            scriptFile = script_file,
            logFile = log_file,
            skipIfOutputFileExists = False,
            job_template_file = 'sbatch-node.hadd.sh.template',
            skip_copy = 0,
        )
