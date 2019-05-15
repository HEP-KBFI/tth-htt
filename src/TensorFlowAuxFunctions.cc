#include "tthAnalysis/HiggsToTauTau/interface/TensorFlowAuxFunctions.h"

/*
tensorflow::Tensor getPredictions(edm::Event& event, const edm::EventSetup& es,
                                          edm::Handle<TauCollection> taus) override
{
    edm::Handle<pat::ElectronCollection> electrons;
    event.getByToken(electrons_token, electrons);

    edm::Handle<pat::MuonCollection> muons;
    event.getByToken(muons_token, muons);

    tensorflow::Tensor predictions(tensorflow::DT_FLOAT, { static_cast<int>(taus->size()),
                                   dnn_inputs_2017v1::NumberOfOutputs});
    for(size_t tau_index = 0; tau_index < taus->size(); ++tau_index) {
        const tensorflow::Tensor& inputs = createInputs<dnn_inputs_2017v1>(taus->at(tau_index), *electrons, *muons);
        std::vector<tensorflow::Tensor> pred_vector;
        tensorflow::run(&(cache_->getSession()), { { input_layer, inputs } }, { output_layer }, &pred_vector);
        for(int k = 0; k < dnn_inputs_2017v1::NumberOfOutputs; ++k)
            predictions.matrix<float>()(tau_index, k) = pred_vector[0].flat<float>()(k);
    }
    return predictions;
}
*/

/*
//template<typename dnn>
tensorflow::Tensor
createInputs(const std::map<std::string, double> & mvaInputs, int NumberOfInputs)
{
    //static constexpr bool check_all_set = false;
    //static constexpr float default_value_for_set_check = -42;

    tensorflow::Tensor inputs(tensorflow::DT_FLOAT, { 1, NumberOfInputs});
    // dumb fill by now
    for (size_t i = 0; i < NumberOfInputs; i++) input.matrix<float>()(0, i) = float(i);
    //inputs.matrix<float>()(0, var_index);
    //const auto& get = [&](int var_index) -> float& { return inputs.matrix<float>()(0, var_index); };
    //auto leadChargedHadrCand = dynamic_cast<const pat::PackedCandidate*>(tau.leadChargedHadrCand().get());

    //if(check_all_set) {
    //    for(int var_index = 0; var_index < dnn::NumberOfInputs; ++var_index) {
    //        get(var_index) = default_value_for_set_check;
    //    }
    //}

    //if(check_all_set) {
    //    for(int var_index = 0; var_index < dnn::NumberOfInputs; ++var_index) {
    //        if(get(var_index) == default_value_for_set_check)
    //            throw cms::Exception("DeepTauId: variable with index = ") << var_index << " is not set.";
    //    }
    //}

    return inputs;
}
*/
