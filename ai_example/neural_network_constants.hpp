#pragma once

namespace aie {
// These may be experimented with.
inline constexpr int    hiddenLayerCount{1};
inline constexpr int    hiddenLayerNeuronCount{400};
inline constexpr double learningRate{0.1};
inline constexpr int    trainingCycles{4};

// This has to be 10.
inline constexpr int outputLayerNeuronCount{10}; // There are 10 decimal digits.
} // namespace aie
