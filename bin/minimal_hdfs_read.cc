#include "tthAnalysis/HiggsToTauTau/interface/TFileOpenWrapper.h" // TFileOpenWrapper::, TFile
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper

#include <TTree.h>

#include <iostream>

/* in order to run this piece of code you must set environment variables in your current shell session as follows:

export CLASSPATH=`hadoop classpath --glob`
for j in $(ls /usr/lib/hadoop/client/*.jar); do export CLASSPATH=$CLASSPATH:$j; done

*/

int main(int argc, char **argv) {

    for(unsigned i = 0; i < 10; ++i)
    {
        const bool try_hdfs = i % 2 == 0;
        const std::string inputFileName = try_hdfs ?
           "hdfs:///local/karl/sandbox/tree_1.root" : "/hdfs/local/karl/sandbox/tree_2.root"
        ;
        TFile * f = TFileOpenWrapper::Open(inputFileName.c_str(), "read");
        TTree * t = static_cast<TTree *>(f -> Get("tree"));
        const unsigned n = t -> GetEntries();
        std::cout << "Read " << n << " events from " << inputFileName << '\n';
        TFileOpenWrapper::Close(f);
     }

    TTreeWrapper w("tree", {
      "/hdfs/local/karl/sandbox/tree_1.root",
      "hdfs:///local/karl/sandbox/tree_2.root"
    });
    std::cout << w.getFileCount() << '\n';
    while(w.hasNextEvent()) { }

    return 0;
}
