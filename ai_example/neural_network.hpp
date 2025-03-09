#pragma once
#include <vector>

#include <genann.h>

#include <tl/expected.hpp>

#include <pl/noncopyable.hpp>

namespace aie {
class NeuralNetwork {
public:
  PL_NONCOPYABLE(NeuralNetwork);

  enum class Error { InvalidInputVectorSize, InvalidOutputVectorSize, NoError };

  NeuralNetwork(
    int    inputs,
    int    hiddenLayers,
    int    hidden,
    int    outputs,
    double learningRate);

  ~NeuralNetwork();

  // backpropagation
  Error train(
    const std::vector<double>& inputs,
    const std::vector<double>& desiredOutputs);

  // feedforward
  tl::expected<std::vector<double>, Error> run(
    const std::vector<double>& inputs);

private:
  int     m_inputs;
  int     m_hiddenLayers;
  int     m_hidden;
  int     m_outputs;
  double  m_learningRate;
  genann* m_genann;
};
} // namespace aie
