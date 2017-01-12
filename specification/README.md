
Running automated tests
=======================

As precondition, your ROOT and CMSSW env variables have to be set.

```
cd $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/specification
git pull
python run_specs.py
```



Why automated tests are important?
==================================


Faster delivery time
--------------------

Tests show that all code is working or show exactly what component is broken.

More time for development, less debugging or testing.



Better quality of results
-------------------------

How can you be certain that your code is doing what is supposed to?

You can test positive scenarios or edge cases.



Better quality of software
--------------------------

Automated tests help developer think about the real task before implementation.

For example, let's thing of a scenario, where software engineer has to think about
simple addition implementation.

As a first question, developer should ask himself "how I create automated test for it?".

As a result he might write a file:

```python
# specs/add_two_numbers_spec.py
import add_two_numbers from add_two_numbers_spec

def main():
  add_two_numbers_spec()
  add_two_negative_numbers_spec()

def add_two_numbers_spec():
  result = add_two_numbers(1, 2)

  if result != 3:
    print "Failed test add_two_numbers_spec"

def add_two_negative_numbers_spec():
  result = add_two_numbers(-1, -2)

  if result != -3:
    print "Failed test add_two_negative_numbers_spec"

main()

```

Note that these tests did:
  * helped to think what would be a good name for method (and files and packages)
  * what are important input parameters
  * what should be the return value
  * document what is going on
  * helped developer to implement what is minimally needed and maximally allowed
  * tested that code is working as expected

Additionally:
  * when other_methods are created, developer can be always certain, that this method is working
