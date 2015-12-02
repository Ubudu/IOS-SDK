//
//  UbuduSDKDelegate.h
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
#import <CoreLocation/CoreLocation.h>

/**
 *  The trigger source of a rule.
 */
typedef NS_ENUM(NSUInteger, UbuduTriggerSource){
    /** Geofence triggered rule. */
    UbuduTriggerSources_GeofenceTrigger = 1,
    /** Beacon triggered rule. */
    UbuduTriggerSources_BeaconTrigger = 2
};

@class UbuduSDK;

/**
 *  The protocol you need to implement to receive events from the UbuduSDK.
 */
@protocol UbuduSDKDelegate <NSObject>

@optional

/*
 *  Methods below are used to ask you if an action should be executed or not when triggered by its associated rule.
 *  You can return NO to prevent the execution, YES to proceed. By default the actions are executed by the SDK.
 *
 *  @note You should NOT actually execute any action in these methods otherwise you may end with double rule executions and biased statistics.
 *  Implement the ubudu:executeXXXRequest:triggeredBy methods if you want to customize how the actions are executed.
 */

/**
 *  Invoked before an action of type "server notification" is executed. Gives you the opportunity to stop its execution.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param url The URL that would be used to perform an HTTP request.
 *  @param trigger The type of source at the origin of the rule triggering.
 *
 *  @return Return YES to proceed to the execution of the action, NO to stop it.
 */
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteServerNotificationRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger;

/**
 *  Invoked before an action of type "local notification" is executed. Gives you the opportunity to stop its execution.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param localNotification The local notification that would be presented.
 *  @param trigger The type of source at the origin of the rule triggering.
 *
 *  @return Return YES to proceed to the execution of the action, NO to stop it.
 */
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)trigger;

/**
 *  Invoked before an action of type "local notification" is executed. Gives you the opportunity to stop its execution. This method is useful if decision about executing the action is a long lasting process. Just call completionBlock with YES to execute an action or call it with NO to stop its execution. Implement it instead of - (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteServerNotificationRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param localNotification The local notification that would be presented.
 *  @param trigger The type of source at the origin of the rule triggering.
 *  @param completionBlock the block to call after making a decision. YES to execute the action. NO otherwise.
 *
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)trigger completionBlock:(void(^)(BOOL shouldExecuteLocalNotificationRequest))completionBlock;
/**
 *  Invoked before an action of type "open web page" is executed. Gives you the opportunity to stop its execution.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param url The URL of the web page that would be presented.
 *  @param trigger The type of source at the origin of the rule triggering.
 *
 *  @return Return YES to proceed to the execution of the action, NO to stop it.
 */
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger;

/**
 *  Invoked before an action of type "open passbook" is executed. Gives you the opportunity to stop its execution.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param passUrl The URL of the pass that would be presented.
 *  @param trigger The type of source at the origin of the rule triggering.
 *
 *  @return Return YES to proceed to the execution of the action, NO to stop it.
 */
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenPassbookRequest:(NSURL *)passUrl triggeredBy:(UbuduTriggerSource)trigger;

/**
 *  Invoked before an action of type "open deep link" is executed. Gives you the opportunity to stop its execution.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param url The URL of the deep link that would be opened.
 *  @param trigger The type of source at the origin of the rule triggering.
 *
 *  @return Return YES to proceed to the execution of the action, NO to stop it.
 */
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenDeepLinkRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger;



