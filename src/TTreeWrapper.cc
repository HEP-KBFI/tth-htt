#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h"

#include "tthAnalysis/HiggsToTauTau/interface/TFileOpenWrapper.h" // TFileOpenWrapper::
#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TTree.h> // TTree
#include <TFile.h> // TFile

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
  , basketSize_(-1)
{
  if(! treeName_.empty())
  {
    std::cout << "Setting TTree name to: " << treeName_ << '\n';
  }
  else
  {
    throw cmsException(this) << "Empty input TTree name given";
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
    throw cmsException(this) << "No input files given";
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
  return currentMaxEventIdx_ > 0 ? currentFileIdx_ + (!!currentFilePtr_ ? 1 : 0) : 0;
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
#if 0
      currentFilePtr_ = TFileOpenWrapper::Open(fileNames_[currentFileIdx_].c_str(), "READ");
#else
      currentFilePtr_ = TFile::Open(fileNames_[currentFileIdx_].c_str(), "READ");
#endif
    }
    else
    {
      // we are out of files
      return false;
    }

    if(! isOpen())
    {
      throw cmsException(this, __func__)
        << "The file '" << fileNames_[currentFileIdx_] << "' failed to open";
    }
    if(currentFilePtr_ -> IsZombie())
    {
      throw cmsException(this, __func__)
        << "The file '" << fileNames_[currentFileIdx_] << "' appears to be corrupted";
    }
  }

  // we should have an open file right now
  if(! currentTreePtr_)
  {
    // attempt to read the TTree
    currentTreePtr_ = static_cast<TTree *>(currentFilePtr_ -> Get(treeName_.c_str()));

    if(! currentTreePtr_)
    {
      throw cmsException(this, __func__)
        << "The file '" << fileNames_[currentFileIdx_] << "' does not have a TTree named "
        << treeName_;
    }

    // set the basket size different than what the default is only if the user has requested so
    if(basketSize_ > 0)
    {
      currentTreePtr_->SetBasketSize("*", basketSize_);
    }
    // set the branch addresses
    for(ReaderBase * reader: readers_)
    {
      reader -> setBranchAddresses(currentTreePtr_);
    }

    // save the total number of events in this file
    const long long currentMaxEvents = currentTreePtr_ -> GetEntries();
    std::cout << "The file " << fileNames_[currentFileIdx_] << " has " << currentMaxEvents << " entries\n";
    currentMaxEvents_ = currentMaxEvents;
    cumulativeMaxEventCount_ += currentMaxEvents_;
  }

  const bool belowMaxEvents = (maxEvents_ == -1 || currentMaxEventIdx_ < maxEvents_);
  if(currentEventIdx_ < currentMaxEvents_ && belowMaxEvents)
  {
    // we still have some events to be read here
    currentTreePtr_ -> GetEntry(currentEventIdx_);
    ++currentEventIdx_;
    ++currentMaxEventIdx_;
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

TTree *
TTreeWrapper::getCurrentTree() const
{
  return currentTreePtr_;
}

void
TTreeWrapper::setBasketSize(int basketSize)
{
  basketSize_ = basketSize;
}

void
TTreeWrapper::close()
{
  if(currentFilePtr_)
  {
    std::cout << "Closing " << fileNames_[currentFileIdx_] << '\n';
#if 0
    TFileOpenWrapper::Close(currentFilePtr_);
#else
    if(currentFilePtr_)
    {
      currentFilePtr_ -> Close();
      delete currentFilePtr_;
      currentFilePtr_ = nullptr;
    }
#endif
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
#if 0
      TFile * filePtr = TFileOpenWrapper::Open(fileName.c_str(), "READ");
#else
      TFile * filePtr = TFile::Open(fileNames_[currentFileIdx_].c_str(), "READ");
#endif
      if(! filePtr)
      {
        throw cmsException(this, __func__) << "Could not open file " << fileName;
      }
      if(filePtr -> IsZombie())
      {
        throw cmsException(this, __func__)
          << "The file '" << fileName << "' appears to be a zombie";
      }
      TTree * treePtr = static_cast<TTree *>(filePtr -> Get(treeName_.c_str()));
      if(! treePtr)
      {
        throw cmsException(this, __func__)
          << "The file '" << fileName << "' does not have a TTree named " << treeName_;
      }
      totalNofEvents += treePtr -> GetEntries();

#if 0
      TFileOpenWrapper::Close(filePtr);
#else
      filePtr -> Close();
      delete filePtr;
#endif
    }
    eventCount_ = totalNofEvents;
  }
  return eventCount_;
}
