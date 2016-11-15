//
//  UbuduSDK.h
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
#import <UIKit/UIKit.h>

#import "UbuduSDKDelegate.h"
#import "UbuduErrorCodes.h"
#import "UbuduUser.h"
#import "UbuduAuthorizationManager.h"

/**
 *  Result of a local content update request.
 */
typedef NS_ENUM(NSUInteger, UbuduServerSyncResult){
    /** Content update request succeeded. */
    UbuduServerSyncResultUpdated,
    /** Content update request failed. */
    UbuduServerSyncResultFailed
};


/**
 *  The `UbuduSDK` class contains the main interface to use the Ubudu SDK.
 *
 *  You typically use this class to setup your application, receive events and customize the SDK behavior.
 *  `UbuduSDK` is a singleton class. You can retrieve the singleton instance using the `sharedInstance` class method and should never instanciate one yourself.
 */
@interface UbuduSDK : NSObject



/**
 *  Lazy singleton instance of the Ubudu SDK.
 *
 *  @return The `UbuduSDK` singleton instance.
 */
+ (UbuduSDK *)sharedInstance;

/**
 *  Check whether the current device supports geofences.
 *
 *  @return YES if the current device supports geofence based features of the SDK, NO otherwise.
 *
 *  @see geofencesEnabled
 */
+ (BOOL)deviceSupportsGeofences;

/**
 *  Check whether the current device supports beacons.
 *
 *  Beacons support has been introduced by Apple in iOS 7.0 and the device must support Bluetooth Low Energy
 *  This is the case with for Apple device starting with the iPhone 4S and iPad 3rd generation.
 *
 *  @return YES if the current device supports beacons based features of the SDK, NO otherwise.
 *
 *  @see beaconsEnabled
 */
+ (BOOL)deviceSupportsBeacons;



/**
 *  The delegate object that will receive the SDK events.
 *
 *  You should set this property before starting the SDK in order to not miss any event.
 */
@property (nonatomic, weak) id<UbuduSDKDelegate> delegate;

/**
 *  Is the SDK currently started.
 */
@property (nonatomic, readonly, getter=isRunning) BOOL running;

/**
 *  The Ubudu namespace of the application. Must be set before starting the SDK.
 *
 *  Need to be set to the value provided by the Ubudu manager platform in order to retrieve the rules you defined for your application.
 */
@property (nonatomic, copy) NSString *appNamespace;

/**
 *  Restricted feature! The URL that the SDK uses to access the platform API. Set by default to Ubudu's manager platform API.
 *
 *  This feature is restricted to servers explicitly allowed by Ubudu. Contact us for more information.
 */
@property (nonatomic, copy) NSString *baseURL;

/**
 *  Enable or disable the beacons features of the SDK. Enabled by default if the device supports beacons.
 *
 *  @see deviceSupportsBeacons
 */
@property (nonatomic) BOOL beaconsEnabled;

/**
 *  Request "When In Use" authorization for location services instead of "Always". Default is NO, which means the SDK will request "Always" location authorization.
 *
 *  By settings this to YES you won't get background support (your app won't be awaken when near your beacons, rules won't trigger when the app is killed or in the background).
 *  However you will still be able to get rules to trigger when the app is in foreground.
 *  You must set this property BEFORE starting the SDK for the FIRST time. Changes done after first SDK start won't have any effect, even if app/decide is restarted.
 *
 *  @note Do not set this to YES if you plan to use geofences features! Geofencing requires "Always" mode to work.
 */
@property (nonatomic) BOOL requestWhenInUseAuthorization;

/**
 *  Use only with a good reason as this will keep location updates running. Requires "location" background-mode capability. Default is NO.
 *
 *  If you use this feature (iBeacon ranging time is supposed to be very limited) you will need to justify to Apple
 *  why is that you need to always access the position of your users in the background (aka why do you need to use the "location" background mode capability).
 *
 *  Also it will use more battery as the location service (means usage of GPS/Cell Tower/Wifi) will need to run to keep receiving iBeacon ranging updates.
 *
 *  We advise very much about enabling this only temporarilly when providing a visible service to the user.
 *  You can dynamically switch the feature on/off by setting this property while the SDK is running.
 *
 *  Finally note that the extended background ranging time can only be granted to your application if the app comes to the foreground once after you enable this feature.
 *  If enabled in foregroun, il will be active immediatelly, if enable in background your app will need to be brought foreground once to get the extended background ranging time.
 */
