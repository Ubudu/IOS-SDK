//
//  UbuduSDKDelegate.h
//  UbuduSDK
//
//  Created by Piotr Barszczewski on 6/20/13.
//  Copyright (c) 2013 Ubudu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

typedef NS_ENUM(NSInteger, UbuduIOSSDKTriggerSource) {
    UbuduIOSSDKTriggerSources_GeofenceTrigger = 1,
    UbuduIOSSDKTriggerSources_BeaconTrigger,
};

@protocol UbuduIOSSDKDelegate <NSObject>

@optional


/* Invoked when an action of type "open web page" has been executed.
 * The SDK first executes the action by presenting a modal web view on the windows' root view controller and then notify you with this method.
 * The ViewController is not presented if any of these is true:
 *   - The root ViewController of the UIApplication's window is already presenting a modal view controller.
 */
- (void)ubuduIOSSDK_receivedOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy;

/* Invoked when an action of type "open passbook pass" has been executed.
 * The SDK first executes the action by presenting a modal PKAddPassesViewController on the root view controller of the UIWindow and then notify you with by invoking this method.
 * The PKAddPassesViewController is not presented if any of these criteria is true:
 *   - the PKPassLibrary is not available on the system.
 *   - the pass data can't be downloaded (network unreachable, invalid pass URL...).
 *   - the pass in already present in the passbook of the user.
 * Please note that this method is invoked even if the action is not executed.
 */
- (void)ubuduIOSSDK_receivedOpenPassbookRequest:(NSURL *)aPassbookUrl triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy;

/*
 */
- (void)ubuduIOSSDK_receivedRegionNotification:(NSDictionary *)notificationData triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy;

/* Invoked when an action of type "local notification" should be executed.
 * If you don't implement this method, then the SDK automatically presents the UILocalNotification to the user
 * by calling the presentLocalNotificationNow: method on the [UIApplication sharedApplication] object.
 * If you implement this method then it is your responsability to present (or not) the UILocalNotification to the user in a convenient way.
 */
- (void)ubuduIOSSDK_receivedLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy;

/* Invoked when a new "ad view" is received.
 * If you implement this method it is your responsability to present (or not) the ad to the user in a convenient way.
 * Iy you don't implement this method the SDK will present the ad for you if the following criteria are met:
 *   - the application state ([UIApplication sharedApplication].applicationState) is equal to UIApplicationStateActive.
 *   - you have set the adPlaceholder property of the SDK to a UView in which you want to display the ads.
 */
- (void)ubuduIOSSDK_receivedNewAdView:(UIView *)view triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy;

/* Called when an error occurs in the SDK.
 * The error object will contain information on the error that occured.
 */
- (void)ubuduIOSSDK_receivedErrorNotification:(NSError *)error;


/****************************
 * Beacon related callbacks
 ****************************/

/* Invoked when a new beacon is detected nearby the device.
 */
- (void)ubuduIOSSDK_foundNewBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

/* Invoked each time ranging data are received from a beacon detected nearby the device.
 */
- (void)ubuduIOSSDK_pingReceivedFromBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

/* Invoked when at least one property of a beacon detected nearby the device changes.
 * For example this method is invoked when the proximity of a beacon changes.
 */
- (void)ubuduIOSSDK_updatedBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

/* Invoked when a previously detected beacon nearby the device is no longer visible.
 */
- (void)ubuduIOSSDK_lostBeaconSignal:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;


/*******************
 * Debug callbacks
 *******************/

/* Invoked when new geo location information are available.
 */
- (void)ubuduIOSSDK_receivedLocationChange:(CLLocation *)newLocation;

/* Invoked when the device entered a registered geofence.
 * Actions trigerred by this "geofence entry" trigger event will have been executred before this method is invoked.
 */
- (void)ubuduIOSSDK_receivedEnterRegionNotification:(CLRegion *)region;

/* Invoked when the device exited a registered geofence.
 * Actions trigerred by this "geofence exit" trigger event will have been executred before this method is invoked.
 */
- (void)ubuduIOSSDK_receivedExitRegionNotification:(CLRegion *)region;

/* Invoked when internal debug data are sent to the public API for debugging and testing purpose.
 * You should not need to implement this method.
 */
- (void)ubuduIOSSDK_receivedDebugData:(id)data;

@end
