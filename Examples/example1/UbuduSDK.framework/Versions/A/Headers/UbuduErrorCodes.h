//
//  UbuduErrorCodes.h
//  UbuduSDK
//
// Copyright (c) 2011, UBUDU SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//         SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#import <Foundation/Foundation.h>

/**
 *  Domain of the NSError objects returned by `UbuduSDK`
 */
#define kUbuduErrorDomain @"UbuduErrorDomain"

/**
 *  Error codes of the NSError objects returned by `UbuduSDK`
 */
typedef NS_ENUM(NSUInteger, UbuduErrorCodes) {
    UbuduError_None = 0,
    UbuduError_UnknownError = 1,
    UbuduError_SDKNotStarted = 2,
    UbuduError_SDKAlreadyStarted = 3,
    UbuduError_DataInitializationError = 4,
    UbuduError_DeviceDoesNotSupportGeofences = 5,
    UbuduError_DeviceDoesNotSupportBeacons = 6,
    UbuduError_NamespaceNotSet = 7,
    UbuduError_GeofencesDisabled = 8,
    UbuduError_BeaconsDisabled = 9,

    UbuduError_Actions_Error = 200,
    /** Odd error. Happens when there is no data for a region which was registered which means that it was in the data storage before. Could've been removed in the meantime. */
    UbuduError_Actions_NoDataFoundForRegionEntered = 201,
    UbuduError_Actions_DataForRegionNotYetAvailableDueToStartDate = 202,
    UbuduError_Actions_DataForRegionNotAvailableDueToEndDateExpiration = 203,
    UbuduError_Actions_DataForRegionNotAvailableDueToSchedule = 204,
    
    UbuduError_API_Error = 400,
    UbuduError_API_ParamError = 401,
    UbuduError_API_ResponseParsingError = 402,
    UbuduError_API_SecondGeofencesRequestsLaunched = 403,
    UbuduError_API_RegionsDownloadResponseCodeNot200 = 404,
    /** Received invalid JSON from HTTP request for a notify_server (server notification) action */
    UbuduError_API_RequestServerBadParam = 405,
    
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
