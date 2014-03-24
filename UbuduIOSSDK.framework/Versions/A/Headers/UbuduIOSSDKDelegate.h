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

- (void)ubuduIOSSDK_receivedOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy;
- (void)ubuduIOSSDK_receivedOpenPassbookRequest:(NSURL *)aPassbookUrl triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy;
- (void)ubuduIOSSDK_receivedRegionNotification:(NSDictionary *)notificationData triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy;
- (void)ubuduIOSSDK_receivedSDKNotification:(NSDictionary *)notificationData triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy;
- (void)ubuduIOSSDK_receivedLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy;

- (void)ubuduIOSSDK_receivedNewAdView:(UIView *)view triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy;
- (void)ubuduIOSSDK_receivedErrorNotification:(NSError *)error;

//Beacon related callbacks
- (void)ubuduIOSSDK_foundNewBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;
- (void)ubuduIOSSDK_pingReceivedFromBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;
- (void)ubuduIOSSDK_updatedBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;
- (void)ubuduIOSSDK_lostBeaconSignal:(NSString *)beaconName userInfo:(NSDictionary *)userInfo;

//Debug callbacks
- (void)ubuduIOSSDK_receivedLocationChange:(CLLocation *)newLocation;
- (void)ubuduIOSSDK_receivedEnterRegionNotification:(CLRegion *)region;
- (void)ubuduIOSSDK_receivedExitRegionNotification:(CLRegion *)region;

- (void)ubuduIOSSDK_receivedDebugData:(id)data;




@end
