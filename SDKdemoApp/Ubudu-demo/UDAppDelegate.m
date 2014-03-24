//
//  UDAppDelegate.m
//  Ubudu-demo
//
//  Created by Jean-Baptiste Quesney on 3/5/14.
//  Copyright (c) 2014 Ubudu. All rights reserved.
//

#import <UbuduIOSSDK/UbuduIOSSDK.h>

#import "UDAppDelegate.h"
#import "UDDefinitions.h"
#import "UDDemoManager.h"
#import "UDOrderSummaryViewController.h"

@implementation UDAppDelegate

#pragma mark - AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [self initUbuduSDK];
    
    NSError * error = nil;
    BOOL hasResumed = [[UbuduIOSSDK sharedInstance] resume:application launchOptions:launchOptions error:&error];
    (void)hasResumed;
    if (error != nil) {
        NSLog(@"UbuduSDK resume error: %@", error);
    }
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    application.applicationIconBadgeNumber = 0;
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification
{
    NSString *notifType = [notification.userInfo valueForKeyPath:@"payload.type"];

    // If the notification contains a custom payload that we want to handle
    if ([notifType isEqualToString:@"order"])
    {
        [self displayOrderAwaitingAlert];
    }
    else
    {
        // Send back to the SDK the notification (that may have been received in background)
        // So it can trigger the right action (passbook or web view for example)
        [[UbuduIOSSDK sharedInstance] receiveLocalNotification:notification];
    }
}

#pragma mark - Ubudu SDK

- (void)initUbuduSDK
{
    NSError *error = nil;
    BOOL deviceSupportsGeofences = [UbuduIOSSDK deviceSupportsGeofences:[UIDevice currentDevice] error:&error];
    if (error != nil)
        NSLog(@"UbuduSDK error with deviceSupportsGeofences: %@", error);
    
    error = nil;
    BOOL deviceSupportsBeacons = [UbuduIOSSDK deviceSupportsBeacons:[UIDevice currentDevice] error:&error];
    if (error != nil)
        NSLog(@"UbuduSDK error with deviceSupportsBeacons: %@", error);
    
    if ([[UbuduIOSSDK sharedInstance] isRunning] == NO && deviceSupportsGeofences && deviceSupportsBeacons) {
        UbuduIOSSDK *sdk = [UbuduIOSSDK sharedInstance];
        [sdk setDelegate:self];
        [sdk setUseNamespace:@"634b207ee2f313c109c58675b44324ac2d41e61e"];
        [sdk setApplication:[UIApplication sharedApplication]];
        [sdk setUser:[[UbuduIOSSDKUser alloc] initWithID:nil withProperties:@{@"ext_id": kUDDefaultClientName}]];
        
        NSError *error = nil;
        BOOL started = [[UbuduIOSSDK sharedInstance] start:&error];
        if (!started) {
            NSLog(@"UbuduSDK start error: %@", error);
        }
    }
}

#pragma mark - UbuduIOSSDK Delegate

- (void)ubuduIOSSDK_receivedOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy
{
    NSLog(@"ubuduIOSSDK_receivedOpenWebPageRequest url = %@", url);
}

- (void)ubuduIOSSDK_receivedOpenPassbookRequest:(NSURL *)aPassbookUrl triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy
{
    NSLog(@"ubuduIOSSDK_receivedOpenPassbookRequest aPassbookUrl = %@", aPassbookUrl);
}

- (void)ubuduIOSSDK_receivedRegionNotification:(NSDictionary *)notificationData triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy
{
//    NSLog(@"ubuduIOSSDK_receivedRegionNotification notificationData = %@", notificationData);
}

- (void)ubuduIOSSDK_receivedSDKNotification:(NSDictionary *)notificationData triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy
{
//    NSLog(@"ubuduIOSSDK_receivedSDKNotification notificationData = %@", notificationData);
}

- (void)ubuduIOSSDK_receivedLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy
{
    NSLog(@"ubuduIOSSDK_receivedLocalNotificationRequest localNotification = %@", localNotification);
    // Post notification only if it's a new one (avoid spamming the user)
    if ([[UDDemoManager sharedManager] hasLocalNotificationBeenTriggered:localNotification] == NO)
    {
        [[UDDemoManager sharedManager] markLocalNotificationAsTrigerred:localNotification];
        [[UIApplication sharedApplication] presentLocalNotificationNow:localNotification];
    }
}

- (void)ubuduIOSSDK_receivedNewAdView:(UIView *)view triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy
{
//    NSLog(@"ubuduIOSSDK_receivedNewAdView view = %@", view);
}

- (void)ubuduIOSSDK_receivedErrorNotification:(NSError *)error
{
    if (error != nil) {
        NSLog(@"ubuduIOSSDK_receivedErrorNotification %@", error);
    }
}

// Beacon related callbacks
- (void)ubuduIOSSDK_foundNewBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo
{
//    NSLog(@"ubuduIOSSDK_foundNewBeacon userInfo = %@", userInfo);
}

- (void)ubuduIOSSDK_pingReceivedFromBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo
{
//    NSLog(@"ubuduIOSSDK_pingReceivedFromBeacon userInfo = %@", userInfo);
}

- (void)ubuduIOSSDK_updatedBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo
{
//    NSLog(@"ubuduIOSSDK_updatedBeacon userInfo = %@", userInfo);
}

- (void)ubuduIOSSDK_lostBeaconSignal:(NSString *)beaconName userInfo:(NSDictionary *)userInfo
{
//    NSLog(@"ubuduIOSSDK_lostBeaconSignal userInfo = %@", userInfo);
}

// Debug callbacks
- (void)ubuduIOSSDK_receivedLocationChange:(CLLocation *)newLocation
{
//    NSLog(@"ubuduIOSSDK_receivedLocationChange newLocation = %@", newLocation);
}

- (void)ubuduIOSSDK_receivedEnterRegionNotification:(CLRegion *)region
{
//    NSLog(@"ubuduIOSSDK_receivedEnterRegionNotification region = %@", region);
}

- (void)ubuduIOSSDK_receivedExitRegionNotification:(CLRegion *)region
{
//    NSLog(@"ubuduIOSSDK_receivedExitRegionNotification region = %@", region);
}

- (void)ubuduIOSSDK_receivedDebugData:(id)data
{
//    NSLog(@"ubuduIOSSDK_receivedDebugData data = %@", data);
}

#pragma mark - Click & Collect Alert

- (void)displayOrderAwaitingAlert
{
    UIAlertView *alert = [[UIAlertView alloc] init];
    [alert setTitle:@"Your order"];
    [alert setMessage:@"Do you want to send your order to preparation now?"];
    [alert setDelegate:self];
    [alert addButtonWithTitle:@"No, I'll do it later"];
    [alert addButtonWithTitle:@"Yes"];
    [alert show];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0) {
        // No. Do nothing.
    } else if (buttonIndex == 1) {
        // Yes. Open order summary page.
        UIViewController * orderSummaryVC = [self.window.rootViewController.storyboard instantiateViewControllerWithIdentifier:@"UDOrderSummaryViewController"];
        [self.window.rootViewController presentViewController:orderSummaryVC animated:YES completion:nil];
    }
}

@end
