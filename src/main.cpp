// THIS CODE FOLLOWS NITGEN'S NBioBSP SDK OLD STANDARD
// so dont judge me, exceptions in C++ are problematic, but because of pybind11, I've used it.
// all code is in a single file as it is just a wrapper for the NBioBSP SDK, so it is easier to maintain and faster to understand the code flow
#include <iostream>
#include <unordered_map>
#include <exception>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <NBioAPI.h>
#include <NBioAPI_IndexSearch.h>

namespace py = pybind11;

// vars that are reused constantly
// depending on the function, other types are declared inside the function scope
NBioAPI_HANDLE nbioApiHandle;
NBioAPI_DEVICE_ID nbioApiDeviceId;
NBioAPI_RETURN nbioApiReturn;
NBioAPI_VERSION version;
NBioAPI_FIR_PURPOSE purpose;
NBioAPI_FIR_HANDLE hCapturedFIR;
NBioAPI_FIR_TEXTENCODE textFIR;
bool indexSearchEngineState;

// custom exception handler class, will be thrown in python
class NBioAPIException : public std::exception {
public:
    NBioAPIException(NBioAPI_RETURN errCode) : errorCode(errCode) {}
    virtual const char* what() const throw() {
        switch (errorCode) {
        case NBioAPIERROR_INVALID_HANDLE:
            return "Invalid handle. Maybe the handle wasn't initialized.";
        case NBioAPIERROR_INVALID_POINTER:
            return "Invalid pointer. Maybe there's no fingerprint registered on your handle.";
        case NBioAPIERROR_INVALID_TYPE:
            return "Invalid type";
        case NBioAPIERROR_FUNCTION_FAIL:
            return "Function failed";
        case NBioAPIERROR_STRUCTTYPE_NOT_MATCHED:
            return "Structure type not matched";
        case NBioAPIERROR_ALREADY_PROCESSED:
            return "Data already processed";
        case NBioAPIERROR_EXTRACTION_OPEN_FAIL:
            return "Extraction open failed";
        case NBioAPIERROR_VERIFICATION_OPEN_FAIL:
            return "Verification open failed";
        case NBioAPIERROR_DATA_PROCESS_FAIL:
            return "Data processing failed";
        case NBioAPIERROR_MUST_BE_PROCESSED_DATA:
            return "Data must be processed";
        case NBioAPIERROR_INTERNAL_CHECKSUM_FAIL:
            return "Internal checksum failed";
        case NBioAPIERROR_ENCRYPTED_DATA_ERROR:
            return "Encrypted data error";
        case NBioAPIERROR_UNKNOWN_FORMAT:
            return "Unknown format";
        case NBioAPIERROR_UNKNOWN_VERSION:
            return "Unknown version";
        case NBioAPIERROR_VALIDITY_FAIL:
            return "Validity check failed";
        case NBioAPIERROR_INIT_MAXFINGER:
            return "Max finger initialization failed";
        case NBioAPIERROR_INIT_SAMPLESPERFINGER:
            return "Samples per finger initialization failed";
        case NBioAPIERROR_INIT_ENROLLQUALITY:
            return "Enroll quality initialization failed";
        case NBioAPIERROR_INIT_VERIFYQUALITY:
            return "Verify quality initialization failed";
        case NBioAPIERROR_INIT_IDENTIFYQUALITY:
            return "Identify quality initialization failed";
        case NBioAPIERROR_INIT_SECURITYLEVEL:
            return "Security level initialization failed";
        case NBioAPIERROR_INVALID_MINSIZE:
            return "Invalid min size";
        case NBioAPIERROR_INVALID_TEMPLATE:
            return "Invalid template";
        case NBioAPIERROR_EXPIRED_VERSION:
            return "Expired version";
        case NBioAPIERROR_INVALID_SAMPLESPERFINGER:
            return "Invalid samples per finger";
        case NBioAPIERROR_UNKNOWN_INPUTFORMAT:
            return "Unknown input format";
        case NBioAPIERROR_INIT_ENROLLSECURITYLEVEL:
            return "Enroll security level initialization failed";
        case NBioAPIERROR_INIT_NECESSARYENROLLNUM:
            return "Necessary enroll number initialization failed";
        case NBioAPIERROR_INIT_RESERVED1:
            return "Reserved initialization error 1";
        case NBioAPIERROR_INIT_RESERVED2:
            return "Reserved initialization error 2";
        case NBioAPIERROR_INIT_RESERVED3:
            return "Reserved initialization error 3";
        case NBioAPIERROR_INIT_RESERVED4:
            return "Reserved initialization error 4";
        case NBioAPIERROR_INIT_RESERVED5:
            return "Reserved initialization error 5";
        case NBioAPIERROR_INIT_RESERVED6:
            return "Reserved initialization error 6";
        case NBioAPIERROR_INIT_RESERVED7:
            return "Reserved initialization error 7";
        case NBioAPIERROR_OUT_OF_MEMORY:
            return "Out of memory";
        case NBioAPIERROR_DEVICE_OPEN_FAIL:
            return "Device open failed";
        case NBioAPIERROR_INVALID_DEVICE_ID:
            return "Invalid device ID";
        case NBioAPIERROR_WRONG_DEVICE_ID:
            return "Wrong device ID";
        case NBioAPIERROR_DEVICE_ALREADY_OPENED:
            return "Device already opened";
        case NBioAPIERROR_DEVICE_NOT_OPENED:
            return "Device not opened";
        case NBioAPIERROR_DEVICE_BRIGHTNESS:
            return "Device brightness error";
        case NBioAPIERROR_DEVICE_CONTRAST:
            return "Device contrast error";
        case NBioAPIERROR_DEVICE_GAIN:
            return "Device gain error";
        case NBioAPIERROR_LOWVERSION_DRIVER:
            return "Low version driver error";
        case NBioAPIERROR_DEVICE_INIT_FAIL:
            return "Device initialization failed";
        case NBioAPIERROR_DEVICE_LOST_DEVICE:
            return "Device lost";
        case NBioAPIERROR_DEVICE_DLL_LOAD_FAIL:
            return "Device DLL load failed";
        case NBioAPIERROR_DEVICE_MAKE_INSTANCE_FAIL:
            return "Device instance creation failed";
        case NBioAPIERROR_DEVICE_DLL_GET_PROC_FAIL:
            return "Device DLL get procedure failed";
        case NBioAPIERROR_DEVICE_IO_CONTROL_FAIL:
            return "Device IO control failed";
        case NBioAPIERROR_DEVICE_NOT_SUPPORT:
            return "Device not supported";
        case NBioAPIERROR_DEVICE_LFD:
            return "Device LFD error";
        case NBioAPIERROR_INVALID_DEVICE_CODE:
            return "Invalid device code";
        case NBioAPIERROR_DEVICE_NOT_FOUND:
            return "Device not found";
        case NBioAPIERROR_USER_CANCEL:
            return "User cancelled";
        case NBioAPIERROR_USER_BACK:
            return "User went back";
        case NBioAPIERROR_CAPTURE_TIMEOUT:
            return "Capture timeout";
        case NBioAPIERROR_CAPTURE_FAKE_SUSPICIOUS:
            return "Fake finger detected";
        case NBioAPIERROR_ENROLL_EVENT_PLACE:
            return "Place finger on sensor";
        case NBioAPIERROR_ENROLL_EVENT_HOLD:
            return "Hold finger on sensor";
        case NBioAPIERROR_ENROLL_EVENT_REMOVE:
            return "Remove finger from sensor";
        case NBioAPIERROR_ENROLL_EVENT_PLACE_AGAIN:
            return "Place finger on sensor again";
        case NBioAPIERROR_ENROLL_EVENT_EXTRACT:
            return "Extracting template";
        case NBioAPIERROR_ENROLL_EVENT_MATCH_FAILED:
            return "Enrollment match failed";
        case NBioAPIERROR_INIT_MAXCANDIDATE:
            return "Max candidate initialization failed";
        case NBioAPIERROR_NSEARCH_OPEN_FAIL:
            return "NSearch open failed";
        case NBioAPIERROR_NSEARCH_INIT_FAIL:
            return "NSearch initialization failed";
        case NBioAPIERROR_NSEARCH_MEM_OVERFLOW:
            return "NSearch memory overflow";
        case NBioAPIERROR_NSEARCH_SAVE_DB:
            return "NSearch save database failed";
        case NBioAPIERROR_NSEARCH_LOAD_DB:
            return "NSearch load database failed";
        case NBioAPIERROR_NSEARCH_INVALD_TEMPLATE:
            return "NSearch invalid template";
        case NBioAPIERROR_NSEARCH_OVER_LIMIT:
            return "NSearch over limit";
        case NBioAPIERROR_NSEARCH_IDENTIFY_FAIL:
            return "NSearch identification failed";
        case NBioAPIERROR_NSEARCH_LICENSE_LOAD:
            return "NSearch license load failed";
        case NBioAPIERROR_NSEARCH_LICENSE_KEY:
            return "NSearch license key error";
        case NBioAPIERROR_NSEARCH_LICENSE_EXPIRED:
            return "NSearch license expired";
        case NBioAPIERROR_NSEARCH_DUPLICATED_ID:
            return "NSearch duplicated ID";
        case NBioAPIERROR_NSEARCH_INVALID_ID:
            return "NSearch invalid ID";
        case NBioAPIERROR_IMGCONV_INVALID_PARAM:
            return "Image conversion invalid parameter";
        case NBioAPIERROR_IMGCONV_MEMALLOC_FAIL:
            return "Image conversion memory allocation failed";
        case NBioAPIERROR_IMGCONV_FILEOPEN_FAIL:
            return "Image conversion file open failed";
        case NBioAPIERROR_IMGCONV_FILEWRITE_FAIL:
            return "Image conversion file write failed";
        case NBioAPIERROR_INIT_PRESEARCHRATE:
            return "Presearch rate initialization failed";
        case NBioAPIERROR_INDEXSEARCH_INIT_FAIL:
            return "Index search initialization failed";
        case NBioAPIERROR_INDEXSEARCH_SAVE_DB:
            return "Index search save database failed";
        case NBioAPIERROR_INDEXSEARCH_LOAD_DB:
            return "Index search load database failed";
        case NBioAPIERROR_INDEXSEARCH_UNKNOWN_VER:
            return "Index search unknown version";
        case NBioAPIERROR_INDEXSEARCH_IDENTIFY_FAIL:
            return "Index search identification failed";
        case NBioAPIERROR_INDEXSEARCH_DUPLICATED_ID:
            return "Index search duplicated ID";
        case NBioAPIERROR_INDEXSEARCH_IDENTIFY_STOP:
            return "Index search identification stopped";
        default:
            return "Unknown error";
        }
    }
private:
    NBioAPI_RETURN errorCode;
};

