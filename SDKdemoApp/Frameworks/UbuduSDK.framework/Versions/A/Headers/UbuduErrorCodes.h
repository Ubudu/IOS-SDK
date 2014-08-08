//
//  UbuduErrorCodes.h
//  UbuduSDK
//
//  Copyright (c) 2013 Ubudu. All rights reserved.
//

#import <Foundation/Foundation.h>

// Error returned as the domain to NSError from Ubudu.
#define kUbuduErrorDomain @"UbuduErrorDomain"

typedef NS_ENUM(NSUInteger, UbuduErrorCodes) {
    UbuduError_None = 0,
    UbuduError_UnknownError = 1,
    UbuduError_SDKNotStarted = 2,
    UbuduError_SDKAlreadyStarted = 3,
    UbuduError_DataInitializationError = 4,
    UbuduError_DeviceDoesNotSupportRegionMonitoring = 5,
    UbuduError_DeviceDoesNotSupportBeacons = 6,
    UbuduError_NamespaceNotSet = 7,
    UbuduError_GeofencesDisabled = 8,
    UbuduError_BeaconsDisabled = 9,

    UbuduError_Actions_Error = 200,
    UbuduError_Actions_NoDataFoundForRegionEntered = 201, // Odd error. Happens when there is no data for a region which was registered which means that it was in the data storage before. Could've been removed in the meantime.
    UbuduError_Actions_DataForRegionNotYetAvailableDueToStartDate = 202,
    UbuduError_Actions_DataForRegionNotAvailableDueToEndDateExpiration = 203,
    UbuduError_Actions_DataForRegionNotAvailableDueToSchedule = 204,
    
    UbuduError_API_Error = 400,
    UbuduError_API_ParamError = 401,
    UbuduError_API_ResponseParsingError = 402,
    UbuduError_API_SecondGeofencesRequestsLaunched = 403,
    UbuduError_API_RegionsDownloadResponseCodeNot200 = 404,
    UbuduError_API_RequestServerBadParam = 405, // Received invalid JSON from HTTP request for notify_server action
    
    UbuduError_Data_Error = 600,
    UbuduError_Data_NSPersistentStoreOldVersionMigrationError = 601,
    UbuduError_Data_NSPersistentStoreOldVersionRemovalError = 602,
    UbuduError_Data_NSPersistentStoreOpeningError = 603,
    UbuduError_Data_NSPersistentStoreDirectoryCreationError = 604,
    UbuduError_Data_NSPredicateParseError = 605,
    UbuduError_Data_AttemptedToModifyDataWhileAnotherRequestIsPerformed = 606,
    UbuduError_Data_UnableToAddNilRuleAndAction = 607,
    UbuduError_Data_UnableToAddNilAction = 608,
    UbuduError_Data_RemovingLocalDataFailed = 609,
    
    UbuduError_Location_Error = 800,
    UbuduError_Location_LocationUnavailable = 801,
    UbuduError_Location_RegionMonitoringUnavailable = 802,
    
    UbuduError_Beacon_Error = 1000,
    UbuduError_Beacon_AlreadyStarted = 1001,
    UbuduError_Beacon_NotStarted = 1002
};
