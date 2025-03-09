#include <cstdio>
#include <cstdlib>

#include <fmt/format.h>

#include <FL/Fl_Double_Window.H>

#include <pl/except.hpp>

#include "as_double_vector.hpp"
#include "closest_to_one.hpp"
#include "collect_images.hpp"
#include "extract_grayscale_images.hpp"
#include "extract_image.hpp"
#include "extract_labels.hpp"
#include "file_paths.hpp"
#include "gui_constants.hpp"
#include "idx_file.hpp"
#include "image_count.hpp"
#include "image_size_from.hpp"
#include "integer_interval_as_string_vector.hpp"
#include "io_constants.hpp"
#include "neural_network.hpp"
#include "neural_network_constants.hpp"
#include "table.hpp"

int main(int argc, char* argv[])
{
  try {
    const aie::IdxFile trainingImagesIdxFile{
      aie::IdxFile::create(aie::trainingImagesFilePath)};
    const aie::IdxFile trainingLabelsIdxFile{
      aie::IdxFile::create(aie::trainingLabelsFilePath)};
    const aie::IdxFile testingImagesIdxFile{
      aie::IdxFile::create(aie::testingImagesFilePath)};
    const aie::IdxFile testingLabelsIdxFile{
      aie::IdxFile::create(aie::testingLabelsFilePath)};
    const std::vector<std::uint32_t>& testingImageDimensions{
      testingImagesIdxFile.dimensions()};
    const std::uint32_t testingImageCount{testingImageDimensions.at(0)};
    const std::uint32_t testingImageRows{testingImageDimensions.at(1)};
    const std::uint32_t testingImageColumns{testingImageDimensions.at(2)};
    const std::uint32_t testingImageByteCount{
      testingImageRows * testingImageColumns};

    const std::vector<std::string> rowHeaders{
      aie::integerIntervalAsStringVector(0, testingImageCount)};

    const std::vector<std::byte>& trainingImageBytes{
      aie::extractGrayscaleImages(trainingImagesIdxFile)};
    const std::vector<std::byte>& trainingLabelsBytes{
      aie::extractLabels(trainingLabelsIdxFile)};
    const std::vector<std::byte>& testingImageBytes{
      aie::extractGrayscaleImages(testingImagesIdxFile)};
    const std::vector<std::byte>& testingLabelsBytes{
      aie::extractLabels(testingLabelsIdxFile)};

    aie::NeuralNetwork neuralNetwork{
      static_cast<int>(aie::imageSizeFrom(trainingImagesIdxFile)),
      aie::hiddenLayerCount,
      aie::hiddenLayerNeuronCount,
      aie::outputLayerNeuronCount,
      aie::learningRate};

    const std::uint32_t trainingImageCount{
      aie::imageCount(trainingImagesIdxFile)};
    const std::uint32_t trainingImageByteSize{
      aie::imageSizeFrom(trainingImagesIdxFile)};

    fmt::print("Starting training ...\n");
    for (int counter{0}; counter < aie::trainingCycles; ++counter) {
      for (std::uint32_t i{0}; i < trainingImageCount; ++i) {
        const std::vector<std::byte> currentImage{
          aie::extractImage(trainingImageBytes, i, trainingImageByteSize)};
        const std::vector<double> input{aie::asDoubleVector(currentImage)};
        const std::byte           expectedLabel{trainingLabelsBytes.at(i)};
        const std::vector<double> labelVector{
          aie::asDoubleVector(expectedLabel)};

        if (
          neuralNetwork.train(input, labelVector)
          != aie::NeuralNetwork::Error::NoError) {
          PL_THROW_WITH_SOURCE_INFO(std::domain_error, "network.train failed!");
        }

        fmt::print(
          "Training cycle {} / {} image {:>{}} / {}\r",
          counter + aie::oneBasedOffset,
          aie::trainingCycles,
          i + aie::oneBasedOffset,
          aie::numberWidth,
          trainingImageCount);
      }
    }
    fmt::print("{:<30}\n", "Finished training.");

    std::vector<std::size_t> calculatedLabels{};
    calculatedLabels.reserve(testingImageCount);

    fmt::print("Starting testing...\n");
    std::uint32_t correctlyDetectedImages{0};
    for (std::uint32_t i{0}; i < testingImageCount; ++i) {
      const std::vector<std::byte> currentImage{
        aie::extractImage(testingImageBytes, i, testingImageByteCount)};
      const std::vector<double> input{aie::asDoubleVector(currentImage)};
      const tl::expected<std::vector<double>, aie::NeuralNetwork::Error>
        expected{neuralNetwork.run(input)};

      if (!expected.has_value()) {
        PL_THROW_WITH_SOURCE_INFO(std::domain_error, "network.run failed!");
      }

      const std::vector<double>& result{*expected};
      const std::size_t          calculatedLabel{aie::closestToOne(result)};
      calculatedLabels.push_back(calculatedLabel);

      if (static_cast<std::byte>(calculatedLabel) == testingLabelsBytes.at(i)) {
        ++correctlyDetectedImages;
      }

      fmt::print(
        "Test image {:>{}} / {}\r",
        i + aie::oneBasedOffset,
        aie::numberWidth,
        testingImageCount);
    }
    fmt::print("{:<30}\n", "Finished testing.");
    fmt::print(
      "{} / {} ({}%) images were correctly labeled.\n",
      correctlyDetectedImages,
      testingImageCount,
      static_cast<double>(correctlyDetectedImages)
        / static_cast<double>(testingImageCount) * 100.0);

    Fl::visual(FL_DOUBLE | FL_INDEX);
    Fl_Double_Window window{
      aie::windowWidth, aie::windowHeight, aie::windowLabel};
    aie::Table table{
      aie::tableTopLeft,
      aie::tableSize,
      rowHeaders,
      aie::columnHeaders,
      aie::tableLabel,
      /* imageWidth */ static_cast<int>(testingImageColumns),
      /* imageHeight */ static_cast<int>(testingImageRows)};

    for (int row{0}; row < table.rowCount(); ++row) {
      table.at(row, aie::labelColumn) = std::to_string(
        static_cast<std::uint32_t>(aie::extractLabels(testingLabelsIdxFile)
                                     .at(static_cast<std::size_t>(row))));
    }

    for (int row{0}; row < table.rowCount(); ++row) {
      table.at(row, aie::calculatedLabelsColumn)
        = std::to_string(calculatedLabels.at(static_cast<std::size_t>(row)));
    }

    const std::vector<std::vector<std::byte>> images{aie::collectImages(
      testingImageCount, testingImageBytes, testingImageByteCount)};
    table.loadImages(images, testingImageColumns, testingImageRows);
    window.end();
    window.resizable(table);
    window.show(argc, argv);
    return Fl::run();
  }
  catch (const pl::precondition_violation_exception& exception) {
    fmt::print(
      stderr,
      "Caught precondition_violation_exception: {}\n",
      exception.what());
    return EXIT_FAILURE;
  }
  catch (const std::domain_error& exception) {
    fmt::print(stderr, "Caught domain_error: {}\n", exception.what());
    return EXIT_FAILURE;
  }
}
