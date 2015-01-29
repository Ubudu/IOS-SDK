//
//  UbuduSDKDelegate.h
//  UbuduSDK
//
// Copyright (c) 2011-2015, UBUDU SAS
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

typedef NS_ENUM(NSUInteger, UbuduTriggerSource) {
    UbuduTriggerSources_GeofenceTrigger = 1,
    UbuduTriggerSources_BeaconTrigger = 2
};

@class UbuduSDK;

@protocol UbuduSDKDelegate <NSObject>

@optional

/* Methods used to ask if an action should be executed or not when it has been triggered by an associated rule.
 * Return NO to prevent the execution, YES to proceed.
 * By default the action is executed by the SDK. You can implement the ubudu:executeXXXRequest:triggeredBy methods if you want to customize how the actions should be executed.
 *
 * NOTE: You should NOT execute the actions in these methods otherwise your statistics may become biased.
 */
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteServerNotificationRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)triggeredBy;
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)triggeredBy;
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)triggeredBy;
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenPassbookRequest:(NSURL *)passUrl triggeredBy:(UbuduTriggerSource)triggeredBy;
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenDeepLinkRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)triggeredBy;

/* Invoked when an action of type "server notification" should be executed.
 * If you don't implement this method, then the SDK automatically perform the HTTP request to the specified URL.
 * If you implement this method then it is your responsability to perform the HTTP request and parse the response.
 * You also need to call the success or failure handler to let the SDK know when the action is done. If you don't call
 * it then your action won't appear in the statistics.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeServerNotificationRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)triggeredBy
      success:(void (^)())successHandler failure:(void (^)(NSError* error))failureHandler;

/* Invoked when an action of type "local notification" should be executed.
 * If you don't implement this method, then the SDK automatically presents the UILocalNotification to the user
 * by calling the presentLocalNotificationNow: method on the [UIApplication sharedApplication] object.
 * If you implement this method then it is your responsability to present the UILocalNotification to the user
 * in a convenient way that depends on the current context of your app.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)triggeredBy;

/* Invoked when an action of type "open web page" should be executed.
 * If you don't implement this method, then the SDK automatically executes the action by presenting a modal web view on the root view controller of the UIWindow.
 * If you implement this method then it is your responsability to present the web page to the user
 * in a convenient way that depends on the current context of your app.
 * The ViewController is not presented if any of these is true:
 *   - the root ViewController of the UIApplication's window is already presenting a modal view controller.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)triggeredBy;

/* Invoked when an action of type "open passbook pass" should be executed.
 * If you don't implement this method, then the SDK automatically executes the action presenting a modal PKAddPassesViewController on the root view controller of the UIWindow.
 * The PKAddPassesViewController is not presented if any of these criteria is true:
 *   - the PKPassLibrary is not available on the system.
 *   - the pass data can't be downloaded (network unreachable, invalid pass URL...).
 *   - the pass is already present in the passbook of the user.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenPassbookRequest:(NSURL *)passbookUrl triggeredBy:(UbuduTriggerSource)triggeredBy;

/* Invoked when an action of type "open deep link" should be executed.
 * If you don't implement this method, then the SDK automatically executes the action.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenDeepLinkRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)triggeredBy;

/* Invoked when a new "ad view" is received.
 * If you implement this method it is your responsability to present (or not) the ad to the user in a convenient way.
 * Iy you don't implement this method the SDK will present the ad for you if the following criteria are met:
 *   - the application state [UIApplication sharedApplication].applicationState is equal to UIApplicationStateActive.
 *   - you have set the adPlaceholder property of the SDK to a UIView in which you want to display the ads.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveNewAdView:(UIView *)view triggeredBy:(UbuduTriggerSource)triggeredBy;

/* Called when an error occurs in the SDK.
 * The error object will contain information on the error that occured.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveErrorNotification:(NSError *)error;


/****************************
 * Beacons related callbacks
 ****************************/

/* Invoked when the device enters the monitored beacon region.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didEnterBeaconRegion:(NSString *)regionUUID userInfo:(NSDictionary *)userInfo;

/* Invoked when the device exits the monitored beacon region.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didExitBeaconRegion:(NSString *)regionUUID userInfo:(NSDictionary *)userInfo;

/* Invoked when a new beacon is detected nearby the device.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didFindNewBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

/* Invoked each time ranging data are received from a beacon detected nearby the device.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceivePingFromBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

/* Invoked when the proximity of a beacon detected nearby the device changes.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didUpdateBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

/* Invoked when a previously detected beacon nearby the device becomes no longer visible.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didLoseBeaconSignal:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;


/*******************
 * Debug callbacks
 *******************/

/* Invoked when new geo location information are available.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveLocationChange:(CLLocation *)newLocation;

/* Invoked when the device entered a registered geofence.
 * Actions trigerred by this "geofence entry" event trigger will have been executed before this method is invoked.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveEnterRegionNotification:(CLRegion *)region;

/* Invoked when the device exited a registered geofence.
 * Actions trigerred by this "geofence exit" event trigger will have been executred before this method is invoked.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveExitRegionNotification:(CLRegion *)region;

/* Invoked when internal debug data are sent to the public API for debugging and testing purpose.
 * You should not need to implement this method.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveDebugData:(id)data;

@end
