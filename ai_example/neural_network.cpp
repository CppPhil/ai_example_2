#include "neural_network.hpp"

namespace aie {
NeuralNetwork::NeuralNetwork(
  int    inputs,
  int    hiddenLayers,
  int    hidden,
  int    outputs,
  double learningRate)
  : m_inputs{inputs}
  , m_hiddenLayers{hiddenLayers}
  , m_hidden{hidden}
  , m_outputs{outputs}
  , m_learningRate{learningRate}
  , m_genann{genann_init(m_inputs, m_hiddenLayers, m_hidden, m_outputs)}
{
  if (m_genann == nullptr) {
    throw std::bad_alloc{};
  }
}

NeuralNetwork::~NeuralNetwork()
{
  genann_free(m_genann);
}

NeuralNetwork::Error NeuralNetwork::train(
  const std::vector<double>& inputs,
  const std::vector<double>& desiredOutputs)
{
  if (inputs.size() != static_cast<std::size_t>(m_inputs)) {
    return Error::InvalidInputVectorSize;
  }

  if (desiredOutputs.size() != static_cast<std::size_t>(m_outputs)) {
    return Error::InvalidOutputVectorSize;
  }

  genann_train(m_genann, inputs.data(), desiredOutputs.data(), m_learningRate);
  return Error::NoError;
}

tl::expected<std::vector<double>, NeuralNetwork::Error> NeuralNetwork::run(
  const std::vector<double>& inputs)
{
  if (inputs.size() != static_cast<std::size_t>(m_inputs)) {
    return tl::make_unexpected(Error::InvalidInputVectorSize);
  }

  const double* const outputLayer{genann_run(m_genann, inputs.data())};
  return std::vector<double>(outputLayer, outputLayer + m_outputs);
}
} // namespace aie
