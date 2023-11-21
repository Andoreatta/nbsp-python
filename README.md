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
- Cmake 20 or higher

## To Do:
- [x] Readable error output using NBioAPI types **(priority)**
- [x] Handle errors properly
    - [x] Throw translatable and proper exceptions from C++ to Python
- [x] Handle return values properly **(priority)**
- [x] Handle fingerprint purposes on capture properly
- [x] Implement IndexSearch methods
- [ ] Implement all functions that are possible in Windows
- [ ] Implement all functions that are *possible* in Linux **(no priority)**

You can test the module with the following code on the Python interpreter:
```python
import nbsp_python as nbsp

# Initialize the NBioBSP instance
nbsp.initialize_handle()

# Get the version of the NBioBSP SDK
nbsp.get_version()

# Enumerate the devices connected to the computer
nbsp.enumerate_device()

# Open the device using auto-detection
nbsp.open_device()

# Capture a fingerprint and assign it to handle
handle = nbsp.capture("enroll", 10000)

# Verify fingerprints contained in handle
nbsp.verify(handle)

# Extract the hash from the last fingerprint added in the handle
fingerprint_hash = nbsp.extract_fir_text(handle)

# Initialize the index search
nbsp.init_index_search()

# Add the fingerprint to the index search and pass
nbsp.add_fir_to_index_search(fingerprint_hash, 1)

# Identify the fingerprint in the index search
nbsp.identify_data_from_index_search(fingerprint_hash)

# Terminate the index search
nbsp.terminate_index_search()

# Terminate the NBioBSP instance
nbsp.terminate_handle()

# Close the device
nbsp.close_device()
```
Or by executing a [TKinter Example](example/tkinter_example.py) with Python.

## Installation
This process is valid for those who want to modify the library only.
```python
git clone https://github.com/Andoreatta/nbsp-python.git
cd nbsp-python
pip install .
```
Pulls all the dependencies and installs the module, if something happens, check if the dependencies in pyproject.toml are installed correctly.  
If you wish to get only the precompiled library, do the following.

```python
pip install nbsp-python
```

## Usage

- `nbsp.initialize_handle()`
    Initializes the NBioBSP instance. Must be called before any other function that **interacts with the device**.
    So you can call `get_version()` before `initialize_handle()`, but not `capture()`. Returns a handle just in case.

- `nbsp.terminate_handle()`
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


- `nbsp.capture("purpose", timeout)`
    Captures a fingerprint. Returns the handle of the fingerprint.
    `purpose` can be one of the following:
    - `"enroll"`
        for registering a fingerprint
    - `"verify"`
        for verifying a fingerprint
    - `"identify"`
        for identifying a fingerprint (deprecated as of 5.2)
    - `"enroll_for_verification"`
        for registering a fingerprint for verification
    - `"enroll_for_identification"`
        for registering a fingerprint for identification
The `timeout` parameter is the maximum time in milliseconds to wait for a fingerprint to be captured.

- `nbsp.verify(handle)`
    Verifies the last fingerprint added in handle. Returns true if successful.

- `nbsp.extract_fir_text(handle)`
    Extracts the fingerprint hash from the handle. Returns the fingerprint hash.

- `nbsp.init_index_search()`
    Initializes the index search.

- `nbsp.terminate_index_search()`
    Terminates the index search.

- `nbsp.add_fir_to_index_search(fingerprint_hash, user_id)`
    Adds a fingerprint to the index search. Returns true if successful.
