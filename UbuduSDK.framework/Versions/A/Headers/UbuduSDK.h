//
//  UbuduSDK.h
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
#import <UIKit/UIKit.h>

#import "UbuduSDKDelegate.h"
#import "UbuduErrorCodes.h"
#import "UbuduUser.h"
#import "UbuduAuthorizationManager.h"

@interface UbuduSDK : NSObject

/* The delegate object that will receive the SDK events.
 * You should set this property rigth when you initialize the SDK so you won't miss any event.
 */
@property (nonatomic, weak) id<UbuduSDKDelegate> delegate;

/* Is the SDK started.
 */
@property (nonatomic, readonly, getter=isRunning) BOOL running;

/* The Ubudu namespace of the application.
 * Should be set to the value provided on the Ubudu manager website in order to retrieve the rules you defined for your application.
 * You MUST set this value before starting the SDK.
 */
@property (nonatomic, copy) NSString *appNamespace;

/* The URL to use to access the API.
 * This feature is restricted to servers explicitly allowed by Ubudu. Contact us for more information.
 */
@property (nonatomic, copy) NSString *baseURL;

/* Enable or disable the beacons features of the SDK. Enabled by default but only if the device supports beacons.
 */
@property (nonatomic) BOOL beaconsEnabled;

/* Enable or disable the geofencing features of the SDK. Enabled by default but only if the device supports geofencing.
 */
@property (nonatomic) BOOL geofencesEnabled;

/* View controller used to modally present the view controllers for PassBook and Web Page actions.
 * If not set the SDK tries to use the currently visible view controller (view controller "on top" of the current window stack).
 * The SDK may fail to retrieve such view controller, particularly if your app uses custom container view controllers
 * for which the SDK doesn't know how to traverse children view controllers.
 */
@property (nonatomic, weak) UIViewController *presentationViewController;

/* An extention point that permits to link business data about your users to the Ubudu users that the SDK and Ubudu manager website use.
 * These data are automatically uploaded to the Ubudu cloud every time you assign this property or change one of its properties.
 */
@property (nonatomic, strong) UbuduUser *user;

/* Enable the generation of a local file that will contain debug information about what the SDK does.
 */
@property (nonatomic, getter=isFileLogEnabled) BOOL fileLogEnabled;

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
 * This is handy for developping and testing purpose. You should not call this method when your app is in production because it will mess with the min & max event limits set in the back-office.
 */
- (BOOL)resetCounters:(NSError **)error;

/* Clear all data stored by the SDK.
 * If the SDK is started, it will be stopped, the data will be cleared, then the SDK will be restarted.
 */
- (BOOL)removeAllData:(NSError **)error;


/* Returns the content of the debug log file.
 */
- (NSData *)getDebugFileContent;

/* Erase the debug log file.
 */
- (void)clearDebugFile;


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

@end
