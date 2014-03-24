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

//this property is used to check application state and request location updates based on that value
@property (nonatomic, weak) UIApplication *application;
@property (nonatomic, weak) id<UbuduIOSSDKDelegate> delegate;
@property (nonatomic,readonly) BOOL isRunning;
@property (nonatomic, strong) NSString *useNamespace;
@property (nonatomic) BOOL locationAdsEnabled;
@property (nonatomic) BOOL beaconsEnabled;
@property (nonatomic, strong) UbuduIOSSDKUser * user;
@property (nonatomic) int refreshInterval;

+ (UbuduIOSSDK *)sharedInstance;

+ (BOOL)deviceSupportsGeofences:(UIDevice *)device error:(NSError **)error;
+ (BOOL)deviceSupportsBeacons:(UIDevice *)device error:(NSError **)error;

- (BOOL)start:(NSError **)error;
- (BOOL)resume:(UIApplication *)application launchOptions:(NSDictionary *)launchOptions error:(NSError **)error;
- (void)receiveLocalNotification:(UILocalNotification *)aLocalNotification;
- (void)setBaseAPIUrl:(NSURL *)url;
- (BOOL)setBeaconProximityUUID:(NSString *)proximityUUID identifier:(NSString *)identifier error:(NSError **)error;
- (void)stop;

- (void)updateUserInformation;

- (BOOL)updateLocation:(NSError **)error;
- (double)getCurrentLatitude;
- (double)getCurrentLongitude;
- (BOOL)removeAllData:(NSError **)error;

- (void)setAdViewPlaceholder:(UIView *)adPlaceholder;
- (UIView *)getAdView;

//Methods made public for development time
- (NSArray *)_getAllStoredGeofencesAsCLRegions;
- (NSArray *)_getAllStoredGeofencesAsNSDictionaries;
- (BOOL)_geofenceIsMonitored:(NSString *)geofenceId;
- (BOOL)_geofenceIsCurrent:(NSString *)geofenceId;
- (BOOL)_executeActionsForGeofence:(NSString *)geofenceId error:(NSError **)error;

- (NSArray *)_getAllCurrentBeacons;

- (NSArray *)_getStoredSDKLogEvents:(int)startPage perPage:(int)perPage;
- (NSManagedObjectContext *)getSDKManagedObjectContext;

+ (NSString *)SDKVersion;

@end
