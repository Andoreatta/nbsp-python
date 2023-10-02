# NBioBSP for Python
### Beta module for integrating NBioBSP SDK with Python
This is a Python module for NBioBSP SDK. Built with C/C++ and pybind11.  
**Works only on Windows at the moment.**  

**All code is self contained into a single file, as it is just bindings.**

### - [Documento em Português](README-PTBR.md)

## Requirements
- Python 3.10 or higher 
- eNBSP SDK greater or equal to 5.2
- MSVC 2019 or higher (maybe it works with another compiler, didn't test it yet)

## To Do:
- [x] Readable error output using NBioAPI types **(priority)**
- [x] Handle errors properly
    - [x] Throw translatable and proper exceptions from C++ to Python
- [x] Handle return values properly **(priority)**
- [x] Handle fingerprint purposes on capture properly
- [ ] Implement IndexSearch methods
- [ ] Implement all functions that are possible in Windows
- [ ] Implement all functions that are *possible* in Linux **(no priority)**

You can test the module with the following code:
```python
import nbsp_python as nbsp

nbsp.initialize()
nbsp.get_version()
nbsp.enumerate_device()
nbsp.open_device()
enrolled_handle = nbsp.capture("enroll", 10000)
nbsp.verify(enrolled_handle)
fingerprint_hash = nbsp.extract_fir_text(handle)
nbsp.terminate()
```

## Installation

```python
git clone https://github.com/Andoreatta/nbsp-python.git
cd nbsp-python
pip install .
```
Pulls all the dependencies and installs the module, if something happens, check if the dependencies in pyproject.toml are installed correctly.


## Usage 

- `nbsp.initialize()`  
    Initializes the NBioBSP instance. Must be called before any other function that **interacts with the device**.  
    So you can call `get_version()` before `initialize()`, but not `capture()`. Returns a handle just in case.

- `nbsp.terminate()`  
    Terminates the NBioBSP instance.

- `nbsp.get_version()`  
    Returns the version of the NBioBSP SDK.

- `nbsp.enumerate_device()`  
    Enumerates the devices connected to the computer. Returns a list of devices.

- `nbsp.open_device()`  
    Opens the device using auto-detection. Returns the handle of the device.

- `nbsp.open_specific_device(index)`  
    Opens the device using the device ID. Returns true if successful.

- `nbsp.close_device()`  
    Closes the device.


- `nbsp.capture(purpose, timeout)`  
    Captures a fingerprint. Returns the handle of the fingerprint.  
    `purpose` can be one of the following:  
    - `enroll`  
        for registering a fingerprint
    - `verify`  
        for verifying a fingerprint
    - `identify`  
        for identifying a fingerprint (deprecated as of 5.2)
    - `enroll_for_verification`  
        for registering a fingerprint for verification
    - `enroll_for_identification`  
        for registering a fingerprint for identification

- `nbsp.verify(handle)`  
    Verifies fingerprints contained in handle. Returns true if successful.

- `nbsp.extract_fir_text(handle)`  
    Extracts the fingerprint hash from the handle. Returns the fingerprint hash.
