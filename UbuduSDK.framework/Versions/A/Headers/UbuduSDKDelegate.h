//
//  UbuduSDKDelegate.h
//  UbuduSDK
//
//  Created by Piotr Barszczewski on 6/20/13.
//  Copyright (c) 2013 Ubudu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

typedef NS_ENUM(NSInteger, UbuduTriggerSource) {
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
 * NOTE: You should NOT execute the actions in these methods.
 */
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)triggeredBy;
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)triggeredBy;
- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenPassbookRequest:(NSURL *)passbookUrl triggeredBy:(UbuduTriggerSource)triggeredBy;

/* Invoked when an action of type "local notification" should be executed.
 * If you don't implement this method, then the SDK automatically presents the UILocalNotification to the user
 * by calling the presentLocalNotificationNow: method on the [UIApplication sharedApplication] object.
 * If you implement this method then it is your responsability to present (or not) the UILocalNotification to the user
 * in a convenient way that depends on the current context of your app.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)triggeredBy;

/* Invoked when an action of type "open web page" should be executed.
 * If you don't implement this method, then the SDK automatically executes the action by presenting a modal web view on the windows' root view controller.
 * If you implement this method then it is your responsability to present (or not) the web page to the user
 * in a convenient way that depends on the current context of your app.
 * The ViewController is not presented if any of these is true:
 *   - The root ViewController of the UIApplication's window is already presenting a modal view controller.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)triggeredBy;

/* Invoked when an action of type "open passbook pass" has been executed.
 * The SDK first executes the action by presenting a modal PKAddPassesViewController on the root view controller of the UIWindow and then notify you with by invoking this method.
 * The PKAddPassesViewController is not presented if any of these criteria is true:
 *   - the PKPassLibrary is not available on the system.
 *   - the pass data can't be downloaded (network unreachable, invalid pass URL...).
 *   - the pass in already present in the passbook of the user.
 * Please note that this method is invoked even if the action is not executed.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenPassbookRequest:(NSURL *)passbookUrl triggeredBy:(UbuduTriggerSource)triggeredBy;

/*
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveRegionNotification:(NSDictionary *)notificationData triggeredBy:(UbuduTriggerSource)triggeredBy;

/* Invoked when a new "ad view" is received.
 * If you implement this method it is your responsability to present (or not) the ad to the user in a convenient way.
 * Iy you don't implement this method the SDK will present the ad for you if the following criteria are met:
 *   - the application state ([UIApplication sharedApplication].applicationState) is equal to UIApplicationStateActive.
 *   - you have set the adPlaceholder property of the SDK to a UView in which you want to display the ads.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveNewAdView:(UIView *)view triggeredBy:(UbuduTriggerSource)triggeredBy;

/* Called when an error occurs in the SDK.
 * The error object will contain information on the error that occured.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveErrorNotification:(NSError *)error;


/****************************
 * Beacon related callbacks
 ****************************/

/* Invoked when a new beacon is detected nearby the device.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didFindNewBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

/* Invoked each time ranging data are received from a beacon detected nearby the device.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didReceivePingFromBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

/* Invoked when at least one property of a beacon detected nearby the device changes.
 * For example this method is invoked when the proximity of a beacon changes.
 */
- (void)ubudu:(UbuduSDK *)ubuduSDK didUpdateBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

/* Invoked when a previously detected beacon nearby the device is no longer visible.
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
