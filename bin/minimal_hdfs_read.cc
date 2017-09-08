#include "tthAnalysis/HiggsToTauTau/interface/TFileOpenWrapper.h" // TFileOpenWrapper::, TFile

#include <TTree.h>

#include <iostream>

/* in order to run this piece of code you must set environment variables in your current shell session as follows:

export CLASSPATH=`hadoop classpath --glob`
for j in $(ls /usr/lib/hadoop/client/*.jar); do export CLASSPATH=$CLASSPATH:$j; done

*/

int main(int argc, char **argv) {

    const bool try_hdfs = true;
    TFile * f = try_hdfs ? TFileOpenWrapper::Open("hdfs:///local/karl/sandbox/tree_1.root", "read") :
                           TFileOpenWrapper::Open("/hdfs/local/karl/sandbox/tree_1.root", "read")
    ;
    TTree * t = static_cast<TTree *>(f -> Get("tree"));
    const unsigned n = t -> GetEntries();
    std::cout << "Read " << n <<" events\n";
    delete f;

    return 0;
}
