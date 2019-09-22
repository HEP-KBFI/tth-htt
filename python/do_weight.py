from HHStatAnalysis.AnalyticalModels.NonResonantModel import NonResonantModel

import os
os.environ["MKL_NUM_THREADS"] = "1"

def load(coefFile):
    model = NonResonantModel()
    model.ReadCoefficients(coefFile)
    return model

def evaluate_weight(kl, kt, c2, cg, c2g, mhh_gen, cost_gen, calcSumOfWeights, denominator, model):
    return model.getScaleFactor(mhh_gen, cost_gen, kl, kt, c2, cg, c2g, denominator, calcSumOfWeights)
