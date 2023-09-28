// THIS CODE FOLLOWS NITGEN'S NBioBSP SDK OLD STANDARD
// so dont judge me
// C++11
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <NBioAPI.h>
#include <unordered_map>

namespace py = pybind11;

// The ERRORs are the sum of hex values from NBioAPI_ERROR.h
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
NBioAPI_FIR_TEXTENCODE textFIR;

std::unordered_map<std::string, NBioAPI_FIR_PURPOSE> purposeMap = {
    {"verify", NBioAPI_FIR_PURPOSE_VERIFY},
    {"identify", NBioAPI_FIR_PURPOSE_IDENTIFY},
    {"enroll", NBioAPI_FIR_PURPOSE_ENROLL},
    {"enroll_for_verification", NBioAPI_FIR_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY},
    {"enroll_for_identification", NBioAPI_FIR_PURPOSE_ENROLL_FOR_IDENTIFICATION_ONLY}
    // {"audit", NBioAPI_FIR_PURPOSE_AUDIT},
    // {"update", NBioAPI_FIR_PURPOSE_UPDATE}
};

bool NBioBSP_Initialize() {
    nbioApiReturn = NBioAPI_Init(&nbioApiHandle);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_Init failed, ERROR: " << nbioApiReturn << std::endl;
        return false;
    }
    std::cout << "NBioAPI_Init Success (Handle Value): " << nbioApiHandle << std::endl;
    return true;
}

bool NBioBSP_Terminate(){
    nbioApiReturn = NBioAPI_Terminate(nbioApiHandle);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_Terminate failed, ERROR: " << nbioApiReturn << std::endl;
        return false;
    }
    std::cout << "NBioAPI_Terminate Success" << std::endl;
    return true;
}

std::string NBioBSP_GetVersion() {
    nbioApiReturn = NBioAPI_GetVersion(nbioApiHandle, &version);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        return "NBioAPI_GetVersion failed, ERROR: " + std::to_string(nbioApiReturn);
    }
    return std::to_string(version.Major) + "." + std::to_string(version.Minor);
}

// This function is to retrieve detailed information about the devices attached,
std::vector<std::vector<std::string>> NBioBSP_EnumeratedDeviceExtra() {
    NBioAPI_UINT32 nDeviceNum;
    NBioAPI_DEVICE_ID *pDeviceList;
    NBioAPI_DEVICE_INFO_EX *pDeviceInfoEx;

    nbioApiReturn = NBioAPI_EnumerateDeviceEx(nbioApiHandle, &nDeviceNum, &pDeviceList, &pDeviceInfoEx);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_EnumerateDeviceEx failed, ERROR: " << nbioApiReturn << std::endl;
        return {};
    }

    std::vector<std::vector<std::string>> deviceList;
    for (int i = 0; i < nDeviceNum; i++){
        std::vector<std::string> deviceInfo;
        deviceInfo.push_back(std::to_string(pDeviceList[i]));
        deviceInfo.push_back(std::to_string(pDeviceInfoEx[i].NameID));
        deviceInfo.push_back(std::to_string(pDeviceInfoEx[i].Instance));
        deviceInfo.push_back(pDeviceInfoEx[i].Name);
        deviceInfo.push_back(pDeviceInfoEx[i].Description);
        deviceInfo.push_back(pDeviceInfoEx[i].Dll);
        deviceInfo.push_back(pDeviceInfoEx[i].Sys);
        deviceInfo.push_back(std::to_string(pDeviceInfoEx[i].AutoOn));
        deviceInfo.push_back(std::to_string(pDeviceInfoEx[i].Brightness));
        deviceInfo.push_back(std::to_string(pDeviceInfoEx[i].Contrast));
        deviceInfo.push_back(std::to_string(pDeviceInfoEx[i].Gain));

        deviceList.push_back(deviceInfo);
    }
    return deviceList;
}

void NBioBSP_OpenDevice(){
    nbioApiDeviceId = NBioAPI_DEVICE_ID_AUTO;
    nbioApiReturn = NBioAPI_OpenDevice(nbioApiHandle, nbioApiDeviceId);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_OpenDevice failed" << std::endl;
        std::cout << "NBioAPI_OpenDevice ERROR: " << nbioApiReturn << std::endl;
        return;
    }
    std::cout << "NBioAPI_OpenDevice Success (Device ID): " << nbioApiDeviceId << std::endl;
}

// pass the device ID (pDeviceInfoEx from NBioBSP_EnumerateDeviceExtra)
void NBioBSP_OpenSpecificDevice(NBioAPI_DEVICE_ID nbioApiDeviceId) {
    nbioApiReturn = NBioAPI_OpenDevice(nbioApiHandle, nbioApiDeviceId);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_OpenDevice failed" << std::endl;
        std::cout << "NBioAPI_OpenDevice ERROR: " << nbioApiReturn << std::endl;
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
        std::cout << "NBioAPI_CloseDevice ERROR: " << nbioApiReturn << std::endl;
        return;
    }
    std::cout << "NBioAPI_CloseDevice Success" << std::endl;
}

NBioAPI_HANDLE NBioBSP_Capture(std::string purpose, int timeout){
    if (purposeMap.find(purpose) == purposeMap.end()) {
        std::cout << "Invalid purpose" << std::endl;
        std::cout << "Valid purposes: verify, identify, enroll, enroll_for_verification, enroll_for_identification" << std::endl;
        // returns 1, workaround which i'll fix later
        return 1;
    }

    nbioApiReturn = NBioAPI_Capture(nbioApiHandle, purposeMap[purpose], &hCapturedFIR, timeout, NULL, NULL);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_Capture ERROR: " << nbioApiReturn << std::endl;
        return nbioApiReturn;
    }
    std::cout << "NBioAPI_Capture Success" << std::endl;

    return nbioApiHandle;
}

NBioAPI_FIR_TEXTENCODE NBioBSP_GetTextFIRFromHandle(NBioAPI_HANDLE nbioApiHandle){
    nbioApiReturn = NBioAPI_GetTextFIRFromHandle(nbioApiHandle, hCapturedFIR, &textFIR, NBioAPI_FALSE);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        std::cout << "NBioAPI_GetTextFIRFromHandle ERROR: " << nbioApiReturn << std::endl;
        // empty textFIR
        return textFIR;
    }

    return textFIR;
}

bool NBioBSP_Verify(NBioAPI_HANDLE nbioApiHandle){
    NBioAPI_FIR_TEXTENCODE extracted_fir = NBioBSP_GetTextFIRFromHandle(nbioApiHandle);
    NBioAPI_INPUT_FIR inputFIR;
    NBioAPI_BOOL result;
    inputFIR.Form = NBioAPI_FIR_FORM_TEXTENCODE;
    inputFIR.InputFIR.TextFIR = &extracted_fir;

    if (nbioApiHandle != NBioAPI_INVALID_HANDLE){
        nbioApiReturn = NBioAPI_Verify(nbioApiHandle, &inputFIR, &result, NULL, 10000, NULL, NULL);
        if (nbioApiReturn != NBioAPIERROR_NONE) {
            std::cout << "NBioAPI_Verify Invalid: " << nbioApiReturn << std::endl;
            return false;
        }
        std::cout << "NBioAPI_Verify result has been generated successfully" << std::endl;
        return result;
    } else {
        std::cout << "Invalid Handle" << std::endl;
        return false;
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
    module.def("extract_fir_text", &NBioBSP_GetTextFIRFromHandle, "Extract FIR Text from Handle");
    module.def("verify", &NBioBSP_Verify, "Capture NBioBSP Device for verification");
}