// purpose map
std::unordered_map<std::string, NBioAPI_FIR_PURPOSE> purposeMap = {
    {"verify", NBioAPI_FIR_PURPOSE_VERIFY},
    {"identify", NBioAPI_FIR_PURPOSE_IDENTIFY},
    {"enroll", NBioAPI_FIR_PURPOSE_ENROLL},
    {"enroll_for_verification", NBioAPI_FIR_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY},
    {"enroll_for_identification", NBioAPI_FIR_PURPOSE_ENROLL_FOR_IDENTIFICATION_ONLY}
    // {"audit", NBioAPI_FIR_PURPOSE_AUDIT},
    // {"update", NBioAPI_FIR_PURPOSE_UPDATE}
};


// ---------------------------------- FUNCTIONS ---------------------------------- //


NBioAPI_HANDLE NBioBSP_Initialize() {
    if (nbioApiHandle != NULL) {
        throw std::invalid_argument("NBioBSP is already initialized");
    }

    nbioApiReturn = NBioAPI_Init(&nbioApiHandle);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    std::cout << "Initialized the handle successfully\n";
    return nbioApiHandle;
}

void NBioBSP_Terminate(){
    if (nbioApiHandle == NULL) {
        throw std::invalid_argument("NBioBSP is already terminated");
    }

    nbioApiReturn = NBioAPI_Terminate(nbioApiHandle);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    nbioApiHandle = NULL;    // overwrite the handle to NULL, as terminate returns something else and I want to follow some sort of standard
    std::cout << "Terminated successfully\n";
    return;
}

