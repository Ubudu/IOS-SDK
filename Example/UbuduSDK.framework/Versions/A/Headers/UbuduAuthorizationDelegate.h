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

@protocol UbuduAuthorizationDelegate <NSObject>

@optional

/*
 * Methods used to inform you that the status of one of the feature of the UbuduSDK changed.
 */
- (void)ubuduBeaconsServiceStatusDidChange:(BOOL)isEnabled; // Beacons service is enabled if UbuduSDK.beaconsEnabled is YES and that UbuduSDK is currently running.
- (void)ubuduGeofencesServiceStatusDidChange:(BOOL)isEnabled; // Geofences service is enabled if UbuduSDK.geofencesEnabled is YES and that UbuduSDK is currently running.

/*
 * Methods used to inform you that the status of a service used by the UbuduSDK has changed.
 */
- (void)locationServiceStatusDidChange:(BOOL)isEnabled; // Global or app-specific location service status changed.
- (void)bluetoothStatusDidChange:(BOOL)isEnabled;
- (void)backgroundRefreshStatusDidChange:(BOOL)isEnabled;

@end