@property (nonatomic) BOOL useExtendedBackgroundRangingTime;

/**
 *  Enable or disable the geofence features of the SDK. Enabled by default if the device supports geofencing.
 *
 *  @see deviceSupportsGeofences
 */
@property (nonatomic) BOOL geofencesEnabled;

/**
 *  If not nil, the view controller used to modally present the SDK view controllers for actions like "passbook" and "web page". Default is nil.
 *
 *  If not set the SDK tries to use the topmost, currently visible, view controller (the view controller "on top" of the current view controllers stack).
 *  The SDK may fail to retrieve such view controller, particularly if your app uses custom container view controllers for which the SDK doesn't know how to traverse children view controllers.
 */
@property (nonatomic, weak) UIViewController *presentationViewController;

/**
 *  An extention point that permits to link business data about your users to the Ubudu users that the SDK and Ubudu manager platform use.
 *
 *  These data are automatically uploaded to the Ubudu platform every time you assign this property or change one of the `UbuduUser` properties.
 *
 *  @see setUser:success:failure: method to set new user
 */
@property (nonatomic, strong, readonly) UbuduUser *user;

/**
 *  Enable the generation of a local file that will contain debug log information about what the SDK does. Default is NO.
 *
 *  Should not be enabled in production.
 *
 *  @see getDebugFileContent
 *  @see clearDebugFile
 */
@property (nonatomic, getter=isFileLogEnabled) BOOL fileLogEnabled;

/**
 *  The flag indicates if SDK can collect idfa for advanced user statistics. Note that this value will be NO if a user has limited ad tracking.
 */
@property (nonatomic, getter=isIDFACollectionEnabled) BOOL enableIDFACollection;

/**
 *  Version of the SDK.
 */
@property (nonatomic, readonly) NSString *SDKVersion;



/**
 *  Start the SDK. This will start the location and/or beacons monitoring. Rules will trigger when matching conditions are met and actions will be executed.
 *
 *  @param error If passed a non-NULL value then will be set to a NSError object if an error occured, let unmodified otherwise.
 *
 *  @note The SDK start is asynchronous, so the SDK may not be effectively started upon method return.
 *
 *  @return YES if the SDK is starting, NO if the start request failed.
 */
- (BOOL)start:(NSError **)error;

/**
 *  Start the SDK if it was started last time app got killed.
 *
 *  @deprecated Do not use this method, instead set you `appNamespace` and call `start:`, typically from your AppDelegate.
 *
 *  @see start:
 */
- (BOOL)resume:(UIApplication *)application launchOptions:(NSDictionary *)launchOptions error:(NSError **)error;

/**
 *  Stop the SDK. Do not stop the SDK on app kill if you want to get background support!
 *
 *  Geofences and beacons will not be monitored anymore and no more action will be triggered until you call again the `start:` method.
 *  Your app will not have geofences/beacons background support anymore and won't be awaken.
 */
- (void)stop;

/**
 *  Give back to the SDK a local notification previously presented to the user that has been opened.
 *
 *  This will permit to the SDK to execute the action associated to the local notification, like an open webpage (or passbook) request.
 *  Typically you should call this from the `application:didReceiveLocalNotification:` method of your `UIApplicationDelegate`.
 *
 *  @param localNotification The local notification provided by the system that has been opened.
 */
- (void)executeLocalNotificationActions:(UILocalNotification *)localNotification;

/**
 *  Give back to the SDK a local notification previously presented to the user that has been opened.
 *
 *  This will permit to the SDK to execute the action associated to the local notification, like an open webpage (or passbook) request.
 *  Typically you should call this from the `userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler:` method of your `UNUserNotificationCenterDelegate`.
 *
 *  @param notificationRequest The notification request provided by the system with the notification response.
 */
- (void)executeNotificationRequestActions:(UNNotificationRequest *)notificationRequest;

/**
 *  Display a webpage.
 *
 *  @param url - url of the web page
 *
 *  @return YES - if web page is dispayed and NO if sdk can't open a web page
 */
- (BOOL)openWebPageForUrl:(NSURL *)url;

/**
 *  Display a wallet ticket.
 *
 *  @param url - url of the web page
 *
 *  @return YES - if web page is dispayed and NO if sdk can't open a wallet ticket
 */
- (BOOL)openPassbookForUrl:(NSURL *)url;

/**
 *  Display a deep link.
 *
 *  @param url - url of the web page
 *
 *  @return YES - if web page is dispayed and NO if sdk can't open a deep link
 */
