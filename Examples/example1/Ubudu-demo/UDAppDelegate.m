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
#import "UDOrderSummaryViewController.h"

@interface UDAppDelegate () <UbuduSDKDelegate>

@end

@implementation UDAppDelegate

#pragma mark - AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSError *error = nil;
//    [UbuduSDK sharedInstance].appNamespace = @"634b207ee2f313c109c58675b44324ac2d41e61e";
    [UbuduSDK sharedInstance].appNamespace = @"19300bf1225da9d5db5cd28b7a9caddc2b9c6341";
    [UbuduSDK sharedInstance].delegate = self;
//    [UbuduSDK sharedInstance].user = [[UbuduUser alloc] initWithID:kUDDefaultClientName];
    BOOL started = [[UbuduSDK sharedInstance] start:&error];
    if (!started) {
        NSLog(@"UbuduSDK start error: %@", error);
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
    
    // Reset app icon badge when the app becomes foreground
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
    if ([notifType isEqualToString:@"order"]) {
        [self displayOrderAwaitingAlert:@"Do you want to send your order to preparation now?"];
    } else {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Notification" message:notification.alertBody delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alert show];
    }
    
    // Send back to the SDK the notification (that may have been received in background)
    // So it can trigger the right action (passbook or web view for example)
    [[UbuduSDK sharedInstance] executeLocalNotificationActions:notification];

    // Clear the received notification
    [application cancelLocalNotification:notification];
    application.applicationIconBadgeNumber--;
}

#pragma mark - UbuduSDKDelegate

// Uncommented and implement any of the methods below if you want to programatically control the execution of the actions.
// Please check on the manager platform if the feature you want to implement to control the triggering of the rules is not already built-in, as it would be less work for you.

//- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteServerNotificationRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger {}
//- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)trigger {}
//- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger {}
//- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenPassbookRequest:(NSURL *)passUrl triggeredBy:(UbuduTriggerSource)trigger {}
//- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteOpenDeepLinkRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger {}


// Uncomment and implement any of the methods below to customize the execution of any type of action.

//- (void)ubudu:(UbuduSDK *)ubuduSDK executeServerNotificationRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger
//      success:(void (^)())successHandler failure:(void (^)(NSError* error))failureHandler {}

//- (void)ubudu:(UbuduSDK *)ubuduSDK executeLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)triggeredBy
//{
//    // That is what the SDK does by default
//    [[UIApplication sharedApplication] presentLocalNotificationNow:localNotification];
//}

//- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger {}

//- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenPassbookRequest:(NSURL *)passbookUrl triggeredBy:(UbuduTriggerSource)trigger {}

//- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenDeepLinkRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)trigger {}

- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveErrorNotification:(NSError *)error;
{
    NSLog(@"UBUDU SDK ERROR: %@", error);
}

// Beacons related callbacks

- (void)ubudu:(UbuduSDK *)ubuduSDK didEnterBeaconRegion:(NSString *)regionUUID userInfo:(NSDictionary *)userInfo
{
//    NSLog(@"Ubudu didEnterBeaconRegion userInfo = %@", userInfo);
}

- (void)ubudu:(UbuduSDK *)ubuduSDK didExitBeaconRegion:(NSString *)regionUUID userInfo:(NSDictionary *)userInfo
{
//    NSLog(@"Ubudu didExitBeaconRegion userInfo = %@", userInfo);
}

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

#pragma mark - Alerts

- (void)displayOrderAwaitingAlert:(NSString *)message
{
    UIAlertView *alert = [[UIAlertView alloc] init];
    [alert setTitle:@"Your order"];
    [alert setMessage:message];
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
        UIViewController *orderSummaryVC = [self.window.rootViewController.storyboard instantiateViewControllerWithIdentifier:@"UDOrderSummaryViewController"];
        [self.window.rootViewController presentViewController:orderSummaryVC animated:YES completion:nil];
    }
}

@end
