//
//  UDAppDelegate.m
//  Ubudu-demo
//
//  Created by Jean-Baptiste Quesney on 3/5/14.
//  Copyright (c) 2014 Ubudu. All rights reserved.
//

#import <UbuduSDK/UbuduSDK.h>

#import "UDAppDelegate.h"
#import "UDDefinitions.h"
#import "UDDemoManager.h"
#import "UDOrderSummaryViewController.h"

#define kUDFirstNotificationName @"Discover today exclusive offers at Les Caves Particulières"
#define kUDSecondNotificationName @"Show this invitation to a Caves Particulieres hostess and enjoy an exclusive Hennessy tasting"
#define kUDNotificationTriggerThreshold 10.0f

@implementation UDAppDelegate

#pragma mark - AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [self initUbuduSDK];
    
    NSError * error = nil;
    BOOL hasResumed = [[UbuduSDK sharedInstance] resume:application launchOptions:launchOptions error:&error];
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
    // In this case we display a custom alert view instead of posting a normal notification
    if ([notifType isEqualToString:@"order"])
    {
        [self displayOrderAwaitingAlert];
    }
    else
    {
        // Send back to the SDK the notification (that may have been received in background)
        // So it can trigger the right action (passbook or web view for example)
        [[UbuduSDK sharedInstance] receiveLocalNotification:notification];
    }
}

#pragma mark - UbuduSDK

- (void)initUbuduSDK
{
    NSError *error = nil;
    BOOL deviceSupportsGeofences = [UbuduSDK deviceSupportsGeofences:[UIDevice currentDevice] error:&error];
    if (error != nil)
        NSLog(@"UbuduSDK error with deviceSupportsGeofences: %@", error);
    
    error = nil;
    BOOL deviceSupportsBeacons = [UbuduSDK deviceSupportsBeacons:[UIDevice currentDevice] error:&error];
    if (error != nil)
        NSLog(@"UbuduSDK error with deviceSupportsBeacons: %@", error);
    
    UbuduSDK *ubuduSDK = [UbuduSDK sharedInstance];
    if ([ubuduSDK isRunning] == NO && deviceSupportsGeofences && deviceSupportsBeacons) {
        ubuduSDK.application = [UIApplication sharedApplication];
        ubuduSDK.useNamespace = @"ff356b88057340a771e9b072d16278829c67b9a1";
        ubuduSDK.delegate = self;
        ubuduSDK.user = [[UbuduUser alloc] initWithID:nil withProperties:@{@"ext_id": kUDDefaultClientName}];
        
        NSError *error = nil;
        BOOL started = [ubuduSDK start:&error];
        if (!started) {
            NSLog(@"UbuduSDK start error: %@", error);
        }
    }
}

#pragma mark - UbuduSDKDelegate

- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)triggeredBy
{
    return YES;
}

- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)triggeredBy
{
    UDDemoManager *manager = [UDDemoManager sharedManager];
    BOOL shouldExecute = ([manager hasLocalNotificationBeenTriggered:[url absoluteString]] == NO);
    [manager markLocalNotificationAsTrigerred:[url absoluteString]];
    return shouldExecute;
}

- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenPassbookRequest:(NSURL *)passbookUrl triggeredBy:(UbuduTriggerSource)triggeredBy
{
    UDDemoManager *manager = [UDDemoManager sharedManager];
    BOOL shouldExecute = ([manager hasLocalNotificationBeenTriggered:[passbookUrl absoluteString]] == NO);
    [manager markLocalNotificationAsTrigerred:[passbookUrl absoluteString]];
    return shouldExecute;
}

// Uncomment the following methods to use a custom implementation of the corresponding action

//- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)triggeredBy
//{
//    NSLog(@"Ubudu executeOpenWebPageRequest url = %@", url);
//}

//- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenPassbookRequest:(NSURL *)passbookUrl triggeredBy:(UbuduTriggerSource)triggeredBy
//{
//    NSLog(@"Ubudu executeOpenPassbookRequest passbookUrl = %@", passbookUrl);
//}

//- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveRegionNotification:(NSDictionary *)notificationData triggeredBy:(UbuduTriggerSource)triggeredBy
//{
//    NSLog(@"Ubudu didReceiveRegionNotification notificationData = %@", notificationData);
//}

- (void)ubudu:(UbuduSDK *)ubuduSDK executeLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)triggeredBy
{
    NSLog(@"Ubudu executeLocalNotificationRequest localNotification = %@", localNotification);
    UDDemoManager *manager = [UDDemoManager sharedManager];
    
    // Post notification only if it's a new one (avoid presenting multiple identical notification to the user)
    if ([manager hasLocalNotificationBeenTriggered:localNotification.alertBody] == NO)
    {
        if ([localNotification.alertBody isEqualToString:kUDSecondNotificationName]) {
            if ([manager hasLocalNotificationBeenTriggered:kUDFirstNotificationName] == YES) {
                NSDate *triggerDate = [manager lastNotificationTriggerDate:kUDFirstNotificationName];
                NSDate *currentDate = [NSDate date];
                NSTimeInterval deltaTime = [currentDate timeIntervalSinceDate:triggerDate];
                if (deltaTime > kUDNotificationTriggerThreshold) {
                    NSLog(@"Delta time between outdoor and indoor notifications = %f > threshold (%f) => posting indoor notification", deltaTime, kUDNotificationTriggerThreshold);
                    [manager markLocalNotificationAsTrigerred:localNotification.alertBody];
                    [[UIApplication sharedApplication] presentLocalNotificationNow:localNotification];
                } else {
                    NSLog(@"Delta time %f < threshold (%f) => not posting", deltaTime, kUDNotificationTriggerThreshold);
                }
            } else {
                NSLog(@"Outdoor notification not posted, not posting indoor notification");
            }
        } else {
            [manager markLocalNotificationAsTrigerred:localNotification.alertBody];
            [[UIApplication sharedApplication] presentLocalNotificationNow:localNotification];
        }
    }
}

- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveNewAdView:(UIView *)view triggeredBy:(UbuduTriggerSource)triggeredBy;
{
    NSLog(@"Ubudu didReceiveNewAdView view = %@", view);
}

- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveErrorNotification:(NSError *)error;
{
    NSLog(@"Ubudu didReceiveErrorNotification error = %@", error);
}

// Beacon related callbacks
- (void)ubudu:(UbuduSDK *)ubuduSDK didFindNewBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo
{
    //    NSLog(@"Ubudu didFindNewBeacon userInfo = %@", userInfo);
}

- (void)ubudu:(UbuduSDK *)ubuduSDK didReceivePingFromBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo
{
    //    NSLog(@"Ubudu didReceivePingFromBeacon userInfo = %@", userInfo);
}

- (void)ubudu:(UbuduSDK *)ubuduSDK didUpdateBeacon:(NSString *)beaconName userInfo:(NSDictionary *)userInfo
{
    //    NSLog(@"Ubudu didUpdateBeacon userInfo = %@", userInfo);
}

- (void)ubudu:(UbuduSDK *)ubuduSDK didLoseBeaconSignal:(NSString *)beaconName userInfo:(NSDictionary *)userInfo
{
    //    NSLog(@"Ubudu didLoseBeaconSignal userInfo = %@", userInfo);
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
