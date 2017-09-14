#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h"

#include "tthAnalysis/HiggsToTauTau/interface/TFileOpenWrapper.h" // TFileOpenWrapper::
#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception

#include <TTree.h> // TTree
#include <iostream> // std::cout

TTreeWrapper::TTreeWrapper()
  : TTreeWrapper("", {})
{}

TTreeWrapper::TTreeWrapper(const std::string & treeName,
                           const std::vector<std::string> & fileNames,
                           long long maxEvents)
  : currentFileIdx_(0)
  , currentEventIdx_(0)
  , currentMaxEvents_(-1)
  , currentMaxEventIdx_(0)
  , maxEvents_(maxEvents)
  , currentFilePtr_(nullptr)
  , currentTreePtr_(nullptr)
  , treeName_(treeName)
  , fileNames_(fileNames)
  , fileCount_(fileNames_.size())
  , cumulativeMaxEventCount_(0)
  , eventCount_(-1)
{
  if(! treeName_.empty())
  {
    std::cout << "Setting TTree name to: " << treeName_ << '\n';
  }
  else
  {
    throw cms::Exception("TTreeWrapper") << "Empty input TTree name given\n";
  }
  if(fileCount_)
  {
    for(std::size_t i = 0; i < fileNames_.size(); ++i)
    {
      std::cout << "Adding file #" << i << ": " << fileNames_[i] << '\n';
    }
  }
  else
  {
    throw cms::Exception("TTreeWrapper") << "No input files given\n";
  }
}

TTreeWrapper::~TTreeWrapper()
{
  close();
}

int
TTreeWrapper::getFileCount() const
{
  return fileCount_;
}

long long
TTreeWrapper::getCurrentMaxEventIdx() const
{
  return currentMaxEventIdx_;
}

long long
TTreeWrapper::getCumulativeMaxEventCount() const
{
  return cumulativeMaxEventCount_;
}

int
TTreeWrapper::getProcessedFileCount() const
{
  return currentMaxEventIdx_ > 0 ? currentFileIdx_ + 1 : 0;
}

long long
TTreeWrapper::getCurrentEventIdx() const
{
  return currentEventIdx_;
}

bool
TTreeWrapper::canReport(unsigned reportEvery) const
{
  return currentMaxEventIdx_ > 0 && (currentMaxEventIdx_ % reportEvery) == 0;
}

bool
TTreeWrapper::isOpen() const
{
  return !! currentFilePtr_;
}

std::string
TTreeWrapper::getCurrentFileName() const
{
  return fileNames_[currentFileIdx_];
}

TTreeWrapper &
TTreeWrapper::registerReader(ReaderBase * reader)
{
  readers_.push_back(reader);
  return *this;
}

bool
TTreeWrapper::hasNextEvent()
{
  // check if we already have an open file
  if(! isOpen())
  {
    // try to open the file
    if(currentFileIdx_ < fileCount_)
    {
      std::cout << "Opening #" << currentFileIdx_ << " file " << fileNames_[currentFileIdx_] << '\n';
      currentFilePtr_ = TFileOpenWrapper::Open(fileNames_[currentFileIdx_].c_str(), "READ");
    }
    else
    {
      // we are out of files
      return false;
    }

    if(! isOpen())
    {
      throw cms::Exception("TTreeWrapper")
        << "The file '" << fileNames_[currentFileIdx_] << "' failed to open\n";
    }
    if(currentFilePtr_ -> IsZombie())
    {
      throw cms::Exception("TTreeWrapper")
        << "The file '" << fileNames_[currentFileIdx_] << "' appears to be corrupted\n";
    }
  }

  // we should have an open file right now
  if(! currentTreePtr_)
  {
    // attempt to read the TTree
    currentTreePtr_ = static_cast<TTree *>(currentFilePtr_ -> Get(treeName_.c_str()));

    if(! currentTreePtr_)
    {
      throw cms::Exception("TTreeWrapper")
        << "The file '" << fileNames_[currentFileIdx_] << "' does not have a TTree named "
        << treeName_ << '\n';
    }

    // set the branch addresses
    for(ReaderBase * reader: readers_)
    {
      reader -> setBranchAddresses(currentTreePtr_);
    }

    // save the total number of events in this file
    currentMaxEvents_ = currentTreePtr_ -> GetEntries();
    cumulativeMaxEventCount_ += currentMaxEvents_;
  }

  const bool belowMaxEvents = (maxEvents_ == -1 || currentMaxEventIdx_ < maxEvents_);
  if(currentEventIdx_ < currentMaxEvents_ && belowMaxEvents)
  {
    // we still have some events to be read here
    ++currentEventIdx_;
    ++currentMaxEventIdx_;
    currentTreePtr_ -> GetEntry(currentEventIdx_);
  }
  else
  {
    // we have to close the current file switch to a new one
    close();
    ++currentFileIdx_;

    return belowMaxEvents ? hasNextEvent() : false;
  }

  return true;
}

void
TTreeWrapper::close()
{
  if(currentFilePtr_)
  {
    std::cout << "Closing " << fileNames_[currentFileIdx_] << '\n';
    TFileOpenWrapper::Close(currentFilePtr_);
    currentTreePtr_ = nullptr;
    currentMaxEvents_ = -1;
    currentEventIdx_  =  0;
  }
}

long long
TTreeWrapper::getEventCount() const
{
  // we have to open the files one-by-one and get the event counts
  // in each file separately
  if(eventCount_ < 0)
  {
    long long totalNofEvents = 0;
    for(const std::string & fileName: fileNames_)
    {
      TFile * filePtr = TFileOpenWrapper::Open(fileName.c_str(), "READ");
      if(! filePtr)
      {
        throw cms::Exception("TTreeWrapper") << "Could not open file " << fileName << '\n';
      }
      if(filePtr -> IsZombie())
      {
        throw cms::Exception("TTreeWrapper")
          << "The file '" << fileName << "' appears to be a zombie\n";
      }
      TTree * treePtr = static_cast<TTree *>(filePtr -> Get(treeName_.c_str()));
      if(! treePtr)
      {
        throw cms::Exception("TTreeWrapper")
          << "The file '" << fileName << "' does not have a TTree named " << treeName_ << '\n';
      }
      totalNofEvents += treePtr -> GetEntries();

      TFileOpenWrapper::Close(filePtr);
    }
    eventCount_ = totalNofEvents;
  }
  return eventCount_;
}
