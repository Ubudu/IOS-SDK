//
//  UbuduErrorCodes.h
//  UbuduSDK
//
//  Created by Piotr Barszczewski on 6/20/13.
//  Copyright (c) 2013 Ubudu. All rights reserved.
//

/* Error returned as the domain to NSError from Ubudu.
 */
#define kUbuduErrorDomain           @"UbuduErrorDomain"

#define kUbuduErrorInfoKeyMessage   @"message"

typedef enum UbuduErrorCodes {
    UbuduError_UnknownError = 1,
    UbuduError_SDKNotStarted,
    UbuduError_SDKAlreadyStarted,
    UbuduError_SDKStartDataInitializationError,
    UbuduError_DeviceDoesNotSupportRegionMonitoring,
    UbuduError_DeviceLocationDisabled, // Currently not used
    UbuduError_ApplicationNotAuthorizedForLocation, // Currently not used
    UbuduError_DeviceDoesNotSupportBeacons,
    UbuduError_DeviceBluetoothDisabled, // Currently not used
    UbuduError_UserInformationNotSet, // Currently not used
    UbuduError_UseNamespaceNotSet,
    UbuduError_GeofencesDisabled, // Geofence specific features
    UbuduError_BeaconsDisabled, // Beacon specific features
    
    UbuduError_Actions_NoDataFoundForRegionEntered = 100, // This is an odd one. Happens when there is no region data for a region which was registered which means that is was in the data storage before. Could've been removed in the meantime.
    UbuduError_Actions_DataForRegionNotYetAvailableDueToStartDate,
    UbuduError_Actions_DataForRegionNotAvailableDueToEndDateExpiration,
    
    UbuduError_API_ParamError = 200,
    UbuduError_API_ResponseParsingError,
    UbuduError_API_SecondGeofencesRequestsLaunched,
    UbuduError_API_GeofencesDownloadResponseCodeNot200,
    UbuduError_API_BadSDKVersion,
    UbuduError_API_RequestServerBadParam,
    
    UbuduError_Data_NSPersistentStoreCreationError = 500, // Currently not used
    UbuduError_Data_NSPersistentStoreOldVersionMigrationError,
    UbuduError_Data_NSPersistentStoreOldVersionRemovalError,
    UbuduError_Data_NSPersistentStoreOpeningError,
    UbuduError_Data_NSPersistentStoreDirectoryCreationError,
    UbuduError_Data_NSEntityDescriptionError, // Currently not used
    UbuduError_Data_NSPredicateParseError,
    UbuduError_Data_AttemptedToModifyDataWhileAnotherRequestIsPerformed,
    UbuduError_Data_UnableToSerializeRulesAndActionsToFieldsDataFormat, // Currently not used
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
