import codecs
import getpass
import jinja2
import logging
import os
import time
import subprocess
from datetime import date

from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd


# Template for wrapper that is ran on cluster node

current_dir = os.path.dirname(os.path.realpath(__file__))
job_template_file = current_dir + "/sbatch-node.template.sh"
job_template = open(job_template_file, 'r').read()


submit_job_version2_template_file = current_dir + \
    "/sbatch-node.submit_job_version2_template.sh"
submit_job_version2_template = open(
    submit_job_version2_template_file, 'r').read()

# Define SbatchManager

command_create_scratchDir = '/scratch/mkscratch'


class sbatchManager:
    """

    """

    def __init__(self):
        self.workingDir = None
        self.logFileDir = None
        # self.queue = "short" # maximum run-time of job = 2 hours
        self.queue = "main"  # maximum run-time of job = 2 days
        if os.environ.get('SBATCH_PRIORITY'):
            self.queue = os.environ.get('SBATCH_PRIORITY')
        self.command_submit = "sbatch"
        self.command_poll = "squeue"
        self.poll_interval = 30
        self.jobIds = []

    def setWorkingDir(self, workingDir):
        """Set path to CMSSW area in which jobs are executed
        """
        self.workingDir = workingDir

    def setLogFileDir(self, logFileDir):
        """Set path to directory in which log files are to be stored (matters only if 'logFile' parameter is not given when calling 'submitJob' method)
        """
        self.logFileDir = logFileDir

    def hadd_on_cluster_node(
        self,
        input_histograms=None,
        output_histogram=None,
        output_dir=None
        ):

        print("SBatchManager#hadd_on_cluster_node(input_histograms=%s, output_histogram=%s, output_dir=%s)" % (input_histograms, output_histogram, output_dir))

        if not (input_histograms and output_histogram and output_dir):
            raise ValueError('SBatchManager#hadd_on_cluster_node: All parameters not defined.')

        bash_command_template = '''

            # Create scratch dir for output root

            export SCRATCHED_OUTPUT_HISTOGRAM="$SCRATCH_DIR/{output_histogram}"
            export SCRATCHED_OUTPUT_HISTOGRAM_DIRECTORY="`dirname $SCRATCHED_OUTPUT_HISTOGRAM`"
            echo "SCRATCHED_OUTPUT_HISTOGRAM: $SCRATCHED_OUTPUT_HISTOGRAM"
            echo "SCRATCHED_OUTPUT_HISTOGRAM_DIRECTORY: $SCRATCHED_OUTPUT_HISTOGRAM_DIRECTORY"

            echo "Create scratch dir for output root: mkdir -p $SCRATCHED_OUTPUT_HISTOGRAM_DIRECTORY"
            mkdir -p $SCRATCHED_OUTPUT_HISTOGRAM_DIRECTORY


            # Create scratched histograms

            export SCRATCHED_INPUT_HISTOGRAMS=""
            export INPUT_HISTOGRAMS="{input_histograms}"
            export OUTPUT_HISTOGRAM="{output_histogram}"
            echo "Create scratched histograms for: $INPUT_HISTOGRAMS"

            for INPUT_HISTOGRAM in $INPUT_HISTOGRAMS; do

                SCRATCHED_INPUT_HISTOGRAM="$SCRATCH_DIR/$INPUT_HISTOGRAM"
                SCRATCHED_INPUT_HISTOGRAM_DIRECTORY="`dirname $SCRATCHED_INPUT_HISTOGRAM`"
                echo "SCRATCHED_INPUT_HISTOGRAM: $SCRATCHED_INPUT_HISTOGRAM"
                echo "SCRATCHED_INPUT_HISTOGRAM_DIRECTORY: $SCRATCHED_INPUT_HISTOGRAM"

                echo "Create parent dir: mkdir -p $SCRATCHED_INPUT_HISTOGRAM_DIRECTORY"
                mkdir -p $SCRATCHED_INPUT_HISTOGRAM_DIRECTORY

                echo "Copy histogram to scratch: cp -a $INPUT_HISTOGRAM $SCRATCHED_INPUT_HISTOGRAM_DIRECTORY"
                cp "$INPUT_HISTOGRAM" "$SCRATCHED_INPUT_HISTOGRAM_DIRECTORY"

                export SCRATCHED_INPUT_HISTOGRAMS="$SCRATCHED_INPUT_HISTOGRAMS $SCRATCHED_INPUT_HISTOGRAM"
            done

            # hadd

            echo "Create a new histogram: hadd $SCRATCHED_OUTPUT_HISTOGRAM $SCRATCHED_INPUT_HISTOGRAMS"
            hadd $SCRATCHED_OUTPUT_HISTOGRAM $SCRATCHED_INPUT_HISTOGRAMS


            # Store result in correct place

            OUTPUT_HISTOGRAM_DIRECTORY="`dirname $OUTPUT_HISTOGRAM`"
            echo "Make a directory for result root: mkdir -p $OUTPUT_HISTOGRAM_DIRECTORY"
            mkdir -p $OUTPUT_HISTOGRAM_DIRECTORY

            echo "Copy result from scratch to /home: cp $SCRATCHED_OUTPUT_HISTOGRAM $OUTPUT_HISTOGRAM_DIRECTORY"
            cp $SCRATCHED_OUTPUT_HISTOGRAM $OUTPUT_HISTOGRAM_DIRECTORY


            # Cleanup will be automatic

            echo "Cleanup will be automatic"
        '''

        bash_command = bash_command_template.format(
            input_histograms = " ".join(input_histograms),
            output_histogram = output_histogram
        )

        self.submit_job_version2(
            task_name = 'create_%s' % output_histogram,
            command = bash_command,
            output_dir = output_dir
        )

    def submitJob(self, inputFiles, executable, cfgFile, outputFilePath, outputFiles, logFile=None, skipIfOutputFileExists=False):
        """Waits for all sbatch jobs submitted by this instance of sbatchManager to finish processing
        """

        # raise if logfile missing
        if not logFile:
            if not self.logFileDir:
                raise ValueError(
                    "Please call 'setLogFileDir' before calling 'submitJob' !!")
            logFile = os.path.join(self.logFileDir, os.path.basename(
                script_file).replace(".sh", ".log"))

        # if any of the output files exists, returns (Margus: BUG? Because only
        # that file should be skipped, not all?)
        if skipIfOutputFileExists:
            for outputFile in outputFiles:
                if os.path.exists(os.path.join(outputFilePath, outputFile)):
                    print "output file = '%s' exists --> skipping !!" % os.path.join(outputFilePath, outputFile)
                    return

        if not self.workingDir:
            raise ValueError(
                "Please call 'setWorkingDir' before calling 'submitJob' !!")

        # create scratch dir
        scratchDir = "/scratch/%s" % getpass.getuser()
        if not os.path.exists(scratchDir):
            print "Directory '%s' does not yet exist, creating it !!" % scratchDir
            run_cmd(command_create_scratchDir)
        scratchDir = os.path.join(
            scratchDir, "tthAnalysis" + "_" + date.today().isoformat())
        create_if_not_exists(scratchDir)

        # create script for executing jobs
        script_file = cfgFile.replace(".py", ".sh")
        script_file = script_file.replace("_cfg", "")

        wrapper_log_file = logFile.replace('.log', '_wrapper.log')
        executable_log_file = logFile.replace('.log', '_executable.log')

        command = "%s --partition=%s --output=%s %s" % (
            self.command_submit, self.queue, wrapper_log_file, script_file)

        script = jinja2.Template(job_template).render(
            working_dir=self.workingDir,
            scratch_dir=scratchDir,
            exec_name=executable,
            cfg_file=cfgFile,
            inputFiles=" ".join(inputFiles),
            outputDir=outputFilePath,
            outputFiles=" ".join(outputFiles),
            wrapper_log_file=wrapper_log_file,
            executable_log_file=executable_log_file,
            RUNNING_COMMAND=command
        )
        print "writing sbatch script file = '%s'" % script_file
        with codecs.open(script_file, "w", "utf-8") as f:
            f.write(script)

        print "<submitJob>: command = %s" % command
        run_cmd_output = run_cmd(command)
        print "run_cmd_output: %s" % run_cmd_output
        ret_val = run_cmd_output.split()[-1]
        print "ret_val: %s" % ret_val
        job_id = ret_val.split()[-1]
        # print " jobId = %s" % jobId
        self.jobIds.append(job_id)

    def submit_job_version2(
        self,
        task_name=None,
        command=None,
        output_dir=None
    ):

        '''
            This method is similar to submitJob, but has less required parameters.
            Supports multiple lines of Bash commands instead of fixed oneliner.
        '''

        print("SBatchManager#hadd_on_cluster_node(task_name=%s, command=%s, output_dir=%s)" % (task_name, command, command))

        if not self.workingDir:
            raise ValueError(
                "Please call 'setWorkingDir' before calling 'submitJob' !!")

        scratch_dir = self.get_scratch_dir()

        # Create script for executing jobs

        script_file = output_dir + "/cfgs/" + task_name + ".sh"
        wrapper_log_file = output_dir + "/logs/" + task_name + "_wrapper.log"
        executable_log_file = output_dir + "/logs/" + task_name + "_executable.log"

        run_cmd("mkdir -p '%s'" % (output_dir + "/cfgs/"))
        run_cmd("mkdir -p '%s'" % (output_dir + "/logs/"))

        sbatch_command = "%s --partition=%s --output=%s %s" % (
            self.command_submit, # "sbatch"
            self.queue,
            wrapper_log_file,
            script_file
        )

        script = jinja2.Template(submit_job_version2_template).render(
            command=command,
            working_dir=self.workingDir,
            scratch_dir=scratch_dir,
            wrapper_log_file=wrapper_log_file,
            executable_log_file=executable_log_file,
            sbatch_command=sbatch_command
        )
        print "writing sbatch script file = '%s'" % script_file
        with codecs.open(script_file, "w", "utf-8") as f:
            f.write(script)


        # Run command

        sbatch_command_result = run_cmd(sbatch_command)
        job_id = sbatch_command_result.split()[-1]
        self.jobIds.append(job_id)

    def get_scratch_dir(self):
        scratch_dir = "/scratch/%s" % getpass.getuser()
        if not os.path.exists(scratch_dir):
            print "Directory '%s' does not yet exist, creating it !!" % scratch_dir
            run_cmd(command_create_scratchDir)
        scratch_dir = os.path.join(
            scratch_dir,
            "tthAnalysis" + "_" + date.today().isoformat()
        )
        create_if_not_exists(scratch_dir)
        return scratch_dir

    def waitForJobs(self):
        """Waits for all sbatch jobs submitted by this instance of sbatchManager to finish processing
        """
        numJobs = len(self.jobIds)
        # print "<waitForJobs>: numJobs = %i" % numJobs
        if numJobs > 0:
            jobIds_per_poll_group = 500
            num_poll_groups = numJobs / jobIds_per_poll_group
            if (numJobs % jobIds_per_poll_group) > 0:
                num_poll_groups = num_poll_groups + 1
            whoami = getpass.getuser()
            while True:
                numJobs_left = 0
                for idx_poll_group in range(num_poll_groups):
                    idx_first = idx_poll_group * jobIds_per_poll_group
                    idx_last = min((idx_poll_group + 1) *
                                   jobIds_per_poll_group, numJobs)
                    jobIds_poll_group = self.jobIds[idx_first:idx_last]
                    command = "%s -u %s | grep \"%s\" | wc -l" % (
                        self.command_poll, whoami, "\\|".join(jobIds_poll_group))
                    # print "idx_poll_group = %i: command = %s" %
                    # (idx_poll_group, command)
                    poll_result = run_cmd(command, True).rstrip("\n")
                    # print " poll_result = %s" % poll_result
                    numJobs_left = numJobs_left + int(poll_result)
                    time.sleep(1)
                # print "numJobs_left = %i" % numJobs_left
                if numJobs_left > 0:
                    time.sleep(self.poll_interval)
                else:
                    break
                logging.info(
                    "Waiting for sbatch to finish (%d jobs still left) ..." % numJobs_left)
