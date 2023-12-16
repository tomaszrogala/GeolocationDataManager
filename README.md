# GEOLOCATION DATA MANAGER

Geolocation Data Manager is a desktop application that enables the management of geolocation data based on IP addresses or URLs. 
By utilizing the API provided by ipstack, the application is capable of retrieving detailed geographical information associated with specific IP addresses or URLs, such as country, city, longitude, latitude etc.


The application's functionalities include:

- Adding Geolocation Data: Users can add geolocation data to the database by providing only an IP address or URL.
- Deleting Data: The application enables the deletion of specific geolocation data from the database, based on the IP address or URL specified in the input.
- Displaying Geolocation Data: Users can view geolocation data stored in the database, with the ability to search for data based on an IP address or URL.

The application is designed with ease of use in mind, providing a clear user interface that allows for quick and intuitive management of geolocation data.

## Prerequisites

- CMake 3.10 or later
- QT SDK 6.6.1
- Compiler MinGw 11.2.0 64-bit for C

## Build project on Windows

Go to GeolocationDataManager directory and open command line.

- Create build folder

```shell
mkdir build && cd build
```

- Set Environment Path for MinGw

Set path to the gcc.exe directory. Eg.:
```shell
set PATH=C:\Qt\Tools\mingw1120_64\bin;%PATH%
```

- Configure Cmake


```shell
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
```
or
```shell
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
```

- Build project

```shell
mingw32-make
```

- Provide requierd dll files

```shell
windeployqt <Your-local-path-to-repository>\GeolocationDataManager\build\GeolocationDataManager.exe
```

or copy from
```shell
C:\Qt\6.6.1\mingw_64\bin
```

## Run Application
Before you run the executable file make sure that Config.ini file is created in your build directory!

### Configuration File Structure

The application uses a `config.ini` file for managing configuration settings. This file should be located in the same directory as the application executable. Below is the structure of the `config.ini` file with explanations for each setting:

#### Database Section

- `[Database]`: This section contains settings related to the database.
  - `DatabasePath`: The file path to the database. This path is where the application will look for its database file.
    - Example: `DatabasePath="C:\\Data\\"`

#### IpStackAPI Section

- `[IpStackAPI]`: This section contains the API key for accessing the IpStack service.
  - `ApiKey`: Your personal API key for IpStack. This key is necessary for the application to fetch geolocation data.
    - Example: `ApiKey="364fd3bbd196e5c709e2d7f3136cfc23"`

Make sure to replace the example values with your actual database path and IpStack API key. The application will read these settings at startup and configure itself accordingly.

#### Config.ini example
```shell
[Database]
DatabasePath="C:\\Data\\"

[IpStackAPI]
ApiKey="364fd3bbd196e5c709e2d7f3136cfc23"

```

## Application Usage

### Entering URL and IP Address

When using the application, please follow these guidelines for entering URLs and IP addresses:

- **URL Input**: Enter URLs without any scheme. For example, instead of typing `http://www.example.com` or `https://www.example.com`, simply enter `www.example.com`.
- **IP Address Input**: Input IP addresses in their standard format, without any prefixes or additional characters. For example, use `192.168.1.1` instead of `http://192.168.1.1`.


# GEOLOCATION DATA MANAGER UNIT TESTS

### Build Unit Test executable on Windows

Go to GeolocationDataManagerTest directory and open command line.

- Create build folder

```shell
mkdir build && cd build
```

- Set Environment Path for MinGw

Set path to the gcc.exe directory. Eg.:
```shell
set PATH=C:\Qt\Tools\mingw1120_64\bin;%PATH%
```

- Configure Cmake

```shell
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE ..
```

- Build project

```shell
mingw32-make
```

- Provide requierd dll files 

```shell
<Qt-path>\bin\windeployqt.exe <GeolocationDataManagerTest-executable-file-path>
```

## Run Unit Tests
Run GeolocationDataManagerTest.exe in command line


## Author
Tomasz Rogala