std::string NBioBSP_GetVersion() {
    nbioApiReturn = NBioAPI_GetVersion(nbioApiHandle, &version);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    return std::to_string(version.Major) + "." + std::to_string(version.Minor);
}

// This function is to retrieve the more detail information about device include number of devices and device IDs attached to the system. <-- from Nitgen's NBioBSP SDK
std::vector<std::unordered_map<std::string, std::string>> NBioBSP_EnumeratedDeviceExtra() {
    NBioAPI_UINT32 nDeviceNum;
    NBioAPI_DEVICE_ID *pDeviceList;
    NBioAPI_DEVICE_INFO_EX *pDeviceInfoEx;

    nbioApiReturn = NBioAPI_EnumerateDeviceEx(nbioApiHandle, &nDeviceNum, &pDeviceList, &pDeviceInfoEx);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    std::vector<std::unordered_map<std::string, std::string>> deviceList(nDeviceNum);
    for (int i = 0; i < nDeviceNum; i++) {
        deviceList[i]["Device ID"] = std::to_string(pDeviceList[i]);
        deviceList[i]["Name ID"] = std::to_string(pDeviceInfoEx[i].NameID);
        deviceList[i]["Instance"] = std::to_string(pDeviceInfoEx[i].Instance);
        deviceList[i]["Name"] = pDeviceInfoEx[i].Name;
        deviceList[i]["Description"] = pDeviceInfoEx[i].Description;
        deviceList[i]["Dll"] = pDeviceInfoEx[i].Dll;
        deviceList[i]["Sys"] = pDeviceInfoEx[i].Sys;
        deviceList[i]["AutoOn"] = std::to_string(pDeviceInfoEx[i].AutoOn);
        deviceList[i]["Brightness"] = std::to_string(pDeviceInfoEx[i].Brightness);
        deviceList[i]["Contrast"] = std::to_string(pDeviceInfoEx[i].Contrast);
        deviceList[i]["Gain"] = std::to_string(pDeviceInfoEx[i].Gain);
    }

    return deviceList;
}

