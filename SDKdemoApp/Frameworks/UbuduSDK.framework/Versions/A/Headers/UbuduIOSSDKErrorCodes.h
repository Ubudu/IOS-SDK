//
//  UbuduIOSSDKErrorCodes.h
//  UbuduSDK
//
//  Created by Piotr Barszczewski on 6/20/13.
//  Copyright (c) 2013 Ubudu. All rights reserved.
//

#ifndef UbuduSDK_UbuduIOSSDKErrorCodes_h
#define UbuduSDK_UbuduIOSSDKErrorCodes_h

#define kUbuduIOSSDKErrorDomain            @"UbuduIOSSDKErrorDomain"

#define kUbuduIOSSDKErrorInfo_Key_Message  @"message"

typedef enum UbuduIOSSDKErrorCodes{
    UbuduIOSSDKError_UnknownError = 1,
    UbuduIOSSDKError_SDKNotStarted,
    UbuduIOSSDKError_SDKAlreadyStarted,
    UbuduIOSSDKError_SDKStartDataInitializationError,
    UbuduIOSSDKError_DeviceDoesNotRegionMonitoring,
    UbuduIOSSDKError_DeviceLocationDisabled,
    UbuduIOSSDKError_ApplicationNotAuthorizedForLocation,
    UbuduIOSSDKError_DeviceDoesNotSupportBeacons,
    UbuduIOSSDKError_DeviceBluetoothDisabled,
    UbuduIOSSDKError_UserInformationNotSet,
    UbuduIOSSDKError_UseNamespaceNotSet,
    
    UbuduIOSSDKError_Actions_NoDataFoundForRegionEntered = 100,     //this is an odd one. happens when there is no region data for a region which was registered which means that is was in the data storage before. could've been removed in the meantime
    UbuduIOSSDKError_Actions_DataForRegionNotYetAvailableDueToStartDate,
    UbuduIOSSDKError_Actions_DataForRegionNotAvailableDueToEndDateExpiration,
    
    UbuduIOSSDKError_API_ParamError = 200,
    UbuduIOSSDKError_API_ResponseParsingError,
    UbuduIOSSDKError_API_SecondGeofencesRequestsLaunched,
    UbuduIOSSDKError_API_GeofencesDownloadResponseCodeNot200,
    UbuduIOSSDKError_API_BadSDKVersion,
    UbuduIOSSDKError_API_RequestServerBadParam,
    
    UbuduIOSSDKError_Data_NSPersistentStoreCreationError = 500,
    UbuduIOSSDKError_Data_NSPersistentStoreOldVersionMigrationError,
    UbuduIOSSDKError_Data_NSPersistentStoreOldVersionRemovalError,
    UbuduIOSSDKError_Data_NSPersistentStoreOpeningError,
    UbuduIOSSDKError_Data_NSPersistentStoreDirectoryCreationError,
    UbuduIOSSDKError_Data_NSEntityDescriptionError,
    UbuduIOSSDKError_Data_NSPredicateParseError,
    UbuduIOSSDKError_Data_AttemptedToModifyDataWhileAnotherRequestIsPerformed,
    UbuduIOSSDKError_Data_UnableToSerializeRulesAndActionsToFieldsDataFormat,
    UbuduIOSSDKError_Data_UnableToAddNilRuleAndAction,
    UbuduIOSSDKError_Data_UnableToAddNilAction,
    UbuduIOSSDKError_Data_RemovingLocalDataFailed,
    
    UbuduIOSSDKError_Location_LocationUnavailable = 1000,
    UbuduIOSSDKError_Location_BackgroundLocationUnavailable,
    UbuduIOSSDKError_Location_RegionMonitoringUnavailable,
    UbuduIOSSDKError_Location_RegionRangingUnavailable,
    
    UbuduIOSSDKError_BLE_StartingFailed = 1100,
    UbuduIOSSDKError_BLE_ScanStartingFailed,
    
    UbuduIOSSDKError_Beacon_ConnectionTimeout = 1110,
    UbuduIOSSDKError_Beacon_ConnectionNotAllowedBySDK,
    
    UbuduIOSSDKError_Beacon_BatteryLevelUpdateNotAvailableForNotConnectedBeacon = 1120,
    UbuduIOSSDKError_Beacon_ServiceDiscoveryNotAvailableForNotConnectedBeacon,
    UbuduIOSSDKError_Beacon_SleepHoursSettingNotAvailableForNotConnectedBeacon,
} UbuduIOSSDKErrorCodes;

#endif