/**
 *  If implemented, invoked when an action of type "server notification" needs to be executed.
 *
 *  If you don't implement this method then the SDK automatically performs the HTTP request to the specified URL.
 *
 *  If you implement this method then it is your responsability to perform the HTTP request and parse the response.
 *  You also need to call the success or failure handler to let the SDK know that the action execution is done or failed.
 *  If you don't call any of the handlers the action won't appear in your statistics.
 *
 *  @param ubuduSDKThe Ubudu SDK singleton object.
 *  @param url The URL to use to perform an HTTP request.
 *  @param trigger The type of source at the origin of the trigger event.
 *  @param successHandler Block to call when the execution is done.
 *  @param failureHandler Block to call if the execution failed.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeServerNotificationRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger
      success:(void (^)())successHandler failure:(void (^)(NSError* error))failureHandler;

/**
 *  If implemented, invoked when an action of type "local notification" needs to be executed.
 *
 *  If you don't implement this method then the SDK automatically presents the `UILocalNotification` to the user
 *  by calling the `presentLocalNotificationNow:` method on the [`UIApplication` sharedApplication] object.
 *
 *  If you implement this method then it is your responsability to present the `UILocalNotification` to the user.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param localNotification The local notification to present.
 *  @param trigger The type of source at the origin of the trigger event.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)trigger;

/**
 *  If implemented, invoked when an action of type "open web page" needs to be executed.
 *
 *  If you don't implement this method, then the SDK automatically executes the action by presenting a modal web view controller on the topmost view controller it can detect.
 *  If you implement this method then it is your responsability to present the web page to the user.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param url The URL of the web page to open.
 *  @param trigger The type of source at the origin of the trigger event.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger;

/**
 *  If implemented, invoked when an action of type "open passbook pass" needs to be executed.
 *
 *  If you don't implement this method then the SDK automatically executes the action by presenting a modal `PKAddPassesViewController` on the topmost view controller it can detect.
 *  The PKAddPassesViewController is not presented if any of these criteria is true:
 *    - the PKPassLibrary is not available (unsupported or not linked with the app).
 *    - the pass data can't be downloaded (network unreachable, invalid pass URL...).
 *    - the pass is already present in the passbook of the user.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param passbookUrl The URL of the passbook to open. Can be a local or online resource, check the URL scheme.
 *  @param trigger The type of source at the origin of the trigger event.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenPassbookRequest:(NSURL *)passbookUrl triggeredBy:(UbuduTriggerSource)trigger;

/**
 *  If implemented, invoked when an action of type "open deep link" needs to be executed.
 *
 *  If you don't implement this method then the SDK automatically executes the action by calling `openURL:` on the [`UIApplication` sharedApplication] object.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param url The URL of the deep link to open.
 *  @param trigger The type of source at the origin of the trigger event.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenDeepLinkRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger;




/**
 *  Invoked when an event that will be sent to the Ubudu manager platform is generated by the SDK.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param event A dictionnary representation of the event data.
 *  @param eventDate Date and time at which the event was generated. This information is contained as well inside the event dictionnary.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didLogEvent:(NSDictionary *)event atTime:(NSDate *)eventDate;

/**
 *  Invoked when an error occurs in the SDK.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param error An error object describing what went wrong.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveErrorNotification:(NSError *)error;




/* ***************************
 * Beacons related callbacks
 * ***************************/

/**
 *  Invoked when the device enters the monitored beacon region.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param regionUUID Proximity UUID of the beacon region.
 *  @param userInfo Additional info on the beacon.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didEnterBeaconRegion:(NSString *)regionUUID userInfo:(NSDictionary *)userInfo;

/**
 *  Invoked when the device exits the monitored beacon region.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param regionUUID Proximity UUID of the beacon region.
 *  @param userInfo Additional info on the beacon.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didExitBeaconRegion:(NSString *)regionUUID userInfo:(NSDictionary *)userInfo;

/**
 *  Invoked when a new beacon is detected nearby the device.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param beaconName String identifier of the beacon.
 *  @param userInfo Additional info on the beacon.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didFindNewBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

/**
 *  Invoked each time ranging data are received from a beacon detected nearby the device.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param beaconName String identifier of the beacon.
 *  @param userInfo Additional info on the beacon.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceivePingFromBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

/**
 *  Invoked when the proximity of a beacon detected nearby the device changes.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param beaconName String identifier of the beacon.
 *  @param userInfo Additional info on the beacon.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didUpdateBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

/**
 *  Invoked when a previously detected beacon nearby the device becomes no longer visible.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param beaconName String identifier of the beacon.
 *  @param userInfo Additional info on the beacon.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didLoseBeaconSignal:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;




/* *****************************
 * Geofences related callbacks
 * *****************************/

/**
 *  Invoked when new device location data are available.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param newLocation The new location of the device.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveLocationChange:(CLLocation *)newLocation;

/**
 *  Invoked when the device entered a registered geofence.
 *
 *  Actions trigerred by this "geofence entry" event will have been executed before this method is invoked.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param region The entered geofence. Object is a `CLCircularRegion` on iOS 7 and above.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveEnterRegionNotification:(CLRegion *)region;

/**
 *  Invoked when the device exited a registered geofence.
 *
 *  Actions trigerred by this "geofence exit" event trigger will have been executred before this method is invoked.
 *
 *  @param ubuduSDK The Ubudu SDK singleton object.
 *  @param region The exited geofence. Object is a `CLCircularRegion` on iOS 7 and above.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveExitRegionNotification:(CLRegion *)region;

@end
