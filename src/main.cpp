#include <iostream>
#include <pybind11/pybind11.h>
#include <NBioAPI.h>

namespace py = pybind11;

NBioAPI_HANDLE nbioApiHandle;
NBioAPI_DEVICE_ID nbioApiDeviceId;
NBioAPI_RETURN nbioApiReturn;
NBioAPI_VERSION version;
NBioAPI_FIR_PURPOSE purpose;
NBioAPI_FIR_HANDLE hCapturedFIR;

bool NBioBSP_Initialize() {
    nbioApiReturn = NBioAPI_Init(&nbioApiHandle);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_Init failed" << std::endl;
        std::cout << "NBioAPI_Init Error: " << nbioApiReturn << std::endl;
        return false;
    }
    std::cout << "NBioAPI_Init Success (Handle Value): " << nbioApiHandle << std::endl;
    return true;
}

void NBioBSP_GetVersion() {
    nbioApiReturn = NBioAPI_GetVersion(nbioApiHandle, &version);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_GetVersion failed" << std::endl;
        std::cout << "NBioAPI_GetVersion Error: " << nbioApiReturn << std::endl;
        return;
    }
    std::cout << "NBioAPI_GetVersion: " << version.Major << "." << version.Minor << "." <<  std::endl;
}

void NBioBSP_OpenDevice(){
    nbioApiDeviceId = NBioAPI_DEVICE_ID_AUTO;
    nbioApiReturn = NBioAPI_OpenDevice(nbioApiHandle, nbioApiDeviceId);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_OpenDevice failed" << std::endl;
        std::cout << "NBioAPI_OpenDevice Error: " << nbioApiReturn << std::endl;
        return;
    }
    std::cout << "NBioAPI_OpenDevice Success (Device ID): " << nbioApiDeviceId << std::endl;
}

void NBioBSP_CloseDevice(){
    nbioApiReturn = NBioAPI_CloseDevice(nbioApiHandle, nbioApiDeviceId);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_CloseDevice failed" << std::endl;
        std::cout << "NBioAPI_CloseDevice Error: " << nbioApiReturn << std::endl;
        return;
    }
    std::cout << "NBioAPI_CloseDevice Success" << std::endl;
}

void NBioBSP_Capture(){
    purpose = NBioAPI_FIR_PURPOSE_VERIFY;
    nbioApiReturn = NBioAPI_Capture(nbioApiHandle, purpose, &hCapturedFIR, 10000, NULL, NULL);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_Capture failed" << std::endl;
        std::cout << "NBioAPI_Capture Error: " << nbioApiReturn << std::endl;
        return;
    }
    std::cout << "NBioAPI_Capture Success" << std::endl;
}

PYBIND11_MODULE(_core, module) {
    module.doc() = "Python binding for NBioBSP";
    module.def("initialize", &NBioBSP_Initialize, "Initialize NBioBSP");
    module.def("get_version", &NBioBSP_GetVersion, "Get NBioBSP Version");
    module.def("open_device", &NBioBSP_OpenDevice, "Open NBioBSP Device");
    module.def("close_device", &NBioBSP_CloseDevice, "Close NBioBSP Device");
    module.def("capture", &NBioBSP_Capture, "Capture NBioBSP Device");
}