- (BOOL)openDeepLinkForURL:(NSURL *)url;

/**
 *  This method sets the custom headers used for server notifications requests only.
 */
- (void)setServerNotificationRequestHeader:(NSString *)header value:(NSString *)value;

/**
 *  Call this method to give a chance to the SDK to synchronize its local content (mainly, your rules) with the online manegement platform.
 *
 *  This method is mainly intended to be called via the background fetch feature (introduced with iOS 7) from the `application:performFetchWithCompletionHandler:` method of your `UIApplicationDelegate`, however it is not an error to call this from elsewhere.
 
 *  You don't have the insurance that the SDK will effectivelly perform an update of the content.
 *  Indeed if an update has been performed recently the SDK may consider the local content recent enough and silently ignore your request.
 *
 *  @param completionHandler This block will be called once update is done or has failed. The "result" parameter will incate if the update succeeded.
 */
- (void)performServerSyncWithCompletionHandler:(void (^)(UbuduServerSyncResult result))completionHandler;


/**
 *  Reset the trigger counters of all rules (geofences and beacons).
 *
 *  The per-rule and per-group counters will be reset. This is handy for developping and testing purpose.
 *  However you should not call this method when your app is in production because it will mess with the min & max event limits set in the back-office.
 *
 *  @param error If not NULL then the pointer is set to a NSError object if an error occured, let unmodified otherwise.
 *
 *  @return YES if all counters have been successfully reset, NO otherwise.
 */
- (BOOL)resetCounters:(NSError **)error;

/**
 *  Clear all data stored by the SDK.
 *
 *  If the SDK is started, it will be stopped, the data will be cleared, then the SDK will be restarted.
 *
 *  @param error If passed a non-NULL value then it will be set to a NSError object if an error occured, let unmodified otherwise.
 *
 *  @return YES if all SDK generated data have been successfully deleted and, if it was started, the SDK has successfully restarted, NO if either failed.
 */
- (BOOL)removeAllData:(NSError **)error;


/**
 *  Returns the content of the debug log file.
 *
 *  @return The current debug log file content.
 *
 *  @see fileLogEnabled
 */
- (NSData *)getDebugFileContent;

/**
 *  Erase the debug log file.
 *
 *  @see fileLogEnabled
 */
- (void)clearDebugFile;


/**
 *  Request a force update of the GPS location of the device. Geofences must be enabled.
 *
 *  The position update is done asynchronously, so may not be reflected immediatelly upon method return.
 *
 *  @param error If passed a non-NULL value then will be set to a NSError object if an error occured, let unmodified otherwise.
 *
 *  @return Was the update request successfully submitted.
 *
 *  @see geofencesEnabled
 */
- (BOOL)updateLocation:(NSError **)error;

/**
 *  Get the lalitude of the last known location. Geofences must be enabled.
 *
 *  @return The current latitude of the device. -1.0 if unknwown or unavailable.
 *
 *  @see geofencesEnabled
 */
- (double)getCurrentLatitude;

/**
 *  Get the longitude of the last known location. Geofences must be enabled.
 *
 *  @return The current longitude of the device. -1.0 if unknwown or unavailable.
 *
 *  @see geofencesEnabled
 */
- (double)getCurrentLongitude;

/**
 *  An extention point that permits to link business data about your users to the Ubudu users that the SDK and Ubudu manager platform use.
 *
 *  These data are automatically uploaded to the Ubudu platform every time you assign this property or change one of the `UbuduUser` properties.
 *
 *  @param newUser UbuduUser object
 *  @param success block called when new user is properly set
 *  @param failuer block called when error occured while setting a new user
 */

/**
 *  An extention point that permits to link business data about your users to the Ubudu users that the SDK and Ubudu manager platform use.
 *
 *  These data are automatically uploaded to the Ubudu platform every time you assign this property or change one of the `UbuduUser` properties.
 */

- (void)setUser:(UbuduUser *)newUser
        success:(void (^)())success
        failure:(void (^)(NSError *error))failure;

/**
 * Registers the device push notifications token for cloud messaging (e.g. Apple Push Notifications)
 *
 * @param pushToken push notifications device token for cloud messaging
 * @param success completion callback
 * @param failure completion callback
 */
- (void)registerCloudMessagingPushNotificationsDeviceToken:(NSData *) pushToken
                                                   success:(void (^)()) success
                                                   failure:(void (^)(NSError *error))failure;

@end
