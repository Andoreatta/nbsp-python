// THIS CODE FOLLOWS NITGEN'S NBioBSP SDK OLD STANDARD
// so dont judge me
#include <iostream>
#include <pybind11/pybind11.h>
#include <NBioAPI.h>

namespace py = pybind11;

// The errors are the sum of hex values from NBioAPI_Error.h
// yet, it will dump you an decimal value, so you have to convert it to hex
// e.g:  NBioAPIERROR_BASE_DEVICE          (0x0100)
//       NBioAPIERROR_DEVICE_OPEN_FAIL     (NBioAPIERROR_BASE_DEVICE + 0x01) returns 257
// 257 in hex is 0x101

// vars that are reused constantly
// depending on the function, other types are declared inside the function scope
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

void NBioBSP_Terminate(){
    nbioApiReturn = NBioAPI_Terminate(nbioApiHandle);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_Terminate failed" << std::endl;
        std::cout << "NBioAPI_Terminate Error: " << nbioApiReturn << std::endl;
        return;
    }
    std::cout << "NBioAPI_Terminate Success" << std::endl;
}

void NBioBSP_GetVersion() {
    nbioApiReturn = NBioAPI_GetVersion(nbioApiHandle, &version);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_GetVersion failed" << std::endl;
        std::cout << "NBioAPI_GetVersion Error: " << nbioApiReturn << std::endl;
        return;
    }
    std::cout << "NBioAPI_GetVersion: " << version.Major << "." << version.Minor <<  std::endl;
}

// This function is to retrieve detailed information about the devices attached,
// itsdifferent from NBioAPI_EnumerateDevice
void NBioBSP_EnumeratedDeviceExtra() {
    NBioAPI_UINT32 nDeviceNum;
    NBioAPI_DEVICE_ID *pDeviceList;
    NBioAPI_DEVICE_INFO_EX *pDeviceInfoEx;

    nbioApiReturn = NBioAPI_EnumerateDeviceEx(nbioApiHandle, &nDeviceNum, &pDeviceList, &pDeviceInfoEx);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_EnumerateDeviceEx failed" << std::endl;
        std::cout << "NBioAPI_EnumerateDeviceEx Error: " << nbioApiReturn << std::endl;
        return;
    }

    std::cout << "-------------------------------------" << std::endl;
    for (int i = 0; i < nDeviceNum; i++){
        std::cout << "Device ID (from pDeviceList): " << pDeviceList[i] << std::endl;
        std::cout << "Device ID (from pDeviceInfoEx): " << pDeviceInfoEx[i].NameID << std::endl;
        std::cout << "Device Instance: " << pDeviceInfoEx[i].Instance << std::endl;
        std::cout << "Device Name: " << pDeviceInfoEx[i].Name << std::endl;
        std::cout << "Device Description: " << pDeviceInfoEx[i].Description << std::endl;
        std::cout << "DLL used: " << pDeviceInfoEx[i].Dll << std::endl;
        std::cout << "Sysinfo: " << pDeviceInfoEx[i].Sys << std::endl;
        std::cout << "Supports Auto-On?:  " << pDeviceInfoEx[i].AutoOn << std::endl;
        std::cout << "Brightness value: " << pDeviceInfoEx[i].Brightness << std::endl;
        std::cout << "Contrast value: " << pDeviceInfoEx[i].Contrast << std::endl;
        std::cout << "Gain value: " << pDeviceInfoEx[i].Gain << std::endl;
        std::cout << "Reserved at: " << pDeviceInfoEx[i].Reserved << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
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

// pass the device ID (pDeviceInfoEx from NBioBSP_EnumerateDeviceExtra)
void NBioBSP_OpenSpecificDevice(NBioAPI_DEVICE_ID nbioApiDeviceId) {
    nbioApiReturn = NBioAPI_OpenDevice(nbioApiHandle, nbioApiDeviceId);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_OpenDevice failed" << std::endl;
        std::cout << "NBioAPI_OpenDevice Error: " << nbioApiReturn << std::endl;
        return;
    }
    std::cout << "NBioAPI_OpenDevice Success (Device ID): " << nbioApiDeviceId << std::endl;
}

// closes all devices
void NBioBSP_CloseDevice(){
    nbioApiDeviceId = NBioAPI_DEVICE_ID_AUTO;       // detects which devices to close
    nbioApiReturn = NBioAPI_CloseDevice(nbioApiHandle, nbioApiDeviceId);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_CloseDevice failed" << std::endl;
        std::cout << "NBioAPI_CloseDevice Error: " << nbioApiReturn << std::endl;
        return;
    }
    std::cout << "NBioAPI_CloseDevice Success" << std::endl;
}

// To do: implement handle different purposes
void NBioBSP_Capture(NBioAPI_FIR_PURPOSE purpose, int timeout){
    nbioApiReturn = NBioAPI_Capture(nbioApiHandle, purpose, &hCapturedFIR, timeout, NULL, NULL);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_Capture failed" << std::endl;
        std::cout << "NBioAPI_Capture Error: " << nbioApiReturn << std::endl;
        return;
    }
}

PYBIND11_MODULE(_core, module) {
    module.doc() = "Python binding for NBioBSP";
    module.def("initialize", &NBioBSP_Initialize, "Initialize NBioBSP");
    module.def("terminate", &NBioBSP_Terminate, "Terminate NBioBSP");
    module.def("get_version", &NBioBSP_GetVersion, "Get NBioBSP Version");
    module.def("enumerate_device", &NBioBSP_EnumeratedDeviceExtra, "Enumerate NBioBSP Devices with extra info");
    module.def("open_device", &NBioBSP_OpenDevice, "Open NBioBSP Device");
    module.def("open_specific_device", &NBioBSP_OpenSpecificDevice, "Open NBioBSP Device with specific ID");
    module.def("close_device", &NBioBSP_CloseDevice, "Close NBioBSP Device");
    module.def("capture", &NBioBSP_Capture, "Capture NBioBSP Device");
}