# GEOLOCATION DATA MANAGER

Geolocation Data Manager is a desktop application that enables the management of geolocation data based on IP addresses or URLs. By utilizing the API provided by ipstack, the application is capable of retrieving detailed geographical information associated with specific IP addresses or URLs, such as country, city, longitude, latitude etc.


The application's functionalities include:

Adding Geolocation Data: Users can add geolocation data to the database by providing only an IP address or URL.
Deleting Data: The application allows for the removal of selected geolocation data from the database.
Displaying Geolocation Data: Users can view geolocation data stored in the database, with the ability to search for data based on an IP address or URL.
The application is designed with ease of use in mind, providing a clear user interface that allows for quick and intuitive management of geolocation data.

## Prerequisites

- CMake 3.10 or later
- Microsoft Visual Studio 2022

## Cloning the Repository

To clone the repository, including its submodules, use the following command:

``` shell
git clone --recursive https://github.com/tomaszrogala/BackToTheFuture.git
```

If you've already cloned the project, you can download the submodules separately using:

``` shell
git submodule init
git submodule update
```

## Building zlib
Navigate to the zlib directory inside your project directory.

Open a Visual Studio 2022 Developer Command Prompt.

``` shell
Set the working directory to the zlib directory!
```

Run the following commands:

``` shell
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
```
This will generate a Visual Studio project file for zlib.

Now zlib should be visible in BackToTheFuture solution.

## Building wolfssl
Add compilation flags to wolfssl project preprocessor properties: HAVE_BLAKE2 and HAVE_BLAKE2B

## Building the main project
Open the BackToTheFuture solution in Visual Studio 2022.

Build the project in Release or Debug mode (only x64 is supported).

# Running the Program
Once you have successfully built the project, you can run the executable from the command line. The program accepts two commands: prepare_file and unpack_file, each requiring different arguments.

## Prepare File
The prepare_file command prepares the file for the processing. It takes two arguments: the source directory and the destination file.

```shell
./BackToTheFuture.exe prepare_file [source_directory] [destination_file]
```

source_directory: The path to the directory containing the files to be processed.

destination_file: The path to the file where the processed data will be saved.

# Example
```shell
./BackToTheFuture.exe prepare_file "C:\Users\YourUser\Documents\SourceRootDirectory" "C:\Users\YourUser\Documents\DestinationFolder"
```

## Unpack File
The unpack_file command unpacks the file previously prepared with the prepare_file command. It takes one argument: the path to the file to be unpacked.

```shell
./BackToTheFuture.exe unpack_file [file_path]
```

file_path: The path to the file to be unpacked.

# Example
```shell
./BackToTheFuture.exe unpack_file "C:\Users\YourUser\Documents\FolderWithCompressedFile"
```

## Author
Tomasz Rogala
