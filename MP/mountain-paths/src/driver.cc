#include <iostream>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

int main() {
  // ElevationDataset dataset(
  // "example-data/ex_input_data/map-input-w51-h55.dat", 51, 55);

  // ElevationDataset dataset(
  // "example-data/ex_input_data/map-input-w844-h480.dat", 844, 480);

  // ElevationDataset dataset(
  // "example-data/ex_input_data/map-input-w480-h480.dat", 480, 480);

  ElevationDataset dataset("example-data/ex_input_data/prompt_5w_2h.dat", 5, 2);

  GrayscaleImage gi(dataset);
  gi.ToPpm("obj/gi.ppm");
  PathImage pi(gi, dataset);
  pi.ToPpm("obj/pi.ppm");

  // ElevationDataset ed(
  //     "example-data/ex_input_data/all-tie-row1-2w-3h.dat", 2, 3);
  // Path path(2, 2);
  // GeneratePath(ed, path);
  // for (auto& row : path.GetPath()) {
  //   std::cout << row << " ";
  // }
  // std::cout << std::endl << path.EleChange() << std::endl;

  return 0;
}