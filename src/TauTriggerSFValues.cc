#include "tthAnalysis/HiggsToTauTau/interface/TauTriggerSFValues.h"

#include <cassert> // assert()
#include <algorithm> // std::max()
#include <iostream> // std::ostream

TauTriggerSFValues::TauTriggerSFValues()
  : TauTriggerSFValues(0., 0., 0.)
{}

TauTriggerSFValues::TauTriggerSFValues(double min_,
                                       double central_,
                                       double max_)
  : min(min_)
  , central(central_)
  , max(max_)
{}

TauTriggerSFValues &
TauTriggerSFValues::max_of(double value)
{
  // if min <= central <= max, then taking max is guaranteed to preserve the order
  min     = std::max(min,     value);
  central = std::max(central, value);
  max     = std::max(max,     value);
  return *this;
}

bool
TauTriggerSFValues::is_ordered() const
{
  return min <= central && central <= max;
}

TauTriggerSFValues
operator*(double factor,
          const TauTriggerSFValues & values)
{
  return values * factor;
}

TauTriggerSFValues
operator*(const TauTriggerSFValues & values,
          double factor)
{
  const double min_value     = values.min     * factor;
  const double central_value = values.central * factor;
  const double max_value     = values.max     * factor;
  if(min_value <= central_value && central_value <= max_value)
  {
    assert(factor >= 0.);
    return { min_value, central_value, max_value };
  }
  else if(min_value >= central_value && central_value >= max_value)
  {
    assert(factor <= 0.);
    return { max_value, central_value, min_value };
  }
  else
  {
    assert(0);
  }
}

TauTriggerSFValues
operator-(double minuend,
          const TauTriggerSFValues & values)
{
  const double min_value     = minuend - values.min;
  const double central_value = minuend - values.central;
  const double max_value     = minuend - values.max;
  if(min_value <= central_value && central_value <= max_value)
  {
    return { min_value, central_value, max_value };
  }
  else if(min_value >= central_value && central_value >= max_value)
  {
    return { max_value, central_value, min_value };
  }
  else
  {
    assert(false);
  }
}

std::ostream &
operator<<(std::ostream & stream,
           const TauTriggerSFValues & values)
{
  stream << values.min << " / " << values.central << " / " << values.max;
  return stream;
}
