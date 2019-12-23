import os.path

class ClusterHistogramAggregatorNonBlocking(object):

    def __init__(self,
        input_files,
        final_output_file,
        sbatch_manager,
        script_file_name,
        log_file_name,
        max_input_files_per_job = 10,
        auxDirName              = None,
     ):
        self.input_files             = input_files
        self.final_output_file       = final_output_file
        self.sbatch_manager          = sbatch_manager
        self.max_input_files_per_job = max_input_files_per_job
        self.auxDirName              = auxDirName
        self.cfg_dir                 = os.path.dirname(script_file_name)
        self.log_dir                 = os.path.dirname(log_file_name)
        self.batches                 = []

        self.create_jobs()

    def submit(self):
        if self.batches:
            next_batch = self.batches.pop(0)
            assert(next_batch)
            for job_args in next_batch:
                self.sbatch_manager.submitJob(**job_args)
            return True
        else:
            return False

    def is_done(self):
        if self.sbatch_manager.isDone():
            sent_jobs = self.submit()
            return not sent_jobs
        else:
            return False

    def create_jobs(self):
        self.batches = []
        level = 0
        input_files = self.input_files
        while True:
            current_batch = []
            output_files = []
            current_job_id = 0
            while current_job_id * self.max_input_files_per_job < len(input_files):
                if len(input_files) <= self.max_input_files_per_job:
                    # This is the last aggregation,
                    # the output file produced by this hadd job will be the final one
                    output_file = self.final_output_file
                else:
                    # This is not the last aggregation,
                    # this hadd job will produce a temporary output file
                    output_file = self.final_output_file.replace(
                        ".root",
                        "_{}-{}.root".format(level, current_job_id)
                    )
                output_files.append(output_file)

                task_name = 'ClusterHistogramAggregator_{}'.format(os.path.basename(output_file)).replace(".root", "")
                script_file = os.path.join(self.cfg_dir, '{}.sh'.format(task_name))
                log_file = os.path.join(self.log_dir, '{}.log'.format(task_name))

                start_pos = current_job_id * self.max_input_files_per_job
                end_pos   = start_pos + self.max_input_files_per_job
                current_batch.append(
                    self.prepare_job(
                        input_files = input_files[start_pos:end_pos],
                        output_file = output_file,
                        script_file = script_file,
                        log_file    = log_file,
                    )
                )
                current_job_id += 1

            assert(current_batch)
            self.batches.append(current_batch)
            if len(output_files) == 1:
                break
            else:
                print("ClusterHistogramAggregatorNonBlocking#create_jobs: created {} jobs at level {}".format(
                    len(current_batch), level
                ))
                input_files = output_files
                level += 1
        nof_jobs = sum(map(len, self.batches))
        print("ClusterHistogramAggregatorNonBlocking#create_jobs: created {} jobs in total".format(nof_jobs))

        return nof_jobs

    def prepare_job(self, input_files, output_file, script_file, log_file):
        output_dir = self.auxDirName if self.auxDirName else os.path.dirname(output_file)
        print("ClusterHistogramAggregatorNonBlocking#prepare_job(input_files={}, output_file={}, output_dir={})".format(
            input_files, output_file, output_dir
        ))

        output_and_input_files = [ os.path.basename(output_file) ] + input_files
        job_args = {
            'inputFiles'             : input_files,
            'executable'             : "hadd -cachesize 1GiB", # CV: use 1 Gb of cache memory to reduce random disk access
            'command_line_parameter' : " ".join(output_and_input_files),
            'outputFilePath'         : os.path.dirname(output_file),
            'outputFiles'            : [ os.path.basename(output_file) ],
            'scriptFile'             : script_file,
            'logFile'                : log_file,
            'skipIfOutputFileExists' : False,
            'job_template_file'      : 'sbatch-node.hadd.sh.template',
        }
        return job_args
