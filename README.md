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

## Application Usage Instructions

### Entering URLs and IP Addresses

#### Accepted Input Formats

##### URLs
- The application accepts the following URL formats:
  - URLs without the protocol scheme. For example, use `www.example.com` or `www.testsite.com` instead of `https://www.example.com` or `http://www.testsite.com`.
  - URLs with subdomains but without the protocol scheme, e.g., `subdomain.example.org/path?query=123`.
  - **Note:** URLs entered with the http/https protocols (like `http://`, `https://`) will not yield expected results.

##### IPv4 Addresses
- The application accepts standard IPv4 addresses, such as:
  - `192.168.1.1`
  - `10.0.0.1`
  - `172.16.254.1`

##### IPv6 Addresses
- The application accepts standard IPv6 addresses, including:
  - Extended addresses, e.g., `2001:0db8:85a3:0000:0000:8a2e:0370:7334`.
  - Compressed addresses, e.g., `::1`, `fe80::1ff:fe23:4567:890a`.

#### Invalid Data Formats

The application does not accept the following formats:
- Empty strings or spaces only.
- URLs with schemes or potentially harmful scripts, e.g., `http://example.com/<script>`, `https://example.com/|pipe`.
- JavaScript code, e.g., `javascript:alert('XSS')`.


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