void NBioBSP_OpenDevice(){
    nbioApiDeviceId = NBioAPI_DEVICE_ID_AUTO;
    nbioApiReturn = NBioAPI_OpenDevice(nbioApiHandle, nbioApiDeviceId);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    std::cout << "Device Opened Successfully (Device ID): " << nbioApiDeviceId << std::endl;
}

// pass the device ID (pDeviceInfoEx from NBioBSP_EnumerateDeviceExtra)
void NBioBSP_OpenSpecificDevice(NBioAPI_DEVICE_ID nbioApiDeviceId) {
    nbioApiReturn = NBioAPI_OpenDevice(nbioApiHandle, nbioApiDeviceId);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    std::cout << "Device Opened Successfully (Device ID): " << nbioApiDeviceId << std::endl;
}

// returns the device ID of the opened device, 0 if no device is opened, 255 if auto
NBioAPI_DEVICE_ID NBioBSP_GetOpenedDeviceID(){
    // no exception handling here, as it numbers returned are treated as errors
    nbioApiReturn = NBioAPI_GetOpenedDeviceID(nbioApiHandle);
    return nbioApiReturn;
}

// closes all devices
void NBioBSP_CloseDevice(){
    nbioApiDeviceId = NBioAPI_DEVICE_ID_AUTO;       // detects which devices to close
    nbioApiReturn = NBioAPI_CloseDevice(nbioApiHandle, nbioApiDeviceId);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    std::cout << "The devices were closed\n";
}

// captures the fingerprint and stores it in the handle, so it can be used later in other functions
NBioAPI_HANDLE NBioBSP_Capture(std::string purpose, int timeout){
    if (purposeMap.find(purpose) == purposeMap.end()) {
        throw std::invalid_argument("Invalid purpose");
    }

    nbioApiReturn = NBioAPI_Capture(nbioApiHandle, purposeMap[purpose], &hCapturedFIR, timeout, NULL, NULL);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    std::cout << "Fingerprint captured, stored in handle\n";
    return nbioApiHandle;
}

// extracts the FIR text from the handle
std::string NBioBSP_GetTextFIRFromHandle(NBioAPI_HANDLE nbioApiHandle){
    nbioApiReturn = NBioAPI_GetTextFIRFromHandle(nbioApiHandle, hCapturedFIR, &textFIR, NBioAPI_FALSE);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    return textFIR.TextFIR;
}

// Remember, it only verifies the fingerprint against the one that is currently on the handle, which is only the last one captured
bool NBioBSP_Verify(NBioAPI_HANDLE nbioApiHandle){
    std::string extracted_fir = NBioBSP_GetTextFIRFromHandle(nbioApiHandle);

    NBioAPI_FIR_TEXTENCODE mouldFirText;
    mouldFirText.TextFIR = &extracted_fir[0];

    NBioAPI_INPUT_FIR inputFIR;
    inputFIR.Form = NBioAPI_FIR_FORM_TEXTENCODE;
    inputFIR.InputFIR.TextFIR = &mouldFirText;

    NBioAPI_BOOL result;

    nbioApiReturn = NBioAPI_Verify(nbioApiHandle, &inputFIR, &result, NULL, 10000, NULL, NULL);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    return result;
}

bool NBioBSP_InitIndexSearchEngine(){
    if (indexSearchEngineState) {
        throw std::invalid_argument("Index Search Engine is already initialized");
    }

    nbioApiReturn = NBioAPI_InitIndexSearchEngine(nbioApiHandle);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    indexSearchEngineState = true;
    std::cout << "Index Search Engine Initialized\n";
    return true;
}

