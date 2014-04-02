//
//  UbuduErrorCodes.h
//  UbuduSDK
//
//  Created by Piotr Barszczewski on 6/20/13.
//  Copyright (c) 2013 Ubudu. All rights reserved.
//

#ifndef UbuduSDK_UbuduErrorCodes_h
#define UbuduSDK_UbuduErrorCodes_h

#define kUbuduErrorDomain            @"UbuduErrorDomain"

#define kUbuduErrorInfo_Key_Message  @"message"

typedef enum UbuduErrorCodes {
    UbuduError_UnknownError = 1,
    UbuduError_SDKNotStarted,
    UbuduError_SDKAlreadyStarted,
    UbuduError_SDKStartDataInitializationError,
    UbuduError_DeviceDoesNotRegionMonitoring,
    UbuduError_DeviceLocationDisabled,
    UbuduError_ApplicationNotAuthorizedForLocation,
    UbuduError_DeviceDoesNotSupportBeacons,
    UbuduError_DeviceBluetoothDisabled,
    UbuduError_UserInformationNotSet,
    UbuduError_UseNamespaceNotSet,
    
    UbuduError_Actions_NoDataFoundForRegionEntered = 100,     //this is an odd one. happens when there is no region data for a region which was registered which means that is was in the data storage before. could've been removed in the meantime
    UbuduError_Actions_DataForRegionNotYetAvailableDueToStartDate,
    UbuduError_Actions_DataForRegionNotAvailableDueToEndDateExpiration,
    
    UbuduError_API_ParamError = 200,
    UbuduError_API_ResponseParsingError,
    UbuduError_API_SecondGeofencesRequestsLaunched,
    UbuduError_API_GeofencesDownloadResponseCodeNot200,
    UbuduError_API_BadSDKVersion,
    UbuduError_API_RequestServerBadParam,
    
    UbuduError_Data_NSPersistentStoreCreationError = 500,
    UbuduError_Data_NSPersistentStoreOldVersionMigrationError,
    UbuduError_Data_NSPersistentStoreOldVersionRemovalError,
    UbuduError_Data_NSPersistentStoreOpeningError,
    UbuduError_Data_NSPersistentStoreDirectoryCreationError,
    UbuduError_Data_NSEntityDescriptionError,
    UbuduError_Data_NSPredicateParseError,
    UbuduError_Data_AttemptedToModifyDataWhileAnotherRequestIsPerformed,
    UbuduError_Data_UnableToSerializeRulesAndActionsToFieldsDataFormat,
    UbuduError_Data_UnableToAddNilRuleAndAction,
    UbuduError_Data_UnableToAddNilAction,
    UbuduError_Data_RemovingLocalDataFailed,
    
    UbuduError_Location_LocationUnavailable = 1000,
    UbuduError_Location_BackgroundLocationUnavailable,
    UbuduError_Location_RegionMonitoringUnavailable,
    UbuduError_Location_RegionRangingUnavailable,
    
    UbuduError_BLE_StartingFailed = 1100,
    UbuduError_BLE_ScanStartingFailed,
    
    UbuduError_Beacon_ConnectionTimeout = 1110,
    UbuduError_Beacon_ConnectionNotAllowedBySDK,
    
    UbuduError_Beacon_BatteryLevelUpdateNotAvailableForNotConnectedBeacon = 1120,
    UbuduError_Beacon_ServiceDiscoveryNotAvailableForNotConnectedBeacon,
    UbuduError_Beacon_SleepHoursSettingNotAvailableForNotConnectedBeacon,
} UbuduErrorCodes;

#endif
