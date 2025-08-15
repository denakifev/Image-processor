# Image Processor

This project is a console application that allows applying various filters to images, similar to those found in popular graphics editors.

## Supported Image Format

The program works with 24-bit BMP images without compression or color tables (using the `BITMAPINFOHEADER` DIB format).

Example input files are available in the `tests/test_data` folder.

## Building

This project uses CMake as the build system. To build the application:

```
mkdir build
cd build
cmake ..
cmake --build .
```

After building, the image_processor executable will be available in the build directory.

## Running

The program accepts the following format:

```
{path_to_build_dir}/image_processor {input_file_path} {output_file_path}"
"[-{filter_name1} [arg1] [arg2] ...]"
"[-{filter_name2} [arg1] [arg2] ...] ...
```

- Running the program without arguments displays help information.

- Filters are applied in the order they are listed.

- The filter list can be empty, in which case the image is saved unchanged.

## Example
```
./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5
```

This command:

1. Loads `input.bmp`

2. Crops it to 800x600 pixels (top-left corner)

3. Converts it to grayscale

4. Applies Gaussian blur with sigma 0.5

5. Saves the result to `/tmp/output.bmp`

## Available Filters

- **Crop** (`-crop width height`) – crops the image to the specified width and height.

- **Grayscale** (`-gs`) – converts the image to grayscale.

- **Negative** (`-neg`) – inverts image colors.

- **Sharpen** (`-sharp`) – sharpens the image.

- **Edge Detection** (`-edge threshold`) – highlights edges based on a threshold.

- **Gaussian Blur** (`-blur sigm`a) – applies Gaussian blur with the given sigma.

- **Glass Distortion** (`-glass strength`) – applies a glass-like distortion effect.

Filters can be combined and applied in any sequence.

## Testing

The project includes both C++ and Python tests.

### C++ Tests

C++ tests are built using Catch2. From the `build` directory:

```
make run_cpp_tests 
```

This will compile and run all C++ unit tests.

### Python Tests

Python tests run in a virtual environment to isolate dependencies. To run them:

```
make run_py3_tests 
```

CMake will automatically:

1. Create a virtual environment if it doesn’t exist.

2. Install required Python packages from `requirements.txt`.

3. Run the Python test script (`tests/test_image_processor.py`) using the built image_processor binary.

You can combine C++ and Python tests by using `make run_all_tests`, which will also run the Python tests as well.