bool NBioBSP_GetIndexSearchState(){
    return indexSearchEngineState;
}

bool NBioBSP_TerminateIndexSearchEngine(){
    if (!indexSearchEngineState) {
        throw std::invalid_argument("Index Search Engine is already terminated");
    }

    nbioApiReturn = NBioAPI_TerminateIndexSearchEngine(nbioApiHandle);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    indexSearchEngineState = false;
    std::cout << "Index Search Engine Terminated\n";
    return true;
}

bool NBioBSP_AddFIRToIndexSearchDB(std::string firText, NBioAPI_UINT32 userId){
    NBioAPI_INDEXSEARCH_SAMPLE_INFO sampleInfo;
    NBioAPI_FIR_TEXTENCODE mouldFirText;
    mouldFirText.TextFIR = &firText[0];

    NBioAPI_INPUT_FIR inputFIR;
    inputFIR.Form = NBioAPI_FIR_FORM_TEXTENCODE;
    inputFIR.InputFIR.TextFIR = &mouldFirText;

    nbioApiReturn = NBioAPI_AddFIRToIndexSearchDB(nbioApiHandle, &inputFIR, userId, &sampleInfo);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    std::cout << "FIR Added to Index Search Database\n";
    return true;
}

NBioAPI_UINT32 NBioBSP_GetDataCountFromIndexSearchDB(){
    NBioAPI_UINT32 dataCount;
    nbioApiReturn = NBioAPI_GetDataCountFromIndexSearchDB(nbioApiHandle, &dataCount);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    return dataCount;
}

uint32_t NBioBSP_IdentifyDataFromIndexSearchDB(std::string firText) {
    NBioAPI_FIR_TEXTENCODE mouldFirText;
    mouldFirText.TextFIR = &firText[0];

    NBioAPI_INPUT_FIR inputFIR;
    inputFIR.Form = NBioAPI_FIR_FORM_TEXTENCODE;
    inputFIR.InputFIR.TextFIR = &mouldFirText;

    NBioAPI_INDEXSEARCH_FP_INFO fpInfo;

    NBioAPI_RETURN nbioApiReturn = NBioAPI_IdentifyDataFromIndexSearchDB(nbioApiHandle, &inputFIR, 5, &fpInfo, NULL);
    if (nbioApiReturn != NBioAPIERROR_NONE) {
        throw NBioAPIException(nbioApiReturn);
    }

    return fpInfo.ID;
}

PYBIND11_MODULE(_core, module) {
    module.doc() = "Python bindings for NBioBSP";
    module.def("initialize_handle", &NBioBSP_Initialize, "Initialize NBioBSP");
    module.def("terminate_handle", &NBioBSP_Terminate, "Terminate NBioBSP");
    module.def("get_version", &NBioBSP_GetVersion, "Get NBioBSP Version");
    module.def("enumerate_device", &NBioBSP_EnumeratedDeviceExtra, "Enumerate NBioBSP Devices with extra info");
    module.def("open_device", &NBioBSP_OpenDevice, "Open NBioBSP Device");
    module.def("open_specific_device", &NBioBSP_OpenSpecificDevice, "Open NBioBSP Device with specific ID");
    module.def("is_device_open", &NBioBSP_GetOpenedDeviceID, "Get NBioBSP Opened Device ID");
    module.def("close_device", &NBioBSP_CloseDevice, "Close NBioBSP Device");
    module.def("capture", &NBioBSP_Capture, "Capture Fingerprint");
    module.def("extract_fir_text", &NBioBSP_GetTextFIRFromHandle, "Extract FIR Text from Handle");
    module.def("verify", &NBioBSP_Verify, "Fingerprint Verification");

    module.def("init_index_search", &NBioBSP_InitIndexSearchEngine, "Initialize Index Search Engine");
    module.def("get_index_search_state", &NBioBSP_GetIndexSearchState, "Get Index Search Engine State");
    module.def("terminate_index_search", &NBioBSP_TerminateIndexSearchEngine, "Terminate Index Search Engine");
    module.def("add_fir_to_index_search", &NBioBSP_AddFIRToIndexSearchDB, "Add FIR to Index Search Database");
    module.def("data_count_from_index_search", &NBioBSP_GetDataCountFromIndexSearchDB, "Data Count from Index Search Database");
    module.def("identify_data_from_index_search", &NBioBSP_IdentifyDataFromIndexSearchDB, "Identify Data from Index Search Database");
}