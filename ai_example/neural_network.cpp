#include "neural_network.hpp"
#include "file.hpp"
#include "file_paths.hpp"

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

NeuralNetwork::NeuralNetwork(
  std::string_view fileName,
  int              inputs,
  int              hiddenLayers,
  int              hidden,
  int              outputs,
  double           learningRate)
  : m_inputs{inputs}
  , m_hiddenLayers{hiddenLayers}
  , m_hidden{hidden}
  , m_outputs{outputs}
  , m_learningRate{learningRate}
  , m_genann{nullptr}
{
  const std::string filePath{findFile(fileName).string()};
  File              file{filePath.c_str(), "rb"};
  genann* const     genann{genann_read(file.get())};

  if (genann == nullptr) {
    throw std::bad_alloc{};
  }

  m_genann = genann;
}

NeuralNetwork::NeuralNetwork(NeuralNetwork&& other) noexcept
  : m_inputs{other.m_inputs}
  , m_hiddenLayers{other.m_hiddenLayers}
  , m_hidden{other.m_hidden}
  , m_outputs{other.m_outputs}
  , m_learningRate{other.m_learningRate}
  , m_genann{other.m_genann}
{
  other.m_genann = nullptr;
}

NeuralNetwork& NeuralNetwork::operator=(NeuralNetwork&& other) noexcept
{
  m_inputs       = other.m_inputs;
  m_hiddenLayers = other.m_hiddenLayers;
  m_hidden       = other.m_hidden;
  m_outputs      = other.m_outputs;
  m_learningRate = other.m_learningRate;

  genann* const tempAnn{other.m_genann};
  other.m_genann = nullptr;
  genann_free(m_genann);
  m_genann = tempAnn;

  return *this;
}

NeuralNetwork::~NeuralNetwork()
{
  genann_free(m_genann);
}

void NeuralNetwork::saveToFile(const std::filesystem::path& path) const
{
  File file{path.string().c_str(), "wb"};
  genann_write(m_genann, file.get());
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
