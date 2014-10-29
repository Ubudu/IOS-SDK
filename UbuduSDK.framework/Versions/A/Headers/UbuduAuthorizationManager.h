//
//  UbuduAuthorizationManager.h
//  UbuduSDK
//
// Copyright (c) 2011-2014, UBUDU SAS
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

@interface UbuduAuthorizationManager : NSObject

@property (nonatomic, readonly, getter = isUbuduBeaconsServiceEnabled) BOOL ubuduBeaconsServiceEnabled;
@property (nonatomic, readonly, getter = isUbuduGeofencesServiceEnabled) BOOL ubuduGeofencesServiceEnabled;
@property (nonatomic, readonly, getter = isLocationServiceEnabled) BOOL locationServiceEnabled;
@property (nonatomic, readonly, getter = isBluetoothEnabled) BOOL bluetoothEnabled;
@property (nonatomic, readonly, getter = isBackgroundRefreshEnabled) BOOL backgroundRefreshEnabled;

@property (nonatomic, weak) id<UbuduAuthorizationDelegate> authorizationDelegate;

- (void)showEnableBluetoothAlert;
- (void)showEnableLocationServiceUI;
- (void)showEnableBackgroundRefreshUI;

@end
