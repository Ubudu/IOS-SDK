//
//  UbuduAuthorizationManager.h
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
#import <CoreBluetooth/CoreBluetooth.h>

#import "UbuduAuthorizationDelegate.h"

/**
 *  Module that allows you to easily check the status of various status required or useful for geofence and beacons monitoring.
 */
@interface UbuduAuthorizationManager : NSObject

/**
 *  Will be YES if beacon features of `UbuduSDK` are enabled and UbuduSDK is currently running.
 *
 *  @see UbuduSDK.beaconsEnabled
 */
@property (nonatomic, readonly, getter = isUbuduBeaconsServiceEnabled) BOOL ubuduBeaconsServiceEnabled;

/**
 *  Will be YES if geofence features of `UbuduSDK` are enabled and UbuduSDK is currently running.
 *
 *  @see UbuduSDK.geofencesEnabled
 */
@property (nonatomic, readonly, getter = isUbuduGeofencesServiceEnabled) BOOL ubuduGeofencesServiceEnabled;

/**
 *  Will be YES if both global and app-specific location services are enabled.
 */
@property (nonatomic, readonly, getter = isLocationServiceEnabled) BOOL locationServiceEnabled;

/**
 *  YES if bluetooth is turned on.
 */
@property (nonatomic, readonly, getter = isBluetoothEnabled) BOOL bluetoothEnabled;

/**
 *  YES if background refresh is enabled for the application.
 */
@property (nonatomic, readonly, getter = isBackgroundRefreshEnabled) BOOL backgroundRefreshEnabled;

/**
 *  Can the application post notifications containing a banner, a sound and a badge.
 *
 *  This will be YES if user has accepted notifications from your app and has not turned off any of the rights (banner, sound & badge).
 */
@property (nonatomic, readonly, getter = areAllNotificationRightsGranted) BOOL allNotificationRightsGranted;

/**
 *  Can the application post notifications containing a banner (sound and badge rights may not be allowed).
 *
 *  You are most likely interested in this specific right (banner right, which means display a message to the user.
 *  Details on how the message is precisely presented (alert, banner, ignored) depend on user's settings, we can't know them programatically.
 */
@property (nonatomic, readonly, getter = isBannerNotificationRightGranted) BOOL bannerNotificationRightGranted;

/**
 *  Delegate to receive notifications when the value of one of the above properties changes.
 */
@property (nonatomic, weak) id<UbuduAuthorizationDelegate> authorizationDelegate;

/**
 *  Shows a system `UIAlertView` with a button that redirects to the application settings, directly on Bluetooth view.
 */
- (void)showEnableBluetoothAlert;

/**
 *  Opens the application settings on iOS 8, shows an alert with instructions to enable location service on iOS 7 and below.
 *
 *  Message of the alert can currently only be in English.
 */
- (void)showEnableLocationServiceUI;

/**
 *  Opens the application settings on iOS 8, shows an alert with instructions to enable background refresh on iOS 7 and below.
 *
 *  Message of the alert can currently only be in English.
 */
- (void)showEnableBackgroundRefreshUI;

@end
