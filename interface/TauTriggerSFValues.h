#ifndef tthAnalysis_HiggsToTauTau_TauTriggerSFValues_h
#define tthAnalysis_HiggsToTauTau_TauTriggerSFValues_h

#include <iosfwd> // std::ostream

struct TauTriggerSFValues
{
  /**
   * @brief Always ensures that the member variables min, central and max obey min <= central <= max and
   * that the central value always remains central after every linear operation (such as addition/subtractiona and
   * multiplication/division).
   */
  TauTriggerSFValues();
  TauTriggerSFValues(double min_,
                     double central_,
                     double max_);

  TauTriggerSFValues &
  max_of(double value);

  bool
  is_ordered() const;

  double min;
  double central;
  double max;
};

TauTriggerSFValues
operator*(double factor,
          const TauTriggerSFValues & values);

TauTriggerSFValues
operator*(const TauTriggerSFValues & values,
          double factor);

TauTriggerSFValues
operator-(double minuend,
          const TauTriggerSFValues & values);

std::ostream &
operator<<(std::ostream & stream,
           const TauTriggerSFValues & values);

#endif
