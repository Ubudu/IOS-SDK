//
//  UbuduAuthorizationDelegate.h
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
 *  A protocol you can implement if you want to monitor changes on properties of a `UbuduAuthorizationManager` object.
 */
@protocol UbuduAuthorizationDelegate <NSObject>

@optional

/*
 *  Methods used to inform you that the status of one of the UbuduSDK services.
 */

/**
 *  Beacons service status changed. Beacons service is considered enabled if `UbuduSDK.beaconsEnabled` is YES and UbuduSDK is currently running.
 *
 *  @param isEnabled Is the beacons service enabled and running.
 */
- (void)ubuduBeaconsServiceStatusDidChange:(BOOL)isEnabled;

/**
 *  Goefences service status changed. Geofences service is enabled if UbuduSDK.geofencesEnabled is YES and that UbuduSDK is currently running.
 *
 *  @param isEnabled Is the geofences service enabled and running.
 */
- (void)ubuduGeofencesServiceStatusDidChange:(BOOL)isEnabled;


/*
 *  Methods used to inform you that the status of a service used by the UbuduSDK has changed.
 */

/**
 *  Global or app-specific location service status changed.
 *
 *  @param isEnabled Is the location service enabled for the application.
 */
- (void)locationServiceStatusDidChange:(BOOL)isEnabled;

/**
 *  Bluetooth status changed.
 *
 *  @param isEnabled Is the bluetooth currently turned on.
 */
- (void)bluetoothStatusDidChange:(BOOL)isEnabled;

/**
 *  Background refresh service status changed.
 *
 *  @param isEnabled Is the background refresh service enabled for the application.
 */
- (void)backgroundRefreshStatusDidChange:(BOOL)isEnabled;

@end