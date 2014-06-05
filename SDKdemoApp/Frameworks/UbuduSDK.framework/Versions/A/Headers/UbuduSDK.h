//
//  UbuduSDK.h
//  UbuduSDK
//
//  Created by Piotr Barszczewski on 6/20/13.
//  Copyright (c) 2013 Ubudu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "UbuduSDKDelegate.h"
#import "UbuduErrorCodes.h"
#import "UbuduUser.h"

@interface UbuduSDK : NSObject

/* The delegate object that will receive the SDK events.
 * You should set this property rigth when you initialize the SDK so you won't miss any event.
 */
@property (nonatomic, weak) id<UbuduSDKDelegate> delegate;

/* Is the SDK currently running.
 */
@property (nonatomic, readonly, getter=isRunning) BOOL running;

/* The Ubudu namespace of the application.
 * Should be set to the value provided by the Ubudu manager in order to retrieve the rules you defined for your application.
 * You must set this value before starting the SDK.
 */
@property (nonatomic, copy) NSString *appNamespace;

/* Enable or disable the advertisements feature of the SDK.
 */
@property (nonatomic) BOOL localizedAdsEnabled;

/* Enable or disable the beacons features of the SDK. Enabled by default but only if the device supports beacons.
 */
@property (nonatomic) BOOL beaconsEnabled;

/* Enable or disable the geofencing features of the SDK. Enabled by default but only if the device supports geofencing.
 */
@property (nonatomic) BOOL geofencesEnabled;

/* View controller used to modally display the view controllers for PassBook and Web Page actions.
 * If not set the SDK tries to use the current window's root view controller,
 * but it may already be presenting a view controller, in which case the SDK won't be able to present the action view controller.
 */
@property (nonatomic, weak) UIViewController *presentationViewController;

/* An extention point that permits to link business data about your users to the Ubudu users that the SDK and back office use.
 * These data are automatically uploaded on the Ubudu back office.
 */
@property (nonatomic, strong) UbuduUser *user;

/* The minimum delay, in seconds, between two updates of the geofences and beacons data from the back office.
 */
@property (nonatomic) NSUInteger refreshInterval;

/* Base URL used to construct the request made against the web services API.
 * This should looks like @"https://example.com"
 */
@property (nonatomic, copy) NSURL *baseAPIUrl;

/* Version of the SDK.
 */
@property (nonatomic, readonly) NSString *SDKVersion;



/* Lazy singleton instance of the Ubudu SDK.
 */
+ (UbuduSDK *)sharedInstance;

/* Check whether the current device supports geofences.
 */
+ (BOOL)deviceSupportsGeofences:(UIDevice *)device error:(NSError **)error;

/* Check whether the current device supports beacons.
 * Beacons support has been introduced by Apple in iOS 7.0 and the device must support Bluetooth Low Energy
 * (which is the case starting with the iPhone 4S and iPad 3rd generation).
 */
+ (BOOL)deviceSupportsBeacons:(UIDevice *)device error:(NSError **)error;



/* Start the SDK.
 * This will start the location and/or beacons monitoring and actions will be triggered when necessary.
 */
- (BOOL)start:(NSError **)error;

/* Restore the state of the SDK when the application is awaken by the system or returns from background.
 * You should call this method in the application:didFinishLaunchingWithOptions: method of your AppDelegate implementation.
 */
- (BOOL)resume:(UIApplication *)application launchOptions:(NSDictionary *)launchOptions error:(NSError **)error;

/* Stop the SDK.
 * Location and beacons will not be monitored anymore and no action will be triggered.
 */
- (void)stop;

/* Call this method in order to give back to the SDK a notification that had been presented to the user.
 * This will permit to the SDK to execute the action associated to the local notification, like an open passbook request or an open web page request.
 *
 * Typically you should call this from the application:didReceiveLocalNotification: method of your AppDelegate.
 */
- (void)executeLocalNotificationActions:(UILocalNotification *)localNotification;

/* Update the information associated to the Ubudu user (provided in the user property).
 * This will force the user data being (re-)sent to the back office and the rules to be update to match the new user tags.
 */
- (void)updateUserInformation;

/* Reset the trigger counters of all rules, for geofences and beacons. The per-rule and per-group counters will be reset.
 * This is handy for developping and testing purpose. You may not want to call this function when your app is in production because it will mess with the min & max events defined in the back-office.
 */
- (BOOL)resetCounters:(NSError **)error;;

/* Clear all data stored by the SDK.
 */
- (BOOL)removeAllData:(NSError **)error;



/* Set the UUID of the beacons you want to monitor.
 */
- (BOOL)setBeaconProximityUUID:(NSString *)proximityUUID identifier:(NSString *)identifier error:(NSError **)error;



/* Update the location.
 * Geofences must be enabled.
 */
- (BOOL)updateLocation:(NSError **)error;

/* Get the lalitude of the last known location.
 * Geofences must be enabled.
 */
- (double)getCurrentLatitude;

/* Get the longitude of the last known location.
 * Geofences must be enabled.
 */
- (double)getCurrentLongitude;



/* Set the UIView placeholder you want to use to automatically display the received advertisements.
 * If you want to manually handle the display of the advertisements, you should implement the ubudu:didReceiveNewAdView:triggeredBy:
 * method of the UbuduSDKDelegate, in which case the view specifid with this setter will not be used.
 */
- (void)setAdViewPlaceholder:(UIView *)adPlaceholder;

/* Return the ad UIView with currently loaded contents.
 */
- (UIView *)getAdView;



/***************************************************************
 * DO NOT USE: Methods made public for development purpose only
****************************************************************/
- (NSArray *)_getAllStoredGeofencesAsCLRegions;
- (NSArray *)_getAllStoredGeofencesAsNSDictionaries;
- (BOOL)_geofenceIsMonitored:(NSString *)geofenceId;
- (BOOL)_geofenceIsCurrent:(NSString *)geofenceId;
- (BOOL)_executeActionsForGeofence:(NSString *)geofenceId error:(NSError **)error;

- (NSArray *)_getAllCurrentBeacons;

- (NSArray *)_getStoredSDKLogEvents:(int)startPage perPage:(int)perPage;
- (NSManagedObjectContext *)getSDKManagedObjectContext;
/*****************
 * DO NOT USE END
 *****************/

@end
