//
//  UbuduIOSSDK.h
//  UbuduIOSSDK
//
//  Created by Piotr Barszczewski on 6/20/13.
//  Copyright (c) 2013 Ubudu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "UbuduIOSSDKDelegate.h"
#import "UbuduIOSSDKErrorCodes.h"
#import "UbuduIOSSDKUser.h"

@interface UbuduIOSSDK : NSObject


/* This property is used to check the application state and request location updates based on that value.
 * You should set this property when you initialize the SDK.
 */
@property (nonatomic, weak) UIApplication *application;

/* The delegate object that will receive the SDK events.
 * You should set this property rigth when you initialize the SDK so you won't miss any event.
 */
@property (nonatomic, weak) id<UbuduIOSSDKDelegate> delegate;

/* Is the SDK currently running.
 */
@property (nonatomic,readonly) BOOL isRunning;

/* The Ubudu namespace of the application.
 * Must be set to the value provided by the Ubudu manager in order to retrieve the rules you defined for your application.
 */
@property (nonatomic, strong) NSString *useNamespace;

/* Enable or disable the advertisements feature of the SDK.
 */
@property (nonatomic) BOOL locationAdsEnabled;

/* Enable or disable the beacon feature of the SDK.
 */
@property (nonatomic) BOOL beaconsEnabled;

/* An extention point that permits to link business data about your users to the Ubudu users that the SDK and back office use.
 * These data are automatically uploaded on the Ubudu back office.
 */
@property (nonatomic, strong) UbuduIOSSDKUser * user;

/* The minimum delay in seconds between two updates of the geofences and beacons data from the Ubudu back office.
 */
@property (nonatomic) int refreshInterval;



/* Lazy singleton instance of the Ubudu SDK.
 */
+ (UbuduIOSSDK *)sharedInstance;

/* Check whether the current device supports geofences.
 */
+ (BOOL)deviceSupportsGeofences:(UIDevice *)device error:(NSError **)error;

/* Check whether the current device supports beacons.
 * Beacons support has been introduced by Apple in iOS 7.0 and the device must support Bluetooth Low Energy
 * (which is the case starting with the iPhone 4S and iPad 3rd generation).
 */
+ (BOOL)deviceSupportsBeacons:(UIDevice *)device error:(NSError **)error;

/* Version of the SDK.
 */
+ (NSString *)SDKVersion;



/* Start the SDK.
 * This will start the location monitoring and actions will be triggered when necessary.
 */
- (BOOL)start:(NSError **)error;

/* Restore the state of the SDK when the application is awaken by the system or returns from background.
 * You should call this method in the application:didFinishLaunchingWithOptions: method of your AppDelegate implementation.
 */
- (BOOL)resume:(UIApplication *)application launchOptions:(NSDictionary *)launchOptions error:(NSError **)error;

/* Stop the SDK.
 * Location will not be monitored anymore and no action will be triggered.
 */
- (void)stop;

/* Set the base URL used to construct the request made against the web services API.
 * This should looks like @"https://example.com"
 */
- (void)setBaseAPIUrl:(NSURL *)url;

/* Set the UUID of the beacons you want to monitor.
 */
- (BOOL)setBeaconProximityUUID:(NSString *)proximityUUID identifier:(NSString *)identifier error:(NSError **)error;

/* Call this method in order to give back to the SDK a notification that had been presented to the user.
 * This will permit to the SDK to execute the action associated to the local notification, like an open passbook request or an open web page request.
 *
 * Typically you should call this from the
 */
- (void)receiveLocalNotification:(UILocalNotification *)aLocalNotification;

/* Update the information associated to the Ubudu user (provided in the user property).
 * This will force the user data being sent to the Ubudu back office API.
 */
- (void)updateUserInformation;



/* Update the location.
 */
- (BOOL)updateLocation:(NSError **)error;

/* Get the lalitude of the last known location.
 */
- (double)getCurrentLatitude;

/* Get the longitude of the last known location.
 */
- (double)getCurrentLongitude;

/* Clear all data stored by the SDK.
 */
- (BOOL)removeAllData:(NSError **)error;



/* Set the UIView you want to use for automatic display of the received advertisements.
 * If you want to handle manually the display of the advertisements, you should implement the ubuduIOSSDK_receivedNewAdView:triggeredBy: method of the UbuduIOSSDKDelegate.
 */
- (void)setAdViewPlaceholder:(UIView *)adPlaceholder;

/* Return the UIView placeholder registered for automatic advertisements display.
 * Will return nil if the view is not set.
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
